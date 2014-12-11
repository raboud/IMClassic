/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_COMBOBOXSTORE_H__260027F0_7144_45DC_89F9_BE539340C853__INCLUDED_)
#define AFX_COMBOBOXSTORE_H__260027F0_7144_45DC_89F9_BE539340C853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxStore.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBoxStore window

class CComboBoxStore : public CComboBox
{
// Construction
public:
	CComboBoxStore();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxStore)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxStore();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxStore)
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXSTORE_H__260027F0_7144_45DC_89F9_BE539340C853__INCLUDED_)
