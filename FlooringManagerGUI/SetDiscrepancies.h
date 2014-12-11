// SetDiscrepancies.h : Declaration of the CSetDiscrepancies

#pragma once

// code generated on Monday, December 08, 2003, 11:47 AM

class CSetDiscrepancies : public CRecordset
{
public:
	CSetDiscrepancies(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetDiscrepancies)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	//CString	m_PONumber;
	//long	m_CustOrStoreID;
	long	m_DiscrepancyTypeID;
	long	m_DiscrepancySubTypeID;
	CString	m_CurrentData;
	CString	m_NewData;
	CString	m_XMLFilePath;
	COleDateTime	m_DateFound;
	long    m_OrderID;
	long    m_DetailID;
	BOOL    m_Reviewed;
	long    m_ReviewedBy;
	COleDateTime   m_ReviewedDate;

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


