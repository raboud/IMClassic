/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CFEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "Flooring.h"
#include "CFEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCFEdit

CCFEdit::CCFEdit()
{
	m_ctrl = NULL;
}

CCFEdit::~CCFEdit()
{
}


BEGIN_MESSAGE_MAP(CCFEdit, CEdit)
	//{{AFX_MSG_MAP(CCFEdit)
	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCFEdit message handlers

BOOL CCFEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= ES_AUTOHSCROLL;
	return CEdit::PreCreateWindow(cs);
}

void CCFEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

int CCFEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ctrl = (CUGCtrl*)GetParent();
	return 0;
}

UINT CCFEdit::OnGetDlgCode() 
{
	if(GetKeyState(VK_TAB)<0)
	{
		return DLGC_WANTTAB;
	}
	else if (GetKeyState(VK_RETURN)<0)
	{
		return  DLGC_WANTALLKEYS;
	}
	else if (GetKeyState(VK_ESCAPE)<0)
	{
		return  DLGC_WANTALLKEYS;
	}
	return CEdit::OnGetDlgCode();
}

void CCFEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
		case VK_TAB:
			{

				if(GetKeyState(VK_SHIFT)<0)
				{
					m_continueCol = m_ctrl->m_editCol -1;
					m_continueRow = m_ctrl->m_editRow;
				}
				else
				{
					m_continueCol = m_ctrl->m_editCol +1;
					m_continueRow = m_ctrl->m_editRow;
				}

				m_continueFlag = TRUE;
				m_ctrl->SetFocus();
				return;
			}
		case VK_RETURN:
			{
				m_continueCol = m_ctrl->m_editCol;
				m_continueRow = m_ctrl->m_editRow +1;
				m_continueFlag = TRUE;
				m_ctrl->SetFocus();
				return;
			}
		case VK_ESCAPE:
			{
				m_cancel = TRUE;
				m_continueFlag = FALSE;
				m_ctrl->SetFocus();
				return;
			}
		case VK_UP:
			{
				m_continueCol = m_ctrl->m_editCol;
				m_continueRow = m_ctrl->m_editRow-1;
				m_continueFlag = TRUE;
				m_ctrl->SetFocus();
				return;
			}
		case VK_DOWN:
			{
				m_continueCol = m_ctrl->m_editCol;
				m_continueRow = m_ctrl->m_editRow+1;
				m_continueFlag = TRUE;
				m_ctrl->SetFocus();
				return;
			}
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCFEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);

	if(pNewWnd->GetSafeHwnd() != NULL)
	{
		if(pNewWnd != m_ctrl && pNewWnd->GetParent() != m_ctrl)
		{
			m_cancel = TRUE;
		}
	}
	else
	{
		m_cancel = TRUE;
	}

	CString string;
	GetWindowText(string);
	if(m_ctrl->EditCtrlFinished(string,m_cancel,m_continueFlag,
	  m_continueCol,m_continueRow) == FALSE)
	{
		m_ctrl->GotoCell(m_ctrl->m_editCol,m_ctrl->m_editRow);
		SetCapture();
		ReleaseCapture();
		SetFocus();
	}
}

int CCFEdit::OnMouseActivate(CWnd* /* pDesktopWnd */, UINT /* nHitTest */, UINT /* message */) 
{
	return MA_ACTIVATE;	
}

void CCFEdit::OnSetFocus(CWnd* pOldWnd) 
{
	m_cancel = FALSE;
	m_continueFlag = FALSE;

	SetSel(0,-1);
	
	CEdit::OnSetFocus(pOldWnd);
}
