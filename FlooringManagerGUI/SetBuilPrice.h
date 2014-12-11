/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetBuilPrice.h : Declaration of the CSetBuilPrice

#pragma once

// code generated on Saturday, February 16, 2002, 2:56 PM

class CSetBuilPrice : public CRecordset
{
public:
	CSetBuilPrice(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetBuilPrice)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_MaterialID;
	double	m_UnitPrice;
	double	m_UnitRetail;
	long	m_MarketId;
	CTime	m_OrderDate;
	long	m_PriceID;

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


