/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETORDERANDCUSTOMER_H__35155509_9D6F_4F3B_9955_D3C2DBD2264E__INCLUDED_)
#define AFX_SETORDERANDCUSTOMER_H__35155509_9D6F_4F3B_9955_D3C2DBD2264E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetOrderAndCustomer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetOrderAndCustomer recordset

class CSetOrderAndCustomer : public CRecordset
{
public:
	CSetOrderAndCustomer(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderAndCustomer)

// Field/Param Data
	//{{AFX_FIELD(CSetOrderAndCustomer, CRecordset)
	CString	m_Address;
	BOOL	m_Billed;
	CString	m_BilledAmount;
	COleDateTime	m_BilledDate;
	BOOL	m_Called;
	BOOL	m_Cancelled;
	CString	m_City;
	CString	m_CostAmount;
	long	m_CustomerID;
	CString	m_Directions;
	CString	m_Extension;
	CString	m_FirstName;
	CString	m_InternalNotes;
	CString	m_LastName;
	long	m_MaterialTypeID;
	BOOL	m_NoMinimum;
	CString	m_Notes;
	CString	m_OrderAmount;
	COleDateTime	m_OrderDate;
	long	m_OrderID;
	BOOL	m_Paid;
	CString	m_PhoneNumber;
	CString	m_PurchaseOrderNumber;
	CString	m_OriginalPO;
	BOOL	m_Scheduled;
	BOOL	m_ScheduledAM;
	COleDateTime	m_ScheduleStartDate;
	COleDateTime	m_ScheduleEndDate;
	CString	m_State;
	CString	m_TripCharge;
	BOOL	m_Warrenty;
	CString	m_WorkNumber;
	CString	m_ZipCode;
	CString	m_TotalAmount;
	CString m_Balance ;
	CString	m_StoreNumber;
	CString	m_MaterialTypeName;
	CString m_ShortName;
	long m_StoreTypeID;
	BOOL	m_Invoice;
	long m_VendorID;
	BOOL m_MarkBilledWhenPaid;
	CString m_XMLOrderCostAmount;
	long m_EntryMethodID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOrderAndCustomer)
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

#endif // !defined(AFX_SETORDERANDCUSTOMER_H__35155509_9D6F_4F3B_9955_D3C2DBD2264E__INCLUDED_)
