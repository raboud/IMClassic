/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridCalled.h: interface for the CGridCalled class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCALLED_H__5C2216D4_6BA7_4B06_BDF2_AD22FCD67027__INCLUDED_)
#define AFX_GRIDCALLED_H__5C2216D4_6BA7_4B06_BDF2_AD22FCD67027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\COMMON\CFGrid.h"

class CGridCalled : public CCFGrid  
{
public:
	void Update(void);
	void SetOrderId(int );
	virtual void OnSetup ();
	CGridCalled();
	virtual ~CGridCalled();
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual BOOL OnCanMove(int /* oldcol */, long /* oldrow */ , int /* newcol*/, long /* newrow */ ) {return TRUE ;};

protected:
	enum {ID = -1, DATE, TIME, USER, COMMENT, LAST} ;
	int m_iOrderId;

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

};

#endif // !defined(AFX_GRIDCALLED_H__5C2216D4_6BA7_4B06_BDF2_AD22FCD67027__INCLUDED_)

