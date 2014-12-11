// SetUserMarketDivisionAssignments.h : Declaration of the CSetUserMarketDivisionAssignments

#pragma once

// code generated on Wednesday, August 18, 2004, 7:17 PM

class CSetUserMarketDivisionAssignments : public CRecordset
{
public:
	CSetUserMarketDivisionAssignments(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetUserMarketDivisionAssignments)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_UserID;
	long	m_MarketID;
	long	m_DivisionID;

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


