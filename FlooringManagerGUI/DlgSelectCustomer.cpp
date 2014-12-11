// DlgSelectCustomer.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSelectCustomer.h"
#include "SetOrders.h"
#include "SetCustomer.h"
#include "SetOrderSOMerchandiseDetails.h"


// CDlgSelectCustomer dialog

IMPLEMENT_DYNAMIC(CDlgSelectCustomer, CDialog)
CDlgSelectCustomer::CDlgSelectCustomer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectCustomer::IDD, pParent)
{
	m_strPONumber = _T("");
	m_strSONumber = _T("");
	m_strStoreNumber = _T("");
	m_iCustomerID = -1;
	m_iOrderID = -1;
}

CDlgSelectCustomer::~CDlgSelectCustomer()
{
}

void CDlgSelectCustomer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PO_NUMBER, m_stStaticText);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER, m_comboCustomers);
}


BEGIN_MESSAGE_MAP(CDlgSelectCustomer, CDialog)
END_MESSAGE_MAP()


// CDlgSelectCustomer message handlers

BOOL CDlgSelectCustomer::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strTemp;
	if (m_strPONumber.Compare(_T("")) != 0)
	{
		m_stStaticText.SetWindowText("P.O. Number: " + m_strPONumber);
	}
	else
	{
		m_stStaticText.SetWindowText("S.O. Number: " + m_strSONumber);
	}

	FillComboBox();

	m_comboCustomers.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectCustomer::FillComboBox()
{
	ASSERT(IsWindow(m_comboCustomers.m_hWnd));

	if (m_strPONumber.Compare(_T("")) != 0)
	{
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter.Format("[PurchaseOrderNumber] = '%s'", m_strPONumber);
		setOrders.Open();

		CSetCustomer setCustomer(&g_dbFlooring);
		setCustomer.m_strFilter = "CustomerID = -1";
		setCustomer.Open();

		CString strLine;
		while (!setOrders.IsEOF())
		{
			setCustomer.m_strFilter.Format("CustomerID = %d", setOrders.m_CustomerID);
			setCustomer.Requery();

			double dAmount = 0.00;
			if (setOrders.m_BilledAmount.GetLength() > 0)
			{
				dAmount = (double)atof(setOrders.m_BilledAmount);
			}

			strLine.Format("%s, %s - P.O. Amount $%0.2f", setCustomer.m_LastName, setCustomer.m_FirstName, dAmount);
			int iIndex = m_comboCustomers.AddString(strLine);
			m_comboCustomers.SetItemData(iIndex, setOrders.m_OrderID);
			setOrders.MoveNext();
		}
		setOrders.Close();
		setCustomer.Close();
	}
	else
	{
		CSetOrderSOMerchandiseDetails setSO(&g_dbFlooring);
		setSO.m_strFilter.Format("[SONumber] = '%s'", m_strSONumber);
		setSO.Open();

		CSetCustomer setCustomer(&g_dbFlooring);
		setCustomer.m_strFilter = "CustomerID = -1";
		setCustomer.Open();

		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter = "[PurchaseOrderNumber] = -1";
		setOrders.Open();

		CString strLine;
		while (!setSO.IsEOF())
		{
			setOrders.m_strFilter.Format("[OrderID] = '%d'", setSO.m_OrderID);
			setOrders.Requery();

			setCustomer.m_strFilter.Format("CustomerID = %d", setOrders.m_CustomerID);
			setCustomer.Requery();

			strLine.Format("%s, %s - %s", setCustomer.m_LastName, setCustomer.m_FirstName, setSO.m_Description);
			int iIndex = m_comboCustomers.AddString(strLine);
			m_comboCustomers.SetItemData(iIndex, setOrders.m_OrderID);
			setSO.MoveNext();
		}
		setSO.Close();
		setOrders.Close();
		setCustomer.Close();
	}

}
int CDlgSelectCustomer::SetSONumber(CString strSONumber, CString strStoreNumber)
{
	m_strSONumber = strSONumber;
	m_strStoreNumber = strStoreNumber;

	CSetOrderSOMerchandiseDetails setSO(&g_dbFlooring);
	setSO.m_strFilter.Format("[SONumber] = '%s' AND [Deleted] = 0", m_strSONumber);
	setSO.Open();


	int iNumMatches = 0;
	while (!setSO.IsEOF())
	{
		iNumMatches++;
		m_iOrderID = setSO.m_OrderID;
		setSO.MoveNext();
	}

	if (iNumMatches == 1)
	{
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter.Format("OrderID = %d", m_iOrderID);
		setOrders.Open();
		m_iCustomerID = setOrders.m_CustomerID;
		m_strStoreNumber = CGlobals::StoreNumberFromOrderID(m_iOrderID);
	}
	else
	{
		m_iCustomerID = -1;
		m_iOrderID = -1;
	}

	setSO.Close();

	return iNumMatches;
}

int CDlgSelectCustomer::SetPONumber(CString strPONumber, CString strStoreNumber)
{
	m_strPONumber = strPONumber;
	m_strStoreNumber = strStoreNumber ;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter.Format("[PurchaseOrderNumber] = '%s' AND [Deleted] = 0 AND [StoreID] = %d", m_strPONumber, CGlobals::StoreIDFromStoreNumber(m_strStoreNumber)) ;
	setOrders.Open() ;

	int iNumMatches = 0;
	while (!setOrders.IsEOF())
	{
		iNumMatches++;
		m_iCustomerID = setOrders.m_CustomerID;
		m_iOrderID = setOrders.m_OrderID;
		setOrders.MoveNext();
	}

	if (iNumMatches != 1)
	{
		m_iCustomerID = -1;
		m_iOrderID = -1;
	}

	setOrders.Close();

	return iNumMatches;
}

void CDlgSelectCustomer::OnOK()
{
	m_iOrderID = m_comboCustomers.GetItemData(m_comboCustomers.GetCurSel());
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = %d", m_iOrderID);
	setOrders.Open();
	m_iCustomerID = setOrders.m_CustomerID;
	m_strStoreNumber = CGlobals::StoreNumberFromOrderID(m_iOrderID);

	CDialog::OnOK();
}

