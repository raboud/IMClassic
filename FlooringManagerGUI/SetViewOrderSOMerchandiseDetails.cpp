// SetViewOrderSOMerchandiseDetails.h : Implementation of the CSetViewOrderSOMerchandiseDetails class



// CSetViewOrderSOMerchandiseDetails implementation

// code generated on Tuesday, December 30, 2003, 12:16 PM

#include "stdafx.h"
#include "SetViewOrderSOMerchandiseDetails.h"
IMPLEMENT_DYNAMIC(CSetViewOrderSOMerchandiseDetails, CRecordset)

const int iMAX_DESCRIPTION_LENGTH = 1024;

CSetViewOrderSOMerchandiseDetails::CSetViewOrderSOMerchandiseDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_BasicLaborID = 0;
	m_PurchaseOrderNumber = "";
	m_OrderDate;
	m_CustomerID = 0;
//	m_FirstName = "";
//	m_LastName = "";
	m_SONumber = "";
	m_SKUNumber = "";
	m_Description = "";
	m_ShortDescription = "";
	m_SOLineNumber = 0;
	m_SOMerLineNumber = 0;
	m_Quantity = 0.0;
	m_Cancelled = FALSE;
	m_Warrenty = FALSE;
	m_UOMDescription = L"";
	m_NumberOfDecimals = 0;
	m_StoreID = 0;
	m_ExpectedArrivalDate;
	m_Paid = FALSE;
	m_Billed = FALSE;
	m_Scheduled = FALSE;
	m_ScheduleStartDate;
	m_ScheduledAM = FALSE;
	m_MaterialTypeName = "";
	m_MaterialStatusID = 0;
	m_Status = L"";
	m_Billable = FALSE;
	m_Installable = FALSE;
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_TransferredTo = 0;
	m_TransferredFrom = 0 ;
	m_OriginalID = 0;
	m_PreSplitQty = 0.0;
	m_Reviewed = FALSE;
	m_NotNeeded = FALSE;
	m_nFields = 37;
	m_nDefaultType = dynaset;
}

CString CSetViewOrderSOMerchandiseDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetViewOrderSOMerchandiseDetails::GetDefaultSQL()
{
	return _T("[dbo].[vwOrderSOMerchandiseDetails]");
}

void CSetViewOrderSOMerchandiseDetails::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
//	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
//	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[SONumber]"), m_SONumber);
	RFX_Text(pFX, _T("[SKUNumber]"), m_SKUNumber);
	RFX_Text(pFX, _T("[Description]"), m_Description, iMAX_DESCRIPTION_LENGTH);
	RFX_Text(pFX, _T("[ShortDescription]"), m_ShortDescription);
	RFX_Long(pFX, _T("[SOLineNumber]"), m_SOLineNumber);
	RFX_Long(pFX, _T("[SOMerLineNumber]"), m_SOMerLineNumber);
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
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Text(pFX, _T("[MaterialTypeName]"), m_MaterialTypeName);
	RFX_Long(pFX, _T("[MaterialStatusID]"), m_MaterialStatusID);
	RFX_Text(pFX, _T("[Status]"), m_Status);
	RFX_Bool(pFX, _T("[Billable]"), m_Billable);
	RFX_Bool(pFX, _T("[Installable]"), m_Installable);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Long(pFX, _T("[TransferredTo]"), m_TransferredTo) ;
	RFX_Long(pFX, _T("[TransferredFrom]"), m_TransferredFrom) ;
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID) ;
	RFX_Double(pFX, _T("[PreSplitQty]"), m_PreSplitQty);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Bool(pFX, _T("[NotNeeded]"), m_NotNeeded);

}
/////////////////////////////////////////////////////////////////////////////
// CSetViewOrderSOMerchandiseDetails diagnostics

#ifdef _DEBUG
void CSetViewOrderSOMerchandiseDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetViewOrderSOMerchandiseDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


