/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ReportPayroll.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "ReportPayroll.h"
#include "SetSubContractor.h"
#include "QuickBooks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportPayroll

IMPLEMENT_DYNCREATE(CReportPayroll, CCFScrollView)

CReportPayroll::CReportPayroll()
{
}

CReportPayroll::~CReportPayroll()
{
	m_set.Close() ;
}


BEGIN_MESSAGE_MAP(CReportPayroll, CCFScrollView)
	//{{AFX_MSG_MAP(CReportPayroll)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportPayroll drawing

void CReportPayroll::OnInitialUpdate()
{
	CCFScrollView::OnInitialUpdate();

	m_set.m_strSort = "[Installer], [Date]" ;
	m_set.Open() ;

	BuildQuickbooksFile() ;
}

void CReportPayroll::OnDraw(CDC* pDC)
{
	CFont* pOldFont = pDC->SelectObject( &m_PrintFont );
	m_set.Requery() ;

	int iX = 0 ;
	int iY = 0 ;
	CString strInstaller = "" ;
	try
	{

		while (!m_set.IsEOF())
		{
			CString	strOut ;
			if (strInstaller != m_set.m_Installer)
			{
				if (strInstaller  != "")
				{
					// show retainage and total ;
					pDC->MoveTo(iX, iY) ;
					pDC->LineTo(iX + 200, iY) ;
					iY += 5 ;
				}
				strInstaller = m_set.m_Installer ;
				strOut = strInstaller ;

				pDC->TextOut(iX, iY, strOut) ;
				CSize szText(pDC->GetTextExtent(strOut)) ;
				iY += szText.cy ;
			}
			strOut.Format("%s  - %-60s - $%7.2f",  
				m_set.m_Date.Format("%Y-%m-%d"), 
				m_set.m_Name,
				atof(m_set.m_Pay_Amount)) ;
			pDC->TextOut(iX, iY, strOut) ;
			CSize szText(pDC->GetTextExtent(strOut)) ;
			iY += szText.cy ;
			try
			{
				m_set.MoveNext() ;
			}
			catch (CException *pE)
			{
				pE->Delete() ;
			}
		}
	}
	catch (CException* pE)
	{
		pE->Delete() ;
	}
	pDC->SelectObject( pOldFont );
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	CRect rect ;
	
	this->GetClientRect(&rect) ;
	sizeTotal.cx = long(rect.Width() * .95) ;
	sizeTotal.cy = iY ;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CReportPayroll diagnostics

#ifdef _DEBUG
void CReportPayroll::AssertValid() const
{
	CCFScrollView::AssertValid();
}

void CReportPayroll::Dump(CDumpContext& dc) const
{
	CCFScrollView::Dump(dc);
}
#endif //_DEBUG


void CReportPayroll::GotoPage(int iPage)
{
	m_set.Requery() ;
	int iNumberOfInstallers = 0 ;
	CString	strInstaller = "" ;

	while (!m_set.IsEOF())
	{
		if (strInstaller != m_set.m_Installer)
		{
			iNumberOfInstallers ++ ;
			if (iNumberOfInstallers == iPage)
			{
				break ;
			}
			strInstaller = m_set.m_Installer ;
		}
		m_set.MoveNext() ;
	}
}

void CReportPayroll::PrintPageBody(CDC *pDC, CPrintInfo *pInfo)
{
	CFont* pOldFont = pDC->SelectObject( &m_PrintFont );

	GotoPage(pInfo->m_nCurPage) ;

	int iY = pInfo->m_rectDraw.top ;
	int iX = m_lLeftMargin ;
	CString strInstaller = m_set.m_Installer ;
	CString	strOut ;
	if (!m_set.IsEOF())
	{

		CString strLastName = strInstaller.Left(strInstaller.Find(',') );
		CString strFirstName = strInstaller.Mid(strInstaller.Find(',') + 2);
		CSetSubContractor setSub(&g_dbFlooring) ;
		setSub.m_strFilter.Format("[LastName] = '%s' AND [FirstName] = '%s'", strLastName, strFirstName) ;
		setSub.Open() ;
		if (setSub.IsEOF())
		{
			CString strMessage ;
			strMessage.Format("%s is not in the installer database. Please update and try agan.", m_set.m_Installer) ;
			MessageBox(strMessage, "Installer Name Error") ;
		}

		strOut.Format("%s - W/E %s", strInstaller, GetWeekEnding()) ;

		// Print banner here
		DrawAlignedText(pDC, m_lLeftMargin, &iY, m_lRightMargin - m_lLeftMargin, strOut) ;
		pDC->MoveTo(m_lLeftMargin, iY) ;
		pDC->LineTo(m_lRightMargin, iY) ;
		iY += 100 ;

		double dPayAmount = 0 ;
		double dSubjectToRetainage = 0 ;

		while (!m_set.IsEOF())
		{
			if (strInstaller == m_set.m_Installer)
			{
				iX = m_lLeftMargin ;

				DrawAlignedText(pDC, &iX, iY, m_lDateColumWidth, m_set.m_Date.Format("%Y-%m-%d")) ;
				DrawAlignedText(pDC, &iX, iY, m_lNameColumWidth, m_set.m_Name) ;
				strOut.Format("$%.2f", atof(m_set.m_Pay_Amount)) ;
				DrawAlignedText(pDC, &iX, iY, m_lAmountColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;
				DrawAlignedText(pDC, iX, &iY, m_lCommentColumWidth, m_set.m_Comments, DT_LEFT | DT_WORDBREAK) ;

				if ((atof(m_set.m_Pay_Amount) >= 0) && (!m_set.m_NO_RETAINAGE))
				{
					dSubjectToRetainage += atof(m_set.m_Pay_Amount) ;
				}
				dPayAmount += atof(m_set.m_Pay_Amount) ;
			}
			else
			{
				break ;
			}
			m_set.MoveNext() ;
		}
		// show retainage and total ;
		pDC->MoveTo(m_lLeftMargin, iY) ;
		pDC->LineTo(m_lRightMargin, iY) ;
		iY += 10 ;

		double fRetainageRate = atof(setSub.m_RetainageRate) ;
		double fSavingsRate = setSub.m_SavingsRate ;
		if ((fRetainageRate > 0.0) || (fSavingsRate > 0.0))
		{
			strOut.Format("$%.2f", dPayAmount) ;  

			iX = m_lLeftMargin + m_lDateColumWidth ;
			DrawAlignedText(pDC, &iX, iY, m_lNameColumWidth, "SubTotal", DT_RIGHT | DT_SINGLELINE) ;
			DrawAlignedText(pDC, iX, &iY, m_lAmountColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;

			if (fRetainageRate > 0.0)
			{
				CString strRetainage ;
				double fRetainage = dSubjectToRetainage * fRetainageRate ;
				long lRet = long ((fRetainage * 100) + .5) ;
				fRetainage = lRet / 100. ;

				iX = m_lLeftMargin + m_lDateColumWidth ;
				strOut.Format("Retainage %.0f%%", fRetainageRate * 100.) ;
				DrawAlignedText(pDC, &iX, iY, m_lNameColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;
				strOut.Format("$%.2f", fRetainage) ;  
				DrawAlignedText(pDC, iX, &iY, m_lAmountColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;
				// print totals here
				dPayAmount -= fRetainage ;
			}

			if (fSavingsRate > 0.0)
			{
				CString strRetainage ;
				double fSavings = dSubjectToRetainage * fSavingsRate ;
				long lSave = long((fSavings * 100) + .5) ;
				fSavings = lSave / 100 ;

				iX = m_lLeftMargin + m_lDateColumWidth ;
				strOut.Format("Savings %.0f%%", fSavingsRate * 100.) ;
				DrawAlignedText(pDC, &iX, iY, m_lNameColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;
				strOut.Format("$%.2f", fSavings) ;  
				DrawAlignedText(pDC, iX, &iY, m_lAmountColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;
				// print totals here
				dPayAmount -= fSavings ;
			}
	

			// show retainage and total ;
			pDC->MoveTo(m_lLeftMargin, iY) ;
			pDC->LineTo(m_lRightMargin, iY) ;
			iY += 10 ;
		}
		strOut.Format("$%.2f", dPayAmount) ;  
		iX = m_lLeftMargin + m_lDateColumWidth ;
		DrawAlignedText(pDC, &iX, iY, m_lNameColumWidth, "Total", DT_RIGHT | DT_SINGLELINE) ;
		DrawAlignedText(pDC, iX, &iY, m_lAmountColumWidth, strOut, DT_RIGHT | DT_SINGLELINE) ;


		iY += 200 ;
		iX = m_lLeftMargin ;
		setSub.m_WorkmansComp ;

		CTime t = CTime::GetCurrentTime();

		if ((setSub.m_WorkmansComp) && (setSub.m_InsuranceDate < t))
		{
			setSub.Edit() ;
			setSub.m_WorkmansComp = false ;
			setSub.Update() ;
			setSub.Requery() ;
		}

		if (setSub.m_WorkmansComp)
		{
			strOut.Format("Worker Compensation Insurance expires %s", setSub.m_InsuranceDate.Format("%B %d, %Y")) ;
		}
		else
		{
			if (!setSub.IsFieldNull(&setSub.m_InsuranceDate))
			{
				strOut.Format("Worker Compensation Insurance EXPIRED %s", setSub.m_InsuranceDate.Format("%B %d, %Y")) ;
			}
			else
			{
				strOut.Format("Worker Compensation Insurance NEVER RECEIVED") ;
			}
		}

		DrawAlignedText(pDC, iX, &iY, this->m_lRightMargin - this->m_lLeftMargin, strOut, DT_LEFT | DT_SINGLELINE) ;
/*
		iY += 50 ;
		strOut = "NOTE: Pay is subject to a 15% charge if Workers Compensation Insurance is not current and installer will receive no additional work until Workers Compensation Insurance is current." ;
		DrawAlignedText(pDC, iX, &iY, this->m_lRightMargin - this->m_lLeftMargin, strOut, DT_LEFT | DT_WORDBREAK) ;

		setSub.Close() ;

		iY += 100 ;

		strOut = "EFFECTIVE 3/5/2001\n$25 Fine for not turning in the waiver and workorder the NEXT BUSINESS DAY after Installation.\nAny Bills not turned in by Tuesday NOON will not be paid until the following week." ;
		DrawAlignedText(pDC, iX, &iY, this->m_lRightMargin - this->m_lLeftMargin, strOut, DT_LEFT | DT_WORDBREAK) ;

		iY += 100 ;

		strOut = "EFFECTIVE 10/1/2001\nLabor prices for plush will be $3.00.\nLabor prices for berber will be $3.25." ;
		DrawAlignedText(pDC, iX, &iY, this->m_lRightMargin - this->m_lLeftMargin, strOut, DT_LEFT | DT_WORDBREAK) ;
*/

	}
	else
	{
		// we must be on the grand total page ;
		strOut.Format("Grand Total for %s - $%.2f", GetWeekEnding(), this->m_fGrandTotal) ;

		// Print banner here
		DrawAlignedText(pDC, m_lLeftMargin, &iY, m_lRightMargin - m_lLeftMargin, strOut) ;
		pDC->MoveTo(m_lLeftMargin, iY) ;
		pDC->LineTo(m_lRightMargin, iY) ;

	}
	pDC->SelectObject( pOldFont );

}

void CReportPayroll::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_set.Requery() ;
	int iNumberOfInstallers = 0 ;
	CString	strInstaller = "" ;

	while (!m_set.IsEOF())
	{
		if (strInstaller != m_set.m_Installer)
		{
			iNumberOfInstallers ++ ;
			strInstaller = m_set.m_Installer ;
		}
		m_set.MoveNext() ;
	}
	pInfo->SetMaxPage(iNumberOfInstallers + 1) ;
	

	CCFScrollView::OnBeginPrinting(pDC, pInfo);
}

void CReportPayroll::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_lLeftMargin = long(pInfo->m_rectDraw.left + (pInfo->m_rectDraw.Width() * .05)) ;
	m_lRightMargin = long(pInfo->m_rectDraw.right - (pInfo->m_rectDraw.Width() * .05)) ;

	m_lDateColumWidth = long(pInfo->m_rectDraw.Width() * .15);
	m_lNameColumWidth = long(pInfo->m_rectDraw.Width() * .3);
	m_lAmountColumWidth = long(pInfo->m_rectDraw.Width() * .15);
	m_lCommentColumWidth = long(pInfo->m_rectDraw.Width() * .3);

	pInfo->m_rectDraw.top += long(pInfo->m_rectDraw.Height() * .05) ;
	pInfo->m_rectDraw.bottom -= long(pInfo->m_rectDraw.Height() * .05 );

	PrintPageBody(pDC, pInfo);

	pDC->MoveTo(m_lLeftMargin, pInfo->m_rectDraw.bottom) ;
	pDC->LineTo(m_lRightMargin, pInfo->m_rectDraw.bottom) ;
}

void CReportPayroll::BuildQuickbooksFile()
{
	try
	{
		CString strFilename = GetQBString(szSETTINGS_VALUE_QBFILENAME, szSETTINGS_VALUE_QBFILENAME_DEFAULT);
		strFilename = "S:/" + strFilename;
		
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
		setSub.Open() ;

		double fRetainage = 0.0;
		double fSavings = 0.0;

		while(!m_set.IsEOF())
		{
			if (strInstaller != m_set.m_Installer)
			{
				// about to switch installers
				if (strInstaller != "")
				{
					// this is not the first installer so output last installers retainage ;
					strOutput += (OutputRetainage(strInstaller, fRetainage, dSubjectToRetainage, dPayAmount)) ;
					strOutput += (OutputSavings(strInstaller, bInstallersOk, fSavings, dSubjectToRetainage, dPayAmount)) ;
					fileOut.WriteString(OutputHeader(strInstaller, dPayAmount)) ;
					fileOut.WriteString(strOutput) ;
					fileOut.WriteString("ENDTRNS\n") ;
				}
				CString strLastName = m_set.m_Installer.Left(m_set.m_Installer.Find(',') );
				CString strFirstName = m_set.m_Installer.Mid(m_set.m_Installer.Find(',') + 2);
				setSub.m_strFilter.Format("[LastName] = '%s' AND [FirstName] = '%s'", strLastName, strFirstName) ;
				setSub.Requery() ;
				if (setSub.IsEOF())
				{
					CString strMessage ;
					strMessage.Format("%s is not in the installer database. Please update and try agan.", m_set.m_Installer) ;
					MessageBox(strMessage, "Installer Name Error") ;
					bInstallersOk = false ;
					break ;
				}
				fRetainage = atof(setSub.m_RetainageRate) ;
				fSavings  = setSub.m_SavingsRate ;

				// start a new installer
				dSubjectToRetainage = 0 ;
				dPayAmount = 0 ;
				strOutput = "" ;
				strInstaller = m_set.m_Installer ;

			}

			CString strAccount = GetQBString(szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT, szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT_DEFAULT);
			
			CString strTransaction ;
			if (atof(m_set.m_Pay_Amount) >= 0)
			{
				if (!m_set.m_NO_RETAINAGE)
				{
					dSubjectToRetainage += atof(m_set.m_Pay_Amount) ;
				}
			}
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
				strAccount = GetQBString(szSETTINGS_VALUE_RETAINAGEACCOUNT, szSETTINGS_VALUE_RETAINAGEACCOUNT_DEFAULT);
				strAccount = strAccount + ":" + m_set.m_Chargeback ;

				
				CString strAccount2 = GetQBString(szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT, szSETTINGS_VALUE_LABORSUBCONTRACTACCOUNT_DEFAULT);

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

		// Retainage for last guy
		strOutput += (OutputRetainage(strInstaller, fRetainage, dSubjectToRetainage, dPayAmount)) ;
		strOutput += (OutputSavings(strInstaller, bInstallersOk, fSavings, dSubjectToRetainage, dPayAmount)) ;
		fileOut.WriteString(OutputHeader(strInstaller, dPayAmount)) ;
		fileOut.WriteString(strOutput) ;
		fileOut.WriteString("ENDTRNS\n") ;

		fileOut.Close() ;
	}
	catch (CException* pE)
	{
		pE->Delete() ;
		
	}
}

CString CReportPayroll::GetWeekEnding()
{
	CTime timeWE = CTime::GetCurrentTime() ;

	timeWE -= CTimeSpan(timeWE.GetDayOfWeek(), 0, 0, 0) ;
	return timeWE.Format("%m/%d/%Y") ;
}

CString CReportPayroll::OutputRetainage(CString strInstaller, double fRetainage, double dSubjectToRetainage, double& dPayAmount)
{
	CString strOutput = "" ;

	if ((dSubjectToRetainage > 0) && (fRetainage > 0.0))
	{
		double dRet = -1.0 * dSubjectToRetainage * fRetainage;
		long lRet = long((dRet * 100) - .5) ;
		dRet = lRet / 100. ;
		CString strAccount = GetQBString(szSETTINGS_VALUE_RETAINAGEACCOUNT, szSETTINGS_VALUE_RETAINAGEACCOUNT_DEFAULT);
		CString strClass = GetQBString(szSETTINGS_VALUE_RETAINAGECLASS, szSETTINGS_VALUE_RETAINAGECLASS_DEFAULT);

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

CString CReportPayroll::OutputSavings(CString strInstaller, bool bInstallersOk, double fSavings, double dSubjectToRetainage, double& dPayAmount) 
{
	CString strOutput = "" ;

	if ((dSubjectToRetainage > 0) && (bInstallersOk) && (fSavings > 0.0))
	{
		double dSave = dSubjectToRetainage * -1 * fSavings;
		long lSave = long ((dSave * 100) - .5) ;
		dSave = lSave / 100. ;
		CString strAccount = GetQBString(szSETTINGS_VALUE_SAVINGSACCOUNT, szSETTINGS_VALUE_SAVINGSACCOUNT_DEFAULT);
		CString strClass = GetQBString(szSETTINGS_VALUE_SAVINGSCLASS, szSETTINGS_VALUE_SAVINGSCLASS_DEFAULT);

		// Retainage
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

CString CReportPayroll::OutputHeader(CString strInstaller, double dPayAmount)
{
	CString strOutput ;
	CString strAccount = GetQBString(szSETTINGS_VALUE_ACCOUNTSPAYABLEACCOUNT, szSETTINGS_VALUE_ACCOUNTSPAYABLEACCOUNT_DEFAULT);
	strOutput.Format("TRNS\tBILL\t%s\t%s\t%s\t%s\t%7.2f\n",
		strAccount,
		strInstaller, 
		GetWeekEnding(),
		"",
		dPayAmount * -1.0) ;
	return strOutput ;
}

CString CReportPayroll::ClassTrans(CString strClass)
{
	CString strOutput ;

	if (strClass.CompareNoCase("C") == 0)
	{
		strOutput = GetQBString(szSETTINGS_VALUE_COMMERCIALCLASS, szSETTINGS_VALUE_COMMERCIALCLASS_DEFAULT) ;
	}
	if (strClass.CompareNoCase("S") == 0)
	{
		strOutput = GetQBString(szSETTINGS_VALUE_SOFTSURFACECLASS, szSETTINGS_VALUE_SOFTSURFACECLASS_DEFAULT);
	}
	if (strClass.CompareNoCase("H") == 0)
	{
		strOutput = GetQBString(szSETTINGS_VALUE_HARDSURFACECLASS, szSETTINGS_VALUE_HARDSURFACECLASS_DEFAULT);
	}
	if (strClass.CompareNoCase("O") == 0)
	{
		strOutput = GetQBString(szSETTINGS_VALUE_OVERHEADCLASS, szSETTINGS_VALUE_OVERHEADCLASS_DEFAULT);
	}

	return strOutput ;
}


// retrieves the value of the specified key, or a default value
CString CReportPayroll::GetQBString(CString strKey, CString strDefault)
{
	CString strValue = "";
	
	CString strREGISTRY_PATH = "SOFTWARE\\Custom Flooring, Inc.\\Flooring\\";
	strREGISTRY_PATH += szREGISTRY_KEY_QBSTRINGS;

	ClRegistrySection clRegistry(HKEY_LOCAL_MACHINE, strREGISTRY_PATH, KEY_READ, FALSE);

	if (clRegistry.m_bError)
		return strDefault;

	strValue = clRegistry.ReadRegistryString(strKey, strDefault );
	return strValue;
}
