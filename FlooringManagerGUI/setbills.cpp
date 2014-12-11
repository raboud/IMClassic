/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// setbills.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "setbills.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetBills

IMPLEMENT_DYNAMIC(CSetBills, CRecordset)

CSetBills::CSetBills(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetBills)
	m_Account = _T("");
	m_ID = 0;
	m_Memo = _T("");
	m_Name = _T("");
	m_Num = _T("");
	m_Original_Amount = _T("");
	m_Paid_Amount = _T("");
	m_Split = _T("");
	m_Type = _T("");
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetBills::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
}

CString CSetBills::GetDefaultSQL()
{
	return _T("[Bills]");
}

void CSetBills::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetBills)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[Account]"), m_Account);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Memo]"), m_Memo);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Num]"), m_Num);
	RFX_Text(pFX, _T("[Original Amount]"), m_Original_Amount);
	RFX_Text(pFX, _T("[Paid Amount]"), m_Paid_Amount);
	RFX_Text(pFX, _T("[Split]"), m_Split);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetBills diagnostics

#ifdef _DEBUG
void CSetBills::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetBills::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
