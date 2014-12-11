/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewActivityList.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Flooring.h"
#include "ViewActivityList.h"
#include "SetSettings.h"
#include "Globals.h"

const int TIMER_ID = 1;

// CViewActivityList

IMPLEMENT_DYNCREATE(CViewActivityList, CFormView)

CViewActivityList::CViewActivityList()
	: CFormView(CViewActivityList::IDD)
{
	m_pgridActivityList = NULL;
}

CViewActivityList::~CViewActivityList()
{
	if (m_pgridActivityList != NULL)
	{
		delete m_pgridActivityList;
	}
}

void CViewActivityList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTIVITIES_SHOWALLACTIVITIES, m_btnShowAllActivities);
	DDX_Control(pDX, IDC_ACTIVITIES_SHOW_ONLY_OPEN_ACTIVITIES, m_btnShowOnlyOpenActivities);
	DDX_Control(pDX, IDC_CHECK_ONLY_MY_ACTIVITIES, m_btnShowOnlyMyActivities);
	DDX_Control(pDX, IDC_CHECK_AUTOUPDATE, m_cbAutoUpdate);
	DDX_Control(pDX, IDC_ACTIVITIES_DTP_START, m_dtpStartDate);
	DDX_Control(pDX, IDC_ACTIVITIES_DTP_END, m_dtpEndDate);
	DDX_Control(pDX, IDC_EDIT_ACTIVITY_ADD_INFO, m_editAdditionalInfo);
	DDX_Control(pDX, IDC_EDIT_ACTIVITY_CLOSED_BY, m_editClosedBy);
}

BEGIN_MESSAGE_MAP(CViewActivityList, CFormView)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVITIES_DTP_START, &CViewActivityList::OnDtnCloseupActivitiesDtpStart)
	ON_NOTIFY(DTN_CLOSEUP, IDC_ACTIVITIES_DTP_END, &CViewActivityList::OnDtnCloseupActivitiesDtpEnd)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVITIES_DTP_START, &CViewActivityList::OnNMKillfocusActivitiesDtpStart)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACTIVITIES_DTP_END, &CViewActivityList::OnNMKillfocusActivitiesDtpEnd)
	ON_BN_CLICKED(IDC_ACTIVITIES_SHOW_ONLY_OPEN_ACTIVITIES, &CViewActivityList::OnBnClickedShowOnlyOpenActivities)
	ON_BN_CLICKED(IDC_ACTIVITIES_SHOWALLACTIVITIES, &CViewActivityList::OnBnClickedShowAllActivities)
	ON_BN_CLICKED(IDC_CHECK_ONLY_MY_ACTIVITIES, &CViewActivityList::OnBnClickedShowOnlyMyActivities)
	ON_BN_CLICKED(IDCANCEL, &CViewActivityList::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_AUTOUPDATE, &CViewActivityList::OnBnClickedCheckAutoupdate)
	ON_MESSAGE( CGlobals::WM_ACTIVITY_DATA_UPDATE, OnUpdateAdditionalInfo)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CViewActivityList diagnostics

#ifdef _DEBUG
void CViewActivityList::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CViewActivityList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CViewActivityList message handlers

void CViewActivityList::OnDtnCloseupActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivityList::OnDtnCloseupActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivityList::OnNMKillfocusActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivityList::OnNMKillfocusActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateDateFilter();
	*pResult = 0;
}

void CViewActivityList::OnBnClickedShowOnlyOpenActivities()
{
	UpdateGrid();
}

void CViewActivityList::OnBnClickedShowAllActivities()
{
	UpdateGrid();
}

void CViewActivityList::OnBnClickedShowOnlyMyActivities()
{
	UpdateGrid();
}

void CViewActivityList::OnBnClickedCancel()
{
	CFrameWnd* pFrame = GetParentFrame();
	pFrame->PostMessage(WM_CLOSE);
}

void CViewActivityList::OnBnClickedCheckAutoupdate()
{
	// TODO: Add your control notification handler code here
}

void CViewActivityList::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	COleDateTime dtMin = COleDateTime(1900, 1, 1, 0,0,0);
	COleDateTime dtMax = COleDateTime(3000, 12, 31, 0,0,0);
	m_dtpStartDate.SetRange(&dtMin, &dtMax);
	m_dtpEndDate.SetRange(&dtMin, &dtMax);

	int iUserID = CGlobals::GetEmployeeID();

	m_pgridActivityList = new CGridActivityList(iUserID);
	m_pgridActivityList->AttachGrid(this, IDC_ACTIVITY_LIST_GRID) ;

	CSetSettings setSettings;
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

	GetParentFrame()->SetTitle("Activity List");
}

void CViewActivityList::RefreshGrid()
{
	m_pgridActivityList->Update();
}

void CViewActivityList::OnTimer(UINT_PTR nIDEvent)
{
	RefreshGrid();

	CFormView::OnTimer(nIDEvent);
}

void CViewActivityList::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	const int iL_BORDER = 10;
	const int iR_BORDER = 10;
	const int iT_BORDER = 10;
	const int iB_BORDER_RPT = 10;
	
	if ((m_pgridActivityList != NULL) && ::IsWindow(m_pgridActivityList->m_hWnd))
	{
		CRect rect;
		GetDlgItem(IDC_ACTIVITY_LIST_GRID)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_pgridActivityList->MoveWindow(rect.left,rect.top, cx-(iL_BORDER+iR_BORDER),cy-rect.top-(iT_BORDER+iB_BORDER_RPT));
	}
}

void CViewActivityList::InitControls()
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

	if (!CGlobals::HasPermission("CanViewAllActivities"))
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

void CViewActivityList::UpdateGrid()
{
	m_pgridActivityList->SetShowAllActivities((m_btnShowAllActivities.GetCheck() == BST_CHECKED), false);
	m_pgridActivityList->SetShowOnlyMyActivities((m_btnShowOnlyMyActivities.GetCheck() == BST_CHECKED), false);

	UpdateDateFilter(false);

	m_pgridActivityList->Update();

}

void CViewActivityList::UpdateDateFilter(bool bUpdateGrid)
{
	COleDateTime dtStart;
	COleDateTime dtEnd;
	m_dtpStartDate.GetTime(dtStart);
	m_dtpEndDate.GetTime(dtEnd);
	dtEnd += COleDateTimeSpan(1, 0, 0, 0);
	m_pgridActivityList->SetCreateDateFilter(dtStart, dtEnd, bUpdateGrid);
}

LRESULT CViewActivityList::OnUpdateAdditionalInfo(WPARAM, LPARAM)
{
	m_editAdditionalInfo.SetWindowText(m_pgridActivityList->GetActivityData());
	m_editClosedBy.SetWindowText(m_pgridActivityList->GetClosedByInfo());
	return TRUE ;
}
void CViewActivityList::OnDestroy()
{
	CFormView::OnDestroy();

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

	AfxGetMainWnd()->SendMessage(CGlobals::WM_ACTIVITY_LIST_DLG_DESTROYED, 0, 0);
}
