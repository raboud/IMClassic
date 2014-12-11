// SetOrderSOMerchandiseDetailsDeleted.h : Implementation of the CSetOrderSOMerchandiseDetailsDeleted class



// CSetOrderSOMerchandiseDetailsDeleted implementation

// code generated on Monday, February 09, 2004, 9:02 PM

#include "stdafx.h"
#include "SetOrderSOMerchandiseDetailsDeleted.h"
IMPLEMENT_DYNAMIC(CSetOrderSOMerchandiseDetailsDeleted, CRecordset)

CSetOrderSOMerchandiseDetailsDeleted::CSetOrderSOMerchandiseDetailsDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OriginalID = 0;
	m_OrderID = 0;
	m_SONumber = "";
	m_SKUNumber = "";
	m_BasicLaborID = 0;
	m_ShortDescription = "";
	m_Description = "";
	m_Quantity = 0.0;
	m_UOMId = 0;
	m_ExpectedArrivalDate;
	m_HDLineNumber = 0;
	m_MaterialStatusID = 0;
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_nFields = 15;
	m_nDefaultType = dynaset;
}

CString CSetOrderSOMerchandiseDetailsDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetOrderSOMerchandiseDetailsDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrderSOMerchandiseDetailsDeleted]");
}

void CSetOrderSOMerchandiseDetailsDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[SONumber]"), m_SONumber);
	RFX_Text(pFX, _T("[SKUNumber]"), m_SKUNumber);
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Text(pFX, _T("[ShortDescription]"), m_ShortDescription);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Long(pFX, _T("[UOMId]"), m_UOMId);
	RFX_Date(pFX, _T("[ExpectedArrivalDate]"), m_ExpectedArrivalDate);
	RFX_Long(pFX, _T("[HDLineNumber]"), m_HDLineNumber);
	RFX_Long(pFX, _T("[MaterialStatusID]"), m_MaterialStatusID);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);

}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderSOMerchandiseDetailsDeleted diagnostics

#ifdef _DEBUG
void CSetOrderSOMerchandiseDetailsDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderSOMerchandiseDetailsDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


