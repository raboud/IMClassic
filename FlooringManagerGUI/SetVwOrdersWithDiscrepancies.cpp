// SetVwOrdersWithDiscrepancies.h : Implementation of the CSetVwOrdersWithDiscrepancies class



// CSetVwOrdersWithDiscrepancies implementation

// code generated on Tuesday, September 28, 2004, 1:29 PM

#include "stdafx.h"
#include "SetVwOrdersWithDiscrepancies.h"
IMPLEMENT_DYNAMIC(CSetVwOrdersWithDiscrepancies, CRecordset)

CSetVwOrdersWithDiscrepancies::CSetVwOrdersWithDiscrepancies(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OrderID = 0;
	m_nFields = 1;
	m_nDefaultType = dynaset;
}

CString CSetVwOrdersWithDiscrepancies::GetDefaultSQL()
{
	return _T("[dbo].[vwOrdersWithAlerts]");
}

void CSetVwOrdersWithDiscrepancies::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwOrdersWithDiscrepancies diagnostics

#ifdef _DEBUG
void CSetVwOrdersWithDiscrepancies::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwOrdersWithDiscrepancies::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


