// DepartmentsRequiredContacts.h : Declaration of the CSetDepartmentsRequiredContacts

#pragma once

// code generated on Monday, January 26, 2004, 1:25 PM

class CSetDepartmentsRequiredContacts : public CRecordset
{
public:
	CSetDepartmentsRequiredContacts(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetDepartmentsRequiredContacts)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_StoreTypeID;
	long	m_DepartmentID;
	long	m_TitleID;

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


