// ContactTitles.h : Implementation of the CSetContactTitles class



// CSetContactTitles implementation

// code generated on Monday, January 26, 2004, 1:22 PM

#include "stdafx.h"
#include "SetContactTitles.h"
IMPLEMENT_DYNAMIC(CSetContactTitles, CRecordset)

CSetContactTitles::CSetContactTitles(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Title = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CSetContactTitles::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetContactTitles::GetDefaultSQL()
{
	return _T("[dbo].[ContactTitles]");
}

void CSetContactTitles::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[Title]"), m_Title);

}
/////////////////////////////////////////////////////////////////////////////
// CSetContactTitles diagnostics

#ifdef _DEBUG
void CSetContactTitles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetContactTitles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


