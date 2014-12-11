// SetOrderRegMerchandiseDetailsDeleted.h : Implementation of the CSetOrderRegMerchandiseDetailsDeleted class



// CSetOrderRegMerchandiseDetailsDeleted implementation

// code generated on Monday, February 09, 2004, 9:01 PM

#include "stdafx.h"
#include "SetOrderRegMerchandiseDetailsDeleted.h"
IMPLEMENT_DYNAMIC(CSetOrderRegMerchandiseDetailsDeleted, CRecordset)

CSetOrderRegMerchandiseDetailsDeleted::CSetOrderRegMerchandiseDetailsDeleted(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OriginalID = 0;
	m_OrderID = 0;
	m_SKUNumber = _T("");
	m_ShortDescription = _T("");
	m_Description = _T("");
	m_Quantity = 0.0;
	m_UOMId = 0;
	m_Price = 0.0;
	m_Retail = 0.0;
	m_HDLineNumber = 0;
	m_Notes = _T("");
	m_StatusID = 0;
	m_Deleted = FALSE;
	m_EntryMethodID = 0;
	m_nFields = 15;
	m_nDefaultType = dynaset;
}

CString CSetOrderRegMerchandiseDetailsDeleted::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetOrderRegMerchandiseDetailsDeleted::GetDefaultSQL()
{
	return _T("[dbo].[OrderRegMerchandiseDetailsDeleted]");
}

void CSetOrderRegMerchandiseDetailsDeleted::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OriginalID]"), m_OriginalID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Text(pFX, _T("[SKUNumber]"), m_SKUNumber);
	RFX_Text(pFX, _T("[ShortDescription]"), m_ShortDescription);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Long(pFX, _T("[UOMId]"), m_UOMId);
	RFX_Double(pFX, _T("[Price]"), m_Price);
	RFX_Double(pFX, _T("[Retail]"), m_Retail);
	RFX_Long(pFX, _T("[HDLineNumber]"), m_HDLineNumber);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);
	RFX_Long(pFX, _T("[StatusID]"), m_StatusID);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
}
/////////////////////////////////////////////////////////////////////////////
// CSetOrderRegMerchandiseDetailsDeleted diagnostics

#ifdef _DEBUG
void CSetOrderRegMerchandiseDetailsDeleted::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderRegMerchandiseDetailsDeleted::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


