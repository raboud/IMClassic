/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridInvoicing.h: interface for the CGridChecking class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "CFGrid.h"
#include "CurrencyFormat.h"	// Added by ClassView
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetOrders.h"	// Added by ClassView
#include "SetChargeBacks.h"	// Added by ClassView

const UINT    wm_CHECKING = RegisterWindowMessage( "Checking" ) ;

class CGridChecking : public CCFGrid  
{
public:
	//bool IsDirty();
	virtual int AppendRow();
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row, CWnd **edit);
	virtual int OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag) ;
	void SetCheckID(int iCheckID);
	void UpdateRecordSet(void);
	CGridChecking();
	virtual ~CGridChecking();
	virtual void OnSetup();
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);

protected:
	enum {ID = -1, NAME, PO_NUMBER, PAID, PAID_AMOUNT, INVOICE, AMOUNT, INVOICE_DATE, LAST} ;
	bool m_bDirty;
//	CSetChargeBacks m_setChargeBacks;
	void UpdateTotals();
	void InitializeData(void);
	
	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	CCurrencyFormat m_formatCurrency;
	CNumericEdit m_editNumeric;
	int m_iCheckID ;
	double m_dOriginalPaid ;
	int m_iVendorID;
};
