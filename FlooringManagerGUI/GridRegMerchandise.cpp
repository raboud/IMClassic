/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridRegMerchandise.cpp: implementation of the CGridRegMerchandise class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>

#include "Flooring.h"
#include "GridRegMerchandise.h"

#include "SetMaterialType.h"
#include "SetOrderRegMerchandiseDetails.h"
#include "DlgSelectPO.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGridRegMerchandise, CGridPOBase)
	//{{AFX_MSG_MAP(CGridRegMerchandise)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CGridRegMerchandise::CGridRegMerchandise()
: m_setViewOrderRegMerchandiseDetails(&g_dbFlooring), m_setUOM(&g_dbFlooring), m_setStatus(&g_dbFlooring)
{
	m_bShowDeleted = false ;
	m_setViewOrderRegMerchandiseDetails.m_strFilter = "OrderID = -1";
	m_setViewOrderRegMerchandiseDetails.Open() ;
	m_setUOM.Open();
	m_setStatus.Open();
}

CGridRegMerchandise::~CGridRegMerchandise()
{
	if (m_setViewOrderRegMerchandiseDetails.IsOpen())
	{
		m_setViewOrderRegMerchandiseDetails.Close() ;
	}
}

void CGridRegMerchandise::OnSetup()
{
	CGridPOBase::OnSetup();

	AddColumn("  ID  ",								ID,						-1);
	AddColumn("SKU NUMBER",							SKU_NUMBER,				-1);
	AddColumn("SKU NUMBER",							ORG_SKU_NUMBER,			-1);
	AddColumn("DESCRIPTION                        ",DESCRIPTION,			-1);
	AddColumn("DESCRIPTION                        ",ORG_DESCRIPTION,		-1);
	AddColumn("QUANTITY",							QUANTITY,				-1);
	AddColumn("QUANTITY",							ORG_QUANTITY,			-1);
	AddColumn("  UNITS  ",								UOM,					-1);
	AddColumn("  UNITS  ",								ORG_UOM,				-1);
	AddColumn("STATUS                  ",			STATUS,					-1);
	AddColumn("STATUS                  ",			ORG_STATUS,				-1);
	AddColumn("NOTES                              ",NOTES,					-1);
	AddColumn("NOTES                              ",ORG_NOTES,				-1);
	AddColumn("ENTRYMETHOD",                        ENTRY_METHOD_ID,		-1);
	AddColumn("ENTRYMETHOD",                        ORG_ENTRY_METHOD_ID,	-1);
	AddColumn("DELETED",                            DELETED,				-1);
	AddColumn("DELETED",                            ORG_DELETED,			-1);
	AddColumn("REVIEWED",							REVIEWED,               -1);
	AddColumn("REVIEWED",							ORG_REVIEWED,           -1);

	
	SetTH_NumberRows(1);
	SetTH_Height(24);

	SetTH_RowHeight(-1,12);
	
	InitColumnHeadings();

	EnableMenu(TRUE) ;

	CUGCell cell;
	
	GetColDefault(ID, &cell);
	cell.SetNumberDecimals(0) ;
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(ID, &cell) ;

	GetColDefault(SKU_NUMBER, &cell);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(SKU_NUMBER, &cell) ;
	SetColDefault(ORG_SKU_NUMBER, &cell) ;

	GetColDefault(DESCRIPTION, &cell);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	SetColDefault(DESCRIPTION, &cell) ;
	SetColDefault(ORG_DESCRIPTION, &cell) ;

	GetColDefault(QUANTITY, &cell);
	cell.SetNumberDecimals(2) ;
	cell.SetFormatClass(&m_formatNumeric) ;
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	SetColDefault(QUANTITY, &cell) ;
	SetColDefault(ORG_QUANTITY, &cell) ;

	GetColDefault(UOM, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(UOM, &cell) ;
	SetColDefault(ORG_UOM, &cell) ;
	
	GetColDefault(STATUS, &cell);
	cell.SetCellType(UGCT_DROPLIST);
	//cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(STATUS, &cell) ;
	SetColDefault(ORG_STATUS, &cell) ;

	GetColDefault(NOTES, &cell);
	cell.SetAlignment( UG_ALIGNLEFT|UG_ALIGNTOP );
	SetColDefault(NOTES, &cell) ;
	SetColDefault(ORG_NOTES, &cell) ;

	GetColDefault(REVIEWED, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(REVIEWED, &cell);
	SetColDefault(ORG_REVIEWED, &cell);

	HideColumn(ENTRY_METHOD_ID);
	HideColumn(DELETED);

	HideColumn(ORG_SKU_NUMBER);
	HideColumn(ORG_DESCRIPTION);
	HideColumn(ORG_QUANTITY);
	HideColumn(ORG_UOM) ;
	HideColumn(ORG_STATUS);
	HideColumn(ORG_NOTES);
	HideColumn(ORG_ENTRY_METHOD_ID);
	HideColumn(ORG_DELETED) ;
	HideColumn(REVIEWED) ;
	HideColumn(ORG_REVIEWED) ;

	// Create a mask edit to use with ultimate grid mask edit
	RECT rect = {0,0,0,0};
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);
	m_editUpper.Create(WS_VISIBLE | ES_UPPERCASE, rect, this, 125);

	UseHints(TRUE);
	SetMultiSelectMode(TRUE);
}

void CGridRegMerchandise::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);

	IsRowDirty(oldrow) ;
	UpdateRowColor(oldrow) ;
	UpdateRowHeights() ;
	RedrawAll() ;
}

int CGridRegMerchandise::OnCellTypeNotify(long ControlID, int col, long row, long msg, long param)
{
	if ((ControlID == UGCT_DROPLIST) && (msg == UGCT_DROPLISTSELECT ) && (col == UOM))
	{
		CString strTemp = "";
		CString *pTempStr = (CString*)param;
		int index = pTempStr->Find('(');
		if (index != -1)
		{
			strTemp = pTempStr->GetAt(index+1);
			int NumDec = atoi(strTemp);
			CUGCell cell;
			GetCell(QUANTITY, row, &cell);
			cell.SetNumberDecimals(NumDec);
			SetCell(QUANTITY, row, &cell);
		}
	}

	IsRowDirty(row) ;
	UpdateRowColor(row) ;
	UpdateRowHeights() ;
	RedrawAll();
	return TRUE ;
}

int CGridRegMerchandise::OnEditStart(int col, long row, CWnd **edit)
{
	BOOL bCanEdit = FALSE;

	if ((m_bConsolidatedView) || (row < 0))
	{
		return FALSE;
	}

	// allow editing an imported item if permission is granted
	double dEntryMethod = QuickGetNumber(ENTRY_METHOD_ID, row);
	if (dEntryMethod != CGlobals::ENTRY_MANUAL)  // auto import
	{
		if (m_bCanModifyImported)
		{
			bCanEdit = TRUE;
		}
	}
	else
	{
		bCanEdit = TRUE;
	}

	if (bCanEdit)
	{
		switch (col)
		{
			case QUANTITY:
				m_editNumeric.LimitText(0) ;
				*edit = &m_editNumeric ;
				break ;
			case DESCRIPTION :
			case NOTES:
			case SKU_NUMBER:
				{
					CUGEdit* editClass = (CUGEdit*)GetEditClass();
					editClass->LimitText(200);
					editClass->ModifyStyle(0, ES_UPPERCASE);
				}
				break;
			default:
				bCanEdit = FALSE;
		}
	}

	return bCanEdit;
}

int CGridRegMerchandise::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(edit);
	UNREFERENCED_PARAMETER(cancelFlag);

	QuickSetText(col, row, string) ;

	IsRowDirty(row) ;
	UpdateRowColor(row) ;
	UpdateRowHeights() ;
	RedrawAll();

	return TRUE;
}

void CGridRegMerchandise::OnKillFocus(CWnd* /* pOldWnd */ )
{
}


BOOL CGridRegMerchandise::OnCanMove(int oldcol, long oldrow, int newcol, long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);

	BOOL bOk = true ;

	return bOk ;
}

int CGridRegMerchandise::DeleteRow(long lRow)
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
		
		QuickSetReadOnly(SKU_NUMBER, lRow, true);
		QuickSetReadOnly(DESCRIPTION, lRow, true);
		QuickSetReadOnly(QUANTITY, lRow, true);
		QuickSetReadOnly(UOM, lRow, true);
		QuickSetReadOnly(STATUS, lRow, true);
		QuickSetReadOnly(NOTES, lRow, true);
		
		IsRowDirty(lRow) ;
		UpdateRowColor(lRow) ;
		UpdateRowHeights() ;
		RedrawAll() ;
	}	
	return TRUE ;
}


int CGridRegMerchandise::UndeleteRow(long lRow)
{	
	//long lStatus = CGridPOBase::DeleteRow(lRow) ;
	long lStatus = TRUE;

	QuickSetBool(DELETED, lRow, false);

	// row specific init
	IsRowDirty(lRow) ;
	UpdateRowColor(lRow) ;
	UpdateRowHeights() ;
	RedrawAll() ;
	return lStatus ;
}

void CGridRegMerchandise::UpdateRecordSet()
{
	bool bUpdateOK = true;
	long lRow ;

	CommitChanges();

	CSetOrderRegMerchandiseDetails setDetails(&g_dbFlooring) ;
	setDetails.m_strFilter = "ID = -1";
	setDetails.Open() ;

	ASSERT(m_listPOs.GetCount() == 1);

	bool bNew = false ;
	for (lRow = 0; lRow < GetNumberRows() ; lRow++)
	{
		try
		{
			if (IsRowDirty(lRow))
			{
				CString strTemp ;
				QuickGetText(ID, lRow, &strTemp) ;
				strTemp.Replace("*", "") ;

				if (strTemp == "")
				{
					setDetails.AddNew() ;
				
					POSITION pos = m_listPOs.GetHeadPosition();
					setDetails.m_OrderID = m_listPOs.GetNext(pos);
					setDetails.m_OriginalOrderID = setDetails.m_OrderID;
					bNew = true ;
				}
				else
				{
					setDetails.m_strFilter.Format("[ID] = '%s'", strTemp) ;
					setDetails.Requery() ;
					setDetails.Edit() ;
					bNew = false ;
				}

				if (IsColumnDirty(SKU_NUMBER, lRow) || bNew)
				{
					QuickGetText(SKU_NUMBER, lRow, &setDetails.m_SKUNumber) ;
				}

				if (IsColumnDirty(DESCRIPTION, lRow) || bNew)
				{
					QuickGetText(DESCRIPTION, lRow, &setDetails.m_Description) ;
				}

				if (IsColumnDirty(QUANTITY, lRow) || bNew)
				{
					setDetails.m_Quantity = QuickGetNumber (QUANTITY, lRow) ;
				}

				if (IsColumnDirty(UOM, lRow) || bNew)
				{
					int UOMId = GetUOMId(QuickGetText(UOM, lRow));
					if (UOMId != -1)
					{
						setDetails.m_UOMId = UOMId;
					}
				}

				if (IsColumnDirty(STATUS, lRow) || bNew)
				{
					CString strMerchStatus = QuickGetText(STATUS, lRow);
					m_setStatus.m_strFilter.Format("Status = '%s'", strMerchStatus);
					m_setStatus.Requery();
					if (!m_setStatus.IsEOF())
					{
						setDetails.m_StatusID = m_setStatus.m_MatStatusID;
					}
				}

				if (IsColumnDirty(NOTES, lRow) || bNew)
				{
					setDetails.m_Notes = QuickGetText(NOTES, lRow);
				}

				if (IsColumnDirty(ENTRY_METHOD_ID, lRow) || bNew)
				{
					setDetails.m_EntryMethodID = (long)QuickGetNumber(ENTRY_METHOD_ID, lRow);
				}

				if (IsColumnDirty(DELETED, lRow) || bNew)
				{
					setDetails.m_Deleted = QuickGetBool(DELETED, lRow);
				}

				bool bReviewedDirty = IsColumnDirty(REVIEWED, lRow);
				if ( bReviewedDirty || bNew)
				{
					bool bReviewed = QuickGetBool(REVIEWED, lRow);
					setDetails.m_Reviewed = bReviewed;
					// if reviewed, update name/date
					// if not-reviewed and dirty, update name/date
					if ((bReviewed) || (bReviewedDirty && !bReviewed))
					{
						setDetails.m_ReviewedBy = CGlobals::GetEmployeeID();
						setDetails.m_ReviewedDate = CGlobals::GetCurrentSystemTime();
					}
				}

				setDetails.Update() ;
			}
		}
		catch (CException* pE)
		{
			pE->Delete() ;
			bUpdateOK = false;
		}
	}
	DeleteRecordList(setDetails, "[ID] = '%s'", "") ;
	setDetails.Close() ;
}

int CGridRegMerchandise::GetUOMId(CString strUOM)
{
	CString UOM = strUOM.Left(2);
	int NumDec = -1;
	int UOMId = -1;
	if ((strUOM.Find('(') != -1) && (strUOM.Find(')') != -1))
	{
		CString strTemp = strUOM.Right(strUOM.GetLength() - (strUOM.Find('(') + 1));
		strTemp = strTemp.Left(strTemp.GetLength() - 1);
		NumDec = atoi(strTemp);
	}

	if (NumDec != -1)
	{
		m_setUOM.m_strFilter.Format("Description = '%s' AND NumberOfDecimals = %d", UOM, NumDec);
	}
	else
	{
		m_setUOM.m_strFilter.Format("Description = '%s'", UOM);
	}

	m_setUOM.Requery();
	if (!m_setUOM.IsEOF())
	{
		UOMId = m_setUOM.m_UnitOfMeasureID;
	}

	return UOMId;
}

void CGridRegMerchandise::UpdateGrid()
{
	Reset();
	if (m_listPOs.GetCount() > 0)
	{
		long lRow = 0 ;

		m_setViewOrderRegMerchandiseDetails.m_strFilter = m_strRecordSetFilter;
		
		if (m_setViewOrderRegMerchandiseDetails.IsOpen())
		{
			m_setViewOrderRegMerchandiseDetails.Requery();
		}
		else
		{
			m_setViewOrderRegMerchandiseDetails.Open();
		}

		while (!m_setViewOrderRegMerchandiseDetails.IsEOF())
		{
			AppendRow() ;
			CUGCell cell ;

			CString strTemp ;
			strTemp.Format("%d", m_setViewOrderRegMerchandiseDetails.m_ID) ;
			QuickSetText(ID, lRow, strTemp) ;

			strTemp = m_setViewOrderRegMerchandiseDetails.m_SKUNumber ;
			strTemp.MakeUpper() ;
			if (strTemp.Find('-') == -1)
			{
				strTemp = strTemp.Right(6);
				strTemp.Insert(3, '-');
			}
			QuickSetText(SKU_NUMBER, lRow, strTemp) ;
			QuickSetText(ORG_SKU_NUMBER, lRow, strTemp) ;

			QuickSetText(DESCRIPTION, lRow, m_setViewOrderRegMerchandiseDetails.m_Description) ;
			QuickSetText(ORG_DESCRIPTION, lRow, m_setViewOrderRegMerchandiseDetails.m_Description) ;

			QuickSetNumber(QUANTITY, lRow, m_setViewOrderRegMerchandiseDetails.m_Quantity ) ;
			QuickSetNumber(ORG_QUANTITY, lRow, m_setViewOrderRegMerchandiseDetails.m_Quantity ) ;

			QuickSetText(UOM, lRow, m_setViewOrderRegMerchandiseDetails.m_UOMDescription);
			QuickSetText(ORG_UOM, lRow, m_setViewOrderRegMerchandiseDetails.m_UOMDescription);

			QuickSetText(NOTES, lRow, m_setViewOrderRegMerchandiseDetails.m_Notes);
			QuickSetText(ORG_NOTES, lRow, m_setViewOrderRegMerchandiseDetails.m_Notes);

			QuickSetText(STATUS, lRow, m_setViewOrderRegMerchandiseDetails.m_Status);
			QuickSetText(ORG_STATUS, lRow, m_setViewOrderRegMerchandiseDetails.m_Status);

			QuickSetNumber(ENTRY_METHOD_ID, lRow, m_setViewOrderRegMerchandiseDetails.m_EntryMethodID);
			QuickSetNumber(ORG_ENTRY_METHOD_ID, lRow, m_setViewOrderRegMerchandiseDetails.m_EntryMethodID);

			QuickSetBool(DELETED, lRow, m_setViewOrderRegMerchandiseDetails.m_Deleted == 1);
			QuickSetBool(ORG_DELETED, lRow, m_setViewOrderRegMerchandiseDetails.m_Deleted == 1);

			QuickSetBool(REVIEWED, lRow, (m_setViewOrderRegMerchandiseDetails.m_Reviewed == TRUE));
			QuickSetBool(ORG_REVIEWED, lRow, (m_setViewOrderRegMerchandiseDetails.m_Reviewed == TRUE));

			UpdateRowColor(lRow);

			if (!m_bAllowStatusUpdate)
			{
				if (m_setViewOrderRegMerchandiseDetails.m_EntryMethodID != CGlobals::ENTRY_MANUAL)
				{
					// if we have a non-manually entered item (i.e. imported)
					if ( (!m_bCanModifyImported) &&
						 (!m_bInvokedFromSPN) && (!(m_setViewOrderRegMerchandiseDetails.m_Deleted == 1)))
					{
						QuickSetCellType(UOM, lRow, UGCT_NORMAL);
						if (!CGlobals::HasPermission("CanModifyRegMerchStatus"))
						{
							QuickSetCellType(STATUS, lRow, UGCT_NORMAL);
						}
					}
				}
			}

			lRow++ ;
			m_setViewOrderRegMerchandiseDetails.MoveNext() ;
		}
	}	
	UpdateRowHeights() ;
}

int CGridRegMerchandise::AppendRow()
{
	int iReturn = CGridPOBase::AppendRow() ;

	long lRow = GetNumberRows() - 1;

	CUGCell cell ;

	GetColDefault(SKU_NUMBER, &cell) ;
	SetCell(SKU_NUMBER, lRow, &cell) ;

	GetColDefault(DESCRIPTION, &cell) ;
	SetCell(DESCRIPTION, lRow, &cell) ;

	GetColDefault(QUANTITY, &cell) ;
	SetCell(QUANTITY, lRow, &cell) ;

	GetColDefault(UOM, &cell) ;
	SetCell(UOM, lRow, &cell) ;

	GetColDefault(NOTES, &cell) ;
	SetCell(NOTES, lRow, &cell) ;

	GetColDefault(STATUS, &cell) ;
	CString strChoices = "" ;
	m_setStatus.m_strFilter = "";
	m_setStatus.Requery();
	while (!m_setStatus.IsEOF())
	{
		strChoices += m_setStatus.m_Status;
		strChoices += "\n" ;
		m_setStatus.MoveNext() ;
	}

	strChoices.MakeUpper() ;
	cell.SetLabelText(strChoices);
	cell.SetText("UNKNOWN");
	SetCell(STATUS, lRow, &cell) ;

	// set up the UOM cell to be a drop list
	strChoices = "" ;
	GetColDefault(UOM, &cell) ;
	m_setUOM.m_strFilter = "";
	m_setUOM.m_strSort = "Description";
	m_setUOM.Requery();

	CString strTemp;
	strTemp.Format("%s (%d)", m_setUOM.m_Description, m_setUOM.m_NumberOfDecimals);
	cell.SetText(strTemp) ;
	int iDecimals = m_setUOM.m_NumberOfDecimals ;
	
	while (!m_setUOM.IsEOF())
	{
		strTemp.Format("%s (%d)\n", m_setUOM.m_Description, m_setUOM.m_NumberOfDecimals);
		strChoices += strTemp ;
		m_setUOM.MoveNext() ;
	}

	strChoices.MakeUpper() ;

	cell.SetCellType( UGCT_DROPLIST);
	cell.SetLabelText(strChoices);
	SetCell(UOM, lRow, &cell);

	GetColDefault(QUANTITY, &cell);
	cell.SetNumberDecimals(iDecimals);
	SetCell(QUANTITY, lRow, &cell);

	QuickSetNumber(ENTRY_METHOD_ID, lRow, CGlobals::ENTRY_MANUAL);
	QuickSetBool(DELETED, lRow, false);

	QuickSetReadOnly(SKU_NUMBER,  lRow, false);
	QuickSetReadOnly(DESCRIPTION, lRow, false);
	QuickSetReadOnly(QUANTITY,    lRow, false);
	QuickSetReadOnly(UOM,         lRow, false);
	QuickSetReadOnly(NOTES,       lRow, false);
	QuickSetReadOnly(STATUS,      lRow, false);

	UpdateRowColor(lRow);
	UpdateRowHeights() ;

	RedrawAll();

	return iReturn ;
}

void CGridRegMerchandise::UpdateRowColor(long lRow)
{
	if (lRow >= 0)
	{
		long lEntryMethodID = (long) QuickGetNumber(ENTRY_METHOD_ID, lRow);
		int iDetailID = (int) GetDetailID(lRow);
		bool bHasAlerts = false;
		if (iDetailID != -1)
		{
			bHasAlerts = (FALSE == QuickGetBool(REVIEWED, lRow));
		}

		if (QuickGetBool(DELETED, lRow))
		{
			if (m_bShowDeleted || bHasAlerts)
			{
				if (lEntryMethodID == CGlobals::ENTRY_MANUAL)
				{
					SetRowColor (lRow, CGlobals::COLOR_MANUAL_DELETED_TEXT, CCFGrid::EnColorMode_TEXT) ;
					if (bHasAlerts)
					{
                        SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
					}
					else
					{
						SetRowColor (lRow, CGlobals::COLOR_MANUAL_DELETED_BACK, CCFGrid::EnColorMode_BACK) ;	
					}
				}
				else
				{
					SetRowColor (lRow, CGlobals::COLOR_XML_DELETED_TEXT, CCFGrid::EnColorMode_TEXT) ;
					if (bHasAlerts)
					{
                        SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
					}
					else
					{
						SetRowColor (lRow, CGlobals::COLOR_XML_DELETED_BACK, CCFGrid::EnColorMode_BACK) ;
					}
				}
			}
		}
		else
		{
			if (bHasAlerts)
			{
				SetRowColor(lRow, CGlobals::COLOR_BLUE, CCFGrid::EnColorMode_TEXT);
				SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
			}
			else
			{
				SetRowColor (lRow, CGlobals::COLOR_NORMAL_BACK, CCFGrid::EnColorMode_BACK) ;

				switch (lEntryMethodID)
				{
					case CGlobals::ENTRY_MANUAL: SetRowColor (lRow, CGlobals::COLOR_MANUAL, CCFGrid::EnColorMode_TEXT) ;
						break;
					case CGlobals::ENTRY_SOSI_IMPORTED:
					case CGlobals::ENTRY_SPN_IMPORTED: 
						SetRowColor (lRow, CGlobals::COLOR_IMPORTED, CCFGrid::EnColorMode_TEXT) ;
						break;
					case CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED:
					case CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED: 
						SetRowColor (lRow, CGlobals::COLOR_IMPORTED_HAND_MODIFIED, CCFGrid::EnColorMode_TEXT) ;
						break;
					default: SetRowColor (lRow, CGlobals::COLOR_MANUAL, CCFGrid::EnColorMode_TEXT) ;
						break;
				}
			}
		}
	}
}

int CGridRegMerchandise::GetFirstColumnIndex()
{
	return ID + 1;
}

int CGridRegMerchandise::GetLastColumnIndex()
{
	return LAST;
}

void CGridRegMerchandise::ShowDeleted(bool bShowDeleted) 
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


int CGridRegMerchandise::OnMenuStart(int col, long row, int section)
{
	UNREFERENCED_PARAMETER(col);

	if (m_bConsolidatedView)
	{
		return FALSE;
	}

	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		//** Add the Menu Items
		AddMenuItem(1000,"New");

		if ((row >= 0) && (row < GetNumberRows()) && (!QuickGetBool(DELETED, row)) && ((QuickGetNumber(ENTRY_METHOD_ID, row) == CGlobals::ENTRY_MANUAL) || m_bCanModifyImported))
		{
			AddMenuItem(2000, "Delete") ;
		}
		if ((row >= 0) && (row < GetNumberRows()) && (QuickGetBool(DELETED, row)) && ((QuickGetNumber(ENTRY_METHOD_ID, row) == CGlobals::ENTRY_MANUAL) || m_bCanModifyImported))
		{
			AddMenuItem(2001, "Undelete") ;
		}
		if ((row >= 0) && (row < GetNumberRows()))
		{
			AddMenuItem(3000, "Transfer To Another PO");
		}
		if (row >= 0)
		{
			if (QuickGetBool(REVIEWED, row) == FALSE)
			{
				if (m_bAllowStatusUpdate)
				{
					AddMenuItem(3001, "Mark Reviewed", !m_bCanMarkReviewed);
				}
				else
				{
					AddMenuItem(3001, "Mark Reviewed", !m_bCanMarkReviewed || GetSelectedRows() > 1);
				}
			}
			else
			{
				if (m_bAllowStatusUpdate)
				{
					AddMenuItem(3001, "Mark Un-Reviewed", !m_bCanMarkReviewed);
				}
				else
				{
					AddMenuItem(3001, "Mark Un-Reviewed", !m_bCanMarkReviewed || GetSelectedRows() > 1);
				}
			}
		}
	}
	return TRUE ;
}

int CGridRegMerchandise::OnHint(int col, long row, int section, CString *string, int *maxwidth)
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

void CGridRegMerchandise::OnMenuCommand(int col, long row, int section, int item)
{
	UNREFERENCED_PARAMETER(col);
	if (section == UG_GRID)
	{
		// The user has selected the 'New' option
		if (item == 1000)
		{
			AppendRow() ;
		}
		else if (item == 2000)
		{
			DeleteRow(row) ;
		}
		else if (item == 2001)
		{
			UndeleteRow(row) ;
		}
		else if (item == 3000)
		{
			// Transfer materials
			TransferMaterials();
		}
		else if (item == 3001)
		{
			// init the list of selected rows
			GetSelectedRows();
			POSITION pos = m_listRows.GetHeadPosition();
			bool bUpdateTabs = false;
			while( pos )
			{
				long lRow = m_listRows.GetNext(pos);
				if (QuickGetBool(REVIEWED, lRow) == FALSE)
				{
					QuickSetBool(REVIEWED, lRow, true);
					bUpdateTabs = bUpdateTabs || IsRowDirty(lRow);
				}
				else
				{
					QuickSetBool(REVIEWED, lRow, false);
					bUpdateTabs = bUpdateTabs || IsRowDirty(lRow);
				}
			}
			if (bUpdateTabs)
			{
				::PostMessage(GetParent()->GetParent()->m_hWnd, wm_TAB_COLOR_UPDATE, 0, 0) ;
			}
		}
	}
	RedrawAll() ;
}

void CGridRegMerchandise::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	StartEdit();
}

void CGridRegMerchandise::CommitChanges()
{
	// this function will make changes to the db permanent

	// start by seeing if anything needs to be transferred.
	if (m_listTransferRows.GetCount() > 0)
	{
		_TRANSFER_STRUCT sTransferRow ;
		POSITION pos = m_listTransferRows.GetHeadPosition();

		CString strSQL;
		while (pos)
		{
			sTransferRow = m_listTransferRows.GetNext(pos);
			strSQL.Format("UPDATE OrderRegMerchandiseDetails SET OrderID = %d WHERE ID = %d", sTransferRow.lNewOrderID, sTransferRow.lID);
			g_dbFlooring.ExecuteSQL(strSQL);
		}
	}

	// any more db changes go here...

}

bool CGridRegMerchandise::TransferMaterials()
{
	// this function adds to a master list the entries to be deleted. it makes no changes
	// to the database - in case the user later cancels the changes, we don't end up with
	// a db out of whack.  If CommitChanges() is called, then that is when the db is updated.
	bool bTransferOK = false;

	// init the list of selected rows
	GetSelectedRows();

	// get the current orderid
	POSITION pos = m_listPOs.GetHeadPosition();
	long lOrderID = m_listPOs.GetNext(pos);
	
	CDlgSelectPO dlg;

	dlg.SetOrderID(lOrderID);
	if (dlg.DoModal() == IDOK)
	{
		_TRANSFER_STRUCT sTransferRow ;
        long lNewOrderID = dlg.GetSelectedOrderID();
		if (lNewOrderID != -1)
		{
			pos = m_listRows.GetHeadPosition();
			while( pos )
			{
				long lRow = m_listRows.GetNext(pos);
				sTransferRow.lID = (long) QuickGetNumber(ID, lRow);
				sTransferRow.lNewOrderID = lNewOrderID;
				m_listTransferRows.AddTail(sTransferRow);
			}

			// delete the rows...
			pos = m_listRows.GetTailPosition();
			while( pos )
			{
				CUGCtrl::DeleteRow(m_listRows.GetPrev(pos));
			}
		}
	}

	return bTransferOK;
}


bool CGridRegMerchandise::IsColumnDirty(int iCol, long lRow)
{
	bool bDirty = true ;

	switch (iCol)
	{
	case SKU_NUMBER :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(SKU_NUMBER, lRow, &str1) ;
			QuickGetText(ORG_SKU_NUMBER, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

	case DESCRIPTION :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(DESCRIPTION, lRow, &str1) ;
			QuickGetText(ORG_DESCRIPTION, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

	case QUANTITY:
		bDirty = QuickGetNumber(QUANTITY, lRow) != QuickGetNumber(ORG_QUANTITY, lRow) ; 
		break ;

	case UOM :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(UOM, lRow, &str1) ;
			QuickGetText(ORG_UOM, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

	case STATUS :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(STATUS, lRow, &str1) ;
			QuickGetText(ORG_STATUS, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

	case NOTES :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(NOTES, lRow, &str1) ;
			QuickGetText(ORG_NOTES, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

	case ENTRY_METHOD_ID :
		bDirty = QuickGetNumber(ENTRY_METHOD_ID, lRow) != QuickGetNumber(ORG_ENTRY_METHOD_ID, lRow) ;
		break ;

	case DELETED :
		bDirty = QuickGetBool(DELETED, lRow) != QuickGetBool(ORG_DELETED, lRow) ;
		break ;

	case REVIEWED :
		bDirty = QuickGetBool(REVIEWED, lRow) != QuickGetBool(ORG_REVIEWED, lRow) ; 
		break ;

	default:
		assert(0) ;
		break ;
	}

	return bDirty ;
}

bool CGridRegMerchandise::IsRowDirty(long lRow)
{
	bool bDirty = false ;

	if (!bDirty) bDirty = IsColumnDirty(SKU_NUMBER, lRow) ; 
	if (!bDirty) bDirty = IsColumnDirty(DESCRIPTION, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(QUANTITY, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(UOM, lRow) ;

	double dOrigEntryMethod = QuickGetNumber(ORG_ENTRY_METHOD_ID, lRow);
	if ((dOrigEntryMethod == CGlobals::ENTRY_SPN_IMPORTED) || (dOrigEntryMethod == CGlobals::ENTRY_SOSI_IMPORTED))
	{
		if (!bDirty)
		{
			QuickSetNumber(ENTRY_METHOD_ID, lRow, dOrigEntryMethod);  // set to imported 
		}
		else
		{
			QuickSetNumber(ENTRY_METHOD_ID, lRow, (dOrigEntryMethod == CGlobals::ENTRY_SPN_IMPORTED) ? CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED : CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED);  // set to auto / manual modified
		}
	}

	if (!bDirty) bDirty = IsColumnDirty(STATUS, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(NOTES, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(ENTRY_METHOD_ID, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(DELETED, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(REVIEWED, lRow) ;

	CString strId ;
	QuickGetText(ID, lRow, &strId) ;

	if (bDirty)
	{
		strId += "*" ;
		strId.Replace("**", "*") ;
	}
	else
	{
		strId.Replace("*", "") ;
	}

	QuickSetText(ID, lRow, strId) ;

	return bDirty ;
}

void CGridRegMerchandise::UpdateRowHeights()
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
			int iDetailID = (int) GetDetailID(lRow);
			bool bHasAlerts = false;
			if (iDetailID != -1) bHasAlerts = (FALSE == QuickGetBool(REVIEWED, lRow));

			if (!QuickGetBool(DELETED, lRow) || (m_bShowDeleted) || (bHasAlerts))
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

int CGridRegMerchandise::RedrawAll()
{
	UpdateColors() ;
	UpdateRowHeights() ;
	int iReturn = CGridPOBase::RedrawAll() ;
	return iReturn;
}

long CGridRegMerchandise::GetDetailID(const long lRow)
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

bool CGridRegMerchandise::HasUnknownStatus()
{
	bool _hasunknownstatus = false;

	long lNumRows = GetNumberRows();
	if (lNumRows >= 0)
	{
		for (long lRow = 0; lRow < lNumRows; lRow++)
		{
			CString strMerchStatus = QuickGetText(STATUS, lRow);
			if (strMerchStatus.MakeUpper().Find("UNKNOWN") != -1)
			{
				_hasunknownstatus = true;
				break;
			}
		}
	}

	return _hasunknownstatus;
}