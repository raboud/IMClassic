// DlgSubContractorsList.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSubContractorsList.h"
#include ".\dlgsubcontractorslist.h"


// CDlgSubContractorsList dialog

IMPLEMENT_DYNAMIC(CDlgSubContractorsList, CDialog)
CDlgSubContractorsList::CDlgSubContractorsList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSubContractorsList::IDD, pParent)
{
}

CDlgSubContractorsList::~CDlgSubContractorsList()
{
}

void CDlgSubContractorsList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILTER_COMBO, m_comboFilter);
}


BEGIN_MESSAGE_MAP(CDlgSubContractorsList, CDialog)
	ON_CBN_SELCHANGE(IDC_FILTER_COMBO, OnCbnSelchangeFilterCombo)
END_MESSAGE_MAP()


// CDlgSubContractorsList message handlers

BOOL CDlgSubContractorsList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_comboFilter.AddAll();

	m_gridSubContractors.AttachGrid(this, IDC_SUBS_GRID) ;
	m_gridSubContractors.Update();
	m_gridSubContractors.ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSubContractorsList::OnCbnSelchangeFilterCombo()
{
	m_gridSubContractors.SetShowFilter(m_comboFilter.GetItemData(m_comboFilter.GetCurSel()));
}
