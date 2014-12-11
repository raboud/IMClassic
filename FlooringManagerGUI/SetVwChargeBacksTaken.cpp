// SetVwChargeBacksTaken.h : Implementation of the CSetVwChargeBacksTaken class



// CSetVwChargeBacksTaken implementation

// code generated on Saturday, May 31, 2003, 1:40 PM

#include "stdafx.h"
#include "SetVwChargeBacksTaken.h"
IMPLEMENT_DYNAMIC(CSetVwChargeBacksTaken, CRecordset)

CSetVwChargeBacksTaken::CSetVwChargeBacksTaken(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ChargeBackID = 0;
	m_Amount = 0.0;
	m_CheckNumber = "";
	m_CheckDate;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetVwChargeBacksTaken::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetVwChargeBacksTaken::GetDefaultSQL()
{
	return _T("[dbo].[vwChargeBacksTaken]");
}

void CSetVwChargeBacksTaken::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ChargeBackID]"), m_ChargeBackID);
	RFX_Double(pFX, _T("[Amount]"), m_Amount);
	RFX_Text(pFX, _T("[CheckNumber]"), m_CheckNumber);
	RFX_Date(pFX, _T("[CheckDate]"), m_CheckDate);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwChargeBacksTaken diagnostics

#ifdef _DEBUG
void CSetVwChargeBacksTaken::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwChargeBacksTaken::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


