/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "ComboBoxStore.h"


// CPropPageReportIssueStorePONumber dialog

class CPropPageReportIssueStorePONumber : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageReportIssueStorePONumber)

public:
	CPropPageReportIssueStorePONumber();
	virtual ~CPropPageReportIssueStorePONumber();
	CString GetInfo();

// Dialog Data
	enum { IDD = IDD_TROUBLEREPORT_2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void Validate();
	bool ValidPONumber();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	CButton m_btnPOYes;
	CComboBoxStore m_comboStoreNumber;
	CEdit m_editPONumber;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioNo();
	afx_msg void OnBnClickedRadioYes();
	afx_msg void OnEnChangeEditTroubleReportPonumber();
};
