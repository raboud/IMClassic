// DlgAttachedDocsList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgAttachedDocsList.h"

// CDlgAttachedDocsList dialog

IMPLEMENT_DYNAMIC(CDlgAttachedDocsList, CDialog)

CDlgAttachedDocsList::CDlgAttachedDocsList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttachedDocsList::IDD, pParent)
	, m_CustomerName(_T(""))
	, m_CustomerAddress(_T(""))
{
	m_iCustomerID = -1;
}

CDlgAttachedDocsList::~CDlgAttachedDocsList()
{
}

void CDlgAttachedDocsList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_CUSTOMERNAME, m_CustomerName);
	DDX_Text(pDX, IDC_TEXT_CUSTOMER_ADDRESS, m_CustomerAddress);
}


BEGIN_MESSAGE_MAP(CDlgAttachedDocsList, CDialog)
END_MESSAGE_MAP()


// CDlgAttachedDocsList message handlers

BOOL CDlgAttachedDocsList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
