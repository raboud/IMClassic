// SetVwOrderSOMerchandiseDetails.h : Implementation of the CSetVwOrderSOMerchandiseDetails class



// CSetVwOrderSOMerchandiseDetails implementation

// code generated on Friday, December 12, 2003, 5:44 PM

#include "stdafx.h"
#include "SetVwOrderSOMerchandiseDetails.h"
IMPLEMENT_DYNAMIC(CSetVwOrderSOMerchandiseDetails, CRecordset)

CSetVwOrderSOMerchandiseDetails::CSetVwOrderSOMerchandiseDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_PurchaseOrderNumber = "";
	m_OrderDate;
	m_CustomerID = 0;
	m_FirstName = "";
	m_LastName = "";
	m_SONumber = "";
	m_SKUNumber = "";
	m_Description = "";
	m_ShortDescription = "";
	m_Quantity = 0.0;
	m_Cancelled = FALSE;
	m_Warrenty = FALSE;
	m_UOMDescription = "";
	m_NumberOfDecimals = 0;
	m_StoreID = 0;
	m_ExpectedArrivalDate;
	m_Paid = FALSE;
	m_Billed = FALSE;
	m_Scheduled = FALSE;
	m_ScheduleDate;
	m_ScheduledAM = FALSE;
	m_MaterialStatusID = 0;
	m_Billable = FALSE;
	m_Installable = FALSE;
	m_MaterialTypeName = "";
	m_TransferredTo = 0 ;
	m_TransferredFrom = 0 ;
	m_nFields = 29;
	m_nDefaultType = dynaset;
}

CString CSetVwOrderSOMerchandiseDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetVwOrderSOMerchandiseDetails::GetDefaultSQL()
{
	return _T("[dbo].[vwOrderSOMerchandiseDetails]");
}

void CSetVwOrderSOMerchandiseDetails::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[SONumber]"), m_SONumber);
	RFX_Text(pFX, _T("[SKUNumber]"), m_SKUNumber);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[ShortDescription]"), m_ShortDescription);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Bool(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Bool(pFX, _T("[Warrenty]"), m_Warrenty);
	RFX_Text(pFX, _T("[UOMDescription]"), m_UOMDescription);
	RFX_Long(pFX, _T("[NumberOfDecimals]"), m_NumberOfDecimals);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Date(pFX, _T("[ExpectedArrivalDate]"), m_ExpectedArrivalDate);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Date(pFX, _T("[ScheduleDate]"), m_ScheduleDate);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Text(pFX, _T("[MaterialTypeName]"), m_MaterialTypeName);
	RFX_Long(pFX, _T("[MaterialStatusID]"), m_MaterialStatusID);
	RFX_Bool(pFX, _T("[Installable]"), m_Installable);
	RFX_Bool(pFX, _T("[Billable]"), m_Billable);
	RFX_Long(pFX, _T("[TransferredTo]"), m_TransferredTo) ;
	RFX_Long(pFX, _T("[TransferredFrom]"), m_TransferredFrom) ;

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwOrderSOMerchandiseDetails diagnostics

#ifdef _DEBUG
void CSetVwOrderSOMerchandiseDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwOrderSOMerchandiseDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


