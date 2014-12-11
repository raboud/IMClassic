/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

#include "atlcomtime.h"
#include "floatedit.h"
#include "afxwin.h"
#include "ComboBoxVendors.h"


// CDlgCheckNew dialog

class CDlgCheckNew : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckNew)

public:
	CDlgCheckNew(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCheckNew();

// Dialog Data
	enum { IDD = IDD_CHECK_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

protected:
	virtual void OnOK();
	void SetVendorCombo(int iVendorID);

	CFloatEdit m_fleditAmount;
	COleDateTime m_CheckDate;
	CString m_strCheckNumber;
	CString m_strCheckAmount;

	COleDateTime m_OriginalCheckDate;
	CString m_strOriginalCheckNumber;
	CString m_strOriginalCheckAmount;
	long m_lOriginalVendorID;

public:
	virtual BOOL OnInitDialog();
protected:
	int m_iCheckID;
public:
	void SetCheckID(int iCheckID) {m_iCheckID = iCheckID ;} ;
	int GetCheckID() {return m_iCheckID ;} ;
	CEdit m_editNumber;
	afx_msg void OnEnChangeCheckNumber();
	afx_msg void OnEnChangeCheckAmount();
	CButton m_butOK;
	void CheckDirty(void);
	afx_msg void OnDtnDatetimechangeCheckDate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupCheckDate(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBoxVendors m_comboVendor;
	afx_msg void OnCbnSelchangeCheckVendor();
};
