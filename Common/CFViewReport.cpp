/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CFViewReport.cpp : implementation file
//

#include "stdafx.h"
//#include "Flooring.h"
#include "CFViewReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCFViewReport

IMPLEMENT_DYNCREATE(CCFViewReport, CView)

CCFViewReport::CCFViewReport()
{
}

CCFViewReport::~CCFViewReport()
{
}


BEGIN_MESSAGE_MAP(CCFViewReport, CView)
	//{{AFX_MSG_MAP(CCFViewReport)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCFViewReport drawing

void CCFViewReport::OnDraw(CDC* /* pDC */)
{
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCFViewReport diagnostics

#ifdef _DEBUG
void CCFViewReport::AssertValid() const
{
	CView::AssertValid();
}

void CCFViewReport::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCFViewReport message handlers

void CCFViewReport::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
}

BOOL CCFViewReport::OnPreparePrinting(CPrintInfo* pInfo) 
{
	CView::OnPreparePrinting(pInfo);
	pInfo->SetMaxPage(1) ;
	pInfo->m_bPreview = true ;
	return DoPreparePrinting(pInfo);
}

void CCFViewReport::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnPrepareDC(pDC, pInfo);

	if (m_fontHuge.m_hObject == NULL)
	{
		m_fontHuge.CreateFont(
			30,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,				   // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");                  // lpszFacename
	}

	if (m_fontLarge.m_hObject == NULL)
	{
		m_fontLarge.CreateFont(
			20,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,                   // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");                  // lpszFacename
	}

	if (m_fontLargeSW.m_hObject == NULL)
	{
		m_fontLargeSW.CreateFont(
			20,                        // nHeight
			0,                         // nWidth
			900,                         // nEscapement
			900,                         // nOrientation
			FW_BOLD,	 			   // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS | CLIP_LH_ANGLES ,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");                 // lpszFacename
	}

	if (m_fontNormal.m_hObject == NULL)
	{
		m_fontNormal.CreateFont(
			18,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Times New Roman");                 // lpszFacename
	}

	if (m_fontNormalBold.m_hObject == NULL)
	{
		m_fontNormalBold.CreateFont(
			18,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,	               // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Times New Roman");                 // lpszFacename
	}

	if (m_fontSmallest.m_hObject == NULL)
	{
		m_fontSmallest.CreateFont(
			14,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");
	}
	if (m_fontTiny.m_hObject == NULL)
	{
		m_fontTiny.CreateFont(
			10,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");
	}
	if (m_fontTinySW.m_hObject == NULL)
	{
		m_fontTinySW.CreateFont(
			10,                        // nHeight
			0,                         // nWidth
			900,                         // nEscapement
			900,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS | CLIP_LH_ANGLES ,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");
	}
	if (m_fontFixedBold.m_hObject == NULL)
	{
		m_fontFixedBold.CreateFont(
			16,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			FIXED_PITCH | FF_MODERN,  // nPitchAndFamily
			"Courier New"	) ;
	}
    if (pDC->IsPrinting ()) 
	{ // If printing...
		pDC->SetMapMode(MM_ISOTROPIC) ;
		pDC->SetWindowExt(800,1050) ;
		pDC->SetViewportExt(pDC->GetDeviceCaps(HORZRES),pDC->GetDeviceCaps(VERTRES)) ;
    }
	else
	{
		CRect rect ;
		GetClientRect(&rect) ;
		pDC->SetMapMode(MM_ISOTROPIC) ;
		pDC->SetWindowExt(800,1050) ;
		pDC->SetViewportExt(rect.Width(), rect.Height()) ;
	}
}

void CCFViewReport::DrawBoxWithText(CDC *pDC, int iXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	CRect rect(iXPos, iYPos, iXPos + iWidth, iYPos + iHeight) ;
	pDC->Rectangle(rect) ;
	rect.DeflateRect(3,3) ;
	pDC->DrawText(strText, rect , nFormat) ;
}

void CCFViewReport::DrawBoxWithText(CDC *pDC, int *pXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	DrawBoxWithText(pDC, *pXPos, iYPos, iWidth, iHeight, strText, nFormat) ;
	*pXPos += iWidth ;
}

void CCFViewReport::DrawBoxWithText(CDC *pDC, int *pXPos, int *pYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	DrawBoxWithText(pDC, *pXPos, pYPos, iWidth, iHeight, strText, nFormat) ;
	*pXPos += iWidth ;
}

void CCFViewReport::DrawBoxWithText(CDC *pDC, int iXPos, int* pYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	DrawBoxWithText(pDC, iXPos, *pYPos, iWidth, iHeight, strText, nFormat) ;
	*pYPos += iHeight ;
}
