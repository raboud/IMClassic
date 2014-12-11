/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_CFVIEWREPORT_H__A5FFE678_8113_4B83_ACB9_906D621BF6F6__INCLUDED_)
#define AFX_CFVIEWREPORT_H__A5FFE678_8113_4B83_ACB9_906D621BF6F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFViewReport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCFViewReport view

class CCFViewReport : public CView
{
protected:
	CCFViewReport();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCFViewReport)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCFViewReport)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCFViewReport();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void DrawBoxWithText(CDC* pDC, int iXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	void DrawBoxWithText(CDC* pDC, int* iXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	void DrawBoxWithText(CDC* pDC, int* iXPos, int* iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	void DrawBoxWithText(CDC* pDC, int iXPos, int* iYPos, int iWidth, int iHeight, CString strText, UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER );
	CFont m_fontHuge ;
	CFont m_fontLarge ;
	CFont m_fontLargeSW ;
	CFont m_fontNormal ;
	CFont m_fontNormalBold ;
	CFont m_fontSmallest ;
	CFont m_fontTiny ;
	CFont m_fontTinySW ;
	CFont m_fontFixedBold ;
	//{{AFX_MSG(CCFViewReport)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFVIEWREPORT_H__A5FFE678_8113_4B83_ACB9_906D621BF6F6__INCLUDED_)
