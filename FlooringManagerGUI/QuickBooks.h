/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once


#include "setpayroll.h"	// Added by ClassView

//const char szREGISTRY_KEY_QBSTRINGS[] = "Quickbooks Settings";
const char szSETTINGS_VALUE_QBFILENAME[] = "QBQuickbooksFilename";
const char szSETTINGS_VALUE_ACCOUNTSPAYABLEACCOUNT[] = "QBAccountsPayableAccount";
const char szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT[] = "QBLaborSubcontractAccount";
const char szSETTINGS_VALUE_RETAINAGEACCOUNT[] = "QBRetainageAccount";
const char szSETTINGS_VALUE_SAVINGSACCOUNT[] = "QBSavingsAccount";
//const char szSETTINGS_VALUE_SOFTSURFACECLASS[] = "QBSoftSurfaceClass";
//const char szSETTINGS_VALUE_HARDSURFACECLASS[] = "QBHardSurfaceClass";
const char szSETTINGS_VALUE_COMMERCIALCLASS[] = "QBCommercialClass";
const char szSETTINGS_VALUE_RETAINAGECLASS[] = "QBRetainageClass";
const char szSETTINGS_VALUE_SAVINGSCLASS[] = "QBSavingsClass";
const char szSETTINGS_VALUE_OVERHEADCLASS[] = "QBOverheadClass";
const char szSETTINGS_VALUE_CABINETSCLASS[] = "QBCabinetsClass";
//const char szSETTINGS_VALUE_MEASURECLASS[] = "QBMeasureClass";
const char szSETTINGS_VALUE_WORKMANSCOMPACCOUNT[] = "QBWorkersCompAccount";
const char szSETTINGS_VALUE_WORKMANSCOMPCLASS[] = "QBWorkersCompClass";
const char szSETTINGS_VALUE_OUTPUTFOLDER[] = "QBOutputFolder";


const char szSETTINGS_VALUE_QBFILENAME_DEFAULT[] = "Sub-Contractors.iif";
const char szSETTINGS_VALUE_ACCOUNTSPAYABLEACCOUNT_DEFAULT[] = "Accounts Payable";
const char szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT_DEFAULT[] = "Labor Subcontract";
const char szSETTINGS_VALUE_RETAINAGEACCOUNT_DEFAULT[] = "Retainage - Long Term";
const char szSETTINGS_VALUE_SAVINGSACCOUNT_DEFAULT[] = "Savings";
//const char szSETTINGS_VALUE_SOFTSURFACECLASS_DEFAULT[] = "Home Depot:Soft Surface";
//const char szSETTINGS_VALUE_HARDSURFACECLASS_DEFAULT[] = "Home Depot:Hard Surface";
const char szSETTINGS_VALUE_COMMERCIALCLASS_DEFAULT[] = "Commercial";
const char szSETTINGS_VALUE_RETAINAGECLASS_DEFAULT[] = "Retainage";
const char szSETTINGS_VALUE_SAVINGSCLASS_DEFAULT[] = "Savings";
const char szSETTINGS_VALUE_OVERHEADCLASS_DEFAULT[] = "Overhead";
const char szSETTINGS_VALUE_CABINETSCLASS_DEFAULT[] = "Home Depot:Cabinets";
//const char szSETTINGS_VALUE_MEASURECLASS_DEFAULT[] = "Home Depot:Measures";
const char szSETTINGS_VALUE_WORKMANSCOMPACCOUNT_DEFAULT[] = "Workerscomp";
const char szSETTINGS_VALUE_WORKMANSCOMPCLASS_DEFAULT[] = "Workerscomp";
const char szSETTINGS_VALUE_OUTPUTFOLDER_DEFAULT[] = "C:\\temp\\";

class CQuickBooks
{
public:
	CQuickBooks(void);
	~CQuickBooks(void);

	bool BuildQuickBooksFile( );
	
	double GetGrandTotal();
	COleDateTime GetWeekEnding();

	int GetErrors(CStringArray* pstrStrings);
	int GetWarnings(CStringArray* pstrStrings);

protected:
	double m_fGrandTotal;
	CSetPayroll m_set;

	CString GetWeekEndingString ();
	CString GetSetting(CString strKey, CString strDefault);

	CString OutputRetainage(CString strInstaller, double fRetainage, double dSusbjectToRetainage, double& dPayAmount) ;
	CString OutputInsuranceRetainage(CString strInstaller, double fInsuranceRate, double dSubjectToRetainage, double& dPayAmount) ;
	CString OutputInsuranceRetainage(CString strInstaller, double fInsuranceDollarAmt, double& dPayAmount);
	CString OutputSavings(CString strInstaller, bool bInstallerOk, double fSavings, double dSusbjectToRetainage, double& dPayAmount) ;
	CString OutputHeader(CString strInstaller, double dPayAmount) ;

	bool ValidateDatabase( );

	CString ClassTrans(CString strClass) ;
	bool GetMarketDivisionFromPO( const CString& strPO, const CString& strInstaller, const CString& strClass, CString& strMarket, CString& strDivision );

	CStringArray m_astrErrors;
	CStringArray m_astrWarnings;
};

inline double CQuickBooks::GetGrandTotal()
{
	return m_fGrandTotal;
}

inline COleDateTime CQuickBooks::GetWeekEnding()
{
	COleDateTime timeWE = CGlobals::GetCurrentSystemTime() ;

	timeWE -= COleDateTimeSpan(timeWE.GetDayOfWeek(), 0, 0, 0) ;
	return timeWE;
}

inline int CQuickBooks::GetErrors(CStringArray* pstrStrings)
{
	pstrStrings->RemoveAll();
	pstrStrings->Append(m_astrErrors);
	return pstrStrings->GetCount();
}

inline int CQuickBooks::GetWarnings(CStringArray* pstrStrings)
{
	pstrStrings->RemoveAll();
	pstrStrings->Append(m_astrWarnings);
	return pstrStrings->GetCount();
}