/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETINSTALLERERROR_H__4B9286B0_A9D3_4AB4_A4E7_C07056F4868B__INCLUDED_)
#define AFX_SETINSTALLERERROR_H__4B9286B0_A9D3_4AB4_A4E7_C07056F4868B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetInstallerError.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetInstallerError recordset

class CSetInstallerError : public CRecordset
{
public:
	CSetInstallerError(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetInstallerError)

// Field/Param Data
	//{{AFX_FIELD(CSetInstallerError, CRecordset)
	long	m_Id;
	CString	m_Description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetInstallerError)
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

#endif // !defined(AFX_SETINSTALLERERROR_H__4B9286B0_A9D3_4AB4_A4E7_C07056F4868B__INCLUDED_)
