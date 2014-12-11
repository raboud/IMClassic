/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CFGrid.h: interface for the CCFGrid class.
//
#pragma once

#include "..\Common\DUNDAS\UG6MFC\Include\UGCtrl.h"
#include <afxtempl.h>

struct SuGridHeading
{
	CString strText ;
	int iCol ;
	int iRow ;
	BOOL bSortAscending;
	bool bVisible;
	int iDefWidth;
} ;

class CCFGrid : public CUGCtrl  
{
public:
	CCFGrid();
	virtual ~CCFGrid();

	enum EnColorMode {EnColorMode_BACK, EnColorMode_TEXT}  ;

	virtual int AppendRow();
	virtual int DeleteRow(long lRow);

	virtual BOOL OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
	virtual BOOL OnCanSizeCol(int col);
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnCharDown(UINT *vcKey, BOOL processed);
	virtual void OnKeyDown(UINT *vcKey, BOOL processed) ;
	virtual int OnEditStart(int col, long row, CWnd **edit) ;
	virtual int OnEditContinue(int oldcol, long oldrow, int *newcol, long *newrow) ;
	virtual void OnSetup();
	virtual void OnTH_LClicked(int col, long /* row */, int updn,RECT * /* rect */, POINT * /* point */, BOOL /* processed */);
	virtual void OnCB_LClicked(int updn, RECT *rect, POINT *point, BOOL processed);
	virtual int OnSortEvaluate(CUGCell* cell1, CUGCell* cell2, int flags);
	virtual void Reset();
	virtual void UpdateRowHeights() ;
	virtual int OnCanSizeRow(long /* row */) {return FALSE ;} ;
	
	void ClearAllDataRows();

	bool IsDirty() ;
		
protected:
	typedef CList<CString, CString> CRecordList;
	
	int AddColumn(CString strHeading, int iColumnID, int iRowID);
	int AddColumn(CString strHeading, int iColumnID);
	int AddColumn(CString strHeading);

	void DisplayColumn(int iColumnID, bool bShow);

	void InitDefaultFont();

	void ClearColumns();
	bool ColumnDefined(int iColumnID, int iRowID, int& iFoundIndex);

	void DeleteRecordList(CRecordset& cSet, CString strFilter, CString strTag);

	int GetColumnID(CString strHeading);
	int GetMaxColumnID();

	virtual int GetFirstColumnIndex();
	virtual int GetLastColumnIndex();

	void HighlightCurrentRow(bool bHighlight = true);

	void InitColumnHeadings();
	
	void QuickSetNumberDecimals(int iCol, long lRow, int iNumberOfDecimals);
	virtual void QuickGetReadOnly(int iCol, long lRow, bool* pbValue);
	void QuickSetReadOnly(int iCol, long lRow, bool);
	void QuickGetNumber(int iCol, long lRow, double* pfValue);
	double QuickGetNumber(int iCol, long lRow);
	void QuickGetBool(int iCol, long lRow, bool* pbValue);
	bool QuickGetBool(int iCol, long lRow);
	void QuickSetBool (int iCol, long lRow, bool bState);

	void SetRowColor(long lRow, COLORREF color, EnColorMode enMode);
	void SetRowTextColor(long lRow, COLORREF color);
	void SetRowBackColor(long lRow, COLORREF color);
	void SetRowHTextColor(long lRow, COLORREF color);

	int GetNumberOfRegularColumns();

	void HideColumn(int iColumnID);
	void ShowColumn(int iColumnID);

	void SortColumnContainer();
	static int Compare(LPCVOID a, LPCVOID b);

	virtual void UpdateGrid();
	virtual bool IsRowDirty(long lRow) = 0 ;
	virtual bool IsColumnDirty(int iCol, long lRow) = 0 ;

	CPen* m_pen;
	int m_fontID ;
	CRecordList m_listRecord;
	bool * m_auDirection;
	CArray<SuGridHeading, SuGridHeading&> m_asuHeadings;

	bool m_bInitHeadingsCalled;
	int m_iColumnToSizeTo ;

	
};
