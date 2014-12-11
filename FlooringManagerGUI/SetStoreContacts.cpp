// SetStoreContacts.h : Implementation of the CSetStoreContacts class



// CSetStoreContacts implementation

// code generated on Tuesday, September 16, 2003, 12:20 PM

#include "stdafx.h"
#include "SetStoreContacts.h"
IMPLEMENT_DYNAMIC(CSetStoreContacts, CRecordset)

CSetStoreContacts::CSetStoreContacts(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_StoreID = 0;
	m_DepartmentID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_TitleID = 0;
	m_PhoneNumber = _T("");
	m_AltPhoneNumber = _T("");
	m_EmailAddress = _T("");
	m_EmailStatusReport = FALSE;
	m_nFields = 10;
	m_nDefaultType = dynaset;
}

CString CSetStoreContacts::GetDefaultSQL()
{
	return _T("[dbo].[StoreContacts]");
}

void CSetStoreContacts::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Long(pFX, _T("[DepartmentID]"), m_DepartmentID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Long(pFX, _T("[TitleID]"), m_TitleID);
	RFX_Text(pFX, _T("[PhoneNumber]"), m_PhoneNumber);
	RFX_Text(pFX, _T("[AltPhoneNumber]"), m_AltPhoneNumber);
	RFX_Text(pFX, _T("[EmailAddress]"), m_EmailAddress);
	RFX_Bool(pFX, _T("[EmailStatusReport]"), m_EmailStatusReport);


}
/////////////////////////////////////////////////////////////////////////////
// CSetStoreContacts diagnostics

#ifdef _DEBUG
void CSetStoreContacts::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetStoreContacts::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


