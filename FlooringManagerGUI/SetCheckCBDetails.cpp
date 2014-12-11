/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
// SetCheckCBDetail.h : Implementation of the CSetCheckCBDetail class



// CSetCheckCBDetail implementation

// code generated on Wednesday, May 28, 2003, 8:10 PM

#include "stdafx.h"
#include "SetCheckCBDetails.h"
IMPLEMENT_DYNAMIC(CSetCheckCBDetail, CRecordset)

CSetCheckCBDetail::CSetCheckCBDetail(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CheckCBDetailID = 0;
	m_CheckID = 0;
	m_ChargeBackID = 0;
	m_Amount = 0.0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetCheckCBDetail::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetCheckCBDetail::GetDefaultSQL()
{
	return _T("[dbo].[CheckCBDetail]");
}

void CSetCheckCBDetail::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[CheckCBDetailID]"), m_CheckCBDetailID);
	RFX_Long(pFX, _T("[CheckID]"), m_CheckID);
	RFX_Long(pFX, _T("[ChargeBackID]"), m_ChargeBackID);
	RFX_Double(pFX, _T("[Amount]"), m_Amount);

}
/////////////////////////////////////////////////////////////////////////////
// CSetCheckCBDetail diagnostics

#ifdef _DEBUG
void CSetCheckCBDetail::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCheckCBDetail::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


