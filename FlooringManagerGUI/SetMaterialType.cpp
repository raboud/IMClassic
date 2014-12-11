/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMaterialType.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetMaterialType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetMaterialType

IMPLEMENT_DYNAMIC(CSetMaterialType, CRecordset)

CSetMaterialType::CSetMaterialType(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetMaterialType)
	m_MaterialTypeID = 0;
	m_MaterialTypeName = _T("");
	m_StoreTypeID = 0;
	m_TripChargeMultiplier = 0.0;
	m_MinimumRetail = _T("");
	m_CustomMultiplier = 0.0;
	m_MinimumCost = _T("");
	m_MinimumPrice = _T("");
	m_CostMultiplier = 0.0;
	m_OnlyBasicToMinimum = FALSE;
	m_Valid = FALSE;
	m_ShortName = _T("");
	m_DivisionID = 0;
	m_Active = FALSE;
	m_SKU = _T("");
	m_SKUDesc = _T("");
	m_HDType = _T("");
	m_AllowMaterialStatusUpdate = FALSE ;
	m_WoodWaiver = FALSE;
	m_nFields = 19;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetMaterialType::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetMaterialType::GetDefaultSQL()
{
	return _T("[dbo].[MaterialType]");
}

void CSetMaterialType::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetMaterialType)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Text(pFX, _T("[MaterialTypeName]"), m_MaterialTypeName);
	RFX_Long(pFX, _T("[StoreTypeID]"), m_StoreTypeID);
	RFX_Double(pFX, _T("[TripChargeMultiplier]"), m_TripChargeMultiplier);
	RFX_Text(pFX, _T("[MinimumRetail]"), m_MinimumRetail);
	RFX_Double(pFX, _T("[CustomMultiplier]"), m_CustomMultiplier);
	RFX_Text(pFX, _T("[MinimumCost]"), m_MinimumCost);
	RFX_Text(pFX, _T("[MinimumPrice]"), m_MinimumPrice);
	RFX_Double(pFX, _T("[CostMultiplier]"), m_CostMultiplier);
	RFX_Bool(pFX, _T("[OnlyBasicToMinimum]"), m_OnlyBasicToMinimum);
	RFX_Bool(pFX, _T("[Valid]"), m_Valid);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Bool(pFX, _T("[Active]"), m_Active);
	RFX_Text(pFX, _T("[SKU]"), m_SKU);
	RFX_Text(pFX, _T("[SKUDesc]"), m_SKUDesc);
	RFX_Text(pFX, _T("[HDType]"), m_HDType);
	RFX_Bool(pFX, _T("[AllowMaterialStatusUpdate]"), m_AllowMaterialStatusUpdate) ;
	RFX_Bool(pFX, _T("[WoodWaiver]"), m_WoodWaiver);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetMaterialType diagnostics

#ifdef _DEBUG
void CSetMaterialType::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMaterialType::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
