/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"


// CPropPageReportIssueDescription dialog

class CPropPageReportIssueDescription : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageReportIssueDescription)

public:
	CPropPageReportIssueDescription();
	virtual ~CPropPageReportIssueDescription();
	CString GetInfo();
	
// Dialog Data
	enum { IDD = IDD_TROUBLEREPORT_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void Validate();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	afx_msg void OnEnChangeEditTroubleReportDescription();
	CEdit m_editDescription;
	virtual BOOL OnWizardFinish();
	virtual BOOL OnInitDialog();
};
