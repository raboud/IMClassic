/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMillError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetMillError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetMillError

IMPLEMENT_DYNAMIC(CSetMillError, CRecordset)

CSetMillError::CSetMillError(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetMillError)
	m_Id = 0;
	m_Description = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetMillError::GetDefaultSQL()
{
	return _T("[dbo].[Mill Error]");
}

void CSetMillError::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetMillError)
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
// CSetMillError diagnostics

#ifdef _DEBUG
void CSetMillError::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMillError::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
