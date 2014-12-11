// SetDiscrepanciesPrice.h : Implementation of the CSetDiscrepanciesPrice class



// CSetDiscrepanciesPrice implementation

// code generated on Friday, July 23, 2004, 12:21 PM

#include "stdafx.h"
#include "SetDiscrepanciesPrice.h"
IMPLEMENT_DYNAMIC(CSetDiscrepanciesPrice, CRecordset)

CSetDiscrepanciesPrice::CSetDiscrepanciesPrice(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_DiscrepancyTypeID = 0;
	m_ItemID = 0;
	m_MarketID = 0;
	m_CurrentPrice = 0.0;
	m_NewPrice = 0.0;
	m_XMLFilePath = "";
	m_DateFound;
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CSetDiscrepanciesPrice::GetDefaultSQL()
{
	return _T("[dbo].[DiscrepanciesPrice]");
}

void CSetDiscrepanciesPrice::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[DiscrepancyTypeID]"), m_DiscrepancyTypeID);
	RFX_Long(pFX, _T("[ItemID]"), m_ItemID);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
	RFX_Double(pFX, _T("[CurrentPrice]"), m_CurrentPrice);
	RFX_Double(pFX, _T("[NewPrice]"), m_NewPrice);
	RFX_Text(pFX, _T("[XMLFilePath]"), m_XMLFilePath, 1024);
	RFX_Date(pFX, _T("[DateFound]"), m_DateFound);

}
/////////////////////////////////////////////////////////////////////////////
// CSetDiscrepanciesPrice diagnostics

#ifdef _DEBUG
void CSetDiscrepanciesPrice::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDiscrepanciesPrice::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


