/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetOrderOptionsDetails.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SetOrderOptionsDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOrderOptionsDetails

IMPLEMENT_DYNAMIC(CSetOrderOptionsDetails, CRecordset)

CSetOrderOptionsDetails::CSetOrderOptionsDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOrderOptionsDetails)
	m_OrdeOptionslID = 0;
	m_OrderID = 0;
	m_OptionID = 0;
	m_Quantity = 0.0;
	m_UnitPrice = _T("");
	m_SubContractorID = 0;
	m_UnitCost = _T("");
	m_UnitRetail = _T("");
	m_EntryMethodID = 0;
	m_PrintOnInvoice = FALSE;
	m_PrintOnWO = FALSE;
	m_Deleted = FALSE;
	m_Reviewed = FALSE;
	m_ReviewedBy = 0;
	m_ReviewedDate;
	m_SubContractorPaid = 0;
	m_SubContractorPay = 0.0;
	m_nFields = 17;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CSetOrderOptionsDetails::GetDefaultSQL()
{
	return _T("[dbo].[Order Options Details]");
}

void CSetOrderOptionsDetails::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOrderOptionsDetails)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[OrdeOptionslID]"), m_OrdeOptionslID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[OptionID]"), m_OptionID);
	RFX_Double(pFX, _T("[Quantity]"), m_Quantity);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[UnitRetail]"), m_UnitRetail);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[PrintOnInvoice]"), m_PrintOnInvoice);
	RFX_Bool(pFX, _T("[PrintOnWO]"), m_PrintOnWO);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[ReviewedDate]"), m_ReviewedDate);
	RFX_Bool(pFX, _T("[SubContractorPaid]"), m_SubContractorPaid);
	RFX_Double(pFX, _T("[SubContractorPay]"), m_SubContractorPay);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOrderOptionsDetails diagnostics

#ifdef _DEBUG
void CSetOrderOptionsDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderOptionsDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
