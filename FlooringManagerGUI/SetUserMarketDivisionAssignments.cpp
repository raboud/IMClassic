// SetUserMarketDivisionAssignments.h : Implementation of the CSetUserMarketDivisionAssignments class



// CSetUserMarketDivisionAssignments implementation

// code generated on Wednesday, August 18, 2004, 7:17 PM

#include "stdafx.h"
#include "SetUserMarketDivisionAssignments.h"
IMPLEMENT_DYNAMIC(CSetUserMarketDivisionAssignments, CRecordset)

CSetUserMarketDivisionAssignments::CSetUserMarketDivisionAssignments(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_UserID = 0;
	m_MarketID = 0;
	m_DivisionID = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetUserMarketDivisionAssignments::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetUserMarketDivisionAssignments::GetDefaultSQL()
{
	return _T("[dbo].[UserMarketDivisionAssignments]");
}

void CSetUserMarketDivisionAssignments::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetUserMarketDivisionAssignments diagnostics

#ifdef _DEBUG
void CSetUserMarketDivisionAssignments::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUserMarketDivisionAssignments::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


