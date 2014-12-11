/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgChargebackList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgChargebackList.h"
#include ".\dlgchargebacklist.h"


// CDlgChargebackList dialog

IMPLEMENT_DYNAMIC(CDlgChargebackList, CDialog)
CDlgChargebackList::CDlgChargebackList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChargebackList::IDD, pParent)
{
}

CDlgChargebackList::~CDlgChargebackList()
{
}

void CDlgChargebackList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgChargebackList, CDialog)
END_MESSAGE_MAP()


// CDlgChargebackList message handlers

BOOL CDlgChargebackList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridChargeBackList.AttachGrid(this, IDC_CHARGEBACK_LIST) ;
	m_gridChargeBackList.Update() ;
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
