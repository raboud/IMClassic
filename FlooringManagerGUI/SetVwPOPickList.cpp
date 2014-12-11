// SetVwPOPickList.h : Implementation of the CSetVwPOPickList class



// CSetVwPOPickList implementation

// code generated on Tuesday, October 26, 2004, 11:37 PM

#include "stdafx.h"
#include "SetVwPOPickList.h"
IMPLEMENT_DYNAMIC(CSetVwPOPickList, CRecordset)

CSetVwPOPickList::CSetVwPOPickList(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OrderID = 0;
	m_CustomerID = 0;
	m_OrderDate;
	m_PurchaseOrderNumber = "";
	m_ScheduleStartDate;
	m_ScheduleEndDate;
	m_ShortName = "";
	m_Total = 0.0;
	m_HasNotes = 0;
	m_HasReports = 0;
	m_Cancelled = 0; 
	m_Warranty = 0;
	m_Billed = 0;
	m_Scheduled = 0;
	m_Paid = 0;
	m_ScheduledAM = FALSE;
	m_nFields = 16;
	m_nDefaultType = dynaset;
}

CString CSetVwPOPickList::GetDefaultConnect()
{
	return _T("DSN=Flooring;ODBC;");
}

CString CSetVwPOPickList::GetDefaultSQL()
{
	return _T("[dbo].[vwPOPickList]");
}

void CSetVwPOPickList::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Date(pFX, _T("[ScheduleEndDate]"), m_ScheduleEndDate);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Double(pFX, _T("[Total]"), m_Total);
	RFX_Long(pFX, _T("[HasNotes]"), m_HasNotes);
	RFX_Long(pFX, _T("[HasReports]"), m_HasReports);
	RFX_Long(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Long(pFX, _T("[Warrenty]"), m_Warranty);
	RFX_Long(pFX, _T("[Billed]"), m_Billed);
	RFX_Long(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Long(pFX, _T("[Paid]"), m_Paid);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
}
/////////////////////////////////////////////////////////////////////////////
// CSetVwPOPickList diagnostics

#ifdef _DEBUG
void CSetVwPOPickList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwPOPickList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


