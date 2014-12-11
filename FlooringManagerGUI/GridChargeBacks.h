/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridChargeBacks.h: interface for the CGridChargeBacks class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "CFGrid.h"

class CGridChargeBacks : public CCFGrid  
{
public:
	CGridChargeBacks();
	virtual ~CGridChargeBacks();

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	void Update() ;

protected:
	enum {EDIT_CB = 2000, NEW_CB} ;
	enum {ID = -1, CB_NUMBER, ORIG_PO, CUSTOMER_NAME, APPROVAL_NUMBER, LAST} ;
	
	void EditCB(long row) ;
	void NewCB() ;
	CString GetPONumber(CString& strStoreNumber);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

};
