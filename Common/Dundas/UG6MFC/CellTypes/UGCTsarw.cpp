/*************************************************************************
				Class Implementation : CUGSortArrowType
**************************************************************************
	Source file : UGCTsarw.cpp
	Copyright � Dundas Software Ltd. 1994 - 2002, All Rights Reserved
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTsarw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***************************************************
CUGSortArrowType - Constructor
	Initialize member variables
****************************************************/
CUGSortArrowType::CUGSortArrowType(){
	m_ArrowWidth = GetSystemMetrics(SM_CXVSCROLL);
}

/***************************************************
~CUGSortArrowType - Destructor
	Free all allocated resources
****************************************************/
CUGSortArrowType::~CUGSortArrowType(){

}

/***************************************************
GetName  - overloaded CUGCellType::GetName
	Returns a readable name for the cell type.
	Returned value is used to help end-users
	to see what cell type are available.

    **See CUGCellType::GetName for more details
	about this function

Params:
	<none>
Return:
	cell type name
****************************************************/
LPCTSTR CUGSortArrowType::GetName()
{
	return _T("Sort Arrow");
}

/***************************************************
GetUGID  - overloaded CUGCellType::GetUGID
	Returns a GUID for the cell type, this number
	is unique for each cell type and never changes.
	This number can be used to find the cell types
	added to this instance of the Ultimate Grid.

    **See CUGCellType::GetUGID for more details
	about this function

Params:
	<none>
Returns:
	UGID (which is actually a GUID)
****************************************************/
LPCUGID CUGSortArrowType::GetUGID()
{
	static const UGID ugid = 
	{ 0x45858895, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draw the cells text on the left hand side of the cell
	using the UGCellType::Draw text, and draw the sort
	arrow on the right hand side. The direction of the
	arrow depends on the cells extended type:
		UGCT_SORTARROWUP or UGCT_SORTARROWDOWN (default)
	
    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGSortArrowType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							 CUGCell *cell,int selected,int current){

	DrawBorder(dc,rect,rect,cell);

	// The printer and the monitor have different resolutions.
	// So we should adjust the size of the button.
	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif
	
	long cellTypeEx = 0;
	if(cell->IsPropertySet(UGCELL_CELLTYPEEX_SET))
		cellTypeEx = cell->GetCellTypeEx();

	DrawBackground( dc, rect, cell->GetBackColor());

	int oldleft = rect->left;
	rect->left = rect->right - (int) (m_ArrowWidth * fScale);

	int inc = m_ArrowWidth / 4;
	if(inc >= (rect->bottom - rect->top))
		inc = rect->bottom - rect->top - (int) fScale;
	int top = rect->top + (rect->bottom - rect->top) / 2 - inc;

	CPen* oldpen = NULL;

	if ( rect->left < oldleft )
	{
		rect->left = oldleft;
		rect->right = rect->left + m_ArrowWidth;
	}

	if(!dc->IsPrinting())	// Displaying
	{
		if(cellTypeEx&UGCT_SORTARROWUP){
			oldpen = dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
			dc->MoveTo(rect->left + inc, top + inc + inc);
			dc->LineTo(rect->right - inc, top + inc + inc);
			dc->LineTo(rect->left + inc + inc, top);
			dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
			dc->LineTo(rect->left + inc, top + inc + inc);
		}
		else{
			oldpen = dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
			dc->MoveTo(rect->right - inc, top);
			dc->LineTo(rect->left + inc, top);
			dc->LineTo(rect->left + inc + inc, top + inc + inc);
			dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
			dc->LineTo(rect->right - inc, top);
		}
	}
#ifdef UG_ENABLE_PRINTING
	else	// Printing
	{
		int nHeight = rect->bottom - rect->top;

		if(cellTypeEx&UGCT_SORTARROWUP){
			oldpen = dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
			dc->MoveTo(rect->right - (int) ((3 + 5) * fScale), rect->top + nHeight / 2 - (int)(4 * fScale));
			dc->LineTo(rect->right - (int) ((3 + 9) * fScale), rect->top + nHeight / 2 + (int)(4 * fScale));
			dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
			dc->LineTo(rect->right - (int) (4 * fScale), rect->top + nHeight / 2 + (int)(4 * fScale));
			dc->LineTo(rect->right - (int) ((3 + 5) * fScale), rect->top + nHeight / 2 - (int)(4 * fScale));
		}
		else{
			oldpen = dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
			dc->MoveTo(rect->right - (int) (4 * fScale), rect->top + nHeight / 2 - (int)(4 * fScale));
			dc->LineTo(rect->right - (int) ((3 + 9) * fScale), rect->top + nHeight / 2 - (int)(4 * fScale));
			dc->LineTo(rect->right - (int) ((3 + 5) * fScale), rect->top + nHeight / 2 + (int)(4 * fScale));
			dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
			dc->LineTo(rect->right - (int) (4 * fScale), rect->top + nHeight / 2 - (int)(4 * fScale));
		}
	}
#endif

	if ( oldpen != NULL )
		dc->SelectObject(oldpen);

	rect->right = rect->left;
	rect->left = oldleft;

	//draw the text in using the default drawing routine
	DrawText(dc,rect,0,col,row,cell,selected,current);
}

/****************************************************
GetBestSize
	Returns the best (nominal) size for a cell using
	this cell type, with the given cell properties.
Params:
	dc		- device context to use to calc the size on	
	size	- return the best size in this param
	cell	- pointer to a cell object to use for the calc.
Return:
	<none>
*****************************************************/
void CUGSortArrowType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	// call the default implementation
	CUGCellType::GetBestSize( dc, size, cell );
	// increase the size of the text by the width of the arrow
	size->cx += m_ArrowWidth;
}