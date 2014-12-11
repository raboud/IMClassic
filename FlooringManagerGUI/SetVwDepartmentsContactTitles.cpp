/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetSetVwDepartmentsContactTitles.h : Implementation of the CSetVwDepartmentsContactTitles class



// CSetVwDepartmentsContactTitles implementation

// code generated on Thursday, April 20, 2006, 11:08 AM

#include "stdafx.h"
#include "SetVwDepartmentsContactTitles.h"
IMPLEMENT_DYNAMIC(CSetVwDepartmentsContactTitles, CRecordset)

CSetVwDepartmentsContactTitles::CSetVwDepartmentsContactTitles(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DepartmentName = _T("");
	m_Title = _T("");
	m_DepartmentID = 0;
	m_ContactTitlesID = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetVwDepartmentsContactTitles::GetDefaultSQL()
{
	return _T("[dbo].[vwDepartmentsContactTitles]");
}

void CSetVwDepartmentsContactTitles::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[DepartmentName]"), m_DepartmentName);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Long(pFX, _T("[DepartmentID]"), m_DepartmentID);
	RFX_Long(pFX, _T("[ContactTitlesID]"), m_ContactTitlesID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwDepartmentsContactTitles diagnostics

#ifdef _DEBUG
void CSetVwDepartmentsContactTitles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwDepartmentsContactTitles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


