/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CustomerPickList.h: interface for the CCustomerPickList class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CFGrid.h"
#include "SetCustomer.h"	// Added by ClassView

const UINT    wm_CUSTOMER_SELECT = RegisterWindowMessage( "Customer Select" ) ;

class CCustomerPickList : public CCFGrid  
{
public:
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnCharDown(UINT *vcKey, BOOL processed);
	void Update (void);
	virtual void OnSetup();
	void SetCustomerSet (CSetCustomer* pSet);
	CCustomerPickList();
	virtual ~CCustomerPickList();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;

protected:

	enum {ID = -1, LAST_NAME, FIRST_NAME, ADDRESS, CITY, STATE, ZIP, LAST} ;
	void SelectCustomer(int col, long row);
	int GetSelectedCustomers();
	void MergeCustomers();
	CSetCustomer* m_pSet;
	CArray<int, int> m_aiSelectedCustIDs;

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);
};
