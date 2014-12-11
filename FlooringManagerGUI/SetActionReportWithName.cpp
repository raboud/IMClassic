// SetActionReportWithName.h : Implementation of the CSetActionReportWithName class



// CSetActionReportWithName implementation

// code generated on Friday, January 31, 2003, 4:15 PM

#include "stdafx.h"
#include "SetActionReportWithName.h"
IMPLEMENT_DYNAMIC(CSetActionReportWithName, CRecordset)

CSetActionReportWithName::CSetActionReportWithName(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ReportDate;
	m_Nature = "";
	m_ActionRequired = "";
	m_Cause = "";
	m_Closed = FALSE;
	m_ID = 0;
	m_PurchaseOrderNumber = "";
	m_FirstName = "";
	m_LastName = "";
	m_Address = "";
	m_City = "";
	m_State = "";
	m_ZipCode = "";
	m_PhoneNumber = "";
	m_WorkNumber = "";
	m_OrderID = 0;
	m_StoreError = 0;
	m_MillError = 0;
	m_InstallerError = 0;
	m_MeasureError = 0;
	m_LastUpdatedDate;
	m_CreatedBy = "";
	m_LastUpdatedBy = "";
	m_nFields = 23;
	m_nDefaultType = dynaset;
}

CString CSetActionReportWithName::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetActionReportWithName::GetDefaultSQL()
{
	return _T("[dbo].[ActionReportView]");
}

void CSetActionReportWithName::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Date(pFX, _T("[ReportDate]"), m_ReportDate);
	RFX_Text(pFX, _T("[Nature]"), m_Nature, CGlobals::iMAX_RICHEDIT_FIELD_LENGTH);
	RFX_Text(pFX, _T("[ActionRequired]"), m_ActionRequired, CGlobals::iMAX_RICHEDIT_FIELD_LENGTH);
	RFX_Text(pFX, _T("[Cause]"), m_Cause, CGlobals::iMAX_RICHEDIT_FIELD_LENGTH);
	RFX_Bool(pFX, _T("[Closed]"), m_Closed);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[PhoneNumber]"), m_PhoneNumber);
	RFX_Text(pFX, _T("[WorkNumber]"), m_WorkNumber);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[StoreError]"), m_StoreError);
	RFX_Long(pFX, _T("[MillError]"), m_MillError);
	RFX_Long(pFX, _T("[InstallerError]"), m_InstallerError);
	RFX_Long(pFX, _T("[MeasureError]"), m_MeasureError);
	RFX_Date(pFX, _T("[LastUpdatedDate]"), m_LastUpdatedDate);
	RFX_Text(pFX, _T("[CreatedBy]"), m_CreatedBy);
	RFX_Text(pFX, _T("[LastUpdatedBy]"), m_LastUpdatedBy);


}
/////////////////////////////////////////////////////////////////////////////
// CSetActionReportWithName diagnostics

#ifdef _DEBUG
void CSetActionReportWithName::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetActionReportWithName::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


