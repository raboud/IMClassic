/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridLabor.cpp: implementation of the CGridLabor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>

#include "Flooring.h"
#include "GridLabor.h"

#include "SetMaterialType.h"
#include "SetOrderBasicLaborDetails.h"
#include "SetOrderOptionsDetails.h"
#include "SeOrderCustomDetails.h"
#include "SetMatStatus.h"
#include "setbasiclabor.h"
#include "setoptions.h"
#include "setstores.h"

#include "pricing.h"
#include "DlgSplitLineItem.h"
#include "SetDiscrepancies.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char szBASIC_LABOR_PREFIX[] = "B";
const char szOPTIONAL_LABOR_PREFIX[] = "O";
const char szCUSTOM_LABOR_PREFIX[] = "C";
const int iPREFIX_LENGTH = 1;
const int iBASIC_LABOR_DETAIL_ID = 12;
const int iOPTIONAL_LABOR_DETAIL_ID = 4;
const int iCUSTOM_LABOR_DETAIL_ID = 13;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGridLabor, CGridPOBase)
	//{{AFX_MSG_MAP(CGridLabor)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CGridLabor::CGridLabor()
: m_setBasicLabor(&g_dbFlooring), m_setOptions(&g_dbFlooring), m_setUOM(&g_dbFlooring)
{
	m_setBasicLabor.m_strFilter = "BasicLaborID = -1";
	m_setBasicLabor.Open() ;
	
	m_setOptions.m_strFilter = "OptionID = -1";
	m_setOptions.Open();

	m_setUOM.m_strFilter = "UnitOfMeasureID = -1";
	m_setUOM.Open();
	
	m_bShowActiveOnly = false;
	m_bShowDeleted = false ;
	m_bShowCfiPrice = false ;
	m_bShowUnitCost = false ;

	ASSERT(strcmp(szBASIC_LABOR_PREFIX, szOPTIONAL_LABOR_PREFIX) != 0);
	ASSERT(strcmp(szBASIC_LABOR_PREFIX, szCUSTOM_LABOR_PREFIX) != 0);
	ASSERT(strcmp(szOPTIONAL_LABOR_PREFIX, szCUSTOM_LABOR_PREFIX) != 0);
	ASSERT(strlen(szBASIC_LABOR_PREFIX) == iPREFIX_LENGTH);
	ASSERT(strlen(szOPTIONAL_LABOR_PREFIX) == iPREFIX_LENGTH);
	ASSERT(strlen(szCUSTOM_LABOR_PREFIX) == iPREFIX_LENGTH);
}

CGridLabor::~CGridLabor()
{
	m_setBasicLabor.Close() ;
	m_setOptions.Close();
}

void CGridLabor::OnSetup()
{
	CGridPOBase::OnSetup();

	AddColumn("   ID   ",												ID,						-1);

	AddColumn("LABOR DESCRIPTION                                    ",	LABOR_DESC,				-1);
	AddColumn("QUANTITY",												QUANTITY,				-1);
	AddColumn("   UOM   ",												UOM,					-1);
	AddColumn(" RETAIL ",												RETAIL,					-1);
	AddColumn("  PRICE   ",												PRICE,					-1);
	AddColumn("  COST  ",												COST,					-1);
	AddColumn(" EXTENSION ",											EXTENSION,				-1);
	AddColumn("ON INV.",												ON_INV,					-1);
	AddColumn("ON W.O.",												ON_WO,					-1);
	AddColumn("ENTRY_METHOD",											ENTRY_METHOD_ID,		-1);
	AddColumn("DELETED",												DELETED,				-1);
	AddColumn("REVIEWED",												REVIEWED,               -1);

	AddColumn("LABOR",													ORG_LABOR_DESC,			-1); 
	AddColumn("QUANTITY",												ORG_QUANTITY,			-1);
	AddColumn("UOM",													ORG_UOM,				-1);
	AddColumn("RETAIL",													ORG_RETAIL,				-1);
	AddColumn("PRICE",													ORG_PRICE,				-1);
	AddColumn("COST",													ORG_COST,				-1);
	AddColumn("EXT",													ORG_EXTENSION,			-1);
	AddColumn("INV",													ORG_ON_INV,				-1);
	AddColumn("WO",														ORG_ON_WO,				-1);
	AddColumn("ENTRY",													ORG_ENTRY_METHOD_ID,	-1);
	AddColumn("DELETE",													ORG_DELETED,			-1);
	AddColumn("REVIEWED",												ORG_REVIEWED,           -1);

	SetTH_NumberRows(1);
	SetTH_Height(24);
	SetTH_RowHeight(-1,12);
	SetSH_NumberCols(1);
	
	InitColumnHeadings();

	EnableMenu(TRUE) ;

	CUGCell cell;
	
	GetColDefault(ID, &cell);
	cell.SetNumberDecimals(0) ;
	cell.SetReadOnly(TRUE) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(LABOR_DESC, &cell);
	cell.SetReadOnly(TRUE) ;
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	SetColDefault(LABOR_DESC, &cell);
	SetColDefault(ORG_LABOR_DESC, &cell);

	GetColDefault(QUANTITY, &cell);
	cell.SetReadOnly(TRUE) ;
	cell.SetNumberDecimals(2) ;
	cell.SetFormatClass(&m_formatNumeric) ;
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	SetColDefault(QUANTITY, &cell) ;
	SetColDefault(ORG_QUANTITY, &cell);

	GetColDefault(UOM, &cell);
	cell.SetReadOnly(TRUE);
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(UOM, &cell);
	SetColDefault(ORG_UOM, &cell);

	GetColDefault(RETAIL, &cell);
	cell.SetNumberDecimals(2) ;
	cell.SetFormatClass(&m_formatCurrency) ;
	cell.SetReadOnly(TRUE) ;
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	SetColDefault(RETAIL, &cell) ;
	SetColDefault(ORG_RETAIL, &cell);
	SetColDefault(EXTENSION, &cell) ;
	SetColDefault(ORG_EXTENSION, &cell);
	SetColDefault(PRICE, &cell) ;
	SetColDefault(ORG_PRICE, &cell);
	SetColDefault(COST, &cell) ;
	SetColDefault(ORG_COST, &cell);

	GetColDefault(ON_INV, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(ON_INV, &cell) ;
	SetColDefault(ON_WO, &cell) ;
	SetColDefault(ORG_ON_INV, &cell);
	SetColDefault(ORG_ON_WO, &cell);

	GetColDefault(DELETED, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(DELETED, &cell) ;
	SetColDefault(ORG_DELETED, &cell);
	
	GetColDefault(REVIEWED, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
	cell.SetReadOnly(TRUE) ;
	SetColDefault(REVIEWED, &cell);
	SetColDefault(ORG_REVIEWED, &cell);

	ShowCFIPrice(m_bShowCfiPrice) ;
	ShowUnitCost(m_bShowUnitCost) ;

	HideColumn(ENTRY_METHOD_ID);
	HideColumn(DELETED);

	HideColumn(ORG_LABOR_DESC);
	HideColumn(ORG_QUANTITY);
	HideColumn(ORG_UOM);
	HideColumn(ORG_RETAIL);
	HideColumn(ORG_EXTENSION);
	HideColumn(ORG_PRICE);
	HideColumn(ORG_COST);
	HideColumn(ORG_ON_INV);
	HideColumn(ORG_ON_WO);
	HideColumn(ORG_ENTRY_METHOD_ID);
	HideColumn(ORG_DELETED) ;
	HideColumn(REVIEWED) ;
	HideColumn(ORG_REVIEWED) ;

	RECT rect = {0,0,0,0};
	// Create a mask edit to use with ultimate grid mask edit
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);
	m_editUpper.Create(WS_VISIBLE | ES_UPPERCASE, rect, this, 125);

	UseHints(TRUE);

	SetDoubleBufferMode(TRUE);
}

void CGridLabor::SetMaterialType(long lMaterialType, bool bShowActiveOnly/* = false*/)
{
	m_lMaterialType = lMaterialType ;
	m_bShowActiveOnly = bShowActiveOnly;
	FilterBasicLabor();
	
	// init the custom labor and cost multiplier values
	CSetMaterialType setType(&g_dbFlooring) ;
	setType.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType) ;
	setType.Open() ;
	m_fMultiplier = setType.m_CustomMultiplier ;
	m_fCostMultiplier = setType.m_CostMultiplier ;
	setType.Close() ;
}

void CGridLabor::FilterBasicLabor()
{
	if (m_bShowActiveOnly)
	{
		m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d' AND [Active] = 1", m_lMaterialType ) ;
	}
	else
	{
		m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
	}
	m_setBasicLabor.m_strSort = "[LaborDescription]" ;
	if (m_setBasicLabor.IsOpen())
	{
		m_setBasicLabor.Requery() ;
	}
	else
	{
		m_setBasicLabor.Open() ;
	}
	RedrawAll() ;
}

void CGridLabor::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	StartEdit();
}

void CGridLabor::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	UNREFERENCED_PARAMETER(oldcol);

	if (oldrow >= 0)
	{
		::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;
		RedrawAll() ;
	}
}

int CGridLabor::OnCellTypeNotify(long ControlID, int col, long row, long msg, long param)
{
	if (m_bConsolidatedView)
	{
		return true;
	}

	if ((ControlID == UGCT_DROPLIST) && (msg == UGCT_DROPLISTSELECT ) && (col == LABOR_DESC))
	{
		if (IsRowType(row, (char*) szBASIC_LABOR_PREFIX))
		{
			CString strMaterial = *(CString*) param ;

			FilterBasicLabor(strMaterial) ;

			CPricing clPricing;
			double dCost;
			double dPrice;
			bool bPriceOK = clPricing.GetBasicPrices(m_setBasicLabor.m_BasicLaborID, m_datePO, m_datePOScheduleDate, m_iStoreID, dCost, dPrice);
		
			CString strCost = "0.00";
			CString strPrice = "0.00";

			if (bPriceOK)
			{
				strPrice.Format("%4.2f", dPrice);
				strCost.Format("%4.2f", dCost);
			}

			QuickSetText(PRICE, row, strPrice) ;
			QuickSetText(COST, row, strCost) ;

			SetUomId(m_setBasicLabor.m_UnitOfMeasureID);
			QuickSetText(UOM, row, m_setUOM.m_Description) ;

			::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;
		}
		else if (IsRowType(row, (char*)szOPTIONAL_LABOR_PREFIX))
		{
			CUGCell cell;
			CString strOptionDescription = *(CString*) param ;

			FilterOptions(strOptionDescription) ;

			CPricing clPricing;
			double dCost;
			double dPrice;
			bool bPriceOK = clPricing.GetOptionPrices(m_setOptions.m_OptionID, m_datePO, m_datePOScheduleDate, m_iStoreID, dCost, dPrice);

			CString strCost = "0.00";
			CString strPrice = "0.00";

			if (bPriceOK)
			{
				strPrice.Format("%4.2f", dPrice);
				strCost.Format("%4.2f", dCost);
			}

			QuickSetText(COST, row, strCost) ;
			QuickSetText(PRICE, row, strPrice) ;
			if (HasImportedItems())
			{
				QuickSetBool(ON_INV, row, false ) ;
			}
			else
			{
				QuickSetBool(ON_INV, row, (m_setOptions.m_PrintOnInvoice == 1) ) ;
			}
			QuickSetBool(ON_WO, row, (m_setOptions.m_PrintOnWorkOrder == 1) );

			SetUomId(m_setOptions.m_UnitOfMeasureID);
			QuickSetText(UOM, row, m_setUOM.m_Description) ;

			GetCell(QUANTITY, row, &cell) ;
			cell.SetReadOnly(FALSE) ;
			cell.SetNumberDecimals(m_setUOM.m_NumberOfDecimals) ;
			SetCell(QUANTITY, row, &cell) ;

			::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;
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
	else if ((col == ON_INV || col == ON_WO) && msg == UGCT_CHECKBOXSET)
	{
		if (col == ON_INV)
		{
			if ( IsRowType(row, (char*)szBASIC_LABOR_PREFIX) ||
				 IsRowType(row, (char*)szOPTIONAL_LABOR_PREFIX) ||
				 IsRowType(row, (char*)szCUSTOM_LABOR_PREFIX))
			{
				// see if this PO has any Imported items
				if (HasImportedItems())
				{
					// disallow adding a basic labor item to the invoice
					QuickSetBool(ON_INV, row, false);			
				}
			}
		}
		::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;
	}
	QuickSetNumber(EXTENSION, row, CalculateRowRetail(row)) ;
	IsRowDirty(row) ;
	RedrawAll() ;  
	TRACE("OnCellTypeNotify(): controlid = %d, col = %d, msg = %d\n", ControlID, col, msg);
	return TRUE ;
}

int CGridLabor::OnEditStart(int col, long row, CWnd **edit)
{
	BOOL bCanEdit = FALSE;

	if (m_bConsolidatedView)
	{
		return FALSE;
	}

	double dEntryMethod = QuickGetNumber(ENTRY_METHOD_ID, row);
	if (dEntryMethod != 1)  // auto import
	{
		//if ((m_bCanModifyImported) || ((col == COST) && (IsRowType(row, (char*)szCUSTOM_LABOR_PREFIX)) && m_bCanEditCustomCost))
		if (m_bCanModifyImported || ((col == COST) && m_bCanEditLaborCost) || ((col == COST) && (IsRowType(row, (char*)szCUSTOM_LABOR_PREFIX)) && m_bCanEditCustomCost)) 
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

			case RETAIL:
				if (IsRowType(row, (char*)szCUSTOM_LABOR_PREFIX))
				{
					*edit = &m_editNumeric ;
				}
				else
				{
					bCanEdit = FALSE;
				}
				break ;

			case LABOR_DESC :
				if (IsRowType(row, (char*)szCUSTOM_LABOR_PREFIX))
				{
					CUGEdit* editClass = (CUGEdit*)GetEditClass();
					editClass->LimitText(200);
					editClass->ModifyStyle(0, ES_UPPERCASE);
				}
				else
				{
					bCanEdit = FALSE;
				}
				break;

			case COST :
				//if (IsRowType(row, (char*)szCUSTOM_LABOR_PREFIX) && m_bCanEditCustomCost)
				//if (m_bCanEditLaborCost)
				//{
					*edit = &m_editNumeric ;
				//}
				//else
				//{
				//	bCanEdit = FALSE;
				//}
				break ;

			default:
				bCanEdit = FALSE;
				break;
		}
	}

	return bCanEdit;
}

int CGridLabor::OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag) 
{
	UNREFERENCED_PARAMETER(cancelFlag);
	UNREFERENCED_PARAMETER(edit);

	bool bChanged = false;
	CString tempstr(string);
	CUGCell cell;
	GetCellIndirect(col, row, &cell);
	CString strOld;
	if ((col == RETAIL) && (IsRowType(row, (char*) szCUSTOM_LABOR_PREFIX)))
	{
		double dRetail = atof(string) ;
		QuickSetNumber(PRICE, row, dRetail * m_fMultiplier) ;
		QuickSetNumber(COST, row, dRetail * m_fMultiplier * m_fCostMultiplier) ;
	}
	if ((col == COST) && (IsRowType(row, (char*) szCUSTOM_LABOR_PREFIX)))
	{
		strOld = QuickGetText(col, row);
		double dCost = atof(string) ;
		double dPrice = QuickGetNumber(PRICE, row) ;
		if (dPrice < dCost)
		{
			if (MessageBox("You are attempting to pay the installer more money than we are getting paid. Is this correct?", "Cost", MB_YESNO) == IDNO)
			{
				QuickSetText(col, row, strOld) ;
				return FALSE ;
			}
		}
	}
	if (cell.GetDataType() == UGCELLDATA_STRING)
	{
		strOld = QuickGetText(col, row);
		bChanged = strOld != tempstr;
	}

	QuickSetText(col, row, string) ;

	QuickSetNumber(EXTENSION, row, CalculateRowRetail(row)) ;

	IsRowDirty(row) ;
	RedrawAll() ;

	return TRUE;
}

void CGridLabor::OnKillFocus(CWnd* /* pOldWnd */ )
{
	// called when an edit field loses focus back to the grid cell
	::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;
}

void CGridLabor::ShowDeleted(bool bShowDeleted) 
{
	m_bShowDeleted = bShowDeleted ; 

	RedrawAll() ;
}

void CGridLabor::ShowUnitCost(bool bShowUnitCost) 
{
	m_bShowUnitCost = bShowUnitCost ;

	if (bShowUnitCost)
	{
		ShowColumn(COST) ;
	}
	else
	{
		HideColumn(COST);
	}
	RedrawAll() ;
}

void CGridLabor::RecalculateRows()
{
	long lNumRows = GetNumberRows();
	CString strId;
	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		double fExtension = CalculateRowRetail(lRow);
		QuickSetNumber(EXTENSION, lRow, fExtension) ;
		
	}

	RedrawAll() ;
}


BOOL CGridLabor::OnCanMove(int /* oldcol */, long /* oldrow */, int newcol, long newrow )
{
	BOOL bOk = true ;

	switch(newcol)
	{
		case PRICE: 
		case EXTENSION:
			bOk = false;
			break;

		case COST:
			{
				if ( (IsRowType(newrow, (char*)szCUSTOM_LABOR_PREFIX) && m_bCanEditCustomCost) || m_bCanEditLaborCost)
				{
					bOk = true ;
				}
				else
				{
					bOk = false;
				}
			}
			break;

		case RETAIL:
			{
				if (!IsRowType(newrow, (char*)szCUSTOM_LABOR_PREFIX))
				{
					bOk = false ;
				}
			}
			break ;
	}
	return bOk ;
}

double CGridLabor::CalculatePrice(bool bOnlyBasic)
{
	long lRow ;
	double fPrice = 0 ;

	for (lRow = 0; lRow < GetNumberRows() ; lRow++)
	{
		if (bOnlyBasic)
		{
			if (IsRowType(lRow, (char*)szBASIC_LABOR_PREFIX))
			{
				fPrice += CalculateRowPrice(lRow) ;
			}
		}
		else
		{
			fPrice += CalculateRowPrice(lRow) ;
		}
	}

	return fPrice ;
}

double CGridLabor::CalculateRowPrice(long lRow, bool bOnInvoiceOnly /* = true */)
{
	double fPrice = 0;
	double fQuantity = 0;
	double fExtension = 0 ;

	if ( ((bOnInvoiceOnly == true) && QuickGetBool(ON_INV, lRow) && !QuickGetBool(DELETED, lRow)) || (bOnInvoiceOnly == false))
	{
		fQuantity = QuickGetNumber(QUANTITY, lRow) ;
		fPrice = QuickGetNumber(PRICE, lRow) ;
		fExtension = fQuantity * fPrice ;
	}

	return fExtension;
}

double CGridLabor::CalculateRowRetail(long lRow)
{
	double fRetail = 0 ;
	double fQuantity = 0 ;
	double fExtension = 0 ;

	fQuantity = QuickGetNumber(QUANTITY, lRow) ;
	fRetail = QuickGetNumber(RETAIL, lRow) ;

	fExtension = Currency(fQuantity * fRetail) ;
	return fExtension;
}


void CGridLabor::FilterBasicLabor(long lRow)
{
	CString strDescription = QuickGetText(LABOR_DESC, lRow) ;
	FilterBasicLabor(strDescription) ;
}

void CGridLabor::FilterBasicLabor(CString strLaborDescription)
{
	strLaborDescription.Replace("'", "''");
	m_setBasicLabor.m_strFilter.Format("[MaterialTypeID] = '%d' and [LaborDescription] = '%s'", m_lMaterialType, strLaborDescription ) ;
	m_setBasicLabor.Requery() ;
}

int CGridLabor::DeleteRow(long lRow)
{	
	//long lStatus = CGridPOBase::DeleteRow(lRow) ;
	long lStatus = TRUE;

	CString strId = QuickGetText(ID, lRow) ;
	if (strId.GetLength() == iPREFIX_LENGTH)
	{
		CCFGrid::DeleteRow(lRow) ;
	}
	else
	{
		QuickSetBool(DELETED, lRow, true);
		QuickSetCellType(LABOR_DESC, lRow, UGCT_NORMAL);
		QuickSetReadOnly(LABOR_DESC, lRow, true);
		QuickSetReadOnly(QUANTITY, lRow, true);
		QuickSetReadOnly(UOM, lRow, true);
		QuickSetReadOnly(ON_INV, lRow, true);
		QuickSetReadOnly(ON_WO, lRow, true);

		UpdateRowColor(lRow) ;
		UpdateRowHeights() ;
		IsRowDirty(lRow) ;
	}

	::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;

	return lStatus ;
}

int CGridLabor::UndeleteRow(long lRow)
{	
	//long lStatus = CGridPOBase::DeleteRow(lRow) ;
	long lStatus = TRUE;

	QuickSetBool(DELETED, lRow, false);

	// row specific init
	if (IsRowType(lRow, (char *) szBASIC_LABOR_PREFIX) || IsRowType(lRow, (char *) szOPTIONAL_LABOR_PREFIX))
	{
		QuickSetCellType(LABOR_DESC, lRow, UGCT_DROPLIST);
	}

	long lEntryMethodID = (long) QuickGetNumber(ENTRY_METHOD_ID, lRow);

	if (lEntryMethodID == CGlobals::ENTRY_MANUAL)
	{
		QuickSetReadOnly(LABOR_DESC, lRow, false);
		QuickSetReadOnly(UOM, lRow, false);
		QuickSetReadOnly(ON_INV, lRow, false);
		QuickSetReadOnly(ON_WO, lRow, false);
		QuickSetReadOnly(QUANTITY, lRow, false);
	}
	else
	{
		if (m_bCanModifyImported)
		{
			QuickSetReadOnly(QUANTITY, lRow, false);
		}
		else
		{
			QuickSetReadOnly(QUANTITY, lRow, true);
		}
	}

	if ( (IsRowType(lRow, (char *) szCUSTOM_LABOR_PREFIX) && m_bCanEditCustomCost) || m_bCanEditLaborCost )
	{
		QuickSetReadOnly(COST, lRow, false) ;
	}
	else
	{
		QuickSetReadOnly(COST, lRow, true) ;
	}

	UpdateRowColor(lRow) ;
	UpdateRowHeights() ;
	IsRowDirty(lRow) ;

	::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;

	return lStatus ;
}

void CGridLabor::UpdateRecordSet(long lOrderID)
{
	bool bUpdateOK = true;
	long lRow ;

	CSetOrderBasicLaborDetails setBasicDetails(&g_dbFlooring) ;
	setBasicDetails.m_strFilter = "ID = -1";

	CSetOrderOptionsDetails setOptionsDetails(&g_dbFlooring) ;
	setOptionsDetails.m_strFilter = "OrdeOptionslID = -1";

	CSetOrderCustomDetails setCustomDetails(&g_dbFlooring) ;
	setCustomDetails.m_strFilter = "OrderCustomID = -1";
	
	CString strTemp ;
	for (lRow = 0; lRow < GetNumberRows() ; lRow++)
	{
		if (IsRowDirty(lRow))
		{
			CString strId = QuickGetText(ID, lRow) ;
			strId.Replace("*", "") ;

			bool bNew ;
			if (IsRowType(lRow, (char*)szBASIC_LABOR_PREFIX))
			{
				try
				{

					// set the BasicLabor recordset to contain only our current item
					FilterBasicLabor(lRow) ;
					
					if (strId.GetLength() == iPREFIX_LENGTH)
					{
						if (!setBasicDetails.IsOpen())
						{
							setBasicDetails.Open() ;
						}
						setBasicDetails.AddNew() ;
						setBasicDetails.m_OrderID = lOrderID ;
						bNew = true ;
					}
					else
					{
						strTemp = strId.Mid(iPREFIX_LENGTH);
						setBasicDetails.m_strFilter.Format("[ID] = '%s'", strTemp) ;
						if (setBasicDetails.IsOpen())
						{
							setBasicDetails.Requery() ;
						}
						else
						{
							setBasicDetails.Open() ;
						}
						setBasicDetails.Edit() ;
						bNew = false ;
					}

					if (IsColumnDirty(LABOR_DESC, lRow) || bNew)
					{
						setBasicDetails.m_BasicLaborID = m_setBasicLabor.m_BasicLaborID ;
					}

					if (IsColumnDirty(RETAIL, lRow) || bNew)
					{
						setBasicDetails.m_UnitRetail = QuickGetText(RETAIL, lRow);
						setBasicDetails.m_UnitRetail.Remove('$');
					}
					
					if (IsColumnDirty(COST, lRow) || bNew)
					{
						setBasicDetails.m_UnitCost = QuickGetText(COST, lRow);
						setBasicDetails.m_UnitCost.Remove('$');
					}

					if (IsColumnDirty(PRICE, lRow) || bNew)
					{
						setBasicDetails.m_UnitPrice = QuickGetText(PRICE, lRow);
						setBasicDetails.m_UnitPrice.Remove('$');
					}

					if (IsColumnDirty(QUANTITY, lRow) || bNew)
					{
						setBasicDetails.m_InstallQuantity = QuickGetNumber (QUANTITY, lRow) ;
					}

					if (IsColumnDirty(ENTRY_METHOD_ID, lRow) || bNew)
					{
						setBasicDetails.m_EntryMethodID = (long) QuickGetNumber(ENTRY_METHOD_ID, lRow);
					}

					if (IsColumnDirty(ON_INV, lRow) || bNew)
					{
						setBasicDetails.m_PrintOnInvoice = QuickGetBool(ON_INV, lRow);
					}

					if (IsColumnDirty(ON_WO, lRow) || bNew)
					{
						setBasicDetails.m_PrintOnWO = QuickGetBool(ON_WO, lRow);
					}

					if (IsColumnDirty(DELETED, lRow) || bNew)
					{
						setBasicDetails.m_Deleted = QuickGetBool(DELETED, lRow);
					}

					bool bReviewedDirty = IsColumnDirty(REVIEWED, lRow);
					if ( bReviewedDirty || bNew)
					{
						bool bReviewed = QuickGetBool(REVIEWED, lRow);
						setBasicDetails.m_Reviewed = bReviewed;
						// if reviewed, update name/date
						// if not-reviewed and dirty, update name/date
						if ((bReviewed) || (bReviewedDirty && !bReviewed))
						{
							CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
							setBasicDetails.m_ReviewedBy = pApp->GetEmployeeID();
							setBasicDetails.m_ReviewedDate = CGlobals::GetCurrentSystemTime();
						}
					}

					setBasicDetails.Update() ;
					
				}
				catch (CException* pE)
				{
					pE->Delete() ;
					bUpdateOK = false;
				}
			}
			else if (IsRowType(lRow, (char*)szOPTIONAL_LABOR_PREFIX))
			{
				try
				{
					FilterOptions(lRow) ;
					if (strId.GetLength() == iPREFIX_LENGTH)
					{
						if (!setOptionsDetails.IsOpen())
						{
							setOptionsDetails.Open() ;
						}
						setOptionsDetails.AddNew() ;
						setOptionsDetails.m_OrderID = lOrderID ;
						bNew = true ;
					}
					else
					{
						strTemp = strId.Mid(iPREFIX_LENGTH) ;
						setOptionsDetails.m_strFilter.Format("[OrdeOptionslID] = '%s'", strTemp) ;
						if (!setOptionsDetails.IsOpen())
						{
							setOptionsDetails.Open() ;
						}
						else
						{
							setOptionsDetails.Requery() ;
						}
						setOptionsDetails.Edit() ;
						bNew = false ;
					}

					if (IsColumnDirty(LABOR_DESC, lRow) || bNew)
					{
						setOptionsDetails.m_OptionID = m_setOptions.m_OptionID ;
					}

					if (IsColumnDirty(RETAIL, lRow) || bNew)
					{
						setOptionsDetails.m_UnitRetail = QuickGetText(RETAIL, lRow);
						setOptionsDetails.m_UnitRetail.Remove('$');
					}
					
					if (IsColumnDirty(COST, lRow) || bNew)
					{
						setOptionsDetails.m_UnitCost = QuickGetText(COST, lRow);
						setOptionsDetails.m_UnitCost.Remove('$');
					}

					if (IsColumnDirty(PRICE, lRow) || bNew)
					{
						setOptionsDetails.m_UnitPrice = QuickGetText(PRICE, lRow);
						setOptionsDetails.m_UnitPrice.Remove('$');
					}

					if (IsColumnDirty(QUANTITY, lRow) || bNew)
					{
						QuickGetNumber(QUANTITY, lRow, &setOptionsDetails.m_Quantity) ;
					}

					if (IsColumnDirty(ENTRY_METHOD_ID, lRow) || bNew)
					{
						setOptionsDetails.m_EntryMethodID = (long) QuickGetNumber(ENTRY_METHOD_ID, lRow);
					}

					if (IsColumnDirty(ON_INV, lRow) || bNew)
					{
						setOptionsDetails.m_PrintOnInvoice = QuickGetBool(ON_INV, lRow);
					}

					if (IsColumnDirty(ON_WO, lRow) || bNew)
					{
						setOptionsDetails.m_PrintOnWO = QuickGetBool(ON_WO, lRow);
					}

					if (IsColumnDirty(DELETED, lRow) || bNew)
					{
						setOptionsDetails.m_Deleted = QuickGetBool(DELETED, lRow);
					}

					if (IsColumnDirty(REVIEWED, lRow) || bNew)
					{
						bool bReviewed = QuickGetBool(REVIEWED, lRow);
						setOptionsDetails.m_Reviewed = bReviewed;
						if (bReviewed)
						{
							CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
							setOptionsDetails.m_ReviewedBy = pApp->GetEmployeeID();
							setOptionsDetails.m_ReviewedDate = CGlobals::GetCurrentSystemTime();
						}
					}

					setOptionsDetails.Update() ;
				}
				catch (CException* pE)
				{
					pE->Delete() ;
					bUpdateOK = false;
				}
			}
			else if (IsRowType(lRow, (char*)szCUSTOM_LABOR_PREFIX))
			{
				try
				{
					if (strId.GetLength() == iPREFIX_LENGTH)
					{
						if (!setCustomDetails.IsOpen())
						{
							setCustomDetails.Open() ;
						}

						setCustomDetails.AddNew() ;
						setCustomDetails.m_OrderID = lOrderID ;
						bNew = true ;
					}
					else
					{
						strTemp = strId.Mid(iPREFIX_LENGTH);
						setCustomDetails.m_strFilter.Format("[OrderCustomID] = '%s'", strTemp) ;
						if (!setCustomDetails.IsOpen())
						{
							setCustomDetails.Open() ;
						}
						else
						{
							setCustomDetails.Requery() ;
						}
						setCustomDetails.Edit() ;
						bNew = false ;
					}

					if (IsColumnDirty(RETAIL, lRow) || bNew)
					{
						setCustomDetails.m_RetailPrice = QuickGetText(RETAIL, lRow);
						setCustomDetails.m_RetailPrice.Remove('$');
					}

					if (IsColumnDirty(PRICE, lRow) || bNew)
					{
						setCustomDetails.m_UnitPrice = QuickGetText(PRICE, lRow);
						setCustomDetails.m_UnitPrice.Remove('$');
					}

					if (IsColumnDirty(COST, lRow) || bNew)
					{
						setCustomDetails.m_UnitCost = QuickGetText(COST, lRow);
						setCustomDetails.m_UnitCost.Remove('$');
					}

					if (IsColumnDirty(LABOR_DESC, lRow) || bNew)
					{
						QuickGetText(LABOR_DESC,	lRow, &setCustomDetails.m_Description) ;
					}

					if (IsColumnDirty(QUANTITY, lRow) || bNew)
					{
						QuickGetNumber(QUANTITY, lRow, &setCustomDetails.m_Quanity) ;
					}

					if (IsColumnDirty(UOM, lRow) || bNew)
					{
						QuickGetText(UOM, lRow, &strTemp) ;
						GetUOMId(strTemp) ;
						setCustomDetails.m_UnitOfMeasureID = m_setUOM.m_UnitOfMeasureID ;
					}

					if (IsColumnDirty(ENTRY_METHOD_ID, lRow) || bNew)
					{
						setCustomDetails.m_EntryMethodID = (long) QuickGetNumber(ENTRY_METHOD_ID, lRow);
					}

					if (IsColumnDirty(ON_INV, lRow) || bNew)
					{
						setCustomDetails.m_NotOnInvoice = !QuickGetBool(ON_INV, lRow) ;
					}

					if (IsColumnDirty(ON_WO, lRow) || bNew)
					{
						setCustomDetails.m_NotOnWorkOrder = !QuickGetBool(ON_WO, lRow) ;
					}

					if (IsColumnDirty(DELETED, lRow) || bNew)
					{
						setCustomDetails.m_Deleted = QuickGetBool(DELETED, lRow);
					}

					if (IsColumnDirty(REVIEWED, lRow) || bNew)
					{
						bool bReviewed = QuickGetBool(REVIEWED, lRow);
						setCustomDetails.m_Reviewed = bReviewed;
						if (bReviewed)
						{
							CFlooringApp* pApp = (CFlooringApp*) AfxGetApp();
							setCustomDetails.m_ReviewedBy = pApp->GetEmployeeID();
							setCustomDetails.m_ReviewedDate = CGlobals::GetCurrentSystemTime();
						}
					}
					setCustomDetails.Update() ;
				}
				catch (CException* pE)
				{
					pE->Delete() ;
					bUpdateOK = false;
				}
			}
		}
	}

	// remove any records from the record sets marked for deletion
	DeleteRecordList(setBasicDetails, "[ID] = '%s'", szBASIC_LABOR_PREFIX) ;
	if (setBasicDetails.IsOpen())
	{
		setBasicDetails.Close() ;
	}

	DeleteRecordList(setOptionsDetails, "[OrdeOptionslID] = '%s'", szOPTIONAL_LABOR_PREFIX) ;
	if (setOptionsDetails.IsOpen())
	{
		setOptionsDetails.Close() ;
	}
	
	DeleteRecordList(setCustomDetails, "[OrderCustomID] = '%s'", szCUSTOM_LABOR_PREFIX) ;
	if (setCustomDetails.IsOpen())
	{
		setCustomDetails.Close() ;
	}
}

void CGridLabor::UpdateGrid()
{
	CSetStores setStores(&g_dbFlooring) ;
	setStores.m_strFilter.Format("[StoreID] = '%d'", m_iStoreID) ;
	setStores.Open() ;

	long lMarketID = setStores.m_MarketId ;
	setStores.Close() ;

	CSetMaterialType setType(&g_dbFlooring) ;
	setType.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType) ;
	setType.Open() ;

	long lDivisionID = setType.m_DivisionID ;
	setType.Close() ;
	
	CPermissions perm;
	m_bCanEditCustomCost = perm.HasPermission("CanEditCustomCost", lMarketID, lDivisionID) ;
	m_bCanEditLaborCost = perm.HasPermission("CanEditLaborCost", lMarketID, lDivisionID);

	Reset();

	if (m_listPOs.GetCount() > 0)
	{
		long lRow = 0 ;

		CSetOrderBasicLaborDetails setBasicDetails(&g_dbFlooring) ;
		setBasicDetails.m_strFilter = m_strRecordSetFilter ;
		setBasicDetails.Open() ;

		CSetOrderOptionsDetails setOptionsDetails(&g_dbFlooring) ;
		setOptionsDetails.m_strFilter = m_strRecordSetFilter ;
		setOptionsDetails.Open() ;

		CSetOrderCustomDetails setCustomDetails(&g_dbFlooring) ;
		setCustomDetails.m_strFilter = m_strRecordSetFilter ;
		setCustomDetails.Open() ;

		while (!setBasicDetails.IsEOF())
		{
			AppendRow(szBASIC_LABOR_PREFIX) ;
			CUGCell cell ;

			long lRow = GetNumberRows() - 1;

			FilterBasicLaborByID(setBasicDetails.m_BasicLaborID) ;
			
			CString strTemp ;
			strTemp.Format("%s%d", szBASIC_LABOR_PREFIX, setBasicDetails.m_ID) ;
			QuickSetText(ID, lRow, strTemp) ;

			SetUomId(m_setBasicLabor.m_UnitOfMeasureID);
			QuickSetText(UOM, lRow, m_setUOM.m_Description) ;
			QuickSetText(ORG_UOM, lRow, m_setUOM.m_Description) ;

			GetCell(QUANTITY, lRow, &cell) ;
			cell.SetReadOnly(FALSE) ;
			cell.SetNumberDecimals(m_setUOM.m_NumberOfDecimals) ;
			SetCell(QUANTITY, lRow, &cell) ;

			strTemp = m_setBasicLabor.m_LaborDescription ;
			strTemp.MakeUpper() ;
			QuickSetText(LABOR_DESC, lRow, strTemp) ;
			QuickSetText(ORG_LABOR_DESC, lRow, strTemp) ;

			QuickSetText(COST, lRow, setBasicDetails.m_UnitCost) ;
			QuickSetText(PRICE, lRow, setBasicDetails.m_UnitPrice) ;
			QuickSetText(RETAIL, lRow, setBasicDetails.m_UnitRetail) ;
			QuickSetNumber(QUANTITY, lRow, setBasicDetails.m_InstallQuantity ) ;

			QuickSetText(ORG_COST, lRow, setBasicDetails.m_UnitCost) ;
			QuickSetText(ORG_PRICE, lRow, setBasicDetails.m_UnitPrice) ;
			QuickSetText(ORG_RETAIL, lRow, setBasicDetails.m_UnitRetail) ;
			QuickSetNumber(ORG_QUANTITY, lRow, setBasicDetails.m_InstallQuantity ) ;

			double fExtension = CalculateRowRetail(lRow);
			QuickSetNumber(EXTENSION, lRow, fExtension) ;
			QuickSetNumber(ORG_EXTENSION, lRow, fExtension) ;

			if (setBasicDetails.m_EntryMethodID != CGlobals::ENTRY_MANUAL)
			{
				QuickSetBool(ON_INV, lRow, true) ;
			}
			else
			{
				QuickSetBool(ON_INV, lRow, (setBasicDetails.m_PrintOnInvoice == 1)) ;
			}
			QuickSetBool(ORG_ON_INV, lRow, (setBasicDetails.m_PrintOnInvoice == 1)) ;
			QuickSetBool(ON_WO, lRow,  (setBasicDetails.m_PrintOnWO == 1)) ;
			QuickSetBool(ORG_ON_WO, lRow,  (setBasicDetails.m_PrintOnWO == 1)) ;

			QuickSetNumber(ENTRY_METHOD_ID, lRow, setBasicDetails.m_EntryMethodID);
			QuickSetNumber(ORG_ENTRY_METHOD_ID, lRow, setBasicDetails.m_EntryMethodID);

			QuickSetBool(DELETED, lRow, (setBasicDetails.m_Deleted == 1));
			QuickSetBool(ORG_DELETED, lRow, (setBasicDetails.m_Deleted == 1));

			QuickSetBool(REVIEWED, lRow, (setBasicDetails.m_Reviewed == TRUE));
			QuickSetBool(ORG_REVIEWED, lRow, (setBasicDetails.m_Reviewed == TRUE));


			// if XML imported, we won't let the user change anything but the "On WO" status
			if ((setBasicDetails.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED) || (setBasicDetails.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED)) // XML imported
			{
				QuickSetCellType(LABOR_DESC, lRow, UGCT_NORMAL);
				QuickSetReadOnly(LABOR_DESC, lRow, true);
				if (m_bCanModifyImported)
				{
					QuickSetReadOnly(QUANTITY, lRow, false);
				}
				else
				{
					QuickSetReadOnly(QUANTITY, lRow, true);
				}
				QuickSetReadOnly(UOM, lRow, true);
				QuickSetReadOnly(ON_INV, lRow, true);

				// only WO column is clickable
				QuickSetReadOnly(ON_WO, lRow, false);
			}
			else
			{
				// manual entered basic labor, so we allow user to edit all
				QuickSetReadOnly(ON_INV, lRow, false);
			}

			if (setBasicDetails.m_Deleted)
			{
				QuickSetCellType(LABOR_DESC, lRow, UGCT_NORMAL);
				QuickSetReadOnly(LABOR_DESC, lRow, true);
				QuickSetReadOnly(QUANTITY, lRow, true);
				QuickSetReadOnly(UOM, lRow, true);

				QuickSetBool(ON_INV, lRow, false);
				QuickSetBool(ON_WO, lRow, false);

				QuickSetReadOnly(ON_INV, lRow, true);
				QuickSetReadOnly(ON_WO, lRow, true);
			}

			lRow++ ;
			setBasicDetails.MoveNext() ;
		}
		setBasicDetails.Close() ;

		// fill in Optional Labor
		while (!setOptionsDetails.IsEOF())
		{
			AppendRow(szOPTIONAL_LABOR_PREFIX) ;
			CUGCell cell ;

			lRow = GetNumberRows() - 1;

			FilterOptionByID(setOptionsDetails.m_OptionID) ;

			CString strTemp ;
			strTemp.Format("%s%d", szOPTIONAL_LABOR_PREFIX, setOptionsDetails.m_OrdeOptionslID) ;
			QuickSetText(ID, lRow, strTemp) ;

			strTemp = m_setOptions.m_OptionDescription ;
			strTemp.MakeUpper() ;
			QuickSetText(LABOR_DESC, lRow, strTemp) ;
			QuickSetText(ORG_LABOR_DESC, lRow, strTemp) ;
			
			if (setOptionsDetails.m_EntryMethodID != CGlobals::ENTRY_MANUAL)
			{
				QuickSetBool(ON_INV, lRow, true) ;
			}
			else
			{
				QuickSetBool(ON_INV, lRow, (setOptionsDetails.m_PrintOnInvoice == 1)) ;
			}
			QuickSetBool(ORG_ON_INV, lRow, (setOptionsDetails.m_PrintOnInvoice == 1)) ;

			QuickSetBool(ON_WO, lRow, (setOptionsDetails.m_PrintOnWO == 1));
			QuickSetBool(ORG_ON_WO, lRow, (setOptionsDetails.m_PrintOnWO == 1));

			SetUomId(m_setOptions.m_UnitOfMeasureID) ;
			QuickSetText(UOM, lRow, m_setUOM.m_Description) ;
			QuickSetText(ORG_UOM, lRow, m_setUOM.m_Description) ;

			GetCell(QUANTITY, lRow, &cell) ;
			cell.SetReadOnly(FALSE) ;
			cell.SetNumberDecimals(m_setUOM.m_NumberOfDecimals) ;
			SetCell(QUANTITY, lRow, &cell) ;

			QuickSetText(COST, lRow, setOptionsDetails.m_UnitCost) ;
			QuickSetText(PRICE, lRow, setOptionsDetails.m_UnitPrice) ;
			QuickSetText(RETAIL, lRow, setOptionsDetails.m_UnitRetail) ;
			QuickSetNumber(QUANTITY, lRow, setOptionsDetails.m_Quantity) ;
			QuickSetNumber(EXTENSION, lRow, CalculateRowRetail(lRow));

			QuickSetText(ORG_COST, lRow, setOptionsDetails.m_UnitCost) ;
			QuickSetText(ORG_PRICE, lRow, setOptionsDetails.m_UnitPrice) ;
			QuickSetText(ORG_RETAIL, lRow, setOptionsDetails.m_UnitRetail) ;
			QuickSetNumber(ORG_QUANTITY, lRow, setOptionsDetails.m_Quantity) ;
			QuickSetNumber(ORG_EXTENSION, lRow, CalculateRowRetail(lRow));

			QuickSetNumber(ENTRY_METHOD_ID, lRow, setOptionsDetails.m_EntryMethodID);
			QuickSetNumber(ORG_ENTRY_METHOD_ID, lRow, setOptionsDetails.m_EntryMethodID);

			QuickSetBool(DELETED, lRow, (setOptionsDetails.m_Deleted == 1));
			QuickSetBool(ORG_DELETED, lRow, (setOptionsDetails.m_Deleted == 1));

			QuickSetBool(REVIEWED, lRow, (setOptionsDetails.m_Reviewed == TRUE));
			QuickSetBool(ORG_REVIEWED, lRow, (setOptionsDetails.m_Reviewed == TRUE));

			// if XML imported, we won't let the user change anything but the "On WO" status
			if ((setOptionsDetails.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED) || (setOptionsDetails.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED)) // XML imported
			{
				QuickSetCellType(LABOR_DESC, lRow, UGCT_NORMAL);
				QuickSetReadOnly(LABOR_DESC, lRow, true);
				if (m_bCanModifyImported)
				{
					QuickSetReadOnly(QUANTITY, lRow, false);
				}
				else
				{
					QuickSetReadOnly(QUANTITY, lRow, true);
				}
				QuickSetReadOnly(UOM, lRow, true);
				QuickSetReadOnly(ON_INV, lRow, true);

				// only WO column is clickable
				QuickSetReadOnly(ON_WO, lRow, false);
			}
			else
			{
				// manual entered basic labor, so we allow user to edit all
				QuickSetReadOnly(ON_INV, lRow, false);
			}

			if (setOptionsDetails.m_Deleted)
			{
				QuickSetCellType(LABOR_DESC, lRow, UGCT_NORMAL);
				QuickSetReadOnly(LABOR_DESC, lRow, true);
				QuickSetReadOnly(QUANTITY, lRow, true);
				QuickSetReadOnly(UOM, lRow, true);

				//QuickSetBool(ON_INV, lRow, false);
				QuickSetBool(ON_WO, lRow, false);

				QuickSetReadOnly(ON_INV, lRow, true);
				QuickSetReadOnly(ON_WO, lRow, true);
			}

			lRow++ ;
			setOptionsDetails.MoveNext() ;
		}
		setOptionsDetails.Close() ;
		
		// fill in custom labor
		while (!setCustomDetails.IsEOF())
		{
			AppendRow(szCUSTOM_LABOR_PREFIX) ;
			lRow = GetNumberRows() - 1;

			CString strTemp ;
			strTemp.Format("%s%d", szCUSTOM_LABOR_PREFIX, setCustomDetails.m_OrderCustomID) ;
			QuickSetText(ID, lRow, strTemp) ;

			SetUomId(setCustomDetails.m_UnitOfMeasureID) ;
			strTemp.Format("%s (%d)", m_setUOM.m_Description, m_setUOM.m_NumberOfDecimals);
			QuickSetText(UOM, lRow, strTemp) ;
			QuickSetText(ORG_UOM, lRow, strTemp) ;

			QuickSetNumberDecimals(QUANTITY, lRow, m_setUOM.m_NumberOfDecimals) ;

			double fExtension = CalculateRowRetail(lRow);
			QuickSetNumber(EXTENSION, lRow, fExtension) ;
			QuickSetNumber(ORG_EXTENSION, lRow, fExtension) ;

			QuickSetText(RETAIL, lRow, setCustomDetails.m_RetailPrice) ;
			QuickSetText(ORG_RETAIL, lRow, setCustomDetails.m_RetailPrice) ;

			QuickSetText(PRICE, lRow, setCustomDetails.m_UnitPrice) ;
			QuickSetText(ORG_PRICE, lRow, setCustomDetails.m_UnitPrice) ;

			QuickSetText(COST, lRow, setCustomDetails.m_UnitCost) ;
			QuickSetText(ORG_COST, lRow, setCustomDetails.m_UnitCost) ;

			QuickSetText(LABOR_DESC,	lRow, setCustomDetails.m_Description) ;
			QuickSetText(ORG_LABOR_DESC,	lRow, setCustomDetails.m_Description) ;

			QuickSetNumber(QUANTITY, lRow, setCustomDetails.m_Quanity) ;
			QuickSetNumber(ORG_QUANTITY, lRow, setCustomDetails.m_Quanity) ;

			QuickSetNumber(EXTENSION, lRow, CalculateRowRetail(lRow)) ;
			QuickSetNumber(ORG_EXTENSION, lRow, CalculateRowRetail(lRow)) ;

			QuickSetNumber(ENTRY_METHOD_ID, lRow, setCustomDetails.m_EntryMethodID);
			QuickSetNumber(ORG_ENTRY_METHOD_ID, lRow, setCustomDetails.m_EntryMethodID);

			if (setCustomDetails.m_EntryMethodID != CGlobals::ENTRY_MANUAL)
			{
                QuickSetBool(ON_INV, lRow, true) ;
			}
			else
			{
				QuickSetBool(ON_INV, lRow, (setCustomDetails.m_NotOnInvoice == FALSE)) ;
			}
			QuickSetBool(ORG_ON_INV, lRow, (setCustomDetails.m_NotOnInvoice == FALSE)) ;

			QuickSetBool(ON_WO, lRow, (setCustomDetails.m_NotOnWorkOrder == FALSE)) ;
			QuickSetBool(ORG_ON_WO, lRow, (setCustomDetails.m_NotOnWorkOrder == FALSE)) ;

			QuickSetBool(DELETED, lRow, (setCustomDetails.m_Deleted == 1));
			QuickSetBool(ORG_DELETED, lRow, (setCustomDetails.m_Deleted == 1));

			QuickSetBool(REVIEWED, lRow, (setCustomDetails.m_Reviewed == TRUE));
			QuickSetBool(ORG_REVIEWED, lRow, (setCustomDetails.m_Reviewed == TRUE));

			if (setCustomDetails.m_EntryMethodID != CGlobals::ENTRY_MANUAL)
			{
				if (!m_bCanModifyImported)
				{
					QuickSetCellType(UOM, lRow, UGCT_NORMAL);
					QuickSetReadOnly(ON_INV, lRow, true);
				}
				
				if (m_bCanModifyImported)
				{
					QuickSetReadOnly(QUANTITY, lRow, false);
				}
				else
				{
					QuickSetReadOnly(QUANTITY, lRow, true);
				}
			}

			if (setCustomDetails.m_Deleted)
			{
				QuickSetCellType(LABOR_DESC, lRow, UGCT_NORMAL);
				QuickSetReadOnly(LABOR_DESC, lRow, true);
				QuickSetReadOnly(QUANTITY, lRow, true);
				QuickSetReadOnly(UOM, lRow, true);

				QuickSetBool(ON_INV, lRow, false);
				QuickSetBool(ON_WO, lRow, false);
				QuickSetReadOnly(ON_INV, lRow, true);
				QuickSetReadOnly(ON_WO, lRow, true);
			}

			if (m_bCanEditCustomCost || m_bCanEditLaborCost)
			{
				QuickSetReadOnly(COST, lRow, false) ;
			}
			else
			{
				QuickSetReadOnly(COST, lRow, true) ;
			}

			lRow++ ;
			setCustomDetails.MoveNext() ;
		}
		setCustomDetails.Close() ;
		
		if (::IsWindow(m_hWnd))
		{
			::PostMessage((GetParent())->m_hWnd, CGlobals::WM_LABOR_UPDATE, 0, 0) ;
		}
	}
	RedrawAll() ;
}

int CGridLabor::OnMenuStart(int /* col */, long row, int section)
{
	if (m_bConsolidatedView)
	{
		return FALSE;
	}

	if (section == UG_GRID )
	{
		//* Empty the Menu!!
		EmptyMenu();

		//** Add the Menu Items
		AddMenuItem(1000,"New Basic Labor");
		AddMenuItem(1001,"New Optional Labor");
		AddMenuItem(1002,"New Custom Labor");
		if ((row >= 0) && (row < GetNumberRows()) && (!QuickGetBool(DELETED, row)) && ((QuickGetNumber(ENTRY_METHOD_ID, row) == CGlobals::ENTRY_MANUAL) || m_bCanModifyImported))
		{
			AddMenuItem(2000, "Delete") ;
		}
		if ((row >= 0) && (row < GetNumberRows()) && (QuickGetBool(DELETED, row))  && ((QuickGetNumber(ENTRY_METHOD_ID, row) == CGlobals::ENTRY_MANUAL) || m_bCanModifyImported))
		{
			AddMenuItem(2001, "Undelete") ;
		}
		if (( IsRowType(row, (char*) szBASIC_LABOR_PREFIX) || IsRowType(row, (char*) szOPTIONAL_LABOR_PREFIX)) && (!QuickGetBool(DELETED, row)))
		{
			AddMenuItem(1003, "Split Line Item");
		}
		if ((row >= 0) && (QuickGetBool(REVIEWED, row) == FALSE))
		{
			AddMenuItem(3001, "Mark Reviewed", !m_bCanMarkReviewed);
		}
		if ((row >= 0) && (QuickGetBool(REVIEWED, row) == TRUE))
		{
			AddMenuItem(3001, "Mark Un-Reviewed", !m_bCanMarkReviewed);
		}
		
	}
	return TRUE ;
}

void CGridLabor::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		// The user has selected the 'Add Basic Labor' option
		if (item == 1000)
		{
			AppendRow(szBASIC_LABOR_PREFIX) ;
		}
		else if (item == 1001)
		{
			AppendRow(szOPTIONAL_LABOR_PREFIX);
		}
		else if (item == 1002)
		{
			AppendRow(szCUSTOM_LABOR_PREFIX);
		}
		else if (item == 1003)
		{
			SplitLineItem(row);
		}
		else if (item == 2000)
		{
			DeleteRow(row) ;
		}
		else if (item == 2001)
		{
			UndeleteRow(row) ;
		}
		else if (item == 3001)
		{
			if (QuickGetBool(REVIEWED, row) == TRUE)
			{
				QuickSetBool(REVIEWED, row, false);
			}
			else
			{
				QuickSetBool(REVIEWED, row, true);
			}
			IsRowDirty(row);
		}
	}
	RedrawAll() ;
}

void CGridLabor::FilterBasicLaborByID(long lBasicLaborID)
{
	m_setBasicLabor.m_strFilter.Format("[BasicLaborID] = '%d'", lBasicLaborID ) ;
	m_setBasicLabor.Requery() ;
}

int CGridLabor::AppendRow()
{
	return AppendRow("");
}

int CGridLabor::AppendRow(CString strType)
{
	int iReturn = CGridPOBase::AppendRow() ;

	if (iReturn == UG_SUCCESS)
	{
		long lRow = GetNumberRows() - 1;
		InitRow(lRow, strType);
	}
		
	return iReturn ;
}

int CGridLabor::InsertRow(long row, CString strType)
{
	int iReturn = CGridPOBase::InsertRow(row);
	if (iReturn == UG_SUCCESS)
	{
		InitRow(row, strType);	
	}

	return iReturn;
}

void CGridLabor::InitRow(long lRow, CString strType)
{
	CUGCell cell ;
	QuickSetText(ID, lRow, strType);

	QuickSetBool(DELETED, lRow, false);

	// init the new cells

	GetColDefault(LABOR_DESC, &cell) ;
	SetCell(LABOR_DESC, lRow, &cell) ;
	
	GetColDefault(QUANTITY, &cell);
	SetCell(QUANTITY, lRow, &cell);

	GetColDefault(UOM, &cell);
	SetCell(UOM, lRow, &cell);

	GetColDefault(RETAIL, &cell) ;
	SetCell(RETAIL, lRow, &cell) ;

	GetColDefault(EXTENSION, &cell);
	SetCell(EXTENSION, lRow, &cell) ;

	GetColDefault(PRICE, &cell) ;
	SetCell(PRICE, lRow, &cell) ;

	GetColDefault(COST, &cell) ;
	SetCell(COST, lRow, &cell) ;
	
	GetColDefault(ON_INV, &cell);
	SetCell(ON_INV, lRow, &cell) ;
	
	GetColDefault(ON_WO, &cell);
	SetCell(ON_WO, lRow, &cell) ;


	// row specific init
	if (strType == szBASIC_LABOR_PREFIX)
	{
		FilterBasicLabor();
		GetColDefault(LABOR_DESC, &cell) ;
		cell.SetCellType(UGCT_DROPLIST);

		CString strChoices = "" ;
		while (!m_setBasicLabor.IsEOF())
		{
			strChoices += m_setBasicLabor.m_LaborDescription ;
			strChoices += "\n" ;
			m_setBasicLabor.MoveNext() ;
		}

		strChoices.MakeUpper() ;
		cell.SetLabelText(strChoices);
		SetCell(LABOR_DESC, lRow, &cell);

		QuickSetReadOnly(LABOR_DESC, lRow, false);
		QuickSetReadOnly(QUANTITY, lRow, false);
		QuickSetReadOnly(ON_WO, lRow, false);

		QuickSetBool(ON_INV, lRow, false);
		QuickSetBool(ON_WO, lRow, true);
	}
	else if (strType == szOPTIONAL_LABOR_PREFIX)
	{
		FilterOptions();   // contains all options for the current materialtypeid
		GetColDefault(LABOR_DESC, &cell);
		cell.SetCellType(UGCT_DROPLIST);

		CString strChoices = "" ;
		while (!m_setOptions.IsEOF())
		{
			strChoices += m_setOptions.m_OptionDescription ;
			strChoices += "\n" ;
			m_setOptions.MoveNext() ;
		}

		strChoices.MakeUpper() ;
		cell.SetLabelText(strChoices);
		SetCell(LABOR_DESC, lRow, &cell);

		QuickSetReadOnly(LABOR_DESC, lRow, false);
		QuickSetReadOnly(QUANTITY, lRow, false);
		QuickSetReadOnly(ON_WO, lRow, false);

		QuickSetBool(ON_INV, lRow, false);
		QuickSetBool(ON_WO, lRow, true);
	}
	else if (strType == szCUSTOM_LABOR_PREFIX)
	{
		// set up the custom labor UOM cell to be a drop list
		CString strChoices = "" ;
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
		cell.SetReadOnly(FALSE) ;
		cell.SetCellType( UGCT_DROPLIST);
		cell.SetLabelText(strChoices);
		cell.SetNumberDecimals(iDecimals);
		SetCell(UOM, lRow, &cell);

		QuickSetReadOnly(LABOR_DESC, lRow, false);
		QuickSetReadOnly(QUANTITY, lRow, false);
        QuickSetReadOnly(RETAIL, lRow, false);
		
		QuickSetReadOnly(ON_WO, lRow, false);
		
		QuickSetBool(ON_INV, lRow, false);
		QuickSetBool(ON_WO, lRow, true);
		
		// if we can edit custom labor cost, make the cell editable.
		if (m_bCanEditCustomCost)
		{
			QuickSetReadOnly(COST, lRow, false) ;
		}
	}

	// if we can edit all labor cost items, make the cell editable.
	if ( m_bCanEditLaborCost )
	{
		QuickSetReadOnly(COST, lRow, false) ;
	}

	QuickSetReadOnly(ON_INV, lRow, HasImportedItems()) ;

	// set to manual entry method id
	QuickSetNumber(ENTRY_METHOD_ID, lRow, CGlobals::ENTRY_MANUAL);
	RedrawAll();
}

void CGridLabor::FilterOptionByID(long lId)
{
	m_setOptions.m_strFilter.Format("[OptionID] = '%d'", lId ) ;
	m_setOptions.Requery() ;
}

void CGridLabor::FilterOptions(long lRow)
{
	CString strOptionDescription = QuickGetText(LABOR_DESC, lRow) ;
	FilterOptions(strOptionDescription) ;
}

void CGridLabor::FilterOptions(CString strOptionDescription)
{
	strOptionDescription.Replace("'", "''");
	m_setOptions.m_strFilter.Format("[MaterialTypeID] = '%d' AND [OptionDescription] = '%s'", m_lMaterialType, strOptionDescription ) ;
	m_setOptions.Requery() ;
}

void CGridLabor::FilterOptions()
{
	//m_setOptions.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
	//m_setOptions.Requery() ;
	if (m_bShowActiveOnly)
	{
		m_setOptions.m_strFilter.Format("[MaterialTypeID] = '%d' AND [Active] = 1", m_lMaterialType ) ;
	}
	else
	{
		m_setOptions.m_strFilter.Format("[MaterialTypeID] = '%d'", m_lMaterialType ) ;
	}
	m_setOptions.m_strSort = "[OptionDescription]" ;
	if (m_setOptions.IsOpen())
	{
		m_setOptions.Requery() ;
	}
	else
	{
		m_setOptions.Open() ;
	}
	RedrawAll() ;
}

void CGridLabor::SetUomId(long lId)
{
	m_setUOM.m_strFilter.Format("[UnitOfMeasureID] = '%d'", lId ) ;
	m_setUOM.Requery() ;
}

bool CGridLabor::IsRowType(const long lRow, char* pstrPrefix)
{
	bool bMatches = false;

	CString strId = QuickGetText(ID, lRow) ;
	if (strId.Left(strlen(pstrPrefix)/sizeof(char)).Compare(pstrPrefix) == 0)
	{
		bMatches = true;
	}

	return bMatches;
}

long CGridLabor::GetDetailID(const long lRow)
{
	long ID = -1;

	CString strID = QuickGetText(ID, lRow);
	strID = strID.Mid(iPREFIX_LENGTH);
	strID.Replace("*", "") ;
	if (strID.GetLength() > 0)
	{
		ID = atol(strID);
	}

	return ID;
}

int CGridLabor::OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags)
{
//	return CGridPOBase::OnSortEvaluate(cell1, cell2, flags);

	int iReturnValue = 0;
	
	CString strCell1;
	CString strCell2;

	CString strTemp;
	long iID1 = -1;
	long iID2 = -1;

	char cID1 ;
	char cID2 ;

	bool bID1 = true ;
	bool bID2 = true ;

	if( NULL == cell1->GetText() && NULL == cell2->GetText() )
	{
        iReturnValue = 0;
	}
    if( NULL == cell1->GetText( ) )
	{
        iReturnValue = 1;
	}
	if( NULL == cell2->GetText( ) )
	{
        iReturnValue = -1;
	}
	
	cell1->GetText(&strCell1);
	cell2->GetText(&strCell2);

	// The next section determines if we are dealing with our ID column - it is sorted differently
	cID1 = strCell1.GetAt(0);
	cID2 = strCell2.GetAt(0);

	strTemp = strCell1.Right(strCell1.GetLength() - 1);
	iID1 = atol(strTemp);

	strTemp = strCell2.Right(strCell2.GetLength() - 1);
	iID2 = atol(strTemp);
	
	bID1 = (strCell1.Right(1) == "*") || iID1 > 0;
	bID2 = (strCell2.Right(1) == "*") || iID2 > 0;
	
	if ( ((cID1 == szBASIC_LABOR_PREFIX[0]) || (cID1 == szOPTIONAL_LABOR_PREFIX[0]) || (cID1 == szCUSTOM_LABOR_PREFIX[0])) &&
		 ((cID2 == szBASIC_LABOR_PREFIX[0]) || (cID2 == szOPTIONAL_LABOR_PREFIX[0]) || (cID2 == szCUSTOM_LABOR_PREFIX[0])) && bID1 && bID2)
	{
		if (cID1 == cID2)
		{
			if (iID1 < iID2)
			{
				iReturnValue = -1;
			}
			else if (iID1 > iID2)
			{
				iReturnValue = 1;
			}
			else
			{
				iReturnValue = 0;
			}
		}
		else if ( (cID1 == szBASIC_LABOR_PREFIX[0]) && (cID2 == szOPTIONAL_LABOR_PREFIX[0]))
		{
            iReturnValue = -1;
		}
		else if ( (cID1 == szBASIC_LABOR_PREFIX[0]) && (cID2 == szCUSTOM_LABOR_PREFIX[0]))
		{
            iReturnValue = -1;
		}
		else if ( (cID1 == szOPTIONAL_LABOR_PREFIX[0]) && (cID2 == szCUSTOM_LABOR_PREFIX[0]))
		{
            iReturnValue = -1;
		}
	}
	else
	{
		// not an ID column, so let the base class handle the sorting
		iReturnValue = CGridPOBase::OnSortEvaluate(cell1, cell2, flags);
	}

	return iReturnValue;
}

int CGridLabor::GetFirstColumnIndex()
{
	return ID + 1 ;
}

int CGridLabor::GetLastColumnIndex()
{
	return LAST;
}

void CGridLabor::UpdateRowColor(long lRow)
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

void CGridLabor::ShowCFIPrice(bool bShowCFIColumn)
{
	m_bShowCfiPrice = bShowCFIColumn ;

	if (bShowCFIColumn)
	{
		ShowColumn(PRICE);
	}
	else
	{
		HideColumn(PRICE);
	}

	RedrawAll() ;
}

int CGridLabor::OnHint(int col, long row, int section, CString *string, int *maxwidth)
{
	if ((section ==UG_GRID) && (col == LABOR_DESC))
	{
		CString text;
		text = QuickGetText(col, row);
		string->Format(_T("%s"), text);
		*maxwidth = 500;
		return TRUE; 
	}
	
	return FALSE;
}

bool CGridLabor::HasImportedItems()
{
	bool bHasImportedItems = false;

	int iNumRows = GetNumberRows();
	for (int iRowIndex = 0; iRowIndex < iNumRows; iRowIndex++)
	{
		bHasImportedItems = bHasImportedItems || (QuickGetNumber(ENTRY_METHOD_ID, iRowIndex) == CGlobals::ENTRY_SPN_IMPORTED) || (QuickGetNumber(ENTRY_METHOD_ID, iRowIndex) == CGlobals::ENTRY_SOSI_IMPORTED) ;
		if (bHasImportedItems)
		{
			// no need to keep going
			break;
		}
	}

    return bHasImportedItems;
}

bool CGridLabor::SplitLineItem(long row)
{
	bool bSplitOK = true;

	CDlgSplitLineItem dlg;

	CUGCell cell;
	GetCell(QUANTITY, row, &cell);
	dlg.SetNumDecimals(cell.GetNumberDecimals());
	dlg.SetTotalAmount(cell.GetNumber());
	dlg.SetSplitText("Enter the amount you wish to split from this line item.");

	if (dlg.DoModal() == IDOK)
	{
		double dNewAmount = dlg.GetNewAmount();
		double dBalance = cell.GetNumber() - dNewAmount;
		int iResult = UG_ERROR;

		long NumRows = GetNumberRows();

		long newrow;

		if (row == NumRows - 1)
		{
			iResult = AppendRow(GetRowType(row));
			newrow = GetNumberRows() - 1;
		}
		else
		{
			iResult = InsertRow(row + 1, GetRowType(row));
			newrow = row+1;
		}

		if (iResult == UG_SUCCESS)
		{
			// set the new amount
			QuickSetNumber(QUANTITY, row, dNewAmount);

			// mark the entry method
			QuickSetNumber(ENTRY_METHOD_ID, row, QuickGetNumber(ENTRY_METHOD_ID, row));
						
			// copy the data to the new row
			CUGCell cell;
			GetCell(LABOR_DESC, row, &cell);
			SetCell(LABOR_DESC, newrow, &cell);

			GetCell(QUANTITY, row, &cell);
			SetCell(QUANTITY, newrow, &cell);
			QuickSetNumber(QUANTITY, newrow, dBalance);

			GetCell(UOM, row, &cell);
			SetCell(UOM, newrow, &cell);
			
			GetCell(RETAIL, row, &cell);
			SetCell(RETAIL, newrow, &cell);
			
			GetCell(PRICE, row, &cell);
			SetCell(PRICE, newrow, &cell);
			
			GetCell(COST, row, &cell);
			SetCell(COST, newrow, &cell);
			
			GetCell(ON_INV, row, &cell);
			SetCell(ON_INV, newrow, &cell);
			
			GetCell(ON_WO, row, &cell);
			SetCell(ON_WO, newrow, &cell);
			
			GetCell(ENTRY_METHOD_ID, row, &cell);
			SetCell(ENTRY_METHOD_ID, newrow, &cell);
			
			RecalculateRows();
		}
	}

	RedrawAll();
	IsRowDirty(row) ;

	return bSplitOK;
}

CString CGridLabor::GetRowType(long row)
{
	CString strRowType = "";

	if (IsRowType(row, (char*)szBASIC_LABOR_PREFIX))
	{
		strRowType = szBASIC_LABOR_PREFIX;
	}
	else if (IsRowType(row, (char*)szOPTIONAL_LABOR_PREFIX))
	{
		strRowType = szOPTIONAL_LABOR_PREFIX;
	}

	return strRowType;
}

void CGridLabor::RefreshPrices()
{
	CSetBasicLabor setBasicLabor(&g_dbFlooring);
	setBasicLabor.m_strFilter = "BasicLaborID = -1";
	setBasicLabor.Open();
	
	CSetOptions setOptions(&g_dbFlooring);
	setOptions.m_strFilter = "OptionID = -1";
	setOptions.Open();
	
	long lNumRows = GetNumberRows();
	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		CString strTemp = "";

		if (IsRowType(lRow, (char*)szBASIC_LABOR_PREFIX))
		{
			strTemp = QuickGetText(LABOR_DESC, lRow);
			strTemp.Replace("'", "''");
			setBasicLabor.m_strFilter.Format("LaborDescription = '%s' AND MaterialTypeID = %d", strTemp, m_lMaterialType);
			setBasicLabor.Requery();
			ASSERT(!setBasicLabor.IsEOF());
			if (!setBasicLabor.IsEOF())
			{
				CPricing clPricing;

				double dCost;
				double dPrice;
				bool bPriceOK = clPricing.GetBasicPrices(setBasicLabor.m_BasicLaborID, m_datePO, m_datePOScheduleDate, m_iStoreID, dCost, dPrice);
				
				CString strCost = "0.00";


				if (bPriceOK)
				{
					strCost.Format("%4.2f", dCost);
				}

				QuickSetText(COST, lRow, strCost) ;
			}
		}
		else if (IsRowType(lRow, (char*)szOPTIONAL_LABOR_PREFIX))
		{
			strTemp = QuickGetText(LABOR_DESC, lRow);
			strTemp.Replace("'", "''");
			setOptions.m_strFilter.Format("OptionDescription = '%s' AND MaterialTypeID = %d", strTemp, m_lMaterialType);
			setOptions.Requery();
			ASSERT(!setOptions.IsEOF());
			if (!setOptions.IsEOF())
			{
				CPricing clPricing;
				double dCost;
				double dPrice;
				bool bPriceOK = clPricing.GetOptionPrices(setOptions.m_OptionID, m_datePO, m_datePOScheduleDate, m_iStoreID, dCost, dPrice);

				CString strCost = "0.00";

				if (bPriceOK)
				{
					strCost.Format("%4.2f", dCost);
				}

				QuickSetText(COST, lRow, strCost) ;
			}
		}
		IsRowDirty(lRow) ;
	}

	setBasicLabor.Close();
	setOptions.Close();

	RedrawAll() ;
}

int CGridLabor::GetUOMId(CString strUOM)
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

bool CGridLabor::IsColumnDirty(int iCol, long lRow)
{
	bool bDirty = true ;

	switch (iCol)
	{
	case QUANTITY:
		bDirty = QuickGetNumber(QUANTITY, lRow) != QuickGetNumber(ORG_QUANTITY, lRow) ; 
		break ;

	case RETAIL:
		bDirty = QuickGetNumber(RETAIL, lRow) != QuickGetNumber(ORG_RETAIL, lRow) ; 
		break ;

	case EXTENSION:
		bDirty = QuickGetNumber(EXTENSION, lRow) != QuickGetNumber(ORG_EXTENSION, lRow) ;
		break ;

	case PRICE :
		bDirty = QuickGetNumber(PRICE, lRow) != QuickGetNumber(ORG_PRICE, lRow) ;
		break ;

	case COST :
		bDirty = QuickGetNumber(COST, lRow) != QuickGetNumber(ORG_COST, lRow) ;
		break ;

	case ENTRY_METHOD_ID :
		bDirty = QuickGetNumber(ENTRY_METHOD_ID, lRow) != QuickGetNumber(ORG_ENTRY_METHOD_ID, lRow) ;
		break ;

	case ON_INV :
		bDirty = QuickGetBool(ON_INV, lRow) != QuickGetBool(ORG_ON_INV, lRow) ;
		break ;

	case ON_WO :
		bDirty = QuickGetBool(ON_WO, lRow) != QuickGetBool(ORG_ON_WO, lRow) ;
		break ;

	case DELETED :
		bDirty = QuickGetBool(DELETED, lRow) != QuickGetBool(ORG_DELETED, lRow) ;
		break ;
	
	case REVIEWED :
		bDirty = QuickGetBool(REVIEWED, lRow) != QuickGetBool(ORG_REVIEWED, lRow) ; 
		break ;

	case LABOR_DESC :
		{
			CString str1 ;
			CString str2 ;

			QuickGetText(LABOR_DESC, lRow, &str1) ;
			QuickGetText(ORG_LABOR_DESC, lRow, &str2) ;
			bDirty = str1.CompareNoCase(str2) != 0 ;
		}
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

	default:
		assert(0) ;
		break ;
	}

	return bDirty ;
}

bool CGridLabor::IsRowDirty(long lRow)
{
	bool bDirty = false ;
//	enum {ID = -1, LABOR_DESC, QUANTITY, UOM, RETAIL, EXTENSION, PRICE, COST, ON_INV, ON_WO, ENTRY_METHOD_ID, DELETED, 

	if (!bDirty) bDirty = IsColumnDirty(QUANTITY, lRow) ; 
	if (!bDirty) bDirty = IsColumnDirty(LABOR_DESC, lRow) ;
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

	if (!bDirty) bDirty = IsColumnDirty(EXTENSION, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(RETAIL, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(PRICE, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(COST, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(ENTRY_METHOD_ID, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(ON_INV, lRow) ;
	if (!bDirty) bDirty = IsColumnDirty(ON_WO, lRow) ;
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

int CGridLabor::RedrawAll()
{
	UpdateColors() ;
	UpdateRowHeights() ;
	return CGridPOBase::RedrawAll() ;
}

void CGridLabor::UpdateRowHeights()
{
	long lNumRows = GetNumberRows();
	int iColumnToSizeTo = LABOR_DESC ;

	if (lNumRows >= 0)
	{
		CDC* pDC = GetDC() ;
		CRect rect(0, 0, GetColWidth(iColumnToSizeTo) - 2, 10) ;
		pDC->DPtoLP(&rect) ;

		int iWidth = rect.Width() - 21 ;

		CUGCell cell ;
		GetCell(iColumnToSizeTo, 0, &cell) ;

		CFont* pFont = cell.GetFont() ;

		if (pFont == NULL)
		{
			pFont = GetFont(m_fontID) ;
		}
		
		LOGFONT lf;
		pFont->GetLogFont(&lf);
		
		int iRowLeader = ((m_GI->m_defRowHeight - lf.lfHeight) / 2) + 2 ;

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
