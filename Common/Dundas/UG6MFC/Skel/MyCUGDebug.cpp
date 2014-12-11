/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

/*////////////////////////////////////////////////////////////////////////////
This is the MyCug CUGCtrl derived class with the 
addition of TRACE statements to allow the various
notification sequences to be seen in the output 
window.  The OnMouseMove and OnGetCell notification
TRACE statements are commented out so as to reduce 
the clutter!  
/*////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MyCUG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
	TRACE("MyCug: Constructor called.\n");
}

MyCug::~MyCug()
{
	TRACE("MyCug: Destructor called.\n");
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void MyCug::OnSetup()
{
	TRACE("MyCug: OnSetup called.\n");
}

/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void MyCug::OnSheetSetup(int sheetNumber)
{
	TRACE("MyCug: OnSheetSetup called for sheet %d.\n", sheetNumber);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanMove
//		Sent when current cell is changed
//	Params:
//		oldcol, oldrow - 
//		newcol, newrow - cell that is gaining focus
//	Return:
//		TRUE - to allow the move
//		FALSE - to prevent new cell from gaining focus
int MyCug::OnCanMove(int oldcol,long oldrow,int newcol,long newrow)
{
	TRACE("MyCug: OnCanMove called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld.\n",
					oldcol,	// the cell that is loosing focus
					oldrow,
					newcol,	// the cell that is gaining focus
					newrow);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanViewMove
//		Is called when current grid view is about to be scrolled
//	Params:
//		oldcol, oldrow - coordinates of orriginal top-left cell
//		newcol, newrow - coordinates of top-left cell that is gaining the focus
//	Return:
//		TRUE - to allow for the scroll
//		FALSE - to prevent the view from scrolling
int MyCug::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	TRACE("MyCug: OnCanViewMove called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld.\n",
					oldcol,	// the cell that is loosing focus
					oldrow,
					newcol,	// the cell that is gaining focus
					newrow);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitBottom
//		This notification allows for dynamic row loading, it will be called
//		when the grid drawing function has hit the last row.  It allows the grid
//		to ask the datasource/developer if there are additional rows to be displayed.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//		rowsfound	- number of rows actually found, usually equal to rowspast or zero.
//	Return:
//		<none>
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	// used by the datasources
	/*if ( rowsfound > 0 )
	{
		SetNumberRows( numrows + rowsfound, FALSE );
	}*/
	TRACE("MyCug: OnHitBottom called with numrows = %d, rowspast = %ld, rowsfound = %ld.\n",
				numrows,	// current number of rows in the grid
				rowspast,
				rowsfound);
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitTop
//		Is called when the user has scrolled all the way to the top of the grid.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//	Return:
//		<none>
void MyCug::OnHitTop(long numrows,long rowspast)
{
	TRACE("MyCug: OnHitTop called with numrows = %d, rowspast = %ld\n",
				numrows, 
				rowspast);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeCol
//		Sent when the user is about to size a given column
//	Params:
//		col - identifies column number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeCol(int col)
{
	TRACE("MyCug: OnCanSizeCol called for col = %d.\n", 
				col);	// column that is being sized
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSizing
//		Sent when the user is sizing a column
//	Params:
//		col - column currently sizing
//		width - current new column width
//	Return:
//		<none>
void MyCug::OnColSizing(int col,int *width)
{
	TRACE("MyCug: OnColSizing called for col = %d, width = %d.\n", 
				col,	// column that is being sized
				*width);// current new width
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSized
//		This is sent when the user finished sizing the 
//		given column.
//	Params:
//		col - column sized
//		width - new column width
//	Return:
//		<none>
void MyCug::OnColSized(int col,int *width)
{
	TRACE("MyCug: OnColSized called for col = %d, width = %d.\n", 
				col,	// column that is being sized
				*width);// new width
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeRow
//		Sent when the user is about to start sizing of a row
//	Params:
//		row - identifies row number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeRow(long row)
{
	TRACE("MyCug: OnCanSizeRow called for row = %ld.\n", 
				row);	// row that is being sized
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSizing
//		Sent durring user sizing of a row, can provide feed back on current height
//	Params:
//		row - row sizing
//		width - current new row height
//	Return:
//		<none>
void MyCug::OnRowSizing(long row,int *height)
{
	TRACE("MyCug: OnRowSizing called for row = %ld, height = %d.\n", 
				row,		// row that is being sized
				*height);	// current new row height
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSized
//		This is sent when the user is finished sizing hte
//		given row.
//	Params:
//		row - row sized
//		width - new row height
//	Return:
//		<none>
void MyCug::OnRowSized(long row,int *height)
{
	TRACE("MyCug: OnRowSized called for row = %ld, height = %d.\n", 
				row,		// row that is being sized
				*height);	// current new row height
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeSideHdg
//		Sent when the user is about to start sizing of the side heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeSideHdg()
{
	TRACE("MyCug: OnCanSizeSideHdg called.\n");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSizing
//		Sent while the heading is being sized
//	Params:
//		width - current new width of the side heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int MyCug::OnSideHdgSizing(int *width)
{
	TRACE("MyCug: OnSideHdgSizing called, width = %d.\n",
				*width );	// current new width
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSized
//		Sent when the user has completed the sizing of the side heading
//	Params:
//		width - new width
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int MyCug::OnSideHdgSized(int *width)
{
	TRACE("MyCug: OnSideHdgSized called, width = %d.\n",
				*width );	// new width
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeTopHdg
//		Sent when the user is about to start sizing of the top heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeTopHdg()
{
	TRACE("MyCug: OnCanSizeTopHdg called.\n");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSizing
//		Sent while the top heading is being sized
//	Params:
//		height - current new height of the top heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int MyCug::OnTopHdgSizing(int *height)
{
	TRACE("MyCug: OnTopHdgSizing called, height.\n",
				*height );	// current new height
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSized
//		Sent when the user has completed the sizing of the top heading
//	Params:
//		height - new height
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int MyCug::OnTopHdgSized(int *height)
{
	TRACE("MyCug: OnTopHdgSized called, height.\n",
				*height );	// current new height
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColChange
//		Sent whenever the current column changes
//	Params:
//		oldcol - column that is loosing the focus
//		newcol - column that the user move into
//	Return:
//		<none>
void MyCug::OnColChange(int oldcol,int newcol)
{
	TRACE("MyCug: OnColChange called with oldcol = %d, newcol = %d\n", 
				oldcol,	// column that is loosing the focus
				newcol);// column that the user move into
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowChange
//		Sent whenever the current row changes
//	Params:
//		oldrow - row that is loosing the locus
//		newrow - row that user moved into
//	Return:
//		<none>
void MyCug::OnRowChange(long oldrow,long newrow)
{
	TRACE("MyCug: OnRowChange called with oldrow = %ld, newrow = %ld\n", 
				oldrow, // row that is loosing the locus
				newrow);// row that user moved into
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellChange
//		Sent whenever the current cell changes
//	Params:
//		oldcol, oldrow - coordinates of cell that is loosing the focus
//		newcol, newrow - coordinates of cell that is gaining the focus
//	Return:
//		<none>
void MyCug::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{
	TRACE("MyCug: OnCellChange called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld.\n",
				oldcol,	// cell that is loosing the focus
				oldrow, 
				newcol, // cell that is gaining the focus
				newrow);
}

/////////////////////////////////////////////////////////////////////////////
//	OnLeftColChange
//		Sent whenever the left visible column in the grid changes, indicating
//		that the view was scrolled horizontaly
//	Params:
//		oldcol - column that used to be on the left
//		newcol - new column that is going to be the first visible column from the left
//	Return:
//		<none>
void MyCug::OnLeftColChange(int oldcol,int newcol)
{
	TRACE("MyCug: OnLeftColChange called with oldcol = %d, newcol = %d.\n"
				oldcol,	// column that used to be the first visible left col
				newcol);// new left col
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopRowChange
//		Sent whenever the top visible row in the grid changes, indicating
//		that the view was scrolled vertically
//	Params:
//		oldrow - row that used to be on the top
//		newrow - new row that is going to be the first visible row from the top
//	Return:
//		<none>
void MyCug::OnTopRowChange(long oldrow,long newrow)
{
	TRACE("MyCug: OnTopRowChange called with oldrow = %ld, newrow = %ld.\n",
				oldrow,	// row that used to be on the top
				newrow);// new top row
}

/***************************************************
OnSelectionChanged
	The OnSelectionChanged notification is called by the multiselect
	class when a change occured in current selection (ie user clicks
	on a new cell, drags a mouse selecting range of cells, or uses
	CTRL/SHIFT - left click key combination to select cells.)
Params:
	startCol, startRow	- coordinates of the cell starting the selection block
	endCol, endRow		- coordinates of the cell ending the selection block
	blockNum			- block number representing this range, this will
						  always represent total number of selection blocks.
Return:
	<none>
****************************************************/
void MyCug::OnSelectionChanged(int startCol,long startRow,int endCol,long endRow,int blockNum)
{
	TRACE("MyCug::OnSelectionChanged called with startCol = %ld, startRow = %ld, endCol = %ld, endRow = %ld, blockNum = %ld.\n",
				startCol, startRow, endCol,	endRow, blockNum );
}

/////////////////////////////////////////////////////////////////////////////
//	OnLClicked
//		Sent whenever the user clicks the left mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	TRACE("MyCug: OnLClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				updn,		// is TRUE if mouse button is 'down' and FALSE if button is 'up'
				processed); // indicates if current event was processed by other control
							// in the grid.
}
		
/////////////////////////////////////////////////////////////////////////////
//	OnRClicked
//		Sent whenever the user clicks the right mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	TRACE("MyCug: OnRClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				updn,		// is TRUE if mouse button is 'down' and FALSE if button is 'up'
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnDClicked
//		Sent whenever the user double clicks the left mouse button within the grid
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnDClicked called with col = %d, row = %ld, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				processed); // indicates if current event was processed by other control
							// in the grid.
}	
			 
/////////////////////////////////////////////////////////////////////////////
//	OnMouseMove
//		Is sent to each cell that the mouse is over.
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		point		- represents the screen point where the mouse event was detected
//		nFlags		- 
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed)
{
/*	TRACE("MyCug: OnMouseMove called with col = %d, row = %ld, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				processed); // indicates if current event was processed by other control
							// in the grid.*/
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_LClicked
//		Sent whenever the user clicks the left mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnTH_LClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				updn,		// is TRUE if mouse button is 'down' and FALSE if button is 'up'
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_RClicked
//		Sent whenever the user clicks the right mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnTH_RClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				updn,		// is TRUE if mouse button is 'down' and FALSE if button is 'up'
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnTH_DClicked called with col = %d, row = %ld, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_LClicked
//		Sent whenever the user clicks the left mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnSH_LClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				updn,		// is TRUE if mouse button is 'down' and FALSE if button is 'up'
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_RClicked
//		Sent whenever the user clicks the right mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnSH_RClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				updn,		// is TRUE if mouse button is 'down' and FALSE if button is 'up'
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_DClicked
//		Sent whenever the user double clicks the left mouse button within the side heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnSH_DClicked called with col = %d, row = %ld, processed = %d\n",
				col,		// column
				row,		// and row coordinates that received mouse click event
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_LClicked
//		Sent whenever the user clicks the left mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnCB_LClicked called with processed = %d\n",
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_RClicked
//		Sent whenever the user clicks the right mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnCB_RClicked called with processed = %d\n",
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top corner button
//	Params:
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{
	TRACE("MyCug: OnCB_DClicked called with processed = %d\n",
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyDown
//		Sent whenever the user types when the grid has focus. The keystroke can be
//		modified here as well. (See WM_KEYDOWN for more information)
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed)
{
	TRACE("MyCug: OnKeyDown called with *vcKey = %d, processed = %d\n", 
				*vcKey,		// virtual key code of the key user has pressed
				processed); // indicates if current event was processed by other control
							// in the grid.
}

/////////////////////////////////////////////////////////////////////////////
//	OnCharDown
//		Sent whenever the user types when the grid has focus. The keystroke can be 
//		modified here as well. (See WM_CHAR for more information)
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnCharDown(UINT *vcKey,BOOL processed)
{
	TRACE("MyCug: OnCharDown called with *vcKey = %d, processed = %d\n", 
				*vcKey,		// virtual key code of the key user has pressed
				processed); // indicates if current event was processed by other control
							// in the grid.
}
	
/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
//		This message is sent everytime the grid needs to
//		draw a cell in the grid. At this point the cell
//		class has been filled with the information to be
//		used to draw the cell. The information can now be
//		changed before it is used for drawing
//
//	Warning:
//		This notification is called for each cell that needs to be painted
//		Placing complicated calculations here will slowdown the refresh speed.
//	Params:
//		col, row	- coordinates of cell currently drawing
//		cell		- pointer to the cell object that is being drawn
//	Return:
//		<none>
void MyCug::OnGetCell(int col,long row,CUGCell *cell)
{
/*	TRACE("MyCug: OnGetCell called with col = %d, row = %ld\n", 
				col,
				row);	// co-ordinates of currently drawing cell */
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetCell
//		This notification is sent everytime a cell is set, here you have a chance
//		to make final modification to the cell's content before it is set.
//	Params:
//		col, row	- coordinates of cell currently saving
//		cell		- pointer to the cell object that is being saved
//	Return:
//		<none>
void MyCug::OnSetCell(int col,long row,CUGCell *cell)
{
	TRACE("MyCug: OnSetCell called with col = %d, row = %ld\n", 
				col,
				row);	// co-ordinates cell that is being set to the datasource
}

/////////////////////////////////////////////////////////////////////////////
//	OnDataSourceNotify
//		This message is sent from a data source and this message
//		depends on the data source - check the information
//		on the data source(s) being used
//		- The ID of the Data source is also returned
//	Params:
//		ID		- datasource ID
//		msg		- message ID to identify current process
//		param	- additional iformation or object that might be needed
//	Return:
//		<none>
void MyCug::OnDataSourceNotify(int ID,long msg,long param)
{
	TRACE("MyCug: OnDataSourceNotify called with ID = %d, msg = %ld, param = %ld\n",
				ID,		// datasource ID
				msg,	// message ID to identify current process
				param);	// additional iformation or object that might be needed
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellTypeNotify
//		This notification is sent by the celltype and it is different from cell-type
//		to celltype and even from notification to notification.  It is usually used to
//		provide the developer with some feed back on the cell events and sometimes to
//		ask the developer if given event is to be accepted or not
//	Params:
//		ID			- celltype ID
//		col, row	- co-ordinates cell that is processing the message
//		msg			- message ID to identify current process
//		param		- additional iformation or object that might be needed
//	Return:
//		TRUE - to allow celltype event
//		FALSE - to disallow the celltype event
int MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	TRACE("MyCug: OnCellTypeNotify called with ID = %d, col = %d, row = %ld, msg = %ld, param = %ld\n",
				ID,		// datasource ID
				col,
				row,	// co-ordinates cell that is processing the message
				msg,	// message ID to identify current process
				param);	// additional iformation or object that might be needed
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditStart
//		This message is sent whenever the grid is ready to start editing a cell
//	Params:
//		col, row - location of the cell that edit was requested over
//		edit -	pointer to a pointer to the edit control, allows for swap of edit control
//				if edit control is swapped permanently (for the whole grid) is it better
//				to use 'SetNewEditClass' function.
//	Return:
//		TRUE - to allow the edit to start
//		FALSE - to prevent the edit from starting
int MyCug::OnEditStart(int col, long row,CWnd **edit)
{
	TRACE("MyCug: OnEditStart called with col = %d, row = %ld\n",
				col,
				row);	// co-ordinates cell that requested StartEdit
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditVerify
//		This notification is sent every time the user hits a key while in edit mode.
//		It is mostly used to create custom behavior of the edit contol, because it is
//		so eazy to allow or disallow keys hit.
//	Params:
//		col, row	- location of the edit cell
//		edit		-	pointer to the edit control
//		vcKey		- virtual key code of the pressed key
//	Return:
//		TRUE - to accept pressed key
//		FALSE - to do not accept the key
int MyCug::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey)
{
	TRACE("MyCug: OnEditVerify called with col = %d, row = %ld, vcKey = %d\n", 
				col, row,	// co-ordinates of the edit cell
				*vcKey );	// virtual key code of pressed key
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditFinish
//		This notification is sent when the edit is being finised
//	Params:
//		col, row	- coordinates of the edit cell
//		edit		- pointer to the edit control
//		string		- actual string that user typed in
//		cancelFlag	- indicates if the edit is being cancelled
//	Return:
//		TRUE - to allow the edit it proceede
//		FALSE - to force the user back to editing of that same cell
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	TRACE("MyCug: OnEditFinish called with col = %d, row = %ld, string = %s, cancelFlag = %d\n",
				col, row,	// co-ordinates of the edit cell
				string,		// edit string, represents what user typed in
				cancelFlag);// indicates if the edit is being cancelles
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditContinue
//		This notification is called when the user pressed 'tab' or 'enter' keys
//		Here you have a chance to modify the destination cell
//	Params:
//		oldcol, oldrow - edit cell that is loosing edit focus
//		newcol, newrow - cell that the edit is going into, by changing their
//							values you are able to change where to edit next
//	Return:
//		TRUE - allow the edit to continue
//		FALSE - to prevent the move, the edit will be stopped
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	TRACE("MyCug: OnEditContinue called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld\n",
		oldcol, oldrow, *newcol, *newrow );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		setcion - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void MyCug::OnMenuCommand(int col,long row,int section,int item)
{
	TRACE("MyCug: OnMenuCommand called with col = %d, row = %ld, section = %d, item = %d\n",
		col, row, section, item);
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuStart
//		Is called when the pop up menu is about to be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		setcion		- identify for which portion of the gird the menu is for.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		TRUE - to allow menu to show
//		FALSE - to prevent the menu from poping up
int MyCug::OnMenuStart(int col,long row,int section)
{
	TRACE("MyCug: OnMenuStart called with col = %d, row = %ld, section = %d\n",
		col, row, section);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetContextHelpID 
//		this notification is called as result of context help bing activated
//		over the UG area
//	Params:
//		col, row	- coordinates of cell which received the message
//		section		- grid section which received this message
//	Return:
//		Context help ID to be shown in the help.
DWORD MyCug::OnGetContextHelpID( int col, long row, int section )
{
	TRACE("MyCug: OnGetContextHelpID called with col %d, row %d, section %d.\n", col, row, section);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHint
//		Is called whent the hint is about to be displayed on the main grid area,
//		here you have a chance to set the text that will be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		string		- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnHint(int col,long row,int section,CString *string)
{
	TRACE("MyCug: OnHint called with col = %d, row = %ld, section = %d, *string = %s\n",
		col, row, section, (LPCTSTR)*string); 
	string->Format( _T("Col:%d Row:%ld") ,col,row);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnVScrollHint
//		Is called whent the hint is about to be displayed on the vertical scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		row		- current top row
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnVScrollHint(long row,CString *string)
{
	TRACE("MyCug: OnVScrollHint called with row = %ld, *string = %s\n",
		row, (LPCTSTR)*string);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHScrollHint
//		Is called whent the hint is about to be displayed on the horizontal scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		col		- current left col
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnHScrollHint(int col,CString *string)
{
	TRACE("MyCug: OnHScrollHint called with col = %ld, *string = %s\n",
		col, (LPCTSTR)*string);
	return TRUE;
}

#ifdef __AFXOLE_H__
/////////////////////////////////////////////////////////////////////////////
//	OLE
//		following 3 functions are to be used with drag and drop functionality
/////////////////////////////////////////////////////////////////////////////
//	OnDragEnter
//	Params:
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragEnter(COleDataObject* pDataObject)
{
	TRACE("MyCug: OnDragEnter called.\n");
	return DROPEFFECT_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragOver
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragOver(COleDataObject* pDataObject,int col,long row)
{
	TRACE("MyCug: OnDragOver called with col = %d, row = %ld.\n",
		col, row);
	return DROPEFFECT_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragDrop
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragDrop(COleDataObject* pDataObject,int col,long row)
{
	TRACE("MyCug: OnDragDrop called with col = %d, row = %ld.\n",
		col, row);
	return DROPEFFECT_NONE;
}
#endif

/////////////////////////////////////////////////////////////////////////////
//	OnScreenDCSetup
//		Is called when each of the components are painted.
//	Params:
//		dc		- pointer to the current CDC object
//		section	- section of the grid painted.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		<none>
void MyCug::OnScreenDCSetup(CDC *dc,int section)
{
	TRACE("MyCug: OnScreenDCSetup called with section = %d\n", section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSortEvaluate
//		Sent as a result of the 'SortBy' call, this is called for each cell
//		comparison and allows for customization of the sorting routines.
//		We provide following code as example of what could be done here,
//		you migh have to modify it to give your application customized sorting.
//	Params:
//		cell1, cell2	- pointers to cells that are compared
//		flags			- identifies sort direction
//	Return:
//		value less than zero to identify that the cell1 comes before cell2
//		value equal to zero to identify that the cell1 and cell2 are equal
//		value greater than zero to identify that the cell1 comes after cell2
int MyCug::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	TRACE("MyCug: OnSortEvaluate called.\n");
	// if one of the cells is NULL, do not compare its text
	if ( cell1 == NULL && cell2 == NULL )
		return 0;
	else if ( cell1 == NULL )
		return 1;
	else if ( cell2 == NULL )
		return -1;

	if(flags&UG_SORT_DESCENDING)
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

	// initialize variables for numeric check
	double num1, num2;
	// compare the cells, with respect to the cell's datatype
	switch(cell1->GetDataType())
	{
		case UGCELLDATA_STRING:
			if(NULL == cell1->GetText() && NULL == cell2->GetText())
				return 0;
			if(NULL == cell1->GetText())
				return 1;
			if(NULL == cell2->GetText())
				return -1;
			return _tcscmp(cell1->GetText(),cell2->GetText());	
		case UGCELLDATA_NUMBER:
		case UGCELLDATA_BOOL:
		case UGCELLDATA_CURRENCY:
			num1 = cell1->GetNumber();
			num2 = cell2->GetNumber();
			if(num1 < num2)
				return -1;
			if(num1 > num2)
				return 1;
			return 0;
		default:
			// if datatype is not recognized, compare cell's text
			if(NULL == cell1->GetText())
				return 1;
			if(NULL == cell2->GetText())
				return -1;
			return _tcscmp(cell1->GetText(),cell2->GetText());	
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void MyCug::OnTabSelected(int ID)
{
	TRACE("MyCug: OnTabSelected called with ID = %d\n", ID);
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are baing arranged.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>
void MyCug::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
		RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs)
{
	TRACE("MyCug: OnAdjustComponentSizes called.\n");
} 

/////////////////////////////////////////////////////////////////////////////
//	OnDrawFocusRect
//		Called when the focus rect needs to be painted.
//	Params:
//		dc		- pointer to the current CDC object
//		rect	- rect of the cell that requires the focus rect
//	Return:
//		<none>
void MyCug::OnDrawFocusRect(CDC *dc,RECT *rect)
{
	TRACE("MyCug: OnDrawFocusRect called.\n");
	//DrawExcelFocusRect(dc,rect);
	
	rect->bottom --;
	rect->right --;
	dc->DrawFocusRect(rect);
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetDefBackColor
//		Sent when the area behind the grid needs to be paindted.
//	Params:
//		section - Id of the grid section that requested this color
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		RGB value representing the color of choice
COLORREF MyCug::OnGetDefBackColor(int section)
{
	TRACE("MyCug: OnGetDefBackColor called with section = %d\n", section);
	return RGB(255,255,255);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetFocus
//		Sent when the grid is gaining focus.
//	Params:
//		section - Id of the grid section gaining focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		<none>
//
//	Note:
//		The grid will loose focus when the edit is started, of drop list shown
void MyCug::OnSetFocus(int section)
{
	TRACE("MyCug: OnSetFocus called with section = %d\n", section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnKillFocus
//		Sent when the grid is loosing focus.
//	Params:
//		section - Id of the grid section loosing focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//		pNewWnd	- pointer to the windows gaining focus
//	Return:
//		<none>
void MyCug::OnKillFocus(int section, CWnd *pNewWnd)
{
	TRACE("MyCug: OnKillFocus called with section = %d\n", section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapStart
//		Called to inform the grid that the col swap was started on given col.
//	Params:
//		col - identifies the column
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL MyCug::OnColSwapStart(int col)
{
	TRACE("MyCug: OnColSwapStart called with col = %d\n", col);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanColSwap
//		Called when col swap is about to take place, here you can 'lock' certain
//		cols in place so that are not swapable.
//	Params:
//		fromCol - where the col orriginated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL MyCug::OnCanColSwap(int fromCol,int toCol)
{
	TRACE("MyCug: OnCanColSwap called with fromCol = %d, toCol = %d\n", fromCol, toCol);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapped
//		Called just after column-swap operation was completed.
//	Params:
//		fromCol - where the col orriginated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		<none>
void MyCug::OnColSwapped(int fromCol,int toCol)
{
	TRACE("MyCug: OnColSwapped called with fromCol = %d, toCol = %d\n", fromCol, toCol);
}

/////////////////////////////////////////////////////////////////////////////
//	OnTrackingWindowMoved
//		Called to notify the grid that the tracking window was moved
//	Params:
//		origRect	- from
//		newRect		- to location and size of the track window
//	Return:
//		<none>
void MyCug::OnTrackingWindowMoved(RECT *origRect,RECT *newRect)
{
	TRACE("MyCug: OnTrackingWindowMoved called.\n");
}
