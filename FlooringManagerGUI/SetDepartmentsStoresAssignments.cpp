// DepartmentsStoresAssignments.h : Implementation of the CSetDepartmentsStoresAssignments class



// CSetDepartmentsStoresAssignments implementation

// code generated on Monday, January 26, 2004, 2:01 PM

#include "stdafx.h"
#include "SetDepartmentsStoresAssignments.h"
IMPLEMENT_DYNAMIC(CSetDepartmentsStoresAssignments, CRecordset)

CSetDepartmentsStoresAssignments::CSetDepartmentsStoresAssignments(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_StoreID = 0;
	m_DepartmentID = 0;
	m_FaxNumber = _T("");
	m_Notes = _T("");
	m_AltFaxNumber = _T("") ;
	m_FaxStatusReportTo = 0 ;
	m_nFields = 7;
	m_nDefaultType = dynaset;
}

CString CSetDepartmentsStoresAssignments::GetDefaultSQL()
{
	return _T("[dbo].[DepartmentsStoresAssignments]");
}

void CSetDepartmentsStoresAssignments::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Long(pFX, _T("[StoreID]"), m_StoreID);
	RFX_Long(pFX, _T("[DepartmentID]"), m_DepartmentID);
	RFX_Text(pFX, _T("[FaxNumber]"), m_FaxNumber);
	RFX_Text(pFX, _T("[Notes]"), m_Notes, 1024);
	RFX_Text(pFX, _T("[AltFaxNumber]"), m_AltFaxNumber) ;
	RFX_Long(pFX, _T("[FaxStatusReportTo]"), m_FaxStatusReportTo) ;
}
/////////////////////////////////////////////////////////////////////////////
// CSetDepartmentsStoresAssignments diagnostics

#ifdef _DEBUG
void CSetDepartmentsStoresAssignments::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetDepartmentsStoresAssignments::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


