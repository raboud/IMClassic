// DlgReportList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgReportList.h"
#include "SetOrders.h"
#include "SetCustomer.h"


// CDlgReportList dialog

IMPLEMENT_DYNAMIC(CDlgReportList, CDialog)
CDlgReportList::CDlgReportList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReportList::IDD, pParent)
{
}

CDlgReportList::~CDlgReportList()
{
}

void CDlgReportList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST_HIDDEN_RICH_EDIT, m_editHiddenRTF);
}


BEGIN_MESSAGE_MAP(CDlgReportList, CDialog)
END_MESSAGE_MAP()


// CDlgReportList message handlers

BOOL CDlgReportList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridReports.AttachGrid(this, IDC_REPORT_LIST) ;

	CAutoRichEditCtrl* pEdit = &m_editHiddenRTF;
	m_gridReports.SetRTFEdit( pEdit );

	m_gridReports.SetOrderId(m_iOrderId) ;
	try
	{
		CSetOrders setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter.Format("OrderId = '%d'", m_iOrderId) ;
		setOrders.Open() ;

		CSetCustomer setCustomer(&g_dbFlooring) ;
		setCustomer.m_strFilter.Format("CustomerID = '%d'", setOrders.m_CustomerID) ;
		setCustomer.Open() ;
		
		CString strTemp ;
		strTemp.Format("Report List - PO: %s - %s, %s", setOrders.m_PurchaseOrderNumber, setCustomer.m_LastName, setCustomer.m_FirstName) ;
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

void CDlgReportList::SetOrderId(int iOrderID)
{
	m_iOrderId = iOrderID ;
}