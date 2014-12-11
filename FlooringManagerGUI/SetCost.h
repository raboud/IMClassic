/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCost.h : Declaration of the CSetCost

#pragma once

// code generated on Friday, February 15, 2002, 10:03 PM

class CSetCost : public CRecordset
{
public:
	CSetCost(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCost)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_CostID;
	CTime	m_StartDate;
	CTime	m_EndDate;
	CStringA	m_Description;
	double	m_Cost;
	long	m_MarketID;

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


