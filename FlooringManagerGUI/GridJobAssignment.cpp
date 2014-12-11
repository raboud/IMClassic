/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridJobAssignment.cpp: implementation of the CGridJobAssignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridJobAssignment.h"
#include "SetJobAssignmentDetailed.h"
#include "SetSubContractor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridJobAssignment::CGridJobAssignment()
{

}

CGridJobAssignment::~CGridJobAssignment()
{

}

void CGridJobAssignment::OnSetup()
{
	CCFGrid::OnSetup() ;

	CString strHeading ;
	int iIndex ;
//	char* auColHeading[] = {"     Name     ", "  PO Number  ", "Installer                      "} ;
	struct
	{
		int		iRow ;
		char*	pString ;
		int		iCol ;
	} asuHeading1[] = {	{-1, "     Name     ",					NAME },
						{-1, "  PO Number  ",					PO_NUMBER},
						{-1, "TYPE         ",					TYPE},
						{-1, "INSTALLER                      ",	INSTALLER}} ;
	const int iCOL_COUNT =  LAST;

	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	SetNumberCols (iCOL_COUNT, false) ;

	//Add the Column Heading to the grid
	for (iIndex = 0; iIndex < sizeof(asuHeading1) / sizeof(asuHeading1[0]); iIndex++)
	{
		QuickSetText(asuHeading1[iIndex].iCol, asuHeading1[iIndex].iRow, asuHeading1[iIndex].pString);
	}

	EnableMenu(TRUE) ;
	BestFit(0, iCOL_COUNT - 1, 0, UG_BESTFIT_TOPHEADINGS) ;

	CSetSubContractor setSub(&g_dbFlooring) ;

	setSub.m_strFilter = "[Active] = '1'" ;
	setSub.m_strSort = "[LastName], [FirstName]" ;
	setSub.Open() ;
	CString strChoices = "" ;

	if (setSub.IsEOF())
	{
		this->ShowWindow(SW_HIDE) ;
		this->EnableWindow(false) ;
		return ;
	}

	CUGCell cell;
	GetColDefault(INSTALLER, &cell) ;

	while (!setSub.IsEOF())
	{
		strChoices += setSub.m_LastName ;
		strChoices += ", " ;
		strChoices += setSub.m_FirstName ;
		strChoices += "\n" ;
		setSub.MoveNext() ;
	}

	strChoices.MakeUpper() ;

	cell.SetLabelText(strChoices);
	cell.SetCellType( UGCT_DROPLIST);
	SetColDefault(INSTALLER, &cell);
}


void CGridJobAssignment::InitializeData(COleDateTime dateScheduled)
{
	CUGCell cell ;

	CWaitCursor curWait ;

	CSetJobAssignmentDetailed set(&g_dbFlooring) ;

	COleDateTime timeSelected(dateScheduled.GetYear() , dateScheduled.GetMonth(), dateScheduled.GetDay(), 0, 0, 0) ;

		
	set.m_strFilter.Format("(CONVERT(nvarchar, Date, 101) = '%s')", timeSelected.Format("%m/%d/%Y")) ;
//	set.m_strFilter += "[PAID] = '0' AND [Warrenty] = '0' AND [Cancelled] = '0'" ;
	set.m_strSort = "[LastName], [FirstName], [MaterialTypeID] " ;
	set.Open() ;

	EnableUpdate(FALSE);


	CString strLastName = "" ;
	CString strLastType = "" ;
	long lFirstRow = -1 ;

	while(!set.IsEOF())
	{
		AppendRow() ;
		long lRow = this->GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("%d", set.m_Id) ;
		QuickSetText(ID, lRow, strID) ;

		CString strName ;
		strName = set.m_LastName + ", " + set.m_FirstName ;

		CString strLastName ;
		CString strLastType ;

		if (strLastName.CompareNoCase(strName) || strLastType.CompareNoCase(set.m_ShortName))
		{
			QuickSetText(NAME, lRow, strName) ;
			QuickSetText(TYPE, lRow, set.m_ShortName) ;
			strLastName = strName ;
			strLastType = set.m_ShortName ;
			lFirstRow = lRow ;

			// populate Combo box
			// set combo box text
		}
		else
		{
			JoinCells(NAME, lFirstRow, NAME, lRow) ;
			JoinCells(TYPE, lFirstRow, TYPE, lRow) ;
			JoinCells(INSTALLER, lFirstRow, INSTALLER, lRow) ;
		}

		QuickSetText(PO_NUMBER, lRow, set.m_PurchaseOrderNumber) ;

		set.MoveNext() ;
	}

	EnableUpdate(TRUE);
	RedrawAll() ;
	set.Close() ;
}

int CGridJobAssignment::GetSubContractorID(long /* lRow */)
{
	return 0 ;
}

void CGridJobAssignment::SetSubContractorID(long /* lRow */, int /* iSubId */)
{

}

bool CGridJobAssignment::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridJobAssignment::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}