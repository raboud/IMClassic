// DlgPassword.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgPassword.h"
#include ".\dlgpassword.h"
#include "SetSettings.h"


// CDlgPassword dialog

IMPLEMENT_DYNAMIC(CDlgPassword, CDialog)
CDlgPassword::CDlgPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPassword::IDD, pParent)
	, m_strPassword(_T(""))
{
}

CDlgPassword::~CDlgPassword()
{
}

void CDlgPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CDlgPassword, CDialog)
END_MESSAGE_MAP()


// CDlgPassword message handlers

BOOL CDlgPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowText(m_strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPassword::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	UpdateData();

	CDialog::OnOK();
}

bool CDlgPassword::ValidatePassword()
{
	bool bValid = false;

	CSetSettings settings(&g_dbFlooring);
	CString strPassword = settings.GetSetting("FlooringPassword");
	if (strPassword == m_strPassword)
	{
		bValid = true;
	}

	return bValid;
}

CString CDlgPassword::GetPassword()
{
	return m_strPassword;
}

void CDlgPassword::SetTitle(CString strTitle)
{
	m_strTitle = strTitle;
}