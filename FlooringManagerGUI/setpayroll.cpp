/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// setpayroll.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "setpayroll.h"
#include "odbcinst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPayroll

IMPLEMENT_DYNAMIC(CSetPayroll, CRecordset)

CSetPayroll::CSetPayroll(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetPayroll)
	m_Installer = _T("");
	m_PONumber = _T("");
	m_Name = _T("");
	m_Pay_Amount = _T("");
	m_Comments = _T("");
	m_Chargeback = _T("");
	m_NO_RETAINAGE = 0.0;
	m_Class = _T("") ;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSetPayroll::GetDefaultConnect()
{
	// Get the name of the Excel-ODBC driver 
	// Contibuted by Christopher W. Backen - Thanx Christoper
    char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver = "Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)";
    // Get the names of the installed drivers ("odbcinst.h" has to be included )
   if(!SQLGetInstalledDrivers(szBuf,cbBufMax,& cbBufOut))
        return "";
    
    // Search for the driver...
    do
    {
        if( strstr( pszBuf, "xlsx" ) != 0 )
        {
            // Found !
            sDriver = CString( pszBuf );
            break;
        }
        pszBuf = strchr( pszBuf, '\0' ) + 1;
    }
    while( pszBuf[1] != '\0' );
//    return sDriver;
	CString sSql;
    CString sItem1, sItem2;
    CString sDsn;
    CString sFile = "s:\\Sub-Contractors.xlsx";        // the file name. Could also be something like C:\\Sheets\\WhatDoIKnow.xls
    
    // Retrieve the name of the Excel driver. This is 
    // necessary because Microsoft tends to use language
    // specific names like "Microsoft Excel Driver (*.xls)" versus
    // "Microsoft Excel Treiber (*.xls)"
    if( sDriver.IsEmpty() )
    {
        // Blast! We didn4t find that driver!
        AfxMessageBox("No Excel ODBC driver found");
//        return;
    }
    
    // Create a pseudo DSN including the name of the Driver and the Excel file
    // so we don4t have to have an explicit DSN installed in our ODBC admin
//    sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s;",sDriver,sFile);
    sDsn.Format("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=s:\\Sub-Contractors.xlsx;",sDriver,sFile);
	return sDsn;
//	return _T("ODBC;DSN=FlooringSub");
}

CString CSetPayroll::GetDefaultSQL()
{
	return _T("[Current]");
}

void CSetPayroll::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetPayroll)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
	RFX_Text(pFX, _T("[Installer]"), m_Installer);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[PO Number]"), m_PONumber);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Pay Amount]"), m_Pay_Amount);
	RFX_Text(pFX, _T("[Comments]"), m_Comments);
	RFX_Text(pFX, _T("[Chargeback]"), m_Chargeback);
	RFX_Double(pFX, _T("[NO RETAINAGE]"), m_NO_RETAINAGE);
	RFX_Text(pFX, _T("[Class]"), m_Class) ;
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetPayroll diagnostics

#ifdef _DEBUG
void CSetPayroll::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPayroll::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

