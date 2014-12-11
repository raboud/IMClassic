/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_FLOATEDIT_H__FB888778_2B97_414F_9204_9FF957A78049__INCLUDED_)
#define AFX_FLOATEDIT_H__FB888778_2B97_414F_9204_9FF957A78049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FloatEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit window

class CFloatEdit : public CEdit
{
// Construction
public:
	CFloatEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloatEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	void AllowBlank(bool bBlank);
	void AllowNegative(bool bAllowNegative);
	virtual ~CFloatEdit();
	void UpdateField();
	void SetNumberDecimals(int iNumberOfDecimals);
	int GetNumberDecimals();

	// Generated message map functions
protected:
	bool m_bBlank;
	bool m_bAllowNegative;
	int m_iNumOfDecimals;
	//{{AFX_MSG(CFloatEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

inline void CFloatEdit::SetNumberDecimals(int iNumberOfDecimals)
{
	m_iNumOfDecimals = iNumberOfDecimals;
}

inline int CFloatEdit::GetNumberDecimals()
{
	return m_iNumOfDecimals;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOATEDIT_H__FB888778_2B97_414F_9204_9FF957A78049__INCLUDED_)
