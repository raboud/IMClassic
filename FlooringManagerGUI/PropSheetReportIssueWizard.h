/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

#include "PropPageReportIssueTypeOfIssue.h"
#include "PropPageReportIssueStorePONumber.h"
#include "PropPageReportIssueDescription.h"
#include "PropPageReportIssueSummary.h"

// CPropSheetReportIssueWizard

class CPropSheetReportIssueWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSheetReportIssueWizard)

public:
	CPropSheetReportIssueWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropSheetReportIssueWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPropSheetReportIssueWizard();

	CPropPageReportIssueTypeOfIssue m_propTypeOfIssue;
	CPropPageReportIssueStorePONumber m_propStorePONumber;
	CPropPageReportIssueDescription m_propDescription;
	CPropPageReportIssueSummary m_propSummary;

	CString GetSubmitInfo();
	int SubmitIssue();
	void SendIssueEmailSMTP(CString strSubject, CString strBody, int iUserID);

protected:
	DECLARE_MESSAGE_MAP()
};


