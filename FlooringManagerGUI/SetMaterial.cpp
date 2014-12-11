/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetMaterial

IMPLEMENT_DYNAMIC(CSetMaterial, CRecordset)

CSetMaterial::CSetMaterial(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetMaterial)
	m_UnitOfMeasureID = 0;
	m_MaterialID = 0;
	m_MaterialDescription = _T("");
	m_UnitPrice = _T("");
	m_HasSONumber = FALSE;
	m_UnitCost = _T("");
	m_MaterialTypeID = 0;
	m_RetailPrice = _T("");
	m_Has2Dimensions = FALSE;
	m_HasColor = FALSE;
	m_HasStyle = FALSE;
	m_Active = FALSE;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CSetMaterial::GetDefaultSQL()
{
	return _T("[dbo].[Materials]");
}

void CSetMaterial::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetMaterial)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	RFX_Long(pFX, _T("[MaterialID]"), m_MaterialID);
	RFX_Text(pFX, _T("[MaterialDescription]"), m_MaterialDescription);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Bool(pFX, _T("[HasSONumber]"), m_HasSONumber);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Text(pFX, _T("[RetailPrice]"), m_RetailPrice);
	RFX_Bool(pFX, _T("[Has2Dimensions]"), m_Has2Dimensions);
	RFX_Bool(pFX, _T("[HasColor]"), m_HasColor);
	RFX_Bool(pFX, _T("[HasStyle]"), m_HasStyle);
	RFX_Bool(pFX, _T("[Active]"), m_Active);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetMaterial diagnostics

#ifdef _DEBUG
void CSetMaterial::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMaterial::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
