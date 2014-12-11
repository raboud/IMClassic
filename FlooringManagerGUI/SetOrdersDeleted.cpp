// SetOrdersDeleted.h : Implementation of the CSetOrdersDeleted class



// CSetOrdersDeleted implementation

// code generated on Wednesday, April 09, 2003, 4:34 PM

#include "stdafx.h"
#include "SetOrdersDeleted.h"
IMPLEMENT_DYNAMIC(CSetOrdersDeleted, CRecordset)

CSetOrdersDeleted::CSetOrdersDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OrderID = 0;
	m_CustomerID = 0;
	m_OrderDate;
	m_PurchaseOrderNumber = "";
	m_Notes = "";
	m_ScheduleDate;
	m_BilledDate;
	m_Scheduled = FALSE;
	m_Billed = FALSE;
	m_Paid = FALSE;
	m_Called = FALSE;
	m_InternalNotes = "";
	m_CostAmount = "";
	m_BilledAmount = "";
	m_MaterialTypeID = 0;
	m_OrderAmount = "";
	m_TripCharge = "";
	m_NoMinimum = FALSE;
	m_ScheduledAM = FALSE;
	m_Cancelled = FALSE;
	m_Warrenty = FALSE;
	m_StoreID = 0;
	m_SevenDay = FALSE;
	m_DrawingNumber = "";
	m_DrawingDate;
	m_CustomerToCall = FALSE;
	m_Invoice = FALSE;
	m_OriginalPO = "";
	m_OrderNo = "";
	m_DateEntered;
	m_EnteredBy = 0;
	m_DateDeleted;
	m_DeletedBy = 0;
	m_EntryMethodID = 0;
	m_FollowUpDate;
	m_FollowUpAction = _T("");
	m_ServiceLineNo = 0;
	m_LastModifiedDateTime;
	m_nFields = 38;
	m_nDefaultType = dynaset;
}

CString CSetOrdersDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrdersDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrdersDeleted]");
}

void CSetOrdersDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);
	RFX_Date(pFX, _T("[ScheduleDate]"), m_ScheduleDate);
	RFX_Date(pFX, _T("[BilledDate]"), m_BilledDate);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Bool(pFX, _T("[Called]"), m_Called);
	RFX_Text(pFX, _T("[InternalNotes]"), m_InternalNotes);
	RFX_Text(pFX, _T("[CostAmount]"), m_CostAmount);
	RFX_Text(pFX, _T("[BilledAmount]"), m_BilledAmount);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Text(pFX, _T("[OrderAmount]"), m_OrderAmount);
	RFX_Text(pFX, _T("[TripCharge]"), m_TripCharge);
	RFX_Bool(pFX, _T("[NoMinimum]"), m_NoMinimum);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Bool(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Bool(pFX, _T("[Warrenty]"), m_Warrenty);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Bool(pFX, _T("[SevenDay]"), m_SevenDay);
	RFX_Text(pFX, _T("[DrawingNumber]"), m_DrawingNumber);
	RFX_Date(pFX, _T("[DrawingDate]"), m_DrawingDate);
	RFX_Bool(pFX, _T("[CustomerToCall]"), m_CustomerToCall);
	RFX_Bool(pFX, _T("[Invoice]"), m_Invoice);
	RFX_Text(pFX, _T("[OriginalPO]"), m_OriginalPO);
	RFX_Text(pFX, _T("[OrderNo]"), m_OrderNo);
	RFX_Date(pFX, _T("[DateEntered]"), m_DateEntered);
	RFX_Long(pFX, _T("[EnteredBy]"), m_EnteredBy);
	RFX_Date(pFX, _T("[DateDeleted]"), m_DateDeleted);
	RFX_Long(pFX, _T("[DeletedBy]"), m_DeletedBy);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID) ;
	RFX_Date(pFX, _T("[FollowUpDate]"), m_FollowUpDate);
	RFX_Text(pFX, _T("[FollowUpAction]"), m_FollowUpAction);
	RFX_Long(pFX, _T("[ServiceLineNo]"), m_ServiceLineNo) ;
	RFX_Date(pFX, _T("[LastModifiedDateTime]"), m_LastModifiedDateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CSetOrdersDeleted diagnostics

#ifdef _DEBUG
void CSetOrdersDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrdersDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


