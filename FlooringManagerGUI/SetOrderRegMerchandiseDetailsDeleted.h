// SetOrderRegMerchandiseDetailsDeleted.h : Declaration of the CSetOrderRegMerchandiseDetailsDeleted

#pragma once

// code generated on Monday, February 09, 2004, 9:01 PM

class CSetOrderRegMerchandiseDetailsDeleted : public CRecordset
{
public:
	CSetOrderRegMerchandiseDetailsDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderRegMerchandiseDetailsDeleted)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long    m_OriginalID;
	long	m_OrderID;
	CString	m_SKUNumber;
	CString	m_ShortDescription;
	CString	m_Description;
	double	m_Quantity;
	long	m_UOMId;
	double	m_Price;
	double	m_Retail;
	long	m_HDLineNumber;
	CString	m_Notes;
	long	m_StatusID;
	BOOL	m_Deleted;
	long    m_EntryMethodID;

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


