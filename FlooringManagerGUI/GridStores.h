/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridStores.h: interface for the CGridStores class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
#define AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFGrid.h"

class CGridStores : public CCFGrid  
{
public:
	CGridStores();
	virtual ~CGridStores();

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	void Update() ;

	void ShowActiveOnly( bool bShowActiveOnly );

protected:
	// menu items
	enum {EDIT_STORE = 2000, NEW_STORE, DELETE_STORE} ;

	// columns
	enum {ID = -1, STORE_NUMBER, STORE_TYPE, MARKET, /*EXPEDITOR, DIRECT_PHONE_NUM,*/ STORE_PHONE_NUM, FAX_NUM, LAST} ;

	void EditStore(long row) ;
	void NewStore() ;
	void DeleteStore(long row);
	bool CanDeleteStore(int iStoreID);

	bool m_bShowActiveOnly;

	int CGridStores::OnCanSizeTopHdg();
	BOOL CGridStores::OnCanSizeCol(int col);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

};

#endif // !defined(AFX_GRIDSTORES_H__D61C34FE_6981_45D3_AF81_A7880F6BB448__INCLUDED_)
