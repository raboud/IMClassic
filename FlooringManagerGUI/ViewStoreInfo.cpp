/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewStoreInfo.h : Implementation of the CViewStoreInfo class



// CViewStoreInfo implementation

// code generated on Friday, June 06, 2003, 6:33 PM

#include "stdafx.h"
#include "ViewStoreInfo.h"
IMPLEMENT_DYNAMIC(CViewStoreInfo, CRecordset)

CViewStoreInfo::CViewStoreInfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_StoreID = 0;
	m_StoreNumber = _T("");
	m_StoreTypeName = _T("");
	m_MarketName = _T("");
	m_StorePhoneNumber = _T("");
	m_DirectPhoneNumber = _T("");
	m_FaxNumber = _T("");
	m_nFields = 7;
	m_nDefaultType = dynaset;
}

CString CViewStoreInfo::GetDefaultSQL()
{
	return _T("[dbo].[vwStoreInfo]");
}

void CViewStoreInfo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Text(pFX, _T("[StoreTypeName]"), m_StoreTypeName);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	RFX_Text(pFX, _T("[StorePhoneNumber]"), m_StorePhoneNumber);
	RFX_Text(pFX, _T("[DirectPhoneNumber]"), m_DirectPhoneNumber);
	RFX_Text(pFX, _T("[FaxNumber]"), m_FaxNumber);

}
/////////////////////////////////////////////////////////////////////////////
// CViewStoreInfo diagnostics

#ifdef _DEBUG
void CViewStoreInfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CViewStoreInfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


