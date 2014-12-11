// SetOrderCustomDetailsDeleted.h : Implementation of the CSetOrderCustomDetailsDeleted class



// CSetOrderCustomDetailsDeleted implementation

// code generated on Wednesday, April 09, 2003, 4:36 PM

#include "stdafx.h"
#include "SetOrderCustomDetailsDeleted.h"
#include "flooring.h"
IMPLEMENT_DYNAMIC(CSetOrderCustomDetailsDeleted, CRecordset)

CSetOrderCustomDetailsDeleted::CSetOrderCustomDetailsDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OriginalID = 0;
	m_OrderID = 0;
	m_SubContractorID = 0;
	m_RetailPrice = "";
//	m_Multiplier = 0.0;
	m_UnitCost = "";
	m_UnitPrice = "";
	m_Quanity = 0.0;
	m_Description = "";
//	m_CostMultiplier = 0.0;
	m_UnitOfMeasureID = 0;
	m_NotOnInvoice = FALSE;
	m_NotOnWorkOrder = FALSE;
	m_SubContractorPaid = FALSE;
	m_SubContractorPay = 0.0;
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_nFields = 16;
	
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	if (pApp->GetDBVersion() > 15)
	{
		m_nFields++;
	}

	m_nDefaultType = dynaset;
}

CString CSetOrderCustomDetailsDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrderCustomDetailsDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrderCustomDetailsDeleted]");
}

void CSetOrderCustomDetailsDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Text(pFX, _T("[RetailPrice]"), m_RetailPrice);
//	RFX_Double(pFX, _T("[Multiplier]"), m_Multiplier);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitCost);
	RFX_Double(pFX, _T("[Quanity]"), m_Quanity);
	RFX_Text(pFX, _T("[Description]"), m_Description);
//	RFX_Double(pFX, _T("[CostMultiplier]"), m_CostMultiplier);
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	RFX_Bool(pFX, _T("[NotOnInvoice]"), m_NotOnInvoice);
	RFX_Bool(pFX, _T("[NotOnWorkOrder]"), m_NotOnWorkOrder);
	RFX_Bool(pFX, _T("[SubContractorPaid]"), m_SubContractorPaid);
	RFX_Double(pFX, _T("[SubContractorPay]"), m_SubContractorPay);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	if (pApp->GetDBVersion() > 15)
	{
		RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	}

}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderCustomDetailsDeleted diagnostics

#ifdef _DEBUG
void CSetOrderCustomDetailsDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderCustomDetailsDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


