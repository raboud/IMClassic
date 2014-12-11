/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridReports.h: interface for the CGridReports class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CFGrid.h"
#include "AutoRichEditCtrl.h"
#include "ugctmfnt.h"

class CGridReports : public CCFGrid
{
public:
	CGridReports();
	virtual ~CGridReports();
	void Update(void);
	void SetOrderId(int );
	virtual void OnSetup ();

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual BOOL OnCanMove(int /* oldcol */, long /* oldrow */, int /* newcol */, long /* newrow */) {return TRUE ;};

	void SetRTFEdit( CAutoRichEditCtrl* pEdit );

protected:
	enum {ID = -1, REPORT_DATE, NATURE, /*ACTION, CAUSE,*/ CREATED_BY, LAST_UPDATED_BY, LAST_UPDATED_DATE, LAST} ;
	int m_iOrderId;
	virtual void UpdateRowHeights() ;

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	CAutoRichEditCtrl* m_pRTFEdit;

	CString GetGridText(CString strRTFText);

	CUGMultiFontType	m_multiFont;
	int m_iMultiFontCellTypeIndex;

};

inline void CGridReports::SetRTFEdit( CAutoRichEditCtrl* pEdit )
{
	ASSERT (pEdit != NULL);
	ASSERT (IsWindow(pEdit->m_hWnd));
	m_pRTFEdit = pEdit;
}
