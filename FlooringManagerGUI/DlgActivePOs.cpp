/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgActivePOs.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgActivePOs.h"
#include "SetSettings.h"
#include ".\dlgactivepos.h"

const int TIMER_ID = 1;

// CDlgActivePOs dialog

IMPLEMENT_DYNAMIC(CDlgActivePOs, CDialog)
CDlgActivePOs::CDlgActivePOs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgActivePOs::IDD, pParent)
{
	m_pgridActivePOs = NULL;
}

CDlgActivePOs::~CDlgActivePOs()
{
	if (m_pgridActivePOs != NULL)
	{
		delete m_pgridActivePOs;
	}
}

void CDlgActivePOs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ONLY_MY_POS, m_btnShowOnlyMyPOs);
	DDX_Control(pDX, IDC_CHECK_AUTOUPDATE, m_cbAutoUpdate);
	DDX_Control(pDX, IDC_ACTIVEPOS_DTP_START, m_dtpStartDate);
	DDX_Control(pDX, IDC_ACTIVEPOS_DTP_END, m_dtpEndDate);
	DDX_Control(pDX, IDC_EDIT_NUMPOS, m_editNumPOs);
	DDX_Control(pDX, IDC_ACTIVEPOS_SHOWONLYACTIVEPOS, m_btnShowAllActivePOs);
	DDX_Control(pDX, IDC_ACTIVEPOS_SHOWPOSWITHALERTS, m_btnShowOnlyPOsWithAlerts);
	DDX_Control(pDX, IDC_ACTIVEPOS_INCLUDECANCELLEDPOS, m_btnIncludeCancelledPOs);
}


BEGIN_MESSAGE_MAP(CDlgActivePOs, CDialog)
	ON_BN_CLICKED(IDC_CHECK_ONLY_MY_POS, OnBnClickedCheckOnlyMyPos)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_AUTOUPDATE, OnBnClickedCheckAutoupdate)
	ON_BN_CLICKED(IDC_ACTIVEPOS_SHOWONLYACTIVEPOS, OnBnClickedActivePOsShowAllActivePOs)
	ON_BN_CLICKED(IDC_ACTIVEPOS_SHOWPOSWITHALERTS, OnBnClickedActivePOsShowPOsWithAlerts)
	ON_BN_CLICKED(IDC_ACTIVEPOS_INCLUDECANCELLEDPOS, OnBnClickedActivePOsIncludeCancelledPOs)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVEPOS_DTP_START, OnDtnCloseupActiveposDtpStart)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVEPOS_DTP_END, OnDtnCloseupActiveposDtpEnd)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVEPOS_DTP_START, OnNMKillfocusActiveposDtpStart)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVEPOS_DTP_END, OnNMKillfocusActiveposDtpEnd)
END_MESSAGE_MAP()


// CDlgActivePOs message handlers
BOOL CDlgActivePOs::OnInitDialog()
{
	CDialog::OnInitDialog();

	COleDateTime dtMin = COleDateTime(1900, 1, 1, 0,0,0);
	COleDateTime dtMax = COleDateTime(3000, 12, 31, 0,0,0);
	m_dtpStartDate.SetRange(&dtMin, &dtMax);
	m_dtpEndDate.SetRange(&dtMin, &dtMax);

	
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	m_pgridActivePOs = new CGridActivePOs(iUserID);
	m_pgridActivePOs->AttachGrid(this, IDC_ACTIVE_POS_GRID) ;

	CSetSettings setSettings(&g_dbFlooring);
	CString strTimer = setSettings.GetSetting("ActivePOsUpdateTimer");
	m_TimerLength = 30000;  // default to 30 sec.
	if (strTimer.GetLength() > 0)
	{
		m_TimerLength = atoi(strTimer);
	}
	else
	{
		setSettings.SetSetting("ActivePOsUpdateTimer", "30000");
	}
	
	InitControls();

	RefreshGrid();

	if (m_pgridActivePOs->GetNumberRows() > 0)
	{
		int RowHeight = m_pgridActivePOs->GetRowHeight(0);
		int HeaderHeight = m_pgridActivePOs->GetRowHeight(-1);
		CRect rect;
		GetDlgItem(IDC_ACTIVE_POS_GRID)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		int GridAreaHeight = rect.Height() - HeaderHeight;
		int NumRows = GridAreaHeight / RowHeight;
		int NewGridAreaHeight = NumRows * RowHeight;
		m_pgridActivePOs->MoveWindow(rect.left,rect.top, rect.Width(), NewGridAreaHeight + HeaderHeight);
	}
	m_pgridActivePOs->ShowWindow(SW_SHOW);
	
	UpdatePOCount();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgActivePOs::OnBnClickedCheckOnlyMyPos()
{
	UpdateGrid();
}

void CDlgActivePOs::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	AfxGetMainWnd()->SendMessage(CGlobals::WM_USER_ACTIVE_POS_DLG_DESTROYED, 0, 0);
	delete this;
}

void CDlgActivePOs::OnCancel()
{
	bool bValue = (m_cbAutoUpdate.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivePOsAutoUpdate", bValue);
	
	bValue = (m_btnShowOnlyMyPOs.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivePOsShowOnlyMyPOs", bValue);

	bValue = (this->m_btnIncludeCancelledPOs.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivePOsIncludeCancelled", bValue);

	bValue = (this->m_btnShowOnlyPOsWithAlerts.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivePOsShowOnlyPOsWithAlerts", bValue);

	COleDateTime dt;
	m_dtpStartDate.GetTime(dt);
	CGlobals::SetUserSetting("ActivePOsOrderStartDate", dt.Format("%m/%d/%Y"));
	
	m_dtpEndDate.GetTime(dt);
	CGlobals::SetUserSetting("ActivePOsOrderEndDate", dt.Format("%m/%d/%Y"));

    KillTimer(TIMER_ID);
	DestroyWindow();
}

void CDlgActivePOs::OnTimer(UINT nIDEvent)
{
	RefreshGrid();
	CDialog::OnTimer(nIDEvent);
}

void CDlgActivePOs::RefreshGrid()
{
	m_pgridActivePOs->Update();
	UpdatePOCount();
}

void CDlgActivePOs::OnSize(UINT nType, int cx, int cy)
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

void CDlgActivePOs::UpdatePOCount()
{
	CString strCount;
	strCount.Format("%d", m_pgridActivePOs->GetNumberRows());
	m_editNumPOs.SetWindowText(strCount);
}

void CDlgActivePOs::OnBnClickedCheckAutoupdate()
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
void CDlgActivePOs::OnBnClickedActivePOsShowAllActivePOs()
{
	m_btnIncludeCancelledPOs.EnableWindow();
	UpdateGrid();
}

void CDlgActivePOs::OnBnClickedActivePOsShowPOsWithAlerts()
{
	m_btnIncludeCancelledPOs.SetCheck(BST_UNCHECKED);
	m_btnIncludeCancelledPOs.EnableWindow(FALSE);
	UpdateGrid();
}

void CDlgActivePOs::OnBnClickedActivePOsIncludeCancelledPOs()
{
	UpdateGrid();
}

void CDlgActivePOs::InitControls()
{
	bool bValue = false;
	CGlobals::GetUserSetting("ActivePOsShowOnlyMyPOs", bValue, true);
	if (bValue)
	{
        m_btnShowOnlyMyPOs.SetCheck(BST_CHECKED);
	}

	CGlobals::GetUserSetting("ActivePOsShowOnlyPOsWithAlerts", bValue, true);
	if (bValue)
	{
		m_btnShowOnlyPOsWithAlerts.SetCheck(BST_CHECKED);
		OnBnClickedActivePOsShowPOsWithAlerts();
	}
	else
	{
		m_btnShowAllActivePOs.SetCheck(BST_CHECKED);
		OnBnClickedActivePOsShowAllActivePOs();
	}

	CGlobals::GetUserSetting("ActivePOsAutoUpdate", bValue) ;
	if (bValue)
	{
        SetTimer(TIMER_ID, m_TimerLength, NULL);
		m_cbAutoUpdate.SetCheck(BST_CHECKED);
	}

	CPermissions perm;
	if (!perm.HasPermission("CanViewAllPOs"))
	{
		m_btnShowOnlyMyPOs.EnableWindow(FALSE);
	}

	CGlobals::GetUserSetting("ActivePOsIncludeCancelled", bValue);
	if (bValue) m_btnIncludeCancelledPOs.SetCheck(BST_CHECKED);

	COleDateTime dt = COleDateTime::GetCurrentTime();
	m_dtpEndDate.SetTime(dt);
	dt.SetDate(dt.GetYear()-1, 1, 1);
	m_dtpStartDate.SetTime(dt);

	CString strTemp = "";
	CGlobals::GetUserSetting("ActivePOsOrderStartDate", strTemp, "");

	COleDateTime dtStartDefault = COleDateTime::GetCurrentTime();
	COleDateTime dtEndDefault = dtStartDefault;
	dtStartDefault.SetDate(dtStartDefault.GetYear()-1, 1, 1);
	
	if (strTemp.GetLength() > 0)
	{
		dt.ParseDateTime(strTemp);
		if (dt.GetStatus() == COleDateTime::invalid)
		{
			dt = dtStartDefault;
		}
		m_dtpStartDate.SetTime(dt);
	}

	CGlobals::GetUserSetting("ActivePOsOrderEndDate", strTemp, "");
	if (strTemp.GetLength() > 0)
	{
		dt.ParseDateTime(strTemp);
		if (dt.GetStatus() == COleDateTime::invalid)
		{
			dt = dtEndDefault;
		}
		m_dtpEndDate.SetTime(dt);
	}

	UpdateGrid();
}
void CDlgActivePOs::OnDtnCloseupActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivePOs::OnDtnCloseupActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivePOs::UpdateDateFilter()
{
	COleDateTime dtStart;
	COleDateTime dtEnd;
	m_dtpStartDate.GetTime(dtStart);
	m_dtpEndDate.GetTime(dtEnd);
	m_pgridActivePOs->SetOrderDateFilter(dtStart, dtEnd);
	UpdatePOCount();
}

void CDlgActivePOs::OnNMKillfocusActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivePOs::OnNMKillfocusActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivePOs::UpdateGrid()
{
	m_pgridActivePOs->SetIncludeCancelledPOs((m_btnIncludeCancelledPOs.GetCheck() == BST_CHECKED), false);
	m_pgridActivePOs->SetShowOnlyMyPOs((m_btnShowOnlyMyPOs.GetCheck() == BST_CHECKED), false);
	m_pgridActivePOs->SetShowOnlyPOsWithAlerts((m_btnShowOnlyPOsWithAlerts.GetCheck() == BST_CHECKED), false);

	COleDateTime dtStart;
	COleDateTime dtEnd;
	m_dtpStartDate.GetTime(dtStart);
	m_dtpEndDate.GetTime(dtEnd);
	m_pgridActivePOs->SetOrderDateFilter(dtStart, dtEnd, false);

	m_pgridActivePOs->Update();

	UpdatePOCount();

}
void CDlgActivePOs::OnOK()
{
	/*CWnd* pWnd = GetFocus();
	
	if ((pWnd->m_hWnd == m_dtpStartDate.m_hWnd) || (pWnd->m_hWnd == m_dtpEndDate.m_hWnd))
	{
		UpdateDateFilter();
	}*/
}
