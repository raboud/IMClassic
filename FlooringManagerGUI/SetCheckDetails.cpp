/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCheckDetails.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetCheckDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetCheckDetails

IMPLEMENT_DYNAMIC(CSetCheckDetails, CRecordset)

CSetCheckDetails::CSetCheckDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetCheckDetails)
	m_CheckDetailID = 0;
	m_CheckID = 0;
	m_OrderID = 0;
	m_Amount = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetCheckDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetCheckDetails::GetDefaultSQL()
{
	return _T("[dbo].[CheckDetail]");
}

void CSetCheckDetails::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetCheckDetails)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[CheckDetailID]"), m_CheckDetailID);
	RFX_Long(pFX, _T("[CheckID]"), m_CheckID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[Amount]"), m_Amount);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetCheckDetails diagnostics

#ifdef _DEBUG
void CSetCheckDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCheckDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
