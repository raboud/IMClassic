/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMarket.h : Declaration of the CSetMarket

#pragma once

// code generated on Wednesday, May 08, 2002, 4:51 PM

class CSetMarket : public CRecordset
{
public:
	CSetMarket(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMarket)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_MarketId;
	CStringA	m_MarketName;
	//CStringW	m_BranchPrinterName;
	//CStringW	m_BranchPrinterPort;
	//CStringW	m_BranchPrinterDriver ;

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


