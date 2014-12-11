/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_LISTBOXMILLERROR_H__0D27629A_CBA0_44C1_8BB4_0791B5567192__INCLUDED_)
#define AFX_LISTBOXMILLERROR_H__0D27629A_CBA0_44C1_8BB4_0791B5567192__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListBoxMillError.h : header file
//
#include "MultiListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CListBoxMillError window

class CListBoxMillError : public CMultiListBox
{
// Construction
public:
	CListBoxMillError();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxMillError)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxMillError();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxMillError)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXMILLERROR_H__0D27629A_CBA0_44C1_8BB4_0791B5567192__INCLUDED_)
