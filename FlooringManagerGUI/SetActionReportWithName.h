// SetActionReportWithName.h : Declaration of the CSetActionReportWithName

#pragma once

// code generated on Friday, January 31, 2003, 4:15 PM

class CSetActionReportWithName : public CRecordset
{
public:
	CSetActionReportWithName(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetActionReportWithName)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	COleDateTime m_ReportDate;
	CString	m_Nature;
	CString	m_ActionRequired;
	CString	m_Cause;
	BOOL	m_Closed;
	long	m_ID;
	CString	m_PurchaseOrderNumber;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_Address;
	CString	m_City;
	CString	m_State;
	CString	m_ZipCode;
	CString	m_PhoneNumber;
	CString	m_WorkNumber;
	long	m_OrderID;
	long	m_StoreError;
	long	m_MillError;
	long	m_InstallerError;
	long	m_MeasureError;
	COleDateTime m_LastUpdatedDate;
	CString m_CreatedBy;
	CString m_LastUpdatedBy;

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


