// DlgPONotesList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgPONotesList.h"
#include ".\dlgponoteslist.h"
#include "SetOrders.h"
#include "SetCustomer.h"


// CDlgPONotesList dialog

IMPLEMENT_DYNAMIC(CDlgPONotesList, CDialog)
CDlgPONotesList::CDlgPONotesList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPONotesList::IDD, pParent)
{
	m_iOrderId = -1 ;
}

CDlgPONotesList::~CDlgPONotesList()
{
}

void CDlgPONotesList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPONotesList, CDialog)
END_MESSAGE_MAP()


// CDlgPONotesList message handlers

BOOL CDlgPONotesList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridPONotes.AttachGrid(this, IDC_PONOTES_LIST) ;
	m_gridPONotes.SetOrderId(m_iOrderId) ;
	try
	{
		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter.Format("OrderId = '%d'", m_iOrderId) ;
		setOrders.Open() ;
		CSetCustomer setCustomer(&g_dbFlooring) ;
		setCustomer.m_strFilter.Format("CustomerID = '%d'", setOrders.m_CustomerID) ;
		setCustomer.Open() ;
		
		CString strTemp ;
		strTemp.Format("PO Notes List - PO: %s - %s, %s", setOrders.m_PurchaseOrderNumber, setCustomer.m_LastName, setCustomer.m_FirstName) ;
		this->SetWindowText(strTemp) ;
		setOrders.Close() ;
		setCustomer.Close() ;
	}
	catch (CException *pE)
	{
		pE->Delete() ;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPONotesList::SetOrderId(int iOrderID)
{
	m_iOrderId = iOrderID ;
}
