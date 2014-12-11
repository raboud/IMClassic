/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once
// SetPayments.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetPayments recordset

class CSetPayments : public CRecordset
{
public:
	CSetPayments(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetPayments)

// Field/Param Data
	//{{AFX_FIELD(CSetPayments, CRecordset)
	CString	m_CheckNumber;
	COleDateTime	m_CheckDate;
	CString	m_Amount;
	long	m_OrderID;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_PurchaseOrderNumber;
	long	m_CheckDetailID;
	BOOL	m_Billed;
	CString	m_BilledAmount;
	COleDateTime	m_BilledDate;
	CString	m_TotalAmount;
	CString	m_Balance;
	BOOL	m_Paid;
	long	m_CheckID ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPayments)
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
