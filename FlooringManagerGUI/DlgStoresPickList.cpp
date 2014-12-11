// DlgStoresPickList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgStoresPickList.h"
#include ".\dlgstorespicklist.h"


// CDlgStoresPickList dialog

IMPLEMENT_DYNAMIC(CDlgStoresPickList, CDialog)
CDlgStoresPickList::CDlgStoresPickList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStoresPickList::IDD, pParent)
{
}

CDlgStoresPickList::~CDlgStoresPickList()
{
}

void CDlgStoresPickList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STORES_SHOWACTIVE, m_btnShowActiveOnly);
}


BEGIN_MESSAGE_MAP(CDlgStoresPickList, CDialog)
	ON_BN_CLICKED(IDC_STORES_SHOWACTIVE, OnBnClickedStoresShowActive)
END_MESSAGE_MAP()


// CDlgStoresPickList message handlers

BOOL CDlgStoresPickList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnShowActiveOnly.SetCheck(1);

	m_gridStores.AttachGrid(this, IDC_STORES_GRID) ;
	m_gridStores.Update();
	m_gridStores.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStoresPickList::OnBnClickedStoresShowActive()
{
	bool bShowActiveOnly = (m_btnShowActiveOnly.GetCheck() == 1);
	m_gridStores.ShowActiveOnly( bShowActiveOnly );
}
