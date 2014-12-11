/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridMatStatus.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "GridMatStatus.h"
#include "SetMatStatus.h"
#include "SetMaterialOrderDetailed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridMatStatus

CGridMatStatus::CGridMatStatus()
  : m_setMaterial(&g_dbFlooring)
{
	m_bHas2Dim = false ;
	m_bHasSo = false ;
	m_bHasStyle = false ;
	m_bHasColor = false ;
	m_setMaterial.Open() ;
}

CGridMatStatus::~CGridMatStatus()
{
	m_setMaterial.Close() ;
}


BEGIN_MESSAGE_MAP(CGridMatStatus, CCFGrid)
	//{{AFX_MSG_MAP(CGridMatStatus)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGridMatStatus message handlers

void CGridMatStatus::OnSetup()
{
	CCFGrid::OnSetup();

	int iIndex ;

	struct
	{
		int		iRow ;
		char*	pString ;
		int		iCol ;
	} asuHeading1[] = {	
						{-2, "STYLE         ",									STYLE},
						{-2, "COLOR         ",									COLOR},
						{-2, "SO NUMBER ",										SO},
						{-1, "FEET",											LEN_FEET},
						{-1, "INCHES",											LEN_INCHES},
						{-1, "FEET",											WIDTH_FEET},
						{-1, "INCHES",											WIDTH_INCHES},
						{-2, "    SIZE    ",									MAT_SIZE},
						{-2, "        STATUS         ",							STATUS},
						{-2, "LENGTH",											LEN_FEET},
						{-2, "WIDTH",											WIDTH_FEET}} ;
	const int iCOL_COUNT =  LAST;


	CUGCell cell;

	SetNumberCols (iCOL_COUNT, false) ;

	//Add the Column Heading to the grid
	for (iIndex = 0; iIndex < sizeof(asuHeading1) / sizeof(asuHeading1[0]); iIndex++)
	{
		QuickSetText(asuHeading1[iIndex].iCol, asuHeading1[iIndex].iRow, asuHeading1[iIndex].pString);
	}


	SetTH_NumberRows(2);
	SetTH_Height(24);
	// Set the heights of the individual rows 
	SetTH_RowHeight(-1,12);
	SetTH_RowHeight(-2,12);

	JoinCells(LEN_FEET, -2, LEN_INCHES, -2) ;
	JoinCells(WIDTH_FEET, -2, WIDTH_INCHES, -2) ;

	JoinCells(STYLE, -2, STYLE, -1) ;
	JoinCells(COLOR, -2, COLOR, -1) ;
	JoinCells(STATUS, -2, STATUS, -1) ;
	JoinCells(SO, -2, SO, -1) ;
	JoinCells(MAT_SIZE, -2, MAT_SIZE, -1) ;

	BestFit(0, iCOL_COUNT - 1, 0, UG_BESTFIT_TOPHEADINGS) ;

	EnableMenu(TRUE) ;

	GetColDefault(LEN_FEET, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(LEN_FEET, &cell) ;
	SetColDefault(LEN_INCHES, &cell) ;
	SetColDefault(WIDTH_FEET, &cell) ;
	SetColDefault(WIDTH_INCHES, &cell) ;
	SetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(2) ;
	SetColDefault(MAT_SIZE, &cell) ;
	cell.SetReadOnly(TRUE) ;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;
}

void CGridMatStatus::SetMaterialType(long lMaterialType)
{
	m_lMaterialType = lMaterialType ;
	m_setMaterial.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
	m_setMaterial.m_strSort = "[MaterialDescription]" ;
	m_setMaterial.Requery() ;

	m_bHas2Dim = false ;
	m_bHasSo = false ;
	m_bHasStyle = false ;
	m_bHasColor = false ;
	CUGCell cell;

	RedrawAll() ;
}

int CGridMatStatus::OnCellTypeNotify(long /* ID */, int /* col */, long /* row */, long /* msg */, long /* param */)
{
	RedrawAll() ;
	return TRUE ;
}

int CGridMatStatus::OnEditStart(int col, long row, CWnd ** /* edit */)
{
	int bEdit = FALSE ;

	if ((row >= 0) && (col >= 0) )
	{

		CUGCell cell ;
		GetCell(col, row, &cell) ;

//		bEdit = !cell.GetReadOnly() ;

		if (bEdit)
		{
			switch (col)
			{
				case SO:
					break ;

				case LEN_INCHES: 
				case WIDTH_INCHES:
				case LEN_FEET: 
				case WIDTH_FEET: 
				case MAT_SIZE:
					break ;
			}
		}
	}

	return bEdit ;

}

void CGridMatStatus::OnKillFocus(CWnd* /* pOldWnd */)
{
	RedrawAll() ;
}


BOOL CGridMatStatus::OnCanMove(int /* oldcol */, long /* oldrow */, int newcol, long /* newrow */)
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
	}
	return bOk ;
}

int CGridMatStatus::DeleteRow(long lRow)
{	
	long lStatus = CCFGrid::DeleteRow(lRow) ;
	return lStatus ;
}

void CGridMatStatus::UpdateRecordSet(long /* lPoID */)
{
}

void CGridMatStatus::SetPoId(long /* lPoId */)
{
//	m_lPoId = lPoId ;
	UpdateGrid() ;
}


void CGridMatStatus::UpdateGrid()
{
/*	if (m_lPoId != 0)
	{
		long lRow = 0 ;
		double fPrice = 0 ;

		CSetMaterialOrderDetailed setDetails(&g_dbFlooring) ;
		setDetails.m_strFilter.Format("[SONumber] = '%s'", m_strSoNumber) ;
		setDetails.Open() ;



		while (!setDetails.IsEOF())
		{
			this->AppendRow() ;
			CUGCell cell ;

//			GetMaterialType(lRow) ;
			CString strTemp ;
			SelectMaterial(setDetails.m_MaterialID) ;
			strTemp = setDetails.m_MaterialDescription ;
			strTemp.MakeUpper() ;
			QuickSetText(TYPE, lRow, strTemp) ;
			QuickSetText(STATUS, lRow, setDetails.m_Status) ;

			strTemp.Format("%d", setDetails.m_OrdeMateriallID) ;

			QuickSetText(ID, lRow, strTemp) ;

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
			QuickSetText(COST, lRow, setDetails.m_UnitCost) ;
			QuickSetText(PRICE, lRow, setDetails.m_UnitPrice) ;
			QuickSetText(RETAIL, lRow, setDetails.m_UnitRetail) ;
			QuickSetText(SO, lRow, setDetails.m_SONumber) ;
			QuickSetNumber(MAT_SIZE, lRow, setDetails.m_Size ) ;
			QuickSetText(STYLE, lRow, setDetails.m_Style) ;
			QuickSetText(COLOR, lRow, setDetails.m_Color) ;

			lRow++ ;
			setDetails.MoveNext() ;
		}
		setDetails.Close() ;
	}	
*/}

void CGridMatStatus::SelectMaterial(long lId)
{
	m_setMaterial.m_strFilter.Format("[MaterialTypeID] = '%d' and [MaterialID] = '%d'", m_lMaterialType, lId ) ;
	m_setMaterial.Requery() ;
}

int CGridMatStatus::AppendRow()
{
	int iReturn = CCFGrid::AppendRow() ;

	long lRow = this->GetNumberRows() - 1;

	CUGCell cell ;

	GetColDefault(MAT_SIZE, &cell) ;
	SetCell(MAT_SIZE, lRow, &cell) ;

	if (!m_setMaterial.m_Has2Dimensions)
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
	QuickSetReadOnly(STYLE, lRow, !m_setMaterial.m_HasStyle) ;
	QuickSetReadOnly(COLOR, lRow, !m_setMaterial.m_HasColor) ;
	QuickSetReadOnly(SO, lRow, !m_setMaterial.m_HasSONumber) ;
	GetCell(STATUS, lRow, &cell) ;
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
	SetCell(STATUS, lRow, &cell) ;
	RedrawCell(STATUS, lRow) ;

	return iReturn ;

}
