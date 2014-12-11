/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETSTORETYPE_H__1DE2A910_6939_4EFC_BFC0_FA9337A4220C__INCLUDED_)
#define AFX_SETSTORETYPE_H__1DE2A910_6939_4EFC_BFC0_FA9337A4220C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetStoreType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetStoreType recordset

class CSetStoreType : public CRecordset
{
public:
	CSetStoreType(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetStoreType)

// Field/Param Data
	//{{AFX_FIELD(CSetStoreType, CRecordset)
	long	m_StoreTypeID;
	CString	m_StoreTypeName;
	CString	m_ImageName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetStoreType)
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

#endif // !defined(AFX_SETSTORETYPE_H__1DE2A910_6939_4EFC_BFC0_FA9337A4220C__INCLUDED_)
