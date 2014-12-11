// SetMeasureCompCalcData.h : Implementation of the CSetMeasureCompCalcData class



// CSetMeasureCompCalcData implementation

// code generated on Monday, April 12, 2004, 7:11 PM

#include "stdafx.h"
#include "SetMeasureCompCalcData.h"
IMPLEMENT_DYNAMIC(CSetMeasureCompCalcData, CRecordset)

CSetMeasureCompCalcData::CSetMeasureCompCalcData(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	//m_CalcTimeStamp = _T("");
	m_Assigned = FALSE;
	m_Identity = _T("");
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CSetMeasureCompCalcData::GetDefaultSQL()
{
	return _T("[dbo].[MeasureCompCalcData]");
}

void CSetMeasureCompCalcData::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Date(pFX, _T("[CalcTimeStamp]"), m_CalcTimeStamp);
	RFX_Bool(pFX, _T("[Assigned]"), m_Assigned);
	RFX_Text(pFX, _T("@@IDENTITY"), m_Identity);

}
/////////////////////////////////////////////////////////////////////////////
// CSetMeasureCompCalcData diagnostics

#ifdef _DEBUG
void CSetMeasureCompCalcData::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMeasureCompCalcData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


