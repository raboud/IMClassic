/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// UGEdit.h : header file
//
#ifndef _NUMERIC_EDIT_H_
#define _NUMERIC_EDIT_H_

#include "UGEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CNumbericEdit window

class CNumericEdit : public CUGEdit
{
// Construction
public:
	CNumericEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumbericEdit)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void OnKillFocus(CWnd* pNewWnd);
	virtual ~CNumericEdit();


	// Generated message map functions
protected:
	//{{AFX_MSG(CNumbericEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
#endif // _NUMERIC_EDIT_H_