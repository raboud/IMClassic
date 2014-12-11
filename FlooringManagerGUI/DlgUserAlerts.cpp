/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgUserAlerts.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgUserAlerts.h"
#include ".\dlguseralerts.h"
#include "GridUserAlerts.h"
#include "SetSettings.h"

const int TIMER_ID = 1;

// CDlgUserAlerts dialog

IMPLEMENT_DYNAMIC(CDlgUserAlerts, CDialog)
CDlgUserAlerts::CDlgUserAlerts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserAlerts::IDD, pParent)
{
	m_pgridUserAlerts = NULL;
}

CDlgUserAlerts::~CDlgUserAlerts()
{
	if (m_pgridUserAlerts != NULL)
	{
		delete m_pgridUserAlerts;
	}
}

void CDlgUserAlerts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ONLY_MY_POS, m_btnShowOnlyMyPOs);
	DDX_Control(pDX, IDC_CHECK_AUTOUPDATE, m_cbAutoUpdate);
	DDX_Control(pDX, IDC_EDIT_NUMALERTS, m_editNumAlerts);
}


BEGIN_MESSAGE_MAP(CDlgUserAlerts, CDialog)
	ON_BN_CLICKED(IDC_CHECK_ONLY_MY_POS, OnBnClickedCheckOnlyMyPos)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_AUTOUPDATE, OnBnClickedCheckAutoupdate)
END_MESSAGE_MAP()


// CDlgUserAlerts message handlers

BOOL CDlgUserAlerts::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	bool bValue = false;
	CGlobals::GetUserSetting("UserAlertsShowOnlyMyPOs", bValue);
	if (bValue)
	{
        m_btnShowOnlyMyPOs.SetCheck(BST_CHECKED);
	}

	m_pgridUserAlerts = new CGridUserAlerts(iUserID);
	m_pgridUserAlerts->AttachGrid(this, IDC_USER_DISCREPANCIES_GRID) ;
	m_pgridUserAlerts->SetShowOnlyMyPOs(bValue);
	m_pgridUserAlerts->Update();
	UpdateAlertCount();
	if (m_pgridUserAlerts->GetNumberRows() > 0)
	{
		int RowHeight = m_pgridUserAlerts->GetRowHeight(0);
		int HeaderHeight = m_pgridUserAlerts->GetRowHeight(-1);
		CRect rect;
		GetDlgItem(IDC_USER_DISCREPANCIES_GRID)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		int GridAreaHeight = rect.Height() - HeaderHeight;
		int NumRows = GridAreaHeight / RowHeight;
		int NewGridAreaHeight = NumRows * RowHeight;
		m_pgridUserAlerts->MoveWindow(rect.left,rect.top, rect.Width(), NewGridAreaHeight + HeaderHeight);
	}
	m_pgridUserAlerts->ShowWindow(SW_SHOW);

	CPermissions perm;
	if (!perm.HasPermission("CanViewAllAlerts"))
	{
		m_btnShowOnlyMyPOs.EnableWindow(FALSE);
	}

	CSetSettings setSettings(&g_dbFlooring);
	CString strTimer = setSettings.GetSetting("UserAlertsUpdateTimer");
	m_TimerLength = 30000;  // default to 30 sec.
	if (strTimer.GetLength() > 0)
	{
		m_TimerLength = atoi(strTimer);
	}
	else
	{
		setSettings.SetSetting("UserAlertsUpdateTimer", "30000");
	}

	CGlobals::GetUserSetting("UserAlertsAutoUpdate", bValue) ;
	if (bValue)
	{
        SetTimer(TIMER_ID, m_TimerLength, NULL);
		m_cbAutoUpdate.SetCheck(BST_CHECKED);
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgUserAlerts::OnBnClickedCheckOnlyMyPos()
{
	if (m_btnShowOnlyMyPOs.GetCheck() == BST_UNCHECKED)
	{
		m_pgridUserAlerts->SetShowOnlyMyPOs(false);
	}
	else
	{
		m_pgridUserAlerts->SetShowOnlyMyPOs(true);
	}
	UpdateAlertCount();
}

void CDlgUserAlerts::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	AfxGetMainWnd()->SendMessage(CGlobals::WM_USER_USER_ALERTS_DLG_DESTROYED, 0, 0);
	delete this;
}

void CDlgUserAlerts::OnCancel()
{
	bool bValue = (m_cbAutoUpdate.GetCheck() > 0);
	CGlobals::SetUserSetting("UserAlertsAutoUpdate", bValue);
	bValue = (m_btnShowOnlyMyPOs.GetCheck() > 0);
	CGlobals::SetUserSetting("UserAlertsShowOnlyMyPOs", bValue);

    KillTimer(TIMER_ID);
	DestroyWindow();
}

void CDlgUserAlerts::OnTimer(UINT nIDEvent)
{
	RefreshGrid();
	CDialog::OnTimer(nIDEvent);
}

void CDlgUserAlerts::RefreshGrid()
{
	m_pgridUserAlerts->Update();
	UpdateAlertCount();
}

void CDlgUserAlerts::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (nType == SIZE_MINIMIZED)
	{
		CFrameWnd* pFrame = GetParentFrame();
		CRect rect;
		pFrame->GetClientRect(&rect);
		pFrame->ClientToScreen(&rect);
		CRect rect2;
		this->GetWindowRect(&rect2);
		MoveWindow(rect.left, rect.bottom - (2*rect2.Height()) ,cx, cy);
	}
}

void CDlgUserAlerts::UpdateAlertCount()
{
	CString strCount;
	strCount.Format("%d", m_pgridUserAlerts->GetNumberRows());
	m_editNumAlerts.SetWindowText(strCount);
}

void CDlgUserAlerts::OnBnClickedCheckAutoupdate()
{
	if (m_cbAutoUpdate.GetCheck() > 0)
	{
		SetTimer(TIMER_ID, m_TimerLength, NULL);
		RefreshGrid();
	}
	else
	{
		KillTimer(TIMER_ID);
	}
}
