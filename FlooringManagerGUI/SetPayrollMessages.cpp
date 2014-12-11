// SetPayrollMessages.h : Implementation of the CSetPayrollMessages class



// CSetPayrollMessages implementation

// code generated on Thursday, August 21, 2003, 11:09 AM

#include "stdafx.h"
#include "SetPayrollMessages.h"
IMPLEMENT_DYNAMIC(CSetPayrollMessages, CRecordset)

CSetPayrollMessages::CSetPayrollMessages(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Message = _T("");
	m_StartDate;
	m_EndDate;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetPayrollMessages::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetPayrollMessages::GetDefaultSQL()
{
	return _T("[dbo].[PayrollMessages]");
}

void CSetPayrollMessages::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Message]"), m_Message);
	RFX_Date(pFX, _T("[StartDate]"), m_StartDate);
	RFX_Date(pFX, _T("[EndDate]"), m_EndDate);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPayrollMessages diagnostics

#ifdef _DEBUG
void CSetPayrollMessages::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPayrollMessages::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


