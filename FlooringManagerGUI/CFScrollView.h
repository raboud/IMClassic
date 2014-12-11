/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "atltime.h"
#if !defined(AFX_CFSCROLLVIEW_H__12F35223_DC6D_4BBC_B85E_A51FB3C39873__INCLUDED_)
#define AFX_CFSCROLLVIEW_H__12F35223_DC6D_4BBC_B85E_A51FB3C39873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFScrollView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCFScrollView view

class CCFScrollView : public CScrollView
{
protected:
	CCFScrollView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCFScrollView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCFScrollView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iLineHeight;
	int m_nTotalLines;		// hold total number of lines to print
	int m_iPageHeight;
	int m_iPageWidth;
	CString m_strTitle;
	BOOL CreateDefaultPrinterDC( CDC* pDC, BOOL bLandscape = FALSE );
	void DrawBoxWithText(CDC* pDC, int iXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	void DrawBoxWithText(CDC* pDC, int* iXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	void DrawBoxWithText(CDC* pDC, int* iXPos, int* iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	void DrawBoxWithText(CDC* pDC, int iXPos, int* iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	int DrawAlignedText(CDC* pDC, int iXPos, int iYPos, int iWidth, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE );
	int DrawAlignedText(CDC* pDC, int* iXPos, int iYPos, int iWidth, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE );
	int DrawAlignedText(CDC* pDC, int* iXPos, int* iYPos, int iWidth, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE );
	int DrawAlignedText(CDC* pDC, int iXPos, int* iYPos, int iWidth, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE );
	virtual ~CCFScrollView();
	enum {	ELEMENTS_PER_PAGE = 4, TOP_MARGIN = 100, BOTTOM_MARGIN = 100,
			LEFT_MARGIN = 200 };
	CFont m_PrintFont;	// special font for printing
	int m_iPixelPageBodyY ;
	int m_iPixelPageBodyX ;
	int m_iLinesPerPage ;
	virtual void PrintPageFooter (CDC* pDC, CPrintInfo* pInfo);
	virtual void PrintPageBody (CDC* pDC, CPrintInfo* pInfo);
	virtual void PrintPageHeader (CDC* pDC, CPrintInfo* pInfo);
	CFont* SelectFont(int size, CString strName, CDC* pDC);
	CFont* SelectFont(int size, CString strName, CDC *pDC, int iExtraSpacing );
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCFScrollView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
protected:
	// keeps track of whether or not the default orientation has been changed
	BOOL m_bResetOrientation;
	// holds the original orientation in case the orientation is changed
	short m_sOldOrientation;
	// gets orientation
	short GetOrientation();
	// sets the orientation for the default printer, returns old orientation
	short SetOrientation(short sOrientation);
public:
	// // holds the division and market filter string
	CString m_strDivMarketFilter;
	// // accessor function to set the Division and Market filter string
	void SetDivMarketFilter(CString strFilter);
protected:
	// COleDateTime object representing the date selected in the DateTime Control of the Report Configuration.
	COleDateTime m_timeFilterTime;
public:
	// Accessor function to set the filter time object if the user selects this from the report configuration.
	void SetFilterDateTime(COleDateTime time);
	void SetMarketsString(CString& strMarkets);
	void SetDivisionsString(CString& strDivisions);
protected:
	// holds a string suitable for printing that lists the divisions filtered into the associated report
	CString m_strDivisions;
	// holds a string suitable for printing the Markets that are filtered into the associated report
	CString m_strMarkets;
};

inline void CCFScrollView::SetMarketsString(CString& strMarkets)
{
	m_strMarkets = strMarkets;
}

inline void CCFScrollView::SetDivisionsString(CString& strDivisions)
{
	m_strDivisions = strDivisions;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFSCROLLVIEW_H__12F35223_DC6D_4BBC_B85E_A51FB3C39873__INCLUDED_)
