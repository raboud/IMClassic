// Stock WatchView.cpp : implementation of the CStockWatchView class
//

#include "stdafx.h"
#include "Stock Watch.h"

#include "Stock WatchDoc.h"
#include "Stock WatchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockWatchView

IMPLEMENT_DYNCREATE(CStockWatchView, CView)

BEGIN_MESSAGE_MAP(CStockWatchView, CView)
	//{{AFX_MSG_MAP(CStockWatchView)
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
// CStockWatchView construction/destruction

CStockWatchView::CStockWatchView()
{
	// TODO: add construction code here

}

CStockWatchView::~CStockWatchView()
{
}

BOOL CStockWatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStockWatchView drawing

void CStockWatchView::OnDraw(CDC* pDC)
{
	CStockWatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CStockWatchView printing

BOOL CStockWatchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStockWatchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStockWatchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStockWatchView diagnostics

#ifdef _DEBUG
void CStockWatchView::AssertValid() const
{
	CView::AssertValid();
}

void CStockWatchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockWatchDoc* CStockWatchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockWatchDoc)));
	return (CStockWatchDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockWatchView message handlers

int CStockWatchView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23422 );
	
	return 0;
}

void CStockWatchView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CStockWatchView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}
