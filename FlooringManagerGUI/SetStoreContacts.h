// SetStoreContacts.h : Declaration of the CSetStoreContacts

#pragma once

// code generated on Tuesday, September 16, 2003, 12:20 PM

class CSetStoreContacts : public CRecordset
{
public:
	CSetStoreContacts(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetStoreContacts)

	long	m_ID;
	long	m_StoreID;
	long	m_DepartmentID;
	CString	m_FirstName;
	CString	m_LastName;
	long	m_TitleID;
	CString	m_PhoneNumber;
	CString	m_AltPhoneNumber;
	CString m_EmailAddress;
	BOOL    m_EmailStatusReport;

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


