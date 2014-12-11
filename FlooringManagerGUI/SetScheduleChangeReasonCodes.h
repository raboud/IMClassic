// SetScheduleChangeReasonCodes.h : Declaration of the CSetScheduleChangeReasonCodes

#pragma once

// code generated on Thursday, October 20, 2005, 11:36 AM

class CSetScheduleChangeReasonCodes : public CRecordset
{
public:
	CSetScheduleChangeReasonCodes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetScheduleChangeReasonCodes)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CString	m_ReasonText;
	BOOL	m_Measure;

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


