/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetUnpaid.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetUnpaid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetUnpaid

IMPLEMENT_DYNAMIC(CSetUnpaid, CRecordset)

CSetUnpaid::CSetUnpaid(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetUnpaid)
	m_fBilledAmount = 0.0;
	m_fPaidAmount = 0.0 ;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetUnpaid::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetUnpaid::GetDefaultSQL()
{
	return _T("[dbo].[CustomerOrders]");
}

void CSetUnpaid::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetUnpaid)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Double(pFX, _T("sum(ISNULL(BilledAmount,0))"), m_fBilledAmount);
	RFX_Double(pFX, _T("sum(ISNULL(TotalAmount,0))"), m_fPaidAmount);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetUnpaid diagnostics

#ifdef _DEBUG
void CSetUnpaid::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUnpaid::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
