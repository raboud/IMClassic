// Departments.h : Implementation of the CSetDepartments class



// CSetDepartments implementation

// code generated on Monday, January 26, 2004, 1:19 PM

#include "stdafx.h"
#include "SetDepartments.h"
IMPLEMENT_DYNAMIC(CSetDepartments, CRecordset)

CSetDepartments::CSetDepartments(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_DepartmentName = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CSetDepartments::GetDefaultSQL()
{
	return _T("[dbo].[Departments]");
}

void CSetDepartments::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[DepartmentName]"), m_DepartmentName);

}
/////////////////////////////////////////////////////////////////////////////
// CSetDepartments diagnostics

#ifdef _DEBUG
void CSetDepartments::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDepartments::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


