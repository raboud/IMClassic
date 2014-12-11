/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewActivePOs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "flooring.h"
#include "ViewActivePOs.h"
#include "SetSettings.h"

const int TIMER_ID = 1;

// CViewActivePOs

IMPLEMENT_DYNCREATE(CViewActivePOs, CCFIFormView)

CViewActivePOs::CViewActivePOs()
	: CCFIFormView(CViewActivePOs::IDD)
{
	m_pgridActivePOs = NULL;
}

CViewActivePOs::~CViewActivePOs()
{
	if (m_pgridActivePOs != NULL)
	{
		delete m_pgridActivePOs;
	}
}

void CViewActivePOs::DoDataExchange(CDataExchange* pDX)
{
	CCFIFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ONLY_MY_POS, m_btnShowOnlyMyPOs);
	DDX_Control(pDX, IDC_CHECK_AUTOUPDATE, m_cbAutoUpdate);
	DDX_Control(pDX, IDC_ACTIVEPOS_DTP_START, m_dtpStartDate);
	DDX_Control(pDX, IDC_ACTIVEPOS_DTP_END, m_dtpEndDate);
	DDX_Control(pDX, IDC_EDIT_NUMPOS, m_editNumPOs);
	DDX_Control(pDX, IDC_ACTIVEPOS_SHOWONLYACTIVEPOS, m_btnShowAllActivePOs);
	DDX_Control(pDX, IDC_ACTIVEPOS_SHOWPOSWITHALERTS, m_btnShowOnlyPOsWithAlerts);
	DDX_Control(pDX, IDC_ACTIVEPOS_INCLUDECANCELLEDPOS, m_btnIncludeCancelledPOs);
}

BEGIN_MESSAGE_MAP(CViewActivePOs, CCFIFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_ONLY_MY_POS, &CViewActivePOs::OnBnClickedCheckOnlyMyPos)
	ON_BN_CLICKED(IDC_CHECK_AUTOUPDATE, &CViewActivePOs::OnBnClickedCheckAutoupdate)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVEPOS_DTP_END, &CViewActivePOs::OnDtnCloseupActiveposDtpEnd)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVEPOS_DTP_END, &CViewActivePOs::OnNMKillfocusActiveposDtpEnd)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVEPOS_DTP_START, &CViewActivePOs::OnDtnCloseupActiveposDtpStart)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVEPOS_DTP_START, &CViewActivePOs::OnNMKillfocusActiveposDtpStart)
	ON_BN_CLICKED(IDC_ACTIVEPOS_SHOWALLACTIVEPOS, &CViewActivePOs::OnBnClickedActivePOsShowAllActivePOs)
	ON_BN_CLICKED(IDC_ACTIVEPOS_SHOWPOSWITHALERTS, &CViewActivePOs::OnBnClickedActivePOsShowPOsWithAlerts)
	ON_BN_CLICKED(IDC_ACTIVEPOS_INCLUDECANCELLEDPOS, &CViewActivePOs::OnBnClickedActivePOsIncludeCancelledPOs)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CViewActivePOs::OnBnClickedCancel)
END_MESSAGE_MAP()


// CViewActivePOs diagnostics

#ifdef _DEBUG
void CViewActivePOs::AssertValid() const
{
	CCFIFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CViewActivePOs::Dump(CDumpContext& dc) const
{
	CCFIFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CViewActivePOs message handlers

void CViewActivePOs::OnInitialUpdate()
{
	CCFIFormView::OnInitialUpdate();

	COleDateTime dtMin = COleDateTime(1900, 1, 1, 0,0,0);
	COleDateTime dtMax = COleDateTime(3000, 12, 31, 0,0,0);
	m_dtpStartDate.SetRange(&dtMin, &dtMax);
	m_dtpEndDate.SetRange(&dtMin, &dtMax);

	int iUserID = CGlobals::GetEmployeeID();

	m_pgridActivePOs = new CGridActivePOs(iUserID);
	m_pgridActivePOs->AttachGrid(this, IDC_ACTIVE_POS_GRID) ;

	CSetSettings setSettings;
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

	GetParentFrame()->SetTitle("Active POs");
	
	UpdatePOCount();
}

void CViewActivePOs::OnSize(UINT nType, int cx, int cy)
{
	CCFIFormView::OnSize(nType, cx, cy);

	const int iL_BORDER = 10;
	const int iR_BORDER = 10;
	const int iT_BORDER = 10;
	const int iB_BORDER_RPT = 10;
	
	if ((m_pgridActivePOs != NULL) && ::IsWindow(m_pgridActivePOs->m_hWnd))
	{
		CRect rect;
		GetDlgItem(IDC_ACTIVE_POS_GRID)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_pgridActivePOs->MoveWindow(rect.left,rect.top, cx-(iL_BORDER+iR_BORDER),cy-rect.top-(iT_BORDER+iB_BORDER_RPT));
	}

}

void CViewActivePOs::OnTimer(UINT_PTR nIDEvent)
{
	RefreshGrid();
	CCFIFormView::OnTimer(nIDEvent);
}

void CViewActivePOs::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CCFIFormView::PostNcDestroy();
}

void CViewActivePOs::OnBnClickedCheckOnlyMyPos()
{
	UpdateGrid();
}

void CViewActivePOs::OnBnClickedCheckAutoupdate()
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

void CViewActivePOs::OnDtnCloseupActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivePOs::OnNMKillfocusActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivePOs::OnDtnCloseupActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivePOs::OnNMKillfocusActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivePOs::OnBnClickedActivePOsShowAllActivePOs()
{
	m_btnIncludeCancelledPOs.EnableWindow();
	UpdateGrid();
}

void CViewActivePOs::OnBnClickedActivePOsShowPOsWithAlerts()
{
	m_btnIncludeCancelledPOs.SetCheck(BST_UNCHECKED);
	m_btnIncludeCancelledPOs.EnableWindow(FALSE);
	UpdateGrid();
}

void CViewActivePOs::OnBnClickedActivePOsIncludeCancelledPOs()
{
	UpdateGrid();
}

void CViewActivePOs::RefreshGrid()
{
	m_pgridActivePOs->Update();
	UpdatePOCount();
}

void CViewActivePOs::UpdatePOCount()
{
	CString strCount;
	strCount.Format("%d", m_pgridActivePOs->GetNumberRows());
	m_editNumPOs.SetWindowText(strCount);
}

void CViewActivePOs::InitControls()
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

	if (!CGlobals::HasPermission("CanViewAllPOs"))
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

void CViewActivePOs::UpdateDateFilter()
{
	COleDateTime dtStart;
	COleDateTime dtEnd;
	m_dtpStartDate.GetTime(dtStart);
	m_dtpEndDate.GetTime(dtEnd);
	m_pgridActivePOs->SetOrderDateFilter(dtStart, dtEnd);
	UpdatePOCount();
}

void CViewActivePOs::UpdateGrid()
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

void CViewActivePOs::OnDestroy()
{
	CCFIFormView::OnDestroy();

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
	
	AfxGetMainWnd()->SendMessage(CGlobals::WM_USER_ACTIVE_POS_DLG_DESTROYED, 0, 0);

}

void CViewActivePOs::OnBnClickedCancel()
{
	CFrameWnd* pFrame = GetParentFrame();
	pFrame->PostMessage(WM_CLOSE);
}