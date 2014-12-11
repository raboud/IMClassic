#include "stdafx.h"
#include "SetVwMaterialTypesAndMarketsMapping.h"
IMPLEMENT_DYNAMIC(CSetVwMaterialTypesAndMarketsMapping, CRecordset)

CSetVwMaterialTypesAndMarketsMapping::CSetVwMaterialTypesAndMarketsMapping(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_MaterialTypeID = 0;
	m_MaterialTypeName = "";
	m_StoreTypeID = 0;
	m_Active = FALSE;
	m_MarketID = 0;
	m_MarketName = "";
	m_DivisionID = 0;
	m_ShortName = "";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CSetVwMaterialTypesAndMarketsMapping::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetVwMaterialTypesAndMarketsMapping::GetDefaultSQL()
{
	return _T("[dbo].[vwMaterialTypesAndMarketsMapping]");
}

void CSetVwMaterialTypesAndMarketsMapping::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Text(pFX, _T("[MaterialTypeName]"), m_MaterialTypeName);
	RFX_Long(pFX, _T("[StoreTypeID]"), m_StoreTypeID);
	RFX_Bool(pFX, _T("[Active]"), m_Active);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwMaterialTypesAndMarketsMapping diagnostics

#ifdef _DEBUG
void CSetVwMaterialTypesAndMarketsMapping::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwMaterialTypesAndMarketsMapping::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


