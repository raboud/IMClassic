/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgCalledList.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "DlgCalledList.h"

#include "SetOrders.h"
#include "SetCustomer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalledList dialog


CDlgCalledList::CDlgCalledList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalledList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCalledList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iOrderId = -1 ;
}


void CDlgCalledList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalledList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalledList, CDialog)
	//{{AFX_MSG_MAP(CDlgCalledList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalledList message handlers

BOOL CDlgCalledList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_gridCalled.AttachGrid(this, IDC_CALLED_LIST) ;
	m_gridCalled.SetOrderId(m_iOrderId) ;
	try
	{
		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter.Format("OrderId = '%d'", m_iOrderId) ;
		setOrders.Open() ;
		CSetCustomer setCustomer(&g_dbFlooring) ;
		setCustomer.m_strFilter.Format("CustomerID = '%d'", setOrders.m_CustomerID) ;
		setCustomer.Open() ;
		
		CString strTemp ;
		strTemp.Format("Call List - PO: %s - %s, %s", setOrders.m_PurchaseOrderNumber, setCustomer.m_LastName, setCustomer.m_FirstName) ;
		SetWindowText(strTemp) ;
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


void CDlgCalledList::SetOrderId(int iOrderID)
{
	m_iOrderId = iOrderID ;
}
