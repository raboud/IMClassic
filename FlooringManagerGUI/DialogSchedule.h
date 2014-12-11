/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_CDialogSchedule_H__8831725A_10BE_4B37_9BB4_F46FB568CCAB__INCLUDED_)
#define AFX_CDialogSchedule_H__8831725A_10BE_4B37_9BB4_F46FB568CCAB__INCLUDED_

#include "GridSchedule.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSchedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogSchedule dialog

class CDialogSchedule : public CDialog
{
// Construction
public:
	void SetUnschedled(long lCustomerId, long lOrderId);
	void SetScheduled (long lCustomerId, long lOrderId, COleDateTime dateSchedule, COleDateTime dateScheduleEnd, bool bAM);
	CDialogSchedule(CWnd* pParent = NULL);   // standard constructor

	CPoList m_listPOsWithModifiedSchedules;

// Dialog Data
	//{{AFX_DATA(CDialogSchedule)
	enum { IDD = IDD_SCHEDULE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSchedule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGridSchedule m_grid;
	long m_lOrderId;
	bool m_bSchedule;
	COleDateTime m_dateScheduled;
	COleDateTime m_dateScheduledEnd;
	bool m_bAM;
	long m_lCustomerId;

	// Generated message map functions
	//{{AFX_MSG(CDialogSchedule)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSCHEDULE_H__8831725A_10BE_4B37_9BB4_F46FB568CCAB__INCLUDED_)
