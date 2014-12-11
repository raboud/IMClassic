// SetOrderBasicLaborDetailsDeleted.h : Declaration of the CSetOrderBasicLaborDetailsDeleted

#pragma once

// code generated on Monday, February 09, 2004, 9:00 PM

class CSetOrderBasicLaborDetailsDeleted : public CRecordset
{
public:
	CSetOrderBasicLaborDetailsDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderBasicLaborDetailsDeleted)

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
	long	m_BasicLaborID;
	double	m_InstallQuantity;
	CString	m_UnitCost;
	CString	m_UnitPrice;
	CString	m_UnitRetail;
	BOOL	m_PrintOnInvoice;
	BOOL	m_PrintOnWO;
	long	m_ServiceLineNumber;
	long	m_EntryMethodID;
	BOOL	m_Deleted;

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


