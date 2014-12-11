// SetScheduleChangeReasonCodes.h : Implementation of the CSetScheduleChangeReasonCodes class



// CSetScheduleChangeReasonCodes implementation

// code generated on Thursday, October 20, 2005, 11:36 AM

#include "stdafx.h"
#include "SetScheduleChangeReasonCodes.h"
IMPLEMENT_DYNAMIC(CSetScheduleChangeReasonCodes, CRecordset)

CSetScheduleChangeReasonCodes::CSetScheduleChangeReasonCodes(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_ReasonText = L"";
	m_Measure = FALSE;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

CString CSetScheduleChangeReasonCodes::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetScheduleChangeReasonCodes::GetDefaultSQL()
{
	return _T("[dbo].[ScheduleChangeReasonCodes]");
}

void CSetScheduleChangeReasonCodes::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[ReasonText]"), m_ReasonText);
	RFX_Bool(pFX, _T("[Measure]"), m_Measure);

}
/////////////////////////////////////////////////////////////////////////////
// CSetScheduleChangeReasonCodes diagnostics

#ifdef _DEBUG
void CSetScheduleChangeReasonCodes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetScheduleChangeReasonCodes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


