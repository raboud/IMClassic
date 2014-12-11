// DlgSelectVendor.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSelectVendor.h"
#include ".\dlgselectvendor.h"

// CDlgSelectVendor dialog

IMPLEMENT_DYNAMIC(CDlgSelectVendor, CDialog)
CDlgSelectVendor::CDlgSelectVendor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectVendor::IDD, pParent)
	, m_iVendorID(0)
{
}

CDlgSelectVendor::~CDlgSelectVendor()
{
}

void CDlgSelectVendor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT_VENDOR_COMBO, m_comboVendor);
}


BEGIN_MESSAGE_MAP(CDlgSelectVendor, CDialog)
	ON_CBN_SELCHANGE(IDC_SELECT_VENDOR_COMBO, OnCbnSelchangeSelectVendorCombo)
END_MESSAGE_MAP()


// CDlgSelectVendor message handlers



void CDlgSelectVendor::OnOK()
{
	if (m_comboVendor.GetCurSel() != CB_ERR)
	{
		CString strTemp;
		m_comboVendor.GetLBText(m_comboVendor.GetCurSel(), strTemp);
		CDialog::OnOK();
	}
	else
	{
		MessageBox("You must select a Vendor Number") ;
	}
}

void CDlgSelectVendor::OnCbnSelchangeSelectVendorCombo()
{
	this->GetDlgItem(IDOK)->EnableWindow(m_comboVendor.GetCurSel() != CB_ERR) ;
	m_iVendorID = m_comboVendor.GetSelectedVendorID();
	m_strVendorDescription = m_comboVendor.GetSelectedVendorDescription();
	m_strVendorNumber = m_comboVendor.GetSelectedVendorNumber();
}

BOOL CDlgSelectVendor::OnInitDialog()
{
	CDialog::OnInitDialog();

	// if only one vendor, automatically select it and send message to press OK button...
	if (m_comboVendor.GetCount() == 1)
	{
		m_comboVendor.SetCurSel(0);
		OnCbnSelchangeSelectVendorCombo();
		::PostMessage(this->m_hWnd, WM_COMMAND, (WPARAM) IDOK, 0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
