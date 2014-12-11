// SetNoteTypes.h : Implementation of the CSetNoteTypes class



// CSetNoteTypes implementation

// code generated on Tuesday, August 23, 2005, 4:13 PM

#include "stdafx.h"
#include "SetNoteTypes.h"
IMPLEMENT_DYNAMIC(CSetNoteTypes, CRecordset)

CSetNoteTypes::CSetNoteTypes(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_NoteTypeDescription = L"";
	m_ShowInList = FALSE;
	m_RequireSpokeWith = FALSE;
	m_ShowEmployees = FALSE;
	m_ShowSpokeWith = FALSE;
	m_EnableSchedulingInfo = FALSE;
	m_CanSendToExpeditor = FALSE;
	m_ShowStoreManagement = FALSE;
	m_PermissionRequiredToSelect = FALSE;
	m_DisplayOrder = 0;
	m_nFields = 11;
	m_nDefaultType = dynaset;
}
CString CSetNoteTypes::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetNoteTypes::GetDefaultSQL()
{
	return _T("[dbo].[NoteTypes]");
}

void CSetNoteTypes::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[NoteTypeDescription]"), m_NoteTypeDescription);
	RFX_Bool(pFX, _T("[ShowInList]"), m_ShowInList);
	RFX_Bool(pFX, _T("[RequireSpokeWith]"), m_RequireSpokeWith);
	RFX_Bool(pFX, _T("[ShowEmployees]"), m_ShowEmployees);
	RFX_Bool(pFX, _T("[ShowSpokeWith]"), m_ShowSpokeWith);
	RFX_Bool(pFX, _T("[EnableSchedulingInfo]"), m_EnableSchedulingInfo);
	RFX_Bool(pFX, _T("[CanSendToExpeditor]"), m_CanSendToExpeditor);
	RFX_Bool(pFX, _T("[ShowStoreManagement]"), m_ShowStoreManagement);
	RFX_Bool(pFX, _T("[PermissionRequiredToSelect]"), m_PermissionRequiredToSelect);
	RFX_Int(pFX, _T("[DisplayOrder]"), m_DisplayOrder);
}
/////////////////////////////////////////////////////////////////////////////
// CSetNoteTypes diagnostics

#ifdef _DEBUG
void CSetNoteTypes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNoteTypes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


