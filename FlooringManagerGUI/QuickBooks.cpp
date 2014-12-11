/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "flooring.h"
#include "quickbooks.h"
#include "SetSubContractor.h"
#include "SetOrders.h"
#include "SetPOMarketDivision.h"
#include "TransactionDetailsDialog.h"
#include "SetSettings.h"
#include "SetStores.h"
#include "SetMarket.h"
#include "DlgInsuranceQuestion.h"
#include "DlgSubContractorInsurance.h"

CQuickBooks::CQuickBooks(void)
{
	m_set.m_strSort = "[Installer], [Date]" ;
	m_set.Open() ;
	m_fGrandTotal = 0.0 ;
}

CQuickBooks::~CQuickBooks(void)
{
	m_set.Close() ;
}

bool CQuickBooks::BuildQuickBooksFile( )
{
	CWaitCursor wait;
	bool bSuccess = ValidateDatabase( );
	wait.Restore();

	if (!bSuccess)
	{
		// we have errors and cannot continue
		return false;
	}

	try
	{
		
		CString strFilename = GetSetting(szSETTINGS_VALUE_QBFILENAME, szSETTINGS_VALUE_QBFILENAME_DEFAULT);
		CString strPath = GetSetting(szSETTINGS_VALUE_OUTPUTFOLDER, szSETTINGS_VALUE_OUTPUTFOLDER_DEFAULT);
		strFilename = strPath + strFilename;
		
		CStdioFile fileOut(strFilename, CFile::modeCreate | CFile::modeWrite | CFile::typeText) ;

		fileOut.WriteString("!TRNS\tTRNSTYPE\tACCNT\tNAME\tDATE\tMEMO\tAMOUNT\n") ;
		fileOut.WriteString("!SPL\tTRNSTYPE\tACCNT\tAMOUNT\tMEMO\tCLASS\n") ;
		fileOut.WriteString("!ENDTRNS\n") ;

		CString strOutput ;

		double dPayAmount = 0 ;
		double dSubjectToRetainage = 0 ;
		strOutput = "" ;
		CString strInstaller = "" ;
		bool bInstallersOk = true ;

		m_fGrandTotal = 0.0 ;
		CSetSubContractor setSub(&g_dbFlooring);
		setSub.m_strFilter = "SubContractorID = -1";
		setSub.Open() ;

		double fRetainage = 0.0;
		double fSavings = 0.0;
		double fInsuranceRate = 0.0 ;
		double fInsuranceDollarAmt = 0.0 ;

		m_set.MoveFirst();

		CString strMarket;
		CString strDivision;

		bool bLiabilityExpired = false;
		bool bWorkmansCompExpired = false;

		while(!m_set.IsEOF())
		{
			if (strInstaller != m_set.m_Installer)
			{
				// about to switch installers
				if (strInstaller != "")
				{
					// this is not the first installer so output last installers retainage ;
					strOutput += (OutputRetainage(strInstaller, fRetainage, dSubjectToRetainage, dPayAmount)) ;
					
					bLiabilityExpired = setSub.IsFieldNull(&setSub.m_LiabilityInsuranceDate) || (setSub.m_LiabilityInsuranceDate < CGlobals::GetCurrentSystemTime()) || (setSub.m_LiabilityInsuranceOK == false);
					bWorkmansCompExpired = setSub.IsFieldNull(&setSub.m_WorkmansCompInsuranceDate) || (setSub.m_WorkmansCompInsuranceDate < CGlobals::GetCurrentSystemTime()) || (setSub.m_WorkmansCompInsuranceOK == false);
					
					if ((fInsuranceRate > 0.0) && (bLiabilityExpired || bWorkmansCompExpired))
					{
						strOutput += (OutputInsuranceRetainage(strInstaller, fInsuranceRate, dSubjectToRetainage, dPayAmount)) ;
					}
					else if ((fInsuranceDollarAmt > 0.0) && (bLiabilityExpired || bWorkmansCompExpired))
					{
						strOutput += (OutputInsuranceRetainage(strInstaller, fInsuranceDollarAmt, dPayAmount)) ;
					}
					strOutput += (OutputSavings(strInstaller, bInstallersOk, fSavings, dSubjectToRetainage, dPayAmount)) ;
					if (dPayAmount < 0.0)
					{
						CString strMessage ;
						strMessage.Format("ERROR: Bill for %s cannot be negative. Payroll processing cannot complete until this is corrected. %f %f", strInstaller.MakeUpper(), dSubjectToRetainage, dPayAmount) ;
						m_astrErrors.Add(strMessage);
					}
					fileOut.WriteString(OutputHeader(strInstaller, dPayAmount)) ;
					fileOut.WriteString(strOutput) ;
					fileOut.WriteString("ENDTRNS\n") ;
				}

				CString strLastName = m_set.m_Installer.Left(m_set.m_Installer.Find(',') );
				CString strFirstName = m_set.m_Installer.Mid(m_set.m_Installer.Find(',') + 2);
				setSub.m_strFilter.Format("[LastName] = '%s' AND [FirstName] = '%s'", strLastName, strFirstName) ;
				setSub.Requery() ;
				fRetainage = atof(setSub.m_RetainageRate) ;
				fInsuranceRate = atof(setSub.m_InsuranceRate) ;
				fInsuranceDollarAmt = atof(setSub.m_InsuranceDollarAmount);
				fSavings  = setSub.m_SavingsRate ;

				// start a new installer
				dSubjectToRetainage = 0 ;
				dPayAmount = 0 ;
				strOutput = "" ;
				strInstaller = m_set.m_Installer ;

			}

			CString strAccount = GetSetting(szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT, szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT_DEFAULT);
			
			CString strTransaction ;
			if (atof(m_set.m_Pay_Amount) >= 0)
			{
				if (!m_set.m_NO_RETAINAGE)
				{
					dSubjectToRetainage += atof(m_set.m_Pay_Amount) ;
				}
			}
			CString strError = "";
			strTransaction.Format("SPL\tBILL\t%s\t%7.2f\t%s\t%s\n", 
				strAccount, 
				atof(m_set.m_Pay_Amount), 
				m_set.m_Name,
				ClassTrans(m_set.m_Class)) ;

			dPayAmount += atof(m_set.m_Pay_Amount) ;
			strOutput += strTransaction ;
			if (m_set.m_Chargeback != "")
			{
				CString strChargeBack ;
				strAccount = GetSetting(szSETTINGS_VALUE_RETAINAGEACCOUNT, szSETTINGS_VALUE_RETAINAGEACCOUNT_DEFAULT);
				strAccount = strAccount + ":" + m_set.m_Chargeback ;

				
				CString strAccount2 = GetSetting(szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT, szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT_DEFAULT);

				strChargeBack.Format("TRNS\tGeneral Journal\t%s\tAdjustment\t%s\t%s\t%7.2f\nSPL\tGeneral Journal\t%s\t%7.2f\t%s\nENDTRNS\n", 
					strAccount, 
					m_set.m_Date.Format("%m/%d/%Y"), 
					strInstaller + " - " + m_set.m_Name, 
					atof(m_set.m_Pay_Amount), 
					strAccount2,
					atof(m_set.m_Pay_Amount) * -1.0, 
					strInstaller + " - " + m_set.m_Name) ;
				fileOut.WriteString(strChargeBack) ;
			}

			m_fGrandTotal += atof(m_set.m_Pay_Amount);

			m_set.MoveNext() ;
		}

		if (bInstallersOk)
		{

			// Retainage for last guy
			strOutput += (OutputRetainage(strInstaller, fRetainage, dSubjectToRetainage, dPayAmount)) ;

			bLiabilityExpired = setSub.IsFieldNull(&setSub.m_LiabilityInsuranceDate) || (setSub.m_LiabilityInsuranceDate < CGlobals::GetCurrentSystemTime()) || (setSub.m_LiabilityInsuranceOK == false);
			bWorkmansCompExpired = setSub.IsFieldNull(&setSub.m_WorkmansCompInsuranceDate) || (setSub.m_WorkmansCompInsuranceDate < CGlobals::GetCurrentSystemTime()) || (setSub.m_WorkmansCompInsuranceOK == false);

			if ((fInsuranceRate > 0.0) && (bLiabilityExpired || bWorkmansCompExpired))
			{
				strOutput += (OutputInsuranceRetainage(strInstaller, fInsuranceRate, dSubjectToRetainage, dPayAmount)) ;
			}
			else if ((fInsuranceDollarAmt > 0.0) && (bLiabilityExpired || bWorkmansCompExpired))
			{
				strOutput += (OutputInsuranceRetainage(strInstaller, fInsuranceDollarAmt, dPayAmount)) ;
			}
			strOutput += (OutputSavings(strInstaller, bInstallersOk, fSavings, dSubjectToRetainage, dPayAmount)) ;
			if (dPayAmount < 0.0)
			{
				CString strMessage ;
				strMessage.Format("ERROR: Bill for %s cannot be negative. Payroll processing cannot complete until this is corrected.", strInstaller.MakeUpper()) ;
				m_astrErrors.Add(strMessage);
			}
			else
			{
				fileOut.WriteString(OutputHeader(strInstaller, dPayAmount)) ;
				fileOut.WriteString(strOutput) ;
				fileOut.WriteString("ENDTRNS\n") ;
				bSuccess = true;
			}
		}
		fileOut.Close() ;
	}
	catch (CException* pE)
	{
		TCHAR   szCause[255];
		CString strFormatted;

		pE->GetErrorMessage(szCause, 255);

		strFormatted = _T("ERROR: Exception Thrown: ");
		strFormatted += szCause;

		m_astrErrors.Add(strFormatted);

		pE->Delete() ;
	}

	if (m_astrErrors.GetCount() > 0)
	{
		bSuccess = false;
	}

	return bSuccess;
}

// retrieves the value of the specified key, or a default value
CString CQuickBooks::GetSetting(CString strKey, CString strDefault)
{
	// retrieve the setting value based on the strKey (the Name of the setting)
	// these settings don't use UserID, therefore called with default params
	CSetSettings setSettings(&g_dbFlooring);
	CString strValue = setSettings.GetSetting(strKey);

	// return default if key is not found
	if (strKey.GetLength() == 0)
	{
		strValue = strDefault;
	}
	
	return strValue;
}

CString CQuickBooks::OutputRetainage(CString strInstaller, double fRetainage, double dSubjectToRetainage, double& dPayAmount)
{
	CString strOutput = "" ;

	if ((dSubjectToRetainage > 0) && (fRetainage > 0.0))
	{
		double dRet = -1.0 * dSubjectToRetainage * fRetainage;
		long lRet = long((dRet * 100) - .5) ;
		dRet = lRet / 100. ;

		if (fRetainage == 1.0)
		{
			dRet = -1.0 * dSubjectToRetainage ;
		}
		CString strAccount = GetSetting(szSETTINGS_VALUE_RETAINAGEACCOUNT, szSETTINGS_VALUE_RETAINAGEACCOUNT_DEFAULT);
		CString strClass = GetSetting(szSETTINGS_VALUE_RETAINAGECLASS, szSETTINGS_VALUE_RETAINAGECLASS_DEFAULT);

		// Retainage
		strOutput.Format("SPL\tBILLCRED\t%s:%s\t%7.2f\t%s %.0f%%\n", 
			strAccount,
			strInstaller, 
			dRet,
			strClass,
			fRetainage * 100.) ;

		m_fGrandTotal += dRet ;
		dPayAmount +=  dRet ;
	}
	return strOutput ;
}

CString CQuickBooks::OutputInsuranceRetainage(CString strInstaller, double fInsuranceRate, double dSubjectToRetainage, double& dPayAmount)
{
	CString strOutput = "" ;

	if (fInsuranceRate > 1.0)
	{
		CString strTemp;
		strTemp.Format("ERROR: Insurance Retainage Rate for %s is greater than 100%%.", strInstaller.MakeUpper());
		m_astrErrors.Add(strTemp);
	}

	if ((dSubjectToRetainage > 0) && (fInsuranceRate > 0.0))
	{
		double dRet = -1.0 * dSubjectToRetainage * fInsuranceRate;
		long lRet = long((dRet * 100) - .5) ;
		dRet = lRet / 100. ;
		CString strAccount = GetSetting(szSETTINGS_VALUE_WORKMANSCOMPACCOUNT, szSETTINGS_VALUE_WORKMANSCOMPACCOUNT_DEFAULT);
		CString strClass = GetSetting(szSETTINGS_VALUE_WORKMANSCOMPCLASS, szSETTINGS_VALUE_WORKMANSCOMPCLASS_DEFAULT);

		// WorkerComp
		strOutput.Format("SPL\tBILLCRED\t%s:%s\t%7.2f\t%s %.0f%%\n", 
			strAccount,
			strInstaller, 
			dRet,
			strClass,
			fInsuranceRate * 100.) ;

		m_fGrandTotal += dRet ;
		dPayAmount +=  dRet ;
	}
	return strOutput ;
}

CString CQuickBooks::OutputInsuranceRetainage(CString strInstaller, double fInsuranceDollarAmt, double& dPayAmount)
{
	CString strOutput = "" ;

	if (fInsuranceDollarAmt > 0.0)
	{
		double dRet = -1.0 * fInsuranceDollarAmt;
		CString strAccount = GetSetting(szSETTINGS_VALUE_WORKMANSCOMPACCOUNT, szSETTINGS_VALUE_WORKMANSCOMPACCOUNT_DEFAULT);
		CString strClass = GetSetting(szSETTINGS_VALUE_WORKMANSCOMPCLASS, szSETTINGS_VALUE_WORKMANSCOMPCLASS_DEFAULT);

		// WorkerComp
		strOutput.Format("SPL\tBILLCRED\t%s:%s\t%7.2f\t%s\n", 
			strAccount,
			strInstaller, 
			dRet,
			strClass) ;

		m_fGrandTotal += dRet ;
		dPayAmount +=  dRet ;
	}
	return strOutput ;
}

CString CQuickBooks::OutputSavings(CString strInstaller, bool bInstallersOk, double fSavings, double dSubjectToRetainage, double& dPayAmount) 
{
	CString strOutput = "" ;

	if ((dSubjectToRetainage > 0) && (bInstallersOk) && (fSavings > 0.0))
	{
		double dSave = dSubjectToRetainage * -1 * fSavings;
		long lSave = long ((dSave * 100) - .5) ;
		dSave = lSave / 100. ;
		CString strAccount = GetSetting(szSETTINGS_VALUE_SAVINGSACCOUNT, szSETTINGS_VALUE_SAVINGSACCOUNT_DEFAULT);
		CString strClass = GetSetting(szSETTINGS_VALUE_SAVINGSCLASS, szSETTINGS_VALUE_SAVINGSCLASS_DEFAULT);

		// Savings 
		strOutput.Format("SPL\tBILLCRED\t%s:%s\t%7.2f\t%s %.0f%%\n",
			strAccount,
			strInstaller, 
			dSave,
			strClass,
			fSavings * 100.) ;

		m_fGrandTotal += -1.0 * dSave ;
		dPayAmount += -1.0 * dSave ;
	}
	return strOutput ;
}

CString CQuickBooks::OutputHeader(CString strInstaller, double dPayAmount)
{
	CString strOutput ;
	CString strAccount = GetSetting(szSETTINGS_VALUE_ACCOUNTSPAYABLEACCOUNT, szSETTINGS_VALUE_ACCOUNTSPAYABLEACCOUNT_DEFAULT);
	strOutput.Format("TRNS\tBILL\t%s\t%s\t%s\t%s\t%7.2f\n",
		strAccount,
		strInstaller, 
		GetWeekEndingString(),
		"",
		dPayAmount * -1.0) ;
	return strOutput ;
}

CString CQuickBooks::ClassTrans(CString strClass)
{
	CString strOutput = "";
	CString strMarket;
	CString strDivision;

	if (GetMarketDivisionFromPO(m_set.m_PONumber, m_set.m_Installer, strClass, strMarket, strDivision))
	{
		strMarket.Trim();
		strDivision.Trim();
		strOutput.Format("Home Depot:%s:%s", strMarket, strDivision);
	}
	else
	{
		if (strClass.CompareNoCase("C") == 0)
		{
			strOutput = GetSetting(szSETTINGS_VALUE_COMMERCIALCLASS, szSETTINGS_VALUE_COMMERCIALCLASS_DEFAULT) ;
		}
		else if (strClass.CompareNoCase("O") == 0)
		{
			strOutput = GetSetting(szSETTINGS_VALUE_OVERHEADCLASS, szSETTINGS_VALUE_OVERHEADCLASS_DEFAULT);
		}
		else if (strClass.CompareNoCase("K") == 0)
		{
			strOutput = GetSetting(szSETTINGS_VALUE_CABINETSCLASS, szSETTINGS_VALUE_CABINETSCLASS_DEFAULT);
		}
	}

	ASSERT(strOutput.GetLength() > 0);

	return strOutput ;
}

CString CQuickBooks::GetWeekEndingString()
{
	COleDateTime timeWE = CGlobals::GetCurrentSystemTime() ;

	timeWE -= COleDateTimeSpan(timeWE.GetDayOfWeek(), 0, 0, 0) ;
	return timeWE.Format("%m/%d/%Y") ;
}

bool CQuickBooks::ValidateDatabase( )
{
	m_astrErrors.RemoveAll();
	m_astrWarnings.RemoveAll();
	
	try
	{
		CSetSubContractor setSub(&g_dbFlooring) ;
		CSetOrders setOrders(&g_dbFlooring);
		CSetStores setStores(&g_dbFlooring);
		CString strMessage = "";

		// parse spreadsheet and make sure all subcontractors are in the subcontractors database and the PO Numbers
		// are OK
		m_set.MoveFirst();
		
		setSub.m_strFilter = "SubContractorID = -1";
		setSub.Open() ;
		
		setOrders.m_strFilter = "OrderID = -1";
		setOrders.Open();

		setStores.m_strFilter = "StoreID = -1";
		setStores.Open();

		CString strPrevSubName = "";
		CString strLastName = "";
		CString strFirstName = "";

		while (!m_set.IsEOF())
		{
			CString strInstaller = m_set.m_Installer ;
			
			if (strInstaller != strPrevSubName)
			{
				strPrevSubName = strInstaller;
				strLastName = strInstaller.Left(strInstaller.Find(',') );
				strFirstName = strInstaller.Mid(strInstaller.Find(',') + 2);

				// validate installer name
				setSub.m_strFilter.Format("[LastName] = '%s' AND [FirstName] = '%s'", strLastName, strFirstName) ;
				setSub.Requery();

				if (setSub.IsEOF())
				{
					strMessage.Format("ERROR: %s is not in the SubContractors database.", m_set.m_Installer) ;
					m_astrErrors.Add(strMessage);
				}
				else if (setSub.m_Status != 1)  // not active
				{
					strMessage.Format("ERROR: %s is not ACTIVE in the SubContractors database.", m_set.m_Installer) ;
					m_astrErrors.Add(strMessage);
				}
				else
				{
					// sub is in the DB and ACTIVE - need to check his insurance
					bool bLiabilityExpired = setSub.IsFieldNull(&setSub.m_LiabilityInsuranceDate) || (setSub.m_LiabilityInsuranceDate < CGlobals::GetCurrentSystemTime()) || (setSub.m_LiabilityInsuranceOK == false);
					bool bWorkmansCompExpired = setSub.IsFieldNull(&setSub.m_WorkmansCompInsuranceDate) || (setSub.m_WorkmansCompInsuranceDate < CGlobals::GetCurrentSystemTime()) || (setSub.m_WorkmansCompInsuranceOK == false);
					bool bInsuranceRetainGTZero = (atof(setSub.m_InsuranceDollarAmount) > 0) || (atof(setSub.m_InsuranceRate) > 0);
					if ((bLiabilityExpired || bWorkmansCompExpired) && !bInsuranceRetainGTZero)
					{
						// gotta ask about this one...expired insurance and not taking anything out for it...
						CString strMessage;
						if (bLiabilityExpired && bWorkmansCompExpired)
						{
							strMessage.Format("WORKMANS COMP and LIABILITY insurance for %s, %s is expired, and nothing is being deducted.  Do you wish to correct this now?", setSub.m_LastName, setSub.m_FirstName);
						}
						else if (bLiabilityExpired)
						{
							strMessage.Format("LIABILITY insurance for %s, %s is expired, and nothing is being deducted.  Do you wish to correct this now?", setSub.m_LastName, setSub.m_FirstName);
						}
						else
						{
							strMessage.Format("WORKMANS COMP insurance for %s, %s is expired, and nothing is being deducted.  Do you wish to correct this now?", setSub.m_LastName, setSub.m_FirstName);
						}

						CDlgInsuranceQuestion dlgQuestion;
						dlgQuestion.SetMessage(strMessage);
						int iResponse = dlgQuestion.DoModal();
						if (iResponse == IDCANCEL)
						{
							if (dlgQuestion.GetCancelPayroll() == true)
							{
								m_astrErrors.RemoveAll();
								m_astrWarnings.RemoveAll();
								return false;
							}
						}

						if (iResponse == IDOK)
						{
							// need to enter insurance info
							DlgSubContractorInsurance dlg;
							dlg.SetSubContractorID(setSub.m_SubContractorID);
							if (dlg.DoModal() != IDOK)
							{
								iResponse = MessageBox(NULL, "Cancel Payroll Processing?", "Question", MB_YESNO);
								if (iResponse == IDYES)
								{
									m_astrErrors.RemoveAll();
									m_astrWarnings.RemoveAll();
									return false;
								}
							}
						}
					}
				}
			}
		
			// validate the PO Number

			if ( m_set.m_PONumber.GetLength() == 8 )
			{
				setOrders.m_strFilter.Format("[PurchaseOrderNumber] = '%s'", m_set.m_PONumber);
				setOrders.Requery();
				
				if (setOrders.IsEOF())
				{
					strMessage.Format("ERROR: P.O. Number %s not found. Installer: %s, Cust. Name: %s", m_set.m_PONumber,m_set.m_Installer, m_set.m_Name);
					m_astrErrors.Add(strMessage);
				}
			}
			else if ( m_set.m_PONumber.GetLength() == 4 )
			{
				setStores.m_strFilter.Format("[StoreNumber] = '%s'", m_set.m_PONumber);
				setStores.Requery();
				if (setStores.IsEOF())
				{
					strMessage.Format("ERROR: P.O. Number %s is not a valid Store Number.  Installer: %s, Cust. Name: %s", m_set.m_PONumber, m_set.m_Installer,m_set.m_Name );
					m_astrErrors.Add(strMessage);
				}
				
				if ( (m_set.m_Class.CompareNoCase("H") != 0) &&  (m_set.m_Class.CompareNoCase("S") != 0) && (m_set.m_Class.CompareNoCase("K") != 0))
				{
					if (m_set.m_Class.GetLength() > 0)
					{
						strMessage.Format("ERROR: Class '%s' is wrong for P.O. Number %s (Only H or S  or K are valid).  Installer: %s, Cust. Name: %s", m_set.m_Class, m_set.m_PONumber, m_set.m_Installer,m_set.m_Name );
					}
					else
					{
						strMessage.Format("ERROR: No Class specified for P.O. Number %s (Only H or S or K are valid).  Installer: %s, Cust. Name: %s", m_set.m_PONumber, m_set.m_Installer,m_set.m_Name );
					}
					m_astrErrors.Add(strMessage);
				}
			}
			else if (m_set.m_PONumber.GetLength() == 0)
			{
				if ( (m_set.m_Class.CompareNoCase("O") != 0) &&  (m_set.m_Class.CompareNoCase("C") != 0))
				{
					if (m_set.m_Class.GetLength() > 0)
					{
						strMessage.Format("ERROR: Class '%s' is wrong for a blank P.O. Number (Only C or O are valid).  Installer: %s, Cust. Name: %s", m_set.m_Class, m_set.m_Installer,m_set.m_Name );
					}
					else
					{
						strMessage.Format("ERROR: No Class specified for blank P.O. Number (Only C or O are valid).  Installer: %s, Cust. Name: %s", m_set.m_Installer, m_set.m_Name );
					}
					m_astrErrors.Add(strMessage);
				}
			}
			else
			{
				strMessage.Format("ERROR: P.O. Number %s is invalid.  Installer: %s, Cust. Name: %s", m_set.m_PONumber, m_set.m_Installer,m_set.m_Name );
				m_astrErrors.Add(strMessage);
			}
			
			m_set.MoveNext();
		}
		setSub.Close() ;
		setOrders.Close();
		setStores.Close();
	}
	catch (CDBException* pDBException)
	{
		CString strMessage;
		strMessage.Format("ERROR: Exception Thrown: %s", pDBException->m_strError);
		m_astrErrors.Add(strMessage);
		strMessage.Format("  Exception Details: Installer: %s, P.O. Number %s, Name: %s", m_set.m_Installer, m_set.m_PONumber, m_set.m_Name);
		m_astrErrors.Add(strMessage);
		pDBException->Delete();
	}

	return (m_astrErrors.GetCount() == 0);  // valid if no errors
}

bool CQuickBooks::GetMarketDivisionFromPO( const CString& strPO, const CString& strInstaller, const CString& strClass, CString& strMarket, CString& strDivision )
{
	bool bPOFound = false;
	strMarket = "";
	strDivision = "";

	CSetPOMarketDivision setPOMarketDivision(&g_dbFlooring);

	setPOMarketDivision.m_strFilter.Format("[PurchaseOrderNumber] = '%s'", strPO);
	setPOMarketDivision.Open();

	// this should have already been caught in validation, but just in case....
	if (setPOMarketDivision.IsEOF())
	{
		return false;
	}

	// see how many records we returned
	while (!setPOMarketDivision.IsEOF())
	{
		setPOMarketDivision.MoveNext();
	}
	long lCount = setPOMarketDivision.GetRecordCount();
	setPOMarketDivision.MoveFirst();

	if ( strPO.GetLength() == 8 )
	{
		if (lCount > 1)
		{
			// have situation where an 8-digit PO has been issued by multiple stores, we can find
			// out the market 1 of 2 ways, either by searching on the customer name, or figuring out 
			// what market the installer has been assigned to.  The second option is better since we 
			// know the subcontractors have already been verified.  

			CSetSubContractor setSub(&g_dbFlooring);
			// get market based on installer's market assignment
			CString strLastName = strInstaller.Left(strInstaller.Find(',') );
			CString strFirstName = strInstaller.Mid(strInstaller.Find(',') + 2);

			// validate installer name
			setSub.m_strFilter.Format("[LastName] = '%s' AND [FirstName] = '%s'", strLastName, strFirstName) ;
			setSub.Open();

			ASSERT(setSub.IsEOF() == FALSE);

			CSetMarket setMarkets(&g_dbFlooring);
			setMarkets.m_strFilter.Format("[MarketId] = %d", setSub.m_MarketId);
			setMarkets.Open();

			strMarket = setMarkets.m_MarketName;

			// figure out which PO is the right one
			while (!setPOMarketDivision.IsEOF())
			{
				if (setPOMarketDivision.m_Market == strMarket)
				{
					strDivision = setPOMarketDivision.m_Division;
					break;
				}
				setPOMarketDivision.MoveNext();
			}

			if (strDivision.GetLength() == 0)
			{
				// if we didn't find a match, we will see if there is an override in the class column...
				if (strClass.GetLength() > 0)
				{
					if (strClass.CompareNoCase("S") == 0)
					{
						strDivision = "Soft Surface";
					}
					else if (strClass.CompareNoCase("H") == 0)
					{
						strDivision = "Hard Surface";
					}
					else if (strClass.CompareNoCase("K") == 0)
					{
						strDivision = "Cabinets";
					}
				}
				else
				{
					// go ahead and init to first division in list
					strDivision = setPOMarketDivision.m_Division;
					CString strMessage;
					CString strTemp;
					strMessage.Format("WARNING: There are multiple POs for the PO Number %s.  The correct Division cannot be determined based on the information in the spreadsheet.  Please modify the Division Class Name in Quickbooks if needed.", strPO);
					strTemp.Format("\r\nInstaller: %s", strInstaller);
					strMessage += strTemp;
					m_astrWarnings.Add(strMessage);
				}
			}
			
			setMarkets.Close();
			setSub.Close();

			bPOFound = true;
		}
		else
		{
			strMarket = setPOMarketDivision.m_Market;
			strDivision = setPOMarketDivision.m_Division;
			bPOFound = true;
		}
	}
    else if ( strPO.GetLength() == 4 )
	{
		// must be a 'store number' or possibly commercial/overhead
		// show the dialog box and allow the user to pick the details for this transaction
		CSetStores setStores(&g_dbFlooring);
		setStores.m_strFilter.Format("[StoreNumber] = '%s'", strPO);
		setStores.Open();

		CSetMarket setMarkets(&g_dbFlooring);
		setMarkets.m_strFilter.Format("[MarketId] = %d", setStores.m_MarketId);
		setMarkets.Open();

		strMarket = setMarkets.m_MarketName;

		if (strClass.CompareNoCase("S") == 0)
		{
			strDivision = "Soft Surface";
		}
		else if (strClass.CompareNoCase("H") == 0)
		{
			strDivision = "Hard Surface";
		}
		else if (strClass.CompareNoCase("K") == 0)
		{
			strDivision = "Cabinets";
		}

		ASSERT(strDivision.GetLength() > 0);

		bPOFound = true;

	}

	return bPOFound;
}