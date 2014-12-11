// SetPOStatusValues.h : Implementation of the CSetPOStatusValues class



// CSetPOStatusValues implementation

// code generated on Sunday, February 01, 2004, 7:40 PM

#include "stdafx.h"
#include "SetPOStatusValues.h"
IMPLEMENT_DYNAMIC(CSetPOStatusValues, CRecordset)

CSetPOStatusValues::CSetPOStatusValues(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Description = _T("");
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CSetPOStatusValues::GetDefaultSQL()
{
	return _T("[dbo].[POStatusValues]");
}

void CSetPOStatusValues::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[Description]"), m_Description);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPOStatusValues diagnostics

#ifdef _DEBUG
void CSetPOStatusValues::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPOStatusValues::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


