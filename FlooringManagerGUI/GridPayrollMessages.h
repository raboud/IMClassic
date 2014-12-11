/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridPayrollMessages.h: interface for the CGridPayrollMessages class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CFGrid.h"
#include "SetPayrollMessages.h"	// Added by ClassView

class CGridPayrollMessages : public CCFGrid  
{
public:
	CGridPayrollMessages();
	virtual ~CGridPayrollMessages();

	virtual void OnSetup();

	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnMenuStart(int col,long row,int section);
	virtual void OnCharDown(UINT *vcKey, BOOL processed);
	
	void Update (void);
	
	virtual void OnSH_DClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;
	virtual void OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed) ;

protected:

	enum {ID = -1, MESSAGE, START_DATE, END_DATE, LAST} ;

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	CSetPayrollMessages m_setPayrollMessages;
};
