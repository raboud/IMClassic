/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// NotesEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "NotesEdit.h"
#include ".\notesedit.h"
#include "DlgNotes.h"

#define ME_SELECTALL WM_USER + 0x7000
#define ME_ADDNOTE   WM_USER + 0x7001


// CNotesEdit

IMPLEMENT_DYNAMIC(CNotesEdit, CEdit)
CNotesEdit::CNotesEdit()
{
	m_bCanAddNote = false;
	m_bShowAddNote = false;
	m_pFont = new CFont();
	m_pFont->CreateFont(12,0,0,0,FW_NORMAL, 0,0,0,0,0,0,0,0,"Lucida Console");
}

CNotesEdit::~CNotesEdit()
{
	delete m_pFont;
}


BEGIN_MESSAGE_MAP(CNotesEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CNotesEdit message handlers


void CNotesEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	SetFont(m_pFont);
	SetSel(-1, 0);
}

void CNotesEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
	UNREFERENCED_PARAMETER(pWnd);

	SetFocus();
    CMenu menu;
    menu.CreatePopupMenu();
    BOOL bReadOnly = GetStyle() & ES_READONLY;
    DWORD flags = CanUndo() && !bReadOnly ? 0 : MF_GRAYED;
    menu.InsertMenu(0, MF_BYPOSITION | flags, EM_UNDO, "&Undo");

    menu.InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR);

    DWORD sel = GetSel();
    flags = LOWORD(sel) == HIWORD(sel) ? MF_GRAYED : 0;
    menu.InsertMenu(2, MF_BYPOSITION | flags, WM_COPY,
        "&Copy");

    flags = (flags == MF_GRAYED || bReadOnly) ? MF_GRAYED : 0;
    menu.InsertMenu(2, MF_BYPOSITION | flags, WM_CUT,
        "Cu&t");
    menu.InsertMenu(4, MF_BYPOSITION | flags, WM_CLEAR,
        "&Delete");

    flags = IsClipboardFormatAvailable(CF_TEXT) &&
        !bReadOnly ? 0 : MF_GRAYED;
    menu.InsertMenu(4, MF_BYPOSITION | flags, WM_PASTE,
        "&Paste");

    menu.InsertMenu(6, MF_BYPOSITION | MF_SEPARATOR);

    int len = GetWindowTextLength();
    flags = (!len || (LOWORD(sel) == 0 && HIWORD(sel) ==
        len)) ? MF_GRAYED : 0;
    menu.InsertMenu(7, MF_BYPOSITION | flags, ME_SELECTALL,
        "Select &All");

	if (m_bShowAddNote)
	{
		menu.InsertMenu(8, MF_BYPOSITION | MF_SEPARATOR);

		flags = (m_bCanAddNote) ? 0 : MF_GRAYED;
		menu.InsertMenu(9, MF_BYPOSITION | flags, ME_ADDNOTE,
			"Add Note");
	}

    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
        TPM_RIGHTBUTTON, point.x, point.y, this);

}

BOOL CNotesEdit::OnCommand(WPARAM wParam, LPARAM lParam)
{

	switch (LOWORD(wParam))
    {
    case EM_UNDO:
    case WM_CUT:
    case WM_COPY:
    case WM_CLEAR:
    case WM_PASTE:
        return SendMessage(LOWORD(wParam));
    case ME_SELECTALL:
        return SendMessage (EM_SETSEL, 0, -1);
	case ME_ADDNOTE:
		{
			HandleAddNote();
			return TRUE;
		}
		break;
    default:
        return CEdit::OnCommand(wParam, lParam);
    }

}

void CNotesEdit::HandleAddNote()
{
	CDlgNotes dlg;
	if (dlg.DoModal() == IDOK)
	{
		CString strExisting;
		GetWindowText(strExisting);
		
		CFlooringApp* pApp = (CFlooringApp*) AfxGetApp() ;
		
		CString strDateTime;
		COleDateTime time = CGlobals::GetCurrentSystemTime();
		
		CString strTemp = "";
		if (strExisting.GetLength() > 0)
		{
            strTemp  = "\r\n---------------------------------------------------------\r\n";
		}
		strTemp += "Modified By: " + pApp->GetUserFirstAndLastName() + " on " + time.Format("%m/%d/%Y at %I:%M:%S %p") + "\r\n";
		strTemp += dlg.m_strNotes;
		strTemp = strExisting + strTemp;
		if (strTemp.GetLength() > CGlobals::iMAX_ORDER_NOTES)
		{
			strTemp = strTemp.Left(CGlobals::iMAX_ORDER_NOTES);
		}
		SetWindowText(strTemp);
		int iLength = strTemp.GetLength();
		SetSel(iLength, iLength);
	}
}