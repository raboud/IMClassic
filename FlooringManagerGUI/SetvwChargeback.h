// SetvwChargeback.h : Declaration of the CSetvwChargeback

#pragma once

// code generated on Wednesday, May 28, 2003, 11:49 PM

class CSetvwChargeback : public CRecordset
{
public:
	CSetvwChargeback(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetvwChargeback)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ChargeBackID;
	double	m_Amount;
	long	m_SubcontractorID;
	double	m_AmountToSub;
	CString	m_Number;
	CString	m_Name;
	CString	m_Reason;
	COleDateTime	m_IssueDate;
	CString	m_OriginalPO;
	BOOL	m_CostAdjustment;
	long	m_OrderID;
	long	m_ApprovalNumber;
	BOOL	m_Approved;
	double	m_Balance;
	CString	m_FirstName;
	CString	m_LastName;
	long m_VendorID;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


