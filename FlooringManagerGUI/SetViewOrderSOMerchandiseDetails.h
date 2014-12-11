// SetViewOrderSOMerchandiseDetails.h : Declaration of the CSetViewOrderSOMerchandiseDetails

#pragma once

// code generated on Tuesday, December 30, 2003, 12:16 PM

class CSetViewOrderSOMerchandiseDetails : public CRecordset
{
public:
	CSetViewOrderSOMerchandiseDetails(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetViewOrderSOMerchandiseDetails)

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
	long    m_BasicLaborID;
	CString	m_PurchaseOrderNumber;
	COleDateTime	m_OrderDate;
	long	m_CustomerID;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_SONumber;
	long    m_SOLineNumber;
	long    m_SOMerLineNumber;
	CString	m_SKUNumber;
	CString	m_Description;
	CString	m_ShortDescription;
	double	m_Quantity;
	BOOL	m_Cancelled;
	BOOL	m_Warrenty;
	CString	m_UOMDescription;
	long	m_NumberOfDecimals;
	long	m_StoreID;
	COleDateTime	m_ExpectedArrivalDate;
	BOOL	m_Paid;
	BOOL	m_Billed;
	BOOL	m_Scheduled;
	COleDateTime	m_ScheduleStartDate;
	BOOL	m_ScheduledAM;
	CString	m_MaterialTypeName;
	long	m_MaterialStatusID;
	CString	m_Status;
	BOOL	m_Billable;
	BOOL	m_Installable;
	long    m_EntryMethodID;
	BOOL    m_Deleted;
	long    m_TransferredTo;
	long    m_TransferredFrom;
	long    m_OriginalID;
	double  m_PreSplitQty;
	BOOL    m_Reviewed;

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


