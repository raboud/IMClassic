/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DialogInvoicing.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DialogInvoicing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogInvoicing dialog


CDialogInvoicing::CDialogInvoicing(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogInvoicing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogInvoicing)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iInvoice = 0 ;
	m_fInvoiced = 0.0 ;
}


void CDialogInvoicing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogInvoicing)
	DDX_Control(pDX, IDC_INVOICEDATE, m_dateInvoice);
	DDX_Control(pDX, IDC_INVOICED, m_Invoiced);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogInvoicing, CDialog)
	//{{AFX_MSG_MAP(CDialogInvoicing)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_INVOICEDATE, OnTimeChangeInvoicedate)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE( wm_INVOICED, OnInvoiced)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogInvoicing message handlers

BOOL CDialogInvoicing::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_gridInvoice.AttachGrid(this, IDC_INVOICE_GRID) ;

	COleDateTime timeInvoice ; 
	m_dateInvoice.GetTime(timeInvoice) ;
	m_gridInvoice.SetBilledDate(timeInvoice) ;

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogInvoicing::OnTimeChangeInvoicedate(NMHDR* /* pNMHDR */, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	COleDateTime timeInvoice ;
	m_dateInvoice.GetTime(timeInvoice) ;
	m_gridInvoice.SetBilledDate(timeInvoice) ;
	*pResult = 0;
}

LRESULT CDialogInvoicing::OnInvoiced(WPARAM wParam, LPARAM lParam)
{
	m_iInvoice = wParam ;
	m_fInvoiced = lParam / 100. ;
	CString strInvoiced ;
	strInvoiced.Format("%d - $%10.2f", m_iInvoice, m_fInvoiced) ;
	m_Invoiced.SetWindowText(strInvoiced) ;

	if (m_iInvoice > 0)
	{
		GetDlgItem(IDOK)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
	return TRUE ;
}

void CDialogInvoicing::OnOK() 
{
	int iResponse = m_gridInvoice.ConfirmSendCompleteServiceDocs();
	if (( iResponse == IDYES) || (iResponse == -1))
	{
		m_gridInvoice.UpdateRecordSet() ;	
		CDialog::OnOK();
		DestroyWindow() ;
	}
}

void CDialogInvoicing::OnCancel() 
{
	if (m_iInvoice)
	{
		if (IDNO == MessageBox("Changes have been made.  Are you sure you want to quit", "Data Changed", MB_YESNO))
		{
			return  ;
		}
	}
	CDialog::OnCancel();
	DestroyWindow() ;
}

void CDialogInvoicing::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this ;
	CDialog::PostNcDestroy();
}

void CDialogInvoicing::SetVendorID(int iVendorID)
{
	m_gridInvoice.SetVendorID(iVendorID);
}