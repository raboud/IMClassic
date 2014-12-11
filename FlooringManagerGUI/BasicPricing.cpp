/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// BasicPricing.h : Implementation of the CBasicPricing class
// CBasicPricing implementation

// code generated on Thursday, October 24, 2002, 8:04 AM

#include "stdafx.h"
#include "BasicPricing.h"
IMPLEMENT_DYNAMIC(CBasicPricing, CRecordset)

CBasicPricing::CBasicPricing(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_BasicPricingID = 0;
	m_BasicLaborID = 0;
	m_MarketID = 0;
	m_StoreID = 0;
	m_Price = 0.0;
	m_Cost = 0.0;
	m_StartDate;
	m_EndDate;
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CBasicPricing::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CBasicPricing::GetDefaultSQL()
{
	return _T("[dbo].[BasicPricing]");
}

void CBasicPricing::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[BasicPricingID]"), m_BasicPricingID);
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Double(pFX, _T("[Price]"), m_Price);
	RFX_Double(pFX, _T("[Cost]"), m_Cost);
	RFX_Date(pFX, _T("[StartDate]"), m_StartDate);
	RFX_Date(pFX, _T("[EndDate]"), m_EndDate);

}
/////////////////////////////////////////////////////////////////////////////
// CBasicPricing diagnostics

#ifdef _DEBUG
void CBasicPricing::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBasicPricing::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


