/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridUserAlerts.h: interface for the CGridUserAlerts class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GridUserAlerts_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
#define AFX_GridUserAlerts_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFGrid.h"

class CGridUserAlerts : public CCFGrid  
{
public:
	CGridUserAlerts(int iUserID);
	virtual ~CGridUserAlerts();

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
	void SetShowOnlyMyPOs(bool bShowOnlyMyPOs);
	void OnTimerUpdate();

protected:
	// menu items
	enum {OPEN_PO = 2000} ;

	// columns
	enum { PO_NUMBER = 0, STORE_NUMBER, CUSTOMER, ORDER_DATE, SCHEDULED_DATE, MARKET, DIVISION, LAST} ;

	int CGridUserAlerts::OnCanSizeTopHdg();
	BOOL CGridUserAlerts::OnCanSizeCol(int col);
	void UpdateRecordSetFilter();

	void OpenPO(long row) ;
	void ViewCustomer(long row);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	int m_iUserID;
	int m_iSortCol;
	int m_iSortFlags;  // sort direction
	CString m_strRecordSetFilter;
	bool m_bShowOnlyMyPOs;
	CFrameWnd* m_pCustomerViewFrame;

};

inline void CGridUserAlerts::SetShowOnlyMyPOs(bool bShowOnlyMyPOs)
{
	bool bTemp = m_bShowOnlyMyPOs;
	CPermissions perm;
	if ((perm.HasPermission("CanViewAllAlerts")) && (bShowOnlyMyPOs == false))
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
		Update();
	}
}

#endif // !defined(AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
