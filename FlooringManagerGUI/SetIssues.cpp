// SetIssues.h : Implementation of the CSetIssues class



// CSetIssues implementation

// code generated on Monday, January 24, 2005, 4:38 PM

#include "stdafx.h"
#include "SetIssues.h"
IMPLEMENT_DYNAMIC(CSetIssues, CRecordset)

CSetIssues::CSetIssues(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_AddedByUser = 0;
	m_DateAdded;
	m_Description = _T("");
	m_StatusID = 0;
	m_StatusDate;
	m_Comment = L"";
	m_Identity = _T("");
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CSetIssues::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetIssues::GetDefaultSQL()
{
	return _T("[dbo].[Issues]");
}

void CSetIssues::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[AddedByUser]"), m_AddedByUser);
	RFX_Date(pFX, _T("[DateAdded]"), m_DateAdded);
	RFX_Text(pFX, _T("[Description]"), m_Description, 2048);
	RFX_Long(pFX, _T("[StatusID]"), m_StatusID);
	RFX_Date(pFX, _T("[StatusDate]"), m_StatusDate);
	RFX_Text(pFX, _T("[Comment]"), m_Comment);
	RFX_Text(pFX, _T("@@IDENTITY"), m_Identity);

}
/////////////////////////////////////////////////////////////////////////////
// CSetIssues diagnostics

#ifdef _DEBUG
void CSetIssues::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetIssues::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


