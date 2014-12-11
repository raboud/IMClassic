/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridActivityList.cpp: implementation of the CGridActivityList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridActivityList.h"
#include "DialogPo.h"
#include "SetVwActivityList.h"
#include "SetUserMarketDivisionAssignments.h"
#include "Globals.h"
#include "SetActivityTypes.h"

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

CGridActivityList::CGridActivityList(int iUserID)
{
	m_bShowOnlyMyActivities = true;
	HighlightCurrentRow();
	m_strRecordSetFilter = "";
	m_dtCreateDateStart = COleDateTime::GetCurrentTime();
	m_dtCreateDateEnd = m_dtCreateDateStart;
	m_dtCreateDateStart.SetDate(m_dtCreateDateStart.GetYear()-1, 1, 1);
	
	SetUserID(iUserID);
	m_iSortCol = FOLLOW_UP_DATE;
	m_iLastSortCol = m_iSortCol;
	m_iSortFlags = UG_SORT_ASCENDING;
	m_pCustomerViewFrame = NULL;

	aszSortString[ACTIVITY_NAME] = "ActivityName";
	aszSortString[CREATED_DATE] = "CreatedDate";
	aszSortString[FOLLOW_UP_DATE] = "FollowUpDate";
	aszSortString[STORE_NUMBER] = "StoreNumber";
	aszSortString[PO_NUMBER] = "PurchaseOrderNumber";
	aszSortString[CUSTOMER] = "CustomerName";
	aszSortString[MARKET] = "MarketName";
	aszSortString[DIVISION] = "Division";

	CPermissions perm;
	m_bCanCloseCancelled = perm.HasPermission("CanMarkPOReviewed");
}

CGridActivityList::~CGridActivityList()
{
}

void CGridActivityList::OnSetup()
{
	CCFGrid::OnSetup() ;

	m_iArrowCellTypeIndex = AddCellType(&m_CellTypeArrow);
	m_iButtonCellTypeIndex = AddCellType(&m_CellTypeButton);

	AddColumn("     Activity Name     ", ACTIVITY_NAME);
	AddColumn("Action", ACTION_BUTTON);
	AddColumn("      Created       ", CREATED_DATE);
	AddColumn("  Follow Up   ", FOLLOW_UP_DATE);
	AddColumn("ActivityID", ACTIVITY_ID);
	AddColumn(" Store Number ", STORE_NUMBER);
	AddColumn(" PO Number ", PO_NUMBER);
	AddColumn("         Customer          ", CUSTOMER);
	AddColumn("    Market    ", MARKET);
	AddColumn("   Division   ", DIVISION);
	AddColumn("ActivityTypeID", ACTIVITY_TYPE_ID);
	AddColumn("OrderID", ORDER_ID);
	AddColumn("ClosedByName", CLOSED_BY_NAME);
	AddColumn("ClosedDate", CLOSED_DATE);
	AddColumn("CreatedDateNumeric", CREATED_DATE_NUMERIC);
	AddColumn("FollowUpDateNumeric", FOLLOW_UP_DATE_NUMERIC);
	AddColumn("ActivityData", ACTIVITY_DATA);
	AddColumn("ClosedByID", CLOSED_BY_ID);

	InitColumnHeadings();

	CUGCell cell;

	GetColDefault(PO_NUMBER, &cell) ;
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	SetColDefault(PO_NUMBER, &cell) ;
	SetColDefault(STORE_NUMBER, &cell) ;	
	SetColDefault(CREATED_DATE, &cell) ;	
	SetColDefault(FOLLOW_UP_DATE, &cell) ;
	cell.SetAlignment( UG_ALIGNVCENTER );
	SetColDefault(ACTIVITY_NAME, &cell);
	SetColDefault(CUSTOMER, &cell);
	SetColDefault(MARKET, &cell);
	SetColDefault(DIVISION, &cell);
	
	SetColWidth(-1, 0);

	GetColDefault(CREATED_DATE_NUMERIC, &cell);
	cell.SetDataType(UGCELLDATA_NUMBER);
	SetColDefault(CREATED_DATE_NUMERIC, &cell);
	SetColDefault(FOLLOW_UP_DATE_NUMERIC, &cell);

	GetColDefault(ACTION_BUTTON, &cell);
	cell.SetCellType(m_iButtonCellTypeIndex);
	cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
	cell.SetText("OK");
	cell.SetAlignment(UG_ALIGNCENTER | UG_ALIGNVCENTER);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	SetColDefault(ACTION_BUTTON, &cell);

	
	HideColumn(ACTIVITY_ID);
	HideColumn(ACTIVITY_TYPE_ID);
	HideColumn(ORDER_ID);
	HideColumn(CLOSED_BY_NAME);
	HideColumn(CLOSED_DATE);
	HideColumn(CREATED_DATE_NUMERIC);
	HideColumn(FOLLOW_UP_DATE_NUMERIC);
	HideColumn(ACTIVITY_DATA);
	HideColumn(CLOSED_BY_ID);

	EnableMenu(TRUE) ;

}

void CGridActivityList::SetUserID(int iUserID)
{
	m_iUserID = iUserID;
	UpdateRecordSetFilter();
}

void CGridActivityList::UpdateRecordSetFilter()
{
	m_strRecordSetFilter = "";
	
	// set up the show only my pos part of the filter
	if (m_bShowOnlyMyActivities)
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

	// set up the include closed activities as part of the filter
	if (false == m_bShowAllActivities)
	{
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " AND ";
		}

		m_strRecordSetFilter += "ClosedByName IS NULL";
	}

	if (m_strRecordSetFilter.GetLength() > 0)
	{
		m_strRecordSetFilter += " AND ";
	}

	// set up the created date part of the filter
	CString strTemp = "";
	strTemp.Format("(CreatedDate >= '%s' AND CreatedDate <= '%s')", m_dtCreateDateStart.Format("%m/%d/%Y"), m_dtCreateDateEnd.Format("%m/%d/%Y"));

	m_strRecordSetFilter += strTemp;

	

	CPermissions permissions;
	CString strPermissionSQL = "";
	strTemp = "";

	CSetActivityTypes setActivityTypes(&g_dbFlooring);
	setActivityTypes.Open();
	while (!setActivityTypes.IsEOF())
	{
		strPermissionSQL = "";
		if (setActivityTypes.m_RequirePermissionToView == TRUE)
		{
			CString strPermission = setActivityTypes.m_Name;
			strPermission.Replace(" ", "");
			strPermission = "CanViewActivity" + strPermission;
			if (permissions.HasPermission(strPermission))
			{
				strPermissionSQL.Format("ActivityTypeID = %d", setActivityTypes.m_ID);
			}
		}
		else
		{
			strPermissionSQL.Format("ActivityTypeID = %d", setActivityTypes.m_ID);
		}

		if ((strTemp.GetLength() > 0) && (strPermissionSQL.GetLength() > 0))
		{
			strTemp += " OR ";
		}

		strTemp += strPermissionSQL;

		setActivityTypes.MoveNext();
	}

	if (strTemp.GetLength() > 0)
	{
		strTemp = "(" + strTemp + ")";
	}

	if ((m_strRecordSetFilter.GetLength() > 0) && (strTemp.GetLength() > 0))
	{
		m_strRecordSetFilter += " AND ";
	}

	m_strRecordSetFilter += strTemp;

}

void CGridActivityList::Update()
{
	UpdateRecordSetFilter();
	CWaitCursor wait;
	SetPaintMode(0);

	// keep the current PO to see if we can reselect it after the update
	long lCurrentRow = GetCurrentRow();
	CString strActivityID = QuickGetText(ACTIVITY_ID, lCurrentRow);	

	long lTopRow = GetTopRow();
	
	// get rid of stale data
	this->Reset();
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	CSetViewActivityList setActivities(&g_dbFlooring) ;
	setActivities.m_strFilter = m_strRecordSetFilter;
	setActivities.m_strSort = GetSortString();
		
	setActivities.Open() ;
	COleDateTime dtToday = CGlobals::GetCurrentSystemTime();
	dtToday.SetDateTime(dtToday.GetYear(), dtToday.GetMonth(), dtToday.GetDay(),0,0,0);
	COleDateTimeSpan tsToday =  dtToday - COleDateTime(1970, 1, 1, 0, 0, 0);
	double dTodaySeconds = tsToday.GetTotalSeconds();
	while (!setActivities.IsEOF())
	{
		AppendRow() ;
		long lRow = GetNumberRows() - 1 ;

		QuickSetText(STORE_NUMBER, lRow, setActivities.m_StoreNumber.Trim());
		QuickSetText(PO_NUMBER, lRow, setActivities.m_PurchaseOrderNumber.Trim());
		QuickSetText(CUSTOMER, lRow, setActivities.m_CustomerName.Trim()) ;
		QuickSetText(ACTIVITY_NAME, lRow, setActivities.m_ActivityName.Trim()) ;		
		QuickSetText(MARKET, lRow, setActivities.m_MarketName.Trim()) ;
		QuickSetText(DIVISION, lRow, setActivities.m_Division.Trim()) ;
		
		COleDateTimeSpan ts;
		CString strDate = "";
				
		strDate = setActivities.m_CreatedDate.Format("%m/%d/%Y %H:%M:%S");
		QuickSetText(CREATED_DATE, lRow, strDate) ;
		ts = setActivities.m_CreatedDate - COleDateTime(1970, 1, 1, 0, 0, 0);
		QuickSetNumber(CREATED_DATE_NUMERIC, lRow, ts.GetTotalSeconds());
				
		strDate = setActivities.m_FollowUpDate.Format("%m/%d/%Y");
		QuickSetText(FOLLOW_UP_DATE, lRow, strDate) ;
		ts = setActivities.m_FollowUpDate - COleDateTime(1970, 1, 1, 0, 0, 0);
		double dFollowUpSeconds = ts.GetTotalSeconds();
		QuickSetNumber(FOLLOW_UP_DATE_NUMERIC, lRow, dFollowUpSeconds);
		if (dFollowUpSeconds < dTodaySeconds)
		{
			if (setActivities.IsFieldNull(&setActivities.m_ClosedByName))
			{
				SetRowColor(lRow, CGlobals::COLOR_RED, CCFGrid::EnColorMode_BACK);
			}
		}
		else
		{
			SetRowColor(lRow, CGlobals::COLOR_WHITE, CCFGrid::EnColorMode_BACK);
		}
        		
		QuickSetNumber(ORDER_ID, lRow, setActivities.m_OrderID);

		QuickSetNumber(ACTIVITY_ID, lRow, setActivities.m_ID);
		QuickSetNumber(ACTIVITY_TYPE_ID, lRow, setActivities.m_ActivityTypeID);

		CString strData = "";
		if (setActivities.m_ActivityTypeID == CGlobals::ACTIVITY_SPACTION_RECEIVED)
		{
			strData = setActivities.IsFieldNull(&setActivities.m_NoteText) ? "" : setActivities.m_NoteText;	
		}
		else
		{
			strData = setActivities.IsFieldNull(&setActivities.m_Data) ? "" : setActivities.m_Data;
		}
		QuickSetText(ACTIVITY_DATA, lRow, strData);

		strDate = setActivities.IsFieldNull(&setActivities.m_ClosedDate) ? "" : setActivities.m_ClosedDate.Format("%m/%d/%Y %H:%M:%S");
		QuickSetText(CLOSED_DATE, lRow, strDate);

		QuickSetText(CLOSED_BY_NAME, lRow, setActivities.IsFieldNull(&setActivities.m_ClosedByName) ? "" : setActivities.m_ClosedByName);
        
		bool bClosed = !setActivities.IsFieldNull(&setActivities.m_ClosedByName);
		if ( bClosed || (!m_bCanCloseCancelled && setActivities.m_ActivityTypeID == CGlobals::ACTIVITY_CANCELLED_PO_RECEIVED) )
		{
			CUGCell cell;
			GetCell(ACTION_BUTTON, lRow, &cell);
			cell.SetCellType(UGCT_NORMAL);
			cell.SetReadOnly(TRUE);
			//if (bClosed)
			//{
				cell.SetText("N/A");
			//}
			//else
			//{
			//	cell.SetText("OK");
			//}
			SetCell(ACTION_BUTTON, lRow, &cell);
		}

		QuickSetNumber(CLOSED_BY_ID, lRow, setActivities.IsFieldNull(&setActivities.m_ClosedByID) ? -1 : setActivities.m_ClosedByID);
						
		setActivities.MoveNext() ;
	}
	setActivities.Close();
	
	long lNumRows = GetNumberRows();
	if (lNumRows > 0)
	{
		CString strTemp = strActivityID;
		long row = 0;
		int col = ACTIVITY_ID;
		if (UG_SUCCESS == FindFirst(&strTemp, &col, &row, 0))
		{
			GotoRow(row);
		}
		else
		{
			if (lCurrentRow <= lNumRows)
			{
				GotoRow(lCurrentRow);
			}
		}
		SetTopRow(lTopRow);
	}

	SetPaintMode(1);
	RedrawAll() ;

	::PostMessage((GetParent())->m_hWnd, CGlobals::WM_ACTIVITY_DATA_UPDATE, 0, 0) ;
}

int CGridActivityList::OnMenuStart(int col, long row, int section)
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

			bool bGrayed = true;

			CPermissions perm;
			int ClosedByID = (int) QuickGetNumber(CLOSED_BY_ID, row);
			if ( ( ClosedByID == m_iUserID) || ( ClosedByID != -1 && perm.HasPermission("CanReopenActivity") ))
			{
				bGrayed = false;
			}

			AddMenuItem(REOPEN_ACTIVITY, "Re-Open Activity", bGrayed);
		}
	}
	return bDisplayMenu ;
}

void CGridActivityList::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case OPEN_PO:
			OpenPO(row) ;
			break ;
		case REOPEN_ACTIVITY:
			ReOpenActivity((int)QuickGetNumber(ACTIVITY_ID, row));
			break;

		default:
			break ;
		}
	}
	RedrawAll() ;
}

void CGridActivityList::OnSH_DClicked(int col,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	if (col != ACTION_BUTTON)
	{
		OpenPO(row) ;
	}
}

void CGridActivityList::OnDClicked(int col,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	if (col != ACTION_BUTTON)
	{
		OpenPO(row) ;
	}
}

void CGridActivityList::OpenPO(long row)
{
	if ( (row >= GetNumberRows()) || (row < 0))
	{
		return;
	}

	long lOrderID = (long) QuickGetNumber(ORDER_ID, row);

//	if ((m_pCustomerViewFrame == NULL) || (m_pCustomerViewFrame != NULL && (FALSE == ::IsWindow(m_pCustomerViewFrame->m_hWnd))))
//	{
		m_pCustomerViewFrame = g_pTemplateCustomerPO->CreateNewFrame(NULL,NULL) ;
		if (m_pCustomerViewFrame != NULL)
		{
			m_pCustomerViewFrame->InitialUpdateFrame(NULL, true) ;
		}
		else
		{
			MessageBox("Could not open customer dialog.", "Error", MB_OK);
		}
//	}

//	if (TRUE == ::IsWindow(m_pCustomerViewFrame->m_hWnd))
//	{
		//this->GetParent()->ShowWindow(SW_SHOWMINIMIZED);
//		m_pCustomerViewFrame->ShowWindow(SW_SHOW);
		CCustomerView* pView = (CCustomerView*) m_pCustomerViewFrame->GetActiveView() ;
		pView->FindByOrderNumber(lOrderID);
//	}
}

void CGridActivityList::ViewCustomer(long row)
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

int CGridActivityList::OnCanSizeTopHdg()
{ 
	return FALSE; 
} 

BOOL CGridActivityList::OnCanSizeCol(int /*col*/)
{
	return TRUE;
}

void CGridActivityList::OnTH_LClicked(int col, long row, int updn, RECT* rect, POINT* point, BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	if (col == ACTION_BUTTON) return;
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
}

int CGridActivityList::SortBy(int col, int flag /*= UG_SORT_ASCENDING*/)
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

	if (m_iSortCol == CREATED_DATE)
	{
        iRetVal = CCFGrid::SortBy(CREATED_DATE_NUMERIC, flag);	
	}
	else if (m_iSortCol == FOLLOW_UP_DATE)
	{
		iRetVal = CCFGrid::SortBy(FOLLOW_UP_DATE_NUMERIC, flag);
	}
	else
	{
		iRetVal = CCFGrid::SortBy(col, flag);
	}

	RedrawAll();
	return iRetVal;
}

int CGridActivityList::OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags)
{
	return CCFGrid::OnSortEvaluate(cell1, cell2, flags);
}

CString CGridActivityList::GetSortString()
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

	if (strSort.GetLength() > 0)
	{
		strSort += ",";
	}
	strSort += "ID DESC";
	
	return strSort;
}

void CGridActivityList::UpdateRowColor(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	/*bool bHasAlerts = (TRUE == QuickGetBool(HASALERTS, lRow));
	bool bCancelled = (TRUE == QuickGetBool(CANCELLED, lRow));
	
	if (bHasAlerts)
	{
		SetRowColor(lRow, CGlobals::COLOR_BLUE, CCFGrid::EnColorMode_TEXT);
		SetRowColor(lRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK);
	}

	if (bCancelled)
	{
		SetRowColor(lRow, CGlobals::COLOR_RED, CCFGrid::EnColorMode_BACK);
	}*/
}

void CGridActivityList::OnRowChange(long oldrow, long newrow)
{
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
	::PostMessage((GetParent())->m_hWnd, CGlobals::WM_ACTIVITY_DATA_UPDATE, 0, 0) ;
}

int CGridActivityList::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(param);
	if((ID == m_iButtonCellTypeIndex) && (msg == UGCT_BUTTONDOWN))
	{
		if ( HandleAction( row ) )
		{
			Update();
		}
	}
	
	return TRUE;
}

BOOL CGridActivityList::HandleAction( long row )
{
	switch ((int)QuickGetNumber(ACTIVITY_TYPE_ID, row))
	{
		case CGlobals::ACTIVITY_CHANGED_PO_RECEIVED:
		case CGlobals::ACTIVITY_CANCELLED_PO_RECEIVED:
		case CGlobals::ACTIVITY_SPACTION_RECEIVED:
		case CGlobals::ACTIVITY_MEASURE_APPT_RESCHEDULED:
		case CGlobals::ACTIVITY_PRODUCT_PICKED_UP:
		case CGlobals::ACTIVITY_XML_ERROR_RECEIVED:
		case CGlobals::ACTIVITY_SCHEDULE_WILL_CALL_RECEIVED:
		case CGlobals::ACTIVITY_COMPLETE_SERVICE_FAILED:
		case CGlobals::ACTIVITY_PRODUCT_CHANGED_PO_RECEIVED:
		case CGlobals::ACTIVITY_SCHEDULE_UPDATE_FAILED:
			{
				CloseActivity((int)QuickGetNumber(ACTIVITY_ID, row));
			}
			break;
		case CGlobals::ACTIVITY_CALL_CUSTOMER:
			{
				MessageBox("Not Implemented...", "Notice");
			}
			break;
		case CGlobals::ACTIVITY_UPDATE_MEASURE_CAPACITY:
			{
				MessageBox("Not Implemented...", "Notice");
			}
			break;
		default:
			{
				CPermissions perm;
				if (perm.IsAdmin())
				{
					CloseActivity((int)QuickGetNumber(ACTIVITY_ID, row));
				}
				else
				{
					MessageBox("You do not have permissions to close this activity!", "Notice!");
				}
			}
			break;
	}
	return TRUE;
}

bool CGridActivityList::CloseActivity(int iActivityID)
{
	bool bSuccess = false;

	try
	{
		CString strDateTime = CGlobals::GetCurrentSystemTime().Format("%m/%d/%Y %H:%M:%S");
		CString strSQL;
		strSQL.Format("UPDATE ActivityList SET ClosedByID = %d, ClosedDate = '%s' WHERE ID = %d", m_iUserID, strDateTime, iActivityID);
		g_dbFlooring.ExecuteSQL(strSQL);
		bSuccess = true;
	}
	catch (CDBException* e)
	{
		CString strMsg = e->m_strError;
		::MessageBox(NULL, strMsg, "Could not update activity!", MB_OK);
		e->Delete();
	}

	return bSuccess;
}

BOOL CGridActivityList::OnCanMove(int /* oldcol */, long /* oldrow */, int newcol, long newrow)
{
	UNREFERENCED_PARAMETER(newrow);
	UNREFERENCED_PARAMETER(newcol);
	//bool bValue ;
	//QuickGetReadOnly(newcol, newrow, &bValue) ;
	//return !bValue ;
	return TRUE;
}

void CGridActivityList::ReOpenActivity(int iActivityID)
{
bool bSuccess = false;

	try
	{
		CString strSQL;
		strSQL.Format("UPDATE ActivityList SET ClosedByID = NULL, ClosedDate = NULL WHERE ID = %d", iActivityID);
		g_dbFlooring.ExecuteSQL(strSQL);
		bSuccess = true;
		Update();
	}
	catch (CDBException* e)
	{
		CString strMsg = e->m_strError;
		::MessageBox(NULL, strMsg, "Could not re-open activity!", MB_OK);
		e->Delete();
	}	
}

bool CGridActivityList::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridActivityList::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}