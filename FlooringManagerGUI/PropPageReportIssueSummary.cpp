/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// PropPageReportIssueSummary.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "PropPageReportIssueSummary.h"
#include ".\proppagereportissuesummary.h"
#include "PropSheetReportIssueWizard.h"


// CPropPageReportIssueSummary dialog

IMPLEMENT_DYNAMIC(CPropPageReportIssueSummary, CPropertyPage)
CPropPageReportIssueSummary::CPropPageReportIssueSummary()
	: CPropertyPage(CPropPageReportIssueSummary::IDD)
{
}

CPropPageReportIssueSummary::~CPropPageReportIssueSummary()
{
}

void CPropPageReportIssueSummary::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TROUBLE_REPORT_SUMMARY, m_editSummary);
}


BEGIN_MESSAGE_MAP(CPropPageReportIssueSummary, CPropertyPage)
END_MESSAGE_MAP()


// CPropPageReportIssueSummary message handlers

BOOL CPropPageReportIssueSummary::OnSetActive()
{
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);

	// enable Back button only
    pParent->SetWizardButtons(PSWIZB_FINISH);
	pParent->SetFinishText("Submit");

	return CPropertyPage::OnSetActive();
}

BOOL CPropPageReportIssueSummary::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnWizardFinish();
}

BOOL CPropPageReportIssueSummary::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);

	m_editSummary.SetWindowText(pParent->GetSubmitInfo());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
