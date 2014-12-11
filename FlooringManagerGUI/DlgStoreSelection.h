/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DLGSTORESELECTION_H__850DE099_E2AC_4439_B1BB_891CC12F9B53__INCLUDED_)
#define AFX_DLGSTORESELECTION_H__850DE099_E2AC_4439_B1BB_891CC12F9B53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStoreSelection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStoreSelection dialog

class CDlgStoreSelection : public CDialog
{
// Construction
public:
	CString GetStoreNumber();
	CDlgStoreSelection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStoreSelection)
	enum { IDD = IDD_STORE_SELECTION };
	CComboBox	m_cbStoreSelection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStoreSelection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strStoreNumber ;

	// Generated message map functions
	//{{AFX_MSG(CDlgStoreSelection)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// Allow for limiting list of stores
	void SetStoreList(CString strStores);
	void SetCurrentStoreNumber(CString strCurrentStoreNumber);
protected:
	// List of filtered stores
	CString m_strStores;
	CString m_strCurrentStoreNumber;
	bool m_bLimited;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTORESELECTION_H__850DE099_E2AC_4439_B1BB_891CC12F9B53__INCLUDED_)
