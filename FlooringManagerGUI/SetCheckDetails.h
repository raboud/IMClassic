/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once
// SetCheckDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetCheckDetails recordset

class CSetCheckDetails : public CRecordset
{
public:
	CSetCheckDetails(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCheckDetails)

// Field/Param Data
	//{{AFX_FIELD(CSetCheckDetails, CRecordset)
	long	m_CheckDetailID;
	long	m_CheckID;
	long	m_OrderID;
	CString	m_Amount;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetCheckDetails)
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
