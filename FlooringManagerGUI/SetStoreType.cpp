/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetStoreType.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetStoreType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetStoreType

IMPLEMENT_DYNAMIC(CSetStoreType, CRecordset)

CSetStoreType::CSetStoreType(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetStoreType)
	m_StoreTypeID = 0;
	m_StoreTypeName = _T("");
	m_ImageName = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetStoreType::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetStoreType::GetDefaultSQL()
{
	return _T("[dbo].[StoreType]");
}

void CSetStoreType::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetStoreType)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[StoreTypeID]"), m_StoreTypeID);
	RFX_Text(pFX, _T("[StoreTypeName]"), m_StoreTypeName);
	RFX_Text(pFX, _T("[ImageName]"), m_ImageName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetStoreType diagnostics

#ifdef _DEBUG
void CSetStoreType::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetStoreType::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
