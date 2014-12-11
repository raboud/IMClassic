/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETCATAGORIES_H__C2DD0EB3_D032_4EFE_8D31_95A12E7A10E4__INCLUDED_)
#define AFX_SETCATAGORIES_H__C2DD0EB3_D032_4EFE_8D31_95A12E7A10E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCatagories.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetCatagories recordset

class CSetCatagories : public CRecordset
{
public:
	CSetCatagories(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCatagories)

// Field/Param Data
	//{{AFX_FIELD(CSetCatagories, CRecordset)
	long	m_CatId;
	CString	m_Description;
	BOOL	m_IsPadding;
	long	m_YardsPerRoll;
	long	m_SubCatId;
	long	m_UnitOfMeasureID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetCatagories)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
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

#endif // !defined(AFX_SETCATAGORIES_H__C2DD0EB3_D032_4EFE_8D31_95A12E7A10E4__INCLUDED_)
