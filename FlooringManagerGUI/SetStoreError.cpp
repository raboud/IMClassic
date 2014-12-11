/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetStoreError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetStoreError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetStoreError

IMPLEMENT_DYNAMIC(CSetStoreError, CRecordset)

CSetStoreError::CSetStoreError(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetStoreError)
	m_Id = 0;
	m_Description = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetStoreError::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetStoreError::GetDefaultSQL()
{
	return _T("[dbo].[Store Error]");
}

void CSetStoreError::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetStoreError)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetStoreError diagnostics

#ifdef _DEBUG
void CSetStoreError::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetStoreError::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
