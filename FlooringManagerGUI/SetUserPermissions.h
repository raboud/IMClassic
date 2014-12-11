// SetUserPermissions.h : Declaration of the CSetUserPermissions

#pragma once

// code generated on Wednesday, March 12, 2003, 10:20 AM

class CSetUserPermissions : public CRecordset
{
public:
	CSetUserPermissions(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetUserPermissions)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_UserID;
	long	m_Market;
	long	m_Division;
	long	m_PermissionID;

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


