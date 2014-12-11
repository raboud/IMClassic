// SetVwOrderBasicLaborDetails.h : Implementation of the CSetVwOrderBasicLaborDetails class



// CSetVwOrderBasicLaborDetails implementation

// code generated on Friday, December 12, 2003, 6:07 PM

#include "stdafx.h"
#include "SetVwOrderBasicLaborDetails.h"
IMPLEMENT_DYNAMIC(CSetVwOrderBasicLaborDetails, CRecordset)

CSetVwOrderBasicLaborDetails::CSetVwOrderBasicLaborDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Cancelled = FALSE;
	m_ScheduledAM = FALSE;
	m_FirstName = "";
	m_LastName = "";
	m_InstallQuantity = 0.0;
	m_IsPadding = FALSE;
	m_LaborDescription = "";
	m_Scheduled = FALSE;
	m_ScheduleStartDate;
	m_StoreID = 0;
	m_CustomerID = 0;
	m_StoreNumber = "";
	m_OrderID = 0;
	m_Billed = FALSE;
	m_PurchaseOrderNumber = "";
	m_UOMDescription = "";
	m_NumberOfDecimals = 0;
	m_UnitPrice = 0.0;
	m_UnitCost = 0.0;
	m_YardsPerRoll = 0;
	m_Paid = FALSE;
	m_UnitRetail = 0.0;
	m_Warrenty = FALSE;
	m_MaterialTypeName = "";
	m_Invoice = FALSE;
	m_DivisionID = 0;
	m_MarketId = 0;
	m_Deleted = FALSE ;
	m_PrintOnInvoice = FALSE ;
	m_PrintOnWO = FALSE ;
	m_nFields = 30;
	m_nDefaultType = dynaset;
}

CString CSetVwOrderBasicLaborDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetVwOrderBasicLaborDetails::GetDefaultSQL()
{
	return _T("[dbo].[vwOrderBasicLaborDetails]");
}

void CSetVwOrderBasicLaborDetails::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Bool(pFX, _T("[Cancelled]"), m_Cancelled);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Double(pFX, _T("[InstallQuantity]"), m_InstallQuantity);
	RFX_Bool(pFX, _T("[IsPadding]"), m_IsPadding);
	RFX_Text(pFX, _T("[LaborDescription]"), m_LaborDescription);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Date(pFX, _T("[ScheduleStartDate]"), m_ScheduleStartDate);
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Bool(pFX, _T("[Billed]"), m_Billed);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[UOMDescription]"), m_UOMDescription);
	RFX_Long(pFX, _T("[NumberOfDecimals]"), m_NumberOfDecimals);
	RFX_Double(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Double(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Long(pFX, _T("[YardsPerRoll]"), m_YardsPerRoll);
	RFX_Bool(pFX, _T("[Paid]"), m_Paid);
	RFX_Double(pFX, _T("[UnitRetail]"), m_UnitRetail);
	RFX_Bool(pFX, _T("[Warrenty]"), m_Warrenty);
	RFX_Text(pFX, _T("[MaterialTypeName]"), m_MaterialTypeName);
	RFX_Bool(pFX, _T("[Invoice]"), m_Invoice);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Bool(pFX, _T("[PrintOnInvoice]"), m_PrintOnInvoice);
	RFX_Bool(pFX, _T("[PrintOnWO]"), m_PrintOnWO) ;

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwOrderBasicLaborDetails diagnostics

#ifdef _DEBUG
void CSetVwOrderBasicLaborDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwOrderBasicLaborDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


