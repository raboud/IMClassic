/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// OptionPricing.h : Implementation of the COptionPricing class
// COptionPricing implementation

// code generated on Thursday, October 24, 2002, 8:06 AM

#include "stdafx.h"
#include "OptionPricing.h"
IMPLEMENT_DYNAMIC(COptionPricing, CRecordset)

COptionPricing::COptionPricing(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OptionID = 0;
	m_MarketID = 0;
	m_StoreID = 0;
	m_Price = 0.0;
	m_Cost = 0.0;
	m_StartDate;
	m_EndDate;
	m_nFields = 7;
	m_nDefaultType = dynaset;
}

CString COptionPricing::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString COptionPricing::GetDefaultSQL()
{
	return _T("[dbo].[OptionPricing]");
}

void COptionPricing::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OptionID]"), m_OptionID);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Double(pFX, _T("[Price]"), m_Price);
	RFX_Double(pFX, _T("[Cost]"), m_Cost);
	RFX_Date(pFX, _T("[StartDate]"), m_StartDate);
	RFX_Date(pFX, _T("[EndDate]"), m_EndDate);

}
/////////////////////////////////////////////////////////////////////////////
// COptionPricing diagnostics

#ifdef _DEBUG
void COptionPricing::AssertValid() const
{
	CRecordset::AssertValid();
}

void COptionPricing::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


