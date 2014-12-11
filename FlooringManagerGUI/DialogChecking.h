/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once
// DialogChecking.h : header file
//

#include "GridChecking.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogChecking dialog

class CDialogChecking : public CDialog
{
// Construction
public:
	CDialogChecking(int iCheckID, CWnd* pParent = NULL);   // standard constructor
	LRESULT OnInvoiced(WPARAM wParam, LPARAM lParam);

// Dialog Data
	//{{AFX_DATA(CDialogChecking)
	enum { IDD = IDD_CHECK };
	CStatic	m_Paid ;
	CStatic m_statDifference;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogChecking)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	double m_fPaid ;
	double m_fCheckAmount ;
	int m_iPaid ;
	int m_iCheckID ;
	CGridChecking m_gridCheck ;

	// Generated message map functions
	//{{AFX_MSG(CDialogChecking)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
