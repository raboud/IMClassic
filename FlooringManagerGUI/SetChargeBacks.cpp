/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetChargeBacks.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetChargeBacks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetChargeBacks

IMPLEMENT_DYNAMIC(CSetChargeBacks, CRecordset)

CSetChargeBacks::CSetChargeBacks(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetChargeBacks)
	m_ChargeBackID = 0;
	m_Amount = _T("");
//	m_CheckAmount = _T("");
//	m_CheckNumber = _T("");
	m_SubcontractorID = 0;
	m_AmountToSub = _T("");
	m_Number = _T("");
	m_Name = _T("");
	m_Reason = _T("");
	m_OriginalPO = _T("");
//	m_DivisionID = 0;
//	m_MarketID = 0;
	m_CostAdjustment = FALSE ;
	m_Approved = FALSE ;
	m_IssueDate = COleDateTime(CGlobals::GetCurrentSystemTime());
//	m_CheckDate = COleDateTime(CGlobals::GetCurrentSystemTime());
	m_OrderID = 0;
	m_ApprovalNumber = 0 ;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CSetChargeBacks::GetDefaultSQL()
{
	return _T("[dbo].[ChargeBacks]");
}

void CSetChargeBacks::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetChargeBacks)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[ChargeBackID]"), m_ChargeBackID);
//	RFX_Text(pFX, _T("[CheckAmount]"), m_CheckAmount);
//	RFX_Text(pFX, _T("[CheckNumber]"), m_CheckNumber);
	RFX_Long(pFX, _T("[SubcontractorID]"), m_SubcontractorID);
	RFX_Text(pFX, _T("[AmountToSub]"), m_AmountToSub);
	RFX_Text(pFX, _T("[Number]"), m_Number);
	RFX_Text(pFX, _T("[Name]"), m_Name);
//	RFX_Date(pFX, _T("[CheckDate]"), m_CheckDate);
	RFX_Date(pFX, _T("[IssueDate]"), m_IssueDate);
	RFX_Text(pFX, _T("[OriginalPO]"), m_OriginalPO);
	//}}AFX_FIELD_MAP
	RFX_Text(pFX, _T("[Amount]"), m_Amount, 255, SQL_DECIMAL, 2);
	RFX_Text(pFX, _T("[Reason]"), m_Reason, 2000);
//	RFX_Long(pFX, _T("[MarketID]"), m_MarketID);
//	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Bool(pFX, _T("[CostAdjustment]"), m_CostAdjustment);
	RFX_Bool(pFX, _T("[Approved]"), m_Approved) ;
	RFX_Long(pFX, _T("[ApprovalNumber]"), m_ApprovalNumber);
}

/////////////////////////////////////////////////////////////////////////////
// CSetChargeBacks diagnostics

#ifdef _DEBUG
void CSetChargeBacks::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetChargeBacks::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
