/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgCheckList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgCheckList.h"

// CDlgCheckList dialog

IMPLEMENT_DYNAMIC(CDlgCheckList, CDialog)
CDlgCheckList::CDlgCheckList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckList::IDD, pParent)
{
}

CDlgCheckList::~CDlgCheckList()
{
}

void CDlgCheckList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCheckList, CDialog)
END_MESSAGE_MAP()


// CDlgCheckList message handlers

BOOL CDlgCheckList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridCheckList.AttachGrid(this, IDC_CHECK_LIST) ;
	m_gridCheckList.Update() ;
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
