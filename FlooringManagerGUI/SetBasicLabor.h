/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETBASICLABOR_H__4B271726_26A9_4591_B8B0_43AA16017CFD__INCLUDED_)
#define AFX_SETBASICLABOR_H__4B271726_26A9_4591_B8B0_43AA16017CFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetBasicLabor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetBasicLabor recordset

class CSetBasicLabor : public CRecordset
{
public:
	CSetBasicLabor(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetBasicLabor)

// Field/Param Data
	//{{AFX_FIELD(CSetBasicLabor, CRecordset)
	long	m_UnitOfMeasureID;
	long	m_BasicLaborID;
	CString	m_LaborDescription;
	long	m_MaterialTypeID;
	BOOL	m_Active;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetBasicLabor)
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

#endif // !defined(AFX_SETBASICLABOR_H__4B271726_26A9_4591_B8B0_43AA16017CFD__INCLUDED_)
