/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETMATERIAL_H__4B271726_26A9_4591_B8B0_43AA16017CFD__INCLUDED_)
#define AFX_SETMATERIAL_H__4B271726_26A9_4591_B8B0_43AA16017CFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetMaterial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetMaterial recordset

class CSetMaterial : public CRecordset
{
public:
	CSetMaterial(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMaterial)

// Field/Param Data
	//{{AFX_FIELD(CSetMaterial, CRecordset)
	long	m_UnitOfMeasureID;
	long	m_MaterialID;
	CString	m_MaterialDescription;
	CString	m_UnitPrice;
	BOOL	m_HasSONumber;
	CString	m_UnitCost;
	long	m_MaterialTypeID;
	CString	m_RetailPrice;
	BOOL	m_Has2Dimensions;
	BOOL	m_HasColor;
	BOOL	m_HasStyle;
	BOOL	m_Active;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetMaterial)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETMATERIAL_H__4B271726_26A9_4591_B8B0_43AA16017CFD__INCLUDED_)
