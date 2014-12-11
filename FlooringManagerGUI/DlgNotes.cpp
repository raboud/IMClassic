// DlgNotes.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgNotes.h"
#include ".\dlgnotes.h"


// CDlgNotes dialog

IMPLEMENT_DYNAMIC(CDlgNotes, CDialog)
CDlgNotes::CDlgNotes(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNotes::IDD, pParent)
{
}

CDlgNotes::~CDlgNotes()
{
}

void CDlgNotes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOTES, m_editNotes);
	DDX_Text(pDX, IDC_EDIT_NOTES, m_strNotes);
}


BEGIN_MESSAGE_MAP(CDlgNotes, CDialog)
END_MESSAGE_MAP()


// CDlgNotes message handlers

void CDlgNotes::OnOK()
{
	CDialog::OnOK();
}
