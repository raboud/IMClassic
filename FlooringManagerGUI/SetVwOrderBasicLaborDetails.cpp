// SetVwOrderBasicLaborDetails.h : Implementation of the CSetVwOrderBasicLaborDetails class



// CSetVwOrderBasicLaborDetails implementation

// code generated on Friday, December 12, 2003, 6:07 PM

#include "stdafx.h"
#include "SetVwOrderBasicLaborDetails.h"
IMPLEMENT_DYNAMIC(CSetVwOrderBasicLaborDetails, CRecordset)

CSetVwOrderBasicLaborDetails::CSetVwOrderBasicLaborDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_InstallQuantity = 0.0;
	m_LaborDescription = "";
	m_UOMDescription = "";
	m_NumberOfDecimals = 0;
	m_UnitPrice = 0.0;
	m_UnitRetail = 0.0;
//	m_PrintOnInvoice = FALSE ;
	//m_PrintOnWO = FALSE ;
	m_nFields = 6;
	m_nDefaultType = dynaset;
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
	RFX_Double(pFX, _T("[InstallQuantity]"), m_InstallQuantity);
	RFX_Text(pFX, _T("[LaborDescription]"), m_LaborDescription);
	RFX_Text(pFX, _T("[UOMDescription]"), m_UOMDescription);
	RFX_Long(pFX, _T("[NumberOfDecimals]"), m_NumberOfDecimals);
	RFX_Double(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Double(pFX, _T("[UnitRetail]"), m_UnitRetail);
//	RFX_Bool(pFX, _T("[PrintOnInvoice]"), m_PrintOnInvoice);

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


