// SetIssueStatus.h : Implementation of the CSetIssueStatus class



// CSetIssueStatus implementation

// code generated on Monday, January 24, 2005, 4:37 PM

#include "stdafx.h"
#include "SetIssueStatus.h"
IMPLEMENT_DYNAMIC(CSetIssueStatus, CRecordset)

CSetIssueStatus::CSetIssueStatus(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_StatusDesc = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CSetIssueStatus::GetDefaultSQL()
{
	return _T("[dbo].[IssueStatus]");
}

void CSetIssueStatus::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[StatusDesc]"), m_StatusDesc);

}
/////////////////////////////////////////////////////////////////////////////
// CSetIssueStatus diagnostics

#ifdef _DEBUG
void CSetIssueStatus::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetIssueStatus::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


