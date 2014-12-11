// SetvwChargeback.h : Implementation of the CSetvwChargeback class



// CSetvwChargeback implementation

// code generated on Wednesday, May 28, 2003, 11:49 PM

#include "stdafx.h"
#include "SetvwChargeback.h"
IMPLEMENT_DYNAMIC(CSetvwChargeback, CRecordset)

CSetvwChargeback::CSetvwChargeback(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ChargeBackID = 0;
	m_Amount = 0.0;
	m_SubcontractorID = 0;
	m_AmountToSub = 0.0;
	m_Number = L"";
	m_Name = L"";
	m_Reason = L"";
	m_IssueDate;
	m_OriginalPO = L"";
	m_CostAdjustment = FALSE;
	m_OrderID = 0;
	m_ApprovalNumber = 0;
	m_Approved = FALSE;
	m_Balance = 0.0;
	m_FirstName = "";
	m_LastName = "";
	m_VendorID = 0;
	m_nFields = 17;
	m_nDefaultType = dynaset;
}

CString CSetvwChargeback::GetDefaultSQL()
{
	return _T("[dbo].[vwChargeback]");
}

void CSetvwChargeback::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ChargeBackID]"), m_ChargeBackID);
	RFX_Double(pFX, _T("[Amount]"), m_Amount);
	RFX_Long(pFX, _T("[SubcontractorID]"), m_SubcontractorID);
	RFX_Double(pFX, _T("[AmountToSub]"), m_AmountToSub);
	RFX_Text(pFX, _T("[Number]"), m_Number);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Reason]"), m_Reason, 2000);
	RFX_Date(pFX, _T("[IssueDate]"), m_IssueDate);
	RFX_Text(pFX, _T("[OriginalPO]"), m_OriginalPO);
	RFX_Bool(pFX, _T("[CostAdjustment]"), m_CostAdjustment);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[ApprovalNumber]"), m_ApprovalNumber);
	RFX_Bool(pFX, _T("[Approved]"), m_Approved);
	RFX_Double(pFX, _T("[Balance]"), m_Balance);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Long(pFX, _T("[VendorID]"), m_VendorID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetvwChargeback diagnostics

#ifdef _DEBUG
void CSetvwChargeback::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetvwChargeback::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


