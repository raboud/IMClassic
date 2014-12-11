/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ReportCheck.cpp : implementation file
//

#include "stdafx.h"
#include  <math.h>

#include "flooring.h"
//#include "ReportCheck.h"

//#include "SetTotalPayment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportCheck

IMPLEMENT_DYNCREATE(CReportCheck, CCFScrollView)

CReportCheck::CReportCheck()
:	m_setPayment(&g_dbFlooring), m_setChargeBacks(&g_dbFlooring)

{
	psuPage = NULL ;

	m_setPayment.m_strFilter = "OrderID = -1";
	m_setPayment.Open() ;


	m_setChargeBacks.Open() ;
}

CReportCheck::~CReportCheck()
{
	if (psuPage)
	{
		delete [] psuPage ;
	}
	m_setPayment.Close() ;
	m_setChargeBacks.Close() ;
}


BEGIN_MESSAGE_MAP(CReportCheck, CCFScrollView)
	//{{AFX_MSG_MAP(CReportCheck)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCheck drawing

void CReportCheck::OnInitialUpdate()
{
	CCFScrollView::OnInitialUpdate();
}

void CReportCheck::OnDraw(CDC* pDC)
{
//	CString strOutput = "s:/" + m_strCheckNumber + ".out" ;
//	CStdioFile fileOut(strOutput, CFile::modeCreate | CFile::modeWrite | CFile::typeText) ;
//	CSetOrderAndCustomer setCombined ;

	m_setPayment.m_strFilter.Format("[CheckNumber] = '%s'", this->m_strCheckNumber) ;
	m_setPayment.m_strSort = "[LastName], [FirstName], [PurchaseOrderNumber]" ;
	m_setPayment.Requery() ;

	CString strOut ;
//	strOut.Format("CK#: %s - BY NAME\n\n", m_strCheckNumber) ;
//	fileOut.WriteString(strOut) ;

	int iYPos = 0 ;

	while (!m_setPayment.IsEOF())
	{
		strOut.Format("%s - %s, %s", m_setPayment.m_PurchaseOrderNumber, m_setPayment.m_LastName, m_setPayment.m_FirstName) ;
		DrawAlignedText(pDC, 0, &iYPos, 300, strOut) ;

		m_setPayment.MoveNext() ;
	}

	strOut.Format("\fCK#: %s - BY PO NUMBER\n\n", m_strCheckNumber) ;
//	fileOut.WriteString(strOut) ;

	m_setPayment.m_strSort = "[PurchaseOrderNumber]" ;
	m_setPayment.Requery() ;
	while (!m_setPayment.IsEOF())
	{
		strOut.Format("%s - %s - %s, %s", m_setPayment.m_BilledDate.Format("%Y/%m/%d"), m_setPayment.m_PurchaseOrderNumber, m_setPayment.m_LastName, m_setPayment.m_FirstName) ;
		DrawAlignedText(pDC, 0, &iYPos, 300, strOut) ;

		m_setPayment.MoveNext() ;
	}

	m_setChargeBacks.Requery() ;
	strOut.Format("\fCK#: %s - CHARGEBACKS REPORT\n\n", m_strCheckNumber) ;
//	fileOut.WriteString(strOut) ;

	while (!m_setChargeBacks.IsEOF())
	{
		strOut.Format("Chargeback   %s - Orig. PO. %s - %s", m_setChargeBacks.m_Number, m_setChargeBacks.m_OriginalPO, m_setChargeBacks.m_Name) ;
		DrawAlignedText(pDC, 0, &iYPos, 300, strOut) ;

		m_setChargeBacks.MoveNext() ;
	}

	strOut.Format("\fCK#: %s - DISCREPENCY REPORT", m_strCheckNumber) ;

	CSize size(400, iYPos) ;
	SetScrollSizes(MM_TEXT, size);
//	fileOut.WriteString(strOut) ;

/*
	m_setPayment.Requery() ;
	while (!m_setPayment.IsEOF())
	{
		double fInvoice ;
		double fPaid ;

		if (!m_setPayment.m_Billed)
		{
			strOut.Format("NOT BILLED YET   %s - %s, %s", setCombined.m_PurchaseOrderNumber, setCombined.m_LastName, setCombined.m_FirstName) ;
			fileOut.WriteString(strOut) ;
		}
		else
		{
			fInvoice = atof(setCombined.m_BilledAmount) ;
			fPaid = atof(setCombined.m_PaidAmount) ;

			if (fabs(fInvoice - fPaid) > 5.0)
			{
				strOut.Format("INCORRECT AMOUNT %s  PAID $%7.2f - INVOICE $%7.2f - %s, %s\n", setCombined.m_PurchaseOrderNumber, fPaid, fInvoice, setCombined.m_LastName, setCombined.m_FirstName) ;
				fileOut.WriteString(strOut) ;
			}
		}

		m_setPayment.MoveNext() ;
	}
*/
//	fileOut.Close() ;

}

/////////////////////////////////////////////////////////////////////////////
// CReportCheck diagnostics

#ifdef _DEBUG
void CReportCheck::AssertValid() const
{
	CCFScrollView::AssertValid();
}

void CReportCheck::Dump(CDumpContext& dc) const
{
	CCFScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCheck message handlers

void CReportCheck::SetCheckNumber(CString strCheckNumber)
{
	m_strCheckNumber = strCheckNumber ;
	m_setChargeBacks.m_strFilter.Format("[CheckNumber] = '%s'", m_strCheckNumber) ;
	m_setChargeBacks.m_strSort = "[Name]" ;
	m_setChargeBacks.Requery() ;
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	DeterminePageBreaks() ;
}

void CReportCheck::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	GotoPage(pInfo->m_nCurPage) ;
	CCFScrollView::OnPrint(pDC, pInfo);
}

void CReportCheck::DeterminePageBreaks()
{
	CDC	dc ;

	CreateDefaultPrinterDC(&dc) ;
	CFont font;
	VERIFY(font.CreatePointFont(120, "Arial", &dc));

	// Do something with the font just created...
	dc.SelectObject(&font);
	CSize size = dc.GetOutputTextExtent("Test q__") ;

	int iLogPixelsY = dc.GetDeviceCaps(LOGPIXELSY) ;

	int iPixelPageBodyY = int(iLogPixelsY * (11 - 1.5))  ;

	int iLinesPerPage = iPixelPageBodyY / size.cy ;

	m_setPayment.m_strFilter.Format("[CheckNumber] = '%s'", this->m_strCheckNumber) ;
	m_setPayment.Requery() ;

	int iNumberOfPayments = 0 ;
	int iNumberOfDiscrepancies = 0 ;
	int iNumberOfChargeBacks = 0 ;

	while (!m_setPayment.IsEOF())
	{
		iNumberOfPayments ++ ;
		if ((fabs(atof(m_setPayment.m_Balance)) > 5.0) || (m_setPayment.m_Billed != TRUE))
		{
			iNumberOfDiscrepancies++ ;
		}

		m_setPayment.MoveNext() ;
	}

	m_setChargeBacks.Requery() ;
	while (!m_setChargeBacks.IsEOF())
	{
		iNumberOfChargeBacks ++ ;
		m_setChargeBacks.MoveNext() ;
	}


	int iPaymentPages = (iNumberOfPayments + iLinesPerPage - 1) / iLinesPerPage ;
	if (!iPaymentPages)
	{
		iPaymentPages = 1 ;
	}

	int iDiscrepPages = (iNumberOfDiscrepancies + iLinesPerPage - 1) / iLinesPerPage ;
	if (!iDiscrepPages)
	{
		iDiscrepPages = 1 ;
	}

	int iChargePages = (iNumberOfChargeBacks + iLinesPerPage - 1) / iLinesPerPage ;
	if (!iChargePages)
	{
		iChargePages += 1 ;
	}

	m_iNumberOfPages = (iPaymentPages * 2) + iDiscrepPages + iChargePages ;

	psuPage = new SuPage [m_iNumberOfPages] ;
	for (int iIndex = 0; iIndex < m_iNumberOfPages; iIndex++)
	{
		if (iIndex < iPaymentPages)
		{
			psuPage[iIndex].enType = EnPageType_ALPHA ;
			psuPage[iIndex].iRecordNumber = (iIndex * iLinesPerPage) + 1;
		}
		else if (iIndex < (iPaymentPages * 2))
		{
			psuPage[iIndex].enType = EnPageType_NUMERIC ;
			psuPage[iIndex].iRecordNumber = ((iIndex - iPaymentPages) * iLinesPerPage) + 1 ;
		}
		else if (iIndex < (iPaymentPages * 2) + iDiscrepPages)
		{
			psuPage[iIndex].enType = EnPageType_DISCREPANCY ;
			psuPage[iIndex].iRecordNumber = ((iIndex - (iPaymentPages * 2)) * iLinesPerPage) + 1;
		}
		else
		{
			psuPage[iIndex].enType = EnPageType_CHARGEBACK ;
			psuPage[iIndex].iRecordNumber = ((iIndex - (iPaymentPages * 2) - iDiscrepPages) * iLinesPerPage) + 1 ; 
		}
	}
}

void CReportCheck::PrintPageBody(CDC *pDC, CPrintInfo *pInfo)
{
	CFont font;
	VERIFY(font.CreatePointFont(120, "Arial", pDC));

	// Do something with the font just created...
	CFont* def_font = pDC->SelectObject(&font);

	switch (psuPage[pInfo->m_nCurPage - 1].enType)
	{
		case EnPageType_ALPHA:
			PrintAlphaPage(pDC, pInfo) ;
			break ;

		case EnPageType_NUMERIC : 
			PrintNumericPage(pDC, pInfo) ;
			break ;

		case EnPageType_CHARGEBACK: 
			PrintChargePage(pDC, pInfo) ;
			break ;

		case EnPageType_DISCREPANCY :
			PrintDiscrepPage(pDC, pInfo) ;
			break ;
	}


	pDC->SelectObject(def_font);

}

BOOL CReportCheck::OnPreparePrinting(CPrintInfo* pInfo) 
{
	pInfo->SetMaxPage(m_iNumberOfPages) ;
	return CCFScrollView::OnPreparePrinting(pInfo);
}

void CReportCheck::PrintAlphaPage(CDC *pDC, CPrintInfo *pInfo)
{
	int iYPos = pInfo->m_rectDraw.top ;
	CString strOut ;
	int iHeight = 0 ;

	while (!m_setPayment.IsEOF() && (iYPos < (pInfo->m_rectDraw.bottom - iHeight)))
	{
		strOut.Format("%s - %s, %s", m_setPayment.m_PurchaseOrderNumber, m_setPayment.m_LastName, m_setPayment.m_FirstName) ;

		DrawAlignedText(pDC, pInfo->m_rectDraw.left, iYPos, pInfo->m_rectDraw.Width(), strOut) ;
		iHeight = DrawAlignedText(pDC, pInfo->m_rectDraw.left + int (pInfo->m_rectDraw.Width() * .5), &iYPos, int(pInfo->m_rectDraw.Width() * .2), m_setPayment.m_Amount, DT_RIGHT | DT_SINGLELINE) ;

		m_setPayment.MoveNext() ;
	}
}

void CReportCheck::PrintNumericPage(CDC *pDC, CPrintInfo *pInfo)
{
	int iYPos = pInfo->m_rectDraw.top ;
	CString strOut ;
	int iHeight = 0 ;

	while (!m_setPayment.IsEOF() && (iYPos < (pInfo->m_rectDraw.bottom - iHeight)))
	{
		strOut.Format("%s - %s - %s, %s", m_setPayment.m_BilledDate.Format("%Y/%m/%d"), m_setPayment.m_PurchaseOrderNumber, m_setPayment.m_LastName, m_setPayment.m_FirstName) ;
		iHeight = DrawAlignedText(pDC, pInfo->m_rectDraw.left, &iYPos, pInfo->m_rectDraw.Width(), strOut) ;

		m_setPayment.MoveNext() ;
	}
}

void CReportCheck::PrintChargePage(CDC *pDC, CPrintInfo *pInfo)
{
	int iYPos = pInfo->m_rectDraw.top ;

	CString strOut ;
	int iHeight = 0 ;

	while (!m_setChargeBacks.IsEOF() && (iYPos < (pInfo->m_rectDraw.bottom - iHeight)))
	{
		strOut.Format("Chargeback   %s - Orig. PO. %s - %s", m_setChargeBacks.m_Number, m_setChargeBacks.m_OriginalPO, m_setChargeBacks.m_Name) ;
		iHeight = DrawAlignedText(pDC, pInfo->m_rectDraw.left, &iYPos, pInfo->m_rectDraw.Width(), strOut) ;

		m_setChargeBacks.MoveNext() ;
	}
}

void CReportCheck::PrintDiscrepPage(CDC *pDC, CPrintInfo *pInfo)
{
	int iYPos = pInfo->m_rectDraw.top ;
	CString strOut ;
	int iHeight = 0 ;

	while (!m_setPayment.IsEOF() && (iYPos < (pInfo->m_rectDraw.bottom - iHeight)))
	{
		double fInvoice ;
		double fPaid ;

		if (!m_setPayment.m_Billed)
		{
			strOut.Format("NOT BILLED YET   %s - %s, %s", m_setPayment.m_PurchaseOrderNumber, m_setPayment.m_LastName, m_setPayment.m_FirstName) ;
			iHeight = DrawAlignedText(pDC, pInfo->m_rectDraw.left, &iYPos, pInfo->m_rectDraw.Width(), strOut) ;
		}
		else
		{
			fInvoice = atof(m_setPayment.m_BilledAmount) ;
			fPaid = atof(m_setPayment.m_TotalAmount) ;

			if (fabs(atof(m_setPayment.m_Balance)) > 5.0)
			{
				strOut.Format("INCORRECT AMOUNT %s  PAID $%7.2f - INVOICE $%7.2f - %s, %s", m_setPayment.m_PurchaseOrderNumber, fPaid, fInvoice, m_setPayment.m_LastName, m_setPayment.m_FirstName) ;
				iHeight = DrawAlignedText(pDC, pInfo->m_rectDraw.left, &iYPos, pInfo->m_rectDraw.Width(), strOut) ;
			}
		}

		m_setPayment.MoveNext() ;
	}
}

void CReportCheck::GotoPage(int iPageNumber)
{
	CRecordset* pSet = NULL ;

	switch (psuPage[iPageNumber - 1].enType)
	{
		case EnPageType_ALPHA:
			m_strTitle.Format("Check Number: %s - ALPHABETICAL", m_strCheckNumber) ;
			pSet = &this->m_setPayment ;
			m_setPayment.m_strSort = "[LastName], [FirstName], [PurchaseOrderNumber]" ;
			m_setPayment.m_strFilter.Format("[CheckNumber] = '%s'", this->m_strCheckNumber) ;
			break ;

		case EnPageType_NUMERIC : 
			m_strTitle.Format("Check Number: %s - NUMERIC", m_strCheckNumber) ;
			pSet = &this->m_setPayment ;
			m_setPayment.m_strSort = "[PurchaseOrderNumber]" ;
			m_setPayment.m_strFilter.Format("[CheckNumber] = '%s'", this->m_strCheckNumber) ;
			break ;

		case EnPageType_CHARGEBACK: 
			m_strTitle.Format("Check Number: %s - CHARGE BACKS", m_strCheckNumber) ;
			pSet = &this->m_setChargeBacks ;
			break ;

		case EnPageType_DISCREPANCY :
			m_strTitle.Format("Check Number: %s - DISCREPANCIES", m_strCheckNumber) ;
			pSet = &this->m_setPayment ;
			m_setPayment.m_strSort = "[LastName], [FirstName], [PurchaseOrderNumber]" ;
			m_setPayment.m_strFilter.Format("[CheckNumber] = '%s' AND ([Balance] > 5.0 OR [Balance] < -5.0 OR [Billed] = 0)", this->m_strCheckNumber) ;
			break ;
	}

	if (pSet != NULL)
	{
		pSet->Requery() ;
		try
		{
			pSet->SetAbsolutePosition(psuPage[iPageNumber - 1].iRecordNumber) ;
		}
		catch (CException* pE)
		{
			pE->Delete() ;
		}
	}
}
