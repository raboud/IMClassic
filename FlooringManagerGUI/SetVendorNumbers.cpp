// SetVendorNumbers.h : Implementation of the CSetVendorNumbers class



// CSetVendorNumbers implementation

// code generated on Tuesday, July 15, 2003, 1:49 PM

#include "stdafx.h"
#include "SetVendorNumbers.h"
IMPLEMENT_DYNAMIC(CSetVendorNumbers, CRecordset)

CSetVendorNumbers::CSetVendorNumbers(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_VendorID = 0;
	m_VendorNumber = _T("");
	m_Description = _T("");
	m_PaySubWhenPaid = FALSE;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetVendorNumbers::GetDefaultSQL()
{
	return _T("[dbo].[VendorNumbers]");
}

void CSetVendorNumbers::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[VendorID]"), m_VendorID);
	RFX_Text(pFX, _T("[VendorNumber]"), m_VendorNumber);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Bool(pFX, _T("[PaySubWhenPaid]"), m_PaySubWhenPaid);

}
/////////////////////////////////////////////////////////////////////////////
// CSetVendorNumbers diagnostics

#ifdef _DEBUG
void CSetVendorNumbers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVendorNumbers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


