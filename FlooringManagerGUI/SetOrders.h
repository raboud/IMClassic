/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

// SetOrders.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOrders recordset
class CSetOrders : public CRecordset
{
private:
	TIMESTAMP_STRUCT	m_ScheduleStartDate2;
	TIMESTAMP_STRUCT	m_ScheduleEndDate2;
public:
	CSetOrders(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrders)

// Field/Param Data
	//{{AFX_FIELD(CSetOrders, CRecordset)
	long			m_OrderID;
	long			m_CustomerID;
	COleDateTime	m_OrderDate;
	CString			m_PurchaseOrderNumber;
	CString			m_OriginalPO;
	CString			m_CustOrderNo;
	CString			m_Notes;
	CString			m_ScheduleStartDate;
	CString			m_ScheduleEndDate;
	COleDateTime	m_BilledDate;
	BOOL			m_Scheduled;
	BOOL			m_Billed;
	BOOL			m_Paid;
	BOOL			m_Called;
	CString			m_BilledAmount;
	long			m_MaterialTypeID;
	BOOL			m_NoMinimum;
	CString			m_OrderAmount;
	CString			m_TripCharge;
	BOOL			m_ScheduledAM;
	BOOL			m_Cancelled;
	BOOL			m_Warrenty;
	CString			m_InternalNotes;
	long			m_StoreID;
	BOOL			m_SevenDay;
	COleDateTime	m_drawingDate;
	CString			m_strDrawingNumber;
	CString			m_CostAmount;
	BOOL			m_Invoice;
	COleDateTime	m_DateEntered;
	long			m_EnteredBy;
	long			m_EntryMethodID;
	COleDateTime	m_FollowUpDate;
	CString			m_FollowUpAction;
	long			m_ServiceLineNo;
	COleDateTime	m_LastModifiedDateTime;
	CString			m_XMLOrderCostAmount;
	BOOL			m_Deleted;
	CString			m_SPNNotes;
	BOOL			m_Reviewed;
	long			m_ReviewedBy;
	COleDateTime   m_ReviewedDate;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOrders)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
