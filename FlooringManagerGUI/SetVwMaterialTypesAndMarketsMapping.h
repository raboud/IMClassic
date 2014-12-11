// SetVwMaterialTypesAndMarketsMapping.h : Declaration of the CSetVwMaterialTypesAndMarketsMapping

#pragma once

// code generated on Monday, August 11, 2003, 6:33 PM

class CSetVwMaterialTypesAndMarketsMapping : public CRecordset
{
public:
	CSetVwMaterialTypesAndMarketsMapping(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetVwMaterialTypesAndMarketsMapping)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_MaterialTypeID;
	CString	m_MaterialTypeName;
	long	m_StoreTypeID;
	BOOL	m_Active;
	long	m_MarketID;
	CString	m_MarketName;
	long	m_DivisionID;
	CString	m_ShortName;

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


