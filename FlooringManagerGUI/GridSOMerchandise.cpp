/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridSOMerchandise.cpp: implementation of the CGridSOMerchandise class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>

#include "Flooring.h"
#include "GridSOMerchandise.h"
#include "SetMaterialType.h"
#include "SetOrderSOMerchandiseDetails.h"
#include "SetMatStatus.h"
#include "DlgSplitLineItem.h"
#include "DlgSelectPO.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int iMAT_STATUS_PRESENT = 2;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGridSOMerchandise, CGridPOBase)
	//{{AFX_MSG_MAP(CGridSOMerchandise)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CGridSOMerchandise::CGridSOMerchandise()
: m_setViewOrderSOMerchandiseDetails(&g_dbFlooring), m_setUOM(&g_dbFlooring), m_setMatStatus(&g_dbFlooring)
{
	m_setUOM.Open();
	m_setMatStatus.Open();
	m_BasicLaborID = -1;
	m_listTransferRows.RemoveAll();
	m_bShowDeleted = false ;
}

CGridSOMerchandise::~CGridSOMerchandise()
{
	if (m_setViewOrderSOMerchandiseDetails.IsOpen())
	{
		m_setViewOrderSOMerchandiseDetails.Close() ;
	}
}

void CGridSOMerchandise::OnSetup()
{
	CGridPOBase::OnSetup();

	CUGCell cell;

	AddColumn("  ID  ",										ID,						-1);
	AddColumn("SO NUMBER",									SO_NUMBER,				-1);
	AddColumn("SO NUMBER",									ORG_SO_NUMBER,			-1);
	AddColumn("SKU NUMBER",									SKU_NUMBER,				-1);
	AddColumn("SKU NUMBER",									ORG_SKU_NUMBER,			-1);
	AddColumn("DESCRIPTION                        ",		DESCRIPTION,			-1);
	AddColumn("DESCRIPTION                        ",		ORG_DESCRIPTION,		-1);
	AddColumn("QUANTITY",									QUANTITY,				-1);
	AddColumn("QUANTITY",									ORG_QUANTITY,			-1);
	AddColumn("  UNITS  ",									UOM,					-1);
	AddColumn("  UNITS  ",									ORG_UOM,				-1);
	AddColumn("EXP. ARRIVAL",								EXP_ARRIVAL_DATE,		-1);
	AddColumn("EXP. ARRIVAL",								ORG_EXP_ARRIVAL_DATE,	-1);
	AddColumn("           STATUS            ",				MAT_STATUS,				-1);
	AddColumn("           STATUS            ",				ORG_MAT_STATUS,			-1);
	AddColumn("ENTRY METHOD ID",							ENTRY_METHOD_ID,		-1);
	AddColumn("ENTRY METHOD ID",							ORG_ENTRY_METHOD_ID,	-1);
	AddColumn("DELETED",									DELETED,				-1);
	AddColumn("DELETED",									ORG_DELETED,			-1);
	AddColumn("REVIEWED",									REVIEWED,               -1);
	AddColumn("REVIEWED",									ORG_REVIEWED,           -1);
	AddColumn("BASIC LABOR",                                BASIC_LABOR_ID,			-1);
	AddColumn("SHORT DESCRIPTION",                          SHORT_DESCRIPTION,		-1);
	AddColumn("SO LINE NUMBER",                             SO_LINE_NUMBER,			-1);
	AddColumn("SO MER LINE NUMBER",                         SO_MER_LINE_NUMBER,		-1);
	AddColumn("ORIGINAL ID",                                ORIGINAL_ID,			-1);
	AddColumn("PRESPLIT_QTY",                               PRESPLIT_QTY,			-1);
	AddColumn("NOT NEEDED",									NOT_NEEDED,             -1);
	AddColumn("NOT NEEDED",									ORG_NOT_NEEDED,         -1);

	SetTH_NumberRows(1);
	SetTH_Height(24);

	SetTH_RowHeight(-1,12);
	
	InitColumnHeadings();

	EnableMenu(TRUE) ;
	
	GetColDefault(ID, &cell);
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(SO_NUMBER, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(SO_NUMBER, &cell) ;
	SetColDefault(ORG_SO_NUMBER, &cell) ;

	GetColDefault(SKU_NUMBER, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(SKU_NUMBER, &cell) ;
	SetColDefault(ORG_SKU_NUMBER, &cell) ;

	GetColDefault(DESCRIPTION, &cell);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	cell.SetReadOnly(TRUE);
	SetColDefault(DESCRIPTION, &cell) ;
	SetColDefault(ORG_DESCRIPTION, &cell) ;

	GetColDefault(QUANTITY, &cell);
	cell.SetNumberDecimals(2) ;
	cell.SetReadOnly(TRUE);
	cell.SetFormatClass(&m_formatNumeric) ;
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	SetColDefault(QUANTITY, &cell) ;
	SetColDefault(ORG_QUANTITY, &cell) ;

	GetColDefault(UOM, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(UOM, &cell) ;
	SetColDefault(ORG_UOM, &cell) ;

	m_dtpControlID = AddCellType(&m_dtpControl);

	GetColDefault(EXP_ARRIVAL_DATE, &cell);
	cell.SetCellType(m_dtpControlID);
	cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(EXP_ARRIVAL_DATE, &cell) ;
	SetColDefault(ORG_EXP_ARRIVAL_DATE, &cell) ;

	GetColDefault(MAT_STATUS, &cell);
	cell.SetCellType(UGCT_DROPLIST);
	cell.SetAlignment( UG_ALIGNLEFT|UG_ALIGNTOP );
	SetColDefault(MAT_STATUS, &cell) ;
	SetColDefault(ORG_MAT_STATUS, &cell) ;

	GetColDefault(REVIEWED, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(REVIEWED, &cell);
	SetColDefault(ORG_REVIEWED, &cell);

	GetColDefault(NOT_NEEDED, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	cell.SetReadOnly(FALSE) ;
	SetColDefault(NOT_NEEDED, &cell);
	SetColDefault(ORG_NOT_NEEDED, &cell);

	HideColumn(ENTRY_METHOD_ID);
	HideColumn(DELETED);

	// Create a mask edit to use with ultimate grid mask edit
	RECT rect = {0,0,0,0};
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);
	m_editUpper.Create(WS_VISIBLE | ES_UPPERCASE, rect, this, 125);

	UseHints(TRUE);
	SetMultiSelectMode(TRUE);

	HideColumn(ORG_SO_NUMBER) ;
	HideColumn(ORG_SKU_NUMBER) ;
	HideColumn(ORG_DESCRIPTION) ;
	HideColumn(ORG_QUANTITY) ;
	HideColumn(ORG_UOM) ;
	HideColumn(ORG_EXP_ARRIVAL_DATE) ;
	HideColumn(ORG_MAT_STATUS) ;
	HideColumn(ORG_ENTRY_METHOD_ID) ;
	HideColumn(ORG_DELETED) ;
	HideColumn(BASIC_LABOR_ID);
	HideColumn(SHORT_DESCRIPTION);
	HideColumn(SO_LINE_NUMBER);
	HideColumn(SO_MER_LINE_NUMBER);
	HideColumn(ORIGINAL_ID);
	HideColumn(PRESPLIT_QTY);
	HideColumn(REVIEWED) ;
	HideColumn(ORG_REVIEWED) ;
	HideColumn(ORG_NOT_NEEDED) ;
}

void CGridSOMerchandise::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
}

int CGridSOMerchandise::OnCellTypeNotify(long ControlID, int col, long row, long msg, long param)
{
	if ((ControlID == m_dtpControlID) && (col == EXP_ARRIVAL_DATE))
	{
		if(msg == UGCT_DISPLAYMONTHCAL)
		{
			UGCTMONTHCALSETTINGS* pmcs = (UGCTMONTHCALSETTINGS*)param;
			CString strTemp = QuickGetText(EXP_ARRIVAL_DATE, row);
			pmcs->dateCur.ParseDateTime(strTemp);
		}
		if(msg == UGCT_CONVERTDATE)
		{
			UGCTCONVERTDATE* cd = (UGCTCONVERTDATE*)param;
			cd->string = cd->date.Format("%#m/%#d/%Y") ;
			QuickSetText(col, row, cd->string) ;
		}
	}
	else if ((ControlID == UGCT_DROPLIST) && (msg == UGCT_DROPLISTSELECT ) && (col == UOM))
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

int CGridSOMerchandise::OnEditStart(int col, long row, CWnd **edit)
{
	BOOL bCanEdit = FALSE;

	if (m_bConsolidatedView)
	{
		return FALSE;
	}

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
				{
					m_editNumeric.LimitText(0) ;
					*edit = &m_editNumeric ;
				}
				break ;
			case DESCRIPTION :
			case SO_NUMBER :
			case SKU_NUMBER :
				{
					CUGEdit* editClass = (CUGEdit*)GetEditClass();
					editClass->LimitText(200);
					editClass->ModifyStyle(0, ES_UPPERCASE);
				}
				break;
			default:
				bCanEdit = FALSE;
				break;
		}
	}

	return bCanEdit;

	//int bEdit = FALSE ;

	//if ((row >= 0) && (col >= 0) )
	//{

	//	CUGCell cell ;
	//	GetCell(col, row, &cell) ;

	//	bEdit = !cell.GetReadOnly() ;

	//	if (bEdit)
	//	{
	//		*edit = &m_editUpper ;
	//		switch (col)
	//		{
	//			case QUANTITY:
	//				m_editNumeric.LimitText(0) ;
	//				*edit = &m_editNumeric ;
	//				break ;
	//			case UOM:
	//			case EXP_ARRIVAL_DATE:
	//				bEdit = FALSE;
	//				break;
	//			default:
	//				bEdit = FALSE;
	//				break;
	//		}
	//	}
	//}

	//return bEdit ;

}

int CGridSOMerchandise::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(cancelFlag);
	UNREFERENCED_PARAMETER(edit);

	QuickSetText(col, row, string) ;

	IsRowDirty(row) ;
	UpdateRowColor(row) ;
	UpdateRowHeights() ;
	RedrawAll();

	return TRUE;
}

void CGridSOMerchandise::OnKillFocus(CWnd* /* pOldWnd */ )
{
}


BOOL CGridSOMerchandise::OnCanMove(int oldcol, long oldrow, int newcol, long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	BOOL bOk = true ;

	return bOk ;
}

int CGridSOMerchandise::DeleteRow(long lRow)
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
		QuickSetReadOnly(UOM, lRow, true);
		QuickSetReadOnly(EXP_ARRIVAL_DATE, lRow, true);
		QuickSetReadOnly(MAT_STATUS, lRow, true);

		IsRowDirty(lRow) ;
		UpdateRowHeights() ;
		UpdateRowColor(lRow) ;
	}

	return TRUE ;
}

int CGridSOMerchandise::UndeleteRow(long lRow)
{	
	//long lStatus = CGridPOBase::DeleteRow(lRow) ;
	long lStatus = TRUE;

	QuickSetBool(DELETED, lRow, false);

	IsRowDirty(lRow) ;

	// row specific init
	UpdateRowColor(lRow) ;
	UpdateRowHeights() ;
	return lStatus ;
}

void CGridSOMerchandise::UpdateRecordSet()
{
	bool bUpdateOK = true;
	long lRow ;

	CommitChanges();

	CSetOrderSOMerchandiseDetails setDetails(&g_dbFlooring) ;
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
					setDetails.m_MaterialStatusID = 1;
					bNew = true ;
				
					POSITION pos = m_listPOs.GetHeadPosition();
					setDetails.m_OrderID = m_listPOs.GetNext(pos);
					setDetails.m_OriginalOrderID = setDetails.m_OrderID;
				}
				else
				{
					setDetails.m_strFilter.Format("[ID] = '%s'", strTemp) ;
					setDetails.Requery() ;
					setDetails.Edit() ;
					bNew = false ;
				}

	//			setDetails.m_BasicLaborID = m_BasicLaborID ;

				if (IsColumnDirty(SO_NUMBER, lRow) || bNew)
				{
					QuickGetText(SO_NUMBER, lRow, &setDetails.m_SONumber) ;
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

				if (IsColumnDirty(EXP_ARRIVAL_DATE, lRow) || bNew)
				{
					COleDateTime time;
					if (time.ParseDateTime(QuickGetText(EXP_ARRIVAL_DATE, lRow)))
					{
						setDetails.m_ExpectedArrivalDate = time;
					}
				}

				bool bMatStatusChanged = IsColumnDirty(MAT_STATUS, lRow);
				if (bMatStatusChanged || bNew)
				{
					CString strMatStatus = QuickGetText(MAT_STATUS, lRow);
					m_setMatStatus.m_strFilter.Format("Status = '%s'", strMatStatus);
					m_setMatStatus.Requery();
					if (!m_setMatStatus.IsEOF())
					{
						setDetails.m_MaterialStatusID = m_setMatStatus.m_MatStatusID;
					}
				}

				if (IsColumnDirty(ENTRY_METHOD_ID, lRow) || bNew)
				{
					setDetails.m_EntryMethodID = (long)QuickGetNumber(ENTRY_METHOD_ID, lRow);
				}

				if (IsColumnDirty(DELETED, lRow) || bNew)
				{
					setDetails.m_Deleted = QuickGetBool(DELETED, lRow);
				}


				if (IsColumnDirty(NOT_NEEDED, lRow) || bNew)
				{
					setDetails.m_NotNeeded = QuickGetBool(NOT_NEEDED, lRow);
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

				setDetails.m_BasicLaborID = (long)QuickGetNumber(BASIC_LABOR_ID, lRow);
				setDetails.m_ShortDescription = QuickGetText(SHORT_DESCRIPTION, lRow);
				setDetails.m_SOLineNumber = (long)QuickGetNumber(SO_LINE_NUMBER, lRow);
				setDetails.m_SOMerLineNumber = (long)QuickGetNumber(SO_MER_LINE_NUMBER, lRow);
				setDetails.m_OriginalID = (long)QuickGetNumber(ORIGINAL_ID, lRow);
				double dPreSplitQty = QuickGetNumber(PRESPLIT_QTY, lRow);
				if (dPreSplitQty > 0.0) 
				{
					setDetails.m_PreSplitQty = dPreSplitQty;
				}

				if (setDetails.Update())
				{
					// Requery to make sure the m_Identity value is updated to the latest
					setDetails.Requery();
					
					// if we just inserted a new record, update the filter and requery so we are looking at the
					// correct one.
					if (bNew)
					{
						setDetails.m_strFilter.Format("[ID] = '%s'", setDetails.m_Identity) ;
						setDetails.Requery();
					}

					if (bMatStatusChanged)
					{
						if ((setDetails.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED) ||
							(setDetails.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED))
						{
							// make sure we are updating the original line item, otherwise we could possibly
							// send out too many documents.
							if ((setDetails.m_ID == setDetails.m_OriginalID) || (setDetails.m_OriginalID == -1))
							{
								if (setDetails.m_MaterialStatusID == iMAT_STATUS_PRESENT)
								{
									CString strSQL = "";
									strSQL.Format("EXEC AddSOSIOutgoingDocument %d, '%d', '%s'", CGlobals::iSOSI_VERIFY_PRODUCT_RECEIPT_DOC_ID, setDetails.m_ID, "");
									g_dbFlooring.ExecuteSQL(strSQL);
								}
							}
						}
						else if ((setDetails.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED) ||
					     (setDetails.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED))
						{
							if ((setDetails.m_ID == setDetails.m_OriginalID) || (setDetails.m_OriginalID == -1))
							{
								if (setDetails.m_MaterialStatusID == iMAT_STATUS_PRESENT)
								{
									CGlobals::QueueProductReceipt(setDetails.m_ID);
								}
							}
						}
					}
				}
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

int CGridSOMerchandise::GetUOMId(CString strUOM)
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

void CGridSOMerchandise::SetAllowStatusUpdate(bool bAllowStatusUpdate) 
{
	m_bAllowStatusUpdate = bAllowStatusUpdate ;
}

void CGridSOMerchandise::UpdateGrid()
{
	//Reset();
	ClearAllDataRows();
	if (m_listPOs.GetCount() > 0)
	{
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
			QuickSetText(ORG_SO_NUMBER, lRow, strTemp) ;

			strTemp = m_setViewOrderSOMerchandiseDetails.m_SKUNumber ;
			strTemp.MakeUpper() ;
			if (strTemp.Find('-') == -1)
			{
				strTemp = strTemp.Right(6);
				strTemp.Insert(3, '-');
			}
			QuickSetText(SKU_NUMBER, lRow, strTemp) ;
			QuickSetText(ORG_SKU_NUMBER, lRow, strTemp) ;

			QuickSetText(DESCRIPTION, lRow, m_setViewOrderSOMerchandiseDetails.m_Description) ;
			QuickSetText(ORG_DESCRIPTION, lRow, m_setViewOrderSOMerchandiseDetails.m_Description) ;

			GetCell(QUANTITY, lRow, &cell) ;
			cell.SetNumberDecimals(m_setViewOrderSOMerchandiseDetails.m_NumberOfDecimals) ;
			SetCell(QUANTITY, lRow, &cell) ;
			SetCell(ORG_QUANTITY, lRow, &cell) ;
			QuickSetNumber(QUANTITY, lRow, m_setViewOrderSOMerchandiseDetails.m_Quantity ) ;
			QuickSetNumber(ORG_QUANTITY, lRow, m_setViewOrderSOMerchandiseDetails.m_Quantity ) ;

			strTemp.Format("%s (%d)", m_setViewOrderSOMerchandiseDetails.m_UOMDescription, m_setViewOrderSOMerchandiseDetails.m_NumberOfDecimals);
			QuickSetText(UOM, lRow, strTemp) ;
			QuickSetText(ORG_UOM, lRow, strTemp) ;

			QuickSetText(MAT_STATUS, lRow, m_setViewOrderSOMerchandiseDetails.m_Status);
			QuickSetText(ORG_MAT_STATUS, lRow, m_setViewOrderSOMerchandiseDetails.m_Status);

			if (m_setViewOrderSOMerchandiseDetails.IsFieldNull(&m_setViewOrderSOMerchandiseDetails.m_ExpectedArrivalDate))
			{
				strTemp = "UNKNOWN";
			}
			else if (m_setViewOrderSOMerchandiseDetails.m_ExpectedArrivalDate == 0)
			{
				strTemp = "UNKNOWN";
			}
			else
			{
				strTemp = m_setViewOrderSOMerchandiseDetails.m_ExpectedArrivalDate.Format("%#m/%#d/%Y");
			}
			QuickSetText(EXP_ARRIVAL_DATE, lRow, strTemp);
			QuickSetText(ORG_EXP_ARRIVAL_DATE, lRow, strTemp);

			if (!m_bAllowStatusUpdate)
			{
				if (m_setViewOrderSOMerchandiseDetails.m_EntryMethodID != CGlobals::ENTRY_MANUAL)
				{
					if ( (!m_bCanModifyImported) && (!m_bInvokedFromSPN) && (!(m_setViewOrderSOMerchandiseDetails.m_Deleted == 1)))
					{
						QuickSetCellType(UOM, lRow, UGCT_NORMAL);
						QuickSetCellType(MAT_STATUS, lRow, UGCT_NORMAL);
						QuickSetCellType(EXP_ARRIVAL_DATE, lRow, UGCT_NORMAL);

						QuickSetCellType(ORG_UOM, lRow, UGCT_NORMAL);
						QuickSetCellType(ORG_MAT_STATUS, lRow, UGCT_NORMAL);
						QuickSetCellType(ORG_EXP_ARRIVAL_DATE, lRow, UGCT_NORMAL);
					}
				}
			}

			QuickSetNumber(ENTRY_METHOD_ID, lRow, m_setViewOrderSOMerchandiseDetails.m_EntryMethodID);
			QuickSetNumber(ORG_ENTRY_METHOD_ID, lRow, m_setViewOrderSOMerchandiseDetails.m_EntryMethodID);

			QuickSetBool(DELETED, lRow, m_setViewOrderSOMerchandiseDetails.m_Deleted == 1);
			QuickSetBool(ORG_DELETED, lRow, m_setViewOrderSOMerchandiseDetails.m_Deleted == 1);

			QuickSetBool(REVIEWED, lRow, (m_setViewOrderSOMerchandiseDetails.m_Reviewed == TRUE));
			QuickSetBool(ORG_REVIEWED, lRow, (m_setViewOrderSOMerchandiseDetails.m_Reviewed == TRUE));

			QuickSetBool(NOT_NEEDED, lRow, (m_setViewOrderSOMerchandiseDetails.m_NotNeeded == TRUE));
			QuickSetBool(ORG_NOT_NEEDED, lRow, (m_setViewOrderSOMerchandiseDetails.m_NotNeeded == TRUE));

			QuickSetNumber(BASIC_LABOR_ID,lRow, m_setViewOrderSOMerchandiseDetails.m_BasicLaborID);
			QuickSetText(SHORT_DESCRIPTION,lRow, m_setViewOrderSOMerchandiseDetails.m_ShortDescription);
			QuickSetNumber(SO_LINE_NUMBER,lRow, m_setViewOrderSOMerchandiseDetails.m_SOLineNumber);
			QuickSetNumber(SO_MER_LINE_NUMBER,lRow, m_setViewOrderSOMerchandiseDetails.m_SOMerLineNumber);

			if (!m_setViewOrderSOMerchandiseDetails.IsFieldNull(&m_setViewOrderSOMerchandiseDetails.m_PreSplitQty))
			{
				QuickSetNumber(PRESPLIT_QTY, lRow, m_setViewOrderSOMerchandiseDetails.m_PreSplitQty);
			}
			if (!m_setViewOrderSOMerchandiseDetails.IsFieldNull(&m_setViewOrderSOMerchandiseDetails.m_OriginalID))
			{
				QuickSetNumber(ORIGINAL_ID, lRow, m_setViewOrderSOMerchandiseDetails.m_OriginalID);
			}
			else
			{
				QuickSetNumber(ORIGINAL_ID, lRow, -1);
			}

			UpdateRowColor(lRow);

			lRow++ ;
			m_setViewOrderSOMerchandiseDetails.MoveNext() ;
		}
	}	
	UpdateRowHeights() ;
}

void CGridSOMerchandise::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	StartEdit();
}

int CGridSOMerchandise::AppendRow()
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

	GetColDefault(UOM, &cell) ;
	SetCell(UOM, lRow, &cell) ;

	GetColDefault(EXP_ARRIVAL_DATE, &cell) ;
	CString strTemp = CGlobals::GetCurrentSystemTime().Format("%#m/%#d/%Y");
	cell.SetText(strTemp);
	cell.SetCellType(m_dtpControlID);
	cell.SetReadOnly(FALSE);
	SetCell(EXP_ARRIVAL_DATE, lRow, &cell) ;

	GetColDefault(MAT_STATUS, &cell) ;
	CString strChoices = "" ;
	m_setMatStatus.m_strFilter = "";
	m_setMatStatus.Requery();
	while (!m_setMatStatus.IsEOF())
	{
		strChoices += m_setMatStatus.m_Status;
		strChoices += "\n" ;
		m_setMatStatus.MoveNext() ;
	}

	strChoices.MakeUpper() ;
	cell.SetLabelText(strChoices);
	cell.SetText("UNKNOWN");
	SetCell(MAT_STATUS, lRow, &cell) ;

	// set up the UOM cell to be a drop list
	strChoices = "" ;
	GetColDefault(UOM, &cell) ;
	m_setUOM.m_strFilter = "";
	m_setUOM.m_strSort = "Description";
	m_setUOM.Requery();

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

	cell.SetReadOnly(FALSE) ;
	cell.SetCellType( UGCT_DROPLIST);
	cell.SetLabelText(strChoices);
	SetCell(UOM, lRow, &cell);

	GetColDefault(QUANTITY, &cell);
	cell.SetNumberDecimals(iDecimals);
	cell.SetReadOnly(FALSE);
	SetCell(QUANTITY, lRow, &cell);

	QuickSetNumber(ENTRY_METHOD_ID, lRow, CGlobals::ENTRY_MANUAL);
	QuickSetBool(DELETED, lRow, false);

	UpdateRowColor(lRow);
	UpdateRowHeights() ;

	RedrawAll();

	return iReturn ;
}

void CGridSOMerchandise::UpdateRowColor(long lRow)
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

int CGridSOMerchandise::GetFirstColumnIndex()
{
	return ID + 1;
}

int CGridSOMerchandise::GetLastColumnIndex()
{
	return LAST;
}

int CGridSOMerchandise::OnHint(int col, long row, int section, CString *string, int *maxwidth)
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

int CGridSOMerchandise::OnMenuStart(int /* col */, long row, int section)
{
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
		if ((row >= 0) && (row < GetNumberRows()))
		{
			if ((!QuickGetBool(DELETED, row)) && ((QuickGetNumber(ENTRY_METHOD_ID, row) == CGlobals::ENTRY_MANUAL) || m_bCanModifyImported))
			{
				AddMenuItem(2000, "Delete") ;
			}
			if ((QuickGetBool(DELETED, row)) && ((QuickGetNumber(ENTRY_METHOD_ID, row) == CGlobals::ENTRY_MANUAL) || m_bCanModifyImported))
			{
				AddMenuItem(2001, "Undelete") ;
			}
			AddMenuItem(3000, "Transfer To Another PO");
			if ( GetSelectedRows() == 1 )
			{
                AddMenuItem(1003, "Split Line Item");
			}
			if (row >= 0)
			{
				if  (QuickGetBool(REVIEWED, row) == FALSE)
				{
					// DKB this needs to be made more clear.  We are using the m_bAllowStatusUpdate variable for two
					// different purposes.  This variable is true for those materials that do not get checked in the 
					// normal way through the material status dialog.  Also, these same materials should allow a user to
					// mark all of them REVIEWED/UNREVIEWED at the same time, instead of clicking on each row individually.

					// In a future code change, we should set a flag in the database on the materials that should allow
					// bulk changing of the reviewed flag.  Use a separate variable for this...

					// when m_bAllowStatusUpdate is TRUE, we allow user to update the status directly via the drop-down
					// instead of having to go through the Material Status dialog.
					if (m_bAllowStatusUpdate)
					{
						// add the menu item - if m_bCanMarkReviewed is FALSE, then gray it out.
						// this doesn't care if multiple items are selected.
						AddMenuItem(3001, "Mark Reviewed", !m_bCanMarkReviewed);
					}
					else
					{
						// if we don't allow direct status changes, then we add the menu item.  GRAY it out 
						// if either user doesn't have permissions, or if more then one item is selected.
						AddMenuItem(3001, "Mark Reviewed", !m_bCanMarkReviewed || GetSelectedRows() > 1);
					}
				}
				else
				{
					// DKB this needs to be made more clear.  We are using the m_bAllowStatusUpdate variable for two
					// different purposes.  This variable is true for those materials that do not get checked in the 
					// normal way through the material status dialog.  Also, these same materials should allow a user to
					// mark all of them REVIEWED/UNREVIEWED at the same time, instead of clicking on each row individually.

					// In a future code change, we should set a flag in the database on the materials that should allow
					// bulk changing of the reviewed flag.  Use a separate variable for this...

					// when m_bAllowStatusUpdate is TRUE, we allow user to update the status directly via the drop-down
					// instead of having to go through the Material Status dialog.
					if (m_bAllowStatusUpdate)
					{
						// add the menu item - if m_bCanMarkReviewed is FALSE, then gray it out.
						// this doesn't care if multiple items are selected.
						AddMenuItem(3001, "Mark Un-Reviewed", !m_bCanMarkReviewed);
					}
					else
					{
						// if we don't allow direct status changes, then we add the menu item.  GRAY it out 
						// if either user doesn't have permissions, or if more then one item is selected.
						AddMenuItem(3001, "Mark Un-Reviewed", !m_bCanMarkReviewed || GetSelectedRows() > 1);
					}
				}
			}
			if (!QuickGetBool(DELETED, row))
			{
				AddMenuItem(9999, "Print Label");
			}

		}
	}
	return TRUE ;
}

void CGridSOMerchandise::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		// The user has selected the 'New' option
		if (item == 1000)
		{
			AppendRow() ;
		}
		else if (item == 1003)
		{
			SplitLineItem(row);
		}
		else if (item == 9999)
		{
			PrintLabels();
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
			while( pos )
			{
				long lRow = m_listRows.GetNext(pos);
				if (QuickGetBool(REVIEWED, lRow) == FALSE)
				{
					QuickSetBool(REVIEWED, lRow, true);
				}
				else
				{
					QuickSetBool(REVIEWED, lRow, false);
				}
			}
			IsRowDirty(row);
		}
	}
	RedrawAll() ;
}


void CGridSOMerchandise::ShowDeleted(bool bShowDeleted) 
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

bool CGridSOMerchandise::SplitLineItem(long row)
{
	bool bSplitOK = true;

	CDlgSplitLineItem dlg;

	CUGCell cell;
	GetCell(QUANTITY, row, &cell);
	dlg.SetNumDecimals(cell.GetNumberDecimals());

	double dCurrentQty = cell.GetNumber();
	double dPreSplitQty = 0.0;
	

	int iOriginalID = (int)QuickGetNumber(ORIGINAL_ID, row);
    if (iOriginalID != -1)
	{
		// previously split item
		dPreSplitQty = QuickGetNumber(PRESPLIT_QTY, row);
	}

	dlg.SetTotalAmount(dCurrentQty);
	dlg.SetSplitText("Enter the amount you wish to split from this line item.");

	if (dlg.DoModal() == IDOK)
	{
		double dNewAmount = dlg.GetNewAmount();
		double dBalance = dCurrentQty - dNewAmount;
		int iResult = UG_ERROR;

		long NumRows = GetNumberRows();

		long newrow;

		if (row == NumRows - 1)
		{
			iResult = AppendRow();
			newrow = GetNumberRows() - 1;
		}
		else
		{
			iResult = InsertRow(row + 1);
			newrow = row+1;
		}

		if (iResult == UG_SUCCESS)
		{
			GetCell(ORIGINAL_ID, row, &cell);
			SetCell(ORIGINAL_ID, newrow, &cell);
			if (iOriginalID == -1)
			{
				// unsplit item, so update both rows
				QuickSetNumber(ORIGINAL_ID, row, QuickGetNumber(ID, row));
				QuickSetNumber(ORIGINAL_ID, newrow, QuickGetNumber(ID, row));
				QuickSetNumber(PRESPLIT_QTY, row, dCurrentQty);
				QuickSetNumber(PRESPLIT_QTY, newrow, dCurrentQty);
			}
			else
			{
				// previously split item, so just update the new row
				QuickSetNumber(ORIGINAL_ID, newrow, iOriginalID);
				QuickSetNumber(PRESPLIT_QTY, newrow, dPreSplitQty);
			}

			// set the new amount for the current row
			QuickSetNumber(QUANTITY, row, dNewAmount);
						
			// set the amount for the new row
			GetCell(QUANTITY, row, &cell);
			SetCell(QUANTITY, newrow, &cell);
			QuickSetNumber(QUANTITY, newrow, dBalance);
			QuickSetNumber(ORG_QUANTITY, newrow, dBalance);

			// mark the entry method to hand modified
			double EntryMethod = QuickGetNumber(ENTRY_METHOD_ID, row);
			double NewEntryMethod = EntryMethod;

			if (EntryMethod == CGlobals::ENTRY_SOSI_IMPORTED)
			{
				NewEntryMethod = CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED;
			}
			else if (EntryMethod == CGlobals::ENTRY_SPN_IMPORTED)
			{
				NewEntryMethod = CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED;
			}
			
			QuickSetNumber(ENTRY_METHOD_ID, row, NewEntryMethod);

            GetCell(ENTRY_METHOD_ID, row, &cell);
			SetCell(ENTRY_METHOD_ID, newrow, &cell);

			GetCell(ORG_ENTRY_METHOD_ID, row, &cell);
			SetCell(ORG_ENTRY_METHOD_ID, newrow, &cell);

			QuickSetNumber(ORG_ENTRY_METHOD_ID, newrow, QuickGetNumber(ENTRY_METHOD_ID, newrow)); 
									
			// copy the data to the new row
			GetCell(SO_NUMBER, row, &cell);
			SetCell(SO_NUMBER, newrow, &cell);

			GetCell(ORG_SO_NUMBER, row, &cell);
			SetCell(ORG_SO_NUMBER, newrow, &cell);

			GetCell(UOM, row, &cell);
			SetCell(UOM, newrow, &cell);

			GetCell(ORG_UOM, row, &cell);
			SetCell(ORG_UOM, newrow, &cell);
			
			GetCell(SKU_NUMBER, row, &cell);
			SetCell(SKU_NUMBER, newrow, &cell);

			GetCell(ORG_SKU_NUMBER, row, &cell);
			SetCell(ORG_SKU_NUMBER, newrow, &cell);
			
			GetCell(DESCRIPTION, row, &cell);
			SetCell(DESCRIPTION, newrow, &cell);

			GetCell(ORG_DESCRIPTION, row, &cell);
			SetCell(ORG_DESCRIPTION, newrow, &cell);
			
			GetCell(EXP_ARRIVAL_DATE, row, &cell);
			SetCell(EXP_ARRIVAL_DATE, newrow, &cell);

			GetCell(ORG_EXP_ARRIVAL_DATE, row, &cell);
			SetCell(ORG_EXP_ARRIVAL_DATE, newrow, &cell);
			
			GetCell(MAT_STATUS, row, &cell);
			SetCell(MAT_STATUS, newrow, &cell);

			GetCell(ORG_MAT_STATUS, row, &cell);
			SetCell(ORG_MAT_STATUS, newrow, &cell);
			
			GetCell(BASIC_LABOR_ID, row, &cell);
			SetCell(BASIC_LABOR_ID, newrow, &cell);

			GetCell(SHORT_DESCRIPTION, row, &cell);
			SetCell(SHORT_DESCRIPTION, newrow, &cell);

			GetCell(SO_LINE_NUMBER, row, &cell);
			SetCell(SO_LINE_NUMBER, newrow, &cell);

			GetCell(SO_MER_LINE_NUMBER, row, &cell);
			SetCell(SO_MER_LINE_NUMBER, newrow, &cell);

			GetCell(DELETED, row, &cell);
			SetCell(DELETED, newrow, &cell);

			GetCell(ORG_DELETED, row, &cell);
			SetCell(ORG_DELETED, newrow, &cell);

			GetCell(REVIEWED, row, &cell);
			SetCell(REVIEWED, newrow, &cell);

			GetCell(ORG_REVIEWED, row, &cell);
			SetCell(ORG_REVIEWED, newrow, &cell);

			UpdateRowColor(row);
			UpdateRowColor(newrow);

			UpdateRowHeights() ;
			RedrawAll();
		}
	}

	return bSplitOK;
}

bool CGridSOMerchandise::PrintLabels()
{
	// this function adds to a master list the entries to be deleted. it makes no changes
	// to the database - in case the user later cancels the changes, we don't end up with
	// a db out of whack.  If CommitChanges() is called, then that is when the db is updated.
	bool bTransferOK = true;

	// init the list of selected rows
	GetSelectedRows();

	// get the current orderid
	POSITION pos = m_listRows.GetHeadPosition();
	while (pos)
	{
		long row = m_listRows.GetNext(pos);
		long lOrderID = GetDetailID(row);

		bTransferOK &= CGlobals::PrintSOLabel(lOrderID);
	}


	return bTransferOK;
}

bool CGridSOMerchandise::TransferMaterials()
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

void CGridSOMerchandise::CommitChanges()
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
			strSQL.Format("UPDATE OrderSOMerchandiseDetails SET OrderID = %d WHERE ID = %d", sTransferRow.lNewOrderID, sTransferRow.lID);
			g_dbFlooring.ExecuteSQL(strSQL);
		}
	}

	// any more db changes go here...

}


bool CGridSOMerchandise::IsColumnDirty(int iCol, long lRow)
{
	bool bDirty = true ;

	switch (iCol)
	{
	case SO_NUMBER :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(SO_NUMBER, lRow, &str1) ;
			QuickGetText(ORG_SO_NUMBER, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

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

	case EXP_ARRIVAL_DATE :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(EXP_ARRIVAL_DATE, lRow, &str1) ;
			QuickGetText(ORG_EXP_ARRIVAL_DATE, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
		break ;

	case MAT_STATUS :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(MAT_STATUS, lRow, &str1) ;
			QuickGetText(ORG_MAT_STATUS, lRow, &str2) ;
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
		bDirty = QuickGetBool(NOT_NEEDED, lRow) != QuickGetBool(ORG_NOT_NEEDED, lRow) ; 
		break ;
	}

	return bDirty ;
}

bool CGridSOMerchandise::IsRowDirty(long lRow)
{
	bool bDirty = false ;
//	enum {ID = -1, LABOR_DESC, QUANTITY, UOM, RETAIL, EXTENSION, PRICE, COST, ON_INV, ON_WO, ENTRY_METHOD_ID, DELETED, 

	if (!bDirty) bDirty = IsColumnDirty(SO_NUMBER, lRow) ; 
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

	if (!bDirty) bDirty = IsColumnDirty(MAT_STATUS, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(EXP_ARRIVAL_DATE, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(ENTRY_METHOD_ID, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(DELETED, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(REVIEWED, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(NOT_NEEDED, lRow) ;

	CString strId ;
	QuickGetText(ID, lRow, &strId) ;
	if (strId.GetLength() == 0)
	{
		bDirty = true;
	}

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

void CGridSOMerchandise::UpdateRowHeights()
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

long CGridSOMerchandise::GetDetailID(const long lRow)
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

int CGridSOMerchandise::RedrawAll()
{
	UpdateColors() ;
	UpdateRowHeights() ;
	return CGridPOBase::RedrawAll() ;
}

bool CGridSOMerchandise::HasUnknownStatus()
{
	bool _hasunknownstatus = false;

	long lNumRows = GetNumberRows();
	if (lNumRows >= 0)
	{
		for (long lRow = 0; lRow < lNumRows; lRow++)
		{
			CString strMerchStatus = QuickGetText(MAT_STATUS, lRow);
			if (strMerchStatus.MakeUpper().Find("UNKNOWN") != -1)
			{
				_hasunknownstatus = true;
				break;
			}
		}
	}

	return _hasunknownstatus;
}