// SetVwOrderBasicLaborDetails.h : Declaration of the CSetVwOrderBasicLaborDetails

#pragma once

// code generated on Friday, December 12, 2003, 6:07 PM

class CSetVwOrderBasicLaborDetails : public CRecordset
{
public:
	CSetVwOrderBasicLaborDetails(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVwOrderBasicLaborDetails)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	BOOL	m_Cancelled;
	BOOL	m_ScheduledAM;
	CString	m_FirstName;
	CString	m_LastName;
	double	m_InstallQuantity;
	BOOL	m_IsPadding;
	CString	m_LaborDescription;
	BOOL	m_Scheduled;
	COleDateTime	m_ScheduleStartDate;
	long	m_StoreID;
	long	m_CustomerID;
	CString	m_StoreNumber;
	long	m_OrderID;
	BOOL	m_Billed;
	CString	m_PurchaseOrderNumber;
	CString	m_UOMDescription;
	long	m_NumberOfDecimals;
	double	m_UnitPrice;
	double	m_UnitCost;
	long	m_YardsPerRoll;
	BOOL	m_Paid;
	double	m_UnitRetail;
	BOOL	m_Warrenty;
	CString	m_MaterialTypeName;
	BOOL	m_Invoice;
	long	m_DivisionID;
	long	m_MarketId;
	BOOL	m_Deleted;
	BOOL	m_PrintOnInvoice;
	BOOL	m_PrintOnWO ;

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


