/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridSOMerchandise.h: interface for the CGridSOMerchandise class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "GridPOBase.h"

#include "CurrencyFormat.h"	// Added by ClassView
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetViewOrderSOMerchandiseDetails.h"
#include "SetOrderSOMerchandiseDetails.h"
#include "SetUintOfMeaser.h"	// Added by ClassView
#include "UGCTdtp.h"
#include "SetUintOfMeaser.h"	// Added by ClassView
#include "SetMatStatus.h"

class CGridSOMerchandise : public CGridPOBase  
{
public:
	CGridSOMerchandise();
	virtual ~CGridSOMerchandise();

	virtual int AppendRow();
	virtual int DeleteRow(long lRow);
	virtual int UndeleteRow(long lRow);
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
	virtual void OnSetup();
	virtual int OnHint(int col, long row, int section, CString *string, int *maxwidth);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual int OnMenuStart(int /* col */, long row, int section);
	virtual void OnMenuCommand(int /* col */, long row, int section, int item);
	virtual void CommitChanges();
	virtual	int RedrawAll() ;

	void SetBasicLaborID(long lBasicLaborID);
	virtual void UpdateRecordSet();
	void ShowDeleted(bool bShowDeleted) ;
	void SetAllowStatusUpdate(bool bAllowStatusUpdate) ;

	bool HasUnknownStatus();

protected:
	enum {ID = -1, SO_NUMBER, SKU_NUMBER, DESCRIPTION, QUANTITY, UOM, EXP_ARRIVAL_DATE, MAT_STATUS, ENTRY_METHOD_ID, DELETED, REVIEWED,
		  BASIC_LABOR_ID, SHORT_DESCRIPTION, SO_LINE_NUMBER, SO_MER_LINE_NUMBER, ORIGINAL_ID, PRESPLIT_QTY,
		  ORG_SO_NUMBER, ORG_SKU_NUMBER, ORG_DESCRIPTION, ORG_QUANTITY, ORG_UOM, ORG_EXP_ARRIVAL_DATE, ORG_MAT_STATUS, ORG_ENTRY_METHOD_ID, ORG_DELETED, 
		  ORG_REVIEWED, NOT_NEEDED, ORG_NOT_NEEDED, LAST} ;

	//enum {ENTRY_MANUAL = 1, SPN_ENTRY_IMPORTED, SPN_ENTRY_IMPORTED_HANDMODIFIED, SPN_ENTRY_IMPORTED_XMLDELETED, SOSI_ENTRY_IMPORTED, SOSI_ENTRY_IMPORTED_HANDMODIFIED, SOSI_ENTRY_IMPORTED_XMLDELETED} ;

	//{{AFX_MSG(CGridSOMerchandise)
	afx_msg void OnKillFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectMaterial (long lId);
	void UpdateGrid ();
	long GetDetailID(const long lRow);

	int GetUOMId(CString strUOM);

	bool SplitLineItem(long row);
	bool TransferMaterials();

	long m_BasicLaborID;
	CUGEdit m_editUpper;
	CNumericEdit m_editNumeric;
	CNumericFormat m_formatNumeric;
	CCurrencyFormat m_formatCurrency;
	CSetViewOrderSOMerchandiseDetails m_setViewOrderSOMerchandiseDetails;
	CSetUnitOfMeasure m_setUOM;
	CSetMatStatus m_setMatStatus;

	CUGCTDateTimePicker m_dtpControl;
	int m_dtpControlID;
	bool m_bShowDeleted;
	bool m_bAllowStatusUpdate ;

	virtual int GetFirstColumnIndex();
	virtual int GetLastColumnIndex();

	virtual void UpdateRowColor(long lRow);
	virtual bool IsRowDirty(long lRow) ;
	virtual bool IsColumnDirty(int iCol, long lRow) ;
	virtual void UpdateRowHeights() ;
};

inline void CGridSOMerchandise::SetBasicLaborID(long lBasicLaborID)
{
	m_BasicLaborID = lBasicLaborID;
	UpdateGrid() ;
}
