/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridSOMerchandise.h: interface for the CGridSelectSOMerchandise class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "GridPOBase.h"
#include "NumericFormat.h"	// Added by ClassView
#include "NumericEdit.h"	// Added by ClassView
#include "SetViewOrderSOMerchandiseDetails.h"

const UINT wm_MATERIAL_SELECT = RegisterWindowMessage( "Material Select" ) ;

class CGridSelectSOMerchandise : public CGridPOBase  
{
public:
	CGridSelectSOMerchandise();
	virtual ~CGridSelectSOMerchandise();

	virtual int AppendRow();
	virtual int DeleteRow(long lRow);
	//virtual int UndeleteRow(long lRow);
	//virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	//virtual int OnEditStart(int col, long row,CWnd **edit);
	//virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	//virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
	virtual void OnSetup();
	virtual int OnHint(int col, long row, int section, CString *string, int *maxwidth);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	//virtual int OnMenuStart(int /* col */, long row, int section);
	//virtual void OnMenuCommand(int /* col */, long row, int section, int item);
	//virtual void CommitChanges();
	virtual	int RedrawAll() ;
	virtual void OnDrawFocusRect(CDC *dc, RECT *rect);

	void SetBasicLaborID(long lBasicLaborID);
	//virtual void UpdateRecordSet();
	void ShowDeleted(bool bShowDeleted) ;
	void SetAllowStatusUpdate(bool bAllowStatusUpdate) ;

	void SetFilter(CString strFilter);
	virtual void UpdateGrid();

	double GetSelectedID();

protected:
	enum {ID = -1, SO_NUMBER, SKU_NUMBER, DESCRIPTION, QUANTITY, MAT_STATUS, DELETED, LAST} ;

	//enum {ENTRY_MANUAL = 1, SPN_ENTRY_IMPORTED, SPN_ENTRY_IMPORTED_HANDMODIFIED, SPN_ENTRY_IMPORTED_XMLDELETED, SOSI_ENTRY_IMPORTED, SOSI_ENTRY_IMPORTED_HANDMODIFIED, SOSI_ENTRY_IMPORTED_XMLDELETED} ;

	//{{AFX_MSG(CGridSelectSOMerchandise)
	//afx_msg void OnKillFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectMaterial (long lId);
//	void UpdateGrid ();
	long GetDetailID(const long lRow);

	int GetUOMId(CString strUOM);

	bool SplitLineItem(long row);
	bool TransferMaterials();

	long m_BasicLaborID;
	CUGEdit m_editUpper;
	CNumericEdit m_editNumeric;
	CNumericFormat m_formatNumeric;
//	CCurrencyFormat m_formatCurrency;
	CSetViewOrderSOMerchandiseDetails m_setViewOrderSOMerchandiseDetails;
//	CSetUnitOfMeasure m_setUOM;
//	CSetMatStatus m_setMatStatus;

//	CUGCTDateTimePicker m_dtpControl;
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

inline void CGridSelectSOMerchandise::SetBasicLaborID(long lBasicLaborID)
{
	m_BasicLaborID = lBasicLaborID;
	UpdateGrid() ;
}

inline void CGridSelectSOMerchandise::SetFilter(CString strFilter)
{
	m_strRecordSetFilter = strFilter;
}