/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridActivePOs.h: interface for the CGridActivePOs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GridActivePOs_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
#define AFX_GridActivePOs_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFGrid.h"
#include "..\Common\DUNDAS\UG6MFC\CellTypes\UGCTsarw.h"

class CGridActivePOs : public CCFGrid  
{
public:
	CGridActivePOs(int iUserID);
	virtual ~CGridActivePOs();

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual int OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags);
	virtual int SortBy(int col, int flag = UG_SORT_ASCENDING);
	virtual void OnTH_LClicked(int col, long row, int updn, RECT* rect, POINT* point, BOOL processed);
	void Update() ;
	void SetUserID(int UserID);
	void SetShowOnlyMyPOs(bool bShowOnlyMyPOs, bool bUpdate = true);
	void SetShowOnlyPOsWithAlerts(bool bShowOnlyPOsWithAlerts, bool bUpdate = true);
	void SetIncludeCancelledPOs(bool bIncludeCancelledPOs, bool bUpdate = true);
	void SetOrderDateFilter(COleDateTime& dtStart, COleDateTime& dtEnd, bool bUpdate = true);

	CUGSortArrowType m_CellTypeArrow;
	int m_iArrowCellTypeIndex;

protected:
	// menu items
	enum {OPEN_PO = 2000} ;

	// columns
	enum { PO_NUMBER = 0, STORE_NUMBER, CUSTOMER, ORDER_DATE, SCHEDULED_DATE, MARKET, DIVISION, ENTRY_METHOD, ORDER_DATE_NUMERIC, SCHEDULED_DATE_NUMERIC, HASALERTS, CANCELLED, ORDERID, LAST} ;

	char* aszSortString[LAST];

	int CGridActivePOs::OnCanSizeTopHdg();
	BOOL CGridActivePOs::OnCanSizeCol(int col);
	void UpdateRecordSetFilter();

	void OpenPO(long row) ;
	void ViewCustomer(long row);

	int m_iUserID;
	int m_iSortCol;
	int m_iLastSortCol;
	int m_iSortFlags;  // sort direction
	CString m_strRecordSetFilter;
	bool m_bShowOnlyMyPOs;
	bool m_bIncludeCancelledPOs;
	bool m_bShowOnlyPOsWithAlerts;
	CFrameWnd* m_pCustomerViewFrame;

	COleDateTime m_dtOrderDateStart;
	COleDateTime m_dtOrderDateEnd;

	CString GetSortString();

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	void UpdateRowColor(long lRow);
};

inline void CGridActivePOs::SetShowOnlyMyPOs(bool bShowOnlyMyPOs, bool bUpdate)
{
	bool bTemp = m_bShowOnlyMyPOs;
	if ((CGlobals::HasPermission("CanViewAllPOs")) && (bShowOnlyMyPOs == false))
	{
		m_bShowOnlyMyPOs = false;
	}
	else
	{
		m_bShowOnlyMyPOs = true;
	}

	if (bTemp != m_bShowOnlyMyPOs)
	{
		UpdateRecordSetFilter();
		if (bUpdate)
		{
			Update();
		}
	}
}

inline void CGridActivePOs::SetShowOnlyPOsWithAlerts(bool bShowOnlyPOsWithAlerts, bool bUpdate)
{
	if (m_bShowOnlyPOsWithAlerts != bShowOnlyPOsWithAlerts)
	{
		m_bShowOnlyPOsWithAlerts = bShowOnlyPOsWithAlerts;
		UpdateRecordSetFilter();
		if (bUpdate)
		{
			Update();
		}
	}

	/*bool bTemp = m_bShowOnlyPOsWithAlerts;
	CPermissions perm;
	if ((perm.HasPermission("CanViewAllPOs")) && (bShowOnlyPOsWithAlerts == false))
	{
		m_bShowOnlyPOsWithAlerts = false;
	}
	else
	{
		m_bShowOnlyPOsWithAlerts = true;
	}

	if (bTemp != m_bShowOnlyPOsWithAlerts)
	{
		UpdateRecordSetFilter();
		if (bUpdate)
		{
			Update();
		}
	}*/
}

inline void CGridActivePOs::SetIncludeCancelledPOs(bool bIncludeCancelledPOs, bool bUpdate)
{
	m_bIncludeCancelledPOs = bIncludeCancelledPOs;
	UpdateRecordSetFilter();
	if (bUpdate)
	{
		Update();
	}
}

inline void CGridActivePOs::SetOrderDateFilter(COleDateTime& dtStart, COleDateTime& dtEnd, bool bUpdate)
{
	bool bChanged = (m_dtOrderDateStart != dtStart) || (m_dtOrderDateEnd != dtEnd);
	m_dtOrderDateStart = dtStart;
	m_dtOrderDateEnd = dtEnd;
	UpdateRecordSetFilter();
	if (bUpdate && bChanged)
	{
		Update();
	}
}

#endif // !defined(AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
