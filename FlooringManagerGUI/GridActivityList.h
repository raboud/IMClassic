/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridActivityList.h: interface for the CGridActivityList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GridActivityList_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
#define AFX_GridActivityList_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFGrid.h"
#include "..\Common\DUNDAS\UG6MFC\CellTypes\UGCTsarw.h"
#include "..\Common\DUNDAS\UG6MFC\CellTypes\UGCTbutn.h"

class CGridActivityList : public CCFGrid  
{
public:
	CGridActivityList(int iUserID);
	virtual ~CGridActivityList();

	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual int OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags);
	virtual int SortBy(int col, int flag = UG_SORT_ASCENDING);
	virtual void OnTH_LClicked(int col, long row, int updn, RECT* rect, POINT* point, BOOL processed);
	virtual void OnRowChange(long oldrow, long newrow);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual int GetFirstColumnIndex();
	void Update() ;
	void SetUserID(int UserID);
	void SetShowOnlyMyActivities(bool bShowOnlyMyPOs, bool bUpdate = true);
	void SetShowAllActivities(bool bShowAllActivities, bool bUpdate = true);
	void SetCreateDateFilter(COleDateTime& dtStart, COleDateTime& dtEnd, bool bUpdate = true);
	CString GetActivityData();
	CString GetClosedByInfo();
	
	CUGSortArrowType m_CellTypeArrow;
	CUGButtonType m_CellTypeButton;

	int m_iArrowCellTypeIndex;
	int m_iButtonCellTypeIndex;

protected:
	// menu items
	enum {OPEN_PO = 2000, REOPEN_ACTIVITY} ;

	// columns
	enum { ACTIVITY_ID, ACTION_BUTTON, ACTIVITY_NAME, CREATED_DATE, FOLLOW_UP_DATE, STORE_NUMBER, PO_NUMBER, CUSTOMER, MARKET, DIVISION, ACTIVITY_TYPE_ID, ORDER_ID, CLOSED_BY_NAME, CLOSED_DATE, CREATED_DATE_NUMERIC, FOLLOW_UP_DATE_NUMERIC, ACTIVITY_DATA, CLOSED_BY_ID, LAST} ;

	char* aszSortString[LAST];

	int CGridActivityList::OnCanSizeTopHdg();
	BOOL CGridActivityList::OnCanSizeCol(int col);
	void UpdateRecordSetFilter();

	void OpenPO(long row) ;
	void ViewCustomer(long row);

	int m_iUserID;
	int m_iSortCol;
	int m_iLastSortCol;
	int m_iSortFlags;  // sort direction
	CString m_strRecordSetFilter;
	bool m_bShowOnlyMyActivities;
	bool m_bShowAllActivities;
	CFrameWnd* m_pCustomerViewFrame;

	COleDateTime m_dtCreateDateStart;
	COleDateTime m_dtCreateDateEnd;

	CString GetSortString();

	BOOL HandleAction( long row );
	bool CloseActivity(int iActivityID);
	void ReOpenActivity(int iActivityID);

	void UpdateRowColor(long lRow);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	bool m_bCanCloseCancelled;
};

inline void CGridActivityList::SetShowOnlyMyActivities(bool bShowOnlyMyActivities, bool bUpdate)
{
	bool bTemp = m_bShowOnlyMyActivities;
	if ((CGlobals::HasPermission("CanViewAllActivities")) && (bShowOnlyMyActivities == false))
	{
		m_bShowOnlyMyActivities = false;
	}
	else
	{
		m_bShowOnlyMyActivities = true;
	}

	if (bTemp != m_bShowOnlyMyActivities)
	{
		UpdateRecordSetFilter();
		if (bUpdate)
		{
			Update();
		}
	}
}

//inline void CGridActivityList::SetShowOnlyPOsWithAlerts(bool bShowOnlyPOsWithAlerts, bool bUpdate)
//{
//	if (m_bShowOnlyPOsWithAlerts != bShowOnlyPOsWithAlerts)
//	{
//		m_bShowOnlyPOsWithAlerts = bShowOnlyPOsWithAlerts;
//		UpdateRecordSetFilter();
//		if (bUpdate)
//		{
//			Update();
//		}
//	}
//
//	/*bool bTemp = m_bShowOnlyPOsWithAlerts;
//	CPermissions perm;
//	if ((perm.HasPermission("CanViewAllPOs")) && (bShowOnlyPOsWithAlerts == false))
//	{
//		m_bShowOnlyPOsWithAlerts = false;
//	}
//	else
//	{
//		m_bShowOnlyPOsWithAlerts = true;
//	}
//
//	if (bTemp != m_bShowOnlyPOsWithAlerts)
//	{
//		UpdateRecordSetFilter();
//		if (bUpdate)
//		{
//			Update();
//		}
//	}*/
//}

inline void CGridActivityList::SetShowAllActivities(bool bShowAllActivities, bool bUpdate)
{
	m_bShowAllActivities = bShowAllActivities;
	UpdateRecordSetFilter();
	if (bUpdate)
	{
		Update();
	}
}

inline void CGridActivityList::SetCreateDateFilter(COleDateTime& dtStart, COleDateTime& dtEnd, bool bUpdate)
{
	bool bChanged = (m_dtCreateDateStart != dtStart) || (m_dtCreateDateEnd != dtEnd);
	m_dtCreateDateStart = dtStart;
	m_dtCreateDateEnd = dtEnd;
	UpdateRecordSetFilter();
	if (bUpdate && bChanged)
	{
		Update();
	}
}

inline CString CGridActivityList::GetActivityData()
{
	int iRow = GetCurrentRow();
	if (iRow < 0)
	{
		return CString("");
	}
	else
	{
		return QuickGetText(ACTIVITY_DATA, GetCurrentRow());
	}
}

inline CString CGridActivityList::GetClosedByInfo()
{
	CString strName;
	int iRow = GetCurrentRow();
	if (iRow < 0)
	{
		strName = "";
	}
	else
	{
		strName.Format("%s on %s", QuickGetText(CLOSED_BY_NAME, iRow), QuickGetText(CLOSED_DATE, iRow));
	}
	
	if (strName.Find("(null)") != -1)
	{
		strName = "";
	}
	return strName;
}

inline int CGridActivityList::GetFirstColumnIndex()
{
	return ACTIVITY_NAME;
}

#endif // !defined(AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
