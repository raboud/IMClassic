// SetSPNImportedPOs.h : Implementation of the CSetSPNImportedPOs class



// CSetSPNImportedPOs implementation

// code generated on Sunday, February 01, 2004, 5:21 PM

#include "stdafx.h"
#include "SetSPNImportedPOs.h"
IMPLEMENT_DYNAMIC(CSetSPNImportedPOs, CRecordset)

CSetSPNImportedPOs::CSetSPNImportedPOs(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_PONumber = "";
	m_StoreID = 0;
	m_POStatusID = 0;
	m_XMLFilePath = "";
	m_DateImported;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}

CString CSetSPNImportedPOs::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetSPNImportedPOs::GetDefaultSQL()
{
	return _T("[dbo].[SPNImportedPOs]");
}

void CSetSPNImportedPOs::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[PONumber]"), m_PONumber);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Long(pFX, _T("[POStatusID]"), m_POStatusID);
	RFX_Text(pFX, _T("[XMLFilePath]"), m_XMLFilePath, 1024);
	RFX_Date(pFX, _T("[DateImported]"), m_DateImported);

}
/////////////////////////////////////////////////////////////////////////////
// CSetSPNImportedPOs diagnostics

#ifdef _DEBUG
void CSetSPNImportedPOs::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetSPNImportedPOs::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


