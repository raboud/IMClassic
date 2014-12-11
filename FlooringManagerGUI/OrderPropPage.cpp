/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// OrderPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "OrderPropPage.h"


// COrderPropPage dialog

IMPLEMENT_DYNAMIC(COrderPropPage, CPropertyPage)
COrderPropPage::COrderPropPage()
: CPropertyPage(), m_pGrid(NULL)
{
}

COrderPropPage::COrderPropPage(UINT nID)
	: CPropertyPage(nID)
{
}

COrderPropPage::~COrderPropPage()
{
}

void COrderPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COrderPropPage, CPropertyPage)
END_MESSAGE_MAP()

void COrderPropPage::SetPOList(CPoList *pListPOs, bool bUpdateGrid)
{
	m_pGrid->SetPOList(pListPOs, bUpdateGrid);
}

void COrderPropPage::UpdateRecordSet()
{
	m_pGrid->UpdateRecordSet();
}

void COrderPropPage::SetInvokedFromSPN(bool bInvokedFromSPN)
{
	m_pGrid->SetInvokedFromSPN(bInvokedFromSPN);
}
// COrderPropPage message handlers
