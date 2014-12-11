/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// FindCustomers.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "FindCustomers.h"


// CFindCustomers

IMPLEMENT_DYNCREATE(CFindCustomers, CFormView)

CFindCustomers::CFindCustomers()
	: CFormView(CFindCustomers::IDD)
{
	m_pSet = NULL;
}

CFindCustomers::~CFindCustomers()
{
	delete m_pSet ;
}

void CFindCustomers::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LAST_NAME, m_editLastName);
	DDX_Control(pDX, IDC_FIRST_NAME, m_editFirstName);
}

BEGIN_MESSAGE_MAP(CFindCustomers, CFormView)
	ON_BN_CLICKED(IDC_BTNRESET, &CFindCustomers::OnBnClickedBtnreset)
	ON_EN_CHANGE(IDC_FIRST_NAME, &CFindCustomers::OnEnChangeFirstName)
	ON_EN_CHANGE(IDC_LAST_NAME, &CFindCustomers::OnEnChangeLastName)
END_MESSAGE_MAP()


// CFindCustomers diagnostics

#ifdef _DEBUG
void CFindCustomers::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFindCustomers::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFindCustomers message handlers

void CFindCustomers::OnBnClickedBtnreset()
{
	m_editLastName.SetWindowText("");
	m_editFirstName.SetWindowText("");
}

void CFindCustomers::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_pSet = new CSetCustomer(&g_dbFlooring);
	m_pSet->m_strFilter = "CustomerID = -1";
	m_pSet->Open();

	m_gridCustomer.SetCustomerSet(m_pSet) ;
	m_gridCustomer.AttachGrid(this, IDC_CUSTOMER_PICKLIST) ;

}

void CFindCustomers::OnEnChangeFirstName()
{
	//OnCustomerFind() ;
	m_editFirstName.SetFocus() ;
}

void CFindCustomers::OnEnChangeLastName()
{
	//OnCustomerFind() ;
	m_editLastName.SetFocus() ;
}

void CFindCustomers::UpdateCustomerFilter()
{
	/*BuildFilterString() ;
	m_pSet->Requery() ;*/
}