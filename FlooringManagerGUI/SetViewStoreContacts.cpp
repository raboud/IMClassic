// SetViewStoreContacts.h : Implementation of the CSetViewStoreContacts class



// CSetViewStoreContacts implementation

// code generated on Monday, January 26, 2004, 5:19 PM

#include "stdafx.h"
#include "SetViewStoreContacts.h"
IMPLEMENT_DYNAMIC(CSetViewStoreContacts, CRecordset)

CSetViewStoreContacts::CSetViewStoreContacts(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_StoreContactsID = 0;
	m_DepartmentStoreID = 0;
	m_StoreID = 0;
	m_DepartmentID = 0;
	m_DepartmentName = _T("");
	m_Title = _T("");
	m_FirstName = _T("");
	m_LastName = _T("");
	m_PhoneNumber = _T("");
	m_FaxNumber = _T("");
	m_AltFaxNumber = _T("");
	m_FaxStatusReportTo = 0;
	m_StoreNumber = _T("");
	m_Active = FALSE;
	m_EmailAddress = _T("");
	m_EmailStatusReport = FALSE;
	m_nFields = 16;
	m_nDefaultType = dynaset;
}

CString CSetViewStoreContacts::GetDefaultSQL()
{
	return _T("[dbo].[vwStoreContacts]");
}

void CSetViewStoreContacts::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[StoreContactsID]"), m_StoreContactsID);
	RFX_Long(pFX, _T("[DepartmentStoreID]"), m_DepartmentStoreID);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Long(pFX, _T("[DepartmentID]"), m_DepartmentID);
	RFX_Text(pFX, _T("[DepartmentName]"), m_DepartmentName);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[PhoneNumber]"), m_PhoneNumber);
	RFX_Text(pFX, _T("[FaxNumber]"), m_FaxNumber);
	RFX_Text(pFX, _T("[AltFaxNumber]"), m_AltFaxNumber);
	RFX_Long(pFX, _T("[FaxStatusReportTo]"), m_FaxStatusReportTo);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Bool(pFX, _T("[Active]"), m_Active);
	RFX_Text(pFX, _T("[EmailAddress]"), m_EmailAddress);
	RFX_Bool(pFX, _T("[EmailStatusReport]"), m_EmailStatusReport);

}
/////////////////////////////////////////////////////////////////////////////
// CSetViewStoreContacts diagnostics

#ifdef _DEBUG
void CSetViewStoreContacts::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetViewStoreContacts::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


