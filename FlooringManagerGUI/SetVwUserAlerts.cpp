// SetVwUserAlerts.h : Implementation of the CSetVwUserAlerts class



// CSetVwUserAlerts implementation

// code generated on Wednesday, August 18, 2004, 4:05 PM

#include "stdafx.h"
#include "SetVwUserAlerts.h"
IMPLEMENT_DYNAMIC(CSetVwUserAlerts, CRecordset)

CSetVwUserAlerts::CSetVwUserAlerts(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PurchaseOrderNumber = "";
	m_StoreNumber = L"";
	m_CustomerName = "";
	m_OrderDate;
	m_ScheduleStartDate;
	m_Scheduled = FALSE;
	m_MarketName = "";
	m_Division = "";
	m_Billed = FALSE;
	m_Paid = FALSE;
	m_DivisionID = 0;
	m_MarketID = 0;
	m_nFields = 12;
	m_nDefaultType = dynaset;
}

CString CSetVwUserAlerts::GetDefaultSQL()
{
	return _T("[dbo].[vwUserAlerts]");
}

void CSetVwUserAlerts::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwUserAlerts diagnostics

#ifdef _DEBUG
void CSetVwUserAlerts::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwUserAlerts::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


