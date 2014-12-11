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
#include "ViewInvoice.h"
#include "DialogInvoicing.h"
#include "DlgCheckList.h"
#include "SetAdmins.h"
#include "DlgChargebackList.h"
#include "SetChecks.h"
#include "SetCheckDetails.h"
#include "oxshape.h"
#include "JobAssignment.h"
#include "DlgStoreSelection.h"
#include "SetPadFix.h"

#include "SetUser.h"
#include "UpdateOptionCost.h"
#include "UpdateMaterialCost.h"
#include "SetMaterialType.h"
#include "SetMaterial.h"
#include "SetOptions.h"
#include "SetDivision.h"

#include "DlgMaterialStatus.h"
#include "JRSVersions.h"
#include "SetVersion.h"
#include "QuickBooks.h"
#include <sscemfc.hpp>
#include "Permissions.h"

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
#include "WorkOrderHelper.h"
#include "WaiverHelper.h"
#include "UnitTests.h"
#include "DlgUnitTestResults.h"

#include "ExceptionHandler.h"

#include "Logger.h"

//#include "DatabaseConfig.h"

CMultiDocTemplate* g_pTemplateWorkOrder ;
CMultiDocTemplate* g_pTemplateInvoice ;
CMultiDocTemplate* g_pTemplateCustomerPO ;

CDatabase g_dbFlooring;
CString g_strSPNWebServiceURL;
//CString g_strSOSIWebServiceURL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace CFI::InstallationManager::Reports::UI;
using namespace CFI::InstallationManager::Business;

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
	//ON_COMMAND(ID_VIEW_JOBASSIGNMENT, OnViewJobassignment)
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
	ON_COMMAND(ID_REPORTS_FINANCIAL_MATERIAL_PRICING, OnFinancialMaterialpricing)
	ON_COMMAND(ID_MAINTENANCE_SPNDISCREPANCIES, OnMaintenanceSpndiscrepancies)
	ON_COMMAND(ID_MAINTENANCE_UNITTESTS, OnMaintenanceUnitTests)
	ON_UPDATE_COMMAND_UI(ID_MAINTENANCE_UNITTESTS, OnUpdateMaintenanceUnitTests)
	ON_UPDATE_COMMAND_UI(ID_REPORTS_FINANCIAL_MATERIAL_PRICING, OnUpdateReportsFinancialMaterialPricing)
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
	m_strUserName = _T("Unknown");
	m_pDlgUserAlerts = NULL;
	m_pDlgActivePOs = NULL;
	m_pDlgActivityList = NULL;
	m_strEmailPassword = "";
	m_iUserID = -1;
	m_strUserName = "";
	m_strEmailPassword = "";
}

CFlooringApp::~CFlooringApp()
{
	delete m_pperms;
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

	g_pTemplateInvoice = new CMultiDocTemplate(
		IDR_REPORT,
		NULL,						//		RUNTIME_CLASS(CFlooringDoc),
		RUNTIME_CLASS(CMDIChildWnd), // custom MDI child frame
		RUNTIME_CLASS(CViewInvoice));

	ReportHelper::InitDefaultContext();

	SetEmployeeID() ;
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
	if (!ValidateMinimumVersion(strVersion))
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
//	g_strSOSIWebServiceURL.Format("http://%s/SOSIWebService/SOSIWebService.asmx", setSettings.GetSetting("SOSIWebServiceServerName") );

	m_pperms = new CPermissions();

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
	delete g_pTemplateInvoice ;

	g_dbFlooring.Close() ;

	return CWinApp::ExitInstance();
}

void CFlooringApp::OnStoreInfo() 
{
	ReportHelper::Stores(Mode::View);
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
	CDlgSelectVendor dlgSelectVendor;
	if ( dlgSelectVendor.DoModal() == IDOK )
	{
		CDialogInvoicing* pdlgInv = new CDialogInvoicing() ;
		pdlgInv->Create(IDD_INVOICING) ;
		pdlgInv->SetVendorID(dlgSelectVendor.GetVendorID());
		pdlgInv->ShowWindow(SW_SHOW) ;
	}
}

void CFlooringApp::OnBillingReceivecheck() 
{
	CDlgCheckList dlgCheckList ;
	dlgCheckList.DoModal() ;
}

#include "SetOrders.h"
#include <math.h>
#include ".\flooring.h"

bool CFlooringApp::IsAdmin()
{
	return m_bAdmin;
}

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
	pCmdUI->Enable(m_pperms->HasPermission("CanReceiveCheck") == true) ;
}

void CFlooringApp::OnUpdateInvoicing(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pperms->HasPermission("CanEnterInvoice") == true ) ;
}

void CFlooringApp::OnBillingChargebacks() 
{
	CDlgChargebackList dlg(this->GetMainWnd()) ;

	dlg.DoModal() ;
//	CFrameWnd* pFrame = m_pTemplateChargeBackView->CreateNewFrame(NULL,NULL) ;
//	pFrame->InitialUpdateFrame(NULL, true) ;
}

void CFlooringApp::OnOverdueInvoices() 
{
	ReportHelper::OverdueInvoices(Mode::View);
}

void CFlooringApp::OnOpenInvoices() 
{
	ReportHelper::OpenInvoices(Mode::View);
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

		ReportHelper::PayrollReport(gcnew System::String(strGrandTotal), System::DateTime::FromOADate(timeWE), Mode::View);
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
	pCmdUI->Enable(m_pperms->HasPermission("CanProcessPayroll") == true) ;
}


void CFlooringApp::OnReportsPending() 
{
	ReportHelper::PendingInvoices(Mode::View);
}

//int DownloadDrawingList(CString strNumber, CString& strTimeStamp)
//{
//	int iNumberFound = -1 ;
//
//	try
//	{
//		CInternetSession session;
//		CHttpConnection* pConnection = session.GetHttpConnection(_T("www.measurecomp.com"));
//
//		CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
//		CString strFormData = _T("Name=raboud&Password=justdoit");
//
//		DWORD dwRet ;
//		CString	name = "" ;
//
//		GetPage(pConnection, "/scripts/renderpdfsys.exe/login", strHeaders, strFormData, name ) ;
//
//		strFormData.Format("MeasNum=%s&StoreOrder=&Style=0", strNumber);
//		strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
//		dwRet = GetPage(pConnection, "/scripts/renderpdfsys.exe/choosecalc", strHeaders, strFormData, name) ;
//
//		int iIndex = 0 ;
//		strTimeStamp = "" ;
//		iNumberFound = 0 ;
///*
//		int i = 0 ;
//		while (i < name.GetLength())
//		{
//			TRACE("%s", name.Mid(i, 128)) ;
//			i += 128 ;
//
//		}
//*/		while  ((iIndex = name.Find("CalcNum=", iIndex)) > 0)
//		{
//			iIndex = name.Find('>', iIndex) + 1;
//			iNumberFound ++ ;
//			if (iNumberFound > 1)
//			{
//				strTimeStamp += "\n" ;
//			}
//			strTimeStamp += name.Mid(iIndex, name.Find('<', iIndex) - iIndex ) ;
//		}
//
//		pConnection->Close() ;
//		delete pConnection;
//		session.Close() ;
//	}
//	catch(CInternetException* pE)
//	{
//		pE->Delete() ;
//	}
//	return iNumberFound ;
//}


//int DownloadDrawing(CString strNumber, CString strTimeStamp)
//{
//	CString strTemp = strTimeStamp ;
//	strTemp.Replace("/", "") ;
//	strTemp.Replace(":", "") ;
//	CSetSettings setSettings(&g_dbFlooring);
//	CString strDrawingsFolder = setSettings.GetSetting("DrawingsFolder");
//	CString strFileName  = strDrawingsFolder + strNumber + "-" + strTemp + ".pdf" ;
//	DWORD dwWritten = 0;
//
//	try
//	{
//		CInternetSession session;
//		CHttpConnection* pConnection = session.GetHttpConnection(_T("www.measurecomp.com"));
//
//		CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
//		CString strFormData = _T("Name=raboud&Password=justdoit");
//
//		DWORD dwRet ;
//		CString	name = "" ;
//
//		GetPage(pConnection, "/scripts/renderpdfsys.exe/login", strHeaders, strFormData, name) ;
//
//		strFormData.Format("MeasNum=%s&StoreOrder=&Style=0", strNumber);
//		strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
//		dwRet = GetPage(pConnection, "/scripts/renderpdfsys.exe/choosecalc", strHeaders, strFormData, name) ;
//
//		// locate the timestamp we want, this identifies the area of the buffer in which to extract our
//		// link
//		int iIndex = name.Find(strTimeStamp) - 4 ;
//		if (iIndex < 0)
//		{
//			pConnection->Close() ;
//			delete pConnection;
//			session.Close() ;
//			::MessageBox(NULL, "Could not retrieve MeasureComp drawing.", "MeasureComp Error", MB_OK) ;
//			return -1 ;
//		}
//
//		// go backwards from the timestamp to the beginning of the anchor tag contents
//		int iStart = name.Left(iIndex).ReverseFind('"') + 1;
//				
//		if (iStart < 0)
//		{
//			pConnection->Close() ;
//			delete pConnection;
//			session.Close() ;
//			::MessageBox(NULL, "Could not retrieve MeasureComp drawing.", "MeasureComp Error", MB_OK) ;
//			return -1 ;
//		}
//
//		// get the substring from the buffer that contains our anchor tag contents (the characters
//		// between the quotes inside the <a> tag)
//				
//		CString strSub;				// substring that will hold the drawing link in it
//		strSub = name.Mid(iStart, iIndex - iStart);
//		
//		// this function uses the Tokenize() call to extract the portion of the URL we want.
//		CString strUrl = "";
//		CString strTemp = GetDrawingURL(strSub);
//
//		if (strTemp.GetLength() == 0)
//		{
//			pConnection->Close() ;
//			delete pConnection;
//			session.Close() ;
//			::MessageBox(NULL, "Could not retrieve MeasureComp drawing.", "MeasureComp Error", MB_OK) ;
//			return -1 ;
//		}
//
//		// format our url to get the PDF file.
//		strUrl.Format("/scripts/renderpdfsys.exe/%s", strTemp) ;
//
//		strFormData = _T("");
//		strHeaders = _T("");
//		HANDLE heMail =	CreateFile (strFileName, GENERIC_WRITE, FILE_SHARE_READ,NULL,
//				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//		
//		// get the pdf and save to disk.  If dwWritten is 0, means we could not write the drawing
//		dwRet = GetPage(pConnection, strUrl, strHeaders, strFormData, name, dwWritten, heMail) ;
//
//		CloseHandle(heMail);
//		pConnection->Close() ;
//		delete pConnection;
//		session.Close() ;
//	}
//	catch(CInternetException* pE)
//	{
//		pE->Delete() ;
//		::MessageBox(NULL, "MeasureComp drawing is not available", "MeasureComp Error", MB_OK) ;
//	}
//
//	if (dwWritten == 0)
//	{
//		::MessageBox(NULL, "Could not retrieve MeasureComp drawing.", "MeasureComp Error", MB_OK) ;
//	}
//	else
//	{
//		ShellExecute(NULL, "print", strFileName, NULL, NULL, SW_HIDE ) ;
//	}
//	return 1 ;
//}

//CString GetDrawingURL(CString strSubString)
//{
//	// passed in string must contain the 'renderpdf?' substring to extract
//	CString strURL = "";
//	CString strTokenSep = "'";
//
//	int iCurPos = 0;
//	
//	CString strToken = strSubString.Tokenize(strTokenSep, iCurPos);
//    while (strToken != "")
//	{
//		if (strToken.Find("renderpdf?") > -1)
//		{
//			strURL = strToken;
//			break;
//		}
//		strToken = strSubString.Tokenize(strTokenSep, iCurPos);
//	}
//
//	return strURL;
//}

//DWORD GetPage(CHttpConnection* pConnection, CString strUrl, CString strHeaders, CString strFormData, CString &name, HANDLE heMail)
//{
//	DWORD dwWritten = 0;
//	return GetPage(pConnection, strUrl, strHeaders, strFormData, name, dwWritten, heMail);
//}

//DWORD GetPage(CHttpConnection* pConnection, CString strUrl, CString strHeaders, CString strFormData, CString &name, DWORD &dwTotalWritten, HANDLE heMail)
//{
//	CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strUrl);
//	pFile->SendRequest(strHeaders, (LPVOID)(LPCTSTR)strFormData, strFormData.GetLength()); 
//
//	DWORD dwRet ;
//	DWORD dwRead ;
//	DWORD dwWritten = 0;
//	dwTotalWritten = 0;
//	char aBuffer[1024] ;
//
//	pFile->QueryInfoStatusCode(dwRet);
//	name = "" ;
//
//	if (dwRet == HTTP_STATUS_OK)
//	{
//		while ((dwRead = pFile->Read(aBuffer, sizeof(aBuffer)-1)) > 0)
//		{
//			aBuffer[dwRead]=NULL;
//			if (heMail != NULL)
//			{
//				WriteFile (heMail, aBuffer, dwRead, &dwWritten, NULL); 
//				dwTotalWritten += dwWritten;
//			}
//			name += aBuffer;
//		}
//	}
//	pFile->Close() ;
//	delete pFile;
//
//	return dwRet ;
//}
//
//
//
//
///*
//	http://www.measurecomp.com/scripts/renderpdfsys.exe/login
//	Name=raboud&Password=justdoit
//	Content-Type: application/x-www-form-urlencoded
//
//  	http://www.measurecomp.com/scripts/renderpdfsys.exe/choosecalc
//	MeasNum=706929&StoreOrder=
//	Content-Type: application/x-www-form-urlencoded
//
//	http://www.measurecomp.com/scripts/renderpdfsys.exe/renderpdf?MeasNum=706929&CalcNum=0
//
//  */



void CFlooringApp::OnNotBilled() 
{
	ReportHelper::NotBilled(Mode::View);
}

void CFlooringApp::OnInventory() 
{
	ReportHelper::Inventory(Mode::View);
}

void CFlooringApp::SetAdmin()
{
	m_bAdmin = false;
	CSetAdmins setAdmins(&g_dbFlooring) ;
	setAdmins.m_strFilter.Format("name = '%s'", this->m_strUserName);
	setAdmins.Open() ;
	if (!setAdmins.IsEOF())
	{
		m_bAdmin = true;
	}
	setAdmins.Close();	
}

void CFlooringApp::OnCriminalCheckName() 
{
	// TODO: Add your command handler code here
	
}

void CFlooringApp::OnReportsBilling() 
{
	ReportHelper::Billing(Mode::View);
}

void CFlooringApp::OnMaterialsChangestatus() 
{
	CDlgMaterialStatus dlg ;
	dlg.DoModal() ;
}

void CFlooringApp::OnViewJobassignment() 
{
	CDlgJobAssignment dlg ;
	dlg.DoModal() ;
}

void CFlooringApp::SetEmployeeID(int ID)
{
	if (ID != -1)
	{
		CachedData::ImpersonateUser(ID);
		CSetEmployees set(&g_dbFlooring);
		set.m_strFilter.Format("ID = %d", ID);
		set.Open() ;
		if (!set.IsEOF())
		{
			m_iUserID = ID;
			m_strUserName = set.m_UserName;
		}
		set.Close();

	}
	else
	{
		SetEmployeeID();
	}

	SetAdmin();
}


void CFlooringApp::SetEmployeeID()
{
	_TCHAR auName[200] ;
	unsigned long lLength = sizeof(auName) / sizeof(auName[0]) ;

	//CSetUser set(&g_dbFlooring) ;
	CSetEmployees set(&g_dbFlooring);
	set.Open() ;

	GetUserName(auName, &lLength) ;

	while (!set.IsEOF())
	{
		if (set.m_UserName.CompareNoCase(auName) == 0)
		{
			m_iUserID = set.m_ID;
			m_strUserName = set.m_UserName;
			break ;
		}
		set.MoveNext() ;
	}
	set.Close() ;

	SetAdmin();
}

CString CFlooringApp::GetComputerName()
{
	CString computerName = "";
	TCHAR buffer[256] = TEXT("");	
	DWORD dwSize = sizeof(buffer);

	if (GetComputerNameEx(ComputerNamePhysicalDnsHostname, buffer, &dwSize))
	{
		computerName = CString(buffer);
	}

	return computerName;
}

int CFlooringApp::GetEmployeeID()
{
	if (m_iUserID == -1)
	{
		SetEmployeeID();
	}
	
	return m_iUserID ;
}

CString CFlooringApp::GetCFUserName()
{
	return m_strUserName ;
}

CString CFlooringApp::GetUserFirstAndLastName()
{
	CString strName = m_strUserName;

	CSetEmployees setEmployees(&g_dbFlooring);
	setEmployees.m_strFilter.Format("UserName = '%s'", m_strUserName);
	setEmployees.Open();
	if (!setEmployees.IsEOF())
	{
		strName.Format(_T("%s %s"), setEmployees.m_FirstName, setEmployees.m_LastName); 
	}

	return strName;
}

void CFlooringApp::OnWarrantySched() 
{
	ReportHelper::ScheduledWarranties(Mode::View);
}

void CFlooringApp::OnWarrantyOpen() 
{
	ReportHelper::OpenWarranties(Mode::View);
}

void CFlooringApp::OnMaterialRa() 
{
	ReportHelper::InventoryWaitingOnRA(Mode::View);
}

void CFlooringApp::OnMaterialsNotreceivedyet() 
{
	ReportHelper::InventoryNotPresent(Mode::View);
}

void CFlooringApp::OnReportsStatus() 
{

	// This function call will cause the stored procedure to generate data for all stores
	int iResponse = AfxMessageBox("This report takes more than 1 minute to generate.\n\nClick OK button to proceed, Cancel to quit.", MB_OKCANCEL | MB_ICONINFORMATION);

	if (iResponse == IDOK)
	{
		ReportHelper::DetailedStatus(Mode::View);
	}
}

void CFlooringApp::OnReportsStatusSingle() 
{
	CDlgStoreSelection dlgStore ;

	if (dlgStore.DoModal() == IDOK)
	{
		ReportHelper::DetailedStatusByStore(gcnew System::String(dlgStore.GetStoreNumber()), Mode::View);
	}
}

void CFlooringApp::OnReportsPulllist()
{
	ReportHelper::PullList(Mode::View);
}

void CFlooringApp::OnReportsWeeklyTotals() 
{
	ReportHelper::WeeklyTotals(Mode::View);
}

void CFlooringApp::OnReportsCompletedJobsNotPaid()
{
	ReportHelper::CompletedJobsNotPaid(Mode::View);
}

void CFlooringApp::OnReportsChargebacksByDate()
{
	ReportHelper::ChargebacksByDate(Mode::View);
}

void CFlooringApp::OnReportsWorkSummaryByWeek()
{
	ReportHelper::WeeklyUnitsTotals(Mode::View);
}

void CFlooringApp::OnUpdateReportsWorkSummaryByWeek(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportWorkSummary") == true) ;
}

void CFlooringApp::OnUpdateReportsBilling(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportBilling") == true) ;
}

void CFlooringApp::OnUpdateReportsPending(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportPending") == true) ;
}

void CFlooringApp::OnUpdateReportNotBilled(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportNotBilled") == true) ;
}

void CFlooringApp::OnUpdateReportsWeeklytotals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportWeeklyTotals") == true) ;
}

void CFlooringApp::OnUpdateReportOpenInvoice(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportOpenInvoiceRequests") == true) ;
}

void CFlooringApp::OnUpdateOverdueInvoices(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportOver14Days") == true) ;
}

void CFlooringApp::OnUpdateReportsPulllist(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportPullList") == true) ;
}

void CFlooringApp::OnUpdateReportsChargebacksbydate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportChargeBacksByDate") == true) ;
}

void CFlooringApp::OnUpdateReportsCompletedjobsnotpaid(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportCompletedJobsNotPaid") == true) ;
}

void CFlooringApp::OnUpdateReportsStatus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportStatusAll") == true) ;
}

void CFlooringApp::OnUpdateReportsStatusSingle(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportStatusSingle") == true) ;
}

void CFlooringApp::OnUpdateWarrantyOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportWarrantyOpen") == true) ;
}

void CFlooringApp::OnUpdateWarrantySched(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportWarrantySched") == true) ;
}

void CFlooringApp::OnUpdateInventory(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportMaterialsInventory") == true) ;
}

void CFlooringApp::OnUpdateMaterialsNotreceivedyet(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportMaterialsNotReceivedYet") == true) ;
}

void CFlooringApp::OnUpdateMaterialRa(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportMaterialsRA") == true) ;
}

void CFlooringApp::OnUpdateBillingChargebacks(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("AccessBillingChargeBacks") == true) ;
}

void CFlooringApp::OnReportsSubPhonelist()
{
	ReportHelper::SubContractorsPhoneList(Mode::View);
}

void CFlooringApp::OnUpdateReportsSubPhonelist(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportSubContractorPhoneList") == true) ;
}

void CFlooringApp::OnBackgroundChecksAlphaByLastName()
{
	ReportHelper::SubContractorsBackgroundCheckStatus(Mode::View);
}

void CFlooringApp::OnUpdateBackgroundChecksAlphaByLastName(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportSubContractorBackground") == true) ;
}

void CFlooringApp::OnJobsAssignments()
{
	ReportHelper::InstallerAssignments(Mode::View);
}

void CFlooringApp::OnUpdateJobsAssignments(CCmdUI *pCmdUI)
{
	// yes using same permission as for pull list - really not different data
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportInstallerAssignments") == true) ;
}

BOOL CFlooringApp::ValidateMinimumVersion( CString strVersion )
{
	BOOL bValid = FALSE;

	int iMinimumVersionMajorSW = atoi(strVersion.Left(strVersion.Find('.')));
	int iMinimumVersionMinorSW = atoi(strVersion.Right(strVersion.GetLength() - strVersion.Find('.') - 1));

	CString computerName = GetComputerName();
	if (computerName.GetLength() > 0)
	{
		CSetSettings setSettings(&g_dbFlooring);
		CString ComputerAndVersionValue = "";
		ComputerAndVersionValue.Format("%s - %s", computerName, strVersion);
		setSettings.SetSetting("IMClassicVersion", ComputerAndVersionValue, m_iUserID);
	}

	CSetVersion setVersion(&g_dbFlooring);
	setVersion.Open();
	if ( (iMinimumVersionMajorSW > setVersion.m_MinimumVersionMajor) ||
		 ((iMinimumVersionMajorSW == setVersion.m_MinimumVersionMajor) &&
		 (iMinimumVersionMinorSW >= setVersion.m_MinimumVersionMinor))
	   )
	{
		bValid = TRUE;
	}
	else
	{
		CString strReqVersion;
		strReqVersion.Format("%d.%d", setVersion.m_MinimumVersionMajor, setVersion.m_MinimumVersionMinor);
		CString strMessage;
		strMessage.Format("This version of Installation Manager (%s) and is too old to run against the database.  You must run Flooring version %s or higher.",
			strVersion, strReqVersion);
		AfxMessageBox(strMessage, MB_OK);
	}

    return bValid;

}
void CFlooringApp::OnPayrollMessages()
{
	CDlgPayrollMessages dlg;
	dlg.DoModal();
}

void CFlooringApp::OnUpdatePayrollMessages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->IsAdmin() == true );
}

void CFlooringApp::OnSubHelpers()
{
	ReportHelper::HelperAssignments(Mode::View);
}

void CFlooringApp::OnFinancialMaterialpricing()
{
	ReportHelper::Pricing(Mode::View);
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
	pCmdUI->Enable(m_pperms->HasPermission("CanRunUnitTests"));
}

void CFlooringApp::OnUpdateReportsFinancialMaterialPricing(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportMaterialPricing"));	
}

void CFlooringApp::OnUpdateMaintenanceSpndiscrepancies(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewMaintenanceSPNDiscrepancies"));	
}

void CFlooringApp::OnUpdateSubHelpers(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportSubHelpers"));	
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


void CFlooringApp::OnWorkmansCompByDate()
{
	ReportHelper::WorkmansCompByDate(Mode::View);
}

void CFlooringApp::OnLiabilityByDate()
{
	ReportHelper::LiabilityByDate(Mode::View);
}

void CFlooringApp::OnUpdateWorkmansCompByDate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportWorkmansCompByDate") == true) ;
}

void CFlooringApp::OnUpdateLiabilityByDate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pperms->HasPermission("ViewReportLiabilityByDate") == true) ;
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
				SetEmployeeID(dlgUsers.GetEmployeeID());
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

void CFlooringApp::OnMaterialsDamaged()
{
	ReportHelper::InventoryDamage(Mode::View);
}

void CFlooringApp::PrintPONote(int iNoteID)
{
	ReportHelper::PONote(iNoteID, Mode::Print);
}

void CFlooringApp::PrintCustSatReport(int iReportID)
{
	ReportHelper::CustomerSatisfactionConcern(iReportID, Mode::Print);
}

void CFlooringApp::PrintPO(int iOrderID)
{
	ReportHelper::PO(iOrderID, Mode::Print);
}

void CFlooringApp::ViewPO(int iOrderID)
{
	ReportHelper::PO(iOrderID, Mode::View);
}

void CFlooringApp::PrintStorePickup(int iOrderID)
{
	ReportHelper::StorePickup(iOrderID, Mode::Print);
}

::System::Collections::Generic::List<int>^ GetPoList(CPoList* listPOs)
{
	::System::Collections::Generic::List<int>^ l = gcnew ::System::Collections::Generic::List<int>();
		POSITION pos = listPOs->GetHeadPosition() ;
		while (pos)
		{
			l->Add(listPOs->GetNext(pos));
		}
	return l;
}

void CFlooringApp::ViewWorkOrder(CPoList* listPOs, bool PrintOnly)
{
	CWorkOrderHelper WorkOrderHelper;
	if (WorkOrderHelper.SetPoList(listPOs))
	{
		if (PrintOnly)
		{
			ReportHelper::WorkOrder(GetPoList(listPOs), Mode::Print);
		}
		else
		{
			ReportHelper::WorkOrder(GetPoList(listPOs), Mode::View);
		}
	}
	else
	{
		if (WorkOrderHelper.m_strErrorMessage.GetLength() > 0)
		{
			MessageBox(NULL, WorkOrderHelper.m_strErrorMessage, "Notice", MB_OK);
		}
	}	
}

void CFlooringApp::PrintWorkOrder(CPoList* listPOs)
{
	ViewWorkOrder(listPOs, true);
}

void CFlooringApp::ViewWaiver(CPoList* listPOs, bool PrintOnly)
{
	CWaiverHelper WaiverHelper;
	if (WaiverHelper.SetPoList(listPOs))
	{
		if (PrintOnly)
		{
			ReportHelper::Waiver(GetPoList(listPOs), Mode::Print);
		}
		else
		{
			ReportHelper::Waiver(GetPoList(listPOs), Mode::View);
		}
	}
	else
	{
		if (WaiverHelper.m_strErrorMessage.GetLength() > 0)
		{
			MessageBox(NULL, WaiverHelper.m_strErrorMessage, "Notice", MB_OK);
		}
	}	
}

void CFlooringApp::PrintWaiver(CPoList* listPOs)
{
	ViewWaiver(listPOs, true);
}

void CFlooringApp::PrintReviewChecklist(int OrderID)
{
	ReportHelper::ReviewChecklist(OrderID, Mode::Print);
}

void CFlooringApp::PrintSchedulingChecklist(int OrderID)
{
	ReportHelper::SchedulingChecklist(OrderID, Mode::Print);
}

void CFlooringApp::ViewWoodFlooringWaiver(int OrderID, bool PrintOnly)
{
	if (PrintOnly)
	{
		ReportHelper::WoodFlooringWaiver(OrderID, Mode::Print);
	}
	else
	{
		ReportHelper::WoodFlooringWaiver(OrderID, Mode::View);
	}
}

void CFlooringApp::PrintWoodFlooringWaiver(int OrderID)
{
	ViewWoodFlooringWaiver(OrderID, true);
}

void CFlooringApp::OnFileSetEmailPassword()
{
	CDlgPassword dlgEmailPassword;
	dlgEmailPassword.SetTitle("Enter Email Password");
	if (dlgEmailPassword.DoModal() == IDOK)
	{
		CString strEmailPassword = dlgEmailPassword.GetPassword();
		CSetSettings setSettings(&g_dbFlooring);
		setSettings.SetSetting("UserEmailPassword", strEmailPassword, GetEmployeeID());
	}
}
