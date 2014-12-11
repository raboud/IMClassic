// =============================================================================
// 							Class Implementation : COXColorsListBox
// =============================================================================
//
// Source file : 		OXColrLB.cpp
// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
// //////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OXColrLB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

// This locally defined version of the color editing common
// dialog box seems necessary to prevent the MFC help routing
// system from passing the wrong ID when the help button is
// pressed.  The behavior seems to vary depending upon the
// parentage of the colors list box.
//
// TODO: Figure out why this is necessary to make the doggone
//       help topic show correctly when the help button is
//       pressed in the color selection dialog.

class OX_CLASS_DECL CMyColorDialog : public CColorDialog
{
protected:
	afx_msg void OnHelp()
		{WinHelp(HID_BASE_RESOURCE + m_nIDHelp);}

	DECLARE_MESSAGE_MAP();

public:
	CMyColorDialog(COLORREF cr = 0, DWORD dwFlags = 0, 
					CWnd* pParentWnd = NULL) :
		CColorDialog(cr, dwFlags, pParentWnd) {}
};

BEGIN_MESSAGE_MAP(CMyColorDialog, CColorDialog)
	ON_BN_CLICKED(ID_HELP, OnHelp)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// This locally defined version of the text editing control.
// We have catch the "important" messages in COXColorsListBox 
// but the routing in dockable controls sends them to parent frame.

UINT g_uMsgEditCancel = ::RegisterWindowMessage(_T("Cancel Edit Item"));
UINT g_uMsgEditOk = ::RegisterWindowMessage(_T("Approve Edit Item"));

struct CMyEdit : public CEdit
{
	void OnKillFocus( CWnd* pNewWnd );
	void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	
	DECLARE_MESSAGE_MAP();
};

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

void CMyEdit::OnKillFocus( CWnd* /* pNewWnd */)
	{

	CWnd* pParent = GetParent();
	pParent->SendMessage( g_uMsgEditCancel );
	}

void CMyEdit::OnKeyUp( UINT nChar, UINT /* nRepCnt */, UINT /* nFlags */)
	{
	CWnd* pParent = GetParent();
	if ( nChar == VK_ESCAPE || nChar == VK_CANCEL)
		{
		pParent->SendMessage( g_uMsgEditCancel );
		return ;
		}

	if ( nChar == VK_RETURN )
		{
		pParent->SendMessage( g_uMsgEditOk );
		return ;
		}
	}

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
static const CPoint g_ptError = CPoint(-1, -1);
static const UINT g_uEditId = 101 ;  // CMyEdit ID. 101 as editable CComboBox does
static const UINT g_uTimerId = 5572 ;// DoubleClick delay - lucky number !

// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:


COXColorsListBox::COXColorsListBox()
	:	CListBox()
	,	m_pCurEditBox( NULL )
	,	m_ptClicked( g_ptError )
	,	m_iEditedItem( -1 )
	,	m_bEditable( FALSE )
	,	m_bAutoEdit( FALSE )
	{
	}

COXColorsListBox::~COXColorsListBox()
	{
	}

BEGIN_MESSAGE_MAP(COXColorsListBox, CListBox)
//{{AFX_MSG_MAP(COXColorsListBox)
ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_REGISTERED_MESSAGE(g_uMsgEditCancel, OnEditCancel)
ON_REGISTERED_MESSAGE(g_uMsgEditOk, OnEditOk)
ON_WM_TIMER()
ON_WM_CHAR()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// This method completely replaces the specified listbox control with
// 'this'.  The original tab order, control ID, position, etc. are
// all maintained.

BOOL COXColorsListBox::ReplaceListbox(CListBox* pWnd)
	{
	// Get the font, parent window, control id, styles,
	// previous window, and figure out the rectangle
	// before destroying the original control.
	
	CFont* pFont = pWnd->GetFont();
    CWnd* pParent = pWnd->GetParent();
    UINT uiID = pWnd->GetDlgCtrlID();
    DWORD dwOldStyles = pWnd->GetStyle();
	CWnd* pPrev = pWnd->GetWindow(GW_HWNDPREV);
    CRect rectBox;
    pWnd->GetWindowRect(&rectBox);

	if (pParent != NULL)
		pParent->ScreenToClient(&rectBox);
    pWnd->DestroyWindow();
	
	// Make sure the styles include necessary bits.
    DWORD dwStyles = (dwOldStyles & ~LBS_OWNERDRAWVARIABLE);
	dwStyles |= LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | WS_VSCROLL;
	
	// Create the window from the parameters obtained above.
    if( !CListBox::Create(dwStyles, rectBox, pParent, uiID))
        return FALSE;
	
    // Set font and position from values obtained.
	SetFont(pFont);
    SetWindowPos(pPrev, 0, 0, 0,0, SWP_NOSIZE | SWP_NOMOVE );
    return TRUE;
	}

// Adds a color to the listbox.
int COXColorsListBox::AddItemColor(LPCTSTR pcszName, COLORREF crColor)
	{
	int iIndex = AddString(pcszName);
	if (iIndex != LB_ERR)
		{
		return SetItemData(iIndex, crColor);
		}
	
	return LB_ERR;
	}

// Gets the color information for a specified item.
BOOL COXColorsListBox::GetItemColor(int iIndex, COLORREF& cr)
	{
	ASSERT(-1 < iIndex && iIndex < GetCount());

	cr = (COLORREF)GetItemData(iIndex);
	return TRUE;
	}

// Sets the color information for a specified item.
BOOL COXColorsListBox::SetItemColor(int iIndex, COLORREF cr, BOOL bUpdate /* = TRUE */)
	{
	BOOL bReturn = FALSE;
	int iCount = GetCount();
	if (-1 < iIndex && iIndex < iCount)
		{
		SetRedraw(FALSE);
		int iSel = GetCurSel();
		if (iSel != LB_ERR)
			{
			SetItemData(iIndex, cr);
			SetCurSel(iSel);
			if (bUpdate)
				Invalidate();

			bReturn = TRUE;
			}
		
		SetRedraw(TRUE);
		}
	
	return bReturn;
	}

// Performs editing of the currently selected color using the custom
// color editing common dialog box declared at the top of this module.
COLORREF COXColorsListBox::EditSelectedColor(BOOL bSetColor /* = TRUE */)
	{
	int iSel = GetCurSel();
	if (iSel != LB_ERR)
		{
		COLORREF cr;
		GetItemColor(iSel, cr);
		CMyColorDialog Dialog(cr, CC_FULLOPEN | CC_RGBINIT, GetParent());
		Dialog.m_cc.rgbResult = cr;
		
		if (Dialog.DoModal() == IDOK)
			{
			if (bSetColor)
				{
				cr = Dialog.GetColor();
				
				if (OnSettingItemColor(iSel, cr) != -1)
					SetItemColor(iSel, cr);
				}

			return cr;
			}
		}
	
	return 0x01000000;
	}

// This method provides a rectangle implementation that is usually quite
// a bit faster on older un-accelerated video cards.
void COXColorsListBox::FastRect(CDC* pDC, CRect* pRect, COLORREF color)
	{
    COLORREF oldcr = pDC->SetBkColor(color);
    pDC->ExtTextOut(pRect->left, pRect->top, ETO_OPAQUE, pRect, NULL, 0, NULL);
    pDC->SetBkColor(oldcr);
	}

/////////////////////////////////////////////////////////////////////////////
// COXColorsListBox message handlers

void COXColorsListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
	{
    CClientDC DC(this);
	CRect rcClient;
	GetClientRect(rcClient);

    TEXTMETRIC tm;
    DC.GetTextMetrics(&tm);
	lpMIS->itemWidth = rcClient.Width();
	lpMIS->itemHeight = tm.tmHeight;
	}

void COXColorsListBox::CalcItemRectangles( CDC * pDC, const CRect& rc, CRect& rcColor, CRect& rcText )
	{
	// Use the golden ratio to calculate the "correct" size of 
	// the colored rectangle, then create an adjusted rectangle
	// for the text.
	const double GOLDEN_RATIO = 1.618034;
	int iLength = (int)(GOLDEN_RATIO * (double)(rc.Height() - 1));
	rcText = rc;
	
	// Provide a 1/8" space between the color rectangle and the
	// textual description.
	int iSpace = MulDiv(pDC->GetDeviceCaps(LOGPIXELSX), 1, 8);
	rcText.left += iLength + iSpace;

	rcColor = rc ;
	rcColor.top += 1;
	rcColor.right = rcColor.left + iLength;
	}

void COXColorsListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
	{
    ASSERT(lpDIS->CtlType == ODT_LISTBOX);
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    CRect rc(&lpDIS->rcItem);
	
	// Negative #'s mean empty listbox.
    if ((int)lpDIS->itemID == -1)
		{
        rc.bottom = HIWORD(GetDialogBaseUnits());
        pDC->DrawFocusRect(&rc);
        return;
		}
	
	COLORREF crColor;
	VERIFY(GetItemColor(lpDIS->itemID, crColor));
	
    if ((lpDIS->itemAction & ODA_DRAWENTIRE) || 
		(lpDIS->itemAction & ODA_SELECT))
		{
        // Set the foreground text color to gray, if need be.
        pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		
        // Draw selection rect.
        if (lpDIS->itemState & ODS_SELECTED)
			{
			FastRect(pDC, &rc, GetSysColor(COLOR_HIGHLIGHT));
            pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			}
        else
			{
			FastRect(pDC, &rc, GetSysColor(COLOR_WINDOW));
			}
		
		CRect rcColor, rcText ;
		CalcItemRectangles( pDC, rc, rcColor, rcText );		
		// Prepare the DC and draw the rectangle.
		CBrush brColor(crColor);
		CBrush* pbrOld = pDC->SelectObject(&brColor);
		pDC->Rectangle(rcColor.left, rcColor.top, rcColor.right, 
			rcColor.bottom);
		pDC->SelectObject(pbrOld);

		// Draw the text in the given rectangle.
		CString strText;
		GetText(lpDIS->itemID, strText);
		UINT uiFlags = DT_VCENTER | DT_SINGLELINE;
		pDC->DrawText(strText, strText.GetLength(), rcText, uiFlags);
		
        if(lpDIS->itemState & ODS_FOCUS)
			pDC->DrawFocusRect(&rc);
		}
    else if (lpDIS->itemAction & ODA_FOCUS)
		{
		pDC->DrawFocusRect(&rc);
		}
	}

void COXColorsListBox::OnLButtonDblClk(UINT nFlags, CPoint point) 
	{
	CListBox::OnLButtonDblClk(nFlags, point);

	if ( m_bEditable )
		{
		ResetEditing();
		}
	
	EditSelectedColor();
	}

void COXColorsListBox::SetEditable(BOOL bEdit)
	{
	m_bEditable = bEdit ;
	}

BOOL COXColorsListBox::GetEditable() const
	{
	return m_bEditable ;
	}

void COXColorsListBox::SetAutoEdit(BOOL bAutoEdit)
	{
	m_bAutoEdit = m_bEditable && bAutoEdit ;
	}

BOOL COXColorsListBox::GetAutoEdit() const
	{
	return m_bAutoEdit ;
	}

void COXColorsListBox::OnLButtonDown(UINT nFlags, CPoint point) 
	{	
	// Checking multilple conditions to be sure that we can enter into edit mode.

	if ( m_pCurEditBox != NULL ) // Are we editing now ?
		{
		ResetEditing();
		return ;
		}

	if ( !m_bEditable ) // Can we edit at all ?
		{
		CListBox::OnLButtonDown(nFlags, point);
		m_ptClicked = g_ptError ;
		return ;
		}
	
	BOOL bOutside ;
	m_iEditedItem = (int)ItemFromPoint(point, bOutside);
	if ( bOutside || (GetSel(m_iEditedItem) <= 0) )//Edit only selected items
		{
		CListBox::OnLButtonDown(nFlags, point);
		ResetEditing();
		return ;
		}
	
	CRect rc ;
	if ( LB_ERR == GetItemRect(m_iEditedItem, &rc) ) // and we can get item's rect
		{
		CListBox::OnLButtonDown(nFlags, point);
		ResetEditing();
		return ;
		}

	CClientDC dc(this);
	CRect rcColor, rcText ;
	CalcItemRectangles( &dc, rc, rcColor, rcText );	

	if ( ! rcText.PtInRect( point ) ) // Hit test 
		{
		CListBox::OnLButtonDown(nFlags, point);
		ResetEditing();
		return ;
		}

	m_ptClicked = point ; // Finally we are in edit mode !
	}
	 
void COXColorsListBox::OnLButtonUp(UINT nFlags, CPoint point) 
	{
	if ( m_pCurEditBox != NULL ) 
		{
		return ;
		}

	CListBox::OnLButtonUp(nFlags, point);

	if ( m_bEditable )
	{ // We can't start editing, because it could be double click
		SetTimer( g_uTimerId, GetDoubleClickTime(), NULL );
		}	
	}

void COXColorsListBox::OnTimer( UINT nIDEvent )
	{
	if ( nIDEvent != g_uTimerId )
		{
		return ;
		}

	KillTimer( g_uTimerId );
	if (	m_bEditable 
		&& (m_pCurEditBox == NULL) 
		&& (m_ptClicked != g_ptError) 
		&& (m_iEditedItem != -1) ) 
		{
		EditSelectedText();
		}
	}

void COXColorsListBox::EditSelectedText()
	{	
	CRect rcEditedItem ; // whole item rectangle
	if ( GetItemRect( m_iEditedItem, &rcEditedItem ) == LB_ERR )
		{
		ResetEditing();
		return ;
		}

	CClientDC dc(this);
	CRect rcColor, rcText ; 
	CalcItemRectangles( &dc, rcEditedItem, rcColor, rcText );// find text part

	CString strEditedItem ;
	GetText( m_iEditedItem, strEditedItem ) ;

	// Create edit box in the size of text part of item.
	m_pCurEditBox = (CEdit*)new CMyEdit(); 
	if ( ! m_pCurEditBox->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
				rcText, this, g_uEditId) )
		{
		ResetEditing();
		return ;
		}

	m_pCurEditBox->SetFont( GetFont() );
	m_pCurEditBox->SetWindowText( (LPCTSTR)strEditedItem );		
	m_pCurEditBox->SetFocus();
	m_pCurEditBox->SetSel(0,-1); 
	}

BOOL COXColorsListBox::IsMoveToFar(UINT ,  const CPoint& pt ) const 
	{
	double dx = (pt.x-m_ptClicked.x) ;
	double dy = (pt.y-m_ptClicked.y) ;
	return (dx*dx + dy*dy) > (OX_CLB_EDIT_RADIUS* OX_CLB_EDIT_RADIUS);
	}

void COXColorsListBox::OnMouseMove(UINT nFlags, CPoint point) 
	{
	CListBox::OnMouseMove(nFlags, point);

	if (	(m_bEditable == FALSE)
		||	(m_pCurEditBox != NULL) 
		||	(m_ptClicked == g_ptError) 
		||	(m_iEditedItem == -1) )
		{
		return ;
		}
	if ( IsMoveToFar(nFlags, point) )// it's drag, not click
		{
		ResetEditing();
		}
	}

LRESULT COXColorsListBox::OnEditCancel( WPARAM, LPARAM )
	{
	ResetEditing();
	return 1 ;
	}

LRESULT COXColorsListBox::OnEditOk( WPARAM , LPARAM )
	{
	CString strResult ;
	m_pCurEditBox->GetWindowText(strResult);

	if ( -1 != GetParent()->SendMessage(WM_OX_SETLISTBOXITEM_TEXT, 
				(WPARAM)m_iEditedItem, (LPARAM)&strResult) )
		{ 
		DWORD clr = GetItemData(m_iEditedItem);
		DeleteString( m_iEditedItem );
		InsertString(m_iEditedItem, strResult);
		SetItemData(m_iEditedItem, clr);
		}

	ResetEditing();
	return 1 ;
	}

LRESULT COXColorsListBox::OnSettingItemColor(int iIndex, COLORREF cr)
	{
	return GetParent()->SendMessage(WM_OX_SETLISTBOXITEM_COLOR, (WPARAM)iIndex, (LPARAM)cr);
	}

void COXColorsListBox::ResetEditing()
	{
	// cleanup
	delete m_pCurEditBox ;
	m_pCurEditBox = NULL ;

	m_ptClicked = g_ptError ;
	m_iEditedItem = -1 ;
	}

void COXColorsListBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
	{
	if (m_bAutoEdit)
		{
		m_iEditedItem = GetCurSel();
		if (m_iEditedItem == LB_ERR)
			{
			ResetEditing() ;
			return;
			}
		EditSelectedText();
		// m_pCurEditBox can be NULL if e.g. no column is editable
		if ( m_pCurEditBox != NULL )
			{
			CString sText((TCHAR)nChar);
			m_pCurEditBox->SetWindowText(sText);
			m_pCurEditBox->SetSel(1, 1);
			}
		else
			{
			// .. No editable subitem is found
			::MessageBeep(0xFFFFFFFF);
			return;
			}

		// We handled the message, do not call base class implementation
		return;
		}
	
	CListBox::OnChar(nChar, nRepCnt, nFlags);
	}

#ifdef _DEBUG
void COXColorsListBox::Dump(CDumpContext& dc) const
	{
	CListBox::Dump(dc);
	}

void COXColorsListBox::AssertValid() const
	{
	CListBox::AssertValid();
	}
#endif



