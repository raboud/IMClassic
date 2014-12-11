// SetOrderRegMerchandiseDetails.h : Implementation of the CSetOrderRegMerchandiseDetails class



// CSetOrderRegMerchandiseDetails implementation

// code generated on Tuesday, December 30, 2003, 3:44 PM

#include "stdafx.h"
#include "SetOrderRegMerchandiseDetails.h"
IMPLEMENT_DYNAMIC(CSetOrderRegMerchandiseDetails, CRecordset)

CSetOrderRegMerchandiseDetails::CSetOrderRegMerchandiseDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_SKUNumber = "";
	m_ShortDescription = "";
	m_Description = "";
	m_Quantity = 0.0;
	m_UOMId = 0;
	m_Price = 0.0;
	m_Retail = 0.0;
	m_HDLineNumber = 0;
	m_Notes = "";
	m_StatusID = 0;
	m_Deleted = FALSE;
	m_EntryMethodID = 0;
	m_TransferredTo = 0;
	m_TransferredFrom = 0;
	m_Identity = _T("");
	m_Reviewed = FALSE;
	m_ReviewedBy = -1;
	m_ReviewedDate;
	m_OriginalOrderID = 0;
	m_nFields = 21;
	m_nDefaultType = dynaset;
}

CString CSetOrderRegMerchandiseDetails::GetDefaultSQL()
{
	return _T("[dbo].[OrderRegMerchandiseDetails]");
}

void CSetOrderRegMerchandiseDetails::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[SKUNumber]"), m_SKUNumber);
	RFX_Text(pFX, _T("[ShortDescription]"), m_ShortDescription);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Long(pFX, _T("[UOMId]"), m_UOMId);
	RFX_Double(pFX, _T("[Price]"), m_Price);
	RFX_Double(pFX, _T("[Retail]"), m_Retail);
	RFX_Long(pFX, _T("[HDLineNumber]"), m_HDLineNumber);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);
	RFX_Long(pFX, _T("[StatusID]"), m_StatusID);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Long(pFX, _T("[TransferredTo]"), m_TransferredTo);
	RFX_Long(pFX, _T("[TransferredFrom]"), m_TransferredFrom);
	RFX_Text(pFX, _T("@@IDENTITY"), m_Identity);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[ReviewedDate]"), m_ReviewedDate);
	RFX_Long(pFX, _T("[OriginalOrderID]"), m_OriginalOrderID);
}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderRegMerchandiseDetails diagnostics

#ifdef _DEBUG
void CSetOrderRegMerchandiseDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderRegMerchandiseDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


