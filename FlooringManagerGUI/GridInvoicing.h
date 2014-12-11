/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridInvoicing.h: interface for the CGridInvoicing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDINVOICING_H__4F222AEF_BDAD_465D_A527_50D88F29A874__INCLUDED_)
#define AFX_GRIDINVOICING_H__4F222AEF_BDAD_465D_A527_50D88F29A874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CFGrid.h"
#include "CurrencyFormat.h"	// Added by ClassView
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetOrders.h"	// Added by ClassView

const UINT    wm_INVOICED = RegisterWindowMessage( "Invoiced" ) ;

class CGridInvoicing : public CCFGrid  
{
public:
	virtual int AppendRow();
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row, CWnd **edit);
	void UpdateRecordSet(void);
	void SetBilledDate( COleDateTime timeBilled);
	CGridInvoicing();
	virtual ~CGridInvoicing();
	virtual void OnSetup();
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	void SetVendorID(int iVendorID);
	int ConfirmSendCompleteServiceDocs();

protected:
	enum {ID = -1, NAME, PO_NUMBER, INVOICE, AMOUNT, INVOICE_DATE, IS_SOSI, IS_INSTALL, LAST} ;
	void UpdateTotals();
	void InitializeData(void);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	CCurrencyFormat m_formatCurrency;
	CNumericEdit m_editNumeric;
	COleDateTime m_BillDate;
	CSetOrders m_setOrders;
	int m_iVendorID;
};

#endif // !defined(AFX_GRIDINVOICING_H__4F222AEF_BDAD_465D_A527_50D88F29A874__INCLUDED_)
