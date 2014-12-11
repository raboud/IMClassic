// SetIssueTypes.h : Implementation of the CSetIssueTypes class



// CSetIssueTypes implementation

// code generated on Monday, January 24, 2005, 4:35 PM

#include "stdafx.h"
#include "SetIssueTypes.h"
IMPLEMENT_DYNAMIC(CSetIssueTypes, CRecordset)

CSetIssueTypes::CSetIssueTypes(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_IssueType = _T("");
	m_DisplayOrder = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

CString CSetIssueTypes::GetDefaultSQL()
{
	return _T("[dbo].[IssueTypes]");
}

void CSetIssueTypes::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[IssueType]"), m_IssueType);
	RFX_Long(pFX, _T("[DisplayOrder]"), m_DisplayOrder);

}
/////////////////////////////////////////////////////////////////////////////
// CSetIssueTypes diagnostics

#ifdef _DEBUG
void CSetIssueTypes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetIssueTypes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


