/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridJobAssignment.h: interface for the CGridJobAssignment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDJOBASSIGNMENT_H__3E9A1567_7306_46DD_AE68_CAC1B1D41D0B__INCLUDED_)
#define AFX_GRIDJOBASSIGNMENT_H__3E9A1567_7306_46DD_AE68_CAC1B1D41D0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\COMMON\CFGrid.h"

class CGridJobAssignment : public CCFGrid  
{
public:
	void InitializeData(COleDateTime dateScheduled);
	void OnSetup();
	CGridJobAssignment();
	virtual ~CGridJobAssignment();

protected:
	enum {ID = -1, NAME, PO_NUMBER, TYPE, INSTALLER, LAST} ;
	void SetSubContractorID(long lRow, int iSubId);
	int GetSubContractorID(long lRow);

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);
};

#endif // !defined(AFX_GRIDJOBASSIGNMENT_H__3E9A1567_7306_46DD_AE68_CAC1B1D41D0B__INCLUDED_)
