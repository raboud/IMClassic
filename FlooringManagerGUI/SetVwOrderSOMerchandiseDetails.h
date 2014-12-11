// SetVwOrderSOMerchandiseDetails.h : Declaration of the CSetVwOrderSOMerchandiseDetails

#pragma once

// code generated on Friday, December 12, 2003, 5:44 PM

class CSetVwOrderSOMerchandiseDetails : public CRecordset
{
public:
	CSetVwOrderSOMerchandiseDetails(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVwOrderSOMerchandiseDetails)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_OrderID;
	CString	m_PurchaseOrderNumber;
	CTime	m_OrderDate;
	long	m_CustomerID;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_SONumber;
	CString	m_SKUNumber;
	CString	m_Description;
	CString	m_ShortDescription;
	double	m_Quantity;
	BOOL	m_Cancelled;
	BOOL	m_Warrenty;
	CString	m_UOMDescription;
	long	m_NumberOfDecimals;
	long	m_StoreID;
	CTime	m_ExpectedArrivalDate;
	BOOL	m_Paid;
	BOOL	m_Billed;
	BOOL	m_Scheduled;
	CTime	m_ScheduleDate;
	BOOL	m_ScheduledAM;
	CString	m_MaterialTypeName;
	long    m_MaterialStatusID;
	BOOL    m_Installable;
	BOOL    m_Billable;
	long	m_TransferredTo ;
	long	m_TransferredFrom ;

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


