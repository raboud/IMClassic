// ==========================================================================
// 							Class Specification : COXStatusBar
// ==========================================================================

// Header file : xstatus.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from MFC 3.0 - MFC 2.5 CStatusBar

//	YES	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption : extends the CStatusBar class with bitmaps and progress indicator
//				allowed in its panes.  This implementation requires MFC 3.0
//				or earlier 
// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////
#ifndef __XSTATUSBAR_H__
#define __XSTATUSBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


#define SBPS_PERCENT 0x0010	 // New Statusbar pane style for progress bars

#define WM_STAT_DBLCLICK (WM_USER + 555)
	// User Message Send when a pane is clicked
	// WPARAM : the ID of the pane that was dubbleclicked
	// LPARAM : not used (= zero)

class OX_CLASS_DECL COXStatusBar : public CStatusBar
{
	DECLARE_DYNCREATE(COXStatusBar)
// Data members -------------------------------------------------------------
public:
	//{{AFX_DATA(COXStatusBar)
	//}}AFX_DATA
			
protected:
	class OX_CLASS_DECL CBmpInfo : public CObject
		{ 
		public:
			UINT 		m_nIDResource;		  // The resource ID of this bitmap
			CBitmap*	m_pBitmap;			  // The bitmap
		};
	
	class OX_CLASS_DECL CEvolInfo : public CObject
	    {
	    public:
			UINT 	m_BarPercent;			  // Percentage of process progress
			CRect 	m_BarRect;				  // the rect where the progressbar is drawn in
	    };

	int m_nCount;

    CObArray 		m_PaneBmp;
										
    CDWordArray     m_ColorArray;		
										
    CPtrArray      	m_EvolArray;

	UINT			m_BarHeight;		
	HFONT 			m_hStatusFont;		
    
// Member functions ---------------------------------------------------------
public:
    COXStatusBar();
    // --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
	
	BOOL Create(CWnd* pParentWnd,int nHeight = 0,
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
			UINT nID = AFX_IDW_STATUS_BAR);
	// --- In  : see CStatusBar::Create(...)
	// --- Out : 
	// --- Returns : TRUE if succes, otherwise FALSE
	// --- Effect : Had to overload this function to Make the Statusbar sensitive
	//				for dubble clicks.  An MFC Statusbar has a WINDOW class with the
	//				CS_DBLCLKS style not set.

	virtual void DoPaint(CDC* pDC);
	// --- In  : pDC : device context of the statusbar
	// --- Out : 
	// --- Returns :
	// --- Effect : 
	
	BOOL SetIndicators(const UINT FAR* lpIDArray, int nIDCount);
	// --- In  :	
	// --- Out : 
	// --- Returns : TRUE if succes, otherwise FALSE
	// --- Effect : 		Sets the number of panes
	//				
	
	BOOL SetPaneBitmap(int nIndex, UINT nIDResource, BOOL bUpdate = TRUE, COLORREF clrBkGnd = ::GetSysColor(COLOR_BTNFACE));
	// --- In  :	nIdex :			index of the pane in which the bitmap must
	//								be painted						
	//				nIDResource :	resource ID of the bitmap
	//				bUpdate :		update pane ?
	//				clrBkGnd :		Color of background
	// --- Out : 
	// --- Returns : TRUE if succes, otherwise FALSE
	// --- Effect : Displays a bitmap in a pane

	BOOL SetPaneText(int nIndex, LPCSTR lpszNewText, BOOL bUpdate = TRUE, COLORREF clrText = ::GetSysColor(COLOR_BTNTEXT));
	// --- In  :	nIndex :		index of the pane in which the text must
	//								be painted						
	//				lpszNewText :	the text
	//				bUpdate :		update pane ?
	//				clrText :		Color of text
	// --- Out : 
	// --- Returns : TRUE if succes, otherwise FALSE
	// --- Effect : Displays text in a pane with a certain text color 
	
	void SetBarProgress(int nIndex, BOOL bUpdate = TRUE, DWORD dwTotal = 100, DWORD dwDone = 0);
	// --- In  :	nIndex : index of the pane in which the progress is shown
	//				bUpdate : Update pane ?
	//				dwTotal : The maximum of the process in progress
	//				dwDone : The number of pieces done of the process in progress
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the part already processed of a proces in progress 

	void ResetBar(int nIndex);
	// --- In  : nIndex : index of the pane in which the progress is to be reset
	// --- Out : 
	// --- Returns :
	// --- Effect : Resets (= Back to zero progress) the progressbar in a pane with index nIndex

	BOOL SetUpBar(int nIndex, BOOL bUpdate = TRUE);
	// --- In  : nIndex : index of the pane in which the progress is to be set
	//  		 bUpdate : Update pane ?
	// --- Out : 
	// --- Returns : TRUE if succes, otherwise FALSE
	// --- Effect : Prepares a pane to begin a progress and to show a progressbar
	
	    
	virtual ~COXStatusBar();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect :Destructor of object 
	
// Implementation
protected:
	void FillSolidRect(CDC* pDC, LPCRECT lpRect, COLORREF clr);
	void FillSolidRect(CDC* pDC, int x, int y, int cx, int cy, COLORREF clr);
	void Draw3dRect(CDC* pDC, LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
	void Draw3dRect(CDC* pDC, int x, int y, int cx, int cy,	COLORREF clrTopLeft, COLORREF clrBottomRight);

	void PaintPane(CDC* pDC, CRect const& rect, UINT nStyle);

	void PASCAL DrawBarProgress(CDC *pDC, CRect const& rect, int nPane, UINT nStyle);
	void PASCAL DrawStatusText(CDC *pDC, CRect const& rect, int nPane,
			LPCSTR lpszText, UINT nStyle);
    void PASCAL DrawStatusBmp(CDC *pDC, CRect const& rect,int nPane, UINT nStyle);
    
	void RecalcEvolutionRect();

    inline AFX_STATUSPANE* _GetPanePtr(int nIndex) const;

#ifdef WIN32
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
#endif

	// Generated message map functions
	//{{AFX_MSG(COXStatusBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:

};

#endif
/////////////////////////////////////////////////////////////////////////////
