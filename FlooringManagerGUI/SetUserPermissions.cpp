// SetUserPermissions.h : Implementation of the CSetUserPermissions class



// CSetUserPermissions implementation

// code generated on Wednesday, March 12, 2003, 10:20 AM

#include "stdafx.h"
#include "SetUserPermissions.h"
IMPLEMENT_DYNAMIC(CSetUserPermissions, CRecordset)

CSetUserPermissions::CSetUserPermissions(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_UserID = 0;
	m_Market = 0;
	m_Division = 0;
	m_PermissionID = 0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CSetUserPermissions::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetUserPermissions::GetDefaultSQL()
{
	return _T("[dbo].[UserPermissions]");
}

void CSetUserPermissions::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Long(pFX, _T("[Market]"), m_Market);
	RFX_Long(pFX, _T("[Division]"), m_Division);
	RFX_Long(pFX, _T("[PermissionID]"), m_PermissionID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetUserPermissions diagnostics

#ifdef _DEBUG
void CSetUserPermissions::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUserPermissions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


