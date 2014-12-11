// RealTimeView.cpp : implementation of the CRealTimeView class
//

#include "stdafx.h"
#include "RealTime.h"

#include "RealTimeDoc.h"
#include "RealTimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView

IMPLEMENT_DYNCREATE(CRealTimeView, CView)

BEGIN_MESSAGE_MAP(CRealTimeView, CView)
	//{{AFX_MSG_MAP(CRealTimeView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView construction/destruction

CRealTimeView::CRealTimeView()
{
	// TODO: add construction code here

}

CRealTimeView::~CRealTimeView()
{
}

BOOL CRealTimeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView drawing

void CRealTimeView::OnDraw(CDC* pDC)
{
	CRealTimeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView printing

BOOL CRealTimeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRealTimeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRealTimeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView diagnostics

#ifdef _DEBUG
void CRealTimeView::AssertValid() const
{
	CView::AssertValid();
}

void CRealTimeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRealTimeDoc* CRealTimeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRealTimeDoc)));
	return (CRealTimeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView message handlers

int CRealTimeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23422 );
	
	return 0;
}

void CRealTimeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CRealTimeView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
