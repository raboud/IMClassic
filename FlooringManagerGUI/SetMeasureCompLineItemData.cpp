// SetMeasureCompLineItemData.h : Implementation of the CSetMeasureCompLineItemData class



// CSetMeasureCompLineItemData implementation

// code generated on Monday, April 12, 2004, 7:10 PM

#include "stdafx.h"
#include "SetMeasureCompLineItemData.h"
IMPLEMENT_DYNAMIC(CSetMeasureCompLineItemData, CRecordset)

CSetMeasureCompLineItemData::CSetMeasureCompLineItemData(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_CalcID = 0;
	m_LineItemNumber = 0;
	m_MaterialType = "";
	m_MaterialDescription = "";
	m_MaterialWidth = 0;
	m_PatternMatch = "";
	m_MaterialAmount = "";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CSetMeasureCompLineItemData::GetDefaultSQL()
{
	return _T("[dbo].[MeasureCompLineItemData]");
}

void CSetMeasureCompLineItemData::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[CalcID]"), m_CalcID);
	RFX_Long(pFX, _T("[LineItemNumber]"), m_LineItemNumber);
	RFX_Text(pFX, _T("[MaterialType]"), m_MaterialType);
	RFX_Text(pFX, _T("[MaterialDescription]"), m_MaterialDescription);
	RFX_Long(pFX, _T("[MaterialWidth]"), m_MaterialWidth);
	RFX_Text(pFX, _T("[PatternMatch]"), m_PatternMatch);
	RFX_Text(pFX, _T("[MaterialAmount]"), m_MaterialAmount);

}
/////////////////////////////////////////////////////////////////////////////
// CSetMeasureCompLineItemData diagnostics

#ifdef _DEBUG
void CSetMeasureCompLineItemData::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMeasureCompLineItemData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


