/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetBasicLabor.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetBasicLabor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetBasicLabor

IMPLEMENT_DYNAMIC(CSetBasicLabor, CRecordset)

CSetBasicLabor::CSetBasicLabor(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetBasicLabor)
	m_UnitOfMeasureID = 0;
	m_BasicLaborID = 0;
	m_LaborDescription = _T("");
	m_UnitPrice = _T("");
	m_UnitCost = _T("");
	m_MaterialTypeID = 0;
	m_Active = FALSE;
	m_MaterialCatagoryID = 0;
	m_nFields = 10;
//	m_HasSONumber = FALSE;
//	m_Has2Dimensions = FALSE;
//	m_HasColor = FALSE;
//	m_HasStyle = FALSE;
	m_IsPadding = FALSE;
	m_YardsPerRoll = 0;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetBasicLabor::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetBasicLabor::GetDefaultSQL()
{
	return _T("[dbo].[BasicLabor]");
}

void CSetBasicLabor::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetBasicLabor)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Text(pFX, _T("[LaborDescription]"), m_LaborDescription);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Bool(pFX, _T("[Active]"), m_Active);
	RFX_Long(pFX, _T("[MaterialCatagoryID]"), m_MaterialCatagoryID);

//	RFX_Bool(pFX, _T("[HasSONumber]"), m_HasSONumber);
//	RFX_Bool(pFX, _T("[Has2Dimensions]"), m_Has2Dimensions);
//	RFX_Bool(pFX, _T("[HasColor]"), m_HasColor);
//	RFX_Bool(pFX, _T("[HasStyle]"), m_HasStyle);
	RFX_Bool(pFX, _T("[IsPadding]"), m_IsPadding);
	RFX_Long(pFX, _T("[YardsPerRoll]"), m_YardsPerRoll);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetBasicLabor diagnostics

#ifdef _DEBUG
void CSetBasicLabor::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetBasicLabor::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
