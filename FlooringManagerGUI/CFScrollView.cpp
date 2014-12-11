/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CFScrollView.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "CFScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCFScrollView

IMPLEMENT_DYNCREATE(CCFScrollView, CScrollView)

CCFScrollView::CCFScrollView()
: m_bResetOrientation(FALSE)
, m_sOldOrientation(0)
, m_strDivMarketFilter(_T(""))
, m_strDivisions(_T("All"))
, m_strMarkets(_T("All"))
{
	m_strTitle = _T( "" );
	m_timeFilterTime = CGlobals::GetCurrentSystemTime();
}

CCFScrollView::~CCFScrollView()
{
	// Release the printing font
	m_PrintFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCFScrollView, CScrollView)
	//{{AFX_MSG_MAP(CCFScrollView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCFScrollView drawing

void CCFScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CString strTitle = GetParentFrame()->GetTitle();
	GetParentFrame()->SetTitle( strTitle + "" + m_strTitle) ;

	CRect rect ;
	this->GetClientRect(&rect) ;

	CSize size ;
	size.cx = long(rect.Width() * .95) ;
	size.cy = rect.Height() * 2 ;

	SetScrollSizes(MM_TEXT, size);
}

void CCFScrollView::OnDraw(CDC* /* pDC */)
{
	// TODO : add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCFScrollView diagnostics

#ifdef _DEBUG
void CCFScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCFScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCFScrollView message handlers

void CCFScrollView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnBeginPrinting(pDC, pInfo);
}

void CCFScrollView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_bResetOrientation)
	{
		m_bResetOrientation = FALSE;
		SetOrientation(m_sOldOrientation);
	}
	CScrollView::OnEndPrinting(pDC, pInfo);
}

void CCFScrollView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CFont* def_font = SelectFont(120, "Arial", pDC);
	PrintPageHeader( pDC, pInfo );
	PrintPageFooter( pDC, pInfo );
	PrintPageBody( pDC, pInfo );
	pDC->SelectObject(def_font);

}


void CCFScrollView::PrintPageHeader(CDC *pDC, CPrintInfo *pInfo)
{
	CRect& rcPage = pInfo->m_rectDraw;
	int iLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY) ;
	int iLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX) ;

	LPDEVMODE pDev = pInfo->m_pPD->GetDevMode() ;
	int iPixelPageBodyY ;
	int iPixelPageBodyX ;

	if (pDev->dmOrientation == DMORIENT_LANDSCAPE)
	{
		iPixelPageBodyY = int(iLogPixelsY * (8.5 - 1.5))  ;
		iPixelPageBodyX = int(iLogPixelsX * (11 - 1.5))  ;
	}
	else
	{
		iPixelPageBodyY = int(iLogPixelsY * (11 - 1.5))  ;
		iPixelPageBodyX = int(iLogPixelsX * (8.5 - 1.5))  ;
	}
	rcPage.left += (rcPage.right - rcPage.left - iPixelPageBodyX) / 2 ;
	rcPage.top += (rcPage.bottom - rcPage.top - iPixelPageBodyY) / 2 ;
	rcPage.right = rcPage.left +  iPixelPageBodyX ;
	rcPage.bottom = rcPage.top + iPixelPageBodyY ;

	CString strHeader = m_strTitle;
	// 1 - Prepare page header
	CSize sizeHeader = pDC->GetTextExtent( strHeader );

	// 2 - Draw header
	int nCurrentY = rcPage.top - (sizeHeader.cy * 2);
	pDC->TextOut( rcPage.left, nCurrentY, strHeader );
	nCurrentY += sizeHeader.cy;
	strHeader = "Market(s): " + m_strMarkets + ", Division(s): " + m_strDivisions;
	pDC->TextOut( rcPage.left, nCurrentY, strHeader );

	// 3 - Draw line
	pDC->MoveTo( rcPage.left, rcPage.top - 1);
	pDC->LineTo( rcPage.right, rcPage.top - 1);

	// 4 - Adjust remaining printable area
}

void CCFScrollView::PrintPageFooter(CDC *pDC, CPrintInfo *pInfo)
{
	CRect& rcPage = pInfo->m_rectDraw;

	// 1 - Prepare page footer
	CString strFooter;
	strFooter.Format( _T( "Page %d of %d" ), pInfo->m_nCurPage, pInfo->GetMaxPage() );
	CSize sizeFooter = pDC->GetTextExtent( strFooter );

	// 2 - Draw line
	pDC->MoveTo( rcPage.left, rcPage.bottom );
	pDC->LineTo( rcPage.right, rcPage.bottom );

	int nCurrentY = rcPage.bottom + (sizeFooter.cy);

	// 3 - Draw footer
	pDC->TextOut(	rcPage.left + ( rcPage.Width() - sizeFooter.cx ) / 2,
					nCurrentY,
					strFooter );


}

void CCFScrollView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO : Add your specialized code here and/or call the base class

	pDC->SetMapMode( MM_TEXT );
	m_nMapMode = MM_TEXT ;

	CScrollView::OnPrepareDC(pDC, pInfo);
	// Create special font for printing
	// ...prepare LOGFONT structure
	m_PrintFont.DeleteObject() ;
	LOGFONT lf;				// logical font structure
	::ZeroMemory( &lf, sizeof( lf ) );

	// ...12 point Times bold
	lf.lfHeight = - MulDiv( 12, pDC->GetDeviceCaps( LOGPIXELSX ), 72 );
	lf.lfWidth			= 0;
	lf.lfEscapement		= 0;
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_BOLD;
	lf.lfItalic			= FALSE;
	lf.lfUnderline		= FALSE;
	lf.lfStrikeOut		= FALSE;
	lf.lfCharSet		= DEFAULT_CHARSET;
	lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= DEFAULT_QUALITY;
	lf.lfPitchAndFamily	= VARIABLE_PITCH | FF_ROMAN;

	// ...create printing font
	m_PrintFont.CreateFontIndirect( &lf );

	pDC->SetMapMode( MM_TEXT );

}

BOOL CCFScrollView::OnPreparePrinting(CPrintInfo* pInfo) 
{	
	return DoPreparePrinting(pInfo) ;
}

void CCFScrollView::PrintPageBody(CDC * /* pDC */, CPrintInfo * /* pInfo */)
{
}

void CCFScrollView::DrawBoxWithText(CDC *pDC, int iXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	CRect rect(iXPos, iYPos, iXPos + iWidth, iYPos + iHeight) ;
	pDC->Rectangle(rect) ;
	rect.DeflateRect(3,3) ;
	pDC->DrawText(strText, rect, nFormat) ;
}

void CCFScrollView::DrawBoxWithText(CDC *pDC, int *pXPos, int iYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	DrawBoxWithText(pDC, *pXPos, iYPos, iWidth, iHeight, strText, nFormat) ;
	*pXPos += iWidth ;
}

void CCFScrollView::DrawBoxWithText(CDC *pDC, int *pXPos, int *pYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	DrawBoxWithText(pDC, *pXPos, pYPos, iWidth, iHeight, strText, nFormat) ;
	*pXPos += iWidth ;
}

void CCFScrollView::DrawBoxWithText(CDC *pDC, int iXPos, int* pYPos, int iWidth, int iHeight, CString strText, UINT nFormat)
{
	DrawBoxWithText(pDC, iXPos, *pYPos, iWidth, iHeight, strText, nFormat) ;
	*pYPos += iHeight ;
}

int CCFScrollView::DrawAlignedText(CDC *pDC, int iXPos, int iYPos, int iWidth, CString strText, UINT nFormat)
{
	CRect rect(iXPos + 25, iYPos, iXPos + iWidth, iYPos + 20) ;

	if (strText != "")
	{
	 	pDC->DrawText(strText, rect, nFormat | DT_CALCRECT) ;
	}
	else
	{
	 	pDC->DrawText("Test", rect, nFormat | DT_CALCRECT) ;
	}

	if ((nFormat & DT_RIGHT) == DT_RIGHT)
	{
		iWidth -= 25 ;
	}
	rect.right = iXPos + iWidth;
 	pDC->DrawText(strText, rect, nFormat) ;
	return rect.Height() ;
}

int CCFScrollView::DrawAlignedText(CDC *pDC, int *pXPos, int iYPos, int iWidth, CString strText, UINT nFormat)
{
	int iHeight = DrawAlignedText(pDC, *pXPos, iYPos, iWidth, strText, nFormat) ;
	*pXPos += iWidth ;
	return iHeight ;
}

int CCFScrollView::DrawAlignedText(CDC *pDC, int *pXPos, int *pYPos, int iWidth, CString strText, UINT nFormat)
{
	int iHeight = DrawAlignedText(pDC, *pXPos, pYPos, iWidth, strText, nFormat) ;
	*pXPos += iWidth ;
	return iHeight ;
}

int CCFScrollView::DrawAlignedText(CDC *pDC, int iXPos, int* pYPos, int iWidth, CString strText, UINT nFormat)
{
	int iHeight = DrawAlignedText(pDC, iXPos, *pYPos, iWidth, strText, nFormat) ;
	*pYPos += iHeight ;
	return iHeight ;
}

BOOL CCFScrollView::CreateDefaultPrinterDC( CDC* pDC, BOOL bLandscape/*= FALSE*/ )
{
	ASSERT_VALID( pDC );
	short sOrientation = GetOrientation();

	if (bLandscape)
	{
		sOrientation = SetOrientation(DMORIENT_LANDSCAPE);
		if (DMORIENT_LANDSCAPE != sOrientation)
		{
			m_sOldOrientation = sOrientation;
			m_bResetOrientation = TRUE;
		}
	}

	return AfxGetApp()->CreatePrinterDC( *pDC );
}

CFont* CCFScrollView::SelectFont(int size, CString strName, CDC *pDC )
{
	if (m_PrintFont.m_hObject != NULL)
	{
		m_PrintFont.DeleteObject();
	}
	VERIFY(m_PrintFont.CreatePointFont(size, strName, pDC));

	// Do something with the font just created...
	CFont* def_font = pDC->SelectObject(&m_PrintFont);
	CSize sizeText = pDC->GetOutputTextExtent("Test q__") ;

	int iLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY) ;
	int iLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX) ;

	m_iPageHeight = pDC->GetDeviceCaps(VERTRES);
	m_iPageWidth = pDC->GetDeviceCaps(HORZRES);

	if (m_iPageHeight > m_iPageWidth)
	{
		//portrait mode	
		m_iPixelPageBodyY = int(iLogPixelsY * (11 - 1.5))  ;
		m_iPixelPageBodyX = int(iLogPixelsX * (8.5 - 1.5))  ;
	}
	else
	{
		// landscape mode
		m_iPixelPageBodyY = int(iLogPixelsY * (8.5/* - 1.5*/))  ;
		m_iPixelPageBodyX = int(iLogPixelsX * (11.5/* - 1.5*/))  ;
	}

	m_iLinesPerPage = m_iPixelPageBodyY / (sizeText.cy) ;
	m_iLineHeight = sizeText.cy ;
	return def_font ;
}

CFont* CCFScrollView::SelectFont(int size, CString strName, CDC *pDC, int iExtraSpacing )
{
	// this version of the function is used when there needs to be extra spacing
	// between lines of text, such as when a line separates things

	CFont* def_font = SelectFont(size, strName, pDC);
	// adjust lines per page 
	CSize sizeText = pDC->GetOutputTextExtent("Test q__") ;
	m_iLinesPerPage = m_iPixelPageBodyY / (sizeText.cy+iExtraSpacing) ;

	return def_font;
}

// sets the orientation for the default printer
short CCFScrollView::GetOrientation()
{
	short sOrientation = 0;
	PRINTDLG pd;
	AfxGetApp()->GetPrinterDeviceDefaults( &pd );
	DEVMODE FAR *pDevMode=(DEVMODE FAR *)::GlobalLock(pd.hDevMode);
	sOrientation = pDevMode->dmOrientation;
	::GlobalUnlock(pd.hDevMode);

	return sOrientation;
}

short CCFScrollView::SetOrientation(short sOrientation)
{
	ASSERT( (sOrientation == DMORIENT_LANDSCAPE) || (sOrientation == DMORIENT_PORTRAIT)) ;
	short sOldOrientation = 0;
	PRINTDLG pd;
	AfxGetApp()->GetPrinterDeviceDefaults( &pd );
	DEVMODE FAR *pDevMode=(DEVMODE FAR *)::GlobalLock(pd.hDevMode);
	sOldOrientation = pDevMode->dmOrientation;
	pDevMode->dmOrientation = sOrientation;
	::GlobalUnlock(pd.hDevMode);

	return sOldOrientation;
}

// accessor function to set the Division and Market filter string
void CCFScrollView::SetDivMarketFilter(CString strFilter)
{
	m_strDivMarketFilter = strFilter;
}

// Accessor function to set the filter time object if the user selects this from the report configuration.
void CCFScrollView::SetFilterDateTime(COleDateTime time)
{
	m_timeFilterTime = time;
}
