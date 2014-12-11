/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "GridPONotes.h"


// CDlgPONotesList dialog

class CDlgPONotesList : public CDialog
{
	DECLARE_DYNAMIC(CDlgPONotesList)

public:
	void SetOrderId (int iOrderID);
	CDlgPONotesList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPONotesList();

// Dialog Data
	enum { IDD = IDD_PONOTES_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CGridPONotes m_gridPONotes;
	int m_iOrderId;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
