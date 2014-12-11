// SetEmployees.h : Implementation of the CSetEmployees class



// CSetEmployees implementation

// code generated on Sunday, January 26, 2003, 2:14 PM

#include "stdafx.h"
#include "SetEmployees.h"
IMPLEMENT_DYNAMIC(CSetEmployees, CRecordset)

CSetEmployees::CSetEmployees(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	//m_uid = 0;
	m_FirstName    = _T("");
	m_LastName     = _T("");
	m_NickName     = _T("");
	m_Address1     = _T("");
	m_Address2     = _T("");
	m_City         = _T("");
	m_State        = _T("");
	m_Zip          = _T("");
	m_HomeNumber   = _T("");
	m_MobileNumber = _T("");
	m_PagerNumber  = _T("");
	m_SSN          = _T("");
	m_Email        = _T("");
	m_UserName     = _T("");
	m_HireDate;
	m_ReceiveCallNotes = FALSE;
	m_SMTPEmail = _T("");
	m_nFields = 18;
	m_nDefaultType = dynaset;
}

CString CSetEmployees::GetDefaultSQL()
{
	return _T("[dbo].[Employees]");
}

void CSetEmployees::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[NickName]"), m_NickName);
	RFX_Text(pFX, _T("[Address1]"), m_Address1);
	RFX_Text(pFX, _T("[Address2]"), m_Address2);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[Zip]"), m_Zip);
	RFX_Text(pFX, _T("[HomeNumber]"), m_HomeNumber);
	RFX_Text(pFX, _T("[MobileNumber]"), m_MobileNumber);
	RFX_Text(pFX, _T("[PagerNumber]"), m_PagerNumber);
	RFX_Text(pFX, _T("[SSN]"), m_SSN);
	RFX_Text(pFX, _T("[Email]"), m_Email);
	RFX_Date(pFX, _T("[HireDate]"), m_HireDate);
	RFX_Bool(pFX, _T("[ReceiveCallNotes]"), m_ReceiveCallNotes);
	RFX_Text(pFX, _T("[SMTPEmail]"), m_SMTPEmail);
	RFX_Text(pFX, _T("[UserName]"), m_UserName);

}
/////////////////////////////////////////////////////////////////////////////
// CSetEmployees diagnostics

#ifdef _DEBUG
void CSetEmployees::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetEmployees::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


