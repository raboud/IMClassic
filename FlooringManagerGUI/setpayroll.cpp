/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// setpayroll.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "setpayroll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPayroll

IMPLEMENT_DYNAMIC(CSetPayroll, CRecordset)

CSetPayroll::CSetPayroll(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetPayroll)
	m_Installer = _T("");
	m_PONumber = _T("");
	m_Name = _T("");
	m_Pay_Amount = _T("");
	m_Comments = _T("");
	m_Chargeback = _T("");
	m_NO_RETAINAGE = 0.0;
	m_Class = _T("") ;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetPayroll::GetDefaultConnect()
{
	return _T("ODBC;DSN=FlooringSub");
}

CString CSetPayroll::GetDefaultSQL()
{
	return _T("[Current]");
}

void CSetPayroll::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetPayroll)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[Installer]"), m_Installer);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[PO Number]"), m_PONumber);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Pay Amount]"), m_Pay_Amount);
	RFX_Text(pFX, _T("[Comments]"), m_Comments);
	RFX_Text(pFX, _T("[Chargeback]"), m_Chargeback);
	RFX_Double(pFX, _T("[NO RETAINAGE]"), m_NO_RETAINAGE);
	RFX_Text(pFX, _T("[Class]"), m_Class) ;
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetPayroll diagnostics

#ifdef _DEBUG
void CSetPayroll::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPayroll::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

