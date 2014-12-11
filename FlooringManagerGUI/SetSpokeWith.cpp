// SetSpokeWith.h : Implementation of the CSetSpokeWith class



// CSetSpokeWith implementation

// code generated on Monday, August 29, 2005, 4:17 PM

#include "stdafx.h"
#include "SetSpokeWith.h"
IMPLEMENT_DYNAMIC(CSetSpokeWith, CRecordset)

CSetSpokeWith::CSetSpokeWith(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SpokeWith = 0;
	m_SW_Text = "";
	m_ShowAlways = FALSE;
	m_EnableSchedulingInfo = FALSE;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetSpokeWith::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetSpokeWith::GetDefaultSQL()
{
	return _T("[dbo].[SpokeWith]");
}

void CSetSpokeWith::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[SpokeWith]"), m_SpokeWith);
	RFX_Text(pFX, _T("[SW_Text]"), m_SW_Text);
	RFX_Bool(pFX, _T("[ShowAlways]"), m_ShowAlways);
	RFX_Bool(pFX, _T("[EnableSchedulingInfo]"), m_EnableSchedulingInfo);
}
/////////////////////////////////////////////////////////////////////////////
// CSetSpokeWith diagnostics

#ifdef _DEBUG
void CSetSpokeWith::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetSpokeWith::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


