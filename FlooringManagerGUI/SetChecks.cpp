/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetChecks.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetChecks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetChecks

IMPLEMENT_DYNAMIC(CSetChecks, CRecordset)

CSetChecks::CSetChecks(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetChecks)
	m_CheckID = 0;
	m_CheckNumber = _T("");
	m_Amount = _T("");
	m_VendorID = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CSetChecks::GetDefaultSQL()
{
	return _T("[dbo].[Checks]");
}

void CSetChecks::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetChecks)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[CheckID]"), m_CheckID);
	RFX_Text(pFX, _T("[CheckNumber]"), m_CheckNumber);
	RFX_Date(pFX, _T("[CheckDate]"), m_CheckDate);
	RFX_Text(pFX, _T("[Amount]"), m_Amount);
	RFX_Long(pFX, _T("[VendorID]"), m_VendorID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetChecks diagnostics

#ifdef _DEBUG
void CSetChecks::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetChecks::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
