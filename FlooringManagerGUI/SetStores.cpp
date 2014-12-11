/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetStores.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetStores.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetStores

IMPLEMENT_DYNAMIC(CSetStores, CRecordset)

CSetStores::CSetStores(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetStores)
	m_StoreID = 0;
	m_StoreTypeID = 0;
	m_StoreNumber = _T("");
	m_BillingAddress = _T("");
	m_City = _T("");
	m_State = _T("");
	m_ZipCode = _T("");
	m_StorePhoneNumber = _T("");
	m_DirectPhoneNumber = _T("");
	m_Extension = _T("");
	m_FaxNumber = _T("");
	m_Notes = _T("");
	m_MarketId = 0 ;
	m_StoreNickName = _T("");
	m_Active = FALSE;
	m_IncludeInStatusReportAll = TRUE;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetStores::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetStores::GetDefaultSQL()
{
	return _T("[dbo].[Stores]");
}

void CSetStores::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetStores)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Long(pFX, _T("[StoreTypeID]"), m_StoreTypeID);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Text(pFX, _T("[BillingAddress]"), m_BillingAddress);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[StorePhoneNumber]"), m_StorePhoneNumber);
	RFX_Text(pFX, _T("[DirectPhoneNumber]"), m_DirectPhoneNumber);
	RFX_Text(pFX, _T("[Extension]"), m_Extension);
	RFX_Text(pFX, _T("[FaxNumber]"), m_FaxNumber);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Text(pFX, _T("[StoreNickName]"), m_StoreNickName);
	RFX_Bool(pFX, _T("[Active]"), m_Active);	
	RFX_Bool(pFX, _T("[IncludeInStatusReportAll]"), m_IncludeInStatusReportAll);	
	
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetStores diagnostics

#ifdef _DEBUG
void CSetStores::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetStores::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
