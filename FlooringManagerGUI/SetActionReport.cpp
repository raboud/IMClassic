/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetActionReport.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "SetActionReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetActionReport

IMPLEMENT_DYNAMIC(CSetActionReport, CRecordset)

CSetActionReport::CSetActionReport(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetActionReport)
	m_Nature = _T("");
	m_ActionRequired = _T("");
	m_Cause = _T("");
	m_Closed = FALSE;
	m_ID = 0;
	m_InstallerError = 0;
	m_MeasureError = 0;
	m_MillError = 0;
	m_OrderID = 0;
	m_StoreError = 0;
	m_StoreErrorText = _T("");
	m_MillErrorText = _T("");
	m_InstallerErrorText = _T("");
	m_MeasureErrorText = _T("");
	m_EnteredBy = 0;
	m_LastEditedBy = 0;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetActionReport::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetActionReport::GetDefaultSQL()
{
	return _T("[dbo].[ActionReport]");
}

void CSetActionReport::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetActionReport)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Date(pFX, _T("[ReportDate]"), m_ReportDate);
	RFX_Text(pFX, _T("[Nature]"), m_Nature, CGlobals::iMAX_RICHEDIT_FIELD_LENGTH);
	RFX_Text(pFX, _T("[ActionRequired]"), m_ActionRequired, CGlobals::iMAX_RICHEDIT_FIELD_LENGTH);
	RFX_Text(pFX, _T("[Cause]"), m_Cause, CGlobals::iMAX_RICHEDIT_FIELD_LENGTH);
	RFX_Bool(pFX, _T("[Closed]"), m_Closed);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[InstallerError]"), m_InstallerError);
	RFX_Long(pFX, _T("[MeasureError]"), m_MeasureError);
	RFX_Long(pFX, _T("[MillError]"), m_MillError);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[StoreError]"), m_StoreError);
	RFX_Text(pFX, _T("[StoreErrorText]"), m_StoreErrorText, iMAX_ERROR_STRING);
	RFX_Text(pFX, _T("[MillErrorText]"), m_MillErrorText, iMAX_ERROR_STRING);
	RFX_Text(pFX, _T("[InstallerErrorText]"), m_InstallerErrorText, iMAX_ERROR_STRING);
	RFX_Text(pFX, _T("[MeasureErrorText]"), m_MeasureErrorText, iMAX_ERROR_STRING);
	RFX_Date(pFX, _T("[LastEditedDate]"), m_LastEditedDate);
	RFX_Long(pFX, _T("[EnteredBy]"), m_EnteredBy);
	RFX_Long(pFX, _T("[LastEditedBy]"), m_LastEditedBy);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetActionReport diagnostics

#ifdef _DEBUG
void CSetActionReport::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetActionReport::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
