// SetOrderSOMerchandiseDetailsDeleted.h : Declaration of the CSetOrderSOMerchandiseDetailsDeleted

#pragma once

// code generated on Monday, February 09, 2004, 9:02 PM

class CSetOrderSOMerchandiseDetailsDeleted : public CRecordset
{
public:
	CSetOrderSOMerchandiseDetailsDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderSOMerchandiseDetailsDeleted)

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
	CString	m_SONumber;
	CString	m_SKUNumber;
	long	m_BasicLaborID;
	CString	m_ShortDescription;
	CString	m_Description;
	double	m_Quantity;
	long	m_UOMId;
	CTime	m_ExpectedArrivalDate;
	long	m_HDLineNumber;
	long	m_MaterialStatusID;
	long	m_EntryMethodID;
	BOOL	m_Deleted;

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


