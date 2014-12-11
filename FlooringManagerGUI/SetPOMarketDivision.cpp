// SetPOMarketDivision.h : Implementation of the CSetPOMarketDivision class



// CSetPOMarketDivision implementation

// code generated on Thursday, January 16, 2003, 7:45 PM

#include "stdafx.h"
#include "SetPOMarketDivision.h"
IMPLEMENT_DYNAMIC(CSetPOMarketDivision, CRecordset)

CSetPOMarketDivision::CSetPOMarketDivision(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PurchaseOrderNumber = "";
	m_Division = "";
	m_Market = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

CString CSetPOMarketDivision::GetDefaultSQL()
{
	return _T("[dbo].[vwPOMarketDivision]");
}

void CSetPOMarketDivision::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	RFX_Text(pFX, _T("[Market]"), m_Market);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPOMarketDivision diagnostics

#ifdef _DEBUG
void CSetPOMarketDivision::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPOMarketDivision::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


