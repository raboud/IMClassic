/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetPayments.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetPayments.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPayments

IMPLEMENT_DYNAMIC(CSetPayments, CRecordset)

CSetPayments::CSetPayments(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetPayments)
	m_CheckNumber = _T("");
	m_Amount = _T("");
	m_OrderID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_PurchaseOrderNumber = _T("");
	m_CheckDetailID = 0;
	m_Billed = FALSE;
	m_BilledAmount = _T("");
	m_TotalAmount = _T("");
	m_Balance = _T("");
	m_Paid = FALSE;
	m_CheckID = 0 ;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetPayments::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetPayments::GetDefaultSQL()
{
	return _T("[dbo].[Payments]");
}

void CSetPayments::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetPayments)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[CheckNumber]"), m_CheckNumber);
	RFX_Date(pFX, _T("[CheckDate]"), m_CheckDate);
	RFX_Text(pFX, _T("[Amount]"), m_Amount);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Long(pFX, _T("[CheckDetailID]"), m_CheckDetailID);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Text(pFX, _T("[BilledAmount]"), m_BilledAmount);
	RFX_Date(pFX, _T("[BilledDate]"), m_BilledDate);
	RFX_Text(pFX, _T("[TotalAmount]"), m_TotalAmount);
	RFX_Text(pFX, _T("[Balance]"), m_Balance);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Long(pFX, _T("[CheckID]"), m_CheckID) ;
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetPayments diagnostics

#ifdef _DEBUG
void CSetPayments::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPayments::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
