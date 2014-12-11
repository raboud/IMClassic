/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetTotalPayment.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetTotalPayment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTotalPayment

IMPLEMENT_DYNAMIC(CSetTotalPayment, CRecordset)

CSetTotalPayment::CSetTotalPayment(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetTotalPayment)
	m_TotalAmount = _T("");
	m_OrderID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetTotalPayment::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetTotalPayment::GetDefaultSQL()
{
	return _T("[dbo].[TotalPayment]");
}

void CSetTotalPayment::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetTotalPayment)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[TotalAmount]"), m_TotalAmount);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetTotalPayment diagnostics

#ifdef _DEBUG
void CSetTotalPayment::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetTotalPayment::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
