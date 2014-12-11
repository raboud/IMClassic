// DlgSelectPO.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSelectPO.h"
#include "SetOrderAndCustomer.h"
#include ".\dlgselectpo.h"


// CDlgSelectPO dialog

IMPLEMENT_DYNAMIC(CDlgSelectPO, CDialog)
CDlgSelectPO::CDlgSelectPO(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectPO::IDD, pParent)
{
	m_lCustomerID = -1;
	m_lOrderID = -1;
	m_lSelectedOrderID = -1;
	m_strStoreNumber = "";
}

CDlgSelectPO::~CDlgSelectPO()
{
}

void CDlgSelectPO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PO_COMBO, m_comboPO);
}


BEGIN_MESSAGE_MAP(CDlgSelectPO, CDialog)
END_MESSAGE_MAP()


// CDlgSelectPO message handlers

void CDlgSelectPO::FillPOCombo(void)
{
	ASSERT(m_lCustomerID != -1);
	int iIndex = 0;
	int iStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(m_strStoreNumber);
	m_comboPO.ResetContent();
	CSetOrderAndCustomer setOrders(&g_dbFlooring);

	setOrders.m_strFilter.Format("[OrderID] <> %d AND [CustomerID] = %d AND [Invoice] = 0 AND [Warrenty] = 0 AND [Cancelled] = 0 AND [StoreTypeID] = %d", m_lOrderID, m_lCustomerID, iStoreTypeID);

	setOrders.Open();
	while (!setOrders.IsEOF())
	{	
		iIndex = m_comboPO.AddString(setOrders.m_PurchaseOrderNumber.Trim());
		m_comboPO.SetItemData(iIndex, setOrders.m_OrderID);
		setOrders.MoveNext();
	}
	setOrders.Close();

	m_comboPO.SetCurSel(-1);
}

bool CDlgSelectPO::SetOrderID(long lOrderID)
{
	bool bOK = false;
	CSetOrderAndCustomer setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("[OrderID] = %d", lOrderID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		m_lOrderID = lOrderID;
		m_lCustomerID = setOrders.m_CustomerID;
		m_strStoreNumber = setOrders.m_StoreNumber;
		bOK = true;
	}
	setOrders.Close();

	return bOK;
}

long CDlgSelectPO::GetSelectedOrderID()
{
	return m_lSelectedOrderID;
}


void CDlgSelectPO::OnOK()
{
	m_lSelectedOrderID = m_comboPO.GetItemData(m_comboPO.GetCurSel());
	CDialog::OnOK();
}

BOOL CDlgSelectPO::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillPOCombo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
