/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetDivision.h : Declaration of the CSetDivision

#pragma once

// code generated on Wednesday, May 08, 2002, 4:54 PM

class CSetDivision : public CRecordset
{
public:
	CSetDivision(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetDivision)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_DivisionID;
	CString	m_Division;
	long m_VendorID;
	long m_DivisionGroupID;
	long m_PrintStatusReport;

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


