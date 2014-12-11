/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETMEASUREERROR_H__A57A1164_C7B4_4CB0_80CF_88CD7C53A8D9__INCLUDED_)
#define AFX_SETMEASUREERROR_H__A57A1164_C7B4_4CB0_80CF_88CD7C53A8D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetMeasureError.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetMeasureError recordset

class CSetMeasureError : public CRecordset
{
public:
	CSetMeasureError(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMeasureError)

// Field/Param Data
	//{{AFX_FIELD(CSetMeasureError, CRecordset)
	long	m_Id;
	CString	m_Description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetMeasureError)
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

#endif // !defined(AFX_SETMEASUREERROR_H__A57A1164_C7B4_4CB0_80CF_88CD7C53A8D9__INCLUDED_)
