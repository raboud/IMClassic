// OnGetCell JoiningView.cpp : implementation of the COnGetCellJoiningView class
//

#include "stdafx.h"
#include "OnGetCell Joining.h"

#include "OnGetCell JoiningDoc.h"
#include "OnGetCell JoiningView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningView

IMPLEMENT_DYNCREATE(COnGetCellJoiningView, CView)

BEGIN_MESSAGE_MAP(COnGetCellJoiningView, CView)
	//{{AFX_MSG_MAP(COnGetCellJoiningView)
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
// COnGetCellJoiningView construction/destruction

COnGetCellJoiningView::COnGetCellJoiningView()
{
	// TODO: add construction code here

}

COnGetCellJoiningView::~COnGetCellJoiningView()
{
}

BOOL COnGetCellJoiningView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningView drawing

void COnGetCellJoiningView::OnDraw(CDC* pDC)
{
	COnGetCellJoiningDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningView printing

BOOL COnGetCellJoiningView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COnGetCellJoiningView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COnGetCellJoiningView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningView diagnostics

#ifdef _DEBUG
void COnGetCellJoiningView::AssertValid() const
{
	CView::AssertValid();
}

void COnGetCellJoiningView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COnGetCellJoiningDoc* COnGetCellJoiningView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COnGetCellJoiningDoc)));
	return (COnGetCellJoiningDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningView message handlers

int COnGetCellJoiningView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect(0,0,0,0);
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, rect, this, 1223 );
	
	return 0;
}

void COnGetCellJoiningView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect( rect );
	m_grid.MoveWindow( rect );
}

BOOL COnGetCellJoiningView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}
