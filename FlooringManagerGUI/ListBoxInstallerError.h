/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_LISTBOXINSTALLERERROR_H__003D2FEB_0CE4_44FC_965A_C51316A87757__INCLUDED_)
#define AFX_LISTBOXINSTALLERERROR_H__003D2FEB_0CE4_44FC_965A_C51316A87757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListBoxInstallerError.h : header file
//
#include "MultiListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CListBoxInstallerError window

class CListBoxInstallerError : public CMultiListBox
{
// Construction
public:
	CListBoxInstallerError();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxInstallerError)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxInstallerError();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxInstallerError)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXINSTALLERERROR_H__003D2FEB_0CE4_44FC_965A_C51316A87757__INCLUDED_)
