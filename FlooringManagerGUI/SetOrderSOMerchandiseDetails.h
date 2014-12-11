// SetOrderSOMerchandiseDetails.h : Declaration of the CSetOrderSOMerchandiseDetails

#pragma once

// code generated on Tuesday, December 30, 2003, 12:18 PM

class CSetOrderSOMerchandiseDetails : public CRecordset
{
public:
	CSetOrderSOMerchandiseDetails(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderSOMerchandiseDetails)

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
	CString	m_SONumber;
	CString	m_SKUNumber;
	long	m_BasicLaborID;
	CString	m_ShortDescription;
	CString	m_Description;
	double	m_Quantity;
	long	m_UOMId;
	COleDateTime	m_ExpectedArrivalDate;
	long	m_SOLineNumber;
	long    m_SOMerLineNumber;
	long	m_MaterialStatusID;
	long    m_EntryMethodID;
	BOOL	m_Deleted ;
	long    m_TransferredTo;
	long    m_TransferredFrom;
	long    m_OriginalID;
	double  m_PreSplitQty;
	BOOL    m_Reviewed ;
	long    m_ReviewedBy ;
	COleDateTime   m_ReviewedDate ;
	CString m_Identity;
	long    m_OriginalOrderID;
	BOOL	m_NotNeeded;

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


