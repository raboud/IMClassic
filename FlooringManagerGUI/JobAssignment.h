/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DLGJOBASSIGNMENT_H__00A79B3B_3757_4D2E_9AEE_98DC982281E0__INCLUDED_)
#define AFX_DLGJOBASSIGNMENT_H__00A79B3B_3757_4D2E_9AEE_98DC982281E0__INCLUDED_

#include "GridJobAssignment.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JobAssignment.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgJobAssignment dialog

class CDlgJobAssignment : public CDialog
{
// Construction
public:
	CDlgJobAssignment(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgJobAssignment)
	enum { IDD = IDD_JOB_ASSIGNMENT };
	CDateTimeCtrl	m_datePicker;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgJobAssignment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGridJobAssignment m_gridJobs;

	// Generated message map functions
	//{{AFX_MSG(CDlgJobAssignment)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusDate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGJOBASSIGNMENT_H__00A79B3B_3757_4D2E_9AEE_98DC982281E0__INCLUDED_)
