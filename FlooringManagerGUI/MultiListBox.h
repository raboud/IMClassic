/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_MULTILISTBOX_H__B65E033E_B8BB_42BE_875B_FDFA33C3A237__INCLUDED_)
#define AFX_MULTILISTBOX_H__B65E033E_B8BB_42BE_875B_FDFA33C3A237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiListBox window

class CMultiListBox : public CListBox
{
// Construction
public:
	CMultiListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetSelection();
	CString GetSelectedItemStrings();
	void SetSelection(int iSelection);
	virtual ~CMultiListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILISTBOX_H__B65E033E_B8BB_42BE_875B_FDFA33C3A237__INCLUDED_)
