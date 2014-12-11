// SetViewStoreContacts.h : Declaration of the CSetViewStoreContacts

#pragma once

// code generated on Monday, January 26, 2004, 5:19 PM

class CSetViewStoreContacts : public CRecordset
{
public:
	CSetViewStoreContacts(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetViewStoreContacts)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_StoreContactsID;
	long    m_DepartmentStoreID;
	long	m_StoreID;
	long    m_DepartmentID;
	CString	m_DepartmentName;
	CString	m_Title;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_PhoneNumber;
	CString	m_FaxNumber;
	CString m_AltFaxNumber;
	long m_FaxStatusReportTo;
	CString m_StoreNumber;
	BOOL m_Active;
	CString m_EmailAddress;
	BOOL m_EmailStatusReport;

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


