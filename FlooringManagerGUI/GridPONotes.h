/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridPONotes.h: interface for the CGridPONotes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GridPONotes_H__5C2216D4_6BA7_4B06_BDF2_AD22FCD67027__INCLUDED_)
#define AFX_GridPONotes_H__5C2216D4_6BA7_4B06_BDF2_AD22FCD67027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\COMMON\CFGrid.h"

class CGridPONotes : public CCFGrid  
{
public:
	void Update(void);
	void SetOrderId(int );
	virtual void OnSetup ();
	CGridPONotes();
	virtual ~CGridPONotes();
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual BOOL OnCanMove(int /* oldcol */, long /* oldrow */ , int /* newcol*/, long /* newrow */ ) {return TRUE ;};

protected:
	enum {ID = -1, DATETIME, USER, NOTES, NOTETYPE, CANSENDTOEXPEDITOR, SENTVIAXML, DATETIMESENT, LAST} ;
	int m_iOrderId;

	bool CanSendToExpeditor(long row);
	bool SentToExpeditor(long row);
	//void SendToExpeditor(int iNoteID, bool bCopyToSASM, bool bCopyToExpeditorEmail);
	void QueueNoteForExpeditor(int iNoteID, bool bCopyToSASM, bool bCopyToExpeditorEmail);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	CPermissions* m_pperms;
};

#endif // !defined(AFX_GridPONotes_H__5C2216D4_6BA7_4B06_BDF2_AD22FCD67027__INCLUDED_)

