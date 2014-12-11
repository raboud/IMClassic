// vwWorkOrderMaterialsChecklist.h : Implementation of the CvwWorkOrderMaterialsChecklist class



// CvwWorkOrderMaterialsChecklist implementation

// code generated on Sunday, February 08, 2004, 6:25 PM

#include "stdafx.h"
#include "vwWorkOrderMaterialsChecklist.h"
IMPLEMENT_DYNAMIC(CvwWorkOrderMaterialsChecklist, CRecordset)

CvwWorkOrderMaterialsChecklist::CvwWorkOrderMaterialsChecklist(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_OrderID = 0;
	m_Quantity = 0.0;
	m_MatDesc = _T("");
	m_UOM = _T("");
	m_Status = _T("");
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CvwWorkOrderMaterialsChecklist::GetDefaultSQL()
{
	return _T("[dbo].[vwWorkOrderMaterialsChecklist]");
}

void CvwWorkOrderMaterialsChecklist::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Text(pFX, _T("[MatDesc]"), m_MatDesc);
	RFX_Text(pFX, _T("[UOM]"), m_UOM);
	RFX_Text(pFX, _T("[Status]"), m_Status);

}
/////////////////////////////////////////////////////////////////////////////
// CvwWorkOrderMaterialsChecklist diagnostics

#ifdef _DEBUG
void CvwWorkOrderMaterialsChecklist::AssertValid() const
{
	CRecordset::AssertValid();
}

void CvwWorkOrderMaterialsChecklist::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


