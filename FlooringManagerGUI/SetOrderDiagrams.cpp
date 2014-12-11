// SetOrderDiagrams.h : Implementation of the CSetOrderDiagrams class



// CSetOrderDiagrams implementation

// code generated on Thursday, April 28, 2005, 2:48 PM

#include "stdafx.h"
#include "SetOrderDiagrams.h"
IMPLEMENT_DYNAMIC(CSetOrderDiagrams, CRecordset)

CSetOrderDiagrams::CSetOrderDiagrams(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_DiagramNumber = "";
	m_DiagramDateTime;
	m_DiagramFileName = "";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CSetOrderDiagrams::GetDefaultSQL()
{
	return _T("[dbo].[OrderDiagrams]");
}

void CSetOrderDiagrams::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[DiagramNumber]"), m_DiagramNumber);
	RFX_Date(pFX, _T("[DiagramDateTime]"), m_DiagramDateTime);
	RFX_Text(pFX, _T("[DiagramFileName]"), m_DiagramFileName);

}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderDiagrams diagnostics

#ifdef _DEBUG
void CSetOrderDiagrams::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderDiagrams::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


