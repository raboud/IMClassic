// Calendar DemoView.cpp : implementation of the CCalendarDemoView class
//

#include "stdafx.h"
#include "Calendar Demo.h"

#include "Calendar DemoDoc.h"
#include "Calendar DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView

IMPLEMENT_DYNCREATE(CCalendarDemoView, CView)

BEGIN_MESSAGE_MAP(CCalendarDemoView, CView)
	//{{AFX_MSG_MAP(CCalendarDemoView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView construction/destruction

CCalendarDemoView::CCalendarDemoView()
{
	// TODO: add construction code here

}

CCalendarDemoView::~CCalendarDemoView()
{
}

BOOL CCalendarDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView drawing

void CCalendarDemoView::OnDraw(CDC* pDC)
{
	CCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView printing

BOOL CCalendarDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCalendarDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCalendarDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView diagnostics

#ifdef _DEBUG
void CCalendarDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCalendarDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCalendarDemoDoc* CCalendarDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCalendarDemoDoc)));
	return (CCalendarDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView message handlers

int CCalendarDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 2342 );
	
	return 0;
}

void CCalendarDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

void CCalendarDemoView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

BOOL CCalendarDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}
