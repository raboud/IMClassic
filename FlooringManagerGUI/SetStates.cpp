// SetStates.h : Implementation of the CSetStates class

#include "stdafx.h"
#include "SetStates.h"
IMPLEMENT_DYNAMIC(CSetStates, CRecordset)

CSetStates::CSetStates(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = _T("");
	m_Abbreviation = _T("");
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

CString CSetStates::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetStates::GetDefaultSQL()
{
	return _T("[dbo].[States]");
}

void CSetStates::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Abbreviation]"), m_Abbreviation);

}
/////////////////////////////////////////////////////////////////////////////
// CSetStates diagnostics

#ifdef _DEBUG
void CSetStates::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetStates::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


