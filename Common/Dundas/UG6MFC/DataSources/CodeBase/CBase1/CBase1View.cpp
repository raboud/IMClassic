// CBase1View.cpp : implementation of the CCBase1View class
//

#include "stdafx.h"
#include "MyCug.h"

#include "CBase1.h"

#include "CBase1Doc.h"
#include "CBase1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBase1View

IMPLEMENT_DYNCREATE(CCBase1View, CView)

BEGIN_MESSAGE_MAP(CCBase1View, CView)
	//{{AFX_MSG_MAP(CCBase1View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_FINDALLCOLUMNS, OnEditFindallcolumns)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBase1View construction/destruction

CCBase1View::CCBase1View()
{
	// TODO: add construction code here

}

CCBase1View::~CCBase1View()
{
}

BOOL CCBase1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCBase1View drawing

void CCBase1View::OnDraw(CDC* pDC)
{
	CCBase1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCBase1View printing

BOOL CCBase1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCBase1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCBase1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCBase1View diagnostics

#ifdef _DEBUG
void CCBase1View::AssertValid() const
{
	CView::AssertValid();
}

void CCBase1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCBase1Doc* CCBase1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCBase1Doc)));
	return (CCBase1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCBase1View message handlers

int CCBase1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT rect = {0,0,0,0};
	m_ctrl.CreateGrid(WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rect,this,123);

	return 0;
}

void CCBase1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	m_ctrl.MoveWindow(&rect);

	
}

void CCBase1View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
    CWaitCursor cw;

	int index = m_ctrl.AddDataSource(&GetDocument()->m_data);
	m_ctrl.SetDefDataSource(index);
	m_ctrl.SetGridUsingDataSource(index);
	m_ctrl.BestFit(0,m_ctrl.GetNumberCols()-1, 1, UG_BESTFIT_TOPHEADINGS);

	m_ctrl.SetNumberRows(GetDocument()->m_data.GetNumRows());

}

void CCBase1View::OnEditFind() 
{
	// TODO: Add your command handler code here
    m_ctrl.FindInAllCols(FALSE);
    m_ctrl.FindDialog();
	
}

BOOL CCBase1View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CCBase1View::OnEditFindallcolumns() 
{
	// TODO: Add your command handler code here
    m_ctrl.FindInAllCols(TRUE);
    m_ctrl.FindDialog();
	
}
