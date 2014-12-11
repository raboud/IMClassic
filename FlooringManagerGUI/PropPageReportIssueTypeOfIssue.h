/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "ComboIssueTypes.h"


// CPropPageReportIssueTypeOfIssue dialog

class CPropPageReportIssueTypeOfIssue : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageReportIssueTypeOfIssue)

public:
	CPropPageReportIssueTypeOfIssue();
	virtual ~CPropPageReportIssueTypeOfIssue();
	CString GetInfo();

// Dialog Data
	enum { IDD = IDD_TROUBLEREPORT_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboIssueTypes m_comboIssueType;
	virtual BOOL OnSetActive();
	afx_msg void OnCbnSelchangeCombo1();
};
