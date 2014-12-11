// SetVwPOPickList.h : Declaration of the CSetVwPOPickList

#pragma once

// code generated on Tuesday, October 26, 2004, 11:37 PM

class CSetVwPOPickList : public CRecordset
{
public:
	CSetVwPOPickList(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetVwPOPickList)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_OrderID;
	long	m_CustomerID;
	COleDateTime m_OrderDate;
	CString	m_PurchaseOrderNumber;
	COleDateTime m_ScheduleStartDate;
	COleDateTime m_ScheduleEndDate;
	CString	m_ShortName;
	double	m_Total;
	long	m_HasNotes;
	long	m_HasReports;
	long    m_Cancelled;
	long    m_Warranty;
	long    m_Billed;
	long    m_Scheduled;
	long    m_Paid;
	BOOL	m_ScheduledAM;

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


