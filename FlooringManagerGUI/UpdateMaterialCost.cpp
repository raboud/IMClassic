/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// UpdateMaterialCost.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "UpdateMaterialCost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateMaterialCost

IMPLEMENT_DYNAMIC(CUpdateMaterialCost, CRecordset)

CUpdateMaterialCost::CUpdateMaterialCost(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUpdateMaterialCost)
	m_Scheduled = FALSE;
	m_UnitCost = _T("");
	m_NewUnitCost = _T("");
	m_OrderID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_PurchaseOrderNumber = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CUpdateMaterialCost::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CUpdateMaterialCost::GetDefaultSQL()
{
	return _T("[dbo].[Update Material Cost]");
}

void CUpdateMaterialCost::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUpdateMaterialCost)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[NewUnitCost]"), m_NewUnitCost);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateMaterialCost diagnostics

#ifdef _DEBUG
void CUpdateMaterialCost::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUpdateMaterialCost::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
