/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgActionReport.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "DlgActionReport.h"

#include "SetActionReport.h"
#include "SetOrders.h"
#include "SetCustomer.h"
#include "SetActionReport.h"
#include "SetEmployees.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace CFI::InstallationManager::Reports::UI;

/////////////////////////////////////////////////////////////////////////////
// CDlgActionReport dialog


CDlgActionReport::CDlgActionReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgActionReport::IDD, pParent)
{
	m_iCustomerId = -1 ;
	m_iOrderId = -1 ;
	m_iId = -1 ;
	m_strCurrentActionText = _T("");
	m_strCurrentCauseText = _T("");
	m_strCurrentNatureText = _T("");

	//{{AFX_DATA_INIT(CDlgActionReport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgActionReport::~CDlgActionReport()
{
	delete m_ppageAction;
	delete m_ppageNature;
	delete m_ppageCause;
}


void CDlgActionReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgActionReport)
	DDX_Control(pDX, IDC_INFO, m_staticInfo);
	DDX_Control(pDX, IDC_STORE_ERROR, m_listStoreError);
	DDX_Control(pDX, IDC_MILL_ERROR, m_listMillError);
	DDX_Control(pDX, IDC_MEASURE_ERROR, m_listMeasureError);
	DDX_Control(pDX, IDC_INSTALLER_ERROR, m_listInstallerError);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_ACTION_REPORT_BOLD_BUTTON, m_btnBold);
	DDX_Control(pDX, IDC_ACTION_REPORT_ITALIC_BUTTON, m_btnItalic);
	DDX_Control(pDX, IDC_ACTION_REPORT_UNDERLINE_BUTTON, m_btnUnderline);
	DDX_Control(pDX, IDC_STATIC_ACTION_REPORT_TODAY, m_stTodaysDate);
	DDX_Control(pDX, IDC_ACTIONREPORT_FONTCOMBO, m_cbFontNames);
	DDX_Control(pDX, IDC_ACTIONREPORT_FONTSIZE_COMBO, m_cbFontSizes);
}


BEGIN_MESSAGE_MAP(CDlgActionReport, CDialog)
	//{{AFX_MSG_MAP(CDlgActionReport)
	ON_LBN_SELCHANGE(IDC_INSTALLER_ERROR, OnChange)
	ON_LBN_SELCHANGE(IDC_MEASURE_ERROR, OnChange)
	ON_LBN_SELCHANGE(IDC_MILL_ERROR, OnChange)
	ON_LBN_SELCHANGE(IDC_STORE_ERROR, OnChange)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ACTION_REPORT_BOLD_BUTTON, OnBnClickedActionReportBoldButton)
	ON_BN_CLICKED(IDC_ACTION_REPORT_ITALIC_BUTTON, OnBnClickedActionReportItalicButton)
	ON_BN_CLICKED(IDC_ACTION_REPORT_UNDERLINE_BUTTON, OnBnClickedActionReportUnderlineButton)
	ON_BN_CLICKED(IDC_ACTION_REPORT_VIEWPRINTREPORT_BUTTON, OnBnClickedActionReportViewprintreportButton)
	ON_MESSAGE(CGlobals::WM_USER_RICHEDITCHANGE, OnRichEditChange)
	ON_MESSAGE(CGlobals::WM_USER_RICHEDITLOSEFOCUS, OnRichEditLoseFocus)
	ON_BN_CLICKED(IDC_ACTION_REPORT_CHECKSPELLING, OnBnClickedActionReportCheckspelling)
	ON_CBN_SELCHANGE(IDC_ACTIONREPORT_FONTSIZE_COMBO, OnCbnSelchangeActionreportFontsizeCombo)
	ON_CBN_SELCHANGE(IDC_ACTIONREPORT_FONTCOMBO, OnCbnSelchangeActionreportFontcombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgActionReport message handlers

LRESULT CDlgActionReport::OnRichEditChange(WPARAM /* wParam */, LPARAM /* lParam */)
{
	bool bDirty = false;
	CString strTemp;
	CString strDummy;
	
	if ( m_ppageAction->GetCombinedRTF(strTemp, strDummy) )
	{
		bDirty = ( strTemp != m_strCurrentActionText);
		if (bDirty)
		{
			m_strCurrentActionText = strTemp;
		}
	}

	if (!bDirty)
	{
		if ( m_ppageNature->GetCombinedRTF(strTemp, strDummy) )
		{
			bDirty = ( strTemp != m_strCurrentNatureText);
			if (bDirty)
			{
				m_strCurrentNatureText = strTemp;
			}
		}
	}

	if (!bDirty)
	{
		if ( m_ppageCause->GetCombinedRTF(strTemp, strDummy) )
		{
			bDirty = ( strTemp != m_strCurrentCauseText);
			if (bDirty)
			{
				m_strCurrentCauseText = strTemp;
			}
		}
	}

	if (bDirty)
	{
		OnChange();
	}
	return 0;
}

LRESULT CDlgActionReport::OnRichEditLoseFocus(WPARAM wParam, LPARAM /* lParam */)
{
	CWnd* pwnd = GetFocus();
	if ((pwnd != NULL) && (IsWindow(pwnd->m_hWnd)))
	{
		if ((pwnd->m_hWnd == m_btnBold.m_hWnd)   ||
			(pwnd->m_hWnd == m_btnItalic.m_hWnd) ||
			(pwnd->m_hWnd == m_btnUnderline.m_hWnd))
		{
			m_wndeditFocus = (CWnd*) wParam;
		}
		else
		{
			m_wndeditFocus = NULL;
		}
	}
	return 0;
}

void CDlgActionReport::SetId(int iID)
{
	m_iId = iID ;
	CSetActionReport set(&g_dbFlooring) ;
	set.m_strFilter.Format("Id = '%d'", m_iId) ;
	set.Open() ;

	SetOrderId(set.m_OrderID) ;
	set.Close() ;
}

void CDlgActionReport::SetOrderId(int iOrderID)
{
	m_iOrderId = iOrderID ;
	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("OrderId = '%d'", m_iOrderId) ;
	setOrders.Open() ;

	SetCustomerId(setOrders.m_CustomerID) ;
	setOrders.Close() ;
}

void CDlgActionReport::SetCustomerId(int iCustomerID)
{
	m_iCustomerId = iCustomerID ;
}

void CDlgActionReport::OnChange() 
{
	m_bDirty = true ;
	GetDlgItem(IDOK)->EnableWindow(TRUE) ;	
}

BOOL CDlgActionReport::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ppageAction = new CCustomerSatPropertyPage(IDS_ACTIONTITLE);
	m_ppageNature = new CCustomerSatPropertyPage(IDS_NATURETITLE);
	m_ppageCause = new CCustomerSatPropertyPage(IDS_CAUSETITLE);

	m_sheetCustomerSat.AddPage(m_ppageNature);
	m_sheetCustomerSat.AddPage(m_ppageAction);
	m_sheetCustomerSat.AddPage(m_ppageCause);
	
	try
	{
		CString strInfo ;

		CSetCustomer set(&g_dbFlooring) ;
		set.m_strFilter.Format("CustomerID = '%d'", m_iCustomerId) ;
		set.Open() ;
		
		CString strTemp ;
		strInfo.Format("%s, %s\n%s\n%s, %s %s\n\nHome: %s\nWork: %s", set.m_LastName, set.m_FirstName, set.m_Address, set.m_City, set.m_State, set.m_ZipCode, set.m_PhoneNumber, set.m_WorkNumber) ;
		m_staticInfo.SetWindowText(strInfo) ;
		set.Close() ;
	}
	catch (CException *pE)
	{
		pE->Delete() ;
	}

	if (m_iId != -1)
	{

		CSetActionReport set(&g_dbFlooring) ;
		set.m_strFilter.Format("Id = '%d'", m_iId) ;
		set.Open() ;

		m_listStoreError.SetSelection(set.m_StoreError) ;
		m_listMillError.SetSelection(set.m_MillError) ;
		m_listMeasureError.SetSelection(set.m_MeasureError) ;
		m_listInstallerError.SetSelection(set.m_InstallerError) ;

		m_ppageAction->SetExistingWindowText(set.m_ActionRequired);
		m_strCurrentActionText = set.m_ActionRequired;
		
		m_ppageCause->SetExistingWindowText(set.m_Cause);
		m_strCurrentCauseText = set.m_Cause;
		
		m_ppageNature->SetExistingWindowText(set.m_Nature);
		m_strCurrentNatureText = set.m_Nature;

		CPermissions perm;
		if ( perm.HasPermission("EditExistingActionReport") == true )
		{
			m_ppageAction->SetExistingReadOnly( false );
			m_ppageCause->SetExistingReadOnly( false );
			m_ppageNature->SetExistingReadOnly( false ) ;
		}

		set.Close() ;
	}

	m_sheetCustomerSat.Create(this, WS_CHILD | WS_VISIBLE, 0);
	m_sheetCustomerSat.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_sheetCustomerSat.ModifyStyle( 0, WS_TABSTOP );
	
	CRect rcSheet;
	GetDlgItem( IDC_PROPSHEET )->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );

	m_sheetCustomerSat.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 
			SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	m_sheetCustomerSat.ShowWindow(SW_SHOW);
    
//	HBITMAP hbmp = ::LoadBitmap( NULL, MAKEINTRESOURCE(IDB_BOLDBITMAP) );

	m_bmpBold.LoadBitmap(IDB_BOLDBITMAP);
	m_bmpItalic.LoadBitmap(IDB_ITALICBITMAP);
	m_bmpUnderline.LoadBitmap(IDB_UNDERLINEBITMAP);

	m_btnBold.SetBitmap( (HBITMAP) m_bmpBold.GetSafeHandle() );
	m_btnItalic.SetBitmap( (HBITMAP) m_bmpItalic.GetSafeHandle() );
	m_btnUnderline.SetBitmap( (HBITMAP) m_bmpUnderline.GetSafeHandle() );

	COleDateTime dtToday = CGlobals::GetCurrentSystemTime();
	CString strDate = "Today's Date: " + dtToday.Format("%m/%d/%Y");
	m_stTodaysDate.SetWindowText( strDate );

	m_cbFontNames.Init();

	int i = m_cbFontSizes.AddString("9");
	m_cbFontSizes.SetItemData(i, 9);
	i = m_cbFontSizes.AddString("10");
	m_cbFontSizes.SetItemData(i, 10);
	i = m_cbFontSizes.AddString("12");
	m_cbFontSizes.SetItemData(i, 12);
	i = m_cbFontSizes.AddString("16");
	m_cbFontSizes.SetItemData(i, 16);
	i = m_cbFontSizes.AddString("18");
	m_cbFontSizes.SetItemData(i, 18);
	i = m_cbFontSizes.AddString("22");
	m_cbFontSizes.SetItemData(i, 22);
	m_cbFontSizes.SetCurSel(m_cbFontSizes.FindStringExact(0, "12"));

	m_cbFontNames.SetCurSel(m_cbFontNames.FindStringExact(0, "Arial"));

	

	m_bDirty = false ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgActionReport::OnOK() 
{
	OnBnClickedActionReportCheckspelling();
	UpdateCurrentRecord();
	CDialog::OnOK();
}

void CDlgActionReport::OnBnClickedActionReportBoldButton()
{
	CCustomerSatPropertyPage* page = (CCustomerSatPropertyPage*) m_sheetCustomerSat.GetActivePage();
	page->SetSelectionBold();
	if (m_wndeditFocus != NULL) m_wndeditFocus->SetFocus();
}

void CDlgActionReport::OnBnClickedActionReportItalicButton()
{
	CCustomerSatPropertyPage* page = (CCustomerSatPropertyPage*) m_sheetCustomerSat.GetActivePage();
	page->SetSelectionItalic();
	if (m_wndeditFocus != NULL) m_wndeditFocus->SetFocus();
}

void CDlgActionReport::OnBnClickedActionReportUnderlineButton()
{
	CCustomerSatPropertyPage* page = (CCustomerSatPropertyPage*) m_sheetCustomerSat.GetActivePage();
	page->SetSelectionUnderlined();
	if (m_wndeditFocus != NULL) m_wndeditFocus->SetFocus();
}

void CDlgActionReport::OnBnClickedActionReportViewprintreportButton()
{
	OnBnClickedActionReportCheckspelling();
	UpdateCurrentRecord();

	ASSERT(m_iId != -1);
	ReportHelper::CustomerSatisfactionConcern(m_iId, Mode::View);
}

void CDlgActionReport::UpdateCurrentRecord()
{
	if (m_bDirty)
	{
		CSetActionReport set(&g_dbFlooring) ;
		if(m_iId != -1)
		{
			set.m_strFilter.Format("Id = '%d'", m_iId) ;
			set.Open() ;
			set.Edit() ;
		}
		else
		{
			set.m_strFilter = "Id = -1";
			set.Open() ;
			set.AddNew() ;
			set.m_OrderID = m_iOrderId ;
		}

		set.m_StoreError = m_listStoreError.GetSelection() ;
		set.m_MillError = m_listMillError.GetSelection() ;
		set.m_MeasureError = m_listMeasureError.GetSelection() ;
		set.m_InstallerError = m_listInstallerError.GetSelection() ;

		set.m_StoreErrorText = m_listStoreError.GetSelectedItemStrings();
		set.m_MillErrorText = m_listMillError.GetSelectedItemStrings();
		set.m_MeasureErrorText = m_listMeasureError.GetSelectedItemStrings();
		set.m_InstallerErrorText = m_listInstallerError.GetSelectedItemStrings();

		if (m_iId != -1)
		{
			// editing record
			set.m_LastEditedDate = CGlobals::GetCurrentSystemTime();
			set.m_LastEditedBy = ((CFlooringApp*) AfxGetApp())->GetEmployeeID();
		}
		else
		{
			// adding new record
			COleDateTime datetime = CGlobals::GetCurrentSystemTime();;
			set.m_ReportDate = datetime;
			set.m_LastEditedDate = datetime;
			set.m_EnteredBy = ((CFlooringApp*) AfxGetApp())->GetEmployeeID();
			set.m_LastEditedBy = ((CFlooringApp*) AfxGetApp())->GetEmployeeID();
		}
		
		// used to id the new record
		int iUID = set.m_LastEditedBy;
		COleDateTime dt = set.m_LastEditedDate;

		CSetEmployees setEmp(&g_dbFlooring);
		setEmp.m_strFilter.Format("ID = %d", iUID);
		setEmp.Open();

		CString strName = "Unknown";

		if (!setEmp.IsEOF())
		{
			strName.Format(_T("Entered By: %s %s on %s"), setEmp.m_FirstName, setEmp.m_LastName, dt.Format("%m/%d/%Y %I:%M:%S %p"));
		}

		CString strRTFText = "";

		if ( m_ppageAction->GetCombinedRTF(strRTFText, strName))
		{
            set.m_ActionRequired = strRTFText;
		}
		
		if ( m_ppageCause->GetCombinedRTF(strRTFText, strName) )
		{
            set.m_Cause = strRTFText;
		}
		
		if ( m_ppageNature->GetCombinedRTF(strRTFText, strName) )
		{
            set.m_Nature = strRTFText;
		}
		
		set.Update() ;
		m_bDirty = false;

		set.m_strFilter.Format("LastEditedBy = %d AND LastEditedDate = '%s'", iUID, dt.Format("%m/%d/%Y %I:%M:%S %p"));
		set.Requery();
		ASSERT(set.GetRecordCount() == 1);

		m_iId = set.m_ID;
		
        set.Close() ;

	}
}
void CDlgActionReport::OnBnClickedActionReportCheckspelling()
{
	SSCE_S16 rv = 0;
	
	rv = CheckSpelling(m_ppageNature);
	if (rv > 0) rv = CheckSpelling(m_ppageAction);
	if (rv > 0) rv = CheckSpelling(m_ppageCause);

	m_sheetCustomerSat.SetActivePage(m_ppageNature);
}

SSCE_S16 CDlgActionReport::CheckSpelling(CCustomerSatPropertyPage* pPage)
{
	SSCE_S16 rv = 0;
	m_sheetCustomerSat.SetActivePage(pPage);
	CAutoRichEditCtrl* pEdit = NULL;
	CSentrySpellDlg sentry(this);
	sentry.SetKey(0xB1B9C65E);

	if (pPage->ExistingHasText())
	{
		pEdit = pPage->GetExistingRichEdit();
		
		rv = sentry.Check(*pEdit);
		if ((rv < 0) && (rv != SSCE_CANCEL_ERR)) 
		{
			CString msg;
			msg.Format(_T("Error: Spell check returned error code %hd"), rv);
			MessageBox(msg, "Error");
			return rv;
		}	
	}

	if (pPage->AdditionalHasText())
	{
		pEdit = pPage->GetAdditionalRichEdit();
		rv = sentry.Check(*pEdit);
		if ((rv < 0) && (rv != SSCE_CANCEL_ERR)) 
		{
			CString msg;
			msg.Format(_T("Error: Spell check returned error code %hd"), rv);
			MessageBox(msg, "Error");
			return rv;
		}	
	}

	return rv;
}


void CDlgActionReport::OnCbnSelchangeActionreportFontsizeCombo()
{
	CCustomerSatPropertyPage* page = (CCustomerSatPropertyPage*) m_sheetCustomerSat.GetActivePage();
	CString strTemp;
	m_cbFontSizes.GetLBText(m_cbFontSizes.GetCurSel(), strTemp);
	page->SetSelectionFontSize(atoi(strTemp));
	if (m_wndeditFocus != NULL) m_wndeditFocus->SetFocus();
}

void CDlgActionReport::OnCbnSelchangeActionreportFontcombo()
{
	CCustomerSatPropertyPage* page = (CCustomerSatPropertyPage*) m_sheetCustomerSat.GetActivePage();
	CString strTemp;
	m_cbFontNames.GetLBText(m_cbFontNames.GetCurSel(), strTemp);
	page->SetSelectionFontName(strTemp);
	if (m_wndeditFocus != NULL) m_wndeditFocus->SetFocus();
}
