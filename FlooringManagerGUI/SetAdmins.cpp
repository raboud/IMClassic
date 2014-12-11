/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CSetAdmins.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetAdmins.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetAdmins

IMPLEMENT_DYNAMIC(CSetAdmins, CRecordset)

CSetAdmins::CSetAdmins(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetAdmins)
	m_name = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetAdmins::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetAdmins::GetDefaultSQL()
{
	return _T("[dbo].[AdminNames]");
}

void CSetAdmins::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetAdmins)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[name]"), m_name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetAdmins diagnostics

#ifdef _DEBUG
void CSetAdmins::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetAdmins::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
