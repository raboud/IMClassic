/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMeasureError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetMeasureError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetMeasureError

IMPLEMENT_DYNAMIC(CSetMeasureError, CRecordset)

CSetMeasureError::CSetMeasureError(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetMeasureError)
	m_Id = 0;
	m_Description = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetMeasureError::GetDefaultSQL()
{
	return _T("[dbo].[Measure Error]");
}

void CSetMeasureError::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetMeasureError)
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
// CSetMeasureError diagnostics

#ifdef _DEBUG
void CSetMeasureError::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMeasureError::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
