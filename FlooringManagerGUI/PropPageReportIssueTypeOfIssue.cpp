/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// PropPageReportIssueTypeOfIssue.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "PropPageReportIssueTypeOfIssue.h"
#include ".\proppagereportissuetypeofissue.h"
#include "PropSheetReportIssueWizard.h"


// CPropPageReportIssueTypeOfIssue dialog

IMPLEMENT_DYNAMIC(CPropPageReportIssueTypeOfIssue, CPropertyPage)
CPropPageReportIssueTypeOfIssue::CPropPageReportIssueTypeOfIssue()
	: CPropertyPage(CPropPageReportIssueTypeOfIssue::IDD)
{
}

CPropPageReportIssueTypeOfIssue::~CPropPageReportIssueTypeOfIssue()
{
}

void CPropPageReportIssueTypeOfIssue::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboIssueType);
}


BEGIN_MESSAGE_MAP(CPropPageReportIssueTypeOfIssue, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CPropPageReportIssueTypeOfIssue message handlers

BOOL CPropPageReportIssueTypeOfIssue::OnSetActive()
{
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);

	CString strTemp = "";
	int iIndex = m_comboIssueType.GetCurSel();
	if (iIndex > -1)
	{
		//m_comboIssueType.GetLBText(m_comboIssueType.GetCurSel(), strTemp);
		//if (strTemp.GetLength() > 0)
		//{
			pParent->SetWizardButtons(PSWIZB_NEXT);
		//}
	}
	else
	{
		// disable both Back / Next buttons
		pParent->SetWizardButtons(0);
	}

	return CPropertyPage::OnSetActive();
}

void CPropPageReportIssueTypeOfIssue::OnCbnSelchangeCombo1()
{
	CPropSheetReportIssueWizard* pParent = (CPropSheetReportIssueWizard*)GetParent();
    ASSERT_KINDOF(CPropSheetReportIssueWizard, pParent);

	// enable the Next button
    pParent->SetWizardButtons(PSWIZB_NEXT);
}

CString CPropPageReportIssueTypeOfIssue::GetInfo()
{
	CString strInfo = "** INVALID **";
	int iIndex = m_comboIssueType.GetCurSel();
	if (iIndex > -1)
	{
		m_comboIssueType.GetLBText(iIndex, strInfo);
	}

	return strInfo;
}