/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_LISTBOXMEASUREERROR_H__CACB845C_05E5_4219_A4A1_B33FA42620B6__INCLUDED_)
#define AFX_LISTBOXMEASUREERROR_H__CACB845C_05E5_4219_A4A1_B33FA42620B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListBoxMeasureError.h : header file
//
#include "MultiListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CListBoxMeasureError window

class CListBoxMeasureError : public CMultiListBox
{
// Construction
public:
	CListBoxMeasureError();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxMeasureError)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxMeasureError();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxMeasureError)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXMEASUREERROR_H__CACB845C_05E5_4219_A4A1_B33FA42620B6__INCLUDED_)
