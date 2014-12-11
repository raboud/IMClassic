/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DLGFIND_H__C090A263_7BAA_48C7_9C0E_C891B3C872E8__INCLUDED_)
#define AFX_DLGFIND_H__C090A263_7BAA_48C7_9C0E_C891B3C872E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFind.h : header file
//

#include "CFIMaskedEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFind dialog

class CDlgFind : public CDialog
{
// Construction
public:

	enum EnFIND_TYPE { EnFIND_TYPE_ORDERID, EnFIND_TYPE_CUSTOMERID, EnFIND_TYPE_PO, EnFIND_TYPE_SO, EnFIND_TYPE_TEXT, EnFIND_TYPE_HOME_PHONE, EnFIND_TYPE_WORK_PHONE } ;

	void SetCaption(CString strCaption);
	void SetMask(CString strMask);
	void SetMaxChars(int iMaxChars);
	CDlgFind(EnFIND_TYPE enType, CWnd* pParent = NULL);   // standard constructor

	CComboBox m_cbStoreNumber;
	CButton m_btnOK;
	CStatic m_stStoreText;

// Dialog Data
	//{{AFX_DATA(CDlgFind)
	enum { IDD = IDD_FIND };
	CString	m_strNumber;
	CString m_strStoreNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCFIMaskedEdit m_editMaskedNumber;
	CString m_strTitle;
	CString m_strMask;
	int m_iMaxChars;

	EnFIND_TYPE m_enType;

	void UpdateStoreNumberCombo(CString strPONumber);
	bool ValidatePO();
	
	// Generated message map functions
	//{{AFX_MSG(CDlgFind)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnCbnSelchangeStorecombo();
	afx_msg void OnEnKillFocusMaskedNumber(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	virtual void OnOK();
};

inline void CDlgFind::SetMaxChars(int iMaxChars)
{
	m_iMaxChars = iMaxChars;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIND_H__C090A263_7BAA_48C7_9C0E_C891B3C872E8__INCLUDED_)

