// SetCompanyInfo.h : Implementation of the CSetCompanyInfo class



// CSetCompanyInfo implementation

// code generated on Friday, September 17, 2004, 3:53 PM

#include "stdafx.h"
#include "SetCompanyInfo.h"
IMPLEMENT_DYNAMIC(CSetCompanyInfo, CRecordset)

CSetCompanyInfo::CSetCompanyInfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = "";
	m_Address1 = "";
	m_Address2 = "";
	m_City = "";
	m_State = "";
	m_Zip = "";
	m_Phone1 = "";
	m_Phone2 = "";
	m_Fax1 = "";
	m_Fax2 = "";
	m_VendorNumber = "";
	m_nFields = 12;
	m_nDefaultType = dynaset;
}

CString CSetCompanyInfo::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetCompanyInfo::GetDefaultSQL()
{
	return _T("[dbo].[CompanyInfo]");
}

void CSetCompanyInfo::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[Address1]"), m_Address1);
	RFX_Text(pFX, _T("[Address2]"), m_Address2);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[Zip]"), m_Zip);
	RFX_Text(pFX, _T("[Phone1]"), m_Phone1);
	RFX_Text(pFX, _T("[Phone2]"), m_Phone2);
	RFX_Text(pFX, _T("[Fax1]"), m_Fax1);
	RFX_Text(pFX, _T("[Fax2]"), m_Fax2);
	RFX_Text(pFX, _T("[VendorNumber]"), m_VendorNumber);

}
/////////////////////////////////////////////////////////////////////////////
// CSetCompanyInfo diagnostics

#ifdef _DEBUG
void CSetCompanyInfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCompanyInfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


