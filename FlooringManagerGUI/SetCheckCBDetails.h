// SetCheckCBDetail.h : Declaration of the CSetCheckCBDetail

#pragma once

// code generated on Wednesday, May 28, 2003, 8:10 PM

class CSetCheckCBDetail : public CRecordset
{
public:
	CSetCheckCBDetail(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCheckCBDetail)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_CheckCBDetailID;
	long	m_CheckID;
	long	m_ChargeBackID;
	double	m_Amount;

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


