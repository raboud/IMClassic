/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetDetails.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetJobDetails

IMPLEMENT_DYNAMIC(CSetJobDetails, CRecordset)

CSetJobDetails::CSetJobDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetJobDetails)
	m_JobDetailID = 0;
	m_JobID = 0;
	m_DetailID = 0;
	m_DetailType = 0;
	m_AmountPaid = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetJobDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetJobDetails::GetDefaultSQL()
{
	return _T("[dbo].[JobDetails]");
}

void CSetJobDetails::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetJobDetails)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[JobDetailID]"), m_JobDetailID);
	RFX_Long(pFX, _T("[JobID]"), m_JobID);
	RFX_Long(pFX, _T("[DetailID]"), m_DetailID);
	RFX_Long(pFX, _T("[DetailType]"), m_DetailType);
	RFX_Text(pFX, _T("[AmountPaid]"), m_AmountPaid);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetJobDetails diagnostics

#ifdef _DEBUG
void CSetJobDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetJobDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
