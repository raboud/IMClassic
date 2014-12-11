/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETMATERIALTYPE_H__E6A8DB4E_3B37_4045_A284_61382432A386__INCLUDED_)
#define AFX_SETMATERIALTYPE_H__E6A8DB4E_3B37_4045_A284_61382432A386__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetMaterialType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetMaterialType recordset

class CSetMaterialType : public CRecordset
{
public:
	CSetMaterialType(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMaterialType)

// Field/Param Data
	//{{AFX_FIELD(CSetMaterialType, CRecordset)
	long	m_MaterialTypeID;
	CString	m_MaterialTypeName;
	long	m_StoreTypeID;
	double	m_TripChargeMultiplier;
	CString	m_MinimumRetail;
	double	m_CustomMultiplier;
	CString	m_MinimumCost;
	CString	m_MinimumPrice;
	double	m_CostMultiplier;
	BOOL	m_OnlyBasicToMinimum;
	BOOL	m_Valid;
	CString	m_ShortName;
	long    m_DivisionID;
	BOOL	m_Active;
	CString m_SKU;
	CString m_SKUDesc;
	CString m_HDType;
	BOOL	m_AllowMaterialStatusUpdate ;
	BOOL	m_WoodWaiver ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetMaterialType)
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

#endif // !defined(AFX_SETMATERIALTYPE_H__E6A8DB4E_3B37_4045_A284_61382432A386__INCLUDED_)
