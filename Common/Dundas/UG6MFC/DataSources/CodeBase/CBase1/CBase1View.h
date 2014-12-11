// CBase1View.h : interface of the CCBase1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBASE1VIEW_H__4F93F021_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_)
#define AFX_CBASE1VIEW_H__4F93F021_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCBase1View : public CView
{
protected: // create from serialization only
	CCBase1View();
	DECLARE_DYNCREATE(CCBase1View)

// Attributes
public:
	CCBase1Doc* GetDocument();

    MyCug   m_ctrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBase1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCBase1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCBase1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditFind();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditFindallcolumns();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CBase1View.cpp
inline CCBase1Doc* CCBase1View::GetDocument()
   { return (CCBase1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBASE1VIEW_H__4F93F021_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_)
