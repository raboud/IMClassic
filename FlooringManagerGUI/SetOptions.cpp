/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// Options.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOptions

IMPLEMENT_DYNAMIC(CSetOptions, CRecordset)

CSetOptions::CSetOptions(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOptions)
	m_OptionID = 0;
	m_OptionDescription = _T("");
//	m_UnitPrice = _T("");
//	m_UnitCost = _T("");
	m_UnitOfMeasureID = 0;
	m_MaterialTypeID = 0;
	m_ApplyToMinimum = FALSE;
	m_ApplyToMinimumWO = FALSE;
	m_PrintOnInvoice = FALSE;
	m_PrintOnWorkOrder = FALSE;
	m_Active = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetOptions::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOptions::GetDefaultSQL()
{
	return _T("[dbo].[vwOptionItems]");
}

void CSetOptions::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOptions)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[OptionID]"), m_OptionID);
	RFX_Text(pFX, _T("[Description]"), m_OptionDescription);
//	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
//	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Bool(pFX, _T("[ApplyToMinimum]"), m_ApplyToMinimum);
	RFX_Bool(pFX, _T("[ApplyToMinimumWO]"), m_ApplyToMinimumWO);
//	RFX_Bool(pFX, _T("[PrintOnInvoice]"), m_PrintOnInvoice);
//	RFX_Bool(pFX, _T("[PrintOnWorkOrder]"), m_PrintOnWorkOrder);
	RFX_Bool(pFX, _T("[Active]"), m_Active);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOptions diagnostics

#ifdef _DEBUG
void CSetOptions::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOptions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
