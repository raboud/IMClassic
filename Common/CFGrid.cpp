/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CFGrid.cpp: implementation of the CCFGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CFGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCFGrid::CCFGrid()
{
	m_iColumnToSizeTo = - 1 ;
	m_bInitHeadingsCalled = false;
	m_pen = NULL ;
}

CCFGrid::~CCFGrid()
{
	if (NULL != m_pen)
	{
		delete m_pen ;
	}
}

BOOL CCFGrid::OnCanSizeCol(int /* col */)
{
	return FALSE ;
}

void CCFGrid::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		// The user has selected the 'Cut' option
		if (item == 1000)
		{
			AppendRow() ;
		}
		else if (item == 2000)
		{
			DeleteRow(row) ;
			this->RedrawAll() ;
		}
	}
}

int CCFGrid::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		//** Add the Menu Items
		AddMenuItem(1000,"New");
		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			AddMenuItem(2000, "Delete") ;
		}
	}
	return TRUE ;
}

void CCFGrid::OnCharDown(UINT *vcKey, BOOL /* processed */)
{
	StartEdit(*vcKey) ;


	if (*vcKey == VK_TAB)
	{
		int iCurCol = this->GetCurrentCol() ;
		int iNextCol = iCurCol ;
		long iCurRow = this->GetCurrentRow() ;
		long iNextRow = iCurRow ;
		CUGCell cell ;
		GetColDefault(iCurCol, &cell) ;

//		if ((cell.GetCellType() != 0))
//		if (m_editCell.GetReadOnly() || (cell.GetCellType() != 0))
		{
			if(GetKeyState(VK_SHIFT)<0)
			{
				iNextCol-- ;
			}
			else
			{
				iNextCol++ ;
			}
			if (OnEditContinue(iCurCol, iCurRow, &iNextCol, &iNextRow))
			{
//				GotoCell(0, 0) ;
//				RedrawCell(0,0) ;
				GotoCell(iNextCol, iNextRow) ;
//				RedrawCell(iNextCol, iNextRow) ;
			}
		}
	}
}

void CCFGrid::OnKeyDown(UINT *vcKey, BOOL /* processed */)
{	
	if ((*vcKey == VK_INSERT) && (GetKeyState(VK_CONTROL)<0))
	{
		OnMenuCommand(0,0,UG_GRID,1000) ;
	}
}

int CCFGrid::OnEditStart(int /* col */, long /* row */, CWnd ** /* edit */)
{
	return FALSE ;
}

int CCFGrid::OnEditContinue(int oldcol, long oldrow, int *newcol, long *newrow)
{
	CUGCell cell ;
	BOOL bReturn = TRUE ;

	while (true)
	{
		if (GetNumberCols() <= *newcol)
		{
			if ((GetNumberRows() - 1) <= *newrow)
			{
				GotoCell(oldcol, oldrow) ;
				CWnd* pParent = this->GetParent();
				CWnd* pNext = pParent->GetNextDlgTabItem(this, false) ;
				pNext->SetFocus() ;
				bReturn = FALSE ;
	//					*newrow = 0 ;
			}
			else
			{
				(*newrow)++ ;
			}
			*newcol = 0 ;
	//				break ;
		}
		GetCell(*newcol, *newrow, &cell) ;
		CUGCell cellColDef ;
		GetColDefault(*newcol, &cellColDef) ;
		if ((cell.GetReadOnly() == FALSE))
//		if ((cell.GetReadOnly() == FALSE) || (cell.GetCellType() != 0) || (cellColDef.GetCellType() != 0))
		{
			break ;
		}
		else
		{
			BOOL bOrigin ;
			int iColJoin ;
			long iRowJoin ;

			if (cell.GetJoinInfo(&bOrigin, & iColJoin, &iRowJoin) == UG_SUCCESS)
			{
				(*newcol) += iColJoin + 1 ;
			}
			else
			{
				(*newcol)++ ;
			}
			
		}
	}
	return bReturn ;
}

void CCFGrid::OnSetup()
{
	// verify we are working with an empty grid
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	InitDefaultFont();

	EnableCellOverLap(false) ;
	m_pen = new CPen(PS_SOLID, 1, RGB(0,0,0));
	SetCancelMode(FALSE) ;

	SetHighlightRow(TRUE);
	CUGCell cell;
	SetDoubleBufferMode(TRUE); 
}

int CCFGrid::DeleteRow(long lRow)
{
	CString strID = QuickGetText(-1, lRow) ;
	if (strID != "")
	{
		m_listRecord.AddHead(QuickGetText(-1, lRow)) ;
	}
	return CUGCtrl::DeleteRow(lRow) ;
}

int CCFGrid::AppendRow()
{
	return CUGCtrl::AppendRow();
}

double CCFGrid::QuickGetNumber(int iCol, long lRow)
{
	CUGCell cell ;

	GetCell(iCol, lRow, &cell) ;
	return cell.GetNumber() ;
}

bool CCFGrid::QuickGetBool(int iCol, long lRow)
{
	CUGCell cell ;

	GetCell(iCol, lRow, &cell) ;
	return (cell.GetBool() == TRUE ) ;
}

void CCFGrid::QuickSetBool(int iCol, long lRow, bool bState)
{
	CUGCell cell ;

	GetCell(iCol, lRow, &cell) ;
	cell.SetBool(bState) ;
	SetCell(iCol, lRow, &cell) ;

}

void CCFGrid::QuickGetBool(int iCol, long lRow, bool* pbValue)
{
	*pbValue = QuickGetBool(iCol, lRow) ;
}

void CCFGrid::QuickGetNumber(int iCol, long lRow, double* pfValue)
{
	*pfValue = QuickGetNumber(iCol, lRow) ;
}

void CCFGrid::QuickSetReadOnly(int iCol, long lRow, bool bValue)
{
	CUGCell cell ;

	GetCell(iCol, lRow, &cell) ;
	cell.SetReadOnly(bValue) ;
	SetCell(iCol, lRow, &cell) ;
}

void CCFGrid::QuickGetReadOnly(int iCol, long lRow, bool *pbValue)
{
	CUGCell cell ;

	GetCell(iCol, lRow, &cell) ;
	*pbValue = cell.GetReadOnly() == TRUE ;
}

BOOL CCFGrid::OnCanMove(int /* oldcol */, long /* oldrow */, int newcol, long newrow)
{
	bool bValue ;
	QuickGetReadOnly(newcol, newrow, &bValue) ;
	return !bValue ;
}

void CCFGrid::QuickSetNumberDecimals(int iCol, long lRow, int iNumberOfDecimals)
{
	CUGCell cell ;

	GetCell(iCol, lRow, &cell) ;
	cell.SetNumberDecimals(iNumberOfDecimals) ;
	SetCell(iCol, lRow, &cell) ;
}

void CCFGrid::DeleteRecordList(CRecordset& cSet, CString strFilter, CString strTag)
{
	POSITION pos = m_listRecord.GetHeadPosition() ;

	CString strID = "";
	if ( strTag.GetLength() > 0 )
	{
		while (pos)
		{
			strID = m_listRecord.GetNext(pos);
			if (strID.Left(strTag.GetLength()) == strTag)
			{
				cSet.m_strFilter.Format(strFilter, strID.Right(strID.GetLength() - strTag.GetLength())) ;
				if (cSet.IsOpen())
				{
					cSet.Requery() ;
				}
				else
				{
					cSet.Open() ;
				}
				if (!cSet.IsEOF())
				{
					cSet.Delete() ;
				}
			}
		} 
	}
	else
	{
		while (pos)
		{
			strID = m_listRecord.GetNext(pos);
			cSet.m_strFilter.Format(strFilter, strID) ;
			if (cSet.IsOpen())
			{
				cSet.Requery() ;
			}
			else
			{
				cSet.Open() ;
			}
			if (!cSet.IsEOF())
			{
				cSet.Delete() ;
			}
		} 
	}
}

void CCFGrid::HighlightCurrentRow(bool bHighlight)
{
	// if true, this changes the color of the entire row to show that it is selected
	// NOTE: It appears that the constants as defined by Dundas help are not really defined,
	// thus we are using the actual numbers...
	if (bHighlight)
	{
		// 3 corresponds to both a focus rect and color highlight
		SetCurrentCellMode(3);	
	}
	else
	{
		// 1 corresponds to just a focus rect
		SetCurrentCellMode(1);
	}
}

int CCFGrid::AddColumn(CString strHeading, int iColumnID, int iRowID)
{
	ASSERT(strHeading.GetLength() > 0);
	ASSERT(iColumnID > -2);
	
	SuGridHeading suGridHeading;
	suGridHeading.strText = strHeading;
	suGridHeading.iCol = iColumnID;
	suGridHeading.iRow = iRowID;
	suGridHeading.bVisible = true;
	suGridHeading.bSortAscending = FALSE;

	int iFoundIndex = -1;
	if (ColumnDefined(iColumnID, iRowID, iFoundIndex))
	{
		// just update it
		m_asuHeadings[iFoundIndex] = suGridHeading;	
	}
	else
	{
		m_asuHeadings.Add(suGridHeading);
	}

	return iColumnID;
}

int CCFGrid::AddColumn(CString strHeading, int iColumnID)
{
	// defaults to row -1
	return AddColumn(strHeading, iColumnID, -1);
}

int CCFGrid::AddColumn(CString strHeading)
{
	// defaults to next highest columnID and row -1
	int iNewColumnID = GetMaxColumnID() + 1;
	return AddColumn(strHeading, iNewColumnID, -1);
}

void CCFGrid::ClearColumns()
{
	m_asuHeadings.RemoveAll();
}

void CCFGrid::DisplayColumn(int iColumnID, bool bShow)
{
	ASSERT( m_bInitHeadingsCalled == true );
	int iNumHeadings = m_asuHeadings.GetCount();
	for (int iIndex = 0; iIndex < iNumHeadings; iIndex++)
	{
		if (m_asuHeadings[iIndex].iCol == iColumnID)
		{
			// if visible and column is being hidden, save the col. width for later restore
			if (m_asuHeadings[iIndex].bVisible && !bShow)
			{
				m_asuHeadings[iIndex].iDefWidth = CUGCtrl::GetColWidth(m_asuHeadings[iIndex].iCol);
				CUGCtrl::SetColWidth(m_asuHeadings[iIndex].iCol, 0);
			}
			else if (!m_asuHeadings[iIndex].bVisible && bShow)
			{
				CUGCtrl::SetColWidth(m_asuHeadings[iIndex].iCol, m_asuHeadings[iIndex].iDefWidth);
			}
			
			m_asuHeadings[iIndex].bVisible = bShow;
		}
	}
}

void CCFGrid::ShowColumn(int iColumnID)
{
	DisplayColumn(iColumnID, true);
}

void CCFGrid::HideColumn(int iColumnID)
{
	DisplayColumn(iColumnID, false);
}

int CCFGrid::GetColumnID(CString strHeading)
{
	int iColumnID = -1;

	for (int iIndex = 0; iIndex < m_asuHeadings.GetCount(); iIndex++)
	{
		SuGridHeading suHeading = m_asuHeadings[iIndex];
		if ( strHeading.MakeUpper().Trim() == suHeading.strText.MakeUpper().Trim() )
		{
			iColumnID = iIndex;
			break;
		}
	}

	return iColumnID;
}

void CCFGrid::InitColumnHeadings()
{
	m_bInitHeadingsCalled = true;

	int iNumColumnHeadings = m_asuHeadings.GetCount();
	ASSERT(iNumColumnHeadings > 0);

	// we want to see how many actual columns there are as some of the headings might be at
	// -2 and others might be the same column, but at -1 for the heading row.
	int iNumRegularColumns = 0;
	SortColumnContainer();
	int iPrevColID = -1000;   // this holds the value of the column ID on the previous iteration through the loop
	                          // used so we know if we are looking at the same column as before but a different header row

	for (int iIndex = 0; iIndex < iNumColumnHeadings; iIndex++)
	{
		if ( (m_asuHeadings[iIndex].iCol != -1) && (m_asuHeadings[iIndex].iCol != iPrevColID) )
		{
			iNumRegularColumns++;
			iPrevColID = m_asuHeadings[iIndex].iCol;
		}
	}

	// iNumRegularColumns now has a count of the actual columns in the grid.
	SetNumberCols(iNumRegularColumns);

	for (int iIndex = 0; iIndex < iNumColumnHeadings; iIndex++)
	{
		CUGCtrl::QuickSetText(m_asuHeadings[iIndex].iCol, m_asuHeadings[iIndex].iRow, m_asuHeadings[iIndex].strText);
	}

	// adjust the column widths based on the text in the headings...
	BestFit(-1, iNumRegularColumns-1, 0, UG_BESTFIT_TOPHEADINGS) ;
	
	// set the default column widths after the best fit call
	for (int iIndex = 0; iIndex < iNumColumnHeadings; iIndex++)
	{
		m_asuHeadings[iIndex].iDefWidth = CUGCtrl::GetColWidth(m_asuHeadings[iIndex].iCol);
	}

}

int CCFGrid::GetMaxColumnID()
{
	int iNumColumns = m_asuHeadings.GetCount();
	ASSERT(iNumColumns > 0);
	int iMaxColumnID = m_asuHeadings[0].iCol;
	if (iNumColumns > 0)
	{
		iMaxColumnID = m_asuHeadings[0].iCol;

		for (int iIndex = 0; iIndex < iNumColumns; iIndex++)
		{
			if (m_asuHeadings[iIndex].iCol > iMaxColumnID)
			{
				iMaxColumnID = m_asuHeadings[iIndex].iCol;
			}
		}
	}

	return iMaxColumnID;
}

void CCFGrid::OnCB_LClicked(int updn, RECT *rect, POINT *point, BOOL processed) 
{
	UNREFERENCED_PARAMETER(processed);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(rect);
	if (!updn)
	{
		for (int iIndex = 0; iIndex < m_asuHeadings.GetCount(); iIndex++)
		{
			if (m_asuHeadings[iIndex].iCol == -1)
			{
                m_asuHeadings[iIndex].bSortAscending = m_asuHeadings[iIndex].bSortAscending ^ 1;
				int iSortFlag[] = {UG_SORT_DESCENDING, UG_SORT_ASCENDING} ;
				SortBy(-1, iSortFlag[m_asuHeadings[iIndex].bSortAscending] ); 
				UpdateRowHeights() ;
				RedrawAll();
				break;
			}
		}
	}
}

void CCFGrid::OnTH_LClicked(int col, long /* row */, int updn,RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	if (!updn)
	{
		for (int iIndex = 0; iIndex < m_asuHeadings.GetCount(); iIndex++)
		{
			if (m_asuHeadings[iIndex].iCol == col)
			{
                m_asuHeadings[iIndex].bSortAscending = m_asuHeadings[iIndex].bSortAscending ^ 1;
				int iSortFlag[] = {UG_SORT_DESCENDING, UG_SORT_ASCENDING} ;
				SortBy(col, iSortFlag[m_asuHeadings[iIndex].bSortAscending] ); 
				UpdateRowHeights() ;
				RedrawAll();
				break;
			}
		}
	}
}

bool CCFGrid::ColumnDefined(int iColumnID, int iRowID, int& iFoundIndex)
{
	bool bFound = false;
	for (int iIndex = 0; iIndex < m_asuHeadings.GetCount(); iIndex++)
	{
		if ((m_asuHeadings[iIndex].iCol == iColumnID) && (m_asuHeadings[iIndex].iRow == iRowID))
		{
			iFoundIndex = iIndex;
			bFound = true;
			break;
		}
	}

	return bFound;
}

void CCFGrid::SortColumnContainer()
{
	if (m_asuHeadings.GetCount() > 2)
	{
		qsort(m_asuHeadings.GetData(), m_asuHeadings.GetSize(), sizeof(SuGridHeading), Compare);
	}
}

int CCFGrid::Compare(LPCVOID a, LPCVOID b)
{
	SuGridHeading * p1 = (SuGridHeading*) a;
	SuGridHeading * p2 = (SuGridHeading*) b;

	if ( p1->iCol < p2->iCol )
	{
		return -1;
	}
	else if (p1->iCol == p2->iCol)
	{
		return 0;
	}

	return 1;
}

void CCFGrid::InitDefaultFont()
{
	// Get the index value of the font.
	CDC * pDC;

    pDC = GetDC();
	int nLogPixelsY = GetDeviceCaps( pDC->m_hDC, LOGPIXELSY);
    int nHeight = MulDiv( 10, nLogPixelsY, 72 );

    ReleaseDC( pDC );

	m_fontID = AddFont("Lucida Console", nHeight, FW_NORMAL);
	//m_fontID = AddFont("MS Sans Serif", 12, FW_NORMAL);

	//Set the Grid's default font
	SetDefFont(m_fontID);

	CUGCell cell;
	GetHeadingDefault( &cell );
	cell.SetFont( GetFont( m_fontID ) );
	SetHeadingDefault( &cell );	
}

int CCFGrid::GetNumberOfRegularColumns()
{
	int iNumColumnHeadings = m_asuHeadings.GetCount();

	int iNumRegularColumns = 0;

	int iLastColID = m_asuHeadings[0].iCol;

	for (int iIndex = 0; iIndex < iNumColumnHeadings; iIndex++)
	{
		if ( (m_asuHeadings[iIndex].iCol != -1) && (m_asuHeadings[iIndex].iCol != iLastColID) )
		{
			iNumRegularColumns++;
			iLastColID = m_asuHeadings[iIndex].iCol;
		}
	}

	return iNumRegularColumns;
}

void CCFGrid::UpdateGrid()
{
}

void CCFGrid::ClearAllDataRows()
{
	while(GetNumberRows())
	{
		CUGCtrl::DeleteRow(0) ;
	}
}
void CCFGrid::Reset()
{
	// clears all rows
	// NOTE: this does not mark rows for deletion in the RecordList
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}
}

int CCFGrid::OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags)
{
	return CUGCtrl::OnSortEvaluate( cell1, cell2, flags );
}

void CCFGrid::SetRowBackColor(long lRow, COLORREF color)
{
	int iStart = GetFirstColumnIndex();
	int iEnd = GetLastColumnIndex();

	// to call this function properly, the derived grid class must override
	// the GetFirstColumnIndex() and GetLastColumnIndex() functions
	// so that the following assertion is true.  By default, the base
	// class defines these functions so the assertion fails.
	ASSERT(iStart < iEnd);

	for (int iCol = iStart; iCol < iEnd; iCol++)
	{
		QuickSetBackColor(iCol, lRow, color) ;
	}
}

void CCFGrid::SetRowTextColor(long lRow, COLORREF color)
{
	int iStart = GetFirstColumnIndex();
	int iEnd = GetLastColumnIndex();

	// to call this function properly, the derived grid class must override
	// the GetFirstColumnIndex() and GetLastColumnIndex() functions
	// so that the following assertion is true.  By default, the base
	// class defines these functions so the assertion fails.
	ASSERT(iStart < iEnd);

	for (int iCol = iStart; iCol < iEnd; iCol++)
	{
		QuickSetTextColor(iCol, lRow, color) ;
	}
}

void CCFGrid::SetRowHTextColor(long lRow, COLORREF color)
{
	int iStart = GetFirstColumnIndex();
	int iEnd = GetLastColumnIndex();

	// to call this function properly, the derived grid class must override
	// the GetFirstColumnIndex() and GetLastColumnIndex() functions
	// so that the following assertion is true.  By default, the base
	// class defines these functions so the assertion fails.
	ASSERT(iStart < iEnd);

	for (int iCol = iStart; iCol < iEnd; iCol++)
	{
		QuickSetHTextColor(iCol, lRow, color) ;
	}
}

void CCFGrid::SetRowColor(long lRow, COLORREF color, EnColorMode enMode)
{
	if (enMode == EnColorMode_BACK)
	{
		SetRowBackColor(lRow, color) ;
	}
	else
	{
		SetRowTextColor(lRow, color) ;
	}
}

int CCFGrid::GetFirstColumnIndex()
{
	return 0 ;
}

int CCFGrid::GetLastColumnIndex()
{
	return GetNumberCols() - 1;
}


//void CCFGrid::BestFit(int startCol,int endCol,int CalcRange,int flag)
//{
//	if(startCol < (m_GI->m_numberSideHdgCols *-1))
//		return UG_ERROR;
//	if(endCol >= m_GI->m_numberCols)
//		return 2;
//	if(startCol > endCol)
//		return 3;
//
//	CUGCell cell;
//	CUGCellType * cellType;
//	CSize size;
//	int count		= 0;
//	int x;
//	long y;
//	int numCols		= endCol-startCol+1;
//	int *bestWidth	= new int[numCols];
//	CDC * dc		= GetDC();
//
//	int startRow = 0;
//	if(flag&UG_BESTFIT_TOPHEADINGS)
//		startRow -= m_GI->m_numberTopHdgRows;
//	
//	//set the best width to 3 pixels (3 for min width)
//	for(x= 0;x < numCols;x++)
//	{
//		if (m_asuHeadings[x]
//		bestWidth[x] = 3;
//	}
//
//	for(y = startRow;y <m_GI->m_numberRows;y++)
//	{
//		if(y == m_GI->m_numLockRows)
//			y = m_GI->m_topRow;
//
//		for(x= startCol;x <= endCol;x++)
//		{	
//			GetCellIndirect(x,y,&cell);
//			
//			if(cell.IsPropertySet(UGCELL_JOIN_SET) == FALSE)
//			{	// reset the size object to reflect cell's width and height
//				size.cx = GetColWidth ( x );
//				size.cy = GetRowHeight( y );
//				// call GetBestSize for cell type set to this cell
//				cellType = GetCellType(cell.GetCellType());
//				cellType->GetBestSize(dc,&size,&cell);
//				if(size.cx > bestWidth[x-startCol])
//					bestWidth[x-startCol] = size.cx;
//			}
//		}
//
//		count++;
//		if(count == CalcRange)
//			break;
//	}
//
//	//update the col widths - restrict to width of grid window
//	int bw;
//	RECT rect;
//	m_CUGGrid->GetClientRect(&rect);		// window may not be created yet
//
//	int maxw, sideHeadingWidth = 0;
//
//	if(rect.right == 0)
//		maxw = 300;
//	else
//		maxw = rect.right - m_GI->m_vScrollWidth;
//
//	for(x= 0;x < numCols;x++)
//	{
//		bw = bestWidth[x];
//		if(bw > maxw)
//			bw = maxw;
//		else
//			bw+=2;	// just a tweak to give edit ctrl room if
//					// AutoSize is turned off 
//		if ( startCol + x < 0 )
//		{
//			sideHeadingWidth += bw;
//		}
//
//		// send notifications to cell types.  In order to provide acceptable performance
//		// this notification will only be sent to the visible rows.
//		for(int nIndex = GetTopRow(); nIndex < GetBottomRow(); nIndex++)
//		{
//			CUGCellType* pCellType = GetCellType( startCol + x, nIndex );
//
//			if ( pCellType != NULL )
//				pCellType->OnChangedCellWidth( startCol + x, nIndex, &bw );
//		}
//
//		OnColSized( startCol + x, &bw );
//		SetColWidth( startCol + x, bw );
//	}
//	if ( sideHeadingWidth > 0 )
//	{	// adjust width of the side heading
//		SetSH_Width( sideHeadingWidth );
//	}
//
//	delete[] bestWidth;
//	ReleaseDC(dc);		
//	AdjustComponentSizes();
//
//	return UG_SUCCESS;
//}



void CCFGrid::UpdateRowHeights()
{
	long lNumRows = GetNumberRows();

	if ((lNumRows >= 0) && (m_iColumnToSizeTo != -1))
	{
		CDC* pDC = GetDC() ;
		CRect rect(0, 0, GetColWidth(m_iColumnToSizeTo) - 2, 10) ;
		pDC->DPtoLP(&rect) ;

		int iWidth = rect.Width() ;

		CUGCell cell ;
		GetCell(m_iColumnToSizeTo, 0, &cell) ;

		CFont* pFont = cell.GetFont() ;

		if (pFont == NULL)
		{
			pFont = GetFont(m_fontID) ;
		}
		
		LOGFONT lf;
		pFont->GetLogFont(&lf);
		
		int iRowLeader = m_GI->m_defRowHeight - lf.lfHeight ;

		pDC->SelectObject(pFont);

		for (long lRow = 0; lRow < lNumRows; lRow++)
		{
			rect.right = rect.left + iWidth  ;
			pDC->DrawText(QuickGetText(m_iColumnToSizeTo, lRow), &rect, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
			pDC->LPtoDP(&rect) ;

			SetRowHeight(lRow, rect.Height() + iRowLeader) ;
		}
	}
	AdjustComponentSizes() ;
}

bool CCFGrid::IsDirty() 
{
	bool bDirty = false;

	long lNumRows = GetNumberRows();
	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		bDirty =bDirty || IsRowDirty(lRow);
		if (bDirty)
		{
			// no need to keep going
			break;
		}
	}

    return bDirty;
}