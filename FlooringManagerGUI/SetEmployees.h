// SetEmployees.h : Declaration of the CSetEmployees

#pragma once

// code generated on Sunday, January 26, 2003, 2:14 PM

class CSetEmployees : public CRecordset
{
public:
	CSetEmployees(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetEmployees)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	//long	m_uid;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_NickName;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_City;
	CString	m_State;
	CString	m_Zip;
	CString	m_HomeNumber;
	CString	m_MobileNumber;
	CString	m_PagerNumber;
	CString	m_SSN;
	CString	m_Email;
	COleDateTime m_HireDate;
	BOOL	m_ReceiveCallNotes;
	CString m_SMTPEmail;
	CString m_UserName;

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


