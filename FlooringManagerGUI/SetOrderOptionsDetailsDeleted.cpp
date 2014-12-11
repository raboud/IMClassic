// SetOrderOptionsDetailsDeleted.h : Implementation of the CSetOrderOptionsDetailsDeleted class



// CSetOrderOptionsDetailsDeleted implementation

// code generated on Wednesday, April 09, 2003, 4:35 PM

#include "stdafx.h"
#include "SetOrderOptionsDetailsDeleted.h"
#include "flooring.h"
IMPLEMENT_DYNAMIC(CSetOrderOptionsDetailsDeleted, CRecordset)

CSetOrderOptionsDetailsDeleted::CSetOrderOptionsDetailsDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OriginalID = 0;
	m_OrderID = 0;
	m_OptionID = 0;
	m_Quantity = 0.0;
	m_UnitPrice = "";
	m_SubContractorID = 0;
	m_UnitCost = "";
	m_UnitRetail = "";
	m_SubContractorPaid = FALSE;
	m_SubContractorPay = 0.0;
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_nFields = 12;
	
	CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
	if (pApp->GetDBVersion() > 15)
	{
		m_nFields++;
	}

	m_nDefaultType = dynaset;
}

CString CSetOrderOptionsDetailsDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrderOptionsDetailsDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrderOptionsDetailsDeleted]");
}

void CSetOrderOptionsDetailsDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[OptionID]"), m_OptionID);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[UnitRetail]"), m_UnitRetail);
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
// CSetOrderOptionsDetailsDeleted diagnostics

#ifdef _DEBUG
void CSetOrderOptionsDetailsDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderOptionsDetailsDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


