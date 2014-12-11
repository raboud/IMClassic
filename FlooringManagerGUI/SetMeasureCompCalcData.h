// SetMeasureCompCalcData.h : Declaration of the CSetMeasureCompCalcData

#pragma once

// code generated on Monday, April 12, 2004, 7:11 PM

class CSetMeasureCompCalcData : public CRecordset
{
public:
	CSetMeasureCompCalcData(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMeasureCompCalcData)

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
	COleDateTime m_CalcTimeStamp;
	BOOL	m_Assigned;
	CString m_Identity;

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


