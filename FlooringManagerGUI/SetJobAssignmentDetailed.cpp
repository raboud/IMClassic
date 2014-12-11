/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetJobAssignmentDetailed.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetJobAssignmentDetailed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetJobAssignmentDetailed

IMPLEMENT_DYNAMIC(CSetJobAssignmentDetailed, CRecordset)

CSetJobAssignmentDetailed::CSetJobAssignmentDetailed(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetJobAssignmentDetailed)
	m_Id = 0;
	m_SubContractorId = 0;
	m_PurchaseOrderNumber = _T("");
	m_LastName = _T("");
	m_FirstName = _T("");
	m_Address = _T("");
	m_City = _T("");
	m_State = _T("");
	m_ZipCode = _T("");
	m_PhoneNumber = _T("");
	m_WorkNumber = _T("");
	m_MaterialTypeID = 0;
	m_ShortName = _T("");
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetJobAssignmentDetailed::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetJobAssignmentDetailed::GetDefaultSQL()
{
	return _T("[dbo].[JobAssignmentDetailed]");
}

void CSetJobAssignmentDetailed::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetJobAssignmentDetailed)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Long(pFX, _T("[SubContractorId]"), m_SubContractorId);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[PhoneNumber]"), m_PhoneNumber);
	RFX_Text(pFX, _T("[WorkNumber]"), m_WorkNumber);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetJobAssignmentDetailed diagnostics

#ifdef _DEBUG
void CSetJobAssignmentDetailed::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetJobAssignmentDetailed::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
