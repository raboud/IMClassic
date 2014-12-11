/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetVwActivePOs.h : Declaration of the CSetVwActivePOs

#pragma once

// code generated on Friday, February 03, 2006, 9:33 AM

class CSetVwActivePOs : public CRecordset
{
public:
	CSetVwActivePOs(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetVwActivePOs)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CString	m_PurchaseOrderNumber;
	CString	m_StoreNumber;
	CString	m_CustomerName;
	COleDateTime m_OrderDate;
	COleDateTime m_ScheduleStartDate;
	COleDateTime m_ScheduleEndDate;
	BOOL	m_Scheduled;
	CString	m_MarketName;
	CString	m_Division;
	BOOL	m_Billed;
	BOOL	m_Paid;
	long	m_DivisionID;
	long	m_MarketId;
	long	m_OrderID;
	long	m_EntryMethodID;
	BOOL	m_Cancelled;
	BOOL    m_HasAlerts;

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


