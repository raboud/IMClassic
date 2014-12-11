// SetOrderMaterialsDetailsDeleted.h : Implementation of the CSetOrderMaterialsDetailsDeleted class



// CSetOrderMaterialsDetailsDeleted implementation

// code generated on Wednesday, April 09, 2003, 4:35 PM

#include "stdafx.h"
#include "SetOrderMaterialsDetailsDeleted.h"
IMPLEMENT_DYNAMIC(CSetOrderMaterialsDetailsDeleted, CRecordset)

CSetOrderMaterialsDetailsDeleted::CSetOrderMaterialsDetailsDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OrdeMateriallID = 0;
	m_OrderID = 0;
	m_MaterialID = 0;
	m_Width = 0.0;
	m_Length = 0.0;
	m_UnitPrice = "";
	m_SubContractorID = 0;
	m_MerchandisPresent = FALSE;
	m_UnitCost = "";
	m_HasSONumber = FALSE;
	m_SONumber = "";
	m_Size = 0.0;
	m_Style = L"";
	m_Color = L"";
	m_UnitRetail = "";
	m_Completed = FALSE;
	m_MatStatusID = 0;
	m_Location = 0;
	m_ReceivedDate;
	m_SubContractorPaid = FALSE;
	m_SubContractorPay = 0.0;
	m_nFields = 21;
	m_nDefaultType = dynaset;
}

CString CSetOrderMaterialsDetailsDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrderMaterialsDetailsDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrderMaterialsDetailsDeleted]");
}

void CSetOrderMaterialsDetailsDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OrdeMateriallID]"), m_OrdeMateriallID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[MaterialID]"), m_MaterialID);
	RFX_Double(pFX, _T("[Width]"), m_Width);
	RFX_Double(pFX, _T("[Length]"), m_Length);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Bool(pFX, _T("[MerchandisPresent]"), m_MerchandisPresent);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Bool(pFX, _T("[HasSONumber]"), m_HasSONumber);
	RFX_Text(pFX, _T("[SONumber]"), m_SONumber);
	RFX_Double(pFX, _T("[Size]"), m_Size);
	RFX_Text(pFX, _T("[Style]"), m_Style);
	RFX_Text(pFX, _T("[Color]"), m_Color);
	RFX_Text(pFX, _T("[UnitRetail]"), m_UnitRetail);
	RFX_Bool(pFX, _T("[Completed]"), m_Completed);
	RFX_Long(pFX, _T("[MatStatusID]"), m_MatStatusID);
	RFX_Long(pFX, _T("[Location]"), m_Location);
	RFX_Date(pFX, _T("[ReceivedDate]"), m_ReceivedDate);
	RFX_Bool(pFX, _T("[SubContractorPaid]"), m_SubContractorPaid);
	RFX_Double(pFX, _T("[SubContractorPay]"), m_SubContractorPay);

}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderMaterialsDetailsDeleted diagnostics

#ifdef _DEBUG
void CSetOrderMaterialsDetailsDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderMaterialsDetailsDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


