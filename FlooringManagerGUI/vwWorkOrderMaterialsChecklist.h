/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// vwWorkOrderMaterialsChecklist.h : Declaration of the CvwWorkOrderMaterialsChecklist

#pragma once

// code generated on Sunday, February 08, 2004, 6:25 PM

class CvwWorkOrderMaterialsChecklist : public CRecordset
{
public:
	CvwWorkOrderMaterialsChecklist(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CvwWorkOrderMaterialsChecklist)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_OrderID;
	double	m_Quantity;
	CString	m_MatDesc;
	CString	m_UOM;
	CString	m_Status;

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


