/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridPayrollMessages.cpp: implementation of the CGridPayrollMessages class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Flooring.h"
#include "GridPayrollMessages.h"
#include "DlgPayrollMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridPayrollMessages::CGridPayrollMessages()
: m_setPayrollMessages(&g_dbFlooring)
{
	HighlightCurrentRow();

	m_setPayrollMessages.Open();
}

CGridPayrollMessages::~CGridPayrollMessages()
{
	m_setPayrollMessages.Close();
}

void CGridPayrollMessages::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn(" ID  ", ID);
	AddColumn("Message                                                   ", MESSAGE);
	AddColumn("Start Date    ", START_DATE);
	AddColumn("End Date      ", END_DATE);

	InitColumnHeadings();
    
	EnableMenu(TRUE) ;
//	SetMultiSelectMode(TRUE);
}

void CGridPayrollMessages::Update()
{
	CWaitCursor cWait ;

	EnableUpdate(FALSE);

	while (GetNumberRows())
	{
		DeleteRow(0) ;
	}

	int iRow = 0;
	try 
	{
		m_setPayrollMessages.MoveFirst();
		//Add the Row Heading to the grid
		while (!m_setPayrollMessages.IsEOF())
		{
			AppendRow() ;
			iRow = GetNumberRows() - 1 ;

			CString strHeading ;
			strHeading.Format("%d", m_setPayrollMessages.m_ID);
			QuickSetText(ID, iRow, strHeading);
			QuickSetText(MESSAGE, iRow, m_setPayrollMessages.m_Message) ;
			strHeading = m_setPayrollMessages.m_StartDate.Format("%m/%d/%Y");
			QuickSetText(START_DATE, iRow, strHeading) ;
			strHeading = m_setPayrollMessages.m_EndDate.Format("%m/%d/%Y");
			QuickSetText(END_DATE, iRow, strHeading) ;
			m_setPayrollMessages.MoveNext() ;
			iRow++ ;
		}
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}
	EnableUpdate(TRUE);
	RedrawAll() ;

}

void CGridPayrollMessages::OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
}

void CGridPayrollMessages::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
}

void CGridPayrollMessages::OnCharDown(UINT *vcKey, BOOL /* processed */)
{
	if ((*vcKey == VK_SPACE) || (*vcKey == VK_RETURN))
	{
//		int col = this->GetCurrentCol() ;
//		long row = this->GetCurrentRow() ;
	}
}

int CGridPayrollMessages::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();
		bool bGrayed = false;

		if ((row >= 0) && (row < GetNumberRows()))
		{
			AddMenuItem(2001, "Edit", bGrayed) ;
			AddMenuItem(2002, "Delete", bGrayed) ;
		}
		else
		{
			AddMenuItem(2000, "Add", bGrayed) ;
		}
	}
	return TRUE ;
}

void CGridPayrollMessages::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		if (item == 2000)  // Add
		{
			CDlgPayrollMessage dlg;
			if ( dlg.DoModal() == IDOK)
			{
				COleDateTime timeStart;
				COleDateTime timeEnd;
				CString strMessageText;
				dlg.GetMessage(strMessageText, timeStart, timeEnd);

				m_setPayrollMessages.AddNew();
				m_setPayrollMessages.m_Message = strMessageText;
				m_setPayrollMessages.m_StartDate = timeStart;
				m_setPayrollMessages.m_EndDate = timeEnd;
				m_setPayrollMessages.Update();
			}
		}
		else if (item == 2001)   // Edit
		{
			int iID = atoi(QuickGetText(ID, row));
			m_setPayrollMessages.m_strFilter.Format("ID = %d", iID);
			m_setPayrollMessages.Requery();
			CDlgPayrollMessage dlg;
			dlg.SetMessage(m_setPayrollMessages.m_Message, m_setPayrollMessages.m_StartDate, m_setPayrollMessages.m_EndDate);
			if (dlg.DoModal() == IDOK)
			{
				m_setPayrollMessages.Edit();
				dlg.GetMessage(m_setPayrollMessages.m_Message, m_setPayrollMessages.m_StartDate, m_setPayrollMessages.m_EndDate);
				m_setPayrollMessages.Update();
			}
			m_setPayrollMessages.m_strFilter = "";
			m_setPayrollMessages.Requery();
		}
		else if (item == 2002)   // Delete
		{
			int iID = atoi(QuickGetText(ID, row));
			if (MessageBox("Are you sure you wish to delete this message?", "Question", MB_YESNO ) == IDYES)
			{
				CString strSQL;
				strSQL.Format("DELETE FROM PayrollMessages where ID = %d", iID);
				g_dbFlooring.ExecuteSQL(strSQL);
				m_setPayrollMessages.Requery();
			}
		}

		Update();
	}
}

bool CGridPayrollMessages::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridPayrollMessages::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}