/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetVwDepartmentsContactTitles.h : Declaration of the CSetVwDepartmentsContactTitles

#pragma once

// code generated on Thursday, April 20, 2006, 11:08 AM

class CSetVwDepartmentsContactTitles : public CRecordset
{
public:
	CSetVwDepartmentsContactTitles(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetVwDepartmentsContactTitles)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CString	m_DepartmentName;
	CString	m_Title;
	long	m_DepartmentID;
	long	m_ContactTitlesID;

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


