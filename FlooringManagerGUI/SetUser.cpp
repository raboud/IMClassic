/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetUser.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetUser

IMPLEMENT_DYNAMIC(CSetUser, CRecordset)

CSetUser::CSetUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetUser)
	m_name = _T("");
	m_uid = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetUser::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetUser::GetDefaultSQL()
{
	return _T("[dbo].[sysusers]");
}

void CSetUser::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetUser)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Int(pFX, _T("[uid]"), m_uid);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetUser diagnostics

#ifdef _DEBUG
void CSetUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
