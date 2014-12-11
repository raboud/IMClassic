// SetVwChargeBacksTaken.h : Declaration of the CSetVwChargeBacksTaken

#pragma once

// code generated on Saturday, May 31, 2003, 1:40 PM

class CSetVwChargeBacksTaken : public CRecordset
{
public:
	CSetVwChargeBacksTaken(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVwChargeBacksTaken)

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
	CString	m_CheckNumber;
	COleDateTime	m_CheckDate;

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


