/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// RegMerchPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "RegMerchPropPage.h"


// CRegMerchPropPage dialog

IMPLEMENT_DYNAMIC(CRegMerchPropPage, COrderPropPage)
CRegMerchPropPage::CRegMerchPropPage()
	: COrderPropPage(CRegMerchPropPage::IDD)
{
	m_pGrid = new CGridRegMerchandise;
}

CRegMerchPropPage::~CRegMerchPropPage()
{
	if (m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CRegMerchPropPage::ShowDeleted(bool bShow) 
{
	((CGridRegMerchandise*)m_pGrid)->ShowDeleted(bShow) ;
}

void  CRegMerchPropPage::SetAllowStatusUpdate(bool bAllowStatusUpdate)
{
	((CGridRegMerchandise*)m_pGrid)->SetAllowStatusUpdate(bAllowStatusUpdate) ;
}

void CRegMerchPropPage::DoDataExchange(CDataExchange* pDX)
{
	COrderPropPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegMerchPropPage, COrderPropPage)
END_MESSAGE_MAP()


// CRegMerchPropPage message handlers

BOOL CRegMerchPropPage::OnInitDialog() 
{
	COrderPropPage::OnInitDialog();

	m_pGrid->AttachGrid(this, IDC_REG_GRID_AREA) ;

//	COleDateTime time = CGlobals::GetCurrentSystemTime();
//	COleDateTime time2 = COleDateTime(time.GetYear(), time.GetMonth(), time.GetDay(), 0,0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CRegMerchPropPage::HasUnknownStatus()
{
	return ((CGridRegMerchandise*)m_pGrid)->HasUnknownStatus();
}