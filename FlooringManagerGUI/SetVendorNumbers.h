// SetVendorNumbers.h : Declaration of the CSetVendorNumbers

#pragma once

// code generated on Tuesday, July 15, 2003, 1:49 PM

class CSetVendorNumbers : public CRecordset
{
public:
	CSetVendorNumbers(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVendorNumbers)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_VendorID;
	CString	m_VendorNumber;
	CString	m_Description;
	BOOL	m_PaySubWhenPaid;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


