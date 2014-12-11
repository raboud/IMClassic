/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridLabor.h: interface for the CGridLabor class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "GridPOBase.h"

#include "CurrencyFormat.h"	// Added by ClassView
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetBasicLabor.h"
#include "SetOptions.h"
#include "SetUintOfMeaser.h"	// Added by ClassView
#include "UGCTdtp.h"

//const UINT    wm_LABOR_UPDATE = RegisterWindowMessage( "Labor Update" ) ;

class CGridLabor : public CGridPOBase  
{
public:
	CGridLabor();
	virtual ~CGridLabor();
	virtual int AppendRow();
	int DeleteRow(long lRow);
	int UndeleteRow(long lRow);
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag) ;
	virtual int OnMenuStart(int /* col */, long row, int section);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
	virtual int OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags);
	virtual int OnHint(int col, long row, int section, CString *string, int *maxwidth);
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed);
	virtual	int RedrawAll() ;
	
	int AppendRow(CString strType);
	void SetOrderID (long lOrderID);
	void UpdateRecordSet(long lOrderID);
	void SetMaterialType(long lMaterialType, bool bShowActiveOnly = false);
	double CalculatePrice(bool bOnlyBasicToMinimum);

	void RecalculateRows();
	void ShowCFIPrice(bool bShowCFIColumn);
	void RefreshPrices();
	void ShowDeleted(bool bShowDeleted)  ;
	void ShowUnitCost(bool bShowUnitCost)  ;
	virtual void UpdateRowHeights() ;

protected:
	enum {ID = -1, LABOR_DESC, QUANTITY, UOM, RETAIL, EXTENSION, PRICE, COST, ON_INV, ON_WO, ENTRY_METHOD_ID, DELETED, REVIEWED, 
		ORG_LABOR_DESC, ORG_QUANTITY, ORG_UOM, ORG_RETAIL, ORG_EXTENSION, ORG_PRICE, ORG_COST, ORG_ON_INV, ORG_ON_WO, ORG_ENTRY_METHOD_ID, ORG_DELETED, 
		ORG_REVIEWED, LAST} ;
	//enum {ENTRY_MANUAL = 1, SPN_ENTRY_IMPORTED, SPN_ENTRY_IMPORTED_HANDMODIFIED, SPN_ENTRY_IMPORTED_XMLDELETED, SOSI_ENTRY_IMPORTED, SOSI_ENTRY_IMPORTED_HANDMODIFIED, SOSI_ENTRY_IMPORTED_XMLDELETED} ;
	//{{AFX_MSG(CGridLabor)
	afx_msg void OnKillFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectMaterial (long lId);
	void UpdateGrid ();
	long m_lMaterialType;
	bool m_bShowActiveOnly;
	CUGEdit m_editUpper;
	CNumericEdit m_editNumeric;
	double m_fMultiplier;
	double m_fCostMultiplier ;

	CNumericFormat m_formatNumeric;
	bool m_bShowDeleted;
	bool m_bShowCfiPrice ;
	bool m_bShowUnitCost ;
	bool m_bCanEditCustomCost ;
	bool m_bCanEditLaborCost ;

	CCurrencyFormat m_formatCurrency;
	void FilterBasicLabor ();
	void FilterBasicLabor (CString strOption);
	void FilterBasicLabor (long lRow);
	void FilterBasicLaborByID( long lBasicLaborID );
	
	CSetBasicLabor m_setBasicLabor;
	CSetOptions m_setOptions;
	CSetUnitOfMeasure m_setUOM;

	double CalculateRowRetail(long lRow);
	double CalculateRowPrice(long lRow, bool bOnInvoiceOnly = true);
	void SetUomId(long lId) ;
	//void SetUom(CString strOption) ;
	void FilterOptionByID(long ID);
	void FilterOptions(CString strOption);
	void FilterOptions(long lRow);
	void FilterOptions();
	bool IsRowType(const long lRow, char* strPrefix);
	long GetDetailID(const long lRow);
	bool HasImportedItems();

	virtual int GetFirstColumnIndex();
	virtual int GetLastColumnIndex();

	bool SplitLineItem(long row);
	CString GetRowType(long row);
	
	int InsertRow(long row, CString strType);

	void InitRow(long row, CString strType);

	virtual void UpdateRowColor(long lRow);
	virtual bool IsRowDirty(long lRow) ;
	virtual bool IsColumnDirty(int iCol, long lRow) ;

	int GetUOMId(CString strUOM);

	CUGCTDateTimePicker m_dtpControl;
	int m_dtpControlID;
};
