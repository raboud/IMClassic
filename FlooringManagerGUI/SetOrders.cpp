/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetOrders.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetOrders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOrders

IMPLEMENT_DYNAMIC(CSetOrders, CRecordset)

CSetOrders::CSetOrders(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOrders)
	m_OrderID = 0;
	m_CustomerID = 0;
	m_PurchaseOrderNumber = _T("");
	m_OriginalPO = _T("") ;
	m_CustOrderNo = _T("") ;
	m_Notes = _T("");
	m_Scheduled = FALSE;
	m_Billed = FALSE;
	m_Paid = FALSE;
	m_Called = FALSE;
	m_BilledAmount = _T("");
	m_MaterialTypeID = 0;
	m_NoMinimum = FALSE;
	m_OrderAmount = _T("");
	m_TripCharge = _T("");
	m_ScheduledAM = FALSE;
	m_Cancelled = FALSE;
	m_Warrenty = FALSE;
	m_InternalNotes = _T("");
	m_StoreID = 0;
	m_SevenDay = FALSE;
	m_strDrawingNumber = _T("");
	m_CostAmount = _T("");
	m_Invoice = FALSE ;
	m_EnteredBy = 0 ;
	m_EntryMethodID = 0;
	m_XMLOrderCostAmount = _T("");
	m_Deleted = FALSE ;
	m_SPNNotes = _T("");
	m_Reviewed = 0;
	m_ReviewedBy = -1;
	m_ReviewedDate;
	m_nFields = 42;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetOrders::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrders::GetDefaultSQL()
{
	return _T("[dbo].[Orders]");
}

void CSetOrders::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOrders)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[OriginalPO]"), m_OriginalPO) ;
	RFX_Text(pFX, _T("[CustomerOrderNumber]"), m_CustOrderNo) ;
	RFX_Text(pFX, _T("[Notes]"), m_Notes, CGlobals::iMAX_ORDER_NOTES);
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Date(pFX, _T("[ScheduleEndDate]"), m_ScheduleEndDate);
	RFX_Date(pFX, _T("[BilledDate]"), m_BilledDate);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Bool(pFX, _T("[Called]"), m_Called);
	RFX_Text(pFX, _T("[BilledAmount]"), m_BilledAmount);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Bool(pFX, _T("[NoMinimum]"), m_NoMinimum);
	RFX_Text(pFX, _T("[OrderAmount]"), m_OrderAmount);
	RFX_Text(pFX, _T("[TripCharge]"), m_TripCharge);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Bool(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Bool(pFX, _T("[Warrenty]"), m_Warrenty);
	RFX_Text(pFX, _T("[InternalNotes]"), m_InternalNotes, CGlobals::iMAX_ORDER_NOTES);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Bool(pFX, _T("[SevenDay]"), m_SevenDay);
	RFX_Date(pFX, _T("[DrawingDate]"), m_drawingDate);
	RFX_Text(pFX, _T("[DrawingNumber]"), m_strDrawingNumber);
	RFX_Text(pFX, _T("[CostAmount]"), m_CostAmount);
	RFX_Bool(pFX, _T("[Invoice]"), m_Invoice) ;
	RFX_Date(pFX, _T("[DateEntered]"), m_DateEntered);
	RFX_Long(pFX, _T("[EnteredBy]"), m_EnteredBy) ;
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID) ;
	RFX_Date(pFX, _T("[FollowUpDate]"), m_FollowUpDate);
	RFX_Text(pFX, _T("[FollowUpAction]"), m_FollowUpAction);
	RFX_Long(pFX, _T("[ServiceLineNo]"), m_ServiceLineNo) ;
	RFX_Date(pFX, _T("[LastModifiedDateTime]"), m_LastModifiedDateTime);
	RFX_Text(pFX, _T("[XMLOrderCostAmount]"), m_XMLOrderCostAmount);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted) ;
	RFX_Text(pFX, _T("[SPNNotes]"), m_SPNNotes, CGlobals::iMAX_ORDER_NOTES);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[ReviewedDate]"), m_ReviewedDate);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOrders diagnostics

#ifdef _DEBUG
void CSetOrders::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrders::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
