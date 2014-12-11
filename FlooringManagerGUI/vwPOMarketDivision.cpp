// vwPOMarketDivision.h : Implementation of the CvwPOMarketDivision class



// CvwPOMarketDivision implementation

// code generated on Saturday, May 31, 2003, 1:04 PM

#include "stdafx.h"
#include "vwPOMarketDivision.h"
IMPLEMENT_DYNAMIC(CvwPOMarketDivision, CRecordset)

CvwPOMarketDivision::CvwPOMarketDivision(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PurchaseOrderNumber = "";
	m_Market = "";
	m_Division = "";
	m_FirstName = "";
	m_OrderID = 0;
	m_LastName = "";
	m_StoreNumber = "";
	m_nFields = 7;
	m_nDefaultType = dynaset;
}

CString CvwPOMarketDivision::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CvwPOMarketDivision::GetDefaultSQL()
{
	return _T("[dbo].[vwPOMarketDivision]");
}

void CvwPOMarketDivision::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[Market]"), m_Market);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);

}
/////////////////////////////////////////////////////////////////////////////
// CvwPOMarketDivision diagnostics

#ifdef _DEBUG
void CvwPOMarketDivision::AssertValid() const
{
	CRecordset::AssertValid();
}

void CvwPOMarketDivision::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


