/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgSendNote.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSendNote.h"


// CDlgSendNote dialog

IMPLEMENT_DYNAMIC(CDlgSendNote, CDialog)

CDlgSendNote::CDlgSendNote(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSendNote::IDD, pParent)
	, m_CopyNoteToSASM(FALSE)
	, m_CopyNoteToExpeditorEmail(FALSE)
{

}

CDlgSendNote::~CDlgSendNote()
{
}

void CDlgSendNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECKNOTETOSASM, m_CopyNoteToSASM);
	DDX_Check(pDX, IDC_CHECKNOTETOEXPEMAIL, m_CopyNoteToExpeditorEmail);
}


BEGIN_MESSAGE_MAP(CDlgSendNote, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgSendNote::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSendNote message handlers

BOOL CDlgSendNote::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Creates a 12-point-Courier-font
	//m_Font.CreatePointFont(120, _T("Arial"));
	m_Font.CreateFontA(18,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
	m_Font2.CreatePointFont(80, _T("Arial"));

	// Without a member variable
	GetDlgItem(IDC_STATIC_NOTETEXT)->SetFont(&m_Font);
	GetDlgItem(IDC_CHECKNOTETOSASM)->SetFont(&m_Font2);

	if (false == m_bShowCopyToSASM)
	{
		GetDlgItem(IDC_CHECKNOTETOSASM)->ShowWindow(SW_HIDE);
	}
	
	if (false == m_bShowCopyToExpeditorEmail)
	{
		GetDlgItem(IDC_CHECKNOTETOEXPEMAIL)->ShowWindow(SW_HIDE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSendNote::ShowCopyToSASM(bool bShow)
{
	m_bShowCopyToSASM = bShow;
}

void CDlgSendNote::ShowCopyToExpeditorEmail(bool bShow)
{
	m_bShowCopyToExpeditorEmail = bShow;
}

void CDlgSendNote::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
