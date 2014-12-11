/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridSOMerchandise.cpp: implementation of the CGridSelectSOMerchandise class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>

#include "Flooring.h"
#include "GridSelectSOMerchandise.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGridSelectSOMerchandise, CGridPOBase)
	//{{AFX_MSG_MAP(CGridSelectSOMerchandise)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CGridSelectSOMerchandise::CGridSelectSOMerchandise()
: m_setViewOrderSOMerchandiseDetails(&g_dbFlooring)
{
	m_bShowDeleted = false ;
}

CGridSelectSOMerchandise::~CGridSelectSOMerchandise()
{
	if (m_setViewOrderSOMerchandiseDetails.IsOpen())
	{
		m_setViewOrderSOMerchandiseDetails.Close() ;
	}
}

void CGridSelectSOMerchandise::OnSetup()
{
	CGridPOBase::OnSetup();

	CUGCell cell;

	AddColumn("  ID  ",										ID,						-1);
	AddColumn("SO NUMBER",									SO_NUMBER,				-1);
	AddColumn("SKU NUMBER",									SKU_NUMBER,				-1);
	AddColumn("DESCRIPTION                        ",		DESCRIPTION,			-1);
	AddColumn("QUANTITY",									QUANTITY,				-1);
	AddColumn("           STATUS            ",				MAT_STATUS,				-1);
	AddColumn("DELETED",									DELETED,				-1);

	SetTH_NumberRows(1);
	SetTH_Height(24);

	SetTH_RowHeight(-1,12);
	
	InitColumnHeadings();

	GetColDefault(ID, &cell);
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(SO_NUMBER, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(SO_NUMBER, &cell) ;

	GetColDefault(SKU_NUMBER, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(SKU_NUMBER, &cell) ;

	GetColDefault(DESCRIPTION, &cell);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	cell.SetReadOnly(TRUE);
	SetColDefault(DESCRIPTION, &cell) ;

	GetColDefault(QUANTITY, &cell);
	cell.SetNumberDecimals(2) ;
	cell.SetReadOnly(TRUE);
	cell.SetFormatClass(&m_formatNumeric) ;
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	SetColDefault(QUANTITY, &cell) ;

	GetColDefault(MAT_STATUS, &cell);
	cell.SetAlignment( UG_ALIGNLEFT|UG_ALIGNTOP );
	SetColDefault(MAT_STATUS, &cell) ;

	HideColumn(DELETED);

	// Create a mask edit to use with ultimate grid mask edit
	RECT rect = {0,0,0,0};
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);
	m_editUpper.Create(WS_VISIBLE | ES_UPPERCASE, rect, this, 125);

	UseHints(TRUE);
	SetMultiSelectMode(FALSE);
	SetHighlightRow(TRUE);
	SetCurrentCellMode(2);
	//Select(0, 1);
}

void CGridSelectSOMerchandise::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
}

int CGridSelectSOMerchandise::DeleteRow(long lRow)
{	
	CString strId = QuickGetText(ID, lRow) ;
	if (strId == "")
	{
		CGridPOBase::DeleteRow(lRow) ;
	}
	else
	{
		//long lStatus = CGridPOBase::DeleteRow(lRow) ;
		QuickSetBool(DELETED, lRow, true);
		QuickSetReadOnly(SO_NUMBER, lRow, true);
		QuickSetReadOnly(SKU_NUMBER, lRow, true);
		QuickSetReadOnly(DESCRIPTION, lRow, true);
		QuickSetReadOnly(QUANTITY, lRow, true);
		UpdateRowHeights() ;
		UpdateRowColor(lRow) ;
	}

	return TRUE ;
}

void CGridSelectSOMerchandise::SetAllowStatusUpdate(bool bAllowStatusUpdate) 
{
	m_bAllowStatusUpdate = bAllowStatusUpdate ;
}

void CGridSelectSOMerchandise::UpdateGrid()
{
	ClearAllDataRows();
	long lRow = 0 ;

	m_setViewOrderSOMerchandiseDetails.m_strFilter = m_strRecordSetFilter ;
	
	if (m_setViewOrderSOMerchandiseDetails.IsOpen())
	{
		m_setViewOrderSOMerchandiseDetails.Requery();
	}
	else
	{
		m_setViewOrderSOMerchandiseDetails.Open();
	}

	while (!m_setViewOrderSOMerchandiseDetails.IsEOF())
	{
		AppendRow() ;
		CUGCell cell ;

		CString strTemp ;
		strTemp.Format("%d", m_setViewOrderSOMerchandiseDetails.m_ID) ;
		QuickSetText(ID, lRow, strTemp) ;

		strTemp = m_setViewOrderSOMerchandiseDetails.m_SONumber ;
		strTemp.MakeUpper() ;
		QuickSetText(SO_NUMBER, lRow, strTemp) ;

		strTemp = m_setViewOrderSOMerchandiseDetails.m_SKUNumber ;
		strTemp.MakeUpper() ;
		if (strTemp.Find('-') == -1)
		{
			strTemp = strTemp.Right(6);
			strTemp.Insert(3, '-');
		}
		QuickSetText(SKU_NUMBER, lRow, strTemp) ;
		QuickSetText(DESCRIPTION, lRow, m_setViewOrderSOMerchandiseDetails.m_Description) ;
		GetCell(QUANTITY, lRow, &cell) ;
		cell.SetNumberDecimals(m_setViewOrderSOMerchandiseDetails.m_NumberOfDecimals) ;
		SetCell(QUANTITY, lRow, &cell) ;
		QuickSetNumber(QUANTITY, lRow, m_setViewOrderSOMerchandiseDetails.m_Quantity ) ;

		QuickSetText(MAT_STATUS, lRow, m_setViewOrderSOMerchandiseDetails.m_Status);
		QuickSetBool(DELETED, lRow, m_setViewOrderSOMerchandiseDetails.m_Deleted == 1);

		UpdateRowColor(lRow);

		lRow++ ;
		m_setViewOrderSOMerchandiseDetails.MoveNext() ;
	}
	UpdateRowHeights() ;
}

void CGridSelectSOMerchandise::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	//StartEdit();
	::PostMessage((this->GetParent())->m_hWnd, wm_MATERIAL_SELECT, 0, 0) ;
}

int CGridSelectSOMerchandise::AppendRow()
{
	int iReturn = CGridPOBase::AppendRow() ;

	long lRow = GetNumberRows() - 1;

	CUGCell cell ;

	GetColDefault(SO_NUMBER, &cell) ;
	cell.SetReadOnly(FALSE);
	SetCell(SO_NUMBER, lRow, &cell) ;
	
	GetColDefault(SKU_NUMBER, &cell) ;
	cell.SetReadOnly(FALSE);
	SetCell(SKU_NUMBER, lRow, &cell) ;

	GetColDefault(DESCRIPTION, &cell) ;
	cell.SetReadOnly(FALSE);
	SetCell(DESCRIPTION, lRow, &cell) ;

	GetColDefault(QUANTITY, &cell);
	cell.SetNumberDecimals(2);
	cell.SetReadOnly(FALSE);
	SetCell(QUANTITY, lRow, &cell);

	QuickSetBool(DELETED, lRow, false);

	UpdateRowColor(lRow);
	UpdateRowHeights() ;

	RedrawAll();

	return iReturn ;
}

void CGridSelectSOMerchandise::OnDrawFocusRect(CDC *dc, RECT *rect)
{
	CGridPOBase::OnDrawFocusRect(dc, rect);
}

void CGridSelectSOMerchandise::UpdateRowColor(long lRow)
{
	if (lRow >= 0)
	{
		//int iDetailID = (int) GetDetailID(lRow);
		
		if (QuickGetBool(DELETED, lRow))
		{
			if (m_bShowDeleted)
			{
				SetRowColor (lRow, CGlobals::COLOR_XML_DELETED_TEXT, CCFGrid::EnColorMode_TEXT) ;
				SetRowHTextColor(lRow, CGlobals::COLOR_XML_DELETED_TEXT);
				SetRowColor (lRow, CGlobals::COLOR_XML_DELETED_BACK, CCFGrid::EnColorMode_BACK) ;
			}
		}
		else
		{
			SetRowColor (lRow, CGlobals::COLOR_NORMAL_BACK, CCFGrid::EnColorMode_BACK) ;
		}
	}
}

int CGridSelectSOMerchandise::GetFirstColumnIndex()
{
	return ID + 1;
}

int CGridSelectSOMerchandise::GetLastColumnIndex()
{
	return LAST;
}

int CGridSelectSOMerchandise::OnHint(int col, long row, int section, CString *string, int *maxwidth)
{
	if ((section == UG_GRID) && (col == DESCRIPTION))
	{
		CString text;
		text = QuickGetText(col, row);
		string->Format(_T("%s"), text);
		*maxwidth = 500;
		return TRUE; 
	}
	
	return FALSE;
}

void CGridSelectSOMerchandise::ShowDeleted(bool bShowDeleted) 
{
	m_bShowDeleted = bShowDeleted ; 

	long lNumRows = GetNumberRows();
	CString strId;
	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		UpdateRowColor(lRow) ;
	}
	UpdateRowHeights() ;
	RedrawAll() ;
}

bool CGridSelectSOMerchandise::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}

bool CGridSelectSOMerchandise::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

void CGridSelectSOMerchandise::UpdateRowHeights()
{
	long lNumRows = GetNumberRows();
	int iColumnToSizeTo = DESCRIPTION ;

	if (lNumRows >= 0)
	{
		CDC* pDC = GetDC() ;

		CRect rect(0, 0, GetColWidth(iColumnToSizeTo) - 2, 10) ;
		pDC->DPtoLP(&rect) ;

		int iWidth = rect.Width() ;

		CUGCell cell ;
		GetCell(iColumnToSizeTo, 0, &cell) ;

		CFont* pFont = cell.GetFont() ;

		if (pFont == NULL)
		{
			pFont = GetFont(m_fontID) ;
		}
		
		LOGFONT lf;
		pFont->GetLogFont(&lf);
		
		int iRowLeader = (m_GI->m_defRowHeight - lf.lfHeight) / 2 ;

		pDC->SelectObject(pFont);

		for (long lRow = 0; lRow < lNumRows; lRow++)
		{
			//int iDetailID = (int) GetDetailID(lRow);

			if (!QuickGetBool(DELETED, lRow) || (m_bShowDeleted))
			{
				rect.right = rect.left + iWidth  ;
				pDC->DrawText(QuickGetText(iColumnToSizeTo, lRow), &rect, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
				pDC->LPtoDP(&rect) ;

				SetRowHeight(lRow, rect.Height() + iRowLeader) ;
			}
			else
			{
				SetRowHeight(lRow, 0) ;
			}
		}
	}
	AdjustComponentSizes() ;
}

long CGridSelectSOMerchandise::GetDetailID(const long lRow)
{
	long ID = -1;

	CString strID = QuickGetText(ID, lRow);
	strID.Replace("*", "") ;
	if (strID.GetLength() > 0)
	{
		ID = atol(strID);
	}

	return ID;
}

int CGridSelectSOMerchandise::RedrawAll()
{
	UpdateColors() ;
	UpdateRowHeights() ;
	return CGridPOBase::RedrawAll() ;
}

double CGridSelectSOMerchandise::GetSelectedID()
{
	double dID = -1;
	if (GetSelectedRows() == 1)
	{
        POSITION pos = m_listRows.GetHeadPosition();
		long lRow = m_listRows.GetNext(pos);
		QuickGetNumber(ID, lRow, &dID);
	}

	return dID;
}