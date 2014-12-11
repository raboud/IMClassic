/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewWorkOrder.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "Flooring.h"
#include "ViewInvoice.h"
#include "SetOrders.h"
#include "SetCustomer.h"
#include "SetMaterialType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int iHEIGHT = 24 ;
const int iTOP_MARGIN = 25 ;
const int iLEFT_MARGIN = 25 ;
const int iRIGHT_MARGIN = 775 ;
const int iCENTER = (iLEFT_MARGIN + iRIGHT_MARGIN) / 2 ;
const int iCOLUMN = ((iLEFT_MARGIN + iRIGHT_MARGIN) * 2) / 3 ;
const int iCOLUMN2 = ((iLEFT_MARGIN + iRIGHT_MARGIN) * 1) / 8 ;
const int iTOP_OF_LOGO = iTOP_MARGIN ;
const int iBOTTOM_OF_LOGO = 175 ;

const int RETAIL = 0 ;
const int COST = 1 ;

/////////////////////////////////////////////////////////////////////////////
// CViewInvoice

IMPLEMENT_DYNCREATE(CViewInvoice, CCFViewReport)

CViewInvoice::CViewInvoice()
: m_setMaterialDetails(&g_dbFlooring)
, m_setOptionDetails(&g_dbFlooring)
, m_setCustomDetails(&g_dbFlooring)
, m_setUOM(&g_dbFlooring)
, m_setOptions(&g_dbFlooring)
, m_setOrders(&g_dbFlooring)
, m_setCompanyInfo(&g_dbFlooring)
{
	m_setMaterialDetails.m_strFilter = "OrderID = -1";
	m_setMaterialDetails.Open() ;
	
	m_setOptionDetails.m_strFilter = "OrdeOptionslID = -1";
	m_setOptionDetails.Open() ;

	m_setCustomDetails.m_strFilter = "OrderCustomID = -1";
	m_setCustomDetails.Open() ;

	m_setUOM.m_strFilter = "UnitOfMeasureID = -1";
	m_setUOM.Open() ;

	m_setOptions.m_strFilter = "OptionID = -1";
	m_setOptions.Open() ;

	m_setOrders.m_strFilter = "OrderID = -1";
	m_setOrders.Open() ;

	m_setCompanyInfo.m_strFilter = "ID = 1";
	m_setCompanyInfo.Open();
}

CViewInvoice::~CViewInvoice()
{
	m_setMaterialDetails.Close() ;
	m_setOptionDetails.Close() ;
	m_setCustomDetails.Close() ;

	m_setUOM.Close() ;

//	m_setMaterial.Close() ;
	m_setOptions.Close() ;

	m_setOrders.Close() ;
}


BEGIN_MESSAGE_MAP(CViewInvoice, CCFViewReport)
	//{{AFX_MSG_MAP(CViewInvoice)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewInvoice drawing

void CViewInvoice::OnDraw(CDC* pDC)
{
	CPen pen ;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0) ) ;
	pDC->SelectObject(&pen) ;
	CString strOut ;

	int iStartY = iTOP_OF_LOGO;
	pDC->SelectObject(&m_fontNormalBold) ;
	DrawLogo(pDC) ;

	pDC->SelectObject(&m_fontHuge) ;
	pDC->DrawText("INVOICE", CRect(iCENTER, iStartY, iRIGHT_MARGIN, iBOTTOM_OF_LOGO), DT_CENTER | DT_VCENTER | DT_SINGLELINE ) ;
	iStartY = iBOTTOM_OF_LOGO + 25 ;

	pDC->SelectObject(&m_fontNormalBold) ;
	pDC->DrawText("TO:", CRect(iLEFT_MARGIN, iStartY, iCOLUMN2, iStartY + iHEIGHT), DT_LEFT | DT_SINGLELINE) ;
	strOut = "STORE " + m_setOrders.m_StoreNumber ;
	pDC->DrawText(strOut, CRect(iCOLUMN2, iStartY, iCENTER - 100, iStartY + iHEIGHT), DT_CENTER | DT_SINGLELINE) ;
	pDC->MoveTo(iCOLUMN2, iStartY + iHEIGHT - 5) ;
	pDC->LineTo(iCENTER - 100, iStartY + iHEIGHT - 5) ;

	pDC->DrawText("DATE:", CRect(iCENTER, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_LEFT | DT_SINGLELINE) ;
	if (m_setOrders.m_Billed)
	{
		pDC->DrawText(m_setOrders.m_BilledDate.Format("%m/%d/%Y"), CRect(iCOLUMN, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_CENTER | DT_SINGLELINE) ;
	}
	pDC->MoveTo(iCOLUMN, iStartY + iHEIGHT - 5) ;
	pDC->LineTo(iRIGHT_MARGIN, iStartY + iHEIGHT - 5) ;
	iStartY += iHEIGHT ;

	m_setOrders.m_strFilter.Format("[OrderID] = '%d'", m_lPO ) ;
	m_setOrders.Requery() ;

	pDC->DrawText("PO Number:", CRect(iCENTER, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_LEFT | DT_SINGLELINE) ;
	pDC->DrawText(m_setOrders.m_PurchaseOrderNumber, CRect(iCOLUMN, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_CENTER | DT_SINGLELINE) ;
	pDC->MoveTo(iCOLUMN, iStartY + iHEIGHT - 5) ;
	pDC->LineTo(iRIGHT_MARGIN, iStartY + iHEIGHT - 5) ;
	iStartY += iHEIGHT ;

	DrawCustomerData(pDC, CRect(iCENTER, iStartY, iRIGHT_MARGIN, iStartY + 150), m_setOrders.m_CustomerID) ;
	pDC->SelectObject(&m_fontFixedBold) ;
	iStartY += 50 ;

	m_fTripCharg[RETAIL] = 0.0 ;
	m_fOptions[RETAIL] = 0.0 ;
	m_fBasic[RETAIL] = 0.0 ;
	m_fCustom[RETAIL] = 0.0 ;

	m_fTripCharg[COST] = 0.0 ;
	m_fOptions[COST] = 0.0 ;
	m_fBasic[COST] = 0.0 ;
	m_fCustom[COST] = 0.0 ;

	CRect rect(iLEFT_MARGIN, iStartY, iRIGHT_MARGIN, iStartY + 150) ;
	DrawTripCharge(pDC, rect) ;
	DrawBasic(pDC, rect);
	DrawOptions(pDC, rect);
	DrawCustom(pDC, rect);
	DrawTotal(pDC,rect) ;
	DrawComments(pDC, rect) ;
	rect.top += 10 ;
}

/////////////////////////////////////////////////////////////////////////////
// CViewInvoice message handlers

void CViewInvoice::SetPo(long lPO)
{
	m_lPO = lPO ;
	InitializeFilters() ;
	this->Invalidate() ;
}

void CViewInvoice::DrawCustomerData(CDC *pDC, CRect rect, long lCustomerId)
{
	CSetCustomer setCustomer(&g_dbFlooring) ;
	setCustomer.m_strFilter.Format("[CustomerID] = '%d'", lCustomerId) ;
	setCustomer.Open() ;
	CString strCustomer = setCustomer.m_LastName ;
	strCustomer.Format("%s, %s",
		setCustomer.m_LastName,
		setCustomer.m_FirstName) ;
	strCustomer.MakeUpper() ;

	pDC->DrawText("Name:", rect, DT_LEFT | DT_SINGLELINE) ;
	int iStartY = rect.top ;
	CRect temp = CRect(iCOLUMN, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT) ;
	pDC->DrawText(strCustomer, temp, DT_CENTER | DT_SINGLELINE | DT_CALCRECT) ;
	if (temp.right <= iRIGHT_MARGIN)
	{
		pDC->DrawText(strCustomer, CRect(iCOLUMN, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_CENTER | DT_SINGLELINE) ;
	}
	else
	{
		pDC->DrawText(strCustomer, CRect(iCOLUMN, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_LEFT | DT_SINGLELINE) ;
	}
	pDC->MoveTo(iCOLUMN, iStartY + iHEIGHT - 5) ;
	pDC->LineTo(iRIGHT_MARGIN, iStartY + iHEIGHT - 5) ;
	setCustomer.Close() ;
}

const int iX_QUANTITY = 70 ;
const int iX_UOM = 40 ;
const int iX_DESCRIPTION = 270 ; ;
const int iX_UNIT = 90 ;
const int iX_EXTENDED = 90 ;
 
void CViewInvoice::DrawBasic(CDC *pDC, CRect& rect)
{
	CString strTemp ;
	m_setMaterialDetails.Requery() ;

	try
	{
//		m_setMaterialDetails.MoveFirst() ;

		DrawHeadings(pDC, rect, "BASIC LABOR") ;

		int iY = rect.top ;

		while(!m_setMaterialDetails.IsEOF())
		{
			int iX = rect.left ;

			double fCost[2] ;
			double fExtCost[2] ;

			fCost[COST] = m_setMaterialDetails.m_UnitPrice ;
			fExtCost[COST] = Currency(fCost[COST]  * m_setMaterialDetails.m_InstallQuantity) ;

			fCost[RETAIL] = m_setMaterialDetails.m_UnitRetail ;
			fExtCost[RETAIL] = Currency(fCost[RETAIL]  * m_setMaterialDetails.m_InstallQuantity) ;

			strTemp.Format("%8.*f", m_setMaterialDetails.m_NumberOfDecimals, m_setMaterialDetails.m_InstallQuantity) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setMaterialDetails.m_UOMDescription ; 
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setMaterialDetails.m_LaborDescription ;
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

			strTemp.Format("%9.2f", fCost[RETAIL] ) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

			strTemp.Format("%9.2f",	fExtCost[RETAIL] ) ;
			DrawBoxWithText(pDC, &iX, iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp.Format("%9.2f", fCost[COST] ) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

			strTemp.Format("%9.2f",	fExtCost[COST] ) ;
			DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			m_fBasic[COST] += fExtCost[COST] ;
			m_fBasic[RETAIL] += fExtCost[RETAIL] ;
			m_setMaterialDetails.MoveNext() ;
		}

		rect.top = iY + iHEIGHT;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

}

void CViewInvoice::DrawOptions(CDC *pDC, CRect& rect)
{
	CString strTemp ;


	try
	{
		m_setOptionDetails.Requery() ;

		DrawHeadings(pDC, rect, "OPTIONAL LABOR") ;

		int iY = rect.top ;

		while(!m_setOptionDetails.IsEOF())
		{
			int iX = rect.left ;
			m_setOptions.m_strFilter.Format("[OptionID] = '%d'", m_setOptionDetails.m_OptionID) ;
			m_setOptions.Requery() ;

			if (m_setOptions.m_PrintOnInvoice)
			{
				m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", m_setOptions.m_UnitOfMeasureID) ;
				m_setUOM.Requery() ;
				double fCost[2] ;
				double fExtCost[2] ;

				fCost[COST] = atof(m_setOptionDetails.m_UnitPrice) ;
				fExtCost[COST] = Currency(fCost[COST]  * m_setOptionDetails.m_Quantity) ;

				fCost[RETAIL] = atof(m_setOptionDetails.m_UnitRetail) ;
				fExtCost[RETAIL] = Currency(fCost[RETAIL]  * m_setOptionDetails.m_Quantity) ;

				strTemp.Format("%8.*f", m_setUOM.m_NumberOfDecimals, m_setOptionDetails.m_Quantity) ;
				DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

				strTemp = m_setUOM.m_Description ; 
				strTemp.MakeUpper() ;
				DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

				strTemp = m_setOptions.m_OptionDescription ;
				strTemp.MakeUpper() ;
				DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

				strTemp.Format("%9.2f", fCost[RETAIL]) ;
				DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

				strTemp.Format("%9.2f",	fExtCost[RETAIL]) ;
				DrawBoxWithText(pDC, &iX, iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

				strTemp.Format("%9.2f", fCost[COST]) ;
				DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

				strTemp.Format("%9.2f",	fExtCost[COST]) ;
				DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

				m_fOptions[COST] += fExtCost[COST] ;
				m_fOptions[RETAIL] += fExtCost[RETAIL] ;
			}
			m_setOptionDetails.MoveNext() ;
		}

		rect.top = iY + iHEIGHT;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}
}

void CViewInvoice::DrawCustom(CDC *pDC, CRect& rect)
{
	CString strTemp ;

	try
	{
		m_setCustomDetails.Requery() ;

		DrawHeadings(pDC, rect, "CUSTOM LABOR") ;

		int iY = rect.top ;

		while(!m_setCustomDetails.IsEOF())
		{
			if (!m_setCustomDetails.m_NotOnInvoice)
			{
				int iX = rect.left ;
				m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", m_setCustomDetails.m_UnitOfMeasureID) ;
				m_setUOM.Requery() ;
				double fCost[2] ;
				double fExtCost[2] ;

				fCost[COST] = (atof(m_setCustomDetails.m_UnitPrice));
				fExtCost[COST] = Currency(fCost[COST] * m_setCustomDetails.m_Quanity) ;
				fCost[COST]  = Currency(fCost[COST] ) ;

				fCost[RETAIL] = atof(m_setCustomDetails.m_RetailPrice);
				fExtCost[RETAIL] = Currency(fCost[RETAIL] * m_setCustomDetails.m_Quanity) ;
				fCost[RETAIL]  = Currency(fCost[RETAIL] ) ;

				strTemp.Format("%8.*f", m_setUOM.m_NumberOfDecimals, m_setCustomDetails.m_Quanity) ;
				DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

				strTemp = m_setUOM.m_Description ; 
				strTemp.MakeUpper() ;
				DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

				strTemp = m_setCustomDetails.m_Description ;
				strTemp.MakeUpper() ;
				DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

				strTemp.Format("%9.2f", fCost[RETAIL]) ;
				DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

				strTemp.Format("%9.2f",	fExtCost[RETAIL] ) ;
				DrawBoxWithText(pDC, &iX, iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

				strTemp.Format("%9.2f", fCost[COST]) ;
				DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

				strTemp.Format("%9.2f",	fExtCost[COST] ) ;
				DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

				m_fCustom[COST] += fExtCost[COST] ;
				m_fCustom[RETAIL] += fExtCost[RETAIL] ;
			}
			m_setCustomDetails.MoveNext() ;
		}

		rect.top = iY + iHEIGHT;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}
}

void CViewInvoice::DrawComments(CDC *pDC, CRect& rect)
{
	if (m_setOrders.m_Invoice)
	{
		CString strTemp ;

		strTemp = m_setOrders.m_Notes ;

		rect.bottom = rect.top + 40 ;

		pDC->SelectObject(this->m_fontLarge) ;

		pDC->DrawText("Notes", rect, DT_CENTER | DT_SINGLELINE) ;
		pDC->SelectObject(this->m_fontFixedBold) ;
		rect.top += 20 ;

		rect.DeflateRect(5,5) ;
		int iRight = rect.right ;
		pDC->DrawText(strTemp, rect, DT_CALCRECT | DT_LEFT | DT_WORDBREAK) ;
		rect.right = iRight ;
		pDC->DrawText(strTemp, rect, DT_LEFT | DT_WORDBREAK) ;
		rect.InflateRect(5,5) ;
		CBrush *pOldBrush = (CBrush *) pDC->SelectStockObject(NULL_BRUSH) ;
		pDC->Rectangle(rect) ;
		pDC->SelectObject(pOldBrush) ;
		rect.top = rect.bottom ;

		rect.top += 10 ;

	}

}

void CViewInvoice::InitializeFilters()
{
	CString strFilter ;

	strFilter.Format("[OrderID] = '%d'", m_lPO) ;

	m_setMaterialDetails.m_strFilter = "((" + strFilter + ") AND (Deleted = 0) AND (PrintOnInvoice = 1))" ; ;
	m_setOptionDetails.m_strFilter = "((" + strFilter + ") AND (Deleted = 0) AND (PrintOnInvoice = 1))" ;
	m_setCustomDetails.m_strFilter = "((" + strFilter + ") AND (Deleted = 0) AND (NotOnInvoice = 0))" ; ;
	m_setOrders.m_strFilter = strFilter ;

//	m_setMaterialDetails.m_NotOnWorkOrder = 0 ;
//	m_setCustomDetails.m_NotOnInvoice ;

	m_setMaterialDetails.Requery() ;
	m_setOptionDetails.Requery() ;
	m_setCustomDetails.Requery() ;
	m_setOrders.Requery() ;
}

void CViewInvoice::DrawTotal(CDC *pDC, CRect &rect)
{
	double fMinimum[2] ;
	fMinimum[COST] = 0 ;
	fMinimum[RETAIL] = 0 ;

	DrawHeadings2(pDC, rect, "") ;
	CSetMaterialType setMT(&g_dbFlooring) ;
	setMT.m_strFilter.Format("[MaterialTypeID] = '%d'", m_setOrders.m_MaterialTypeID ) ;
	setMT.Open() ;

	if (!m_setOrders.m_NoMinimum) 
	{
		CString strMin ;
		fMinimum[COST] = atof(setMT.m_MinimumPrice) ;
		fMinimum[RETAIL] = atof(setMT.m_MinimumRetail) ;
	}
	bool bOnlyBasic = setMT.m_OnlyBasicToMinimum == TRUE;

	setMT.Close() ;

	bool bMinApplied[2] ;
	bMinApplied[COST] = false ;
	bMinApplied[RETAIL] = false ;

	double fTotal[2] ;
	fTotal[COST] = m_fBasic[COST] ;
	fTotal[RETAIL] = m_fBasic[RETAIL] ;

	if (!bOnlyBasic)
	{
		fTotal[COST] += m_fOptions[COST] + m_fCustom[COST] + m_fTripCharg[COST] ;
		fTotal[RETAIL] += m_fOptions[RETAIL] + m_fCustom[RETAIL] + m_fTripCharg[RETAIL] ;
	}

	if (fMinimum[COST] > fTotal[COST])
	{
		bMinApplied[COST] = true ;
		fTotal[COST] = fMinimum[COST] ;
	}

	if (fMinimum[RETAIL] > fTotal[RETAIL])
	{
		bMinApplied[RETAIL] = true ;
		fTotal[RETAIL] = fMinimum[RETAIL] ;
	}

	if (bOnlyBasic)
	{
		fTotal[COST] += m_fOptions[COST] + m_fCustom[COST] + m_fTripCharg[COST] ;
		fTotal[RETAIL] += m_fOptions[RETAIL] + m_fCustom[RETAIL] + m_fTripCharg[RETAIL] ;
	}

	int iX = rect.left ;
	int iY = rect.top ;
	CString strTemp ;

	if (!m_setOrders.IsFieldNull(&m_setOrders.m_BilledAmount) && (m_setOrders.m_BilledAmount != m_setOrders.m_OrderAmount))
	{
		double fBilled = atof(m_setOrders.m_BilledAmount) ;
		{
			int iX = rect.left ;
			DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY + iX_UOM + iX_DESCRIPTION, iHEIGHT, "ADMINISTRATIVE OVERIDE APPLIED",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
			strTemp.Format("%9.2f",	fTotal[RETAIL]) ; 
			DrawBoxWithText(pDC, &iX, iY, iX_EXTENDED + iX_UNIT, iHEIGHT, strTemp,	DT_RIGHT | DT_SINGLELINE | DT_VCENTER) ;
			strTemp.Format("%9.2f",	fBilled) ; 
			DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED + iX_UNIT, iHEIGHT, strTemp,	DT_RIGHT | DT_SINGLELINE | DT_VCENTER) ;
		}
	}
	else
	{
		if (bMinApplied[COST] && bMinApplied[RETAIL])
		{
			DrawBoxWithText(pDC, &iX,  rect.top, iX_QUANTITY + iX_UOM + iX_DESCRIPTION, iHEIGHT, "TOTAL - MINIMUM APPLIED BOTH",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
		}
		else if (bMinApplied[COST])
		{
			DrawBoxWithText(pDC, &iX,  rect.top, iX_QUANTITY + iX_UOM + iX_DESCRIPTION, iHEIGHT, "TOTAL - MINIMUM APPLIED COST ONLY",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
		}
		else if (bMinApplied[RETAIL])
		{
			DrawBoxWithText(pDC, &iX,  rect.top, iX_QUANTITY + iX_UOM + iX_DESCRIPTION, iHEIGHT, "TOTAL - MINIMUM APPLIED RETAIL ONLY",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
		}
		else
		{
			DrawBoxWithText(pDC, &iX,  rect.top, iX_QUANTITY + iX_UOM + iX_DESCRIPTION, iHEIGHT, "TOTAL",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
		}

		strTemp.Format("%9.2f",	fTotal[RETAIL]) ;
		DrawBoxWithText(pDC, &iX, iY, iX_EXTENDED + iX_UNIT, iHEIGHT, strTemp,	DT_RIGHT | DT_SINGLELINE | DT_VCENTER) ;

		strTemp.Format("%9.2f",	fTotal[COST]) ;
		DrawBoxWithText(pDC, &iX, &iY, iX_EXTENDED + iX_UNIT, iHEIGHT, strTemp,	DT_RIGHT | DT_SINGLELINE | DT_VCENTER) ;
	}
	rect.top = iY + iHEIGHT;
}

void CViewInvoice::DrawTripCharge(CDC *pDC, CRect &rect)
{
	CString strTemp ;

	double fCost[2] ;
	fCost[COST] = atof(m_setOrders.m_TripCharge) ;
	fCost[RETAIL] = atof(m_setOrders.m_TripCharge) ;

	if (fCost[COST] != 0)
	{
		DrawHeadings(pDC, rect, "TRIP CHARGE") ;

		int iY = rect.top ;

		CSetMaterialType setMT(&g_dbFlooring) ;
		setMT.m_strFilter.Format("[MaterialTypeID] = '%d'", m_setOrders.m_MaterialTypeID ) ;
		setMT.Open() ;

		fCost[COST] *= setMT.m_TripChargeMultiplier ;
		fCost[COST] = Currency(fCost[COST]) ;

		fCost[RETAIL] = Currency(fCost[RETAIL]) ;

		setMT.Close() ;

		int iX = rect.left ;

		DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "1", DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

		DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "EA", DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

		DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "TRIP CHARGE" ) ;

		strTemp.Format("%9.2f", fCost[RETAIL]) ;
		DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, "", DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;
		DrawBoxWithText(pDC, &iX, iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

		strTemp.Format("%9.2f", fCost[COST]) ;
		DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,		iHEIGHT, "", DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;
		DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

		m_fTripCharg[COST] += fCost[COST] ;
		m_fTripCharg[RETAIL] += fCost[RETAIL] ;
		rect.top = iY + iHEIGHT;
	}
}

void CViewInvoice::DrawLogo(CDC* pDC)
{
	CRect rect = CRect(iLEFT_MARGIN, iTOP_OF_LOGO, iCENTER, iBOTTOM_OF_LOGO) ;
	CString strOut = m_setCompanyInfo.m_Name.Trim() + "\r\n" + m_setCompanyInfo.m_Address1.Trim() + "\r\n" ;
	strOut += m_setCompanyInfo.m_City.Trim() + ", " + m_setCompanyInfo.m_State.Trim() + "  " + m_setCompanyInfo.m_Zip.Trim() + "\r\nVendor #" + m_setCompanyInfo.m_VendorNumber.Trim() ;
	pDC->DrawText(strOut, rect, DT_CENTER | DT_WORDBREAK | DT_CALCRECT) ;
	int iHeight = rect.bottom - rect.top ;
	int iYOffset = (iHeight) / 2 ;
	rect = CRect(iLEFT_MARGIN, iTOP_MARGIN + iYOffset, iCENTER, iBOTTOM_OF_LOGO) ;
	pDC->DrawText(strOut, rect, DT_CENTER | DT_WORDBREAK) ;
}

void CViewInvoice::DrawHeadings(CDC *pDC, CRect &rect, CString strTitle)
{
	DrawHeadings2(pDC, rect, strTitle) ;

	int iX = rect.left ;
	int iY = rect.top ;

	CFont* pfontOld = (CFont*) pDC->SelectObject(&m_fontNormal) ;

	CBrush* pOldBrush = (CBrush*) pDC->SelectStockObject(LTGRAY_BRUSH) ;
	int iOldMode = pDC->SetBkMode(TRANSPARENT) ;

	this->DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "QUANT.",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "UOM",			DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "DESCRIPTION",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,			iHEIGHT, "UNIT",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_EXTENDED,		iHEIGHT, "EXTENDED",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UNIT,			iHEIGHT, "UNIT",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC,  iX, &iY, iX_EXTENDED,		iHEIGHT, "EXTENDED",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

	pDC->SelectObject(pfontOld) ;
	pDC->SetBkMode(iOldMode) ;
	pDC->SelectObject(pOldBrush) ;

	rect.top = iY ;
}

void CViewInvoice::DrawHeadings2(CDC *pDC, CRect &rect, CString strTitle)
{
	int iX = rect.left ;
	int iY = rect.top ;

	CFont* pfontOld = (CFont*) pDC->SelectObject(&m_fontNormal) ;

	pDC->DrawText(strTitle, CRect(iX, iY, iX + iX_QUANTITY + iX_UOM + iX_DESCRIPTION, iY +iHEIGHT), DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
	iX += iX_QUANTITY + iX_UOM + iX_DESCRIPTION ;

	CBrush* pOldBrush = (CBrush*) pDC->SelectStockObject(LTGRAY_BRUSH) ;
	int iOldMode = pDC->SetBkMode(TRANSPARENT) ;

	this->DrawBoxWithText(pDC, &iX,  iY, iX_UNIT + iX_EXTENDED,	iHEIGHT, "RETAIL",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC,  iX,  &iY, iX_UNIT + iX_EXTENDED,	iHEIGHT, "COST",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

	pDC->SelectObject(pfontOld) ;
	pDC->SetBkMode(iOldMode) ;
	pDC->SelectObject(pOldBrush) ;

	rect.top = iY ;
}
