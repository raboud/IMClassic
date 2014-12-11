// SetVwUserAlerts.h : Declaration of the CSetVwUserAlerts

#pragma once

// code generated on Wednesday, August 18, 2004, 4:05 PM

class CSetVwUserAlerts : public CRecordset
{
public:
	CSetVwUserAlerts(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetVwUserAlerts)

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
	COleDateTime   m_OrderDate;
	COleDateTime	m_ScheduleStartDate;
	BOOL    m_Scheduled;
	CString	m_MarketName;
	CString	m_Division;
	BOOL	m_Billed;
	BOOL	m_Paid;
	long	m_DivisionID;
	long	m_MarketID;

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


