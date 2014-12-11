/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_CFRICHEDIT_H__3540C3B6_93B1_438A_93AC_D7195D00D66A__INCLUDED_)
#define AFX_CFRICHEDIT_H__3540C3B6_93B1_438A_93AC_D7195D00D66A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFRichEdit.h : header file
//
#include "AutoRichEditCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCFRichEdit window

class CCFRichEdit : public CAutoRichEditCtrl
{
// Construction
public:
	CCFRichEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCFRichEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCFRichEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCFRichEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	bool m_bPopUpDisplayed;

public:
	afx_msg void OnEnChange();
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnMsgfilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFRICHEDIT_H__3540C3B6_93B1_438A_93AC_D7195D00D66A__INCLUDED_)
