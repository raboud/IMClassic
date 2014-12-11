/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetPadFix.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetPadFix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPadFix

IMPLEMENT_DYNAMIC(CSetPadFix, CRecordset)

CSetPadFix::CSetPadFix(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetPadFix)
	m_OrderID = 0;
	m_PurchaseOrderNumber = _T("");
	m_Billed = FALSE;
	m_Paid = FALSE;
	m_BilledAmount = _T("");
	m_OrderAmount = _T("");
	m_MaterialID = 0;
	m_UnitPrice = _T("");
	m_Size = 0.0;
	m_Price = _T("");
	m_CurrentPrice = _T("");
	m_CurrentExt = _T("");
	m_Amount = _T("");
	m_ActualUnit = _T("");
	m_Balance = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetPadFix::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetPadFix::GetDefaultSQL()
{
	return _T("[dbo].[pad fix]");
}

void CSetPadFix::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetPadFix)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Text(pFX, _T("[BilledAmount]"), m_BilledAmount);
	RFX_Text(pFX, _T("[OrderAmount]"), m_OrderAmount);
	RFX_Long(pFX, _T("[MaterialID]"), m_MaterialID);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Double(pFX, _T("[Size]"), m_Size);
	RFX_Text(pFX, _T("[Price]"), m_Price);
	RFX_Text(pFX, _T("[CurrentPrice]"), m_CurrentPrice);
	RFX_Text(pFX, _T("[CurrentExt]"), m_CurrentExt);
	RFX_Text(pFX, _T("[Amount]"), m_Amount);
	RFX_Text(pFX, _T("[ActualUnit]"), m_ActualUnit);
	RFX_Text(pFX, _T("[Balance]"), m_Balance);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetPadFix diagnostics

#ifdef _DEBUG
void CSetPadFix::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPadFix::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
