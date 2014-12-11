/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridCalled.cpp: implementation of the CGridCalled class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridCalled.h"
#include "DlgPONoteEntry.h"

#include "SetCallWithName.h"

#include "ReportDialog.h"
//#include "ReportDialogWF.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCalled::CGridCalled()
{
	HighlightCurrentRow();
	m_iColumnToSizeTo = COMMENT ;
}

CGridCalled::~CGridCalled()
{

}

void CGridCalled::SetOrderId(int iOrderId)
{
	m_iOrderId = iOrderId ;
	Update() ;
}


void CGridCalled::OnSetup()
{
	CCFGrid::OnSetup() ;

	CUGCell cell;
	GetGridDefault(&cell) ;
	cell.SetAlignment(UG_ALIGNVCENTER) ;
	SetGridDefault(&cell) ;
	SetDoubleBufferMode(TRUE); 

	AddColumn("  ID  ",														ID);
	AddColumn("   Date   ",													DATE);
	AddColumn("   Time   ",													TIME);
	AddColumn("   Entered By   ",													USER);
	AddColumn("Comment                                                ",	COMMENT);

	InitColumnHeadings();

	EnableMenu(TRUE) ;
}

int CGridCalled::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		AddMenuItem(1000, "Add") ;
		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			AddMenuItem(1001, "Edit") ;
			AddMenuItem(1002, "Print for Faxing") ;
		}
	}
	return TRUE ;
}

void CGridCalled::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	CDlgPONoteEntry dlg;
	dlg.SetNoteId(int(QuickGetNumber(ID, row))) ;
	dlg.SetEditingFlag(true);
	if (dlg.DoModal() == IDOK)
	{
		Update() ;
	}
}

void CGridCalled::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		if (item == 1000)
		{
			CDlgPONoteEntry dlg;
			dlg.SetOrderID(m_iOrderId) ;
			if (dlg.DoModal() == IDOK)
			{
				Update() ;
			}
		}
		if (item == 1001)
		{
			CDlgPONoteEntry dlg;
			dlg.SetNoteId(int(QuickGetNumber(ID, row))) ;
			dlg.SetEditingFlag(true);
			if (dlg.DoModal() == IDOK)
			{
				Update() ;
			}
		}
		if (item == 1002)
		{
			CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
			pApp->PrintPONote(int(QuickGetNumber(ID, row)));

			/*CReportDialogWF dlg;
			dlg.ReportName = "PONote";
			dlg.WindowTitle = "PO Note Report";
			dlg.PrintOnly = true;
			CString strID;
			strID.Format("%d", int(QuickGetNumber(ID, row)));
			dlg.AddParameter("NoteID", strID);
			dlg.DoModal();*/

			//CReportDialog dlg;
			//dlg.SetReportFilename("PONote.rpt");

			//VARIANT vtValue;
			//VariantInit(&vtValue);
			//
			//vtValue.vt = VT_I4;

			//vtValue.intVal = int(QuickGetNumber(ID, row)) ;
			//dlg.AddParameter("NoteID", vtValue);
			//if (dlg.InitializeReport())
			//{
			//	dlg.PrintReport();
			//}
		}
	}
}

void CGridCalled::Update()
{
	EnableUpdate(FALSE);

	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetCallWithName set(&g_dbFlooring) ;
	set.m_strFilter.Format("OrderId = '%d'", m_iOrderId) ;
	set.m_strSort = "[Time]" ;
	set.Open() ;

	int iRow = 0;
	SetNumberRows (0, false) ;

	while (!set.IsEOF())
	{
		CString strOut ;

		AppendRow() ;
		iRow = GetNumberRows() - 1 ;

		strOut.Format("%d", set.m_Id) ;
		QuickSetText(ID, iRow, strOut) ;
		QuickSetReadOnly(ID, iRow, true) ;

		QuickSetText(DATE, iRow, set.m_Time.Format("%Y/%m/%d")) ;
		QuickSetReadOnly(DATE, iRow, true) ;

		QuickSetText(TIME, iRow, set.m_Time.Format("%I:%M %p")) ;
		QuickSetReadOnly(TIME, iRow, true) ;

		QuickSetCellTypeEx(COMMENT, iRow,UGCT_NORMALMULTILINE);
		QuickSetAlignment(COMMENT, iRow, UG_ALIGNVCENTER | UG_ALIGNLEFT) ;
		if (set.m_Schedule)
		{
			QuickSetText(COMMENT, iRow, "SCHEDULED") ;
		}
		else if (set.m_Unscheduled)
		{
			QuickSetText(COMMENT, iRow, "UNSCHEDULED") ;
		}
		else
		{
			QuickSetText(COMMENT, iRow, set.m_Comments.Trim()) ;
		}
		QuickSetReadOnly(COMMENT, iRow, true) ;
		CString strName = set.m_name ;
		strName.MakeUpper() ;
		QuickSetText(USER, iRow, strName.Trim()) ;
		QuickSetReadOnly(USER, iRow, true) ;

		set.MoveNext() ;

		iRow++ ;
	}
	set.Close() ;

	UpdateRowHeights() ;
	
	EnableUpdate(TRUE);
	RedrawAll();
}

bool CGridCalled::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridCalled::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}