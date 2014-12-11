/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridRegMerchandise.h: interface for the CGridRegMerchandise class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "GridPOBase.h"

#include "CurrencyFormat.h"	// Added by ClassView
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetViewOrderRegMerchandiseDetails.h"
#include "SetOrderRegMerchandiseDetails.h"
#include "SetUintOfMeaser.h"	// Added by ClassView
#include "SetMatStatus.h"

class CGridRegMerchandise : public CGridPOBase  
{
public:
	CGridRegMerchandise();
	virtual ~CGridRegMerchandise();

	virtual int AppendRow();
	virtual int DeleteRow(long lRow);
	virtual int UndeleteRow(long lRow);
	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual int OnEditStart(int col, long row, CWnd **edit);
	virtual int OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag) ;
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
	virtual void OnSetup();
	virtual int OnHint(int col, long row, int section, CString *string, int *maxwidth);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed);
	virtual int OnMenuStart(int /* col */, long row, int section);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual	int RedrawAll() ;
	
	virtual void UpdateRecordSet();
	void ShowDeleted(bool bShowDeleted) ;
	void SetAllowStatusUpdate(bool bAllowStatusUpdate) {m_bAllowStatusUpdate = bAllowStatusUpdate ;} ;
	bool HasUnknownStatus();

protected:
	enum {ID = -1, SKU_NUMBER, DESCRIPTION, QUANTITY, UOM, STATUS, NOTES, ENTRY_METHOD_ID, DELETED, REVIEWED,
		ORG_SKU_NUMBER, ORG_DESCRIPTION, ORG_QUANTITY, ORG_UOM, ORG_STATUS, ORG_NOTES, ORG_ENTRY_METHOD_ID, ORG_DELETED, ORG_REVIEWED, LAST} ;

	//enum {ENTRY_MANUAL = 1, SPN_ENTRY_IMPORTED, SPN_ENTRY_IMPORTED_HANDMODIFIED, SPN_ENTRY_IMPORTED_XMLDELETED, SOSI_ENTRY_IMPORTED, SOSI_ENTRY_IMPORTED_HANDMODIFIED, SOSI_ENTRY_IMPORTED_XMLDELETED} ;
	//{{AFX_MSG(CGridRegMerchandise)
	afx_msg void OnKillFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectMaterial (long lId);
	void UpdateGrid ();

	void CommitChanges();
	bool TransferMaterials();
	long GetDetailID(const long lRow);

	CUGEdit m_editUpper;
	CNumericEdit m_editNumeric;
	CNumericFormat m_formatNumeric;
	CCurrencyFormat m_formatCurrency;
	CSetViewOrderRegMerchandiseDetails m_setViewOrderRegMerchandiseDetails;

	int GetUOMId(CString strUOM);

	CSetUnitOfMeasure m_setUOM;
	CSetMatStatus m_setStatus;

	virtual int GetFirstColumnIndex();
	virtual int GetLastColumnIndex();

	bool m_bShowDeleted;
	bool m_bAllowStatusUpdate ;

	virtual void UpdateRowColor(long lRow);
	virtual bool IsRowDirty(long lRow) ;
	virtual bool IsColumnDirty(int iCol, long lRow) ;
	virtual void UpdateRowHeights() ;
};
