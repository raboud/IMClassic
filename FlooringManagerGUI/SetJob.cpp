/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetJob.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetJob.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetJob

IMPLEMENT_DYNAMIC(CSetJob, CRecordset)

CSetJob::CSetJob(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetJob)
	m_OrderID = 0;
	m_JobID = 0;
	m_SubContractorID = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetJob::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetJob::GetDefaultSQL()
{
	return _T("[dbo].[Job]");
}

void CSetJob::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetJob)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[JobID]"), m_JobID);
	RFX_Date(pFX, _T("[DateScheduled]"), m_DateScheduled);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Date(pFX, _T("[PaidDate]"), m_PaidDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetJob diagnostics

#ifdef _DEBUG
void CSetJob::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetJob::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
