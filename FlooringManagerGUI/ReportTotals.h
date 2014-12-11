/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_REPORTTOTALS_H__DB704800_7083_450D_A17B_D8E9B2318866__INCLUDED_)
#define AFX_REPORTTOTALS_H__DB704800_7083_450D_A17B_D8E9B2318866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportTotals.h : header file
//

#include "CFScrollView.h"
#include "SetTotalMaterials.h"	// Added by ClassView
#include "SetTotalOptions.h"	// Added by ClassView
#include "SetCatagories.h"
#include "SetSubCat.h"

/////////////////////////////////////////////////////////////////////////////
// CReportTotals view

class CReportTotals : public CCFScrollView
{
protected:
	CReportTotals();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportTotals)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportTotals)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTime m_timeStart;
	bool m_abWorkThisDay[8] ;
	double **m_adAmounts;
	double **m_adSuperAmounts;
	UINT m_aiLinesPerDay[8];
	int m_iLastCatId;
	int m_iLastSubCatId;
	UINT m_DayIndex;
	int PrintPageBody(CDC *pDC, CRect rect);
	virtual void PrintPageBody(CDC *pDC, CPrintInfo *pInfo);
	virtual ~CReportTotals();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//	CSetTotalOptions m_setTotalOptions;
	CSetTotalMaterials m_setTotalMaterial;
	CSetCatagories m_setCats;
	CSetSubCat m_setSubCats;

	// Generated message map functions
	//{{AFX_MSG(CReportTotals)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	// Initializes the data structures, totals the amounts
	bool InitializeData(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTTOTALS_H__DB704800_7083_450D_A17B_D8E9B2318866__INCLUDED_)
