/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CSetOrderAndCustomer.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetOrderAndCustomer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOrderAndCustomer

IMPLEMENT_DYNAMIC(CSetOrderAndCustomer, CRecordset)

CSetOrderAndCustomer::CSetOrderAndCustomer(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOrderAndCustomer)
	m_Address = _T("");
	m_Billed = FALSE;
	m_BilledAmount = _T("");
	m_Called = FALSE;
	m_Cancelled = FALSE;
	m_City = _T("");
	m_CostAmount = _T("");
	m_CustomerID = 0;
	m_Directions = _T("");
	m_Extension = _T("");
	m_FirstName = _T("");
	m_InternalNotes = _T("");
	m_LastName = _T("");
	m_MaterialTypeID = 0;
	m_NoMinimum = FALSE;
	m_Notes = _T("");
	m_OrderAmount = _T("");
	m_OrderID = 0;
	m_Paid = FALSE;
	m_PhoneNumber = _T("");
	m_PurchaseOrderNumber = _T("");
	m_OriginalPO = _T("") ;
	m_Scheduled = FALSE;
	m_ScheduledAM = FALSE;
	m_State = _T("");
	m_TripCharge = _T("");
	m_Warrenty = FALSE;
	m_WorkNumber = _T("");
	m_ZipCode = _T("");
	m_TotalAmount = _T("");
	m_Balance = _T("") ;
	m_StoreNumber = _T("");
	m_MaterialTypeName = _T("");
	m_ShortName = _T("");
	m_Invoice = FALSE ;
	m_StoreTypeID = 0;
	m_VendorID = 0;
	m_MarkBilledWhenPaid = FALSE;
	m_XMLOrderCostAmount = _T("");
	m_EntryMethodID = 0;
	m_nFields = 44;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetOrderAndCustomer::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrderAndCustomer::GetDefaultSQL()
{
	return _T("[dbo].[CustomerOrders]");
}

void CSetOrderAndCustomer::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOrderAndCustomer)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Text(pFX, _T("[BilledAmount]"), m_BilledAmount);
	RFX_Date(pFX, _T("[BilledDate]"), m_BilledDate);
	RFX_Bool(pFX, _T("[Called]"), m_Called);
	RFX_Bool(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[CostAmount]"), m_CostAmount);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[Directions]"), m_Directions, CGlobals::iMAX_CUSTOMER_DIRECTIONS);
	RFX_Text(pFX, _T("[Extension]"), m_Extension);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[InternalNotes]"), m_InternalNotes, CGlobals::iMAX_ORDER_NOTES);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Long(pFX, _T("[MaterialTypeID]"), m_MaterialTypeID);
	RFX_Bool(pFX, _T("[NoMinimum]"), m_NoMinimum);
	RFX_Text(pFX, _T("[Notes]"), m_Notes, CGlobals::iMAX_ORDER_NOTES);
	RFX_Text(pFX, _T("[OrderAmount]"), m_OrderAmount);
	RFX_Date(pFX, _T("[OrderDate]"), m_OrderDate);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Text(pFX, _T("[PhoneNumber]"), m_PhoneNumber);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[OriginalPO]"), m_OriginalPO) ;
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Date(pFX, _T("[ScheduleEndDate]"), m_ScheduleEndDate);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[TripCharge]"), m_TripCharge);
	RFX_Bool(pFX, _T("[Warrenty]"), m_Warrenty);
	RFX_Text(pFX, _T("[WorkNumber]"), m_WorkNumber);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[TotalAmount]"), m_TotalAmount);
	RFX_Text(pFX, _T("[Balance]"), m_Balance) ;
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Text(pFX, _T("[MaterialTypeName]"), m_MaterialTypeName);
	RFX_Text(pFX, _T("[ShortName]"), m_ShortName);
	RFX_Long(pFX, _T("[StoreTypeID]"), m_StoreTypeID);
	RFX_Bool(pFX, _T("[Invoice]"), m_Invoice) ;
	RFX_Long(pFX, _T("[VendorID]"), m_VendorID) ;
	RFX_Bool(pFX, _T("[MarkBilledWhenPaid]"), m_MarkBilledWhenPaid);
	RFX_Text(pFX, _T("[XMLOrderCostAmount]"), m_XMLOrderCostAmount);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOrderAndCustomer diagnostics

#ifdef _DEBUG
void CSetOrderAndCustomer::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderAndCustomer::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
