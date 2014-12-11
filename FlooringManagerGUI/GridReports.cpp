/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridReports.cpp: implementation of the CGridReports class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridReports.h"
#include "SetActionReportWithName.h"
#include "DlgActionReport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int iMAX_CHARS_FOR_ACTION_REPORT_GRID = 25;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGridReports::CGridReports()
{
	m_pRTFEdit = NULL;
	HighlightCurrentRow();
}

CGridReports::~CGridReports()
{

}

void CGridReports::SetOrderId(int iOrderId)
{
	m_iOrderId = iOrderId ;
	Update() ;
}


void CGridReports::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn("  ID  ",										ID,				   -1);
	AddColumn("   Report Date         ",					REPORT_DATE,	   -1);
	AddColumn("Nature/Action/Cause                  ",		NATURE,			   -1);
	//AddColumn("Action                   ",					ACTION,			   -1);
	//AddColumn("Cause                        ",				CAUSE,			   -1);
	AddColumn("  Created By   ",							CREATED_BY,        -1);
	AddColumn("  Last Updated By  ",							LAST_UPDATED_BY,   -1);
	AddColumn("   Last Updated Date   ",							LAST_UPDATED_DATE, -1);

	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	m_iMultiFontCellTypeIndex = AddCellType(&m_multiFont);

	CUGCell cell;
	/*GetColDefault(NATURE, &cell);
	cell.SetAlignment(UG_ALIGNTOP | UG_ALIGNLEFT) ;
	cell.SetReadOnly(TRUE);
	cell.SetCellType(m_iMultiFontCellTypeIndex);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	SetColDefault(NATURE, &cell);*/
	//SetColDefault(CAUSE, &cell);
	//SetColDefault(ACTION, &cell);

	GetColDefault(CREATED_BY, &cell);
	cell.SetReadOnly(TRUE);
	SetColDefault(CREATED_BY, &cell);
	SetColDefault(LAST_UPDATED_BY, &cell);
	SetColDefault(LAST_UPDATED_DATE, &cell);

	InitColumnHeadings();

	EnableMenu(TRUE) ;
}

int CGridReports::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		AddMenuItem(1000, "Add") ;
		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			AddMenuItem(1001, "Edit") ;
			AddMenuItem(1002, "Print") ;
			if (CGlobals::IsAdmin())
			{
				AddMenuItem(1003, "Email to COS");
			}
		}
	}
	return TRUE ;
}

void CGridReports::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	if (row != -1)
	{
		CDlgActionReport dlg;
		dlg.SetId(int(QuickGetNumber(ID, row)));
		if (dlg.DoModal() == IDOK)
		{
			Update();
		}
	}
}

void CGridReports::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		if (item == 1000)
		{
			CDlgActionReport dlg;
			dlg.SetOrderId(m_iOrderId);
			if (dlg.DoModal() == IDOK)
			{
				Update() ;
			}
		}
		if (item == 1001)
		{
			CDlgActionReport dlg;
			dlg.SetId(int(QuickGetNumber(ID, row)));
			if (dlg.DoModal() == IDOK)
			{
				Update();
			}
		}
		if (item == 1002)
		{
			CWaitCursor curWait;
			CGlobals::PrintCustSatReport(int(QuickGetNumber(ID, row)));
		}
		if (item == 1003)
		{
			CWaitCursor curWait;
			CGlobals::EmailCosCustSatReport(int(QuickGetNumber(ID, row)));
		}
	}
}



void CGridReports::Update()
{
	EnableUpdate(FALSE);

	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetActionReportWithName set(&g_dbFlooring);
	set.m_strFilter.Format("OrderId = '%d'", m_iOrderId);
	set.m_strSort = "[ReportDate]" ;
	set.Open();

	int iRow = 0;
	SetNumberRows (0, false) ;

	while (!set.IsEOF())
	{
		CString strOut ;
		CString strNature;
		//CString strActionRequired;
		//CString strCause;

		AppendRow() ;
		iRow = GetNumberRows() - 1 ;

		strOut.Format("%d", set.m_ID) ;
		QuickSetText(ID, iRow, strOut) ;
		QuickSetReadOnly(ID, iRow, true) ;

		QuickSetText(REPORT_DATE, iRow, set.m_ReportDate.Format("%m/%d/%Y %H:%M:%S %p"));
		QuickSetReadOnly(REPORT_DATE, iRow, true) ;

		ASSERT(m_pRTFEdit != NULL);

		//strNature.Format("<:F,Arial,12,600>Nature:<:F,Arial,12,400> %s\n<:F,Arial,12,600>Action:<:F,Arial,12,400> %s\n<:F,Arial,12,600>Cause:<:F,Arial,12,400> %s", GetGridText(set.m_Nature), GetGridText(set.m_ActionRequired), GetGridText(set.m_Cause));
		strNature.Format("Nature: %s\nAction: %s\n Cause: %s", GetGridText(set.m_Nature), GetGridText(set.m_ActionRequired), GetGridText(set.m_Cause));
		CUGCell cell;
		GetCell(NATURE, iRow, &cell);

		// DKB - cannot use Multi-Font type AND Multi Line, so we are just using Multi-line...
		//cell.SetCellType(m_iMultiFontCellTypeIndex);
		cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
		cell.SetText(strNature);
		SetCell(NATURE, iRow, &cell);

		QuickSetText(CREATED_BY, iRow, set.m_CreatedBy);
		QuickSetText(LAST_UPDATED_BY, iRow, set.m_LastUpdatedBy);
		QuickSetText(LAST_UPDATED_DATE, iRow, set.m_LastUpdatedDate.Format("%m/%d/%Y %H:%M:%S %p"));

		set.MoveNext() ;

		iRow++ ;
	}
	set.Close() ;

	UpdateRowHeights() ;

	EnableUpdate(TRUE);
	RedrawAll();

}

void CGridReports::UpdateRowHeights()
{
	//return;
	long lNumRows = GetNumberRows();

	if (lNumRows >= 0)
	{
		CDC* pDC = GetDC() ;


		/*CRect rect(0, 0, GetColWidth(ACTION) - 2, 10) ;
		pDC->DPtoLP(&rect) ;
		int iActionWidth = rect.Width() ;*/

		CRect rect = CRect(0, 0, GetColWidth(NATURE) - 2, 10) ;
		pDC->DPtoLP(&rect) ;
		int iNatureWidth = rect.Width() ;

		/*rect = CRect(0, 0, GetColWidth(CAUSE) - 2, 10) ;
		pDC->DPtoLP(&rect) ;
		int iCauseWidth = rect.Width() ;*/

		CUGCell cell ;
		GetCell(NATURE, 0, &cell) ;

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
			/*rect.right = rect.left + iActionWidth  ;
			pDC->DrawText(QuickGetText(ACTION, lRow), &rect, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
			pDC->LPtoDP(&rect) ;
			int iHeight = rect.Height() ;*/

			rect.right = rect.left + iNatureWidth  ;
			pDC->DrawText(QuickGetText(NATURE, lRow), &rect, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
			pDC->LPtoDP(&rect) ;
			int iHeight = rect.Height() ;
			//int iHeight = max(iHeight, rect.Height()) ;

			/*rect.right = rect.left + iCauseWidth  ;
			pDC->DrawText(QuickGetText(CAUSE, lRow), &rect, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
			pDC->LPtoDP(&rect) ;
			iHeight = max(iHeight, rect.Height()) ;*/

			SetRowHeight(lRow, iHeight + iRowLeader) ;
		}
	}
}

CString CGridReports::GetGridText(CString strRTFText)
{
	CString strText = "";
	CStringArray astrParagraphs;
	m_pRTFEdit->SetRTF(strRTFText);
	int iNumPars = m_pRTFEdit->GetParagraphContents(astrParagraphs, true);
	if (iNumPars > 0)
	{
		strText = astrParagraphs[0];
		if (astrParagraphs[0].Find("Entered") > -1)
		{
			if (iNumPars > 1)
			{
				strText = astrParagraphs[1];
			}
		}
	}

	CString strTemp = strText.Left(iMAX_CHARS_FOR_ACTION_REPORT_GRID);
	strTemp = strTemp.Left(strTemp.ReverseFind(' ')) + "...";

	return strTemp.MakeUpper();
}

bool CGridReports::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridReports::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}