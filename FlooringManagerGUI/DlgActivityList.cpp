/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgActivityList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgActivityList.h"
#include "SetSettings.h"
#include "Globals.h"
#include ".\dlgactivitylist.h"

const int TIMER_ID = 1;

// CDlgActivityList dialog

IMPLEMENT_DYNAMIC(CDlgActivityList, CDialog)
CDlgActivityList::CDlgActivityList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgActivityList::IDD, pParent)
{
	m_pgridActivityList = NULL;
}

CDlgActivityList::~CDlgActivityList()
{
	if (m_pgridActivityList != NULL)
	{
		delete m_pgridActivityList;
	}
}

void CDlgActivityList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTIVITIES_SHOWALLACTIVITIES, m_btnShowAllActivities);
	DDX_Control(pDX, IDC_ACTIVITIES_SHOW_ONLY_OPEN_ACTIVITIES, m_btnShowOnlyOpenActivities);
	DDX_Control(pDX, IDC_CHECK_ONLY_MY_ACTIVITIES, m_btnShowOnlyMyActivities);
	DDX_Control(pDX, IDC_CHECK_AUTOUPDATE, m_cbAutoUpdate);
	DDX_Control(pDX, IDC_ACTIVITIES_DTP_START, m_dtpStartDate);
	DDX_Control(pDX, IDC_ACTIVITIES_DTP_END, m_dtpEndDate);
	DDX_Control(pDX, IDC_EDIT_ACTIVITY_ADD_INFO, m_editAdditionalInfo);
	DDX_Control(pDX, IDC_EDIT_ACTIVITY_CLOSED_BY, m_editClosedBy);
}


BEGIN_MESSAGE_MAP(CDlgActivityList, CDialog)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVITIES_DTP_START, OnDtnCloseupActivitiesDtpStart)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVITIES_DTP_START, OnNMKillfocusActivitiesDtpStart)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVITIES_DTP_END, OnDtnCloseupActivitiesDtpEnd)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVITIES_DTP_END, OnNMKillfocusActivitiesDtpEnd)
	ON_BN_CLICKED(IDC_ACTIVITIES_SHOWALLACTIVITIES, OnBnClickedShowAllActivities)
	ON_BN_CLICKED(IDC_ACTIVITIES_SHOW_ONLY_OPEN_ACTIVITIES, OnBnClickedShowOnlyOpenActivities)
	ON_BN_CLICKED(IDC_CHECK_ONLY_MY_ACTIVITIES, OnBnClickedShowOnlyMyActivities)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_MESSAGE( CGlobals::WM_ACTIVITY_DATA_UPDATE, OnUpdateAdditionalInfo)
	ON_BN_CLICKED(IDC_CHECK_AUTOUPDATE, OnBnClickedCheckAutoupdate)
END_MESSAGE_MAP()


// CDlgActivityList message handlers

void CDlgActivityList::OnDtnCloseupActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivityList::OnNMKillfocusActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivityList::OnDtnCloseupActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivityList::OnNMKillfocusActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CDlgActivityList::OnBnClickedShowAllActivities()
{
	UpdateGrid();
}

void CDlgActivityList::OnBnClickedShowOnlyOpenActivities()
{
	UpdateGrid();
}

void CDlgActivityList::OnBnClickedShowOnlyMyActivities()
{
	UpdateGrid();
}

void CDlgActivityList::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	AfxGetMainWnd()->SendMessage(CGlobals::WM_ACTIVITY_LIST_DLG_DESTROYED, 0, 0);
	delete this;
}

BOOL CDlgActivityList::OnInitDialog()
{
	CDialog::OnInitDialog();

	COleDateTime dtMin = COleDateTime(1900, 1, 1, 0,0,0);
	COleDateTime dtMax = COleDateTime(3000, 12, 31, 0,0,0);
	m_dtpStartDate.SetRange(&dtMin, &dtMax);
	m_dtpEndDate.SetRange(&dtMin, &dtMax);
	
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	int iUserID = pApp->GetEmployeeID();

	m_pgridActivityList = new CGridActivityList(iUserID);
	m_pgridActivityList->AttachGrid(this, IDC_ACTIVITY_LIST_GRID) ;

	CSetSettings setSettings(&g_dbFlooring);
	CString strTimer = setSettings.GetSetting("ActivityListUpdateTimer");
	m_TimerLength = 60000;  // default to 60 sec.
	if (strTimer.GetLength() > 0)
	{
		m_TimerLength = atoi(strTimer);
	}
	else
	{
		setSettings.SetSetting("ActivityListUpdateTimer", "60000");
	}
	
	InitControls();

	RefreshGrid();

	if (m_pgridActivityList->GetNumberRows() > 0)
	{
		int RowHeight = m_pgridActivityList->GetRowHeight(0);
		int HeaderHeight = m_pgridActivityList->GetRowHeight(-1);
		CRect rect;
		GetDlgItem(IDC_ACTIVITY_LIST_GRID)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		int GridAreaHeight = rect.Height() - HeaderHeight;
		int NumRows = GridAreaHeight / RowHeight;
		int NewGridAreaHeight = NumRows * RowHeight;
		m_pgridActivityList->MoveWindow(rect.left,rect.top, rect.Width(), NewGridAreaHeight + HeaderHeight);
	}
	m_pgridActivityList->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgActivityList::OnTimer(UINT nIDEvent)
{
	RefreshGrid();
	CDialog::OnTimer(nIDEvent);
}

void CDlgActivityList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void CDlgActivityList::RefreshGrid()
{
	m_pgridActivityList->Update();
}

void CDlgActivityList::InitControls()
{
	bool bValue = false;
	CGlobals::GetUserSetting("ActivityListShowOnlyMyActivities", bValue, true);
	if (bValue)
	{
        m_btnShowOnlyMyActivities.SetCheck(BST_CHECKED);
	}

	CGlobals::GetUserSetting("ActivityListShowOnlyOpenActivities", bValue, true);
	if (bValue)
	{
		m_btnShowOnlyOpenActivities.SetCheck(BST_CHECKED);
		OnBnClickedShowOnlyOpenActivities();
	}
	else
	{
		m_btnShowAllActivities.SetCheck(BST_CHECKED);
		OnBnClickedShowAllActivities();
	}

	CGlobals::GetUserSetting("ActivityListAutoUpdate", bValue) ;
	if (bValue)
	{
        SetTimer(TIMER_ID, m_TimerLength, NULL);
		m_cbAutoUpdate.SetCheck(BST_CHECKED);
	}

	CPermissions perm;
	if (!perm.HasPermission("CanViewAllActivities"))
	{
		m_btnShowOnlyMyActivities.EnableWindow(FALSE);
	}

	COleDateTime dt = COleDateTime::GetCurrentTime();
	m_dtpEndDate.SetTime(dt);
	dt.SetDate(dt.GetYear()-1, 1, 1);
	m_dtpStartDate.SetTime(dt);

	CString strTemp = "";
	CGlobals::GetUserSetting("ActivityListCreateStartDate", strTemp, "");

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

	CGlobals::GetUserSetting("ActivityListCreateEndDate", strTemp, "");
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

void CDlgActivityList::UpdateGrid()
{
	m_pgridActivityList->SetShowAllActivities((m_btnShowAllActivities.GetCheck() == BST_CHECKED), false);
	m_pgridActivityList->SetShowOnlyMyActivities((m_btnShowOnlyMyActivities.GetCheck() == BST_CHECKED), false);

	UpdateDateFilter(false);

	m_pgridActivityList->Update();

}
void CDlgActivityList::OnCancel()
{
	bool bValue = (m_cbAutoUpdate.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivityListAutoUpdate", bValue);
	
	bValue = (m_btnShowOnlyMyActivities.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivityListShowOnlyMyActivities", bValue);

	bValue = (m_btnShowOnlyOpenActivities.GetCheck() > 0);
	CGlobals::SetUserSetting("ActivityListShowOnlyOpenActivities", bValue);

	COleDateTime dt;
	m_dtpStartDate.GetTime(dt);
	CGlobals::SetUserSetting("ActivityListCreateStartDate", dt.Format("%m/%d/%Y"));
	
	m_dtpEndDate.GetTime(dt);
	CGlobals::SetUserSetting("ActivityListCreateEndDate", dt.Format("%m/%d/%Y"));

    KillTimer(TIMER_ID);
	DestroyWindow();

}

void CDlgActivityList::UpdateDateFilter(bool bUpdateGrid)
{
	COleDateTime dtStart;
	COleDateTime dtEnd;
	m_dtpStartDate.GetTime(dtStart);
	m_dtpEndDate.GetTime(dtEnd);
	dtEnd += COleDateTimeSpan(1, 0, 0, 0);
	m_pgridActivityList->SetCreateDateFilter(dtStart, dtEnd, bUpdateGrid);
}

LRESULT CDlgActivityList::OnUpdateAdditionalInfo(WPARAM, LPARAM)
{
	m_editAdditionalInfo.SetWindowText(m_pgridActivityList->GetActivityData());
	m_editClosedBy.SetWindowText(m_pgridActivityList->GetClosedByInfo());
	return TRUE ;
}
void CDlgActivityList::OnBnClickedCheckAutoupdate()
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

void CDlgActivityList::OnOK()
{
	CWnd* pWnd = GetFocus();
	
	if ((pWnd->m_hWnd == m_dtpStartDate.m_hWnd) || (pWnd->m_hWnd == m_dtpEndDate.m_hWnd))
	{
		UpdateDateFilter();
	}
}
