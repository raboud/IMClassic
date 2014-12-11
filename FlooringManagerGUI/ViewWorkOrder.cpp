/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewWorkOrder.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "Flooring.h"
#include "ViewWorkOrder.h"
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

/////////////////////////////////////////////////////////////////////////////
// CViewWorkOrder

IMPLEMENT_DYNCREATE(CViewWorkOrder, CCFViewReport)


CViewWorkOrder::CViewWorkOrder()
:	m_setMaterialDetails(&g_dbFlooring), m_setOptionDetails(&g_dbFlooring),	m_setCustomDetails(&g_dbFlooring),
	m_setOrders(&g_dbFlooring), m_setUOM(&g_dbFlooring), m_setOptions(&g_dbFlooring), m_setCustomer(&g_dbFlooring)
{
	m_setMaterialDetails.Open() ;
	m_setOptionDetails.Open() ;
	m_setCustomDetails.Open() ;
	m_setOrders.Open() ;

	m_setUOM.Open() ;

//	m_setMaterial.Open() ;
	m_setOptions.Open() ;
	m_setCustomer.Open() ;
}

CViewWorkOrder::~CViewWorkOrder()
{
	m_setMaterialDetails.Close() ;
	m_setOptionDetails.Close() ;
	m_setCustomDetails.Close() ;
	m_setOrders.Close() ;

	m_setUOM.Close() ;

//	m_setMaterial.Close() ;
	m_setOptions.Close() ;
	m_setCustomer.Close() ;
}


BEGIN_MESSAGE_MAP(CViewWorkOrder, CCFViewReport)
	//{{AFX_MSG_MAP(CViewWorkOrder)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewWorkOrder drawing

void CViewWorkOrder::OnDraw(CDC* pDC)
{
	CPen pen ;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0) ) ;
	pDC->SelectObject(&pen) ;


	int iStartY = iTOP_MARGIN;

	pDC->SelectObject(&m_fontLarge) ;
	pDC->DrawText("WORK ORDER", CRect(iLEFT_MARGIN, iStartY, iRIGHT_MARGIN, iStartY + iHEIGHT), DT_CENTER | DT_VCENTER | DT_SINGLELINE ) ;
	iStartY += 35 ;

	CString strOut = "Purchase Order(s)";

	pDC->SelectObject(&m_fontFixedBold) ;
	try
	{
		m_setOrders.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	while (!m_setOrders.IsEOF())
	{
		if (m_setOrders.m_MaterialTypeID != 4)
		{
			strOut += " - " ;
			strOut += m_setOrders.m_PurchaseOrderNumber ;
			if (m_setOrders.m_PurchaseOrderNumber.GetLength() == 3)
			{
				strOut += " WARRANTY" ;
			}
		}
		m_setOrders.MoveNext() ;
	} 
	pDC->TextOut(iLEFT_MARGIN, iStartY, strOut) ; 
	iStartY += iHEIGHT ;
	CRect rect(iLEFT_MARGIN, iStartY, iRIGHT_MARGIN, iStartY + 150) ;
	DrawCustomerData(pDC, rect, m_setOrders.m_CustomerID) ;
	rect.top += 10 ;
	DrawDirections(pDC, rect) ;

	pDC->DrawText("INSTALLER", CRect(500, iStartY, 600, iStartY + iHEIGHT), DT_LEFT | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, 600, &iStartY, 175, iHEIGHT, "") ;
	pDC->DrawText("DATE", CRect(500, iStartY, 600, iStartY + iHEIGHT), DT_LEFT | DT_SINGLELINE | DT_VCENTER ) ;
	if (m_bScheduled)
	{
		strOut = m_dateScheduled.Format("%m/%d/%Y") ;
	}
	else
	{
		strOut = "     /     /     " ;
	}
	this->DrawBoxWithText(pDC, 600, &iStartY, 175, iHEIGHT, strOut, DT_CENTER | DT_SINGLELINE) ;

	m_fTotal = 0.0 ;
	m_fMaterialCost = 0.0 ;
	DrawBasic(pDC, rect);
	DrawOptions(pDC, rect, true);   // draw options with ApplyToMinimumWO set
	DrawMinApplied(pDC, rect) ;
	DrawStorePickup(pDC, rect) ;
	DrawOptions(pDC, rect, false);  // draw options with ApplyToMinimumWO unset
	DrawCustom(pDC, rect);
	DrawTotal(pDC,rect) ;
	rect.top += 10 ;

	DrawExtras(pDC, rect) ;
	rect.top += 10 ;

	DrawPadding(pDC, rect) ;

	DrawComments(pDC, rect);

	DrawInstallerComments(pDC, rect) ;
	rect.top += 10 ;

	DrawMaterials(pDC, rect) ;
}

/////////////////////////////////////////////////////////////////////////////
// CViewWorkOrder message handlers

bool CViewWorkOrder::SetPoList(CPoList* plistPOs)
{
	bool bOk = true ;

	m_PoList.AddHead(plistPOs) ;
	InitializeFilters() ;

	m_setOrders.MoveFirst() ;
	m_bScheduled = false ;
	CTime dateStart ;
	CTime dateEnd ;

	while (!m_setOrders.IsEOF())
	{
		if (m_setOrders.m_Scheduled)
		{
			if (!m_bScheduled)
			{
				m_bScheduled = m_setOrders.m_Scheduled == TRUE  ;
				m_bAM = m_setOrders.m_ScheduledAM == TRUE  ;
				m_dateScheduled = m_setOrders.m_ScheduleDate ;

				dateStart = CTime(m_dateScheduled.GetYear(), m_dateScheduled.GetMonth(), m_dateScheduled.GetDay(), 0, 0, 0) ;
				dateEnd = CTime(m_dateScheduled.GetYear(), m_dateScheduled.GetMonth(), m_dateScheduled.GetDay(), 24, 59, 59) ;
			}
			else
			{
				if ((m_setOrders.m_ScheduleDate > dateEnd) || (m_setOrders.m_ScheduleDate < dateStart))
				{
					bOk = false ;
				}
				else if ((m_setOrders.m_ScheduledAM == TRUE)!= m_bAM)
				{
					bOk = false ;
				}

//			break ;
			}
		}
		m_setOrders.MoveNext() ;
	}
	m_setOrders.MoveFirst() ;

	if (bOk && m_bScheduled)
	{
		while (!m_setOrders.IsEOF())
		{
			if (!m_setOrders.m_Scheduled)
			{
				m_setOrders.Edit() ;
				m_setOrders.m_Scheduled = m_bScheduled ;
				m_setOrders.m_ScheduledAM  = m_bAM ;
				m_setOrders.m_ScheduleDate	= dateStart ;
				m_setOrders.Update() ;
			}
			m_setOrders.MoveNext() ;
		}
		m_setOrders.MoveFirst() ;
	}

	this->Invalidate() ;

	return bOk ;
}

void CViewWorkOrder::DrawCustomerData(CDC *pDC, CRect& rect, long lCustomerId)
{
	m_setCustomer.m_strFilter.Format("[CustomerID] = '%d'", lCustomerId) ;
	m_setCustomer.Requery() ;
	CString strCustomer = m_setCustomer.m_LastName ;
	strCustomer.Format("%s, %s\r\n%s\r\n%s, %s %s\r\nHOME: %s - WORK: %s",
		m_setCustomer.m_LastName,
		m_setCustomer.m_FirstName,
		m_setCustomer.m_Address,
		m_setCustomer.m_City,
		m_setCustomer.m_State,
		m_setCustomer.m_ZipCode,
		m_setCustomer.m_PhoneNumber,
		m_setCustomer.m_WorkNumber) ;
	strCustomer.MakeUpper() ;

	int iRight = rect.right ;
	pDC->DrawText(strCustomer, rect, DT_CALCRECT | DT_LEFT | DT_WORDBREAK) ;
	rect.right = iRight ;
	pDC->DrawText(strCustomer, rect, DT_LEFT | DT_WORDBREAK) ;

	rect.top = rect.bottom ;
}

const int iX_QUANTITY = 90 ;
const int iX_UOM = 50 ;
const int iX_DESCRIPTION = 400 ; ;
const int iX_UNIT_COST = 100 ;
const int iX_EXTENDED = 110 ;
 
void CViewWorkOrder::DrawBasic(CDC *pDC, CRect& rect)
{
	CString strTemp ;

	int iX = rect.left ;
	int iY = rect.top ;

	pDC->SelectObject(&m_fontNormal) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "QUANTITY",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "UOM",			DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "DESCRIPTION",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, "UNIT COST",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, "EXTENDED",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	pDC->SelectObject(m_fontFixedBold) ;

	try
	{
		m_setMaterialDetails.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	m_bStorePickup = false ;
	while(!m_setMaterialDetails.IsEOF())
	{
		int iX = rect.left ;
//		m_setMaterial.m_strFilter.Format("[MaterialID] = '%d'", m_setMaterialDetails.m_MaterialID) ;
//		m_setMaterial.Requery() ;

		if (!m_bStorePickup)
		{
			m_bStorePickup = m_setMaterialDetails.m_MatStatusID == 4 ;
		}

		double fCost = atof(m_setMaterialDetails.m_UnitCost) ;
		double fExtCost = Currency(fCost * m_setMaterialDetails.m_Size) ;

		if (!m_setMaterialDetails.m_IsPadding && fExtCost > 0.0)
		{
//			m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", m_setMaterial.m_UnitOfMeasureID) ;
//			m_setUOM.Requery() ;

			strTemp.Format("%8.*f", m_setMaterialDetails.m_NumberOfDecimals, m_setMaterialDetails.m_Size) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setMaterialDetails.m_Description ; 
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setMaterialDetails.m_LaborDescription ;
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

			strTemp.Format("%9.2f", fCost) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

			strTemp.Format("%9.2f",	fExtCost) ;
			DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			m_fMaterialCost += fExtCost ;
		}

		m_setMaterialDetails.MoveNext() ;
	}

	rect.top = iY ;

}

void CViewWorkOrder::DrawOptions(CDC *pDC, CRect& rect, bool bApplyToMinimumWOOnly)
{
	CString strTemp ;

	int iY = rect.top ;

	try
	{
		m_setOptionDetails.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	while(!m_setOptionDetails.IsEOF())
	{
		int iX = rect.left ;

		int iApply = (bApplyToMinimumWOOnly) ? 1 : 0;
		m_setOptions.m_strFilter.Format("[OptionID] = '%d' AND [ApplyToMinimumWO] = '%d'", m_setOptionDetails.m_OptionID, iApply) ;

		m_setOptions.Requery() ;

		if ((!m_setOptions.IsEOF()) && (!m_setOptions.m_IsPadding) && (m_setOptions.m_PrintOnWorkOrder))
		{
			m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", m_setOptions.m_UnitOfMeasureID) ;
			m_setUOM.Requery() ;
			double fCost = atof(m_setOptionDetails.m_UnitCost) ;
			double fExtCost = Currency(fCost * m_setOptionDetails.m_Quantity) ;

			strTemp.Format("%8.*f", m_setUOM.m_NumberOfDecimals, m_setOptionDetails.m_Quantity) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setUOM.m_Description ; 
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setOptions.m_OptionDescription ;
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

			strTemp.Format("%9.2f", fCost) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

			strTemp.Format("%9.2f",	fExtCost) ;
			DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			if (bApplyToMinimumWOOnly)
			{
				m_fMaterialCost += fExtCost;
			}
			else
			{
				m_fTotal += fExtCost ;
			}
		}
		m_setOptionDetails.MoveNext() ;
	}

	rect.top = iY ;
}

void CViewWorkOrder::DrawCustom(CDC *pDC, CRect& rect)
{
	CString strTemp ;

	int iY = rect.top ;

	try
	{
		m_setCustomDetails.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	while(!m_setCustomDetails.IsEOF())
	{
		if (!m_setCustomDetails.m_NotOnWorkOrder)
		{
			int iX = rect.left ;
			m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", m_setCustomDetails.m_UnitOfMeasureID) ;
			m_setUOM.Requery() ;
			double fCost = Currency(atof(m_setCustomDetails.m_RetailPrice)  * m_setCustomDetails.m_CostMultiplier * m_setCustomDetails.m_Multiplier, false);
			double fExtCost = Currency(fCost * m_setCustomDetails.m_Quanity) ;

			if (m_setCustomDetails.IsFieldNull(&m_setCustomDetails.m_UnitCost))
			{
				fCost = Currency(atof(m_setCustomDetails.m_RetailPrice)  * m_setCustomDetails.m_CostMultiplier * m_setCustomDetails.m_Multiplier, false);
				fExtCost = Currency(fCost * m_setCustomDetails.m_Quanity) ;
			}
			else
			{
				fCost = atof(m_setCustomDetails.m_UnitCost) ;
				fExtCost = Currency(fCost * m_setCustomDetails.m_Quanity) ;
			}

			strTemp.Format("%8.*f", m_setUOM.m_NumberOfDecimals, m_setCustomDetails.m_Quanity) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setUOM.m_Description ; 
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setCustomDetails.m_Description ;
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

			strTemp.Format("%9.2f", fCost) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;

			strTemp.Format("%9.2f",	fExtCost) ;
			DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			m_fTotal += fExtCost ;
		}
		m_setCustomDetails.MoveNext() ;
	}

	rect.top = iY ;
}

void CViewWorkOrder::DrawComments(CDC *pDC, CRect& rect)
{
	m_setOrders.MoveFirst() ;
	CString strTemp ;

	bool bFirst = true ;
	while (!m_setOrders.IsEOF())
	{
		if (m_setOrders.m_Notes != "")
		{
			if (!bFirst)
			{
				strTemp += "\r\n" ;
			}
			bFirst = false ;
			strTemp += m_setOrders.m_Notes ;
			strTemp.GetLength() ;
			strTemp.TrimRight("\n\r") ;
		}

		m_setOrders.MoveNext() ;
	}

	strTemp.TrimRight("\n\r") ;
	while (strTemp.Replace("\n\r\n\r\n\r", "\n\r\n\r")) ;

	if (!bFirst)
	{
		rect.bottom = rect.top + 40 ;

		pDC->SelectObject(this->m_fontLarge) ;

		pDC->DrawText("Special Instructions", rect, DT_CENTER | DT_SINGLELINE) ;
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

void CViewWorkOrder::InitializeFilters()
{
	CString strTemp ;
	CString strFilter ;

	POSITION pos = this->m_PoList.GetHeadPosition() ;
	bool bFirst = true ;
	while (pos)
	{
		strTemp.Format("[OrderID] = '%d'", m_PoList.GetNext(pos) ) ;
		if (!bFirst)
		{
			strFilter += " OR " ;
		}
		bFirst = false ;
		strFilter += strTemp ;
	} 
	m_setMaterialDetails.m_MatStatusID ;
	m_setMaterialDetails.m_strFilter = "(" + strFilter + ") AND (MatStatusID = 4 OR MatStatusID = 2 OR MatStatusID = 11)" ;
	m_setOptionDetails.m_strFilter = strFilter ;
	m_setCustomDetails.m_strFilter = strFilter ;
	m_setOrders.m_strFilter = strFilter ;

	m_setMaterialDetails.Requery() ;
	m_setOptionDetails.Requery() ;
	m_setCustomDetails.Requery() ;
	m_setOrders.Requery() ;

}

void CViewWorkOrder::DrawTotal(CDC *pDC, CRect &rect)
{
	int iX = rect.left ;
	DrawBoxWithText(pDC, &iX,  rect.top, iX_QUANTITY + iX_UOM + iX_DESCRIPTION + iX_UNIT_COST, iHEIGHT, "TOTAL",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;

	CString strTemp ;
	strTemp.Format("%9.2f",	m_fTotal) ;

	int iY = rect.top ;
	DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED, iHEIGHT, strTemp,	DT_RIGHT | DT_SINGLELINE | DT_VCENTER) ;
	rect.top = iY ;
}

void CViewWorkOrder::DrawPadding(CDC *pDC, CRect &rect)
{
	CString strTemp ;

	int iRolls ;
	int iFeet ;

	const int iX_TYPE = 500 ;
	const int iX_AMOUNT = 250 ; ;

	try
	{
		m_setOptionDetails.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	try
	{
		m_setMaterialDetails.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	bool bFirst = true ;	
	int iY = rect.top ;

	while(!m_setOptionDetails.IsEOF())
	{
		int iX = rect.left ;
		m_setOptions.m_strFilter.Format("[OptionID] = '%d'", m_setOptionDetails.m_OptionID) ;
		m_setOptions.Requery() ;

		if (m_setOptions.m_IsPadding)
		{
			if (bFirst)
			{
				pDC->SelectObject(this->m_fontLarge) ;

				rect.bottom = rect.top + 40 ;
				pDC->DrawText("Padding", rect, DT_CENTER | DT_SINGLELINE) ;
				pDC->SelectObject(this->m_fontFixedBold) ;
				rect.top += 20 ;
				iY = rect.top ;
				bFirst = false ;
			}

			this->CalculatePadding(iRolls, iFeet, m_setOptionDetails.m_Quantity, m_setOptions.m_YardsPerRoll) ;

			DrawBoxWithText(pDC, &iX,  iY, iX_TYPE, iHEIGHT, m_setOptions.m_OptionDescription, DT_LEFT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp.Format("%d Rolls - %d Feet", iRolls, iFeet) ;
			DrawBoxWithText(pDC, &iX,  &iY, iX_AMOUNT,	iHEIGHT, strTemp ) ;
		}

		m_setOptionDetails.MoveNext() ;

	}
	while(!m_setMaterialDetails.IsEOF())
	{
		int iX = rect.left ;
//		m_setMaterial.m_strFilter.Format("[MaterialID] = '%d'", m_setMaterialDetails.m_MaterialID) ;
//		m_setMaterial.Requery() ;

		if (m_setMaterialDetails.m_IsPadding)
		{
			if (bFirst)
			{
				pDC->SelectObject(this->m_fontLarge) ;

				rect.bottom = rect.top + 40 ;
				pDC->DrawText("Padding", rect, DT_CENTER | DT_SINGLELINE) ;
				pDC->SelectObject(this->m_fontFixedBold) ;
				rect.top += 20 ;
				iY = rect.top ;
				bFirst = false ;
			}

			this->CalculatePadding(iRolls, iFeet, m_setMaterialDetails.m_Size, m_setMaterialDetails.m_YardsPerRoll) ;

			DrawBoxWithText(pDC, &iX,  iY, iX_TYPE, iHEIGHT, m_setMaterialDetails.m_LaborDescription, DT_LEFT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp.Format("%d Rolls - %d Feet", iRolls, iFeet) ;
			DrawBoxWithText(pDC, &iX,  &iY, iX_AMOUNT,	iHEIGHT, strTemp ) ;
		}

		m_setMaterialDetails.MoveNext() ;
	}
	
	rect.top = iY ;
	if (!bFirst)
	{
		rect.top += 10 ;
	}
}

void CViewWorkOrder::CalculatePadding(int &iRolls, int &iFeet, double fYards, int iYardsPerRoll)
{
	fYards *= .93 ;

	int iWIDTH_OF_ROLL = 6 ;

	int iFeetPerRoll = iYardsPerRoll * 9 / iWIDTH_OF_ROLL ;

	iRolls = int(fYards / iYardsPerRoll) ;
	iFeet = int((((fmod(fYards, iYardsPerRoll)) * 9.0) / iWIDTH_OF_ROLL) + .5) ;

	if (iFeet >= iFeetPerRoll)
	{
		iFeet -= iFeetPerRoll;
		iRolls++ ;
	}
}

void CViewWorkOrder::DrawDirections(CDC *pDC, CRect &rect)
{
	if (m_setCustomer.m_Directions != "")
	{
		rect.bottom = rect.top + 40 ;
		pDC->SelectObject(this->m_fontLarge) ;

		pDC->DrawText("Driving Directions", rect, DT_CENTER | DT_SINGLELINE) ;
		pDC->SelectObject(this->m_fontFixedBold) ;
		rect.top += 20 ;

		CString strTemp = m_setCustomer.m_Directions ;

		rect.DeflateRect(5,5) ;
		int iRight = rect.right ;
		pDC->DrawText(strTemp, rect, DT_CALCRECT | DT_LEFT | DT_WORDBREAK) ;
		rect.right = iRight ;
		pDC->DrawText(strTemp, rect, DT_LEFT | DT_WORDBREAK) ;
		rect.InflateRect(5,5) ;
		CBrush *pOldBrush = (CBrush *) pDC->SelectStockObject(NULL_BRUSH) ;
		pDC->Rectangle(rect) ;
		pDC->SelectObject(pOldBrush) ;
		rect.top = rect.bottom + 10 ;
	}
}

void CViewWorkOrder::DrawMaterials(CDC *pDC, CRect &rect)
{
	CString strTemp ;

	int iY = rect.top ;
	bool bFirst = true ;


	try
	{
		m_setMaterialDetails.MoveFirst() ;
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	m_bStorePickup = false ;
	while(!m_setMaterialDetails.IsEOF())
	{
//		m_setMaterial.m_strFilter.Format("[MaterialID] = '%d'", m_setMaterialDetails.m_MaterialID) ;
//		m_setMaterial.Requery() ;

		if (!m_setMaterialDetails.m_IsPadding)
		{
			int iX = rect.left ;

			if (bFirst)
			{
				rect.bottom = rect.top + 40 ;

				pDC->SelectObject(this->m_fontLarge) ;

				pDC->DrawText("Material Checklist", rect, DT_CENTER | DT_SINGLELINE) ;
				pDC->SelectObject(this->m_fontFixedBold) ;
				rect.top += 20 ;
				iY = rect.top ;

				CFont* pfontOld = (CFont*) pDC->SelectObject(&m_fontNormal) ;
				this->DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "QUANTITY",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
				this->DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "UOM",			DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
				this->DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "STYLE - COLOR - SO NUMBER",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
				this->DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, "LOADED",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
				this->DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, "VERIFIED",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
				pDC->SelectObject(pfontOld) ;
				bFirst = false ;
			}
			iX = rect.left ;
//			m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", m_setMaterial.m_UnitOfMeasureID) ;
//			m_setUOM.Requery() ;

			strTemp.Format("%8.*f", m_setMaterialDetails.m_NumberOfDecimals, m_setMaterialDetails.m_Size) ;
			DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, strTemp, DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

			strTemp = m_setMaterialDetails.m_Description ; 
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, strTemp, DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

			if (m_setMaterialDetails.m_MatStatusID == 4)
			{
				strTemp.Format("%s - %s", m_setMaterialDetails.m_Style, m_setMaterialDetails.m_Color) ;
			}
			else
			{
				strTemp.Format("SO:%s: %s - %s", m_setMaterialDetails.m_SONumber, m_setMaterialDetails.m_Style, m_setMaterialDetails.m_Color) ;
			}
			strTemp.MakeUpper() ;
			DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, strTemp ) ;

			if (m_setMaterialDetails.m_MatStatusID == 4)
			{
				DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, "PICKUP", DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;
			}
			else
			{
				DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, "", DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;
			}
			DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, "", DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;
		}

		m_setMaterialDetails.MoveNext() ;
	}
	if (!bFirst)
	{
		rect.top = iY + 10;
	}
}

void CViewWorkOrder::DrawInstallerComments(CDC *pDC, CRect &rect)
{
	rect.bottom = rect.top + 40 ;

	pDC->SelectObject(this->m_fontLarge) ;

	pDC->DrawText("Installer Comments", rect, DT_CENTER | DT_SINGLELINE) ;
	pDC->SelectObject(this->m_fontFixedBold) ;
	rect.top += 20 ;
	int iY = rect.top ;

	for (int i=0; i< 5; i++)
	{
		DrawBoxWithText(pDC, rect.left,  &iY, 750, iHEIGHT, "", DT_LEFT | DT_SINGLELINE | DT_VCENTER ) ;
	}
	rect.top = iY ;

}

void CViewWorkOrder::DrawExtras(CDC *pDC, CRect &rect)
{
	int iX = rect.left ;
	rect.bottom = rect.top + 40 ;

	pDC->SelectObject(this->m_fontLarge) ;

	pDC->DrawText("Installer Extras", rect, DT_CENTER | DT_SINGLELINE) ;
	pDC->SelectObject(this->m_fontFixedBold) ;
	rect.top += 20 ;
	int iY = rect.top ;

	CFont* pfontOld = (CFont*) pDC->SelectObject(&m_fontNormal) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "QUANTITY",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "DESCRIPTION",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "APP",			DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, "UNIT COST",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	this->DrawBoxWithText(pDC, iX,	 &iY, iX_EXTENDED,		iHEIGHT, "EXTENDED",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	pDC->SelectObject(pfontOld) ;

	for (int i=0; i< 3; i++)
	{
		iX = rect.left ;
		DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "",	DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
		DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
		DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
		DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,	iHEIGHT, "",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
		DrawBoxWithText(pDC, iX,  &iY, iX_EXTENDED,		iHEIGHT, "",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	}
	iX = rect.left + iX_QUANTITY + iX_DESCRIPTION + iX_UOM;
	DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,	iHEIGHT, "TOTAL",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	DrawBoxWithText(pDC, iX,  &iY, iX_EXTENDED,		iHEIGHT, "",	DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;
	rect.top = iY ;
}

void CViewWorkOrder::DrawMinApplied(CDC *pDC, CRect &rect)
{
	double fMinimum = 0 ;
	if (!m_setOrders.m_NoMinimum) 
	{
		m_setOrders.MoveFirst() ;
		CSetMaterialType setMT(&g_dbFlooring) ;
		setMT.Open() ;
		while (!m_setOrders.IsEOF())
		{
			setMT.m_strFilter.Format("[MaterialTypeID] = '%d'", m_setOrders.m_MaterialTypeID ) ;
			setMT.Requery() ;

			double fMin = atof(setMT.m_MinimumCost) ;
			if (fMin > fMinimum)
			{
				fMinimum = fMin ;
			}
			m_setOrders.MoveNext() ;
		}
		setMT.Close() ;
	}

	bool bMinApplied = false ;

	if (fMinimum > m_fMaterialCost)
	{
		bMinApplied = true ;
		m_fMaterialCost = fMinimum ;
	}

	int iX = rect.left ;
	if (bMinApplied)
	{
		DrawBoxWithText(pDC, &iX,  rect.top, iX_QUANTITY + iX_UOM + iX_DESCRIPTION + iX_UNIT_COST, iHEIGHT, "MINIMUM APPLIED TO ABOVE",		DT_CENTER | DT_SINGLELINE | DT_VCENTER) ;
		CString strTemp ;
		strTemp.Format("%9.2f",	m_fMaterialCost) ;

		int iY = rect.top ;
		DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED, iHEIGHT, strTemp,	DT_RIGHT | DT_SINGLELINE | DT_VCENTER) ;
		rect.top = iY ;
	}
	m_fTotal += m_fMaterialCost ;
}

void CViewWorkOrder::DrawStorePickup(CDC *pDC, CRect &rect)
{
	int iY = rect.top ;

	if (m_bStorePickup)
	{
		int iX = rect.left ;
		DrawBoxWithText(pDC, &iX,  iY, iX_QUANTITY,		iHEIGHT, "", DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;
		DrawBoxWithText(pDC, &iX,  iY, iX_UOM,			iHEIGHT, "", DT_CENTER | DT_SINGLELINE | DT_VCENTER ) ;

		DrawBoxWithText(pDC, &iX,  iY, iX_DESCRIPTION,	iHEIGHT, "STORE PICKUP" ) ;

		DrawBoxWithText(pDC, &iX,  iY, iX_UNIT_COST,		iHEIGHT, "25.00", DT_RIGHT | DT_SINGLELINE | DT_VCENTER  ) ;
		DrawBoxWithText(pDC, iX, &iY, iX_EXTENDED,		iHEIGHT, "25.00", DT_RIGHT | DT_SINGLELINE | DT_VCENTER ) ;

		m_fTotal += 25.0 ;
	}

	rect.top = iY ;


}
