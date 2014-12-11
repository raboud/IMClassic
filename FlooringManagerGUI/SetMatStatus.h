/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETMATSTATUS_H__D39396E6_9EB4_4A95_B91E_502D00AF0CE1__INCLUDED_)
#define AFX_SETMATSTATUS_H__D39396E6_9EB4_4A95_B91E_502D00AF0CE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetMatStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetMatStatus recordset

class CSetMatStatus : public CRecordset
{
public:
	CSetMatStatus(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMatStatus)

// Field/Param Data
	//{{AFX_FIELD(CSetMatStatus, CRecordset)
	long	m_MatStatusID;
	CString	m_Status;
	BOOL	m_Billable;
	BOOL	m_Installable;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetMatStatus)
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

#endif // !defined(AFX_SETMATSTATUS_H__D39396E6_9EB4_4A95_B91E_502D00AF0CE1__INCLUDED_)
