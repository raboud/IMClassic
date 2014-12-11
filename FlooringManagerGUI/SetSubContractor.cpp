/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetSubContractor.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetSubContractor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSubContractor

IMPLEMENT_DYNAMIC(CSetSubContractor, CRecordset)

CSetSubContractor::CSetSubContractor(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetSubContractor)
	m_SubContractorID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_NickName = _T("");
	m_Address = _T("");
	m_City = _T("");
	m_State = _T("");
	m_ZipCode = _T("");
	m_HomePhoneNumber = _T("");
	m_CellPhoneNumber = _T("");
	m_Pager = _T("");
	m_SSN = _T("");
	m_WorkmansCompInsuranceOK = FALSE ;
	m_LiabilityInsuranceOK = FALSE ;
	m_BackgroundCheckPassed = FALSE;
	m_Notes = _T("");
	m_Retainage = _T("");
	m_RetainageRate = _T("");
	m_SavingsRate = 0.0;
	m_BackgroundRptRequested = FALSE;
	m_BadgeStatus = _T("");
	m_InsuranceDollarAmount = _T("");
	m_Helper = FALSE;
	m_InsuranceRate = _T("");
	m_BackgroundRptRequested = FALSE;
	m_AssignedTo = -1;
	m_MarketId = -1;
	m_Status = -1;
	m_PictureFilename = _T("");
	
	m_nFields = 31;
	
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetSubContractor::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetSubContractor::GetDefaultSQL()
{
	return _T("[dbo].[SubContractors]");
}

void CSetSubContractor::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetSubContractor)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[NickName]"), m_NickName);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[State]"), m_State);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[HomePhoneNumber]"), m_HomePhoneNumber);
	RFX_Text(pFX, _T("[CellPhoneNumber]"), m_CellPhoneNumber);
	RFX_Text(pFX, _T("[Pager]"), m_Pager);
	RFX_Text(pFX, _T("[SSN]"), m_SSN);
	RFX_Bool(pFX, _T("[WorkmansCompInsuranceOK]"), m_WorkmansCompInsuranceOK);
	RFX_Bool(pFX, _T("[LiabilityInsuranceOK]"), m_LiabilityInsuranceOK);
	RFX_Date(pFX, _T("[WorkmansCompInsuranceDate]"), m_WorkmansCompInsuranceDate);
	RFX_Date(pFX, _T("[LiabilityInsuranceDate]"), m_LiabilityInsuranceDate);
	RFX_Date(pFX, _T("[BackgroundChkDateApproved]"), m_BackgroundChkDateApproved);
	RFX_Bool(pFX, _T("[BackgroundCheckPassed]"), m_BackgroundCheckPassed);
	RFX_Text(pFX, _T("[Notes]"), m_Notes);
	RFX_Text(pFX, _T("[Retainage]"), m_Retainage);
	RFX_Text(pFX, _T("[RetainageRate]"), m_RetainageRate);
	RFX_Double(pFX, _T("[SavingsRate]"), m_SavingsRate);
	RFX_Text(pFX, _T("[InsuranceRate]"), m_InsuranceRate);
	RFX_Bool(pFX, _T("[Helper]"), m_Helper);
	RFX_Bool(pFX, _T("[BackgroundRptRequested]"), m_BackgroundRptRequested);
	RFX_Text(pFX, _T("[InsuranceDollarAmount]"), m_InsuranceDollarAmount);
	RFX_Text(pFX, _T("[BadgeStatus]"), m_BadgeStatus);
	RFX_Long(pFX, _T("[AssignedTo]"), m_AssignedTo);
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Long(pFX, _T("[Status]"), m_Status);
	RFX_Text(pFX, _T("[PictureFilename]"), m_PictureFilename);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetSubContractor diagnostics

#ifdef _DEBUG
void CSetSubContractor::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetSubContractor::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
