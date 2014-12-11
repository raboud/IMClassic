/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetVwActivePOs.h : Implementation of the CSetVwActivePOs class



// CSetVwActivePOs implementation

// code generated on Friday, February 03, 2006, 9:33 AM

#include "stdafx.h"
#include "SetVwActivePOs.h"
IMPLEMENT_DYNAMIC(CSetVwActivePOs, CRecordset)

CSetVwActivePOs::CSetVwActivePOs(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PurchaseOrderNumber = "";
	m_StoreNumber = "";
	m_CustomerName = "";
	m_OrderDate;
	m_ScheduleStartDate;
	m_ScheduleEndDate;
	m_Scheduled = FALSE;
	m_MarketName = "";
	m_Division = "";
	m_Billed = FALSE;
	m_Paid = FALSE;
	m_DivisionID = 0;
	m_MarketId = 0;
	m_OrderID = 0;
	m_EntryMethodID = 0;
	m_Cancelled = FALSE;
	m_HasAlerts = FALSE;
	m_nFields = 17;
	m_nDefaultType = dynaset;
}

CString CSetVwActivePOs::GetDefaultSQL()
{
	return _T("[dbo].[vwActivePOs]");
}

void CSetVwActivePOs::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Date(pFX, _T("[ScheduleEndDate]"), m_ScheduleEndDate);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Bool(pFX, _T("[HasAlerts]"), m_HasAlerts);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwActivePOs diagnostics

#ifdef _DEBUG
void CSetVwActivePOs::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwActivePOs::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


