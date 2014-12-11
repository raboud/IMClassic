/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridMaterials.cpp: implementation of the CGridMaterials class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Flooring.h"
#include "GridMaterials.h"

#include "SetMaterialType.h"
#include "SetOrderMaterialsDetails.h"
#include "SetMatStatus.h"

#include "pricing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGridMaterials, CGridPOBase)
	//{{AFX_MSG_MAP(CGridMaterials)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CGridMaterials::CGridMaterials()
: m_setBasicLabor(&g_dbFlooring)
{
	m_bHas2Dim = false ;
	m_bHasSo = false ;
	m_bHasStyle = false ;
	m_bHasColor = false ;
	m_setBasicLabor.Open() ;
	m_lOrderID = 0 ;
}

CGridMaterials::~CGridMaterials()
{
	m_setBasicLabor.Close() ;
}

void CGridMaterials::OnSetup()
{
	CGridPOBase::OnSetup();

	AddColumn("  ID  ",									ID,				-1);
	AddColumn("BASIC                          ",	TYPE,			-2);
	AddColumn("STYLE             ",						STYLE,			-2);
	AddColumn("COLOR             ",						COLOR,			-2);
	AddColumn("SO NUMBER ",							SO,				-2);
	AddColumn("FEET",								LEN_FEET,		-1);
	AddColumn("INCHES",								LEN_INCHES,		-1);
	AddColumn("FEET",								WIDTH_FEET,		-1);
	AddColumn("INCHES",								WIDTH_INCHES,	-1);
	AddColumn("    SIZE    ",						MAT_SIZE,		-2);
	AddColumn("        STATUS         ",			STATUS,			-2);
	AddColumn("RETAIL",								RETAIL,			-2);
	AddColumn("EXTENSION",							EXTENTION,		-2);
	AddColumn("PRICE",								PRICE,			-2);
	AddColumn("COST",								COST,			-2);
	AddColumn("LENGTH",								LEN_FEET,		-2);
	AddColumn("WIDTH",								WIDTH_FEET,		-2);

	SetTH_NumberRows(2);
	SetTH_Height(24);

	SetTH_RowHeight(-1,12);
	SetTH_RowHeight(-2,12);
	
	InitColumnHeadings();

	CUGCell cell;

	// we are going to join some cells together...
	EnableJoins(TRUE);

	JoinCells(LEN_FEET, -2, LEN_INCHES, -2) ;        // "Length" will span Feet and Inches columns
	JoinCells(WIDTH_FEET, -2, WIDTH_INCHES, -2) ;    // "Width" will span Feet and Inches columns

	// All other column headers will span rows 1 and 2 of heading
	JoinCells(TYPE, -2, TYPE, -1) ;					
	JoinCells(STYLE, -2, STYLE, -1) ;
	JoinCells(COLOR, -2, COLOR, -1) ;
	JoinCells(STATUS, -2, STATUS, -1) ;
	JoinCells(SO, -2, SO, -1) ;
	JoinCells(RETAIL, -2, RETAIL, -1) ;
	JoinCells(MAT_SIZE, -2, MAT_SIZE, -1) ;
	JoinCells(EXTENTION, -2, EXTENTION, -1) ;

	EnableMenu(TRUE) ;

	GetColDefault(TYPE, &cell) ;
	cell.SetCellType( UGCT_DROPLIST);
	SetColDefault(TYPE, &cell);

	GetColDefault(LEN_FEET, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(LEN_FEET, &cell) ;
	SetColDefault(LEN_INCHES, &cell) ;
	SetColDefault(WIDTH_FEET, &cell) ;
	SetColDefault(WIDTH_INCHES, &cell) ;
	SetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(2) ;
	cell.SetFormatClass(&m_formatNumeric) ;
	SetColDefault(MAT_SIZE, &cell) ;
	cell.SetFormatClass(&m_formatCurrency) ;
	cell.SetReadOnly(TRUE) ;
	SetColDefault(EXTENTION, &cell) ;
	SetColDefault(RETAIL, &cell) ;
	SetColDefault(PRICE, &cell) ;
	SetColDefault(COST, &cell) ;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	HideColumn(PRICE);
	HideColumn(COST);

	RECT			rect = {0,0,0,0};
	// Create a mask edit to use with ultimate grid mask edit
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);
	m_editUpper.Create(WS_VISIBLE | ES_UPPERCASE, rect, this, 125);
}

void CGridMaterials::SetMaterialType(long lMaterialType, bool bShowActiveOnly/* = false*/)
{
	m_lMaterialType = lMaterialType ;
	if (bShowActiveOnly)
	{
		m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d' AND [Active] = 1", m_lMaterialType ) ;
	}
	else
	{
		m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
	}
	m_setBasicLabor.m_strSort = "[LaborDescription]" ;
	m_setBasicLabor.Requery() ;

	m_bHas2Dim = false ;
	m_bHasSo = false ;
	m_bHasStyle = false ;
	m_bHasColor = false ;
	CUGCell cell;

	GetColDefault(TYPE, &cell) ;
	cell.SetText(m_setBasicLabor.m_LaborDescription) ;

	CPricing clPricing;
	double dCost;
	double dPrice;
	double dRetail;
	bool bPriceOK = clPricing.GetBasicPrices(m_setBasicLabor.m_BasicLaborID, m_datePO, m_iStoreID, dCost, dPrice, dRetail);
	
	CString strRetail = "0.00";
	CString strCost = "0.00";
	CString strPrice = "0.00";

	if (bPriceOK)
	{
		strPrice.Format("%4.2f", dPrice);
		strCost.Format("%4.2f", dCost);
		strRetail.Format("%4.2f", dRetail);
	}

	CString strChoices = "" ;
	while (!m_setBasicLabor.IsEOF())
	{
		strChoices += m_setBasicLabor.m_LaborDescription ;
		strChoices += "\n" ;
		m_bHas2Dim = m_bHas2Dim || m_setBasicLabor.m_Has2Dimensions ;
		m_bHasSo = m_bHasSo || m_setBasicLabor.m_HasSONumber ;
		m_bHasStyle = m_bHasStyle || m_setBasicLabor.m_HasStyle ;
		m_bHasColor = m_bHasColor || m_setBasicLabor.m_HasColor ;
		m_setBasicLabor.MoveNext() ;
	}

	SetColWidth(LEN_FEET, 1) ;
	SetColWidth(LEN_INCHES, 1) ;
	SetColWidth(WIDTH_FEET, 1) ;
	SetColWidth(WIDTH_INCHES, 1) ;
	/*SetColWidth(SO, 1) ;
	SetColWidth(STYLE, 1) ;
	SetColWidth(COLOR, 1) ;*/

	if (!m_bHas2Dim)
	{
		HideColumn(LEN_FEET);
		HideColumn(LEN_INCHES);
		HideColumn(WIDTH_FEET);
		HideColumn(WIDTH_INCHES);
	}

	if (!m_bHasSo)
	{
		HideColumn(SO);
	}

	if (!m_bHasStyle)
	{
		HideColumn(STYLE);
	}

	if (!m_bHasColor)
	{
		HideColumn(COLOR);
	}
	strChoices.MakeUpper() ;

	cell.SetLabelText(strChoices);
	SetColDefault(TYPE, &cell);

	GetColDefault(RETAIL, &cell) ;
	if (strRetail == "")
	{
		strRetail = "0.00" ;
	}
	cell.SetText(strRetail) ;
	SetColDefault(RETAIL, &cell) ;

	GetColDefault(PRICE, &cell) ;
	if (strPrice == "")
	{
		strPrice = "0.00" ;
	}
	cell.SetText(strPrice) ;
	SetColDefault(PRICE, &cell) ;

	GetColDefault(COST, &cell) ;
	if (strCost == "")
	{
		strCost = "0.00" ;
	}
	cell.SetText(strCost) ;
	SetColDefault(COST, &cell) ;

	RedrawAll() ;
}

int CGridMaterials::OnCellTypeNotify(long ID, int col, long row, long msg, long param)
{
	if ((ID == UGCT_DROPLIST) && (msg == UGCT_DROPLISTSELECT ) && (col == TYPE))
	{
		CUGCell cell;
		CString strMaterial = *(CString*) param ;

		GetMaterialType(strMaterial ) ;

		QuickSetReadOnly(COLOR, row, !m_setBasicLabor.m_HasColor) ;
		QuickSetReadOnly(STYLE, row, !m_setBasicLabor.m_HasStyle) ;
		QuickSetReadOnly(SO, row, !m_setBasicLabor.m_HasSONumber) ;

		if (!m_setBasicLabor.m_Has2Dimensions)
		{
			JoinCells(LEN_FEET, row, WIDTH_INCHES, row) ;
			QuickSetText(LEN_FEET, row, "N\\A") ;
			QuickSetAlignment(LEN_FEET, row, UG_ALIGNCENTER) ;
			
			QuickSetReadOnly(LEN_FEET, row, true) ;
			QuickSetReadOnly(MAT_SIZE, row, false) ;
		}
		else
		{
			QuickSetReadOnly(LEN_FEET, row, false) ;
			QuickSetReadOnly(LEN_INCHES, row, false) ;
			QuickSetReadOnly(WIDTH_FEET, row, false) ;
			QuickSetReadOnly(WIDTH_INCHES, row, false) ;
			QuickSetReadOnly(MAT_SIZE, row, true) ;

			UnJoinCells(LEN_FEET, row) ;
		}

		CPricing clPricing;
		double dCost;
		double dPrice;
		double dRetail;
		bool bPriceOK = clPricing.GetBasicPrices(m_setBasicLabor.m_BasicLaborID, m_datePO, m_iStoreID, dCost, dPrice, dRetail);
	
		CString strRetail = "0.00";
		CString strCost = "0.00";
		CString strPrice = "0.00";

		if (bPriceOK)
		{
			strPrice.Format("%4.2f", dPrice);
			strCost.Format("%4.2f", dCost);
			strRetail.Format("%4.2f", dRetail);
		}

		QuickSetText(RETAIL, row, strRetail) ;
		QuickSetText(PRICE, row, strPrice) ;
		QuickSetText(COST, row, strCost) ;

	}

	QuickSetNumber(EXTENTION, row, CalculateRowRetail(row)) ;
	::PostMessage((GetParent())->m_hWnd, wm_MATERIAL_UPDATE, 0, 0) ;
	RedrawAll() ;
	return TRUE ;
}

int CGridMaterials::OnEditStart(int col, long row, CWnd **edit)
{
	int bEdit = FALSE ;

	if ((row >= 0) && (col >= 0) )
	{

		CUGCell cell ;
		GetCell(col, row, &cell) ;

		bEdit = !cell.GetReadOnly() ;

		if (bEdit)
		{
			*edit = &this->m_editUpper ;
			switch (col)
			{
				case SO:
					m_editNumeric.LimitText(iMAX_SO_NUMBER) ;
					*edit = &this->m_editNumeric ;
					break ;

				case LEN_INCHES: 
				case WIDTH_INCHES:
				case LEN_FEET: 
				case WIDTH_FEET: 
				case MAT_SIZE:
					m_editNumeric.LimitText(0) ;
					*edit = &this->m_editNumeric ;
					break ;
			}
		}
		if (col == TYPE)
		{
			bEdit = FALSE ;
		}
	}

	return bEdit ;

}

void CGridMaterials::OnKillFocus(CWnd* /* pOldWnd */ )
{
	for (long lRow = 0; lRow < GetNumberRows(); lRow++)
	{
		double fExtention = CalculateRowRetail(lRow);

		QuickSetNumber(EXTENTION, lRow, fExtention) ;
	}
	::PostMessage((GetParent())->m_hWnd, wm_MATERIAL_UPDATE, 0, 0) ;
	RedrawAll() ;
}


BOOL CGridMaterials::OnCanMove(int /* oldcol */, long /* oldrow */, int newcol, long /* newrow */)
{
	BOOL bOk = true ;

	switch(newcol)
	{
		case LEN_FEET:
		case LEN_INCHES :
		case WIDTH_FEET :
		case WIDTH_INCHES :
			bOk = m_bHas2Dim ;
			break ;

		case SO :
			bOk = m_bHasSo ;
			break ;

		case STYLE :
			bOk = m_bHasStyle ;
			break ;

		case COLOR :
			bOk = m_bHasColor ;
			break ;

		case PRICE: 
		case COST:
		case EXTENTION:
		case RETAIL:
			bOk = false ;
			break ;
	}
	return bOk ;
}

double CGridMaterials::CalculatePrice()
{
	long lRow ;
	double fPrice = 0 ;

	for (lRow = 0; lRow < this->GetNumberRows() ; lRow++)
	{
		fPrice += CalculateRowPrice(lRow) ;
	}

	return fPrice ;
}

double CGridMaterials::CalculateRowPrice(long lRow)
{
	double fPrice = 0;
	double fQuanity = 0;
	double fExtention = 0 ;

	GetMaterialType(lRow) ;

	CString strStatus = QuickGetText(STATUS, lRow) ;
	CSetMatStatus setStatus(&g_dbFlooring) ;
	setStatus.m_strFilter.Format("Status = '%s'", strStatus) ;
	setStatus.Open() ;
	if (!setStatus.IsEOF())
	{
		if (setStatus.m_Billable)
		{
			fQuanity = QuickGetNumber(MAT_SIZE, lRow) ;
			fPrice = QuickGetNumber(PRICE, lRow) ;
		}
	}

//	return fExtention = Currency(fQuanity * fPrice );
	return fExtention = fQuanity * fPrice ;
}

double CGridMaterials::CalculateRowRetail(long lRow)
{
	double fRetail = 0 ;
	double fQuanity = 0 ;
	double fExtention = 0 ;

	CString strStatus = QuickGetText(STATUS, lRow) ;
	CSetMatStatus setStatus(&g_dbFlooring) ;
	setStatus.m_strFilter.Format("Status = '%s'", strStatus) ;
	setStatus.Open() ;
	if (!setStatus.IsEOF())
	{
		if (setStatus.m_Billable)
		{
			fQuanity = QuickGetNumber(MAT_SIZE, lRow) ;
			fRetail = QuickGetNumber(RETAIL, lRow) ;
		}
	}

	return fExtention = Currency(fQuanity * fRetail) ;
}


void CGridMaterials::GetMaterialType(long lRow)
{
	CString strOption = QuickGetText(TYPE, lRow) ;
	GetMaterialType(strOption) ;
}

void CGridMaterials::GetMaterialType(CString strOption)
{
	m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d' and [LaborDescription] = '%s'", m_lMaterialType, strOption ) ;
	m_setBasicLabor.Requery() ;
}

int CGridMaterials::DeleteRow(long lRow)
{	
	long lStatus = CGridPOBase::DeleteRow(lRow) ;
	::PostMessage((GetParent())->m_hWnd, wm_MATERIAL_UPDATE, 0, 0) ;
	return lStatus ;
}

void CGridMaterials::UpdateRecordSet(long lOrderID)
{
	long lRow ;
//	double fPrice = 0 ;

	CSetOrderMaterialsDetails setDetails(&g_dbFlooring) ;
	setDetails.Open() ;

	for (lRow = 0; lRow < this->GetNumberRows() ; lRow++)
	{
		GetMaterialType(lRow) ;
		CString strTemp ;
		this->QuickGetText(ID, lRow, &strTemp) ;
		if (strTemp == "")
		{
			setDetails.AddNew() ;
		}
		else
		{
			setDetails.m_strFilter.Format("[OrdeMateriallID] = '%s'", strTemp) ;
			setDetails.Requery() ;
			setDetails.Edit() ;
		}

		QuickGetText(STATUS, lRow, &strTemp) ;
		CSetMatStatus setStatus(&g_dbFlooring) ;
		setStatus.m_strFilter.Format("[Status] = '%s'", strTemp) ;
		setStatus.Open() ;
		setDetails.m_MaterialStatusID = setStatus.m_MatStatusID ;
		setStatus.Close() ;

		if (m_setBasicLabor.m_Has2Dimensions)
		{
			double dLength ;
			double dWidth ;

			dLength = QuickGetNumber(LEN_INCHES, lRow) / 12.0;
			dLength += QuickGetNumber(LEN_FEET, lRow) ;

			dWidth = QuickGetNumber(WIDTH_INCHES, lRow) / 12.0;
			dWidth += QuickGetNumber(WIDTH_FEET, lRow) ;

			setDetails.m_Length = dLength ;
			setDetails.m_Width = dWidth ;
		}
		setDetails.m_MaterialID = m_setBasicLabor.m_BasicLaborID ;
		setDetails.m_OrderID = lOrderID ;

		QuickGetText(RETAIL, lRow, &setDetails.m_UnitRetail) ;
		QuickGetText(COST, lRow, &setDetails.m_UnitCost) ;
		QuickGetText(PRICE, lRow, &setDetails.m_UnitPrice) ;
//		setDetails.m_MerchandisPresent = QuickGetBool(PRESENT, lRow) ;
		QuickGetText(SO, lRow, &setDetails.m_SONumber) ;
		QuickGetText(STYLE, lRow, &setDetails.m_Style) ;
		QuickGetText(COLOR, lRow, &setDetails.m_Color) ;
		
		setDetails.m_Size = QuickGetNumber (MAT_SIZE, lRow) ;
		setDetails.Update() ;
	}
	DeleteRecordList(setDetails, "[OrdeMateriallID] = '%d'") ;
	setDetails.Close() ;
}

void CGridMaterials::SetOrderID(long lOrderID)
{
	m_lOrderID = lOrderID ;
	UpdateGrid() ;
}


void CGridMaterials::UpdateGrid()
{
	if (m_lOrderID != 0)
	{
		long lRow = 0 ;
//		double fPrice = 0 ;

		CSetOrderMaterialsDetails setDetails(&g_dbFlooring) ;
		setDetails.m_strFilter.Format("[OrderID] = '%d'", m_lOrderID) ;
		setDetails.Open() ;



		while (!setDetails.IsEOF())
		{
			this->AppendRow() ;
			CUGCell cell ;

//			GetMaterialType(lRow) ;
			CString strTemp ;
			SelectMaterial(setDetails.m_MaterialID) ;
			strTemp = m_setBasicLabor.m_LaborDescription ;
			strTemp.MakeUpper() ;
			QuickSetText(TYPE, lRow, strTemp) ;

			CSetMatStatus setStatus(&g_dbFlooring) ;
			setStatus.m_strFilter.Format("[MatStatusID] = '%d'", setDetails.m_MaterialStatusID) ;
			setStatus.Open() ;
			QuickSetText(STATUS, lRow, setStatus.m_Status) ;
			setStatus.Close() ;

			strTemp.Format("%d", setDetails.m_OrdeMateriallID) ;

			QuickSetText(ID, lRow, strTemp) ;

//			if (m_setBasicLabor.m_Has2Dimensions)
			{
				double dFeet ;
				double dInches ;

				dInches = setDetails.m_Length - long(setDetails.m_Length) ;
				dFeet = setDetails.m_Length - dInches ;

				QuickSetNumber(LEN_INCHES, lRow, dInches * 12) ;
				QuickSetNumber(LEN_FEET, lRow, dFeet) ;

				dInches = setDetails.m_Width - long(setDetails.m_Width) ;
				dFeet = setDetails.m_Width - dInches ;

				QuickSetNumber(WIDTH_INCHES, lRow, dInches * 12) ;
				QuickSetNumber(WIDTH_FEET, lRow, dFeet) ;
			}
//			m_setBasicLabor.m_BasicLaborID = setDetails.m_BasicLaborID ;
//			setDetails.m_OrderID = lOrderID ;

//			QuickSetBool(PRESENT, lRow, setDetails.m_MerchandisPresent == TRUE) ;
			QuickSetText(COST, lRow, setDetails.m_UnitCost) ;
			QuickSetText(PRICE, lRow, setDetails.m_UnitPrice) ;
			QuickSetText(RETAIL, lRow, setDetails.m_UnitRetail) ;
			QuickSetText(SO, lRow, setDetails.m_SONumber) ;
			QuickSetNumber(MAT_SIZE, lRow, setDetails.m_Size ) ;
			QuickSetText(STYLE, lRow, setDetails.m_Style) ;
			QuickSetText(COLOR, lRow, setDetails.m_Color) ;

			double fExtention = CalculateRowRetail(lRow);
			QuickSetNumber(EXTENTION, lRow, fExtention) ;

			lRow++ ;
			setDetails.MoveNext() ;
		}
		setDetails.Close() ;
		::PostMessage((GetParent())->m_hWnd, wm_MATERIAL_UPDATE, 0, 0) ;
	}	
}

void CGridMaterials::SelectMaterial(long lId)
{
	m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d' and [BasicLaborID] = '%d'", m_lMaterialType, lId ) ;
	m_setBasicLabor.Requery() ;
}

int CGridMaterials::AppendRow()
{
	int iReturn = CGridPOBase::AppendRow() ;

	long lRow = this->GetNumberRows() - 1;

	CUGCell cell ;

	GetColDefault(TYPE, &cell) ;
	SetCell(TYPE, lRow, &cell) ;
	QuickSetReadOnly(TYPE, lRow, false) ;

	GetColDefault(PRICE, &cell) ;
	SetCell(PRICE, lRow, &cell) ;

	GetColDefault(RETAIL, &cell) ;
	SetCell(RETAIL, lRow, &cell) ;

	GetColDefault(COST, &cell) ;
	SetCell(COST, lRow, &cell) ;

	GetColDefault(MAT_SIZE, &cell) ;
	SetCell(MAT_SIZE, lRow, &cell) ;

	if (!m_setBasicLabor.m_Has2Dimensions)
	{
		JoinCells(LEN_FEET, lRow, WIDTH_INCHES, lRow) ;
		QuickSetText(LEN_FEET, lRow, "N\\A") ;
		QuickSetAlignment(LEN_FEET, lRow, UG_ALIGNCENTER) ;
		
		QuickSetReadOnly(LEN_FEET, lRow, true) ;
		QuickSetReadOnly(MAT_SIZE, lRow, false) ;
	}
	else
	{
		QuickSetReadOnly(LEN_FEET, lRow, false) ;
		QuickSetReadOnly(LEN_INCHES, lRow, false) ;
		QuickSetReadOnly(WIDTH_FEET, lRow, false) ;
		QuickSetReadOnly(WIDTH_INCHES, lRow, false) ;
		QuickSetReadOnly(MAT_SIZE, lRow, true) ;

		UnJoinCells(LEN_FEET, lRow) ;
	}
	QuickSetReadOnly(STYLE, lRow, !m_setBasicLabor.m_HasStyle) ;
	QuickSetReadOnly(COLOR, lRow, !m_setBasicLabor.m_HasColor) ;
	QuickSetReadOnly(SO, lRow, !m_setBasicLabor.m_HasSONumber) ;
	GetCell(STATUS, lRow, &cell) ;
	if (m_setBasicLabor.m_IsPadding)
	{
		cell.SetReadOnly(true) ;
		cell.SetText("PRESENT") ;
//		cell.SetCellType(0) ;
	}
	else
	{
		cell.SetCellType( UGCT_DROPLIST);

		CString strChoices = "" ;
		CSetMatStatus setStatus(&g_dbFlooring) ;
		setStatus.Open() ;
		cell.SetText(setStatus.m_Status) ;

		while (!setStatus.IsEOF())
		{
			strChoices += setStatus.m_Status ;
			strChoices += "\n" ;
			setStatus.MoveNext() ;
		}
		cell.SetReadOnly(true) ;
		cell.SetLabelText(strChoices);
		setStatus.Close() ;
	}
	SetCell(STATUS, lRow, &cell) ;
	RedrawCell(STATUS, lRow) ;

	return iReturn ;

}

