/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMatStatus.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetMatStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetMatStatus

IMPLEMENT_DYNAMIC(CSetMatStatus, CRecordset)

CSetMatStatus::CSetMatStatus(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetMatStatus)
	m_MatStatusID = 0;
	m_Status = _T("");
	m_Billable = FALSE;
	m_Installable = FALSE;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetMatStatus::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetMatStatus::GetDefaultSQL()
{
	return _T("[dbo].[Material Status]");
}

void CSetMatStatus::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetMatStatus)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[MatStatusID]"), m_MatStatusID);
	RFX_Text(pFX, _T("[Status]"), m_Status);
	RFX_Bool(pFX, _T("[Billable]"), m_Billable);
	RFX_Bool(pFX, _T("[Installable]"), m_Installable);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetMatStatus diagnostics

#ifdef _DEBUG
void CSetMatStatus::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMatStatus::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
