// SetOrderBasicLaborDetails.h : Implementation of the CSetOrderBasicLaborDetails class



// CSetOrderBasicLaborDetails implementation

// code generated on Tuesday, December 09, 2003, 1:46 PM

#include "stdafx.h"
#include "SetOrderBasicLaborDetails.h"
IMPLEMENT_DYNAMIC(CSetOrderBasicLaborDetails, CRecordset)

CSetOrderBasicLaborDetails::CSetOrderBasicLaborDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_BasicLaborID = 0;
	m_InstallQuantity = 0.0;
	m_UnitCost = _T("");
	m_UnitPrice = _T("");
	m_UnitRetail = _T("");
	m_ServiceLineNumber = 0;
	m_EntryMethodID = 0;
	m_PrintOnInvoice = FALSE;
	m_PrintOnWO = FALSE;
	m_Deleted = FALSE;
	m_Reviewed = FALSE;
	m_ReviewedBy = -1;
	m_ReviewedDate;
	m_nFields = 15;
	m_nDefaultType = dynaset;
}

CString CSetOrderBasicLaborDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetOrderBasicLaborDetails::GetDefaultSQL()
{
	return _T("[dbo].[OrderBasicLaborDetails]");
}

void CSetOrderBasicLaborDetails::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[BasicLaborID]"), m_BasicLaborID);
	RFX_Double(pFX, _T("[InstallQuantity]"), m_InstallQuantity);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Text(pFX, _T("[UnitRetail]"), m_UnitRetail);
	RFX_Long(pFX, _T("[ServiceLineNumber]"), m_ServiceLineNumber);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[PrintOnInvoice]"), m_PrintOnInvoice);
	RFX_Bool(pFX, _T("[PrintOnWO]"), m_PrintOnWO);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[ReviewedDate]"), m_ReviewedDate);
}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderBasicLaborDetails diagnostics

#ifdef _DEBUG
void CSetOrderBasicLaborDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderBasicLaborDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


