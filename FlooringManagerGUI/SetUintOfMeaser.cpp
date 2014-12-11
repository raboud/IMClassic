/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetUintOfMeaser.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetUintOfMeaser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetUnitOfMeasure

IMPLEMENT_DYNAMIC(CSetUnitOfMeasure, CRecordset)

CSetUnitOfMeasure::CSetUnitOfMeasure(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetUnitOfMeasure)
	m_UnitOfMeasureID = 0;
	m_Description = _T("");
	m_Divisor = 0.0 ;
	m_NumberOfDecimals = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CSetUnitOfMeasure::GetDefaultSQL()
{
	return _T("[dbo].[UnitOfMeasure]");
}

void CSetUnitOfMeasure::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetUnitOfMeasure)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Double(pFX, _T("[Divisor]"), m_Divisor);
	RFX_Long(pFX, _T("[NumberOfDecimals]"), m_NumberOfDecimals);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetUnitOfMeasure diagnostics

#ifdef _DEBUG
void CSetUnitOfMeasure::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUnitOfMeasure::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
