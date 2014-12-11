// SetPermissions.h : Implementation of the CSetPermissions class



// CSetPermissions implementation

// code generated on Wednesday, March 12, 2003, 10:19 AM

#include "stdafx.h"
#include "SetPermissions.h"
IMPLEMENT_DYNAMIC(CSetPermissions, CRecordset)

CSetPermissions::CSetPermissions(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_PermissionName = "";
	m_Description = "";
	m_PermissionType = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetPermissions::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetPermissions::GetDefaultSQL()
{
	return _T("[dbo].[Permissions]");
}

void CSetPermissions::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[PermissionName]"), m_PermissionName);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Long(pFX, _T("[PermissionType]"), m_PermissionType);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPermissions diagnostics

#ifdef _DEBUG
void CSetPermissions::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPermissions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


