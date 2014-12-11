#pragma once

#include "cfgrid.h"
#include "CurrencyFormat.h"	// Added by ClassView

class CGridCheckList :
	public CCFGrid
{
public:
	CGridCheckList(void);
	~CGridCheckList(void);

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnSetup();
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	void Update() ;

protected:
	enum {EDIT_CHECK = 2000, EDIT_CHECK_DETAILS, NEW_CHECK, PRINT_CHECK, VIEW_CHECK, ADD_QUICKBOOKS} ;
	enum {ID = -1, CHECK_NUMBER, CHECK_DATE, CHECK_AMOUNT, /* VENDOR_ID, */ QBTXN_ID, LAST} ;

	void EditCheck(long row) ;
	void EditCheckDetail(long row) ;
	void NewCheck() ;
	void PrintCheck(long row);
	void ViewCheck(long row);
	void AddToQuickbooks(long row);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	CCurrencyFormat m_formatCurrency;
};
