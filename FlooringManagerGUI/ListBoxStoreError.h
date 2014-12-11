/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_LISTBOXSTOREERROR_H__34ABC8C4_923A_45F5_B3CE_0C0F7887BFF8__INCLUDED_)
#define AFX_LISTBOXSTOREERROR_H__34ABC8C4_923A_45F5_B3CE_0C0F7887BFF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListBoxStoreError.h : header file
//
#include "MultiListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CListBoxStoreError window

class CListBoxStoreError : public CMultiListBox
{
// Construction
public:
	CListBoxStoreError();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxStoreError)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxStoreError();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxStoreError)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXSTOREERROR_H__34ABC8C4_923A_45F5_B3CE_0C0F7887BFF8__INCLUDED_)
