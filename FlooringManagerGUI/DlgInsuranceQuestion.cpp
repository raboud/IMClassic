// DlgInsuranceQuestion.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgInsuranceQuestion.h"
#include ".\dlginsurancequestion.h"


// CDlgInsuranceQuestion dialog

IMPLEMENT_DYNAMIC(CDlgInsuranceQuestion, CDialog)
CDlgInsuranceQuestion::CDlgInsuranceQuestion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInsuranceQuestion::IDD, pParent)
	, m_strMessage(_T(""))
{
		m_bCancelPayroll = false;
}

CDlgInsuranceQuestion::~CDlgInsuranceQuestion()
{
}

void CDlgInsuranceQuestion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INSURANCE_QUESTION_MESSAGE, m_strMessage);
}


BEGIN_MESSAGE_MAP(CDlgInsuranceQuestion, CDialog)
	ON_BN_CLICKED(IDC_CANCEL_PAYROLL_BUTTON, OnBnClickedCancelPayrollButton)
END_MESSAGE_MAP()


// CDlgInsuranceQuestion message handlers

BOOL CDlgInsuranceQuestion::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInsuranceQuestion::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

void CDlgInsuranceQuestion::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}

void CDlgInsuranceQuestion::OnBnClickedCancelPayrollButton()
{
	// TODO: Add your control notification handler code here
	m_bCancelPayroll = true;
	OnCancel();
}
