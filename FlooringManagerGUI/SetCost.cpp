/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCost.h : Implementation of the CSetCost class



// CSetCost implementation

// code generated on Friday, February 15, 2002, 10:03 PM

#include "stdafx.h"
#include "SetCost.h"
IMPLEMENT_DYNAMIC(CSetCost, CRecordset)

CSetCost::CSetCost(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CostID = 0;
	m_StartDate;
	m_EndDate;
	m_Description = "";
	m_Cost = 0.0;
	m_MarketID = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSetCost::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
//	return _T("DSN=Flooring;UID=sa;PWD=s3afa182;APP=Microsoft\x00ae Visual Studio .NET;WSID=FLOORING-NB;DATABASE=Flooring;Network=DBMSSOCN;Address=64.90.4.102");
}

CString CSetCost::GetDefaultSQL()
{
	return _T("[dbo].[Cost]");
}

void CSetCost::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[CostID]"), m_CostID);
	RFX_Date(pFX, _T("[StartDate]"), m_StartDate);
	RFX_Date(pFX, _T("[EndDate]"), m_EndDate);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Double(pFX, _T("[Cost]"), m_Cost);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetCost diagnostics

#ifdef _DEBUG
void CSetCost::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCost::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


