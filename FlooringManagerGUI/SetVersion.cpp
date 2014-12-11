// SetVersion.h : Implementation of the CSetVersion class



// CSetVersion implementation

// code generated on Wednesday, May 01, 2002, 12:47 AM

#include "stdafx.h"
#include "SetVersion.h"
IMPLEMENT_DYNAMIC(CSetVersion, CRecordset)

CSetVersion::CSetVersion(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_VersionNo = 0;
	m_MinimumVersionMajor = 0;
	m_MinimumVersionMinor = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

CString CSetVersion::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetVersion::GetDefaultSQL()
{
	return _T("[dbo].[Version]");
}

void CSetVersion::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[VersionNo]"), m_VersionNo);
	RFX_Long(pFX, _T("[MinimumVersionMajor]"), m_MinimumVersionMajor);
	RFX_Long(pFX, _T("[MinimumVersionMinor]"), m_MinimumVersionMinor);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVersion diagnostics

#ifdef _DEBUG
void CSetVersion::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVersion::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


