// SetCompanyInfo.h : Declaration of the CSetCompanyInfo

#pragma once

// code generated on Friday, September 17, 2004, 3:53 PM

class CSetCompanyInfo : public CRecordset
{
public:
	CSetCompanyInfo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCompanyInfo)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CString	m_Name;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_City;
	CString	m_State;
	CString	m_Zip;
	CString	m_Phone1;
	CString	m_Phone2;
	CString	m_Fax1;
	CString	m_Fax2;
	CString	m_VendorNumber;

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


