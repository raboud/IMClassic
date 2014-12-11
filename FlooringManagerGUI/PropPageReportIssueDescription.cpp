/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// PropPageReportIssueDescription.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "PropPageReportIssueDescription.h"
#include ".\proppagereportissuedescription.h"
#include "PropSheetReportIssueWizard.h"


// CPropPageReportIssueDescription dialog

IMPLEMENT_DYNAMIC(CPropPageReportIssueDescription, CPropertyPage)
CPropPageReportIssueDescription::CPropPageReportIssueDescription()
	: CPropertyPage(CPropPageReportIssueDescription::IDD)
{
}

CPropPageReportIssueDescription::~CPropPageReportIssueDescription()
{
}

void CPropPageReportIssueDescription::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TROUBLE_REPORT_DESCRIPTION, m_editDescription);
}


BEGIN_MESSAGE_MAP(CPropPageReportIssueDescription, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_TROUBLE_REPORT_DESCRIPTION, OnEnChangeEditTroubleReportDescription)
END_MESSAGE_MAP()


// CPropPageReportIssueDescription message handlers

BOOL CPropPageReportIssueDescription::OnSetActive()
{
	Validate();

	return CPropertyPage::OnSetActive();
}

void CPropPageReportIssueDescription::OnEnChangeEditTroubleReportDescription()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	Validate();
}

CString CPropPageReportIssueDescription::GetInfo()
{
	CString strInfo = "";
	m_editDescription.GetWindowText(strInfo);

	return strInfo;
}

BOOL CPropPageReportIssueDescription::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class

	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
	int iSubmitID = pParent->SubmitIssue();

	if (iSubmitID > 0)
	{
		CString strMessage;
		strMessage.Format("Issue Submitted Successfully.  Tracking ID is %d", iSubmitID);
		MessageBox(strMessage, "Submit Issue Status");
	}
	else
	{
		MessageBox("Error!  Could not submit issue!");
	}

	return CPropertyPage::OnWizardFinish();
}

void CPropPageReportIssueDescription::Validate()
{
	CString strDescription;
	m_editDescription.GetWindowText(strDescription);
	
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);

	if (strDescription.GetLength() > 0)
	{
		pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	}
	else
	{
		pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_DISABLEDFINISH);
	}	
}

BOOL CPropPageReportIssueDescription::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);
	pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_DISABLEDFINISH);

	CWnd* pWnd = pParent->GetDlgItem(ID_WIZFINISH);
	pWnd->SetWindowText("Submit");
	//pWnd->EnableWindow(FALSE);

	m_editDescription.SetLimitText(1024);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
