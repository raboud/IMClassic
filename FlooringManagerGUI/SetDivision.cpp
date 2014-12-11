/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetDivision.h : Implementation of the CSetDivision class

// CSetDivision implementation

// code generated on Wednesday, May 08, 2002, 4:54 PM

#include "stdafx.h"
#include "SetDivision.h"
IMPLEMENT_DYNAMIC(CSetDivision, CRecordset)

CSetDivision::CSetDivision(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DivisionID = 0;
	m_Division = "";
	m_VendorID = 0;
	m_DivisionGroupID = 0;
	m_PrintStatusReport = 0;
    m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CSetDivision::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetDivision::GetDefaultSQL()
{
	return _T("[dbo].[Division]");
}

void CSetDivision::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	RFX_Long(pFX, _T("[VendorID]"), m_VendorID);
	RFX_Long(pFX, _T("[DivisionGroupID]"), m_DivisionGroupID);
	RFX_Long(pFX, _T("[PrintStatusReport]"), m_PrintStatusReport);

}
/////////////////////////////////////////////////////////////////////////////
// CSetDivision diagnostics

#ifdef _DEBUG
void CSetDivision::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDivision::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


