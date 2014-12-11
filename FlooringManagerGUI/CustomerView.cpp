/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CustomerView.cpp : implementation of the CCustomerView class
//

#include "stdafx.h"
#include "Flooring.h"

#include "SetCustomer.h"
#include "FlooringDoc.h"
#include "CustomerView.h"
#include "DialogPo.h"
#include "SetViewOrderSOMerchandiseDetails.h"
#include "DlgFind.h"
#include "DlgSelectCustomer.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomerView

IMPLEMENT_DYNCREATE(CCustomerView, CFRecordView)

BEGIN_MESSAGE_MAP(CCustomerView, CFRecordView)
	//{{AFX_MSG_MAP(CCustomerView)
	ON_BN_CLICKED(IDC_CUSTOMER_FIND, OnCustomerFind)
	ON_BN_CLICKED(IDC_CUSTOMER_NEW, OnCustomerNew)
	ON_BN_CLICKED(IDC_CUSTOMER_EDIT, OnCustomerEdit)
	ON_EN_CHANGE(IDC_FIRST_NAME, OnChangeFirstName)
	ON_EN_CHANGE(IDC_LAST_NAME, OnChangeLastName)
	ON_COMMAND(ID_FIND_BY_PO, OnFindByPo)
	ON_COMMAND(ID_FIND_BY_ORDER_NUMBER, OnFindByOrderNumber)
	ON_COMMAND(ID_FIND_BY_CUSTOMER_NUMBER, OnFindByCustomerNumber)
	ON_WM_CTLCOLOR()
	ON_REGISTERED_MESSAGE( wm_CUSTOMER_SELECT, OnCustomerSelected)
	ON_REGISTERED_MESSAGE( wm_PO_SELECT, OnPOSelected)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_COMMAND(ID_FIND_BY_SPECIAL_ORDER, OnFindBySpecialOrder)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFRecordView::OnFilePrintPreview)
	ON_COMMAND(ID_FIND_BY_HOME_PHONENUMBER, OnFindByHomePhonenumber)
	ON_COMMAND(ID_FIND_BY_WORK_PHONENUMBER, OnFindByWorkPhonenumber)
	ON_COMMAND(ID_FIND_BYSEARCHINGNOTES, OnFindBysearchingnotes)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomerView construction/destruction

CCustomerView::CCustomerView()
	: CFRecordView(CCustomerView::IDD)
{
	//{{AFX_DATA_INIT(CCustomerView)
	m_pSet = NULL;
	m_pSetOrders = NULL;
	//}}AFX_DATA_INIT
	m_bEditing = false ;
	m_pBrush = NULL ;
//	m_lCustomerID = -1;

}

CCustomerView::~CCustomerView()
{
	delete m_pSet ;
	delete m_pSetOrders;
	if (m_pBrush)
	{
		delete m_pBrush ;
	}
}

void CCustomerView::DoDataExchange(CDataExchange* pDX)
{
	CFRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomerView)
	DDX_Control(pDX, IDC_WARRENTY, m_statWarrenty);
	DDX_Control(pDX, IDC_SCHEDULED, m_statScheduled);
	DDX_Control(pDX, IDC_PAID, m_statPaid);
	DDX_Control(pDX, IDC_INV_PAID, m_InvAndPaid);
	DDX_Control(pDX, IDC_INVOICED, m_statInvoiced);
	DDX_Control(pDX, IDC_CANCELLED, m_statCancelled);
	DDX_Control(pDX, IDC_FIRST_NAME, m_editFirstName);
	DDX_Control(pDX, IDC_LAST_NAME, m_editLastName);
	DDX_Control(pDX, IDC_EMAIL_ADDRESS, m_editEmailAddress);
	//}}AFX_DATA_MAP

	if (m_bEditing)
	{
		DDX_Control(pDX, IDC_ZIP, m_editZip);
		DDX_Control(pDX, IDC_HOME_PHONE, m_editHomePhone);
		DDX_Control(pDX, IDC_WORK, m_editWorkPhone);
		DDX_Control(pDX, IDC_MOBILE_PHONE, m_editMobilePhone);
		DDX_FieldText(pDX, IDC_ADDRESS, m_pSet->m_Address, m_pSet);
		DDX_FieldText(pDX, IDC_CITY, m_pSet->m_City, m_pSet);
		DDX_FieldText(pDX, IDC_FIRST_NAME, m_pSet->m_FirstName, m_pSet);
		DDX_FieldText(pDX, IDC_HOME_PHONE, m_pSet->m_PhoneNumber, m_pSet);
		DDX_FieldText(pDX, IDC_LAST_NAME, m_pSet->m_LastName, m_pSet);
		DDX_FieldText(pDX, IDC_WORK, m_pSet->m_WorkNumber, m_pSet);
		DDX_FieldText(pDX, IDC_ZIP, m_pSet->m_ZipCode, m_pSet);
		DDX_FieldText(pDX, IDC_STATE, m_pSet->m_State, m_pSet);
		DDV_MaxChars(pDX, m_pSet->m_State, 2);
		DDX_FieldText(pDX, IDC_DIRECTIONS, m_pSet->m_Directions, m_pSet) ;
		DDX_FieldText(pDX, IDC_MOBILE_PHONE, m_pSet->m_MobileNumber, m_pSet);
		DDX_FieldText(pDX, IDC_EMAIL_ADDRESS, m_pSet->m_EmailAddress, m_pSet);
		DDV_MaxChars(pDX, m_pSet->m_EmailAddress, 255);
	}
}

BOOL CCustomerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFRecordView::PreCreateWindow(cs);
}

void CCustomerView::OnInitialUpdate()
{
	m_pSet = new CSetCustomer(&g_dbFlooring);
	m_pSet->m_strFilter = "CustomerID = -1";
	m_pSet->Open();

	m_pSetOrders = new CSetOrders(&g_dbFlooring);
	m_pSetOrders->m_strFilter = "OrderID = -1";
	m_pSetOrders->Open();

	m_bInsertable = true ;

	CFRecordView::OnInitialUpdate();

	CString strTemp ;

	this->ShowCustomerData(SW_HIDE) ;
	this->EnableCustomerData(false) ;

	m_editHomePhone.SetMask(_T("(###)###-####")) ;
	m_editHomePhone.SetPromptSymbol(' ');
//	m_editHomePhone.m_ctrl = this;
	
	m_editWorkPhone.SetMask(_T("(###)###-#### Ext. #####")) ;
	m_editWorkPhone.SetPromptSymbol(' ');
//	m_editWorkPhone.m_ctrl = this;

	m_editMobilePhone.SetMask(_T("(###)###-####")) ;
	m_editMobilePhone.SetPromptSymbol(' ');

	m_editZip.SetMask(_T("#####-####")) ;
//	m_editZip.m_ctrl = this;

	m_gridCustomer.SetCustomerSet(m_pSet) ;
	m_gridCustomer.AttachGrid(this, IDC_CUSTOMER_PICKLIST) ;

	m_gridPoPickList.AttachGrid(this, IDC_PO_PICKLIST) ;
	CEdit* pNotes = (CEdit*) GetDlgItem(IDC_DIRECTIONS) ;
	pNotes->SetLimitText(CGlobals::iMAX_CUSTOMER_DIRECTIONS) ;

	m_editEmailAddress.SetLimitText(255);

	EnableControl(IDC_CUSTOMER_NEW, true);
	EnableControl(IDC_CUSTOMER_FIND, true) ;
	m_editLastName.SetFocus() ;

	GetParentFrame()->SetTitle("Customer Records");

}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView printing

BOOL CCustomerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCustomerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCustomerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView diagnostics

#ifdef _DEBUG
void CCustomerView::AssertValid() const
{
	CFRecordView::AssertValid();
}

void CCustomerView::Dump(CDumpContext& dc) const
{
	CFRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomerView database support
CRecordset* CCustomerView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CCustomerView message handlers

void CCustomerView::OnCustomerFind() 
{
	BuildFilterString() ;
	m_pSet->Requery() ;

	CustomerFind() ;
}

void CCustomerView::EnableCustomerData(bool bState)
{
	EnableControl (IDC_ADDRESS, bState);
	EnableControl (IDC_CITY, bState);
	EnableControl (IDC_WORK, bState);
	EnableControl (IDC_HOME_PHONE, bState);
	EnableControl (IDC_ZIP, bState);
	EnableControl (IDC_STATE, bState);
	EnableControl (IDC_DIRECTIONS, bState) ;
	EnableControl (IDC_MOBILE_PHONE, bState);
	EnableControl (IDC_EMAIL_ADDRESS, bState);
}

void CCustomerView::ShowCustomerData(int nCmdShow)
{
	ShowControl (IDC_ADDRESS, nCmdShow);
	ShowControl (IDC_CITY, nCmdShow);
	ShowControl (IDC_WORK, nCmdShow);
	ShowControl (IDC_HOME_PHONE, nCmdShow);
	ShowControl (IDC_ZIP, nCmdShow);
	ShowControl (IDC_STATE, nCmdShow);
	ShowControl (IDC_MOBILE_PHONE, nCmdShow);
	ShowControl (IDC_EMAIL_ADDRESS, nCmdShow);

	ShowControl (IDC_STATIC_ADDRESS, nCmdShow);
	ShowControl (IDC_STATIC_CITY, nCmdShow);
	ShowControl (IDC_STATIC_WORK, nCmdShow);
	ShowControl (IDC_STATIC_HOME, nCmdShow);
	ShowControl (IDC_STATIC_ZIP, nCmdShow);
	ShowControl (IDC_STATIC_STATE, nCmdShow);
	ShowControl (IDC_CUSTOMER_EDIT, nCmdShow);
	ShowControl (IDC_STATIC_MOBILE, nCmdShow);
	ShowControl (IDC_STATIC_EMAIL, nCmdShow);
}

void CCustomerView::BuildFilterString(bool bDoPartial)
{
	struct
	{
		UINT uID ;
		char* pcFieldName ;
	} auField[] = {	{IDC_FIRST_NAME, "FirstName"},
					{IDC_LAST_NAME, "LastName"} } ;

	int iNUMBER_FIELDS = sizeof(auField) / sizeof(auField[0]) ;
	
	m_pSet->m_strFilter = "" ;
	m_pSet->Close() ;
	
	for (int iIndex = 0; iIndex < iNUMBER_FIELDS; iIndex++)
	{
		CString strData ;

		this->GetDlgItemText(auField[iIndex].uID, strData) ;
		if (strData != "")
		{
			if (m_pSet->m_strFilter != "")
			{
				m_pSet->m_strFilter += " AND " ;
			}
			if (bDoPartial)
			{

				m_pSet->m_strFilter += "[" ;
				m_pSet->m_strFilter += auField[iIndex].pcFieldName ;
				m_pSet->m_strFilter += "] LIKE '" ;
				m_pSet->m_strFilter += strData ;
				m_pSet->m_strFilter += "%'" ;

			}
			else
			{
				m_pSet->m_strFilter += "[" ;
				m_pSet->m_strFilter += auField[iIndex].pcFieldName ;
				m_pSet->m_strFilter += "] = '" ;
				m_pSet->m_strFilter += strData ;
				m_pSet->m_strFilter += "'" ;
			}
		}
		m_pSet->m_strSort = "LastName, FirstName" ;
	}
	m_pSet->Open() ;
}

void CCustomerView::OnCancel() 
{
	CFRecordView::OnCancel();
	EnableCustomerData(false) ;
	ShowCustomerData(SW_HIDE) ;
	m_editLastName.SetWindowText("") ;
	m_editFirstName.SetWindowText("") ;
	EnableControl(IDC_CUSTOMER_FIND, true) ;
	EnableControl(IDC_CUSTOMER_NEW, true);

	EnableControl(IDC_DIRECTIONS, false) ;
	EnableControl(IDC_DIRECTIONS_LABLE, false) ;
	ShowControl(IDC_DIRECTIONS, SW_HIDE) ;
	ShowControl(IDC_DIRECTIONS_LABLE, SW_HIDE) ;

	EnableControl(IDOK, false) ;
	EnableControl(IDCANCEL, false) ;
	ShowControl(IDOK, SW_HIDE) ;
	ShowControl(IDCANCEL, SW_HIDE) ;

	m_bEditing = false ;

}

void CCustomerView::OnOK() 
{
	this->m_bEditing = true ;

	UpdateData(true) ;
	if ((m_pSet->m_Address == "") &&
		(m_pSet->m_City == "") &&
		(m_pSet->m_State == ""))
	{
		UINT uResponse = MessageBox("Click Yes to save record with no address. Click No discard the changes. Click Cancel to continue editing.",
			"Empty fields", MB_YESNOCANCEL) ;
		if (uResponse == IDCANCEL)
		{
			m_bEditing = false ;

			EnableControl(IDC_CUSTOMER_FIND, true) ;
			EnableControl(IDC_CUSTOMER_NEW, true);

			EnableControl(IDC_DIRECTIONS, false) ;
			EnableControl(IDC_DIRECTIONS_LABLE, false) ;

			EnableControl(IDOK, false) ;
			EnableControl(IDCANCEL, false) ;
			ShowControl(IDOK, SW_HIDE) ;
			ShowControl(IDCANCEL, SW_HIDE) ;
			return ;
		}
		else if (uResponse == IDNO)
		{
			OnCancel() ;
			return ;
		}
	}

	if ((m_pSet->m_Address == "") &&(m_pSet->m_City == ""))
	{
		m_pSet->m_strFilter.Format("[FirstName] = '%s' AND [LastName] = '%s' AND [Address] IS NULL AND [City] IS NULL AND [State] = '%s' AND [ZipCode] = '%s' AND [PhoneNumber] = '%s' AND [WorkNumber] = '%s'", 
			m_pSet->m_FirstName,
			m_pSet->m_LastName, 
			m_pSet->m_State, 
			m_pSet->m_ZipCode,
			m_pSet->m_PhoneNumber,
			m_pSet->m_WorkNumber);

	}
	else if (m_pSet->m_Address == "")
	{
		m_pSet->m_strFilter.Format("[FirstName] = '%s' AND [LastName] = '%s' AND [Address] IS NULL AND [City] = '%s' AND [State] = '%s' AND [ZipCode] = '%s' AND [PhoneNumber] = '%s' AND [WorkNumber] = '%s'", 
			m_pSet->m_FirstName,
			m_pSet->m_LastName, 
			m_pSet->m_City,
			m_pSet->m_State,
			m_pSet->m_ZipCode,
			m_pSet->m_PhoneNumber,
			m_pSet->m_WorkNumber);
	}
	else if (m_pSet->m_City == "")
	{
		m_pSet->m_strFilter.Format("[FirstName] = '%s' AND [LastName] = '%s' AND [Address] = '%s' AND [City] IS NULL AND [State] = '%s' AND [ZipCode] = '%s' AND [PhoneNumber] = '%s' AND [WorkNumber] = '%s'", 
			m_pSet->m_FirstName,
			m_pSet->m_LastName, 
			m_pSet->m_Address, 
			m_pSet->m_State,
			m_pSet->m_ZipCode,
			m_pSet->m_PhoneNumber,
			m_pSet->m_WorkNumber);
	}
	else
	{
		m_pSet->m_strFilter.Format("[FirstName] = '%s' AND [LastName] = '%s' AND [Address] = '%s' AND [City] = '%s' AND [State] = '%s' AND [ZipCode] = '%s' AND [PhoneNumber] = '%s' AND [WorkNumber] = '%s'", 
			m_pSet->m_FirstName,
			m_pSet->m_LastName, 
			m_pSet->m_Address, 
			m_pSet->m_City,
			m_pSet->m_State,
			m_pSet->m_ZipCode,
			m_pSet->m_PhoneNumber,
			m_pSet->m_WorkNumber);
	}
	m_pSet->Update() ;
	m_pSet->Requery() ;
	ShowCustomerData(SW_SHOW) ;
	EnableCustomerData(false) ;
	m_gridCustomer.ShowWindow(SW_HIDE) ;
	m_bEditing = true ;
	UpdateData(false) ;

	m_bEditing = false ;

	EnableControl(IDC_CUSTOMER_FIND, true) ;
	EnableControl(IDC_CUSTOMER_NEW, true);

	EnableControl(IDC_DIRECTIONS, false) ;
	EnableControl(IDC_DIRECTIONS_LABLE, false) ;

	EnableControl(IDOK, false) ;
	EnableControl(IDCANCEL, false) ;
	ShowControl(IDOK, SW_HIDE) ;
	ShowControl(IDCANCEL, SW_HIDE) ;
	OnCustomerSelected(0,0) ;
}

void CCustomerView::OnCustomerNew() 
{
	BuildFilterString(false) ;
	if (m_pSet->m_strFilter != "")
	{
		m_pSet->Requery() ;
		if (!m_pSet->IsEOF())
		{
			if (MessageBox("Customer Name is already in database. Click Yes to continue creating a NEW record.", "Duplicate Name", MB_YESNO) == IDNO)
			{
				return ;
			}
		}
	}

	m_pSet->AddNew() ;
	CString strName ;
	m_editLastName.GetWindowText(strName) ;
	m_pSet->m_LastName = strName ;
	m_editFirstName.GetWindowText(strName) ;
	m_pSet->m_FirstName = strName ;
	m_pSet->m_State = "GA" ;
	EnableCustomerEdit() ;

	m_gridPoPickList.ShowWindow(SW_HIDE) ;
}

void CCustomerView::OnCustomerEdit() 
{
	m_pSet->Edit() ;
	EnableCustomerEdit() ;

	EnableControl(IDC_DIRECTIONS, true) ;
	EnableControl(IDC_DIRECTIONS_LABLE, true) ;
	ShowControl(IDC_DIRECTIONS, SW_SHOW) ;
	ShowControl(IDC_DIRECTIONS_LABLE, SW_SHOW) ;

	m_gridPoPickList.Update(m_pSet->m_CustomerID) ;
	m_gridPoPickList.ShowWindow(SW_HIDE) ;

	CWnd* pNext = GetDlgItem(IDC_ADDRESS) ;
	pNext->SetFocus() ;
}

LRESULT CCustomerView::OnCustomerSelected(WPARAM /* wParam */, LPARAM /* lParam */)
{
	// Display the Record
	ShowCustomerData(SW_SHOW) ;
	ShowControl(IDC_DIRECTIONS, SW_SHOW) ;
	ShowControl(IDC_DIRECTIONS_LABLE, SW_SHOW) ;
	EnableCustomerData(false) ;
	m_gridCustomer.ShowWindow(SW_HIDE) ;
	m_bEditing = true ;
	UpdateData(false) ;
	m_bEditing = false ;
	EnableControl(IDC_CUSTOMER_EDIT, true) ;
	m_gridPoPickList.ShowWindow(SW_SHOW) ;
	m_gridPoPickList.Update(m_pSet->m_CustomerID) ;
	m_gridPoPickList.RedrawAll() ;
	return true ;
}


LRESULT CCustomerView::OnPOSelected(WPARAM /* wParam */, LPARAM /* lParam */)
{
/*	// Display the Record
	ShowCustomerData(SW_SHOW) ;
	EnableCustomerData(false) ;
	m_gridCustomer.ShowWindow(SW_HIDE) ;
	m_bEditing = true ;
	UpdateData(false) ;
	ShowControl(IDC_CUSTOMER_EDIT, SW_SHOW) ;
	EnableControl(IDC_CUSTOMER_EDIT, true) ;
	m_gridPoPickList.ShowWindow(SW_SHOW) ;
	m_gridPoPickList.Update(m_pSet->m_CustomerID) ;
*/	return true ;
}


void CCustomerView::EnableCustomerEdit()
{
	ShowCustomerData(SW_SHOW) ;
	EnableCustomerData(true) ;
	m_gridCustomer.ShowWindow(SW_HIDE) ;
	m_bEditing = true ;
	UpdateData(false) ;

	EnableControl(IDOK, true) ;
	EnableControl(IDCANCEL, true) ;
	ShowControl(IDOK, SW_SHOW) ;
	ShowControl(IDCANCEL, SW_SHOW) ;

	EnableControl(IDC_CUSTOMER_NEW, false);
	EnableControl(IDC_CUSTOMER_FIND, false) ;

	EnableControl(IDC_DIRECTIONS, true) ;
	EnableControl(IDC_DIRECTIONS_LABLE, true) ;
	ShowControl(IDC_DIRECTIONS, SW_SHOW);
	ShowControl(IDC_DIRECTIONS_LABLE, SW_SHOW) ;
	EnableControl(IDC_CUSTOMER_EDIT, false) ;
	ShowControl(IDC_CUSTOMER_EDIT, SW_HIDE) ;
}

void CCustomerView::CloseView()
{

}

void CCustomerView::OnChangeFirstName() 
{
	if (!m_bEditing)
	{
		OnCustomerFind() ;
		m_editFirstName.SetFocus() ;
	}
}

void CCustomerView::OnChangeLastName() 
{
	if (!m_bEditing)
	{
		OnCustomerFind() ;	
		m_editLastName.SetFocus() ;
	}
}

void CCustomerView::OnFindByPo() 
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_PO, this) ;
	bool bContinue = true;
	if (dlg.DoModal() == IDOK)
	{
		CDlgSelectCustomer dlgCustomer;
		int iNumRecords = dlgCustomer.SetPONumber(dlg.m_strNumber, dlg.m_strStoreNumber);

		if ( iNumRecords > 1 )
		{
			if ( dlgCustomer.DoModal() != IDOK )
			{
				bContinue = false;
			}
		}
		else if ( iNumRecords == 0 )
		{
			//CString strStoreNumber = CGlobals::POtoStoreNumber(dlg.m_strNumber);
			
			ASSERT(dlg.m_strStoreNumber.GetLength() == 4);
			ASSERT(dlg.m_strNumber.GetLength() == 8);

			if (CGlobals::SPNUpdatePO(dlg.m_strStoreNumber, dlg.m_strNumber))
			{
				iNumRecords = dlgCustomer.SetPONumber(dlg.m_strNumber, dlg.m_strStoreNumber);
				if ( iNumRecords > 1 )
				{
					if ( dlgCustomer.DoModal() != IDOK )
					{
						bContinue = false;
					}
				}
				else if (iNumRecords == 0)
				{
					bContinue = false ;
				}
			}
			else
			{
				MessageBox("No matching records found!", "Record Not Found") ;
				bContinue = false;
			}
		}

		if (bContinue)
		{
			int iCustomerID = dlgCustomer.GetCustomerID();
			int iOrderID = dlgCustomer.GetOrderID();

			m_pSet->m_strFilter.Format("[CustomerID] = '%d'", iCustomerID) ;
			m_pSet->Requery() ;
			OnCustomerSelected(0,0) ;

			CDlgPo dlgPo ;
			dlgPo.SetOrderId(iOrderID) ;

			if (dlgPo.DoModal() == IDOK)
			{
				m_gridPoPickList.Update(iCustomerID) ;
			}
		}
	}
}


void CCustomerView::FindByOrderNumber(long lOrderID)
{
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("[OrderID] = %d", lOrderID) ;
	setOrders.Open() ;
	if (!setOrders.IsEOF())
	{
		m_pSet->m_strFilter.Format("[CustomerID] = '%d'", setOrders.m_CustomerID) ;
		m_pSet->Requery() ;
		OnCustomerSelected(0,0) ;

		CDlgPo dlgPo ;
		dlgPo.SetOrderId(setOrders.m_OrderID) ;

		if (dlgPo.DoModal() == IDOK)
		{
			m_gridPoPickList.Update(setOrders.m_CustomerID) ;
		}
	}
	else
	{
		MessageBox("No matching records found!", "Record Not Found") ;
	}
	setOrders.Close() ;
}

void CCustomerView::OnFindByOrderNumber() 
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_ORDERID, this) ;
	if (dlg.DoModal() == IDOK)
	{
		long lOrderID = atol(dlg.m_strNumber);
		FindByOrderNumber(lOrderID);
	}
}

void CCustomerView::OnFindByCustomerNumber() 
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_CUSTOMERID, this) ;
	dlg.SetCaption("Find by Customer Number") ;
	if (dlg.DoModal() == IDOK)
	{
		FindByCustomerNumber(dlg.m_strNumber);	
	}
}

void CCustomerView::FindByCustomerNumber(CString strNumber)
{
	m_pSet->m_strFilter.Format("[CustomerID] = '%s'", strNumber) ;
	m_pSet->Requery() ;
	if (!m_pSet->IsEOF())
	{
		//m_bEditing = true ;
		//m_editFirstName.SetWindowText(m_pSet->m_FirstName) ;
		//m_editLastName.SetWindowText(m_pSet->m_LastName) ;
		//m_bEditing = false ;
		//CustomerFind() ;
		OnCustomerSelected(0,0) ;
	}
	else
	{
		MessageBox("No matching records found!", "Record Not Found") ;
	}
}

void CCustomerView::CustomerFind()
{
	m_gridPoPickList.ShowWindow(SW_HIDE) ;

//	int iCount = 0 ;
//	while (!)
//	{
//		iCount++ ;
//		m_pSet->MoveNext() ;
//	}

	if (m_pSet->IsEOF()) 
	{
		// New Record let them start editing
		OnCustomerNew() ;
		m_bEditing = false ;

		ShowControl(IDC_DIRECTIONS, SW_SHOW) ;
		ShowControl(IDC_DIRECTIONS_LABLE, SW_SHOW) ;
	}
/*
	else if (iCount == 1)
	{
		// Display the Record
		OnCustomerSelected(0,0) ;		
		ShowCustomerData(SW_SHOW) ;
		EnableCustomerData(false) ;
		m_gridCustomer.ShowWindow(SW_HIDE) ;
		m_bEditing = true ;
		UpdateData(false) ;
		m_bEditing = false ;

	}
*/
	else
	{
		ShowCustomerData(SW_HIDE) ;
		EnableCustomerData(false) ;
		if (m_pSet->m_strFilter != "")
		{
			// Pick list
			ShowCustomerData(SW_HIDE) ;
			EnableCustomerData(false) ;
			m_gridCustomer.ShowWindow(SW_SHOW) ;
			m_gridCustomer.Update() ;
			m_gridCustomer.RedrawAll() ;
			m_gridCustomer.Invalidate() ;
		}
		else
		{
			m_gridCustomer.ShowWindow(SW_HIDE) ;
		}
		m_bEditing = false ;
		ShowControl(IDC_DIRECTIONS, SW_HIDE) ;
		ShowControl(IDC_DIRECTIONS_LABLE, SW_HIDE) ;
		EnableControl(IDOK, false) ;
		EnableControl(IDCANCEL, false) ;
		ShowControl(IDOK, SW_HIDE) ;
		ShowControl(IDCANCEL, SW_HIDE) ;
	}
}

HBRUSH CCustomerView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFRecordView::OnCtlColor(pDC, pWnd, nCtlColor);
	struct 
	{
		COLORREF	color ;
		CPOPickList::EnColorMode	enMode ;
		int			id ;
	} asuControls[] = 
	{
		{CGlobals::COLOR_SCHEDULED,	enMODE_SCHEDULED,	IDC_SCHEDULED},
		{CGlobals::COLOR_INV_PAID,	enMODE_INV_PAID,	IDC_INV_PAID},
		{CGlobals::COLOR_INVOICED,	enMODE_INVOICED,	IDC_INVOICED},
		{CGlobals::COLOR_PAID,		enMODE_PAID,		IDC_PAID},	
		{CGlobals::COLOR_CANCELED,	enMODE_CANCELED,	IDC_CANCELLED},
		{CGlobals::COLOR_WAR_COMP,	enMODE_WAR_COMP,	IDC_WAR_COMP},
		{CGlobals::COLOR_WARRENTY,	enMODE_WARRENTY,	IDC_WARRENTY}	
	} ;

	for (int iIndex = 0; iIndex < sizeof(asuControls) / sizeof(asuControls[0]); iIndex++)
	{
		if (pWnd->GetDlgCtrlID() == asuControls[iIndex].id )
		{
			if (asuControls[iIndex].enMode == CPOPickList::EnColorMode_BACK)
			{
				pDC->SetBkColor(asuControls[iIndex].color) ;
				if (m_pBrush != NULL)
				{
					delete m_pBrush ;
				}
				m_pBrush = new CBrush (asuControls[iIndex].color) ;
				pDC->SetBkMode(OPAQUE) ;
				return (HBRUSH) *m_pBrush ;
			}
			else
			{
				pDC->SetTextColor(asuControls[iIndex].color) ;
			}
			break ;

		}
	}
	return hbr;
}

void CCustomerView::OnFindBySpecialOrder() 
{
	int iCustomerID = -1;
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_SO, this) ;
	dlg.SetCaption("Find by Special Order Number") ;

	if (dlg.DoModal() == IDOK)
	{
		int iOrderID = CGlobals::OrderIDFromSONumberAndStoreNumber(dlg.m_strNumber, dlg.m_strStoreNumber);
		if (iOrderID != -1)
		{
			CSetOrders setOrders(&g_dbFlooring) ;
			setOrders.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
			setOrders.Open() ;

			int iNumMatches = 0;
			while (!setOrders.IsEOF())
			{
				iNumMatches++;
				setOrders.MoveNext();
			}

			if (iNumMatches == 1)
			{
				iCustomerID = setOrders.m_CustomerID;
			}
			setOrders.Close();

			m_pSet->m_strFilter.Format("[CustomerID] = '%d'", iCustomerID) ;
			m_pSet->Requery() ;
			OnCustomerSelected(0,0) ;

			CDlgPo dlgPo ;
			dlgPo.SetOrderId(iOrderID) ;

			if (dlgPo.DoModal() == IDOK)
			{
				m_gridPoPickList.Update(iCustomerID) ;
			}
		}
		else
		{
			MessageBox("No matching records found!", "Record Not Found") ;
		}
	}
}

void CCustomerView::OnFindByHomePhonenumber()
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_HOME_PHONE, this) ;
	dlg.SetCaption("Find by Home Phone Number") ;
	dlg.SetMask(_T("(###)###-####"));
	if (dlg.DoModal() == IDOK)
	{
		CString strNumber = dlg.m_strNumber;
		m_pSet->m_strFilter.Format("[PhoneNumber] = '%s'", strNumber) ;
		m_pSet->Requery() ;
		if (!m_pSet->IsEOF())
		{
			m_bEditing = true ;
			m_editFirstName.SetWindowText(m_pSet->m_FirstName) ;
			m_editLastName.SetWindowText(m_pSet->m_LastName) ;
			m_bEditing = false ;
			CustomerFind() ;
		}
		else
		{
			MessageBox("No matching records found!", "Record Not Found") ;
		}
	}
}

void CCustomerView::OnFindByWorkPhonenumber()
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_WORK_PHONE, this) ;
	dlg.SetCaption("Find by Work Phone Number") ;
	dlg.SetMask(_T("(###)###-####"));
	if (dlg.DoModal() == IDOK)
	{
		CString strNumber = dlg.m_strNumber;
		m_pSet->m_strFilter.Format("[WorkNumber] LIKE '%s%%'", strNumber) ;
		m_pSet->Requery() ;
		if (!m_pSet->IsEOF())
		{
			m_bEditing = true ;
			m_editFirstName.SetWindowText(m_pSet->m_FirstName) ;
			m_editLastName.SetWindowText(m_pSet->m_LastName) ;
			m_bEditing = false ;
			CustomerFind() ;
		}
		else
		{
			MessageBox("No matching records found!", "Record Not Found") ;
		}
	}
}

void CCustomerView::OnFindBysearchingnotes()
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_TEXT, this) ;
	dlg.SetCaption("Find by Searching Notes") ;
	dlg.SetMaxChars(255);
	dlg.SetMask("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
	if (dlg.DoModal() == IDOK)
	{
		CString strSearchData = dlg.m_strNumber.Trim();   // not really a number in this case...
		m_pSetOrders->m_strFilter.Format("Notes LIKE '%%%s%%'", strSearchData) ;
		m_pSetOrders->Requery() ;
		if (!m_pSetOrders->IsEOF())
		{
			m_bEditing = true ;
			m_pSet->m_strFilter.Format("[CustomerID] = %d", m_pSetOrders->m_CustomerID) ;
			m_pSet->Requery() ;
			/*m_editFirstName.SetWindowText(m_pSet->m_FirstName) ;
			m_editLastName.SetWindowText(m_pSet->m_LastName) ;
			m_bEditing = false ;
			CustomerFind() ;*/

			OnCustomerSelected(0,0) ;

			CDlgPo dlgPo ;
			dlgPo.SetOrderId(m_pSetOrders->m_OrderID) ;

			if (dlgPo.DoModal() == IDOK)
			{
				m_gridPoPickList.Update(m_pSetOrders->m_CustomerID) ;
			}
		}
		else
		{
			MessageBox("No matching records found!", "Record Not Found") ;
		}
	}
}
