/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetActivityTypes.h : Implementation of the CSetActivityTypes class



// CSetActivityTypes implementation

// code generated on Thursday, September 07, 2006, 3:51 PM

#include "stdafx.h"
#include "SetActivityTypes.h"
IMPLEMENT_DYNAMIC(CSetActivityTypes, CRecordset)

CSetActivityTypes::CSetActivityTypes(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = L"";
	m_Description = L"";
	m_RequirePermissionToView = FALSE;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetActivityTypes::GetDefaultSQL()
{
	return _T("[dbo].[ActivityTypes]");
}

void CSetActivityTypes::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Bool(pFX, _T("[RequirePermissionToView]"), m_RequirePermissionToView);

}
/////////////////////////////////////////////////////////////////////////////
// CSetActivityTypes diagnostics

#ifdef _DEBUG
void CSetActivityTypes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetActivityTypes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


