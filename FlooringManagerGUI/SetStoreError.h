/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETSTOREERROR_H__6FC2284A_DE41_4E0E_B1DE_E49E81F863E1__INCLUDED_)
#define AFX_SETSTOREERROR_H__6FC2284A_DE41_4E0E_B1DE_E49E81F863E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetStoreError.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetStoreError recordset

class CSetStoreError : public CRecordset
{
public:
	CSetStoreError(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetStoreError)

// Field/Param Data
	//{{AFX_FIELD(CSetStoreError, CRecordset)
	long	m_Id;
	CString	m_Description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetStoreError)
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

#endif // !defined(AFX_SETSTOREERROR_H__6FC2284A_DE41_4E0E_B1DE_E49E81F863E1__INCLUDED_)
