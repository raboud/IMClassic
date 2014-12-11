/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetMarket.h : Implementation of the CSetMarket class
// code generated on Wednesday, May 08, 2002, 4:51 PM

#include "stdafx.h"
#include "SetMarket.h"
IMPLEMENT_DYNAMIC(CSetMarket, CRecordset)

CSetMarket::CSetMarket(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_MarketId = 0;
	m_MarketName = "";
	//m_BranchPrinterName = _T("") ;
	//m_BranchPrinterPort = _T("") ;
	//m_BranchPrinterDriver = _T("") ;
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CSetMarket::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring");
}

CString CSetMarket::GetDefaultSQL()
{
	return _T("[dbo].[Market]");
}

void CSetMarket::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[MarketId]"), m_MarketId);
	RFX_Text(pFX, _T("[MarketName]"), m_MarketName);
	//RFX_Text(pFX, _T("[BranchPrinterName]"), m_BranchPrinterName);
	//RFX_Text(pFX, _T("[BranchPrinterPort]"), m_BranchPrinterPort) ;
	//RFX_Text(pFX, _T("[BranchPrinterDriver]"), m_BranchPrinterDriver) ;

}
/////////////////////////////////////////////////////////////////////////////
// CSetMarket diagnostics

#ifdef _DEBUG
void CSetMarket::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetMarket::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


