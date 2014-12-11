/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DLGCALLEDLIST_H__173C4233_1F24_4C48_B084_6BFC037B2165__INCLUDED_)
#define AFX_DLGCALLEDLIST_H__173C4233_1F24_4C48_B084_6BFC037B2165__INCLUDED_

#include "GridCalled.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalledList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCalledList dialog

class CDlgCalledList : public CDialog
{
// Construction
public:
	void SetOrderId (int iOrderID);
	CDlgCalledList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalledList)
	enum { IDD = IDD_CALLED_LIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalledList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGridCalled m_gridCalled;
	int m_iOrderId;

	// Generated message map functions
	//{{AFX_MSG(CDlgCalledList)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALLEDLIST_H__173C4233_1F24_4C48_B084_6BFC037B2165__INCLUDED_)
