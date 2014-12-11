// SetOrderMaterialsDetailsDeleted.h : Declaration of the CSetOrderMaterialsDetailsDeleted

#pragma once

// code generated on Wednesday, April 09, 2003, 4:35 PM

class CSetOrderMaterialsDetailsDeleted : public CRecordset
{
public:
	CSetOrderMaterialsDetailsDeleted(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderMaterialsDetailsDeleted)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_OrdeMateriallID;
	long	m_OrderID;
	long	m_MaterialID;
	double	m_Width;
	double	m_Length;
	CString	m_UnitPrice;
	long	m_SubContractorID;
	BOOL	m_MerchandisPresent;
	CString	m_UnitCost;
	BOOL	m_HasSONumber;
	CString	m_SONumber;
	double	m_Size;
	CString	m_Style;
	CString	m_Color;
	CString	m_UnitRetail;
	BOOL	m_Completed;
	long	m_MatStatusID;
	long	m_Location;
	CTime	m_ReceivedDate;
	BOOL	m_SubContractorPaid;
	double	m_SubContractorPay;

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


