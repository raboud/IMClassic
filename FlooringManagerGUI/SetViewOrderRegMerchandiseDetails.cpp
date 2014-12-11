// SetViewOrderRegMerchandiseDetails.h : Implementation of the CSetViewOrderRegMerchandiseDetails class



// CSetViewOrderRegMerchandiseDetails implementation

// code generated on Tuesday, December 30, 2003, 3:43 PM

#include "stdafx.h"
#include "SetViewOrderRegMerchandiseDetails.h"
IMPLEMENT_DYNAMIC(CSetViewOrderRegMerchandiseDetails, CRecordset)

CSetViewOrderRegMerchandiseDetails::CSetViewOrderRegMerchandiseDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_SKUNumber = "";
	m_ShortDescription = "";
	m_Description = "";
	m_Quantity = 0.0;
	m_UOMDescription = L"";
	m_Price = 0.0;
	m_Retail = 0.0;
	m_Notes = "";
	m_Status = "";
	m_EntryMethodID = 0;
	m_Deleted = FALSE;
	m_Reviewed = FALSE;
	m_nFields = 14;
	m_nDefaultType = dynaset;
}

CString CSetViewOrderRegMerchandiseDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetViewOrderRegMerchandiseDetails::GetDefaultSQL()
{
	return _T("[dbo].[vwOrderRegMerchandiseDetails]");
}

void CSetViewOrderRegMerchandiseDetails::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[UOMDescription]"), m_UOMDescription);
	RFX_Double(pFX, _T("[Price]"), m_Price);
	RFX_Double(pFX, _T("[Retail]"), m_Retail);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);
	RFX_Text(pFX, _T("[Status]"), m_Status);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);

}
/////////////////////////////////////////////////////////////////////////////
// CSetViewOrderRegMerchandiseDetails diagnostics

#ifdef _DEBUG
void CSetViewOrderRegMerchandiseDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetViewOrderRegMerchandiseDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG



