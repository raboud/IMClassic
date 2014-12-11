/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridSchedule.h: interface for the CGridSchedule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDSCHEDULE_H__EDBEC1DA_392A_4DA2_B77C_7B11091985D7__INCLUDED_)
#define AFX_GRIDSCHEDULE_H__EDBEC1DA_392A_4DA2_B77C_7B11091985D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\COMMON\CFGrid.h"
#include "SetOrders.h"	// Added by ClassView

class CGridSchedule : public CCFGrid  
{
public:
	void SetScheduled (long lCustomerId, long lOrderId, COleDateTime dateSchedule, COleDateTime dateScheduleEnd, bool bAM);
	void SetUnscheduled(long lCustomerId, long lOrderId);
	void Update();
	void OnSetup();
	CGridSchedule();
	virtual ~CGridSchedule();

	CPoList m_listSOSIPOsWithModifiedSchedules;
	CPoList m_listSPNPOsWithModifiedSchedules;
	CPoList m_listPOsWithModifiedSchedules;

	bool m_bRescheduled;
	bool m_bIsMeasure;

protected:
	enum {ID = -1, PO, MATERIAL_TYPE, MAT_SIZE, SCHEDULE, LAST} ;
	void Fill();

	virtual bool IsRowDirty(long lRow);
	virtual bool IsColumnDirty(int iCol, long lRow);

	long m_lOrderId;
	bool m_bSchedule;
	COleDateTime m_dateScheduled;
	COleDateTime m_dateScheduledEnd;
	bool m_bAM;
	long m_lCustomerId;
	CSetOrders m_setOrders;
	
};

#endif // !defined(AFX_GRIDSCHEDULE_H__EDBEC1DA_392A_4DA2_B77C_7B11091985D7__INCLUDED_)
