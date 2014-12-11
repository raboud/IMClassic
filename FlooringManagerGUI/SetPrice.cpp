/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetPrice.h : Implementation of the CSetPrice class



// CSetPrice implementation

// code generated on Saturday, February 16, 2002, 2:57 PM

#include "stdafx.h"
#include "SetPrice.h"
IMPLEMENT_DYNAMIC(CSetPrice, CRecordset)

CSetPrice::CSetPrice(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PriceID = 0;
	m_StartDate;
	m_EndDate;
	m_Retail = 0.0;
	m_Price = 0.0;
	m_MarketID = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSetPrice::GetDefaultConnect()
{
//	return _T("DSN=Flooring;APP=Microsoft\x00ae Visual Studio .NET;WSID=FLOORING-NB;DATABASE=Flooring;Trusted_Connection=Yes");
	return _T("ODBC;DSN=Flooring");
}

CString CSetPrice::GetDefaultSQL()
{
	return _T("[dbo].[Price]");
}

void CSetPrice::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[PriceID]"), m_PriceID);
	RFX_Date(pFX, _T("[StartDate]"), m_StartDate);
	RFX_Date(pFX, _T("[EndDate]"), m_EndDate);
	RFX_Double(pFX, _T("[Retail]"), m_Retail);
	RFX_Double(pFX, _T("[Price]"), m_Price);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPrice diagnostics

#ifdef _DEBUG
void CSetPrice::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPrice::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


