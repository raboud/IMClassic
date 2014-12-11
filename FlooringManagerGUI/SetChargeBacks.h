/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once
// SetChargeBacks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetChargeBacks recordset

class CSetChargeBacks : public CRecordset
{
public:
	CSetChargeBacks(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetChargeBacks)

// Field/Param Data
	//{{AFX_FIELD(CSetChargeBacks, CRecordset)
	long	m_ChargeBackID;
	CString	m_Amount;
	long	m_SubcontractorID;
	CString	m_AmountToSub;
	CString	m_Number;
	CString	m_Name;
	CString	m_Reason;
	COleDateTime m_IssueDate;
	CString	m_OriginalPO;
	long    m_OrderID ;
	BOOL    m_CostAdjustment;
	BOOL	m_Approved;
	long	m_ApprovalNumber ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetChargeBacks)
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
