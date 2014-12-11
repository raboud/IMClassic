// SetDiscrepancies.h : Implementation of the CSetDiscrepancies class



// CSetDiscrepancies implementation

// code generated on Monday, December 08, 2003, 11:47 AM

#include "stdafx.h"
#include "SetDiscrepancies.h"
IMPLEMENT_DYNAMIC(CSetDiscrepancies, CRecordset)

CSetDiscrepancies::CSetDiscrepancies(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	//m_PONumber = "";
	//m_CustOrStoreID = 0;
	m_DiscrepancyTypeID = 0;
	m_DiscrepancySubTypeID = 0;
	m_CurrentData = _T("");
	m_NewData = _T("");
	m_XMLFilePath = "";
	m_DateFound;
	m_OrderID = -1;
	m_DetailID = -1;
	m_Reviewed = 0;
	m_ReviewedBy = -1;
	m_ReviewedDate;
	m_nFields = 12;
	m_nDefaultType = dynaset;
}

CString CSetDiscrepancies::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetDiscrepancies::GetDefaultSQL()
{
	return _T("[dbo].[Discrepancies]");
}

void CSetDiscrepancies::DoFieldExchange(CFieldExchange* pFX)
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
	//RFX_Text(pFX, _T("[PONumber]"), m_PONumber);
	//RFX_Long(pFX, _T("[CustOrStoreID]"), m_CustOrStoreID);
	RFX_Long(pFX, _T("[DiscrepancyTypeID]"), m_DiscrepancyTypeID);
	RFX_Long(pFX, _T("[DiscrepancySubTypeID]"), m_DiscrepancySubTypeID);
	RFX_Text(pFX, _T("[CurrentData]"), m_CurrentData, 1024);
	RFX_Text(pFX, _T("[NewData]"), m_NewData,1024);
	RFX_Text(pFX, _T("[XMLFilePath]"), m_XMLFilePath, 1024);
	RFX_Date(pFX, _T("[DateFound]"), m_DateFound);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[DetailID]"), m_DetailID);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[DateReviewed]"), m_ReviewedDate);


}
/////////////////////////////////////////////////////////////////////////////
// CSetDiscrepancies diagnostics

#ifdef _DEBUG
void CSetDiscrepancies::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDiscrepancies::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


