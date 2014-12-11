/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_COMBOBOXMATERIALTYPE_H__EDA70504_DFAF_490C_8A37_6CF3917BE676__INCLUDED_)
#define AFX_COMBOBOXMATERIALTYPE_H__EDA70504_DFAF_490C_8A37_6CF3917BE676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxMaterialType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBoxMaterialType window

class CComboBoxMaterialType : public CComboBox
{
// Construction
public:
	CComboBoxMaterialType();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxMaterialType)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateChoices(long lStoreTypeId, long lMarketID, CString strShortName = "", bool bShowActiveOnly = false);
	virtual ~CComboBoxMaterialType();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxMaterialType)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXMATERIALTYPE_H__EDA70504_DFAF_490C_8A37_6CF3917BE676__INCLUDED_)
