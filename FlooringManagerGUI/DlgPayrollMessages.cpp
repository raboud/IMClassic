// DlgPayrollMessages.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgPayrollMessages.h"

// CDlgPayrollMessages dialog

IMPLEMENT_DYNAMIC(CDlgPayrollMessages, CDialog)
CDlgPayrollMessages::CDlgPayrollMessages(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPayrollMessages::IDD, pParent)
{
}

CDlgPayrollMessages::~CDlgPayrollMessages()
{
}

void CDlgPayrollMessages::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPayrollMessages, CDialog)
END_MESSAGE_MAP()


// CDlgPayrollMessages message handlers

BOOL CDlgPayrollMessages::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridPayrollMessages.AttachGrid(this, IDC_PAYROLL_GRID) ;
	m_gridPayrollMessages.Update();
	m_gridPayrollMessages.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
