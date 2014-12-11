/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_COMBOBOXSTORETYPE_H__01EF5FCF_8D0E_49E5_AE26_657118362313__INCLUDED_)
#define AFX_COMBOBOXSTORETYPE_H__01EF5FCF_8D0E_49E5_AE26_657118362313__INCLUDED_

#include "SetStoreType.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxStoreType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBoxStoreType window

class CComboBoxStoreType : public CComboBox
{
// Construction
public:
	CComboBoxStoreType();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxStoreType)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxStoreType();

	// Generated message map functions
protected:
//	CSetStoreType m_setStoreType;
	//{{AFX_MSG(CComboBoxStoreType)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXSTORETYPE_H__01EF5FCF_8D0E_49E5_AE26_657118362313__INCLUDED_)
