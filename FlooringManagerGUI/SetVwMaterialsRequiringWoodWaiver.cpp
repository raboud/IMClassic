// SetVwMaterialsRequiringWoodWaiver.h : Implementation of the CSetVwMaterialsRequiringWoodWaiver class



// CSetVwMaterialsRequiringWoodWaiver implementation

// code generated on Tuesday, February 21, 2012, 1:26 PM

#include "stdafx.h"
#include "SetVwMaterialsRequiringWoodWaiver.h"
IMPLEMENT_DYNAMIC(CSetVwMaterialsRequiringWoodWaiver, CRecordset)

CSetVwMaterialsRequiringWoodWaiver::CSetVwMaterialsRequiringWoodWaiver(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_MaterialTypeID = 0;
	m_nFields = 1;
	m_nDefaultType = dynaset;
}

CString CSetVwMaterialsRequiringWoodWaiver::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetVwMaterialsRequiringWoodWaiver::GetDefaultSQL()
{
	return _T("[dbo].[vwMaterialsRequiringWoodWaiver]");
}

void CSetVwMaterialsRequiringWoodWaiver::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwMaterialsRequiringWoodWaiver diagnostics

#ifdef _DEBUG
void CSetVwMaterialsRequiringWoodWaiver::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwMaterialsRequiringWoodWaiver::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


