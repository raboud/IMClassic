/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridPONotes.cpp: implementation of the CGridPONotes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridPONotes.h"
#include "DlgPONoteEntry.h"

#include "SetPONotesWithName.h"
#include "SetNoteTypes.h"
#include "SetOrders.h"
#include "SetMaterialType.h"

#include "DlgWebService.h"
#include "DlgSendNote.h"
#include "Logger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridPONotes::CGridPONotes()
{
	HighlightCurrentRow();
	m_iColumnToSizeTo = NOTES ;
	m_pperms = new CPermissions();
}

CGridPONotes::~CGridPONotes()
{
	delete m_pperms;
}

void CGridPONotes::SetOrderId(int iOrderId)
{
	m_iOrderId = iOrderId ;
	Update() ;
}


void CGridPONotes::OnSetup()
{
	CCFGrid::OnSetup() ;

	CUGCell cell;
	GetGridDefault(&cell) ;
	cell.SetAlignment(UG_ALIGNVCENTER) ;
	SetGridDefault(&cell) ;
	SetDoubleBufferMode(TRUE); 

	AddColumn("  ID  ",														 ID);
	AddColumn("     Date/Time     ",										 DATETIME);
	AddColumn("   Entered By   ",										     USER);
	AddColumn("Note                                                       ", NOTES);
	AddColumn("        Note Type        ", NOTETYPE);
	AddColumn("CANSENDTOEXPEDITOR",	CANSENDTOEXPEDITOR);
	AddColumn("Sent", SENTVIAXML);
	AddColumn("    Date/Time Sent    ", DATETIMESENT);

	InitColumnHeadings();

	GetColDefault(SENTVIAXML, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(SENTVIAXML, &cell) ;
	
	HideColumn(CANSENDTOEXPEDITOR);

	EnableMenu(TRUE) ;
}

int CGridPONotes::OnMenuStart(int /* col */, long row, int section)
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
			bool bGrayed = (m_pperms->HasPermission("CanSendNoteToStore") == FALSE);
			if (CanSendToExpeditor(row))
			{
				if (SentToExpeditor(row))
				{
					AddMenuItem(1003, "Resend to Store", bGrayed);
				}
				else
				{
					AddMenuItem(1004, "Send to Store", bGrayed);
				}
			}
		}
	}
	return TRUE ;
}

void CGridPONotes::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	CDlgPONoteEntry dlg;
	dlg.SetNoteId(int(QuickGetNumber(ID, row))) ;
	dlg.SetEditingFlag(true);
	if (dlg.DoModal() == IDOK)
	{
		Update() ;
	}
}

void CGridPONotes::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		if (item == 1000)  // add note
		{
			CDlgPONoteEntry dlg;
			dlg.SetOrderID(m_iOrderId) ;
			if (dlg.DoModal() == IDOK)
			{
				Logger::Instance().LogMessage("Added new note.");
				if (dlg.m_bSendToExpeditor)
				{
					Logger::Instance().LogMessage("Before Calling SendToExpeditor()");
					
					//SendToExpeditor(dlg.GetNoteID(), dlg.m_bCopyToSASM, dlg.m_bCopyToExpeditorEmail);
					QueueNoteForExpeditor(dlg.GetNoteID(), dlg.m_bCopyToSASM, dlg.m_bCopyToExpeditorEmail);					
					
					Logger::Instance().LogMessage("After Calling SendToExpeditor()");
				}
				Logger::Instance().LogMessage("Calling Update() after adding new note.");
				Update() ;
				Logger::Instance().LogMessage("After calling Update()");
			}
		}
		else if (item == 1001)  // edit note
		{
			CDlgPONoteEntry dlg;
			dlg.SetNoteId(int(QuickGetNumber(ID, row))) ;
			dlg.SetEditingFlag(true);
			if (dlg.DoModal() == IDOK)
			{
				Update() ;
			}
		}
		else if (item == 1002)  // print for faxing
		{
			CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
			pApp->PrintPONote(int(QuickGetNumber(ID, row)));
		}
		else if ( (item == 1003) || (item == 1004))  // resend to store , send to store
		{
			// resend to expeditor
			CString strNoteType = "";
			bool bCopyToSASM = false;
			bool bCopyToExpeditorEmail = false;
			
			CDlgSendNote dlgSendNote;
				
			dlgSendNote.ShowCopyToSASM(true);
			dlgSendNote.ShowCopyToExpeditorEmail(true);

			if (dlgSendNote.DoModal() == IDOK)
			{				
				bCopyToSASM = (dlgSendNote.m_CopyNoteToSASM == TRUE);
				bCopyToExpeditorEmail = (dlgSendNote.m_CopyNoteToExpeditorEmail == TRUE);
				Logger::Instance().LogMessage("Before calling SendToExpeditor() - send / resend existing note to store.");					
				
				//SendToExpeditor(int(QuickGetNumber(ID, row)), bCopyToSASM, bCopyToExpeditorEmail);
				QueueNoteForExpeditor(int(QuickGetNumber(ID, row)), bCopyToSASM, bCopyToExpeditorEmail);
				
				Logger::Instance().LogMessage("After calling SendToExpeditor() - send / resend existing note to store.");					
			}
		}
	}
}

void CGridPONotes::QueueNoteForExpeditor(int NoteID, bool CopyToSASM, bool CopyToExpeditorEmail)
{
	bool QueuedOK = CGlobals::QueueNoteForExpeditor(NoteID, CopyToSASM, CopyToExpeditorEmail);
	if (QueuedOK)
	{
		MessageBox("The note was added to outgoing messages list.\r\nIt will be sent by the SPN service as soon as possible.", "Information");
	}
	else
	{
		MessageBox("The note WAS NOT added to the outgoing messages list.  Please contact your support team for assistance.", "Error!");
	}
}

void CGridPONotes::Update()
{
	Logger::Instance().LogMessage("Entering GridPONotes::Update()");
	EnableUpdate(FALSE);

	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetPONotesWithName set(&g_dbFlooring) ;
	set.m_strFilter.Format("OrderId = '%d'", m_iOrderId) ;
	set.m_strSort = "[DateTimeEntered]" ;
	set.Open() ;

	CSetNoteTypes setNoteTypes(&g_dbFlooring);
	setNoteTypes.m_strFilter = "ID = 0";
	setNoteTypes.Open();

	int iRow = 0;
	SetNumberRows (0, false) ;

	while (!set.IsEOF())
	{
		CString strOut ;

		AppendRow() ;
		iRow = GetNumberRows() - 1 ;

		setNoteTypes.m_strFilter.Format("ID = '%d'", set.m_NoteTypeID);
		setNoteTypes.Requery();

		strOut.Format("%d", set.m_ID) ;
		QuickSetText(ID, iRow, strOut) ;
		QuickSetReadOnly(ID, iRow, true) ;

		QuickSetText(DATETIME, iRow, set.m_DateTimeEntered.Format("%Y/%m/%d %I:%M %p")) ;
		QuickSetReadOnly(DATETIME, iRow, true) ;

		QuickSetCellTypeEx(NOTES, iRow,UGCT_NORMALMULTILINE);
		QuickSetAlignment(NOTES, iRow, UG_ALIGNVCENTER | UG_ALIGNLEFT) ;
		if (set.m_Scheduled)
		{
			strOut.Format("SCHEDULED FOR: %s %s", set.m_ScheduledDate.Format( "%Y/%m/%d" ), (set.m_ScheduledAM) ? "AM" : "PM");
			QuickSetText(NOTES, iRow, strOut) ;
		}
		else if (set.m_Unscheduled)
		{
			QuickSetText(NOTES, iRow, "UNSCHEDULED") ;
		}
		else
		{
			if (set.m_NoteText.GetLength() > 500)
			{
				strOut = set.m_NoteText.Left(500);
				int iLastSpaceIndex = strOut.ReverseFind(' ');
				if ((iLastSpaceIndex > 0) && (iLastSpaceIndex < 500))
				{
					strOut = strOut.Left(iLastSpaceIndex);
				}
				strOut += "...";
				QuickSetText(NOTES, iRow, strOut) ;
			}
			else
			{
				QuickSetText(NOTES, iRow, set.m_NoteText.Trim()) ;
			}
		}
		QuickSetReadOnly(NOTES, iRow, true) ;
		CString strName = set.m_EnteredByName ;
		strName.MakeUpper() ;
		QuickSetText(USER, iRow, strName.Trim()) ;
		QuickSetReadOnly(USER, iRow, true) ;

		QuickSetText(NOTETYPE, iRow, setNoteTypes.m_NoteTypeDescription);

		QuickSetBool(CANSENDTOEXPEDITOR, iRow, ((setNoteTypes.m_CanSendToExpeditor == TRUE)));
		QuickSetBool(SENTVIAXML, iRow, set.m_SentViaXML == TRUE);
		if (set.m_DateTimeSent.GetStatus() == COleDateTime::valid)
		{
			QuickSetText(DATETIMESENT, iRow, set.m_DateTimeSent.Format("%Y/%m/%d %I:%M:%S %p"));
		}
		else
		{
			QuickSetText(DATETIMESENT, iRow, "");
		}

		set.MoveNext() ;

		iRow++ ;
	}
	set.Close() ;

	UpdateRowHeights() ;
	
	EnableUpdate(TRUE);
	RedrawAll();
	Logger::Instance().LogMessage("Leaving GridPONotes::Update()");
}

bool CGridPONotes::CanSendToExpeditor(long row)
{
	return QuickGetBool(CANSENDTOEXPEDITOR, row);
}

bool CGridPONotes::SentToExpeditor(long row)
{
	return QuickGetBool(SENTVIAXML, row);
}

//void CGridPONotes::SendToExpeditor(int iNoteID, bool CopyToSASM, bool CopyToExpeditorEmail)
//{
//	Logger::Instance().LogMessage("Entering GridPONotes::SendToExpeditor()");	
//
//	try
//	{
//		CDlgWebService dlg;
//		bool bInstall = false;
//		if (CGlobals::IsInstall(m_iOrderId, bInstall))
//		{
//			Logger::Instance().LogMessage("Calling dlg.SPNAddExpeditorNote() in GridPONotes::SendToExpeditor()");
//			dlg.SPNAddExpeditorNote(iNoteID, CopyToSASM, CopyToExpeditorEmail);
//			Logger::Instance().LogMessage("After calling dlg.SPNAddExpeditorNote() in GridPONotes::SendToExpeditor()");
//		}
//
//		Logger::Instance().LogMessage("Calling Update() in GridPONotes::SendToExpeditor()");
//		Update();
//	}
//	catch (CMemoryException* e)
//	{
//		Logger::Instance().LogMessage("MemoryException thrown in GridPONotes::SendToExpeditor()");
//	}
//	catch (CFileException* e)
//	{
//		Logger::Instance().LogMessage("FileException thrown in GridPONotes::SendToExpeditor()");
//	}
//	catch (CException* e)
//	{
//		Logger::Instance().LogMessage("Exception thrown in GridPONotes::SendToExpeditor()");
//	}	
//
//	Logger::Instance().LogMessage("Leaving GridPONotes::SendToExpeditor()");
//}

bool CGridPONotes::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridPONotes::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}