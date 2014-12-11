/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"


// CPropPageReportIssueSummary dialog

class CPropPageReportIssueSummary : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageReportIssueSummary)

public:
	CPropPageReportIssueSummary();
	virtual ~CPropPageReportIssueSummary();

// Dialog Data
	enum { IDD = IDD_TROUBLEREPORT_4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnInitDialog();
	CEdit m_editSummary;
};
