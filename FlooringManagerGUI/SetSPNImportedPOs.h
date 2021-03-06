// SetSPNImportedPOs.h : Declaration of the CSetSPNImportedPOs

#pragma once

// code generated on Sunday, February 01, 2004, 5:21 PM

class CSetSPNImportedPOs : public CRecordset
{
public:
	CSetSPNImportedPOs(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetSPNImportedPOs)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CString	m_PONumber;
	long	m_StoreID;
	long	m_POStatusID;
	CString	m_XMLFilePath;
	COleDateTime	m_DateImported;

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


