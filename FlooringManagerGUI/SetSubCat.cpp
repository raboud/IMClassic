/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetSubCat.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetSubCat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSubCat

IMPLEMENT_DYNAMIC(CSetSubCat, CRecordset)

CSetSubCat::CSetSubCat(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetSubCat)
	m_SubCatId = 0;
	m_Description = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetSubCat::GetDefaultSQL()
{
	return _T("[dbo].[MatSubCat]");
}

void CSetSubCat::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetSubCat)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[SubCatId]"), m_SubCatId);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetSubCat diagnostics

#ifdef _DEBUG
void CSetSubCat::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetSubCat::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
