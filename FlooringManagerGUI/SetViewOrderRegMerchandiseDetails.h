// SetViewOrderRegMerchandiseDetails.h : Declaration of the CSetViewOrderRegMerchandiseDetails

#pragma once

// code generated on Tuesday, December 30, 2003, 3:43 PM

class CSetViewOrderRegMerchandiseDetails : public CRecordset
{
public:
	CSetViewOrderRegMerchandiseDetails(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetViewOrderRegMerchandiseDetails)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_OrderID;
	CString	m_SKUNumber;
	CString	m_ShortDescription;
	CString	m_Description;
	double	m_Quantity;
	CString	m_UOMDescription;
	double	m_Price;
	double	m_Retail;
	CString	m_Notes;
	CString m_Status;
	long    m_EntryMethodID;
	BOOL    m_Deleted;
	BOOL    m_Reviewed;

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


