// SetOrderRegMerchandiseDetails.h : Declaration of the CSetOrderRegMerchandiseDetails

#pragma once

// code generated on Tuesday, December 30, 2003, 3:44 PM

class CSetOrderRegMerchandiseDetails : public CRecordset
{
public:
	CSetOrderRegMerchandiseDetails(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderRegMerchandiseDetails)

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
	long	m_UOMId;
	double	m_Price;
	double	m_Retail;
	long	m_HDLineNumber;
	CString	m_Notes;
	long    m_StatusID;
	long    m_EntryMethodID;
	BOOL	m_Deleted ;
	long    m_TransferredTo;
	long    m_TransferredFrom;
	BOOL    m_Reviewed ;
	long    m_ReviewedBy ;
	COleDateTime   m_ReviewedDate ;
	CString m_Identity;
	long    m_OriginalOrderID;

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


