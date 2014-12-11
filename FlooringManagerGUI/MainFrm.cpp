/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Flooring.h"
#include "MainFrm.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int TIMER_ID = 1;

#define UPDATER_NAME                   _T("updater.exe")
#define UPDATER_COMMAND_LINE_CHECKNOW  _T(" /checknow")
#define UPDATER_COMMAND_LINE_OPTIONS   _T(" /configure %u")
#define UPDATER_COMMAND_LINE_SILENT    _T(" /silent")


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	ON_MESSAGE(CGlobals::WM_USER_USER_ALERTS_DLG_DESTROYED, OnUserAlertsDlgDestroyed)
	ON_MESSAGE(CGlobals::WM_USER_ACTIVE_POS_DLG_DESTROYED, OnActivePOsDlgDestroyed)
	ON_MESSAGE(CGlobals::WM_ACTIVITY_LIST_DLG_DESTROYED, OnActivityListDlgDestroyed)
	ON_MESSAGE(CGlobals::WM_CHECK_FOR_IM_UPDATES, OnCheckForIMUpdates)
	ON_REGISTERED_MESSAGE( wm_UPDATE_USER_ALERTS, OnUpdateUserAlerts)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USERNAME, OnUpdateUserName)	
	ON_REGISTERED_MESSAGE( wm_SendEmailError, OnSendEmailError)
	ON_WM_TIMER()

	ON_COMMAND(ID_HELP_CHECKFORUPDATES, &CMainFrame::OnHelpCheckforupdates)
	ON_COMMAND(ID_HELP_UPDATEOPTIONS, &CMainFrame::OnHelpUpdateOptions)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_USERNAME,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_strFrameTitle(_T("Installation Manager"))
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
/*	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	else
	{
		m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_USERNAME, SBPS_NORMAL, 150);
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	SetTimer(TIMER_ID, 15000, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_MAXIMIZE ;


	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateFrameTitle(BOOL /* bAddToTitle */)
{
	// This is overridden so we can control the main frame title better.
	// Any time the mainframe needs to set its title, it calls this function.

	SetWindowText(m_strFrameTitle);
}

LRESULT CMainFrame::OnUserAlertsDlgDestroyed(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
	pApp->m_pDlgUserAlerts = NULL;
	return 0;
}

LRESULT CMainFrame::OnActivePOsDlgDestroyed(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
	pApp->m_pDlgActivePOs = NULL;
	return 0;
}

LRESULT CMainFrame::OnActivityListDlgDestroyed(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
	pApp->m_pDlgActivityList = NULL;
	return 0;
}



LRESULT CMainFrame::OnUpdateUserAlerts(WPARAM, LPARAM)
{
	CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
	if (pApp->m_pDlgUserAlerts != NULL)
	{
		pApp->m_pDlgUserAlerts->RefreshGrid();
	}
	return 0;
}

LRESULT CMainFrame::OnSendEmailError(WPARAM wp, LPARAM lp)
{
	CString* s = (CString*)lp;
	MessageBox(*s, "Email Send Error!");
	delete s;
	return 0;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_KEYUP )
	{
		if ( (pMsg->wParam == 0x50) && (GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_RSHIFT) & 0x8000) )
		{
			CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
			pApp->ImpersonateUser();
			return TRUE;
		}
		return FALSE;
	}
	else
	{
        return CMDIFrameWnd::PreTranslateMessage(pMsg);
	}
}

void CMainFrame::OnUpdateUserName(CCmdUI* pCmdUI)
{
	CFlooringApp* pApp = (CFlooringApp*)AfxGetApp();
	CString strText = "User: " + pApp->GetCFUserName();
	pCmdUI->SetText(strText);
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	KillTimer(TIMER_ID);

	OnCheckForIMUpdates(NULL,NULL);

	CMDIFrameWnd::OnTimer(nIDEvent);
}

LRESULT CMainFrame::OnCheckForIMUpdates( WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	DoRunUpdater(UPDATER_COMMAND_LINE_SILENT);

	return 0;
}

void CMainFrame::OnHelpCheckforupdates()
{	
	DoRunUpdater(UPDATER_COMMAND_LINE_CHECKNOW);
}

void CMainFrame::OnHelpUpdateOptions()
{
	CString commandLine;
	commandLine.Format(UPDATER_COMMAND_LINE_OPTIONS, m_hWnd);    
	DoRunUpdater(commandLine);
}

void CMainFrame::DoRunUpdater(CString aCommandLine) 
{
	TCHAR path[MAX_PATH];
	::GetModuleFileName(NULL, path, MAX_PATH);

	CString updaterPath(path);
	int ind = updaterPath.ReverseFind(_T('\\'));
	if (ind > 0)
		updaterPath = updaterPath.Left(ind);
	if (updaterPath[updaterPath.GetLength() - 1] != _T('\\'))
		updaterPath += _T('\\');
	updaterPath += UPDATER_NAME;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	::CreateProcess(updaterPath, const_cast<LPSTR>((LPCTSTR)aCommandLine), 
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}

