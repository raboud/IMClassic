/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once


// CDlgInsuranceQuestion dialog

class CDlgInsuranceQuestion : public CDialog
{
	DECLARE_DYNAMIC(CDlgInsuranceQuestion)

public:
	CDlgInsuranceQuestion(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgInsuranceQuestion();

	bool GetCancelPayroll();
	void SetMessage(CString strMessage);

// Dialog Data
	enum { IDD = IDD_INSURANCE_QUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	bool m_bCancelPayroll;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedCancelPayrollButton();
	CString m_strMessage;
};

inline bool CDlgInsuranceQuestion::GetCancelPayroll()
{
	return m_bCancelPayroll;
}

inline void CDlgInsuranceQuestion::SetMessage(CString strMessage)
{
	m_strMessage = strMessage;
}
