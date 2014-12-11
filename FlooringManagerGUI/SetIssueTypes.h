// SetIssueTypes.h : Declaration of the CSetIssueTypes

#pragma once

// code generated on Monday, January 24, 2005, 4:35 PM

class CSetIssueTypes : public CRecordset
{
public:
	CSetIssueTypes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetIssueTypes)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CString	m_IssueType;
	long    m_DisplayOrder;

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


