// DlgTransferPO.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgTransferPO.h"
#include "DlgFind.h"

// CDlgTransferPO dialog

IMPLEMENT_DYNAMIC(CDlgTransferPO, CDialog)
CDlgTransferPO::CDlgTransferPO(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransferPO::IDD, pParent)
	, m_strMessage(_T(""))
	, m_strCustName(_T(""))
	, m_lCustID(0)
	, m_bEditing(false)
{
}

CDlgTransferPO::~CDlgTransferPO()
{
	delete m_pSet ;
}

void CDlgTransferPO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TRANSFER_DIALOG_MESSAGE, m_strMessage);
	DDX_Control(pDX, IDC_TRANSFERPO_CUSTLNAME, m_editLastName);
	DDX_Control(pDX, IDC_TRANSFERPO_CUSTFNAME, m_editFirstName);
}


BEGIN_MESSAGE_MAP(CDlgTransferPO, CDialog)
	ON_EN_CHANGE(IDC_TRANSFERPO_CUSTLNAME, OnEnChangeTransferpoCustlname)
	ON_EN_CHANGE(IDC_TRANSFERPO_CUSTFNAME, OnEnChangeTransferpoCustfname)
	ON_BN_CLICKED(IDC_TRANSFERPO_FINDBUTTON, OnBnClickedTransferpoFindbutton)
	ON_REGISTERED_MESSAGE( wm_CUSTOMER_SELECT, OnCustomerSelected)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgTransferPO message handlers

BOOL CDlgTransferPO::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pSet = new CSetCustomer(&g_dbFlooring);
	m_pSet->Open();

	m_gridCustomer.SetCustomerSet(m_pSet) ;
	m_gridCustomer.AttachGrid(this, IDC_TRANSFERPO_CUST_PICK_LIST) ;

	CString strPOList = "";
	POSITION pos = m_PoList.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_PoList.GetNext(pos);
		if (strPOList.GetLength() > 0)
		{
			strPOList += ", ";
		}
		strPOList += CGlobals::POFromOrderID(iOrderID);
	}

	if (m_PoList.GetCount() > 1)
	{
		m_strMessage.Format("Transferring MULTIPLE POs %s from %s (ID = %d)\n\nSelect the customer to receive this PO:", strPOList, m_strCustName, m_lCustID);
	}
	else
	{
		m_strMessage.Format("Transferring PO %s from %s (ID = %d)\n\nSelect the customer to receive this PO:", strPOList, m_strCustName, m_lCustID);
	}

	UpdateData(FALSE);

	EnableControl(IDOK, false);

	m_editLastName.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransferPO::OnOK()
{
	long lNewCustomerID = m_pSet->m_CustomerID;
	
	POSITION pos = m_PoList.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_PoList.GetNext(pos);
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter.Format("[OrderID] = %d", iOrderID);
		setOrders.Open();

		if (!setOrders.IsEOF())
		{
			long lCurrentCustID = setOrders.m_CustomerID;
			if (lCurrentCustID == m_lCustID)
			{
				setOrders.Edit();
				setOrders.m_CustomerID = lNewCustomerID;
				setOrders.Update();
			}
			else
			{
				MessageBox("The current Customer ID does not match the the customer ID in the database.\n(Please contact the system admin immediately)", "Error!");
			}
		}
		else
		{
			CString strTemp;
			strTemp.Format("There was an error locating Order ID %d in the database.", iOrderID);
			MessageBox(strTemp, "Error!");
			return;
		}

		setOrders.Close();
	}
    
	CDialog::OnOK();
}

void CDlgTransferPO::OnEnChangeTransferpoCustlname()
{
	if (!m_bEditing)
	{
		OnCustomerFind() ;
		m_editLastName.SetFocus() ;
	}
}

void CDlgTransferPO::OnEnChangeTransferpoCustfname()
{
	if (!m_bEditing)
	{
		OnCustomerFind() ;
		m_editFirstName.SetFocus() ;
	}
}


void CDlgTransferPO::OnBnClickedTransferpoFindbutton()
{
	CDlgFind dlg(CDlgFind::EnFIND_TYPE_CUSTOMERID, this) ;
	dlg.SetCaption("Find by Customer Number") ;
	dlg.SetMaxChars(6);
	if (dlg.DoModal() == IDOK)
	{
		m_pSet->m_strFilter.Format("[CustomerID] = '%s'", dlg.m_strNumber) ;
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

void CDlgTransferPO::CustomerFind()
{
	int iCount = 0 ;
	while (!m_pSet->IsEOF())
	{
		iCount++ ;
		m_pSet->MoveNext() ;
	}

	if (iCount == 0) 
	{
		m_gridCustomer.Update();
		m_gridCustomer.Invalidate() ;
	}
	else
	{
		// Pick list
		m_gridCustomer.ShowWindow(SW_SHOW) ;
		m_gridCustomer.Update() ;
		m_gridCustomer.RedrawAll() ;
		m_gridCustomer.Invalidate() ;
		EnableControl(IDOK, false) ;
	}
}

void CDlgTransferPO::OnCustomerFind() 
{
	if ( BuildFilterString() )
	{
		m_pSet->Requery() ;
		CustomerFind() ;
	}
}

bool CDlgTransferPO::BuildFilterString(bool bDoPartial)
{
	bool bValidFilter = false;

	struct
	{
		UINT uID ;
		char* pcFieldName ;
	} auField[] = {	{IDC_TRANSFERPO_CUSTFNAME, "FirstName"},
					{IDC_TRANSFERPO_CUSTLNAME, "LastName"} } ;

	int iNUMBER_FIELDS = sizeof(auField) / sizeof(auField[0]) ;
	
	m_pSet->m_strFilter = "" ;
	m_pSet->Close() ;
	
	for (int iIndex = 0; iIndex < iNUMBER_FIELDS; iIndex++)
	{
		CString strData ;

		this->GetDlgItemText(auField[iIndex].uID, strData) ;
		if (strData != "")
		{
			bValidFilter = true;
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
	m_pSet->Open();

	return bValidFilter;
}

void CDlgTransferPO::EnableControl(UINT nID, bool bEnable) 
{
	CWnd* pwnd = GetDlgItem(nID);
	pwnd->EnableWindow(bEnable == true);
}

void CDlgTransferPO::ShowControl(UINT nID, bool bShow) 
{
	CWnd* pwnd = GetDlgItem(nID);
	if (bShow)
		pwnd->ShowWindow(SW_SHOW);
	else
		pwnd->ShowWindow(SW_HIDE);
}

LRESULT CDlgTransferPO::OnCustomerSelected(WPARAM /* wParam */, LPARAM /* lParam */)
{
	EnableControl(IDOK);
	::PostMessage(this->m_hWnd, WM_COMMAND, (WPARAM) IDOK, 0);
	return true ;
}
void CDlgTransferPO::OnBnClickedCancel()
{
	OnCancel();
}
