/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CFRichEdit.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "CFRichEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCFRichEdit

CCFRichEdit::CCFRichEdit()
{
	m_bPopUpDisplayed = false;
}

CCFRichEdit::~CCFRichEdit()
{
}


BEGIN_MESSAGE_MAP(CCFRichEdit, CAutoRichEditCtrl)
	//{{AFX_MSG_MAP(CCFRichEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	ON_CONTROL_REFLECT(EN_CHANGE, OnEnChange)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnEnKillfocus)
	ON_NOTIFY_REFLECT(EN_MSGFILTER, OnEnMsgfilter)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCFRichEdit message handlers

void CCFRichEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == 0x02) && (::GetKeyState(VK_CONTROL) < 0))
	{
		SetSelectionBold() ;
	}
	else if ((nChar == 0x9) && (::GetKeyState(VK_CONTROL) < 0))
	{
		SetSelectionItalic() ;
	}
	else if ((nChar == 0x15) && (::GetKeyState(VK_CONTROL) < 0))
	{
		SetSelectionUnderlined() ;
	}
	else
	{
		CAutoRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CCFRichEdit::OnEnChange()
{
	GetParentOwner()->SendMessage(CGlobals::WM_USER_RICHEDITCHANGE);
}

void CCFRichEdit::OnEnKillfocus()
{
	GetParentOwner()->SendMessage(CGlobals::WM_USER_RICHEDITLOSEFOCUS, (WPARAM) this, 0);
}

void CCFRichEdit::OnEnMsgfilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	MSGFILTER *pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);
	if ((pMsgFilter->nmhdr.code == EN_MSGFILTER) && (pMsgFilter->msg == WM_RBUTTONDOWN))
	{
		//if we get through here, we have trapped the right click event of the richeditctrl! 
		CPoint point;                                            
		::GetCursorPos(&point); //where is the mouse?
		CMenu menu; //lets display out context menu :) 
		DWORD dwSelectionMade;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, 1000, "Cut");
		menu.AppendMenu(MF_STRING, 1001, "Copy");
		menu.AppendMenu(MF_STRING, 1002, "Paste");
		
		m_bPopUpDisplayed = true;
		dwSelectionMade = menu.TrackPopupMenu( (TPM_LEFTALIGN|TPM_LEFTBUTTON|
                                                       TPM_NONOTIFY|TPM_RETURNCMD),
                                                       point.x, point.y, this);
		TRACE("dwSelection = %d", dwSelectionMade);
		m_bPopUpDisplayed = false;
		switch ( dwSelectionMade ) 
		{
			case 1000 : Cut();
				break;
			case 1001 : Copy();
				break;
			case 1002 : Paste();
				break;
			default : break;
		}
        
		*pResult = 0;
	}
}

BOOL CCFRichEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bPopUpDisplayed)
	{
		HCURSOR hc = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        SetCursor(hc);
		return FALSE;
	}
	else
	{
        return CAutoRichEditCtrl::OnSetCursor(pWnd, nHitTest, message);
	}
}