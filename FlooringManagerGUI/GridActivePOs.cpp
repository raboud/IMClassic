/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridStores.cpp: implementation of the CGridActivePOs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridActivePOs.h"
#include "DialogPo.h"
#include "SetVwActivePOs.h"
#include "SetUserMarketDivisionAssignments.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CMultiDocTemplate* g_pTemplateCustomerPO ;

#include "CustomerView.h"

//enum {ENTRY_MANUAL = 1, SPN_ENTRY_IMPORTED, SPN_ENTRY_IMPORTED_HANDMODIFIED, SPN_ENTRY_IMPORTED_XMLDELETED, SOSI_ENTRY_IMPORTED, SOSI_ENTRY_IMPORTED_HANDMODIFIED, SOSI_ENTRY_IMPORTED_XMLDELETED} ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridActivePOs::CGridActivePOs(int iUserID)
{
	m_bShowOnlyMyPOs = true;
	HighlightCurrentRow();
	m_strRecordSetFilter = "";
	m_dtOrderDateStart = COleDateTime::GetCurrentTime();
	m_dtOrderDateEnd = m_dtOrderDateStart;
	m_dtOrderDateStart.SetDate(m_dtOrderDateStart.GetYear()-1, 1, 1);
	
	SetUserID(iUserID);
	m_iSortCol = SCHEDULED_DATE;
	m_iLastSortCol = m_iSortCol;
	m_iSortFlags = UG_SORT_ASCENDING;
	m_pCustomerViewFrame = NULL;

	aszSortString[PO_NUMBER] = "PurchaseOrderNumber";
	aszSortString[STORE_NUMBER] = "StoreNumber";
	aszSortString[CUSTOMER] = "CustomerName";
	aszSortString[ORDER_DATE] = "OrderDate";
	aszSortString[SCHEDULED_DATE] = "Scheduled DESC, ScheduleStartDate";
	aszSortString[MARKET] = "MarketName";
	aszSortString[DIVISION] = "Division";
	aszSortString[ENTRY_METHOD] = "EntryMethodID";
}

CGridActivePOs::~CGridActivePOs()
{
}

void CGridActivePOs::OnSetup()
{
	CCFGrid::OnSetup() ;

	m_iArrowCellTypeIndex = AddCellType(&m_CellTypeArrow);

	AddColumn(" PO Number ", PO_NUMBER);
	AddColumn(" Store Number ", STORE_NUMBER);
	AddColumn("         Customer          ", CUSTOMER);
	AddColumn("    Market    ", MARKET);
	AddColumn("   Division   ", DIVISION);
	AddColumn(" Order Date ", ORDER_DATE);
	AddColumn(" Scheduled Start Date ", SCHEDULED_DATE);
	AddColumn(" Entry ", ENTRY_METHOD);
	AddColumn("OrderDateNumeric", ORDER_DATE_NUMERIC);
	AddColumn("ScheduleDateNumeric", SCHEDULED_DATE_NUMERIC);
	AddColumn("HasAlerts", HASALERTS);
	AddColumn("Cancelled", CANCELLED);
	AddColumn("OrderID", ORDERID);
	InitColumnHeadings();

	CUGCell cell;

	GetColDefault(PO_NUMBER, &cell) ;
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(PO_NUMBER, &cell) ;
	SetColDefault(STORE_NUMBER, &cell) ;	
	SetColDefault(ORDER_DATE, &cell) ;	
	SetColDefault(SCHEDULED_DATE, &cell) ;	
	SetColDefault(ENTRY_METHOD, &cell) ;	

	SetColWidth(-1, 0);

	GetColDefault(ORDER_DATE_NUMERIC, &cell);
	cell.SetDataType(UGCELLDATA_NUMBER);
	SetColDefault(ORDER_DATE_NUMERIC, &cell);
	SetColDefault(SCHEDULED_DATE_NUMERIC, &cell);
	
	HideColumn(ORDER_DATE_NUMERIC);
	HideColumn(SCHEDULED_DATE_NUMERIC);
	HideColumn(HASALERTS);
	HideColumn(CANCELLED);
	HideColumn(ORDERID);

	EnableMenu(TRUE) ;

}

void CGridActivePOs::SetUserID(int iUserID)
{
	m_iUserID = iUserID;
	UpdateRecordSetFilter();
}

void CGridActivePOs::UpdateRecordSetFilter()
{
	m_strRecordSetFilter = "";
	
	// set up the show only my pos part of the filter
	if (m_bShowOnlyMyPOs)
	{
		CSetUserMarketDivisionAssignments setUserAssign(&g_dbFlooring);
		setUserAssign.m_strFilter.Format("UserID = %d", m_iUserID);
		setUserAssign.Open();
		CString strTemp = "";
		while (!setUserAssign.IsEOF())
		{
			if (m_strRecordSetFilter.GetLength() > 0)
			{
				m_strRecordSetFilter += " OR ";
			}
			strTemp.Format("(MarketID = %d AND DivisionID = %d)", setUserAssign.m_MarketID, setUserAssign.m_DivisionID);
			m_strRecordSetFilter += strTemp;
			setUserAssign.MoveNext();
		}
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter = "(" + m_strRecordSetFilter + ")";
		}
		else
		{
			m_strRecordSetFilter = "(MarketID = -1 AND DivisionID = -1)";
		}
	}

	// set up the include cancelled pos part of the filter
	if (false == m_bIncludeCancelledPOs)
	{
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " AND ";
		}

		m_strRecordSetFilter += "Cancelled = 0";
	}

	if (m_strRecordSetFilter.GetLength() > 0)
	{
		m_strRecordSetFilter += " AND ";
	}

	// set up the order date part of the filter
	CString strTemp = "";
	strTemp.Format("(OrderDate >= '%s' AND OrderDate <= '%s')", m_dtOrderDateStart.Format("%m/%d/%Y"), m_dtOrderDateEnd.Format("%m/%d/%Y"));

	m_strRecordSetFilter += strTemp;

	// set up the include only POs with alerts part of the filter
	if (m_bShowOnlyPOsWithAlerts)
	{
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " AND ";
		}

		m_strRecordSetFilter += "HasAlerts = 1";
	}

}

void CGridActivePOs::Update()
{
	CWaitCursor wait;
	SetPaintMode(0);

	// keep the current PO to see if we can reselect it after the update
	long lCurrentRow = GetCurrentRow();
	CString strCurrentPONumber = QuickGetText(PO_NUMBER, lCurrentRow);	
	
	// get rid of stale data
	this->Reset();
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	CSetVwActivePOs setActivePOs(&g_dbFlooring) ;
	setActivePOs.m_strFilter = m_strRecordSetFilter;
	setActivePOs.m_strSort = GetSortString();
		
	setActivePOs.Open() ;
	while (!setActivePOs.IsEOF())
	{
		AppendRow() ;
		long lRow = GetNumberRows() - 1 ;

		QuickSetText(PO_NUMBER, lRow, setActivePOs.m_PurchaseOrderNumber.Trim());
		QuickSetText(STORE_NUMBER, lRow, setActivePOs.m_StoreNumber.Trim());
		QuickSetText(CUSTOMER, lRow, setActivePOs.m_CustomerName.Trim()) ;
		QuickSetText(MARKET, lRow, setActivePOs.m_MarketName.Trim()) ;
		QuickSetText(DIVISION, lRow, setActivePOs.m_Division.Trim()) ;
		
		CString strDate = "";
		COleDateTimeSpan ts;
		if (!setActivePOs.IsFieldNull(&setActivePOs.m_OrderDate))
		{
			strDate = setActivePOs.m_OrderDate.Format("%m/%d/%Y");
			QuickSetText(ORDER_DATE, lRow, strDate) ;
			ts = setActivePOs.m_OrderDate - COleDateTime(1970, 1, 1, 0, 0, 0);
			QuickSetNumber(ORDER_DATE_NUMERIC, lRow, ts.GetDays());
		}
		else
		{
			QuickSetNumber(ORDER_DATE_NUMERIC, lRow, (double) 0xFFFFFFFFFFFFFFFF) ;
		}
		
		if ((!setActivePOs.IsFieldNull(&setActivePOs.m_ScheduleStartDate)) && (setActivePOs.m_Scheduled == TRUE))
		{
			strDate = setActivePOs.m_ScheduleStartDate.Format("%m/%d/%Y");
			QuickSetText(SCHEDULED_DATE, lRow, strDate) ;
			ts = setActivePOs.m_ScheduleStartDate - COleDateTime(1970, 1, 1, 0, 0, 0);
			QuickSetNumber(SCHEDULED_DATE_NUMERIC, lRow, ts.GetDays());
		}
		else
		{
			QuickSetText(SCHEDULED_DATE, lRow, "") ;
			QuickSetNumber(SCHEDULED_DATE_NUMERIC, lRow, (double) 0xFFFFFFFFFFFFFFFF);
		}

		if (setActivePOs.m_EntryMethodID == CGlobals::ENTRY_MANUAL)
		{
			QuickSetText(ENTRY_METHOD, lRow, "MAN.");
		}
		else if ((setActivePOs.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED) ||
			     (setActivePOs.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED) ||
				 (setActivePOs.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED_XMLDELETED))
		{
			QuickSetText(ENTRY_METHOD, lRow, "SPN");
		}
		else if ((setActivePOs.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED) ||
			     (setActivePOs.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED) ||
				 (setActivePOs.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED_XMLDELETED))
		{
			QuickSetText(ENTRY_METHOD, lRow, "SOSI");
		}
		else
		{
			QuickSetText(ENTRY_METHOD, lRow, "");
		}

		bool bHasAlerts = (TRUE == setActivePOs.m_HasAlerts);
		QuickSetBool(HASALERTS, lRow, bHasAlerts);
		
		bool bCancelled = (TRUE == setActivePOs.m_Cancelled);
		QuickSetBool(CANCELLED, lRow, bCancelled);

		if (bHasAlerts)
		{
			SetRowColor(lRow, CGlobals::COLOR_BLUE, CCFGrid::EnColorMode_TEXT);
			SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
		}

		if (bCancelled)
		{
			SetRowColor(lRow, CGlobals::COLOR_RED, CCFGrid::EnColorMode_BACK);
		}

		QuickSetNumber(ORDERID, lRow, setActivePOs.m_OrderID);
		
				
		setActivePOs.MoveNext() ;
	}
	setActivePOs.Close();

	long lNumRows = GetNumberRows();
	if (lNumRows > 0)
	{
		CString strTemp;
		long row = 0;
		int col = PO_NUMBER;
		strTemp = strCurrentPONumber;
		if (UG_SUCCESS == FindFirst(&strTemp, &col, &row, 0))
		{
			GotoRow(row);
		}
	}

	SetPaintMode(1);
	RedrawAll() ;
}

int CGridActivePOs::OnMenuStart(int col, long row, int section)
{
	UNREFERENCED_PARAMETER(col);

	BOOL bDisplayMenu = FALSE;
	if ((section == UG_GRID) && (row >= 0))
	{
		//* Empty the Menu!!
		EmptyMenu();

		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			AddMenuItem(OPEN_PO, "Open PO");
			bDisplayMenu = TRUE;
		}
	}
	return bDisplayMenu ;
}

void CGridActivePOs::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case OPEN_PO:
			OpenPO(row) ;
			break ;

		default:
			break ;
		}
	}
	this->RedrawAll() ;
}

void CGridActivePOs::OnSH_DClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	OpenPO(row) ;
}

void CGridActivePOs::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	OpenPO(row) ;
}

void CGridActivePOs::OpenPO(long row)
{
	if ( (row >= GetNumberRows()) || (row < 0))
	{
		return;
	}

	long lOrderID = (long) QuickGetNumber(ORDERID, row);

	if ((m_pCustomerViewFrame == NULL) || (m_pCustomerViewFrame != NULL && (FALSE == ::IsWindow(m_pCustomerViewFrame->m_hWnd))))
	{
		m_pCustomerViewFrame = g_pTemplateCustomerPO->CreateNewFrame(NULL,NULL) ;
		if (m_pCustomerViewFrame != NULL)
		{
			m_pCustomerViewFrame->InitialUpdateFrame(NULL, true) ;
		}
		else
		{
			MessageBox("Could not open customer dialog.", "Error", MB_OK);
		}
	}

	if (TRUE == ::IsWindow(m_pCustomerViewFrame->m_hWnd))
	{
		this->GetParent()->ShowWindow(SW_SHOWMINIMIZED);
		m_pCustomerViewFrame->ShowWindow(SW_SHOW);
		CCustomerView* pView = (CCustomerView*) m_pCustomerViewFrame->GetActiveView() ;
		pView->FindByOrderNumber(lOrderID);
	}
}

void CGridActivePOs::ViewCustomer(long row)
{
	CString strPONumber = QuickGetText(PO_NUMBER, row);
	CString strStoreNumber = QuickGetText(STORE_NUMBER, row);
	int iStoreID = CGlobals::StoreIDFromStoreNumber(strStoreNumber);

	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("PurchaseOrderNumber = '%s' AND StoreID = %d", strPONumber, iStoreID);
	setOrders.Open();

	if (!setOrders.IsEOF())
	{
		CFrameWnd* pFrame = g_pTemplateCustomerPO->CreateNewFrame(NULL,NULL) ;
		if (pFrame != NULL)
		{
			pFrame->InitialUpdateFrame(NULL, true) ;
			CCustomerView* pView = (CCustomerView*) pFrame->GetActiveView() ;
			CString strNumber;
			strNumber.Format("%ld", setOrders.m_CustomerID);
			pView->FindByCustomerNumber(strNumber);
		}
		else
		{
			MessageBox("Could not open customer dialog.", "Error", MB_OK);
		}
	}
}

int CGridActivePOs::OnCanSizeTopHdg()
{ 
	return FALSE; 
} 

BOOL CGridActivePOs::OnCanSizeCol(int /*col*/)
{
	return TRUE;
}

void CGridActivePOs::OnTH_LClicked(int col, long row, int updn, RECT* rect, POINT* point, BOOL processed)
{
	UNREFERENCED_PARAMETER(processed);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(row);

	if (updn == 0)
	{
		if (m_iSortFlags == UG_SORT_ASCENDING)
		{
			m_iSortFlags = UG_SORT_DESCENDING;
		}
		else
		{
			m_iSortFlags = UG_SORT_ASCENDING;
		}

		SortBy(col, m_iSortFlags);
	}

	//CCFGrid::OnTH_LClicked(col, row, updn, rect, point, processed);
}

int CGridActivePOs::SortBy(int col, int flag /*= UG_SORT_ASCENDING*/)
{
	CWaitCursor wait;
	int iRetVal = UG_ERROR;

	m_iLastSortCol = m_iSortCol;
	m_iSortCol = col;
	m_iSortFlags = flag;
	CUGCell cell;
	GetCell(col, -1, &cell);
	cell.SetCellType(m_iArrowCellTypeIndex);
	if (flag == UG_SORT_ASCENDING)
	{
		cell.SetCellTypeEx(UGCT_SORTARROWUP);
	}
	else
	{
		cell.SetCellTypeEx(UGCT_SORTARROWDOWN);
	}
	SetCell(col, -1, &cell);
	if (m_iLastSortCol != m_iSortCol)
	{
		QuickSetCellType(m_iLastSortCol, -1, UGCT_NORMAL);
	}

	if (m_iSortCol == SCHEDULED_DATE)
	{
        iRetVal = CCFGrid::SortBy(SCHEDULED_DATE_NUMERIC, flag);	
	}
	else if (m_iSortCol == ORDER_DATE)
	{
		iRetVal = CCFGrid::SortBy(ORDER_DATE_NUMERIC, flag);
	}
	else
	{
		iRetVal = CCFGrid::SortBy(col, flag);
	}

	RedrawAll();
	return iRetVal;
}

int CGridActivePOs::OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags)
{
	return CCFGrid::OnSortEvaluate(cell1, cell2, flags);
}

CString CGridActivePOs::GetSortString()
{
	CString strSort = "";

	if ((m_iSortCol >= 0) && (m_iSortCol < (sizeof(aszSortString) / sizeof(char*))))
	{
		strSort = aszSortString[m_iSortCol];
	}

	if (m_iSortFlags == UG_SORT_DESCENDING)
	{
		strSort += " DESC";
	}
	
	return strSort;
}

void CGridActivePOs::UpdateRowColor(long lRow)
{
	bool bHasAlerts = (TRUE == QuickGetBool(HASALERTS, lRow));
	bool bCancelled = (TRUE == QuickGetBool(CANCELLED, lRow));
	
	if (bHasAlerts)
	{
		SetRowColor(lRow, CGlobals::COLOR_BLUE, CCFGrid::EnColorMode_TEXT);
		SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
	}

	if (bCancelled)
	{
		SetRowColor(lRow, CGlobals::COLOR_RED, CCFGrid::EnColorMode_BACK);
	}
}

bool CGridActivePOs::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridActivePOs::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}