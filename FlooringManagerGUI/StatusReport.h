/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_STATUSREPORT_H__616AC12E_FCB1_44D4_845B_AD791C00DAD0__INCLUDED_)
#define AFX_STATUSREPORT_H__616AC12E_FCB1_44D4_845B_AD791C00DAD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusReport.h : header file
//
#include <afxtempl.h>
#include "CFScrollView.h"
#include "SetInvTotal.h"	// Added by ClassView
#include "SetCallDetails.h"

/////////////////////////////////////////////////////////////////////////////
// CStatusReport view

class CStatusReport : public CCFScrollView
{
protected:
	CStatusReport();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatusReport)

// Attributes
public:

// Operations
public:
	void SetDetailLevel(int iLevel);
	void SetStoreNumber(CString strStoreNumber);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusReport)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iDetailLevel;
	CString GetStoreNumber(CString strLine);
	int Lines (CString strLine);
//	CString GetSpokeWith(CSetCallDetails& set);
//	CString GetLocation(CSetCallDetails& set);
	CStringList m_listString;
	void SortReport();
	void BuildReport();
	long m_iReport;
	CString m_strStoreNumber ;
	POSITION m_Pos ;
	POSITION m_PosNextPage ;
	CArray <int, int> m_pageOffsets ;
	void GotoPage(int iPageNumber);
	virtual int PrintLine(CDC *pDC, int iX, int iY, int iW);
	virtual void PrintPageBody(CDC *pDC, CPrintInfo *pInfo);
	void DeterminePageBreaks();
	virtual ~CStatusReport();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStatusReport)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSREPORT_H__616AC12E_FCB1_44D4_845B_AD791C00DAD0__INCLUDED_)
