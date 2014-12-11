/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCustomer.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetCustomer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetCustomer

IMPLEMENT_DYNAMIC(CSetCustomer, CRecordset)

CSetCustomer::CSetCustomer(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetCustomer)
	m_CustomerID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_Address = _T("");
	m_City = _T("");
	m_State = _T("");
	m_ZipCode = _T("");
	m_PhoneNumber = _T("");
	m_WorkNumber = _T("");
	m_MobileNumber = _T("");
	m_EmailAddress = _T("");
//	m_Extension = _T("");
	m_Directions = _T("");
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetCustomer::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetCustomer::GetDefaultSQL()
{
	return _T("[dbo].[Customers]");
}

void CSetCustomer::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetCustomer)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[PhoneNumber]"), m_PhoneNumber);
	RFX_Text(pFX, _T("[WorkNumber]"), m_WorkNumber);
	RFX_Text(pFX, _T("[MobileNumber]"), m_MobileNumber);
	RFX_Text(pFX, _T("[EmailAddress]"), m_EmailAddress);
//	RFX_Text(pFX, _T("[Extension]"), m_Extension);
	RFX_Text(pFX, _T("[Directions]"), m_Directions, CGlobals::iMAX_CUSTOMER_DIRECTIONS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetCustomer diagnostics

#ifdef _DEBUG
void CSetCustomer::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetCustomer::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
