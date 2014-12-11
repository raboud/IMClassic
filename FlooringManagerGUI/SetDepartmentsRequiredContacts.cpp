// DepartmentsRequiredContacts.h : Implementation of the CSetDepartmentsRequiredContacts class



// CSetDepartmentsRequiredContacts implementation

// code generated on Monday, January 26, 2004, 1:25 PM

#include "stdafx.h"
#include "SetDepartmentsRequiredContacts.h"
IMPLEMENT_DYNAMIC(CSetDepartmentsRequiredContacts, CRecordset)

CSetDepartmentsRequiredContacts::CSetDepartmentsRequiredContacts(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_StoreTypeID = 0;
	m_DepartmentID = 0;
	m_TitleID = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetDepartmentsRequiredContacts::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetDepartmentsRequiredContacts::GetDefaultSQL()
{
	return _T("[dbo].[DepartmentsRequiredContacts]");
}

void CSetDepartmentsRequiredContacts::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[StoreTypeID]"), m_StoreTypeID);
	RFX_Long(pFX, _T("[DepartmentID]"), m_DepartmentID);
	RFX_Long(pFX, _T("[TitleID]"), m_TitleID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetDepartmentsRequiredContacts diagnostics

#ifdef _DEBUG
void CSetDepartmentsRequiredContacts::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDepartmentsRequiredContacts::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


