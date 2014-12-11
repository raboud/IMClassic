/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetDuplicates.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetDuplicates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDuplicates

IMPLEMENT_DYNAMIC(CSetDuplicates, CRecordset)

CSetDuplicates::CSetDuplicates(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetDuplicates)
	m_ID1 = 0;
	m_Last1 = _T("");
	m_First1 = _T("");
	m_PO1 = _T("");
	m_OrderID1 = 0;
	m_SO1 = _T("");
	m_MatStatusID = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetDuplicates::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetDuplicates::GetDefaultSQL()
{
	return _T("[dbo].[Duplicates]");
}

void CSetDuplicates::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetDuplicates)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID1]"), m_ID1);
	RFX_Text(pFX, _T("[Last1]"), m_Last1);
	RFX_Text(pFX, _T("[First1]"), m_First1);
	RFX_Text(pFX, _T("[PO1]"), m_PO1);
	RFX_Long(pFX, _T("[OrderID1]"), m_OrderID1);
	RFX_Text(pFX, _T("[SO1]"), m_SO1);
	RFX_Long(pFX, _T("[MatStatusID]"), m_MatStatusID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetDuplicates diagnostics

#ifdef _DEBUG
void CSetDuplicates::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDuplicates::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
