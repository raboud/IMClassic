/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETMILLERROR_H__CD8A65E5_CA16_4106_BF3A_E363261453D1__INCLUDED_)
#define AFX_SETMILLERROR_H__CD8A65E5_CA16_4106_BF3A_E363261453D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetMillError.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetMillError recordset

class CSetMillError : public CRecordset
{
public:
	CSetMillError(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMillError)

// Field/Param Data
	//{{AFX_FIELD(CSetMillError, CRecordset)
	long	m_Id;
	CString	m_Description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetMillError)
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

#endif // !defined(AFX_SETMILLERROR_H__CD8A65E5_CA16_4106_BF3A_E363261453D1__INCLUDED_)
