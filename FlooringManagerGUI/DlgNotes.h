/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "Notesedit.h"

// CDlgNotes dialog

class CDlgNotes : public CDialog
{
	DECLARE_DYNAMIC(CDlgNotes)

public:
	CDlgNotes(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNotes();

	CNotesEdit m_editNotes;
	CString m_strNotes;

// Dialog Data
	enum { IDD = IDD_NOTES_PROP_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

	
};
