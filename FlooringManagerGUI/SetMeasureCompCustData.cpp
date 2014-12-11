// SetMeasureCompCustData.h : Implementation of the CSetMeasureCompCustData class



// CSetMeasureCompCustData implementation

// code generated on Friday, April 09, 2004, 1:17 AM

#include "stdafx.h"
#include "SetMeasureCompCustData.h"
IMPLEMENT_DYNAMIC(CSetMeasureCompCustData, CRecordset)

CSetMeasureCompCustData::CSetMeasureCompCustData(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_CustomerID = 0;
	m_LastName = "";
	m_FirstName = "";
	m_Address1 = "";
	m_Address2 = "";
	m_City = "";
	m_State = "";
	m_Zip = "";
	m_HomePhone = "";
	m_BusinessPhone = "";
	m_CellPhone = "";
	m_Pager = "";
	m_CrossStreetDir1 = "";
	m_CrossStreet1 = "";
	m_CrossStreetDir2 = "";
	m_CrossStreet2 = "";
	this->m_EmailAddress = "";
	m_nFields = 18;
	m_nDefaultType = dynaset;
}

CString CSetMeasureCompCustData::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetMeasureCompCustData::GetDefaultSQL()
{
	return _T("[dbo].[MeasureCompCustData]");
}

void CSetMeasureCompCustData::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[Address1]"), m_Address1);
	RFX_Text(pFX, _T("[Address2]"), m_Address2);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[Zip]"), m_Zip);
	RFX_Text(pFX, _T("[HomePhone]"), m_HomePhone);
	RFX_Text(pFX, _T("[BusinessPhone]"), m_BusinessPhone);
	RFX_Text(pFX, _T("[CellPhone]"), m_CellPhone);
	RFX_Text(pFX, _T("[Pager]"), m_Pager);
	RFX_Text(pFX, _T("[CrossStreetDir1]"), m_CrossStreetDir1);
	RFX_Text(pFX, _T("[CrossStreet1]"), m_CrossStreet1);
	RFX_Text(pFX, _T("[CrossStreetDir2]"), m_CrossStreetDir2);
	RFX_Text(pFX, _T("[CrossStreet2]"), m_CrossStreet2);
	RFX_Text(pFX, _T("[EmailAddress]"), this->m_EmailAddress);

}
/////////////////////////////////////////////////////////////////////////////
// CSetMeasureCompCustData diagnostics

#ifdef _DEBUG
void CSetMeasureCompCustData::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMeasureCompCustData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


