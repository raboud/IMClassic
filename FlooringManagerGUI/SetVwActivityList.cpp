/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetVwActivityList.h : Implementation of the CSetViewActivityList class



// CSetViewActivityList implementation

// code generated on Wednesday, March 15, 2006, 1:43 PM

#include "stdafx.h"
#include "SetVwActivityList.h"
IMPLEMENT_DYNAMIC(CSetViewActivityList, CRecordset)

CSetViewActivityList::CSetViewActivityList(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_StoreNumber = L"";
	m_PurchaseOrderNumber = "";
	m_CustomerName = "";
	m_ActivityName = L"";
	m_CreatedDate;
	m_FollowUpDate;
	m_Data = L"";
	m_MarketName = "";
	m_Division = "";
	m_ActivityTypeID = 0;
	m_OrderID = 0;
	m_ClosedDate;
	m_MarketId = 0;
	m_DivisionID = 0;
	m_ClosedByName = "";
	m_NoteText = "";
	m_ClosedByID = 0;
	m_nFields = 18;
	m_nDefaultType = dynaset;
}

CString CSetViewActivityList::GetDefaultSQL()
{
	return _T("[dbo].[vwActivityList]");
}

void CSetViewActivityList::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PurchaseOrderNumber);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Text(pFX, _T("[ActivityName]"), m_ActivityName);
	RFX_Date(pFX, _T("[CreatedDate]"), m_CreatedDate);
	RFX_Date(pFX, _T("[FollowUpDate]"), m_FollowUpDate);
	RFX_Text(pFX, _T("[Data]"), m_Data, CGlobals::iMAX_ACTIVITY_DATA);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	RFX_Long(pFX, _T("[ActivityTypeID]"), m_ActivityTypeID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Date(pFX, _T("[ClosedDate]"), m_ClosedDate);
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Text(pFX, _T("[ClosedByName]"), m_ClosedByName);
	RFX_Text(pFX, _T("[NoteText]"), m_NoteText, CGlobals::iMAX_ORDER_NOTES);
	RFX_Long(pFX, _T("[ClosedByID]"), m_ClosedByID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetViewActivityList diagnostics

#ifdef _DEBUG
void CSetViewActivityList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetViewActivityList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


