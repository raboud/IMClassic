// SetOrderSOMerchandiseDetails.h : Implementation of the CSetOrderSOMerchandiseDetails class



// CSetOrderSOMerchandiseDetails implementation

// code generated on Tuesday, December 30, 2003, 12:18 PM

#include "stdafx.h"
#include "SetOrderSOMerchandiseDetails.h"
IMPLEMENT_DYNAMIC(CSetOrderSOMerchandiseDetails, CRecordset)

const int iMAX_DESCRIPTION_LENGTH = 1024;

CSetOrderSOMerchandiseDetails::CSetOrderSOMerchandiseDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_SONumber = "";
	m_SKUNumber = "";
	m_BasicLaborID = 0;
	m_ShortDescription = "";
	m_Description = "";
	m_Quantity = 0.0;
	m_UOMId = 0;
	m_ExpectedArrivalDate;
	m_SOLineNumber = 0;
	m_SOMerLineNumber = 0;
	m_MaterialStatusID = 0;
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_TransferredTo = 0;
	m_TransferredFrom = 0;
	m_Identity = _T("");
	m_OriginalID = 0;
	m_PreSplitQty = 0.0;
	m_Reviewed = FALSE;
	m_ReviewedBy = -1;
	m_ReviewedDate;
	m_OriginalOrderID = 0;
	m_NotNeeded = FALSE;
	m_nFields = 25;
	m_nDefaultType = dynaset;
}

CString CSetOrderSOMerchandiseDetails::GetDefaultSQL()
{
	return _T("[dbo].[OrderSOMerchandiseDetails]");
}

void CSetOrderSOMerchandiseDetails::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[SONumber]"), m_SONumber);
	RFX_Text(pFX, _T("[SKUNumber]"), m_SKUNumber);
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Text(pFX, _T("[ShortDescription]"), m_ShortDescription);
	RFX_Text(pFX, _T("[Description]"), m_Description, iMAX_DESCRIPTION_LENGTH);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Long(pFX, _T("[UOMId]"), m_UOMId);
	RFX_Date(pFX, _T("[ExpectedArrivalDate]"), m_ExpectedArrivalDate);
	RFX_Long(pFX, _T("[SOLineNumber]"), m_SOLineNumber);
	RFX_Long(pFX, _T("[SOMerLineNumber]"), m_SOMerLineNumber);
	RFX_Long(pFX, _T("[MaterialStatusID]"), m_MaterialStatusID);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Long(pFX, _T("[TransferredTo]"), m_TransferredTo);
	RFX_Long(pFX, _T("[TransferredFrom]"), m_TransferredFrom);
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID);
	RFX_Double(pFX, _T("[PreSplitQty]"), m_PreSplitQty);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[ReviewedDate]"), m_ReviewedDate);
	RFX_Long(pFX, _T("[OriginalOrderID]"), m_OriginalOrderID);
	RFX_Bool(pFX, _T("[NotNeeded]"), m_NotNeeded);
	

	RFX_Text(pFX, _T("@@IDENTITY"), m_Identity);
}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderSOMerchandiseDetails diagnostics

#ifdef _DEBUG
void CSetOrderSOMerchandiseDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderSOMerchandiseDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


