// SetViewUserPermissions.h : Implementation of the CSetViewUserPermissions class



// CSetViewUserPermissions implementation

// code generated on Wednesday, March 12, 2003, 10:24 AM

#include "stdafx.h"
#include "flooring.h"
#include "SetViewUserPermissions.h"
IMPLEMENT_DYNAMIC(CSetViewUserPermissions, CRecordset)

CSetViewUserPermissions::CSetViewUserPermissions(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_MarketName = _T("");
	m_DivisionName = _T("");
	m_Market = 0;
	m_Division = 0;
	m_PermissionID = 0;
	m_PermissionName = _T("");
	m_PermissionType = 0;
	m_nFields = 10;
	m_nDefaultType = dynaset;
}

CString CSetViewUserPermissions::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetViewUserPermissions::GetDefaultSQL()
{
	return _T("[dbo].[vwUserPermissions]");
}

void CSetViewUserPermissions::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	RFX_Text(pFX, _T("[DivisionName]"), m_DivisionName);
	RFX_Long(pFX, _T("[Market]"), m_Market);
	RFX_Long(pFX, _T("[Division]"), m_Division);
	RFX_Long(pFX, _T("[PermissionID]"), m_PermissionID);
	RFX_Text(pFX, _T("[PermissionName]"), m_PermissionName);
	RFX_Long(pFX, _T("[PermissionType]"), m_PermissionType);

}
/////////////////////////////////////////////////////////////////////////////
// CSetViewUserPermissions diagnostics

#ifdef _DEBUG
void CSetViewUserPermissions::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetViewUserPermissions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


