/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridStores.cpp: implementation of the CGridUserAlerts class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridUserAlerts.h"
#include "DialogPo.h"
#include "SetVwUserAlerts.h"
#include "SetUserMarketDivisionAssignments.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CMultiDocTemplate* g_pTemplateCustomerPO ;

#include "CustomerView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridUserAlerts::CGridUserAlerts(int iUserID)
{
	m_bShowOnlyMyPOs = true;
	HighlightCurrentRow();
	m_strRecordSetFilter = "";
	SetUserID(iUserID);
	m_iSortCol = SCHEDULED_DATE;
	m_iSortFlags = UG_SORT_ASCENDING;
	m_pCustomerViewFrame = NULL;
}

CGridUserAlerts::~CGridUserAlerts()
{
}

void CGridUserAlerts::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn("PO Number", PO_NUMBER);
	AddColumn("Store Number", STORE_NUMBER);
	AddColumn("         Customer          ", CUSTOMER);
	AddColumn("    Market    ", MARKET);
	AddColumn("   Division   ", DIVISION);
	AddColumn("Order Date", ORDER_DATE);
	AddColumn("Scheduled Date", SCHEDULED_DATE);
	InitColumnHeadings();

	CUGCell cell;

	GetColDefault(PO_NUMBER, &cell) ;
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(PO_NUMBER, &cell) ;
	SetColDefault(STORE_NUMBER, &cell) ;	
	SetColDefault(ORDER_DATE, &cell) ;	
	SetColDefault(SCHEDULED_DATE, &cell) ;	

	SetColWidth(-1, 0);

	EnableMenu(TRUE) ;

}

void CGridUserAlerts::SetUserID(int iUserID)
{
	m_iUserID = iUserID;
	UpdateRecordSetFilter();
}

void CGridUserAlerts::UpdateRecordSetFilter()
{
	m_strRecordSetFilter = "";
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
}

void CGridUserAlerts::Update()
{
	//SetPaintMode(0);
	EnableUpdate(FALSE);

	// keep the current PO to see if we can reselect it after the update
	long lCurrentRow = GetCurrentRow();
	CString strCurrentPONumber = QuickGetText(PO_NUMBER, lCurrentRow);	
	
	// get rid of stale data
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	CSetVwUserAlerts setAlerts(&g_dbFlooring) ;
	setAlerts.m_strFilter = m_strRecordSetFilter;
	setAlerts.m_strSort = "ScheduleStartDate, CustomerName";
		
	setAlerts.Open() ;
	while (!setAlerts.IsEOF())
	{
		AppendRow() ;
		long lRow = GetNumberRows() - 1 ;

		QuickSetText(PO_NUMBER, lRow, setAlerts.m_PurchaseOrderNumber.Trim());
		//if (setAlerts.m_PurchaseOrderNumber.Trim() == strCurrentPONumber)
		//{
		//	lCurrentRow = lRow;
		//}
		QuickSetText(STORE_NUMBER, lRow, setAlerts.m_StoreNumber.Trim());
		QuickSetText(CUSTOMER, lRow, setAlerts.m_CustomerName.Trim()) ;
		QuickSetText(MARKET, lRow, setAlerts.m_MarketName.Trim()) ;
		QuickSetText(DIVISION, lRow, setAlerts.m_Division.Trim()) ;
		
		CString strDate = "";
		if (!setAlerts.IsFieldNull(&setAlerts.m_OrderDate))
		{
			strDate = setAlerts.m_OrderDate.Format("%m/%d/%Y");
			QuickSetText(ORDER_DATE, lRow, strDate) ;
		}
		
		if ((!setAlerts.IsFieldNull(&setAlerts.m_ScheduleStartDate)) && (setAlerts.m_Scheduled == TRUE))
		{
			strDate = setAlerts.m_ScheduleStartDate.Format("%m/%d/%Y");
			QuickSetText(SCHEDULED_DATE, lRow, strDate) ;
		}
		else
		{
			QuickSetText(SCHEDULED_DATE, lRow, "") ;
		}
				
		setAlerts.MoveNext() ;
	}
	setAlerts.Close();

	long lNumRows = GetNumberRows();
	if (lNumRows > 0)
	{
		SortBy(m_iSortCol, m_iSortFlags);
	
		for (long lIndex = 0; lIndex < lNumRows; lIndex++)
		{
			if (strCurrentPONumber == QuickGetText(PO_NUMBER, lIndex))
			{
				GotoRow(lIndex);
				break;
			}
		}
	}

	EnableUpdate(TRUE);
	RedrawAll() ;
	//SetPaintMode(1);
}

int CGridUserAlerts::OnMenuStart(int col, long row, int section)
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

void CGridUserAlerts::OnMenuCommand(int /* col */, long row, int section, int item)
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

void CGridUserAlerts::OnSH_DClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	OpenPO(row) ;
}

void CGridUserAlerts::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	OpenPO(row) ;
}

void CGridUserAlerts::OpenPO(long row)
{
	CString strPONumber = QuickGetText(PO_NUMBER, row);
	CString strStoreNumber = QuickGetText(STORE_NUMBER, row);

	long lOrderID = CGlobals::OrderIDFromPOAndStoreNumber(strPONumber, strStoreNumber);

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

void CGridUserAlerts::ViewCustomer(long row)
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

int CGridUserAlerts::OnCanSizeTopHdg()
{ 
	return FALSE; 
} 

BOOL CGridUserAlerts::OnCanSizeCol(int /*col*/)
{
	return TRUE;
}

void CGridUserAlerts::OnTH_LClicked(int col, long row, int updn, RECT* rect, POINT* point, BOOL processed)
{
	m_iSortCol = col;
	if (1 == updn)
	{
		m_iSortFlags = UG_SORT_ASCENDING;
	}
	else
	{
		m_iSortFlags = UG_SORT_DESCENDING;
	}

	CCFGrid::OnTH_LClicked(col, row, updn, rect, point, processed);
}

int CGridUserAlerts::SortBy(int col, int flag /*= UG_SORT_ASCENDING*/)
{
	m_iSortCol = col;
	m_iSortFlags = flag;
	return CCFGrid::SortBy(col, flag);	
}

int CGridUserAlerts::OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags)
{
	if ((m_iSortCol == SCHEDULED_DATE) || (m_iSortCol == ORDER_DATE))
	{
		// Make sure that both cells contains values
		if( NULL == cell1->GetText())
			return 1;
		if( NULL == cell2->GetText())
			return -1;

		// If we are sorting in descending order, swap cell values
		if( flags & UG_SORT_DESCENDING )
		{
			CUGCell *ptr = cell1;
			cell1 = cell2;
			cell2 = ptr;
		}

		COleDateTime dt1;
		COleDateTime dt2;
		CString str1 = cell1->GetText();
		CString str2 = cell2->GetText();
		dt1.ParseDateTime(str1);
		dt2.ParseDateTime(str2);

		if ( dt1.m_status != COleDateTime::valid ) return 1;

		if ( dt2.m_status != COleDateTime::valid ) return -1;

		if (dt1 < dt2)
		{
			return -1;
		}
		else if (dt1 > dt2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return CCFGrid::OnSortEvaluate(cell1, cell2, flags);
	}
}

void CGridUserAlerts::OnTimerUpdate()
{
	Update();
}

bool CGridUserAlerts::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridUserAlerts::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}