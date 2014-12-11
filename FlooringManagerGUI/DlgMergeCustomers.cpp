// DlgMergeCustomers.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgMergeCustomers.h"

// CDlgMergeCustomers dialog

IMPLEMENT_DYNAMIC(CDlgMergeCustomers, CDialog)
CDlgMergeCustomers::CDlgMergeCustomers(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMergeCustomers::IDD, pParent)
	, m_strCustomer1(_T(""))
	, m_strCustomer2(_T(""))
	, m_iCustID1(-1) 
	, m_iCustID2(-1) 
{
}

CDlgMergeCustomers::~CDlgMergeCustomers()
{
	if (m_pSetCustomers->IsOpen())
	{
		m_pSetCustomers->Close();
	}
	
	delete m_pSetCustomers;
}

void CDlgMergeCustomers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_CUST1, m_strCustomer1);
	DDX_Text(pDX, IDC_STATIC_CUST2, m_strCustomer2);
	DDX_Control(pDX, IDC_RADIO_CUST1, m_btnCust1);
	DDX_Control(pDX, IDCANCEL, m_btnCust2);
}


BEGIN_MESSAGE_MAP(CDlgMergeCustomers, CDialog)
END_MESSAGE_MAP()


// CDlgMergeCustomers message handlers

void CDlgMergeCustomers::OnOK()
{
	Merge();
    CDialog::OnOK();
}

BOOL CDlgMergeCustomers::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT(m_iCustID1 != -1);
	ASSERT(m_iCustID2 != -1);
	ASSERT(m_bCustomerIDsOK);

	m_pSetCustomers->MoveFirst();
	CString strTemp;
	strTemp.Format("%s, %s (Cust. ID = %d)\n%s\n%s, %s, %s", 
		m_pSetCustomers->m_LastName,
		m_pSetCustomers->m_FirstName,
		m_pSetCustomers->m_CustomerID,
		m_pSetCustomers->m_Address,
		m_pSetCustomers->m_City,
		m_pSetCustomers->m_State,
		m_pSetCustomers->m_ZipCode);

	m_strCustomer1 = strTemp;

	m_pSetCustomers->MoveNext();
	strTemp.Format("%s, %s (Cust. ID = %d)\n%s\n%s, %s, %s", 
		m_pSetCustomers->m_LastName,
		m_pSetCustomers->m_FirstName,
		m_pSetCustomers->m_CustomerID,
		m_pSetCustomers->m_Address,
		m_pSetCustomers->m_City,
		m_pSetCustomers->m_State,
		m_pSetCustomers->m_ZipCode);
	
	m_strCustomer2 = strTemp;

	m_btnCust1.SetCheck(BST_CHECKED);

	UpdateData(FALSE);
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgMergeCustomers::SetCustomerIDs(int iCustID1, int iCustID2)
{
	m_bCustomerIDsOK = false;

	// we set the customerIDs so that m_iCustID1 has the lower ID value, m_iCustID2 has higher ID value
	if (iCustID1 < iCustID2)
	{
        m_iCustID1 = iCustID1 ;
		m_iCustID2 = iCustID2 ;
	}
	else
	{
		m_iCustID1 = iCustID2 ;
		m_iCustID2 = iCustID1 ;
	}

	m_pSetCustomers = new CSetCustomer(&g_dbFlooring);
	m_pSetCustomers->m_strFilter.Format("CustomerID = %d OR CustomerID = %d", m_iCustID1, m_iCustID2);
	m_pSetCustomers->m_strSort = "CustomerID";
	m_pSetCustomers->Open();

	int iNumCustomers = 0;
	while (!m_pSetCustomers->IsEOF())
	{
		iNumCustomers++;
		m_pSetCustomers->MoveNext();
	}

	if (iNumCustomers == 2)
	{
		m_bCustomerIDsOK = true;
	}

	return m_bCustomerIDsOK;
	
}

void CDlgMergeCustomers::Merge()
{
	int iCustIDKeep;
	int iCustIDDelete;

	if (m_btnCust1.GetCheck())
	{
		iCustIDKeep = m_iCustID1;
		iCustIDDelete = m_iCustID2;
	}
	else
	{
		iCustIDKeep = m_iCustID2;
		iCustIDDelete = m_iCustID1;
	}

	CString strSQL;	

	strSQL.Format("UPDATE Orders SET CustomerID = %d WHERE CustomerID = %d", iCustIDKeep, iCustIDDelete);
	g_dbFlooring.ExecuteSQL(strSQL);

	strSQL.Format("DELETE Customers WHERE CustomerID = %d", iCustIDDelete);
	g_dbFlooring.ExecuteSQL(strSQL);
}