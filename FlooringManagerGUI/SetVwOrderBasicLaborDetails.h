// SetVwOrderBasicLaborDetails.h : Declaration of the CSetVwOrderBasicLaborDetails

#pragma once

// code generated on Friday, December 12, 2003, 6:07 PM

class CSetVwOrderBasicLaborDetails : public CRecordset
{
public:
	CSetVwOrderBasicLaborDetails(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVwOrderBasicLaborDetails)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	double	m_InstallQuantity;
	CString	m_LaborDescription;
	CString	m_UOMDescription;
	long	m_NumberOfDecimals;
	double	m_UnitPrice;
	double	m_UnitRetail;
//	BOOL	m_PrintOnInvoice;

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


