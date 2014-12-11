/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCustomerDocuments.h : Implementation of the CSetCustomerDocuments class
#include "stdafx.h"
#include "SetCustomerDocuments.h"



// CSetCustomerDocuments implementation

// code generated on Monday, February 23, 2009, 11:17 PM

IMPLEMENT_DYNAMIC(CSetCustomerDocuments, CRecordset)

CSetCustomerDocuments::CSetCustomerDocuments(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_CustomerID = 0;
	m_Path = L"";
	m_Filename = L"";
	m_Notes = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CSetCustomerDocuments::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetCustomerDocuments::GetDefaultSQL()
{
	return _T("[dbo].[CustomerDocuments]");
}

void CSetCustomerDocuments::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Text(pFX, _T("[Filename]"), m_Filename);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);

}
/////////////////////////////////////////////////////////////////////////////
// CSetCustomerDocuments diagnostics

#ifdef _DEBUG
void CSetCustomerDocuments::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCustomerDocuments::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


