// SetVwChecksWithVendorInfo.h : Implementation of the CSetVwChecksWithVendorInfo class



// CSetVwChecksWithVendorInfo implementation

// code generated on Tuesday, July 15, 2003, 5:24 PM

#include "stdafx.h"
#include "SetVwChecksWithVendorInfo.h"
IMPLEMENT_DYNAMIC(CSetVwChecksWithVendorInfo, CRecordset)

CSetVwChecksWithVendorInfo::CSetVwChecksWithVendorInfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CheckID = 0;
	m_CheckNumber = "";
	m_CheckDate;
	m_Amount = _T("");
	m_VendorNumber = L"";
	m_Description = L"";
	m_PaySubWhenPaid = FALSE;
	m_QBTxnId = _T("");;
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CSetVwChecksWithVendorInfo::GetDefaultSQL()
{
	return _T("[dbo].[vwChecksWithVendorInfo]");
}

void CSetVwChecksWithVendorInfo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[CheckID]"), m_CheckID);
	RFX_Text(pFX, _T("[CheckNumber]"), m_CheckNumber);
	RFX_Date(pFX, _T("[CheckDate]"), m_CheckDate);
	RFX_Text(pFX, _T("[Amount]"), m_Amount);
	RFX_Text(pFX, _T("[VendorNumber]"), m_VendorNumber);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Bool(pFX, _T("[PaySubWhenPaid]"), m_PaySubWhenPaid);
	RFX_Text(pFX, _T("[QBTxnId]"), m_QBTxnId);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVwChecksWithVendorInfo diagnostics

#ifdef _DEBUG
void CSetVwChecksWithVendorInfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVwChecksWithVendorInfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


