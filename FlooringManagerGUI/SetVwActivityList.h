/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetVwActivityList.h : Declaration of the CSetViewActivityList

#pragma once

// code generated on Wednesday, March 15, 2006, 1:43 PM

class CSetViewActivityList : public CRecordset
{
public:
	CSetViewActivityList(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetViewActivityList)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CString	m_StoreNumber;
	CString	m_PurchaseOrderNumber;
	CString	m_CustomerName;
	CString	m_ActivityName;
	COleDateTime	m_CreatedDate;
	COleDateTime	m_FollowUpDate;
	CString	m_Data;
	CString	m_MarketName;
	CString	m_Division;
	long	m_ActivityTypeID;
	long	m_OrderID;
	COleDateTime	m_ClosedDate;
	long	m_MarketId;
	long	m_DivisionID;
	CString m_ClosedByName;
	CString m_NoteText;
	long    m_ClosedByID;

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


