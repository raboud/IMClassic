/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// PropPageReportIssueStorePONumber.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "PropPageReportIssueStorePONumber.h"
#include ".\proppagereportissuestoreponumber.h"
#include "PropSheetReportIssueWizard.h"


// CPropPageReportIssueStorePONumber dialog

IMPLEMENT_DYNAMIC(CPropPageReportIssueStorePONumber, CPropertyPage)
CPropPageReportIssueStorePONumber::CPropPageReportIssueStorePONumber()
	: CPropertyPage(CPropPageReportIssueStorePONumber::IDD)
{
}

CPropPageReportIssueStorePONumber::~CPropPageReportIssueStorePONumber()
{
}

void CPropPageReportIssueStorePONumber::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_YES, m_btnPOYes);
	DDX_Control(pDX, IDC_COMBO_STORENUMBER, m_comboStoreNumber);
	DDX_Control(pDX, IDC_EDIT_TROUBLE_REPORT_PONUMBER, m_editPONumber);
}


BEGIN_MESSAGE_MAP(CPropPageReportIssueStorePONumber, CPropertyPage)
	ON_BN_CLICKED(IDC_RADIO_NO, OnBnClickedRadioNo)
	ON_BN_CLICKED(IDC_RADIO_YES, OnBnClickedRadioYes)
	ON_EN_CHANGE(IDC_EDIT_TROUBLE_REPORT_PONUMBER, OnEnChangeEditTroubleReportPonumber)
END_MESSAGE_MAP()


// CPropPageReportIssueStorePONumber message handlers

BOOL CPropPageReportIssueStorePONumber::OnSetActive()
{
	
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);

	// enable Back button only
    Validate();
	return CPropertyPage::OnSetActive();
}

BOOL CPropPageReportIssueStorePONumber::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_btnPOYes.SetCheck(BST_CHECKED);

	m_editPONumber.SetLimitText(8);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropPageReportIssueStorePONumber::OnBnClickedRadioNo()
{
	// TODO: Add your control notification handler code here
	m_editPONumber.EnableWindow(FALSE);
	m_comboStoreNumber.EnableWindow(FALSE);
	Validate();
}

void CPropPageReportIssueStorePONumber::OnBnClickedRadioYes()
{
	// TODO: Add your control notification handler code here
	m_editPONumber.EnableWindow();
	m_comboStoreNumber.EnableWindow();
	Validate();
}

void CPropPageReportIssueStorePONumber::Validate()
{
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
	pParent->SetWizardButtons(PSWIZB_BACK);

	// this will validate the data and if valid, enable the Next button
	if (((CButton*)GetDlgItem(IDC_RADIO_NO))->GetCheck() == BST_CHECKED)
	{
		pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	}
	else
	{
		// "yes" must be checked then
		int iIndex = m_comboStoreNumber.GetCurSel();
		if ((iIndex > -1) && (ValidPONumber()))
		{
			pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
		}
	}
}

bool CPropPageReportIssueStorePONumber::ValidPONumber()
{
	bool bValid = false;

	CString strPONumber;
	m_editPONumber.GetWindowText(strPONumber);

	int iLength = strPONumber.GetLength();
	
	if (iLength == 8)
	{
		if (strPONumber.GetAt(2) == '4')
		{
			bValid = true;
		}
	}
	else if (iLength == 4)
	{
		CString strStoreNumber = "";
		m_comboStoreNumber.GetLBText(m_comboStoreNumber.GetCurSel(), strStoreNumber);
		if (strPONumber == strStoreNumber)
		{
			bValid = true;
		}
	}

	return bValid;
}
void CPropPageReportIssueStorePONumber::OnEnChangeEditTroubleReportPonumber()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	Validate();
}

CString CPropPageReportIssueStorePONumber::GetInfo()
{
	CString strInfo = "** INVALID **";
	if (m_btnPOYes.GetCheck() != BST_CHECKED)
	{
		strInfo = "N/A";
	}
	else
	{
        int iIndex = m_comboStoreNumber.GetCurSel();
		if (iIndex > -1)
		{
			m_comboStoreNumber.GetLBText(iIndex, strInfo);
			CString strPONumber = "";
			m_editPONumber.GetWindowText(strPONumber);
			strInfo += "/" + strPONumber;
		}
	}

	return strInfo;
}