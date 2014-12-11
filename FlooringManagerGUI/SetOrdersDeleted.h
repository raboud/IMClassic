// SetOrdersDeleted.h : Declaration of the CSetOrdersDeleted

#pragma once

// code generated on Wednesday, April 09, 2003, 4:34 PM

class CSetOrdersDeleted : public CRecordset
{
public:
	CSetOrdersDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrdersDeleted)

// Field/Param Data

	long	m_OrderID;
	long	m_CustomerID;
	CTime	m_OrderDate;
	CString	m_PurchaseOrderNumber;
	CString	m_Notes;
	CTime	m_ScheduleDate;
	CTime	m_BilledDate;
	BOOL	m_Scheduled;
	BOOL	m_Billed;
	BOOL	m_Paid;
	BOOL	m_Called;
	CString	m_InternalNotes;
	CString	m_CostAmount;
	CString	m_BilledAmount;
	long	m_MaterialTypeID;
	CString	m_OrderAmount;
	CString	m_TripCharge;
	BOOL	m_NoMinimum;
	BOOL	m_ScheduledAM;
	BOOL	m_Cancelled;
	BOOL	m_Warrenty;
	long	m_StoreID;
	BOOL	m_SevenDay;
	CString	m_DrawingNumber;
	CTime	m_DrawingDate;
	BOOL	m_CustomerToCall;
	BOOL	m_Invoice;
	CString	m_OriginalPO;
	CString	m_OrderNo;
	CTime	m_DateEntered;
	long	m_EnteredBy;
	long    m_EntryMethodID;
	CTime   m_FollowUpDate;
	CString m_FollowUpAction;
	long    m_ServiceLineNo;
	CTime   m_LastModifiedDateTime;
	COleDateTime   m_DateDeleted;
	long	m_DeletedBy;

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


