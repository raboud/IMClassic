// SetMeasureCompLineItemData.h : Declaration of the CSetMeasureCompLineItemData

#pragma once

// code generated on Monday, April 12, 2004, 7:10 PM

class CSetMeasureCompLineItemData : public CRecordset
{
public:
	CSetMeasureCompLineItemData(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMeasureCompLineItemData)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_CalcID;
	long	m_LineItemNumber;
	CString	m_MaterialType;
	CString	m_MaterialDescription;
	long	m_MaterialWidth;
	CString	m_PatternMatch;
	CString	m_MaterialAmount;

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


