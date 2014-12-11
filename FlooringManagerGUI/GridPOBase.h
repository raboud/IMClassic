#pragma once

// CGridPOBase

#include "CFGrid.h"
#include "flooring.h"

typedef struct
{
	long lID;
	long lNewOrderID;
} _TRANSFER_STRUCT;

typedef CList<_TRANSFER_STRUCT, _TRANSFER_STRUCT> CRowList;

class CGridPOBase : public CCFGrid
{
public:
	CGridPOBase();
	virtual ~CGridPOBase();

	virtual int AppendRow();
	virtual int DeleteRow(long lRow);

	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual BOOL OnCanSizeCol(int col);
	virtual int OnCellTypeNotify(long ControlID,int col,long row,long msg,long param);
	virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnCharDown(UINT *vcKey, BOOL processed);
	virtual void OnKeyDown(UINT *vcKey, BOOL processed) ;
	virtual int OnEditStart(int col, long row, CWnd **edit) ;
	virtual int OnEditContinue(int oldcol, long oldrow, int *newcol, long *newrow) ;
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual void OnSetup();
	virtual int OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags);
	virtual void Reset();
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;

	virtual void UpdateGrid();
	virtual void UpdateRecordSet();
	void SetPODate(COleDateTime _date);
	void SetPOScheduleDate(COleDateTime _date);
	void SetStoreID(int iStoreID);
	void SetPOList(CPoList* pListPOs, bool bUpdateGrid = true);
	void CommitChanges();
	void SetInvokedFromSPN(bool bInvokedFromSPN);

	bool IsDirty() ;

protected:
	DECLARE_MESSAGE_MAP()

	COleDateTime m_datePO;
	COleDateTime m_datePOScheduleDate;

	int m_iStoreID;
	
	bool m_bConsolidatedView;
	CPoList m_listPOs;
	CString m_strRecordSetFilter;

	CRowList m_listTransferRows;

	bool m_bInvokedFromSPN;

	bool m_bCanModifyImported;
	bool m_bIsAdmin ;
	bool m_bCanMarkReviewed;

	virtual void UpdateRowColor(long lRow) = 0 ;
	void UpdateColors() ;

	virtual bool IsRowDirty(long lRow) = 0 ;
	virtual bool IsColumnDirty(int iCol, long lRow) = 0 ;

	int GetSelectedRows();
	CPoList m_listRows;
};

inline void CGridPOBase::SetInvokedFromSPN(bool bInvokedFromSPN)
{
	if (m_bInvokedFromSPN != bInvokedFromSPN)
	{
		m_bInvokedFromSPN = bInvokedFromSPN;
		UpdateGrid();
	}
}
