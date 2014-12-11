// SetOrderBasicLaborDetailsDeleted.h : Implementation of the CSetOrderBasicLaborDetailsDeleted class



// CSetOrderBasicLaborDetailsDeleted implementation

// code generated on Monday, February 09, 2004, 9:00 PM

#include "stdafx.h"
#include "SetOrderBasicLaborDetailsDeleted.h"
IMPLEMENT_DYNAMIC(CSetOrderBasicLaborDetailsDeleted, CRecordset)

CSetOrderBasicLaborDetailsDeleted::CSetOrderBasicLaborDetailsDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OriginalID = 0;
	m_OrderID = 0;
	m_BasicLaborID = 0;
	m_InstallQuantity = 0.0;
	m_UnitCost = _T("");
	m_UnitPrice = _T("");
	m_UnitRetail = _T("");
	m_PrintOnInvoice = FALSE;
	m_PrintOnWO = FALSE;
	m_ServiceLineNumber = 0;
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_nFields = 13;
	m_nDefaultType = dynaset;
}

CString CSetOrderBasicLaborDetailsDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetOrderBasicLaborDetailsDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrderBasicLaborDetailsDeleted]");
}

void CSetOrderBasicLaborDetailsDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Double(pFX, _T("[InstallQuantity]"), m_InstallQuantity);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Text(pFX, _T("[UnitRetail]"), m_UnitRetail);
	RFX_Bool(pFX, _T("[PrintOnInvoice]"), m_PrintOnInvoice);
	RFX_Bool(pFX, _T("[PrintOnWO]"), m_PrintOnWO);
	RFX_Long(pFX, _T("[ServiceLineNumber]"), m_ServiceLineNumber);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);

}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderBasicLaborDetailsDeleted diagnostics

#ifdef _DEBUG
void CSetOrderBasicLaborDetailsDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderBasicLaborDetailsDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


