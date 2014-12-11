// SetVwDiscrepancies.h : Implementation of the CSetVwDiscrepancies class



// CSetVwDiscrepancies implementation

// code generated on Friday, December 05, 2003, 4:34 PM

#include "stdafx.h"
#include "SetVwDiscrepancies.h"
IMPLEMENT_DYNAMIC(CSetVwDiscrepancies, CRecordset)

CSetVwDiscrepancies::CSetVwDiscrepancies(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_PONumber = _T("");
	m_StoreNumber = _T("");
	m_Type = _T("");
	m_SubType = _T("");
	m_CustomerName = _T("");
	m_CurrentData = _T("");
	m_NewData = _T("");
	m_Reviewed = FALSE;
	m_DetailID = 0;
	m_OrderID = 0;
	//m_XMLFilePath = _T("");
	//m_DateFound;
	m_MarketID = 0;
	m_DivisionID = 0;
	m_nFields = 13;
	m_nDefaultType = dynaset;
}

CString CSetVwDiscrepancies::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetVwDiscrepancies::GetDefaultSQL()
{
	return _T("[dbo].[vwDiscrepancies]");
}

void CSetVwDiscrepancies::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[PurchaseOrderNumber]"), m_PONumber);
	RFX_Text(pFX, _T("[StoreNumber]"), m_StoreNumber);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	RFX_Text(pFX, _T("[SubType]"), m_SubType);
	RFX_Text(pFX, _T("[CurrentData]"), m_CurrentData, 1024);
	RFX_Text(pFX, _T("[NewData]"), m_NewData, 1024);
	RFX_Text(pFX, _T("[CustName]"), m_CustomerName);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[DetailID]"), m_DetailID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	//RFX_Text(pFX, _T("[XMLFilePath]"), m_XMLFilePath, 1024);
	//RFX_Date(pFX, _T("[DateFound]"), m_DateFound);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwDiscrepancies diagnostics

#ifdef _DEBUG
void CSetVwDiscrepancies::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwDiscrepancies::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


