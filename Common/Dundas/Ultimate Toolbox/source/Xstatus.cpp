// ==========================================================================
// 							Class Implementation : COXStatusBar
// ==========================================================================

// Implementation file : xstatus.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                          
// //////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xstatus.h"

#ifdef WIN32 
#ifndef __OXMFCIMPL_H__
#include <..\src\afximpl.h>
#define __OXMFCIMPL_H__
#endif
#else

#ifndef __OX_AUXDATA_H__
	#include <..\src\auxdata.h> // for AUX_DATA struct
#define __OX_AUXDATA_H__
#endif __OX_AUXDATA_H__
#endif

#include <malloc.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

struct AFX_STATUSPANE
	{
	UINT    nID;        // IDC of indicator: 0 => normal text area
	UINT    nStyle;     // style flags (SBPS_*)
	int     cxText;     // width of string area in pixels
						//   on both sides there is a 1 pixel gap and
						//    a one pixel border, making a pane 4 pixels wider
	LPCSTR  lpszText;   // always far strings
	};

#define CX_BORDER   1
#define CY_BORDER   1

IMPLEMENT_DYNAMIC(COXStatusBar, CStatusBar)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:
	//	int			m_nCount;
	// --- The number of panes on this Statusbar

	//  CObArray	m_PaneBmp;
	// --- Each item represents a pane. When there is
	// 	   a pointer stored in it, that pane contains a bitmap
    // 	   Each item represents a pane. When there is         
	//     a WORD stored in it, that pane contains a COLOR

    //  CDWordArray m_ColorArray;
	// --- An array containing possible textcolors when drawing a pane with Text in it.
	
	//  CPtrArray  	m_EvolArray;
	// --- An array containing possible Objects that configure each a Progress bar in a pane.

	//  UINT		m_BarHeight;
	// --- The new height of the StatusBar
	
	//  HFONT 		m_hStatusFont;
	// --- The Font of the StatusBar

// Member functions ---------------------------------------------------------
// public:

COXStatusBar::COXStatusBar()
	: m_BarHeight(0),
	  m_hStatusFont(NULL)
	{
#ifndef WIN32
	HDC hDCScreen = ::GetDC(NULL);
	ASSERT(hDCScreen != NULL);
	   
	if (m_hStatusFont == NULL)
		{
		// load status bar font
		LOGFONT logfont;
		memset(&logfont, 0, sizeof(logfont));
		if (!GetSystemMetrics(SM_DBCSENABLED))
			{
			// 10 point height Sans Serif font
			logfont.lfHeight = -MulDiv(10, GetDeviceCaps(hDCScreen, LOGPIXELSY), 72);
			logfont.lfWeight = FW_NORMAL;
			logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
			static char BASED_CODE szFaceName[] = "MS Sans Serif";
			lstrcpy(logfont.lfFaceName, szFaceName);
			m_hStatusFont = ::CreateFontIndirect(&logfont);
			}

		if (m_hStatusFont == NULL)
			{
			if (!GetSystemMetrics(SM_DBCSENABLED))
				TRACE0("Warning: Using system font for status font\n");
			m_hStatusFont = (HFONT)::GetStockObject(SYSTEM_FONT);
			}
		}
		
	::ReleaseDC(NULL, hDCScreen);
#endif
	}

COXStatusBar::~COXStatusBar()
	{     
	// free strings before freeing array of elements
	for (int j = 0; j < m_nCount; j++)
		VERIFY(SetPaneText(j, NULL, FALSE));    // no update
	
	// free all bitmaps and their container objects
	int i(0);
	while(i < m_PaneBmp.GetSize())
		{
		if((CBmpInfo*)m_PaneBmp[i] != NULL)
			{
			((CBmpInfo*)m_PaneBmp[i])->m_pBitmap->DeleteObject();
			delete ((CBmpInfo*)m_PaneBmp[i])->m_pBitmap;			
			delete m_PaneBmp[i];
			}
		i++;
		}

	// free all progress container objects
	i = 0;
	while(i < m_EvolArray.GetSize())
		{
		if((CEvolInfo*)m_EvolArray[i] != NULL)
			{
			delete (CEvolInfo*)m_EvolArray[i];
			}
		i++;
		}

	}

BOOL COXStatusBar::Create(CWnd* pParentWnd,int nHeight, DWORD dwStyle, UINT nID)
	{
	ASSERT_VALID(pParentWnd);   // must have a parent

#ifdef WIN32
	// save the style
	m_dwStyle = (UINT)dwStyle;
#else
	// force WS_CLIPSIBLINGS (avoids SetWindowPos bugs)
	dwStyle |= WS_CLIPSIBLINGS;
#endif

	// create the HWND
	// Need to register a new window class to be sensitive for dubbleclicks
	CRect rect;
	rect.SetRectEmpty();
	if (!CWnd::Create(AfxRegisterWndClass(CS_DBLCLKS,
										  ::LoadCursor(NULL, IDC_ARROW),
										  (HBRUSH)(COLOR_BTNFACE + 1)),
		NULL, dwStyle, rect, pParentWnd, nID))
		return FALSE;

	// Note: Parent must resize itself for control bar to be resized

	// set initial font and calculate bar height
#ifdef WIN32
	SendMessage(WM_SETFONT, (WPARAM)afxData.hStatusFont);
#else
	OnSetFont((WPARAM) m_hStatusFont, 0);  // initialize font height etc
#endif

#ifdef WIN32
	// In 32 bit MFC no special place for the BarHeight to be stored.
	// Becausqe we need it later, we store it ourselves.
	m_BarHeight = nHeight;
#else
	if(nHeight > m_sizeFixedLayout.cy)
		m_sizeFixedLayout.cy = nHeight;
#endif
					
	return TRUE;
	}

inline AFX_STATUSPANE* COXStatusBar::_GetPanePtr(int nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nCount);
	ASSERT(m_pData != NULL);
	return ((AFX_STATUSPANE*)m_pData) + nIndex;
}

#ifdef WIN32
CSize COXStatusBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
	// Need to overload this function i WIN32 because it's used internally
	// to construct a Statusbar with a certain height and we're probably changing
	// that height
	{
	CSize BarSize = CStatusBar::CalcFixedLayout(bStretch, bHorz);

	if (BarSize.cy < m_BarHeight)
		BarSize.cy = m_BarHeight;

	return BarSize;
	}
#endif

BOOL COXStatusBar::SetIndicators(const UINT FAR* lpIDArray, int nIDCount)
	{
	m_nCount = nIDCount;
	// Init the Bitmap array
	for(int i = 0; i < m_nCount;i++)
		{
		m_PaneBmp.SetAtGrow(i, NULL);
		}
		
	// Init the Color array
	for(int j = 0; j < m_nCount;j++)
		{
		m_ColorArray.SetAtGrow(j, ::GetSysColor(COLOR_BTNTEXT));
		}
		
	// Init the Progress array
	for(int k = 0; k < m_nCount;k++)
		{
		m_EvolArray.SetAtGrow(k, NULL);
		}


	return CStatusBar::SetIndicators(lpIDArray, nIDCount);
	}  

BOOL COXStatusBar::SetPaneBitmap(int nIndex, UINT nIDResource , BOOL bUpdate /* = TRUE */,
	COLORREF clrBkGnd /* = ::GetSysColor(COLOR_BTNFACE) */)
	{
	CRect rect;
	UINT nID,nStyle;
	BITMAP bm;
	int cxWidth;
	BOOL bSucces = FALSE;
	
	CBmpInfo*	pBmpInfo;
	if(m_PaneBmp[nIndex] == NULL)
		// The pane we're referring to, has no bitmap assigned to it yet.
		{
		// The CBmpInfo is the class where all bitmap info will be stored
		pBmpInfo = new CBmpInfo;
		pBmpInfo->m_pBitmap = new CBitmap;
	    if (!pBmpInfo->m_pBitmap->LoadBitmap(nIDResource))
			{
			// fixed 15.01.1998
			delete pBmpInfo->m_pBitmap;
			delete pBmpInfo;
			m_PaneBmp[nIndex] = NULL;
			bSucces = FALSE;
			TRACE0("COXStatusBar::SetPaneBitmap: Cannot load bitmap resource!");
			////////
			}
		else
			{		
	    	pBmpInfo->m_nIDResource = nIDResource;
			bSucces = TRUE;
			}
		
		m_ColorArray[nIndex] = clrBkGnd;
	    }
	else 
		{
		if (((CBmpInfo*)m_PaneBmp[nIndex])->m_nIDResource != nIDResource)
			{
			((CBmpInfo*)m_PaneBmp[nIndex])->m_pBitmap->DeleteObject();
			// fixed 15.01.1998
		    if (!((CBmpInfo*)m_PaneBmp[nIndex])->m_pBitmap->LoadBitmap(nIDResource))
				{
				delete pBmpInfo->m_pBitmap;
				delete pBmpInfo;
				m_PaneBmp[nIndex] = NULL;
				bSucces = FALSE;
				TRACE0("COXStatusBar::SetPaneBitmap: Cannot load bitmap resource!");
				}
			else
				{
				((CBmpInfo*)m_PaneBmp[nIndex])->m_nIDResource = nIDResource;
				}
			///////////////
			m_ColorArray[nIndex] = clrBkGnd;
			}
		else
			return TRUE;
		}
		
    if(!bSucces)
    	return FALSE;
    	
    GetItemRect(nIndex, &rect);  // get pane rect

    // Check and set bitmap size to the pane
	pBmpInfo->m_pBitmap->GetObject(sizeof(bm), &bm);
	// Assign this Bitmap Info to the pane
	m_PaneBmp[nIndex] = pBmpInfo;
	GetPaneInfo(nIndex,nID,nStyle,cxWidth);
	SetPaneInfo(nIndex,nID,nStyle,bm.bmWidth);

	// Adding, removing or changing a Bitmap can cause a pane to grow or shrink.
	// Could influence the stored rects for the evolution panes, so recalc them
	RecalcEvolutionRect();

	if(bUpdate)
		InvalidateRect(rect, FALSE);
	
	return TRUE;
	}
	
BOOL COXStatusBar::SetPaneText(int nIndex, LPCSTR lpszNewText, BOOL bUpdate /* =TRUE */,
	COLORREF clrText /* = ::GetSysColor(COLOR_BTNTEXT) */)
	{
	ASSERT_VALID(this);

	AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
	if (pSBP == NULL)
		return FALSE;

	if (pSBP->lpszText != NULL)
		{
		// Check Text and Color
		if (lpszNewText != NULL && lstrcmp(pSBP->lpszText, lpszNewText) == 0 &&
			m_ColorArray[nIndex] == clrText)
			return TRUE;        // nothing to change

		// Free the memory allocated for the previous string
#ifdef WIN32
		free((LPVOID)pSBP->lpszText);
#else
		_ffree((LPVOID)pSBP->lpszText);
#endif
		}

	m_ColorArray[nIndex] = clrText;
	BOOL bOK = TRUE;
	if (lpszNewText == NULL || *lpszNewText == '\0')
		{
		pSBP->lpszText = NULL;
		}
	else
		{
		// allocate memory for the new string
#ifdef WIN32
		pSBP->lpszText = _tcsdup(lpszNewText);
#else
		pSBP->lpszText = _fstrdup(lpszNewText);
#endif
		if (pSBP->lpszText == NULL)
			bOK = FALSE; // old text is lost and replaced by NULL
		}

	if (bUpdate)
		{
		// invalidate the text of the pane - but not the border
		CRect rect;
		GetItemRect(nIndex, &rect);
#ifdef WIN32
   		if (!(pSBP->nStyle & SBPS_NOBORDERS))
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
		else
			rect.top -= CY_BORDER;  // base line adjustment
#else
		rect.InflateRect(-CX_BORDER, -CY_BORDER);
#endif
		InvalidateRect(rect, FALSE);
		}
	return bOK;
	
	}

void COXStatusBar::FillSolidRect(CDC* pDC, LPCRECT lpRect, COLORREF clr)
	// --- In  : pDC : the device context to draw on
	//			 lpRect : the client coordinates to draw with
	//			 clr : the color of the rectangle
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a Solid rectangle in a specified color
	{
	ASSERT_VALID(this);
	ASSERT(pDC != NULL);

	::SetBkColor(pDC->m_hDC, clr);
	::ExtTextOut(pDC->m_hDC, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	}

void COXStatusBar::FillSolidRect(CDC* pDC, int x, int y, int cx, int cy, COLORREF clr)
	// --- In  : pDC : the device context to draw on
	//			 x,y,cx,cy : the client coordinates to draw with
	//			 clr : the color of the rectangle
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a Solid rectangle in a specified color
	{
	ASSERT_VALID(this);
	ASSERT(pDC != NULL);

	::SetBkColor(pDC->m_hDC, clr);
	CRect rect(x, y, x + cx, y + cy);
	::ExtTextOut(pDC->m_hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
	}

void COXStatusBar::Draw3dRect(CDC* pDC, LPCRECT lpRect,
	COLORREF clrTopLeft, COLORREF clrBottomRight)
	// --- In  : pDC : the device context to draw on
	//			 lpRect : the client coordinates to draw with
	//			 clrTopLeft : the color of the Top left rectangle
	//			 clrBottomRight : the color of the bottom right rectangle
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a rectangle with a 3D look
	{
	Draw3dRect(pDC, lpRect->left, lpRect->top, lpRect->right - lpRect->left,
		lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
	}

void COXStatusBar::Draw3dRect(CDC* pDC, int x, int y, int cx, int cy,
	COLORREF clrTopLeft, COLORREF clrBottomRight)
	// --- In  : pDC : the device context to draw on
	//			 x,y,cx,cy : the client coordinates to draw with
	//			 clrTopLeft : the color of the Top left rectangle
	//			 clrBottomRight : the color of the bottom right rectangle
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a rectangle with a 3D look by drawing 4 rectangles
	//				in such a way upon one another so they get a Chiseled look
	{
	FillSolidRect(pDC, x, y, cx - 1, 1, clrTopLeft);
	FillSolidRect(pDC, x, y, 1, cy - 1, clrTopLeft);
	FillSolidRect(pDC, x + cx, y, -1, cy, clrBottomRight);
	FillSolidRect(pDC, x, y + cy, cx, -1, clrBottomRight);
	}
	
void COXStatusBar::DoPaint(CDC *pDC)
	{

	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	
    CControlBar::DoPaint(pDC);

    CRect rect;
	GetClientRect(rect);

#ifdef WIN32
	CalcInsideRect(rect, TRUE);
#else
	CalcInsideRect(rect);
#endif

	AFX_STATUSPANE* pSBP;
	int i;

	ASSERT(m_hFont != NULL);        // must have a font !
	HGDIOBJ hOldFont = pDC->SelectObject(m_hFont);

#ifdef WIN32
	// protect space for size box
	int cxSizeBox = m_bHideSizeBox ? 0 : m_cxSizeBox;
	int xMax = (rect.right -= cxSizeBox);
	if (cxSizeBox == 0)
		xMax += m_cxRightBorder + 1;
	int cxExtra = rect.Width() + m_cxDefaultGap;
#else
	int cxExtra = rect.Width() - m_cxRightBorder + m_cxDefaultGap;
#endif
			 
	// first walk through to calculate extra space
	for (i = 0, pSBP = (AFX_STATUSPANE*)m_pData; i < m_nCount; i++, pSBP++)
		cxExtra -= (pSBP->cxText + CX_BORDER * 4 + m_cxDefaultGap);
	// if cxExtra <= 0 then we will not stretch but just clip

	for (i = 0, pSBP = (AFX_STATUSPANE*)m_pData; i < m_nCount; i++, pSBP++)
		{
		ASSERT(pSBP->cxText >= 0);
		int cxText = pSBP->cxText;
		if ((pSBP->nStyle & SBPS_STRETCH) && cxExtra > 0)
			{
			cxText += cxExtra;
			cxExtra = 0;
			}
		rect.right = rect.left + cxText + CX_BORDER * 4;
#ifdef WIN32
		rect.right = __min(rect.right, xMax);
		if (!afxData.bWin32s || ::RectVisible(pDC->m_hDC, &rect))
#else
		if (::RectVisible(pDC->m_hDC, &rect))
#endif
			{
			if (pSBP->nStyle & SBPS_PERCENT && m_EvolArray[i] != NULL)
				// This pane is a Progress pane, so draw the progress
				{
				DrawBarProgress(pDC, rect, i, pSBP->nStyle);
				}                              
			else
				{
		    	if(((CBmpInfo*)m_PaneBmp[i]) != NULL)
					// This pane is a pane with a bitmap , so draw the bitmap
	    			DrawStatusBmp(pDC, rect, i, pSBP->nStyle);
	    		else														 				// This pane is a Progress pane, so draw the progress
					// This pane is a pane with text , so draw the text
					DrawStatusText(pDC, rect, i, pSBP->lpszText, pSBP->nStyle);
				}
			}
		rect.left = rect.right + m_cxDefaultGap;
#ifdef WIN32
		if (rect.left >= xMax)
			break;
#endif
		}
	
	pDC->SelectObject(hOldFont);

#ifdef WIN32
   	// draw the size box in the bottom right corner
	if (cxSizeBox != 0)
		{
		int cxMax = __min(cxSizeBox, rect.Height()+m_cyTopBorder);
		rect.left = xMax + (cxSizeBox - cxMax) + CX_BORDER;
		rect.bottom -= CX_BORDER;
		HPEN hPenOld = (HPEN)pDC->SelectObject(afxData.hpenBtnHilite);
		for (int i = 0; i < cxMax; i += 4)
			{
			pDC->MoveTo(rect.left+i, rect.bottom);
			pDC->LineTo(rect.left+cxMax, rect.bottom-cxMax+i);
			}
		pDC->SelectObject(afxData.hpenBtnShadow);
		for (i = 1; i < cxMax; i += 4)
			{
			pDC->MoveTo(rect.left+i, rect.bottom);
			pDC->LineTo(rect.left+cxMax, rect.bottom-cxMax+i);
			}
		for (i = 2; i < cxMax; i += 4)
			{
			pDC->MoveTo(rect.left+i, rect.bottom);
			pDC->LineTo(rect.left+cxMax, rect.bottom-cxMax+i);
			}
		pDC->SelectObject(hPenOld);
		}
#endif

  }
  
void COXStatusBar::SetBarProgress(int nIndex, BOOL bUpdate /* = TRUE */, 
	DWORD dwTotal /* = 100 */, DWORD dwDone /* = 0 */)
	{
	CEvolInfo* pEvolInfo = (CEvolInfo*)m_EvolArray[nIndex];
	if (pEvolInfo == NULL)
		{
		TRACE(_T("The pane '%i'has never been SetUp as a progress pane"), nIndex);
		return; 
		}

	if (dwTotal > 0)
		pEvolInfo->m_BarPercent = (int)((dwDone * 100) / dwTotal);
	else
		pEvolInfo->m_BarPercent = 0;	
		
	// This will cause OnPaint to be called ...
	if (bUpdate)		
		RedrawWindow(&pEvolInfo->m_BarRect, NULL, RDW_UPDATENOW | /* RDW_ERASE | */
			 RDW_INVALIDATE);
	}

void COXStatusBar::ResetBar(int nIndex)
	{
	if(m_EvolArray[nIndex] != NULL)
		{
		//	Redraw the frame control under the gauge
		SetBarProgress(nIndex, TRUE, 60, 0);

		CEvolInfo*	pEvolInfo  = (CEvolInfo*)m_EvolArray[nIndex];
		delete pEvolInfo;
		m_EvolArray[nIndex] = NULL;
		}
	}
	
BOOL COXStatusBar::SetUpBar(int nIndex, BOOL bUpdate /* = TRUE */)
	{
	CEvolInfo*	pEvolInfo;
	if(m_EvolArray[nIndex] == NULL)
		{
		pEvolInfo = new CEvolInfo;
		m_EvolArray[nIndex] = pEvolInfo;

        GetItemRect(nIndex, &pEvolInfo->m_BarRect);  // get pane rect

        // Make the progressbar itself a little smaller than the pane
        pEvolInfo->m_BarRect.InflateRect(-2*CX_BORDER, -CY_BORDER);
        
        // Start at the utmost left of the pane = nothing done yet
        pEvolInfo->m_BarPercent = 0;

		//	Redraw the frame control under the gauge
		SetBarProgress(nIndex, bUpdate, 60, 0);
	    }
	else 
		ResetBar(nIndex);

	return TRUE;
	}
	
void PASCAL COXStatusBar::DrawBarProgress(CDC* pDC, CRect const& rect, int nPane, UINT nStyle)
	// --- In  : pDC : the device context to draw on
	//			 rect : the client coordinates of the pane to draw
	//			 nPane : the index of the pane to draw
	//			 nStyle : the style of the pane
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a standard 3D pane with a progressbar in it
	{
	ASSERT(pDC->m_hDC != NULL);
	
	PaintPane(pDC, rect, nStyle);

    // Do not draw a progress bar if the pane is disabled
    if(!(nStyle & SBPS_DISABLED))
    	{
		CEvolInfo* pEvolInfo = (CEvolInfo*)m_EvolArray[nPane];
		if (pEvolInfo == NULL)
			return; 
    	
		CBrush brBarColor(::GetSysColor(COLOR_ACTIVECAPTION)); // Foreground Color
		CBrush brBarUndone(::GetSysColor(COLOR_BTNFACE)); // Background Color
		char tmpBuf[10];
	
		CRect rectText(rect);
#ifdef WIN32
		if (!(nStyle & SBPS_NOBORDERS)) // only adjust if there are borders
			rectText.InflateRect(-2*CX_BORDER, -CY_BORDER);
		else
			rectText.OffsetRect(0, -CY_BORDER); // baselines line up
#else
		rectText.InflateRect(-2*CX_BORDER, -CY_BORDER);
#endif

		//	Draw the unfinished part
		int nxPos;
		RECT FillBar = pEvolInfo->m_BarRect;
		RECT TextRect = pEvolInfo->m_BarRect;
		nxPos = pEvolInfo->m_BarRect.left + (pEvolInfo->m_BarRect.Width() * pEvolInfo->m_BarPercent / 100);
		FillBar.left = nxPos;
		pDC->FillRect(&FillBar,&brBarUndone);
		
		//	Draw the finished part
		FillBar = pEvolInfo->m_BarRect;
		FillBar.right = nxPos;
		pDC->FillRect(&FillBar,&brBarColor);
		
		//  Draw the percent complete text indicator in the bar 
		TEXTMETRIC	tm;
		GetTextMetrics(pDC->m_hDC,&tm);
		int nYCorrection = (rectText.Height()-tm.tmHeight) / 2;

		int oldBkMode = pDC->SetBkMode(TRANSPARENT);
		COLORREF oldColor = pDC->SetTextColor(::GetSysColor(COLOR_CAPTIONTEXT));
		wsprintf(tmpBuf,"%d%%",pEvolInfo->m_BarPercent);
		CSize TextSize;
		GetTextExtentPoint(pDC->m_hDC, tmpBuf, lstrlen(tmpBuf), &TextSize);
		int nXCorrection = (rectText.Width() - TextSize.cy) / 2;
		
#ifdef WIN32
		// Windows 95 needs a correction otherwise leaves to much space above
		// the text (not centered vertically) caused by our adjustement to the Height 
		// of a statusbar
		if (!afxData.bWin4)
			nYCorrection = 0;	

		SetTextAlign(pDC->m_hDC, TA_LEFT | TA_BOTTOM);
		pDC->ExtTextOut(rectText.left + nXCorrection, rectText.bottom - nYCorrection,
			ETO_CLIPPED, &rectText, tmpBuf, lstrlen(tmpBuf), NULL);
#else
		SetTextAlign(pDC->m_hDC, TA_LEFT /*| TA_BOTTOM*/);
		ExtTextOut(pDC->m_hDC, rectText.left + nXCorrection, rectText.top + nYCorrection,
			ETO_CLIPPED, &rectText, tmpBuf, lstrlen(tmpBuf), NULL);
#endif

		//	Restore the original DC parameters
		pDC->SetBkMode(oldBkMode);
		pDC->SetTextColor(oldColor);

		}
	}


void PASCAL COXStatusBar::DrawStatusBmp(CDC *pDC, CRect const& rect,int nPane , UINT nStyle)
	// --- In  : pDC : the device context to draw on
	//			 rect : the client coordinates of the pane to draw
	//			 nPane : the index of the pane to draw
	//			 nStyle : the style of the pane
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a standard 3D pane with a Bitmap in it
	{
	ASSERT(pDC->m_hDC != NULL);
	
	// background is already grey
	int nOldMode = ::SetBkMode(pDC->m_hDC, TRANSPARENT);

	PaintPane(pDC, rect, nStyle);

    if(!(nStyle & SBPS_DISABLED))
    	{
    	CDC srcDC; // select current bitmap into a compatible CDC    
		srcDC.CreateCompatibleDC(NULL);

		CBitmap* pOldBitmap = srcDC.SelectObject(((CBmpInfo*)m_PaneBmp[nPane])->m_pBitmap);

		CRect rectBmp(rect);	
		rectBmp.InflateRect(-2*CX_BORDER, -CY_BORDER);
	
		pDC->BitBlt(rectBmp.left, rectBmp.top+1, rectBmp.Width(), rectBmp.Height(),
	      	&srcDC, 0, 0, SRCCOPY); // BitBlt to pane rect

    	srcDC.SelectObject(pOldBitmap);

		}
		
	}
	
void PASCAL COXStatusBar::DrawStatusText(CDC* pDC, CRect const& rect, int nPane ,
			LPCSTR lpszText, UINT nStyle)
	// --- In  : pDC : the device context to draw on
	//			 rect : the client coordinates of the pane to draw
	//			 nPane : the index of the pane to draw
	//			 lpszText : the text of the pane to draw
	//			 nStyle : the style of the pane
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a standard 3D pane with a Text in it
	{
	ASSERT(pDC != NULL);
	
	PaintPane(pDC, rect, nStyle);

	// We need to adjust the rect for the ExtTextOut, and then adjust it back

	// just support left justified text
	if (lpszText != NULL && !(nStyle & SBPS_DISABLED))
		{
		CRect rectText(rect);
#ifdef WIN32
		if (!(nStyle & SBPS_NOBORDERS)) // only adjust if there are borders
			rectText.InflateRect(-2*CX_BORDER, -CY_BORDER);
		else
			rectText.OffsetRect(0, -CY_BORDER); // baselines line up
#else
		rectText.InflateRect(-2*CX_BORDER, -CY_BORDER);
#endif
		int nOldMode = pDC->SetBkMode(OPAQUE);
		// background is already grey, but text color may vary.
		COLORREF crTextColor = pDC->SetTextColor((COLORREF)m_ColorArray[nPane]);

		TEXTMETRIC	tm;
		GetTextMetrics(pDC->m_hDC,&tm);
		int nCorrection = (rectText.Height()-tm.tmHeight) / 2;

#ifdef WIN32
		// Windows 95 needs a correction otherwise leaves to much space above
		// the text (not centered vertically) caused by our adjustement to the Height 
		// of a statusbar
		if (!afxData.bWin4)
			nCorrection = 0;	

		COLORREF crBkColor = pDC->SetBkColor(afxData.clrBtnFace);
		SetTextAlign(pDC->m_hDC, TA_LEFT | TA_BOTTOM);
		pDC->ExtTextOut(rectText.left, rectText.bottom - nCorrection,
			ETO_CLIPPED, &rectText, lpszText, lstrlen(lpszText), NULL);
#else
		COLORREF crBkColor = pDC->SetBkColor(GetSysColor(COLOR_BTNFACE));
		SetTextAlign(pDC->m_hDC, TA_LEFT /*| TA_BOTTOM*/);
		ExtTextOut(pDC->m_hDC, rectText.left, rectText.top+nCorrection,
			ETO_CLIPPED, &rectText, lpszText, lstrlen(lpszText), NULL);
#endif
		}
	}

void COXStatusBar::PaintPane(CDC* pDC, CRect const& rect, UINT nStyle)
	// --- In  : pDC : the device context to draw on
	//			 rect : the client coordinates of the pane to draw
	//			 nStyle : the style of the pane
	// --- Out : 
	// --- Returns :
	// --- Effect : Draws a standard 3D pane
	{
	if (!(nStyle & SBPS_NOBORDERS))
		{   
		// draw the borders
		COLORREF clrHilite;
		COLORREF clrShadow;

#ifdef WIN32
		if (nStyle & SBPS_POPOUT)
			{
			// reverse colors
			clrHilite = afxData.clrBtnShadow;
			clrShadow = afxData.clrBtnHilite;
			}
		else
			{
			// normal colors
			clrHilite = afxData.clrBtnHilite;
			clrShadow = afxData.clrBtnShadow;
			}

		pDC->Draw3dRect(rect, clrShadow, clrHilite);
#else
		if (nStyle & SBPS_POPOUT)
			{
			// reverse colors
			clrHilite = ::GetSysColor(COLOR_BTNSHADOW);
			clrShadow = ::GetSysColor(COLOR_BTNHIGHLIGHT);
			}
		else
			{
			// normal colors
			clrHilite = ::GetSysColor(COLOR_BTNHIGHLIGHT);
			clrShadow = ::GetSysColor(COLOR_BTNSHADOW);
			}

		Draw3dRect(pDC, rect, clrShadow, clrHilite);
#endif
		}

	}

void COXStatusBar::RecalcEvolutionRect()
	{
	CRect PaneRect;

	AFX_STATUSPANE* pSBP;
	int i;
	CEvolInfo* pEvolInfo;
	for (i = 0, pSBP = (AFX_STATUSPANE*)m_pData; i < m_nCount; i++, pSBP++)
		{
		if (pSBP->nStyle & SBPS_PERCENT && m_EvolArray[i] != NULL)
			// This pane is a Progress pane, so draw the progress
			{
			pEvolInfo = (CEvolInfo*)m_EvolArray[i];

			GetItemRect(i, &pEvolInfo->m_BarRect);	 // get pane rect

		    // Make the progressbar itself a little smaller than the pane
			pEvolInfo->m_BarRect.InflateRect(-2*CX_BORDER, -CY_BORDER);

			}
		}                            

	}



BEGIN_MESSAGE_MAP(COXStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(COXStatusBar)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL COXStatusBar::OnEraseBkgnd(CDC* pDC)
	{
    return CStatusBar::OnEraseBkgnd(pDC);
	}

void COXStatusBar::OnSize(UINT nType, int cx, int cy)
	{
	CStatusBar::OnSize(nType, cx, cy);
	
	if (cx == 0 || cy == 0)
		return;

	RecalcEvolutionRect();

	/////////////
	// fixed: 15.01.1998
	// bitmap does not refresh correctly if you size
	// (horizontally) the application window.  If you reduce the width of the
	// window to hide the bitmap and then expand the width to show it, the bitmap
	// is not always refreshed
	///////////
	// redraw panes with bitmaps
	CRect rect;
	for (int nIndex = 0; nIndex < m_nCount; nIndex++)
		{
		if((CBmpInfo*)m_PaneBmp[nIndex]!=NULL)
			{
			GetItemRect(nIndex, &rect);  // get pane rect
			InvalidateRect(rect, FALSE);
			}
		}
	/////////////////////
	}

void COXStatusBar::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
	{
	
	CRect PaneRect;
	// first walk through to calculate extra space
	for (int i = 0; i < m_nCount; i++)
		{
		GetItemRect(i, PaneRect);
		if (PaneRect.PtInRect(point) != 0)
			{
			GetParent()->SendMessage(WM_STAT_DBLCLICK, (WPARAM)GetItemID(i));
			break;
			}
		}

	}

