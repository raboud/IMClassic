// SetVwDiscrepancies.h : Declaration of the CSetVwDiscrepancies

#pragma once

// code generated on Friday, December 05, 2003, 4:34 PM

class CSetVwDiscrepancies : public CRecordset
{
public:
	CSetVwDiscrepancies(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVwDiscrepancies)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	CString m_PONumber;
	CString m_StoreNumber;
	CString	m_Type;
	CString	m_SubType;
	CString m_CustomerName;
	BOOL    m_Reviewed;
	CString	m_CurrentData;
	CString	m_NewData;
	long    m_DetailID;
	long    m_OrderID;
	long    m_MarketID;
	long    m_DivisionID;
	//CString	m_XMLFilePath;
	//COleDateTime m_DateFound;

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


