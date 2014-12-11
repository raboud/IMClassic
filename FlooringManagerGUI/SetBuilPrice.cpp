/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetBuilPrice.h : Implementation of the CSetBuilPrice class

// CSetBuilPrice implementation

// code generated on Saturday, February 16, 2002, 2:56 PM

#include "stdafx.h"
#include "SetBuilPrice.h"
IMPLEMENT_DYNAMIC(CSetBuilPrice, CRecordset)

CSetBuilPrice::CSetBuilPrice(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_MaterialID = 0;
	m_UnitPrice = 0.0;
	m_UnitRetail = 0.0;
	m_MarketId = 0;
	m_OrderDate;
	m_PriceID = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSetBuilPrice::GetDefaultConnect()
{
//	return _T("DSN=Flooring;APP=Microsoft\x00ae Visual Studio .NET;WSID=FLOORING-NB;DATABASE=Flooring;Trusted_Connection=Yes");
	return _T("ODBC;DSN=Flooring");
}

CString CSetBuilPrice::GetDefaultSQL()
{
	return _T("[dbo].[BuilPrice]");
}

void CSetBuilPrice::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[MaterialID]"), m_MaterialID);
	RFX_Double(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Double(pFX, _T("[UnitRetail]"), m_UnitRetail);
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Long(pFX, _T("[PriceID]"), m_PriceID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetBuilPrice diagnostics

#ifdef _DEBUG
void CSetBuilPrice::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetBuilPrice::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


