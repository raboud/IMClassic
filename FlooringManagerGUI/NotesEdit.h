/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once


// CNotesEdit

class CNotesEdit : public CEdit
{
	DECLARE_DYNAMIC(CNotesEdit)

public:
	CNotesEdit();
	virtual ~CNotesEdit();

	void SetCanAddNote(bool bCanAddNote);
	void SetShowAddNote(bool bShowAddNote);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void HandleAddNote();

	bool m_bCanAddNote;
	bool m_bShowAddNote;

	CFont* m_pFont;

};

inline void CNotesEdit::SetCanAddNote(bool bCanAddNote)
{
	m_bCanAddNote = bCanAddNote;
}

inline void CNotesEdit::SetShowAddNote(bool bShowAddNote)
{
	m_bShowAddNote = bShowAddNote;
}
