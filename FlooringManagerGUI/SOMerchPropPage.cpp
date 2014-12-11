/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SOMerchPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SOMerchPropPage.h"


// CSOMerchPropPage dialog

IMPLEMENT_DYNAMIC(CSOMerchPropPage, COrderPropPage)
CSOMerchPropPage::CSOMerchPropPage()
	: COrderPropPage(CSOMerchPropPage::IDD)
{
	m_pGrid = new CGridSOMerchandise;
}

CSOMerchPropPage::~CSOMerchPropPage()
{
	if (m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CSOMerchPropPage::ShowDeleted(bool bShow) 
{
	((CGridSOMerchandise*)m_pGrid)->ShowDeleted(bShow) ;
}

void  CSOMerchPropPage::SetAllowStatusUpdate(bool bAllowStatusUpdate)
{
	((CGridSOMerchandise*)m_pGrid)->SetAllowStatusUpdate(bAllowStatusUpdate) ;
}

void CSOMerchPropPage::DoDataExchange(CDataExchange* pDX)
{
	COrderPropPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSOMerchPropPage, COrderPropPage)
END_MESSAGE_MAP()


// CSOMerchPropPage message handlers

BOOL CSOMerchPropPage::OnInitDialog() 
{
	COrderPropPage::OnInitDialog();

	m_pGrid->AttachGrid(this, IDC_SO_GRID_AREA) ;

//	COleDateTime time = CGlobals::GetCurrentSystemTime();
//	CTime time2 = CTime(time.GetYear(), time.GetMonth(), time.GetDay(), 0,0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CSOMerchPropPage::HasUnknownStatus()
{
	return ((CGridSOMerchandise*)m_pGrid)->HasUnknownStatus();
}

