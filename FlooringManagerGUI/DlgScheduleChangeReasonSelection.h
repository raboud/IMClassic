/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"


// CDlgScheduleChangeReasonSelection dialog

class CDlgScheduleChangeReasonSelection : public CDialog
{
	DECLARE_DYNAMIC(CDlgScheduleChangeReasonSelection)

public:
	CDlgScheduleChangeReasonSelection(bool bIsMeasure, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgScheduleChangeReasonSelection();

// Dialog Data
	enum { IDD = IDD_SCHEDULE_REASONCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	bool m_bIsMeasure;

	CString m_strReasonCode;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboReasons;

	CString GetReasonCode();

protected:
	virtual void OnOK();
};

inline CString CDlgScheduleChangeReasonSelection::GetReasonCode()
{
	return m_strReasonCode;
}