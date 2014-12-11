/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// Flooring.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Flooring.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "FlooringDoc.h"
#include "CustomerView.h"
#include "DlgStoresPickList.h"
#include "DlgSubContractorsList.h"
#include "DialogInvoicing.h"
#include "DlgCheckList.h"
#include "DlgChargebackList.h"
#include "SetChecks.h"
#include "SetCheckDetails.h"
#include "oxshape.h"
#include "DlgStoreSelection.h"

#include "UpdateOptionCost.h"
#include "UpdateMaterialCost.h"
#include "SetMaterialType.h"
#include "SetMaterial.h"
#include "SetOptions.h"
#include "SetDivision.h"

#include "DlgMaterialStatus.h"
#include "JRSVersions.h"
#include "QuickBooks.h"
#include <sscemfc.hpp>

#include "SetSettings.h"

#include "DlgMessages.h"
#include "DlgSelectVendor.h"
#include "DlgPayrollMessages.h"

#include "SetEmployees.h"
#include "DlgDiscrepancies.h"
#include "SetVwOrdersWithDiscrepancies.h"
#include "PropSheetReportIssueWizard.h"
#include "DlgPassword.h"
#include "DlgUserSelect.h"
#include "UnitTests.h"
#include "DlgUnitTestResults.h"

#include "ExceptionHandler.h"

#include "Logger.h"

int CGlobals::m_iUserID;
CString CGlobals::m_strUserName;
bool CGlobals::m_bAdmin;		

CMultiDocTemplate* g_pTemplateCustomerPO ;

CDatabase g_dbFlooring;
CString g_strSPNWebServiceURL;
//CString g_strSOSIWebServiceURL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlooringApp

BEGIN_MESSAGE_MAP(CFlooringApp, CWinApp)
	//{{AFX_MSG_MAP(CFlooringApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_STORES, OnViewStores)
	ON_COMMAND(ID_STORE_INFO, OnStoreInfo)
	ON_COMMAND(ID_VIEW_SUBCONTRACTORS, OnViewSubcontractors)
	ON_COMMAND(ID_VIEW_CUSTOMER_PO, OnViewCustomerPo)
	ON_COMMAND(ID_INVOICING, OnInvoicing)
	ON_COMMAND(ID_BILLING_RECEIVECHECK, OnBillingReceivecheck)
	ON_COMMAND(ID_BILLING_CHARGEBACKS, OnBillingChargebacks)
	ON_COMMAND(ID_OVERDUE_INVOICES, OnOverdueInvoices)
	ON_COMMAND(ID_OPEN_INVOICE, OnOpenInvoices)
	ON_COMMAND(ID_PAYROLL, OnPayroll)
	ON_COMMAND(ID_REPORTS_PENDING, OnReportsPending)
	ON_COMMAND(ID_NOT_BILLED, OnNotBilled)
	ON_COMMAND(ID_INVENTORY, OnInventory)
	ON_COMMAND(ID_CRIMINAL_CHECK_NAME, OnCriminalCheckName)
	ON_COMMAND(ID_REPORTS_BILLING, OnReportsBilling)
	ON_COMMAND(ID_MATERIALS_CHANGESTATUS, OnMaterialsChangestatus)
	ON_COMMAND(ID_REPORTS_STATUS, OnReportsStatus)
	ON_COMMAND(ID_WARRANTY_SCHED, OnWarrantySched)
	ON_COMMAND(ID_WARRANTY_OPEN, OnWarrantyOpen)
	ON_COMMAND(ID_MATERIAL_RA, OnMaterialRa)
	ON_COMMAND(ID_MATERIALS_NOTRECEIVEDYET, OnMaterialsNotreceivedyet)
	ON_COMMAND(ID_REPORTS_STATUS_SINGLE, OnReportsStatusSingle)
	ON_UPDATE_COMMAND_UI(ID_BILLING_RECEIVECHECK, OnUpdateBillingReceivecheck)
	ON_UPDATE_COMMAND_UI(ID_INVOICING, OnUpdateInvoicing)
	ON_UPDATE_COMMAND_UI(ID_PAYROLL, OnUpdatePayroll)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_BILLING, OnUpdateReportsBilling)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_REPORTS_PULLLIST, OnReportsPulllist)
	ON_COMMAND(ID_REPORTS_WEEKLYTOTALS, OnReportsWeeklyTotals)	
	ON_COMMAND(ID_REPORTS_COMPLETEDJOBSNOTPAID, OnReportsCompletedJobsNotPaid)
	ON_COMMAND(ID_REPORTS_CHARGEBACKSBYDATE, OnReportsChargebacksByDate)
	ON_COMMAND(ID_REPORTS_WORKSUMMARYBYWEEK, OnReportsWorkSummaryByWeek)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_WORKSUMMARYBYWEEK, OnUpdateReportsWorkSummaryByWeek)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_PENDING, OnUpdateReportsPending)
	ON_UPDATE_COMMAND_UI(ID_NOT_BILLED, OnUpdateReportNotBilled)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_WEEKLYTOTALS, OnUpdateReportsWeeklytotals)
	ON_UPDATE_COMMAND_UI(ID_OPEN_INVOICE, OnUpdateReportOpenInvoice)
	ON_UPDATE_COMMAND_UI(ID_OVERDUE_INVOICES, OnUpdateOverdueInvoices)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_PULLLIST, OnUpdateReportsPulllist)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_CHARGEBACKSBYDATE, OnUpdateReportsChargebacksbydate)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_COMPLETEDJOBSNOTPAID, OnUpdateReportsCompletedjobsnotpaid)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_STATUS, OnUpdateReportsStatus)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_STATUS_SINGLE, OnUpdateReportsStatusSingle)
	ON_UPDATE_COMMAND_UI(ID_WARRANTY_OPEN, OnUpdateWarrantyOpen)
	ON_UPDATE_COMMAND_UI(ID_WARRANTY_SCHED, OnUpdateWarrantySched)
	ON_UPDATE_COMMAND_UI(ID_INVENTORY, OnUpdateInventory)
	ON_UPDATE_COMMAND_UI(ID_MATERIALS_NOTRECEIVEDYET, OnUpdateMaterialsNotreceivedyet)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_RA, OnUpdateMaterialRa)
	ON_UPDATE_COMMAND_UI(ID_BILLING_CHARGEBACKS, OnUpdateBillingChargebacks)
	ON_COMMAND(ID_SUB_PHONELIST, OnReportsSubPhonelist)
	ON_UPDATE_COMMAND_UI(ID_SUB_PHONELIST, OnUpdateReportsSubPhonelist)
	ON_COMMAND(ID_BACKGROUNDCHECKS_ALPHABYLASTNAME, OnBackgroundChecksAlphaByLastName)
	ON_UPDATE_COMMAND_UI(ID_BACKGROUNDCHECKS_ALPHABYLASTNAME, OnUpdateBackgroundChecksAlphaByLastName)
	ON_COMMAND(ID_JOBS_ASSIGNMENTS, OnJobsAssignments)
	ON_UPDATE_COMMAND_UI(ID_JOBS_ASSIGNMENTS, OnUpdateJobsAssignments)
	ON_COMMAND(ID_PAYROLL_MESSAGES, OnPayrollMessages)
	ON_UPDATE_COMMAND_UI(ID_PAYROLL_MESSAGES, OnUpdatePayrollMessages)
	ON_COMMAND(ID_SUB_HELPERS, OnSubHelpers)
	ON_UPDATE_COMMAND_UI(ID_SUB_HELPERS, OnUpdateSubHelpers)
	ON_COMMAND(ID_MAINTENANCE_SPNDISCREPANCIES, OnMaintenanceSpndiscrepancies)
	ON_COMMAND(ID_MAINTENANCE_UNITTESTS, OnMaintenanceUnitTests)
	ON_UPDATE_COMMAND_UI(ID_MAINTENANCE_UNITTESTS, OnUpdateMaintenanceUnitTests)
	ON_UPDATE_COMMAND_UI(ID_MAINTENANCE_SPNDISCREPANCIES, OnUpdateMaintenanceSpndiscrepancies)
	ON_COMMAND(ID_VIEW_USERALERTS, OnViewUseralerts)
	ON_COMMAND(ID_WORKMANS_COMP_BY_DATE, OnWorkmansCompByDate)
	ON_COMMAND(ID_LIABILITY_BY_DATE, OnLiabilityByDate)
	ON_UPDATE_COMMAND_UI(ID_WORKMANS_COMP_BY_DATE, OnUpdateWorkmansCompByDate)
	ON_UPDATE_COMMAND_UI(ID_LIABILITY_BY_DATE, OnUpdateLiabilityByDate)
	ON_COMMAND(ID_HELP_REPORTISSUE, OnHelpReportissue)
	ON_COMMAND(ID_VIEW_ACTIVEPOS, OnViewActivePOs)
	ON_COMMAND(ID_VIEW_ACTIVITYLIST, OnViewActivitylist)
	ON_COMMAND(ID_MATERIALS_DAMAGED, &CFlooringApp::OnMaterialsDamaged)
	ON_COMMAND(ID_FILE_SETEMAILPASSWORD, &CFlooringApp::OnFileSetEmailPassword)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlooringApp construction

CFlooringApp::CFlooringApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	CGlobals::m_strUserName = "";
	CGlobals::m_iUserID = -1;

	m_pDlgUserAlerts = NULL;
	m_pDlgActivePOs = NULL;
	m_pDlgActivityList = NULL;
	m_strEmailPassword = "";
	m_strEmailPassword = "";
}

CFlooringApp::~CFlooringApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlooringApp object

CFlooringApp theApp;

LONG WINAPI ExcHandler(struct _EXCEPTION_POINTERS *ExceptionInfo)
{	
	::MessageBox(NULL, "Exception handler called.", "Error!", MB_OK);
	RecordExceptionInfo(ExceptionInfo, _T("Flooring.cpp - Exception Handler"));
	ExitProcess(0);
	return EXCEPTION_CONTINUE_SEARCH;
}

int CFlooringApp::Run()
{
	BOOL bRun = FALSE;
	BOOL bExit = FALSE;

	while(!bExit)
	{
		try
		{
			SetUnhandledExceptionFilter(ExcHandler);
			bRun = CWinApp::Run();
			bExit = TRUE;
		}
		catch (CMemoryException* /* e */)
		{
			TRACE("CMemoryException caught in Run();");
		}
		catch (CFileException* /* e */)
		{
			TRACE("CFileException caught in Run();");
		}
		catch (CException* /* e */)
		{
			TRACE("CException caught in Run();");
		}
	}

	return bRun;
}
/////////////////////////////////////////////////////////////////////////////
// CFlooringApp initialization

BOOL CFlooringApp::InitInstance()
{
	AfxEnableControlContainer();
	AfxInitRichEdit( );
	AfxOleInit();

	// Connect the object to a data source (no password) the ODBC connection dialog box
	// will always remain hidden
	//String ^name = Configuration::ConfigurationManager::AppSettings["name"];

	try
	{
		BOOL ConnectOK = g_dbFlooring.OpenEx( _T( "DSN=Flooring"), CDatabase::noOdbcDialog);		

		Logger& logger = Logger::Instance();
		logger.LogMessage("Starting up...");

		if (TRUE == ConnectOK)
		{
			g_dbFlooring.SetQueryTimeout(4000) ;
		}
		else
		{
			::MessageBox(NULL, "Could not connect to the database.  The program cannot continue.", "Error!", MB_OK);
			return FALSE;
		}
	}
	catch(CDBException e)
	{
		::MessageBox(NULL, "A critical error occurred when connecting to the database.  The program cannot continue.", "Error!", MB_OK);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MFC_VER < 0x0700
	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Custom Installations, Inc."));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	g_pTemplateCustomerPO = new CMultiDocTemplate(
		IDR_CUSTOMER,
		RUNTIME_CLASS(CFlooringDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCustomerView));

	CGlobals::InitDefaultContext();

	CGlobals::SetEmployeeID() ;
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing ;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	CJRSVersion clVersion;
	clVersion.RetrieveInfo();
#ifdef _DEBUG
	CString strTitle = clVersion.GetProductName() + _T(" - Version ") +	clVersion.GetCompleteVersionInfo(); 
#else
	CString strTitle = clVersion.GetProductName() + _T(" - Version ") + clVersion.GetProductVersion();  
#endif

	CString strVersion = clVersion.GetProductVersion();
	if (!CGlobals::ValidateMinimumVersion(strVersion))
	{
		return FALSE;
	}
	
	pMainFrame->m_strFrameTitle = strTitle; 
	pMainFrame->SetWindowText(strTitle); 
	
	// The main window has been initialized, so show and update it.
	m_nCmdShow = SW_SHOWMAXIMIZED ;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	SSCE_SetRegTreeName("HKEY_LOCAL_MACHINE\\SOFTWARE\\Custom Installations, Inc.\\Installation Manager Classic\\Sentry Spelling");

	CSetSettings setSettings(&g_dbFlooring);
	CString strValue = "";
		
	strValue = setSettings.GetSetting("SSCEMainLexPath");
	SSCE_SetMainLexPath(strValue);
    
	strValue = setSettings.GetSetting("SSCEMainLexFiles");
	SSCE_SetMainLexFiles(strValue);

	strValue = setSettings.GetSetting("SSCEUserLexPath");
	SSCE_SetUserLexPath(strValue);

	strValue = setSettings.GetSetting("SSCEUserLexFiles");
	SSCE_SetUserLexFiles(strValue);

	g_strSPNWebServiceURL.Format("http://%s/SpnWebService/SpnWebService.asmx", setSettings.GetSetting("SPNWebServiceServerName") );

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    virtual HWND GetHWND() { return CDialog::GetSafeHwnd(); }    

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strTitle;
	CString m_strVersion;
	CString m_strCopyright;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_strTitle(_T(""))
, m_strVersion(_T(""))
, m_strCopyright(_T(""))
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_ABOUT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_ABOUT_VERSION, m_strVersion);
	DDX_Text(pDX, IDC_ABOUT_COPYRIGHT, m_strCopyright);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFlooringApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFlooringApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CJRSVersion clVersion;
	clVersion.RetrieveInfo();
	m_strVersion = "Version " + clVersion.GetCompleteVersionInfo() ;
	m_strTitle = clVersion.GetProductName() ;
	m_strCopyright = clVersion.GetCopyright() ;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFlooringApp::OnViewStores() 
{
	CDlgStoresPickList dlg(this->GetMainWnd()) ;
	dlg.DoModal() ;
}

int CFlooringApp::ExitInstance() 
{
	delete g_pTemplateCustomerPO ;

	g_dbFlooring.Close() ;

	return CWinApp::ExitInstance();
}

void CFlooringApp::OnViewSubcontractors() 
{
	CDlgSubContractorsList dlg(this->GetMainWnd()) ;
	dlg.DoModal() ;
}

void CFlooringApp::OnViewCustomerPo() 
{
	CFrameWnd* pFrame = g_pTemplateCustomerPO->CreateNewFrame(NULL,NULL) ;
	pFrame->InitialUpdateFrame(NULL, true) ;
}

void CFlooringApp::OnInvoicing() 
{
	CDialogInvoicing* pdlgInv = new CDialogInvoicing() ;
	pdlgInv->Create(IDD_INVOICING) ;
	pdlgInv->ShowWindow(SW_SHOW) ;
}

void CFlooringApp::OnBillingReceivecheck() 
{
	CDlgCheckList dlgCheckList ;
	dlgCheckList.DoModal() ;
}

#include "SetOrders.h"
#include <math.h>
#include ".\flooring.h"

CString CFlooringApp::GetEmailPassword()
{
	return m_strEmailPassword;
}

void CFlooringApp::SetEmailPassword(CString strPassword)
{
	m_strEmailPassword = strPassword;
}

void CFlooringApp::OnUpdateBillingReceivecheck(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CGlobals::HasPermission("CanReceiveCheck") == true) ;
}

void CFlooringApp::OnUpdateInvoicing(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CGlobals::HasPermission("CanEnterInvoice") == true ) ;
}

void CFlooringApp::OnBillingChargebacks() 
{
	CDlgChargebackList dlg(this->GetMainWnd()) ;

	dlg.DoModal() ;
}

void CFlooringApp::OnPayroll() 
{

	CQuickBooks clQB;
	CString strTemp;
	CStringArray astrErrors;
	CStringArray astrWarnings;
	if ( clQB.BuildQuickBooksFile( ) )
	{
		// to get here, we must only have warnings...hence the assertion
		clQB.GetErrors( &astrErrors );
		ASSERT( astrErrors.GetCount() == 0 );

		clQB.GetWarnings(&astrWarnings);

		if ( astrWarnings.GetCount() > 0 )
		{
			CDlgMessages dlgMessages;
			dlgMessages.SetDialogTitle("Payroll Spreadsheet Warnings");
			dlgMessages.SetListTitle("Warning List");
			dlgMessages.SetMessages( &astrWarnings );
			dlgMessages.SetButtonText(IDOK, "Continue");
			dlgMessages.SetButtonText(IDCANCEL, "Abort");
			int iReturn = dlgMessages.DoModal();
			if (iReturn != IDOK)
			{
				// the user did not want to continue, so we are going to exit
				return;
			}
		}

		#ifdef _DEBUG
			strTemp = "After BuildQuickBooksFile";
			AfxMessageBox(strTemp);
		#endif


		// get the grand total from QB class - it's calculated as part of building
		// the QB file.  This way we just pass it in to Crystal and don't have to
		// duplicate the calculation code.
		double fGrandTotal = clQB.GetGrandTotal();
		CString strGrandTotal;
		strGrandTotal.Format("$%.2f", fGrandTotal);

		// also pass in the Week Ending date, which is the date of the next Saturday
		// from today.
		COleDateTime timeWE = clQB.GetWeekEnding();

		CGlobals::PayrollReport(strGrandTotal, timeWE);
	}
	else
	{
		clQB.GetErrors( &astrErrors );
		clQB.GetWarnings(&astrWarnings);

		if ((astrWarnings.GetCount() > 0) || (astrErrors.GetCount() > 0))
		{
			CDlgMessages dlgMessages;
			dlgMessages.SetDialogTitle("Payroll Spreadsheet Warnings / Errors");
			dlgMessages.SetListTitle("Warning / Error List");
			clQB.GetWarnings(&astrWarnings);
			clQB.GetErrors(&astrErrors);
			dlgMessages.SetMessages( &astrWarnings );
			dlgMessages.SetMessages( &astrErrors );
			dlgMessages.DoModal();
		}
	}
}

void CFlooringApp::OnUpdatePayroll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CGlobals::HasPermission("CanProcessPayroll") == true) ;
}


void CFlooringApp::OnCriminalCheckName() 
{
	// TODO: Add your command handler code here
	
}

void CFlooringApp::OnMaterialsChangestatus() 
{
	CDlgMaterialStatus dlg ;
	dlg.DoModal() ;
}

CString CFlooringApp::GetCFUserName()
{
	return CGlobals::m_strUserName ;
}

void CFlooringApp::OnUpdateReportsWorkSummaryByWeek(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportWorkSummary") == true) ;
}

void CFlooringApp::OnUpdateReportsBilling(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportBilling") == true) ;
}

void CFlooringApp::OnUpdateReportsPending(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportPending") == true) ;
}

void CFlooringApp::OnUpdateReportNotBilled(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportNotBilled") == true) ;
}

void CFlooringApp::OnUpdateReportsWeeklytotals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportWeeklyTotals") == true) ;
}

void CFlooringApp::OnUpdateReportOpenInvoice(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportOpenInvoiceRequests") == true) ;
}

void CFlooringApp::OnUpdateOverdueInvoices(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportOver14Days") == true) ;
}

void CFlooringApp::OnUpdateReportsPulllist(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportPullList") == true) ;
}

void CFlooringApp::OnUpdateReportsChargebacksbydate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportChargeBacksByDate") == true) ;
}

void CFlooringApp::OnUpdateReportsCompletedjobsnotpaid(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportCompletedJobsNotPaid") == true) ;
}

void CFlooringApp::OnUpdateReportsStatus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportStatusAll") == true) ;
}

void CFlooringApp::OnUpdateReportsStatusSingle(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportStatusSingle") == true) ;
}

void CFlooringApp::OnUpdateWarrantyOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportWarrantyOpen") == true) ;
}

void CFlooringApp::OnUpdateWarrantySched(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportWarrantySched") == true) ;
}

void CFlooringApp::OnUpdateInventory(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportMaterialsInventory") == true) ;
}

void CFlooringApp::OnUpdateMaterialsNotreceivedyet(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportMaterialsNotReceivedYet") == true) ;
}

void CFlooringApp::OnUpdateMaterialRa(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportMaterialsRA") == true) ;
}

void CFlooringApp::OnUpdateBillingChargebacks(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("AccessBillingChargeBacks") == true) ;
}

void CFlooringApp::OnUpdateReportsSubPhonelist(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportSubContractorPhoneList") == true) ;
}

void CFlooringApp::OnUpdateBackgroundChecksAlphaByLastName(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportSubContractorBackground") == true) ;
}

void CFlooringApp::OnUpdateJobsAssignments(CCmdUI *pCmdUI)
{
	// yes using same permission as for pull list - really not different data
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportInstallerAssignments") == true) ;
}
void CFlooringApp::OnPayrollMessages()
{
	CDlgPayrollMessages dlg;
	dlg.DoModal();
}

void CFlooringApp::OnUpdatePayrollMessages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::IsAdmin() == true );
}

void CFlooringApp::OnMaintenanceSpndiscrepancies()
{
	CDlgDiscrepancies dlg;
	dlg.DoModal();
}

void CFlooringApp::OnMaintenanceUnitTests()
{
	DlgUnitTestResults* p_dialogUnitTestResults = new DlgUnitTestResults();
	p_dialogUnitTestResults->Create(DlgUnitTestResults::IDD);
	p_dialogUnitTestResults->ShowWindow(SW_SHOW);

	UnitTests tests;
	
	bool result = tests.TestSendEmail();
	p_dialogUnitTestResults->AddResults("TestSendEmail()", result);
}

void CFlooringApp::OnUpdateMaintenanceUnitTests(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("CanRunUnitTests"));
}

void CFlooringApp::OnUpdateMaintenanceSpndiscrepancies(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewMaintenanceSPNDiscrepancies"));	
}

void CFlooringApp::OnUpdateSubHelpers(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportSubHelpers"));	
}

void CFlooringApp::OnViewUseralerts()
{
	if (m_pDlgUserAlerts != NULL)
	{
		WINDOWPLACEMENT place;
		m_pDlgUserAlerts->GetWindowPlacement(&place);
		if (place.showCmd == SW_SHOWMINIMIZED)
		{
			m_pDlgUserAlerts->ShowWindow(SW_NORMAL);
		}
		
		m_pDlgUserAlerts->GetWindowPlacement(&place);
		
		CRect main_rect;
		CWnd* pWnd = GetMainWnd();
		pWnd->GetClientRect(&main_rect);
		pWnd->ClientToScreen(&main_rect);

		if ((place.rcNormalPosition.right < main_rect.left) || (place.rcNormalPosition.top > main_rect.bottom))
		{
			CRect rect;
			m_pDlgUserAlerts->GetWindowRect(&rect);
			m_pDlgUserAlerts->MoveWindow(0,0, rect.Width(), rect.Height());
		}
		m_pDlgUserAlerts->SetFocus();
	}
	else
	{
        m_pDlgUserAlerts = new CDlgUserAlerts;
		m_pDlgUserAlerts->Create(IDD_USER_ALERTS);
		m_pDlgUserAlerts->ShowWindow(SW_SHOW);
	}
}


void CFlooringApp::OnUpdateWorkmansCompByDate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportWorkmansCompByDate") == true) ;
}

void CFlooringApp::OnUpdateLiabilityByDate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CGlobals::HasPermission("ViewReportLiabilityByDate") == true) ;
}

void CFlooringApp::OnHelpReportissue()
{
	CPropSheetReportIssueWizard dlg("Report An Issue");
	dlg.DoModal();
}

void CFlooringApp::ImpersonateUser()
{
	CDlgPassword dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.ValidatePassword())
		{
			CDlgUserSelect dlgUsers;
			if (dlgUsers.DoModal() == IDOK)
			{
				CGlobals::SetEmployeeID(dlgUsers.GetEmployeeID());
			}
		}
	}
}

void CFlooringApp::OnViewActivePOs()
{
	if (m_pDlgActivePOs != NULL)
	{
		WINDOWPLACEMENT place;
		m_pDlgActivePOs->GetWindowPlacement(&place);
		if (place.showCmd == SW_SHOWMINIMIZED)
		{
			m_pDlgActivePOs->ShowWindow(SW_NORMAL);
		}
		
		m_pDlgActivePOs->GetWindowPlacement(&place);
		
		CRect main_rect;
		CWnd* pWnd = GetMainWnd();
		pWnd->GetClientRect(&main_rect);
		pWnd->ClientToScreen(&main_rect);

		if ((place.rcNormalPosition.right < main_rect.left) || (place.rcNormalPosition.top > main_rect.bottom))
		{
			CRect rect;
			m_pDlgActivePOs->GetWindowRect(&rect);
			m_pDlgActivePOs->MoveWindow(0,0, rect.Width(), rect.Height());
		}
		m_pDlgActivePOs->SetFocus();
	}
	else
	{
        m_pDlgActivePOs = new CDlgActivePOs;
		m_pDlgActivePOs->Create(IDD_ACTIVE_POS);
		m_pDlgActivePOs->ShowWindow(SW_SHOW);
	}
}

void CFlooringApp::OnViewActivitylist()
{
	if (m_pDlgActivityList != NULL)
	{
		WINDOWPLACEMENT place;
		m_pDlgActivityList->GetWindowPlacement(&place);
		if (place.showCmd == SW_SHOWMINIMIZED)
		{
			m_pDlgActivityList->ShowWindow(SW_NORMAL);
		}
		
		m_pDlgActivityList->GetWindowPlacement(&place);
		
		CRect main_rect;
		CWnd* pWnd = GetMainWnd();
		pWnd->GetClientRect(&main_rect);
		pWnd->ClientToScreen(&main_rect);

		if ((place.rcNormalPosition.right < main_rect.left) || (place.rcNormalPosition.top > main_rect.bottom))
		{
			CRect rect;
			m_pDlgActivityList->GetWindowRect(&rect);
			m_pDlgActivityList->MoveWindow(0,0, rect.Width(), rect.Height());
		}
		m_pDlgActivityList->SetFocus();
	}
	else
	{
        m_pDlgActivityList = new CDlgActivityList;
		m_pDlgActivityList->Create(IDD_ACTIVITY_LIST);
		m_pDlgActivityList->ShowWindow(SW_SHOW);
	}
}

void CFlooringApp::OnFileSetEmailPassword()
{
	CDlgPassword dlgEmailPassword;
	dlgEmailPassword.SetTitle("Enter Email Password");
	if (dlgEmailPassword.DoModal() == IDOK)
	{
		CString strEmailPassword = dlgEmailPassword.GetPassword();
		CSetSettings setSettings(&g_dbFlooring);
		setSettings.SetSetting("UserEmailPassword", strEmailPassword, CGlobals::GetEmployeeID());
	}
}
//////////////////////////////// .Net Code /////////////////////////
void CFlooringApp::OnStoreInfo() 
{
	CGlobals::OnStoreInfo();
}

void CFlooringApp::OnOverdueInvoices() 
{
	CGlobals::OnOverdueInvoices();
}

void CFlooringApp::OnOpenInvoices() 
{
	CGlobals::OnOpenInvoices();
}

void CFlooringApp::OnReportsPending() 
{
	CGlobals::OnReportsPending();
}

void CFlooringApp::OnNotBilled() 
{
	CGlobals::OnNotBilled();
}

void CFlooringApp::OnInventory() 
{
	CGlobals::OnInventory();
}

void CFlooringApp::OnReportsBilling() 
{
	CGlobals::OnReportsBilling();
}

void CFlooringApp::OnWarrantySched() 
{
	CGlobals::OnWarrantySched();
}

void CFlooringApp::OnWarrantyOpen() 
{
	CGlobals::OnWarrantyOpen();
}

void CFlooringApp::OnMaterialRa() 
{
	CGlobals::OnMaterialRa();
}

void CFlooringApp::OnMaterialsNotreceivedyet() 
{
	CGlobals::OnMaterialsNotreceivedyet();
}

void CFlooringApp::OnReportsStatus() 
{
	CGlobals::OnReportsStatus();
}

void CFlooringApp::OnReportsStatusSingle() 
{
	CGlobals::OnReportsStatusSingle();
}

void CFlooringApp::OnReportsPulllist()
{
	CGlobals::OnReportsPulllist();
}

void CFlooringApp::OnReportsWeeklyTotals() 
{
	CGlobals::OnReportsWeeklyTotals();
}

void CFlooringApp::OnReportsCompletedJobsNotPaid()
{
	CGlobals::OnReportsCompletedJobsNotPaid();
}

void CFlooringApp::OnReportsChargebacksByDate()
{
	CGlobals::OnReportsChargebacksByDate();
}

void CFlooringApp::OnReportsWorkSummaryByWeek()
{
	CGlobals::OnReportsWorkSummaryByWeek();
}

void CFlooringApp::OnReportsSubPhonelist()
{
	CGlobals::OnReportsSubPhonelist();
}

void CFlooringApp::OnBackgroundChecksAlphaByLastName()
{
	CGlobals::OnBackgroundChecksAlphaByLastName();
}

void CFlooringApp::OnJobsAssignments()
{
	CGlobals::OnJobsAssignments();
}

void CFlooringApp::OnSubHelpers()
{
	CGlobals::OnSubHelpers();
}

void CFlooringApp::OnWorkmansCompByDate()
{
	CGlobals::OnWorkmansCompByDate();
}

void CFlooringApp::OnLiabilityByDate()
{
	CGlobals::OnLiabilityByDate();
}

void CFlooringApp::OnMaterialsDamaged()
{
	CGlobals::OnMaterialsDamaged();
}
