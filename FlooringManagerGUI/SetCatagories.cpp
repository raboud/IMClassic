/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCatagories.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetCatagories.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetCatagories

IMPLEMENT_DYNAMIC(CSetCatagories, CRecordset)

CSetCatagories::CSetCatagories(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetCatagories)
	m_CatId = 0;
	m_Description = _T("");
	m_IsPadding = FALSE;
	m_YardsPerRoll = 0;
	m_SubCatId = 0;
	m_UnitOfMeasureID = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetCatagories::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetCatagories::GetDefaultSQL()
{
	return _T("[dbo].[Material Catagory]");
}

void CSetCatagories::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetCatagories)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[CatId]"), m_CatId);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Bool(pFX, _T("[IsPadding]"), m_IsPadding);
	RFX_Long(pFX, _T("[YardsPerRoll]"), m_YardsPerRoll);
	RFX_Long(pFX, _T("[SubCatId]"), m_SubCatId);
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetCatagories diagnostics

#ifdef _DEBUG
void CSetCatagories::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCatagories::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
