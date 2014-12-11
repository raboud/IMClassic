/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SeOrderCustomDetails.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SeOrderCustomDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOrderCustomDetails

IMPLEMENT_DYNAMIC(CSetOrderCustomDetails, CRecordset)

CSetOrderCustomDetails::CSetOrderCustomDetails(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOrderCustomDetails)
	m_OrderCustomID = 0;
	m_OrderID = 0;
	m_SubContractorID = 0;
	m_RetailPrice = _T("");
	m_UnitPrice = _T("");
	m_UnitCost = _T("");
	m_Quanity = 0.0;
	m_Description = _T("");
	m_UnitOfMeasureID = 0;
	m_NotOnInvoice = FALSE;
	m_NotOnWorkOrder = FALSE;
	m_Deleted = FALSE ;
	m_EntryMethodID = 0;
	m_Reviewed = FALSE;
	m_ReviewedBy = 0;
	m_ReviewedDate;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetOrderCustomDetails::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetOrderCustomDetails::GetDefaultSQL()
{
	return _T("[dbo].[OrderCustomDetails]");
}

void CSetOrderCustomDetails::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOrderCustomDetails)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Long(pFX, _T("[OrderCustomID]"), m_OrderCustomID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Long(pFX, _T("[SubContractorID]"), m_SubContractorID);
	RFX_Text(pFX, _T("[RetailPrice]"), m_RetailPrice);
	RFX_Text(pFX, _T("[UnitCost]"), m_UnitCost);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Double(pFX, _T("[Quanity]"), m_Quanity);
	RFX_Text(pFX, _T("[Description]"), m_Description, 1024);
//	RFX_Double(pFX, _T("[Multiplier]"), m_Multiplier);
//	RFX_Double(pFX, _T("[CostMultiplier]"), m_CostMultiplier);
	RFX_Long(pFX, _T("[UnitOfMeasureID]"), m_UnitOfMeasureID);
	RFX_Bool(pFX, _T("[NotOnInvoice]"), m_NotOnInvoice);
	RFX_Bool(pFX, _T("[NotOnWorkOrder]"), m_NotOnWorkOrder);
	RFX_Bool(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Long(pFX, _T("[EntryMethodID]"), m_EntryMethodID);
	RFX_Bool(pFX, _T("[Reviewed]"), m_Reviewed);
	RFX_Long(pFX, _T("[ReviewedByID]"), m_ReviewedBy);
	RFX_Date(pFX, _T("[ReviewedDate]"), m_ReviewedDate);

	pFX->m_prs->ClearNullFieldStatus(7) ;
//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOrderCustomDetails diagnostics

#ifdef _DEBUG
void CSetOrderCustomDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrderCustomDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
