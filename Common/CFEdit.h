/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_CFEDIT_H__D40E1446_DC95_4BC8_9F2F_605711D0C68E__INCLUDED_)
#define AFX_CFEDIT_H__D40E1446_DC95_4BC8_9F2F_605711D0C68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFEdit.h : header file
//
#include "UGCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCFEdit window

class CCFEdit : public CEdit
{
// Construction
public:
	CCFEdit();

// Attributes
public:
	//pointer to the main class
	CUGCtrl *	m_ctrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCFEdit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCFEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCFEdit)
	virtual afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	char		m_blankChar;
	BOOL m_cancel;
	BOOL m_continueFlag;
	int  m_continueCol;
	int  m_continueRow;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFEDIT_H__D40E1446_DC95_4BC8_9F2F_605711D0C68E__INCLUDED_)
