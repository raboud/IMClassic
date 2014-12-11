// SetOrderCustomDetailsDeleted.h : Declaration of the CSetOrderCustomDetailsDeleted

#pragma once

// code generated on Wednesday, April 09, 2003, 4:36 PM

class CSetOrderCustomDetailsDeleted : public CRecordset
{
public:
	CSetOrderCustomDetailsDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderCustomDetailsDeleted)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long    m_OriginalID;
	long	m_OrderID;
	long	m_SubContractorID;
	CString	m_RetailPrice;
//	double	m_Multiplier;
	CString	m_UnitCost;
	CString	m_UnitPrice;
	double	m_Quanity;
	CString	m_Description;
//	double	m_CostMultiplier;
	long	m_UnitOfMeasureID;
	BOOL	m_NotOnInvoice;
	BOOL	m_NotOnWorkOrder;
	BOOL	m_SubContractorPaid;
	double	m_SubContractorPay;
	long    m_EntryMethodID;
	BOOL    m_Deleted;

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


