// SetMeasureCompOrderData.h : Declaration of the CSetMeasureCompOrderData

#pragma once

// code generated on Friday, April 09, 2004, 1:19 AM

class CSetMeasureCompOrderData : public CRecordset
{
public:
	CSetMeasureCompOrderData(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetMeasureCompOrderData)

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
	BOOL	m_Heat;
	BOOL	m_Pets;
	BOOL	m_Electricity;
	BOOL	m_FurnitureMoving;
	BOOL	m_NewPaint;
	BOOL	m_Removal;
	BOOL	m_PavedDriveway;
	BOOL	m_Garage;
	BOOL	m_Elevator;
	CString	m_Disposal;
	CString	m_Access;
	CString	m_SiteType;
	CString	m_MetalColor;

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


