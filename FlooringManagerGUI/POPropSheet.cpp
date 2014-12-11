/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// POPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "POPropSheet.h"
#include "Globals.h"

const char szSO_MERCHANDISE[] = "S.O. Merchandise";
const char szREG_MERCHANDISE[] = "Reg. Merchandise";

// CPOPropSheet

IMPLEMENT_DYNAMIC(CPOPropSheet, CPropertySheet)
CPOPropSheet::CPOPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPOPropSheet::CPOPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPOPropSheet::CPOPropSheet(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet("test", pParentWnd, iSelectPage)
{
	m_SOMerchPropPage.m_psp.dwFlags |= PSP_USETITLE;
	m_SOMerchPropPage.m_psp.pszTitle = szSO_MERCHANDISE;

	m_RegMerchPropPage.m_psp.dwFlags |= PSP_USETITLE;
	m_RegMerchPropPage.m_psp.pszTitle = szREG_MERCHANDISE;

	AddPage(&m_SOMerchPropPage);
	AddPage(&m_RegMerchPropPage);
}

void CPOPropSheet::ShowDeleted(bool bShow)
{
	m_SOMerchPropPage.ShowDeleted(bShow) ;
	m_RegMerchPropPage.ShowDeleted(bShow) ;
}

void CPOPropSheet::SetAllowStatusUpdate(bool bAllowStatusUpdate)
{
	m_SOMerchPropPage.SetAllowStatusUpdate(bAllowStatusUpdate) ;
	m_RegMerchPropPage.SetAllowStatusUpdate(bAllowStatusUpdate) ;
}

void CPOPropSheet::SetInvokedFromSPN(bool bInvokedFromSPN)
{
	m_SOMerchPropPage.SetInvokedFromSPN(bInvokedFromSPN);
	m_RegMerchPropPage.SetInvokedFromSPN(bInvokedFromSPN);
}

CPOPropSheet::~CPOPropSheet()
{
}


BEGIN_MESSAGE_MAP(CPOPropSheet, CPropertySheet)
	ON_WM_SETFOCUS()
	ON_REGISTERED_MESSAGE( wm_TAB_COLOR_UPDATE, OnTabColorUpdate)
END_MESSAGE_MAP()


// CPOPropSheet message handlers

void CPOPropSheet::SetPOList(CPoList* pListPOs, bool bUpdateGrid /*=true*/)
{
	m_listPOs.RemoveAll();
	m_listPOs.AddTail(pListPOs);

	m_SOMerchPropPage.SetPOList(pListPOs, bUpdateGrid);
	m_RegMerchPropPage.SetPOList(pListPOs, bUpdateGrid);

	UpdateTabColors();
}

void CPOPropSheet::UpdateRecordSet()
{
	m_SOMerchPropPage.UpdateRecordSet();
	m_RegMerchPropPage.UpdateRecordSet();
}
void CPOPropSheet::OnSetFocus(CWnd* pOldWnd)
{
	CPropertySheet::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
}

BOOL CPOPropSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	m_colorTabCtrl.SubclassWindow(GetTabControl()->m_hWnd);
	m_colorTabCtrl.ModifyStyle(0, TCS_OWNERDRAWFIXED);

	m_colorTabCtrl.SetTextColor(CGlobals::COLOR_BLUE);
	m_colorTabCtrl.SetBkColor(CGlobals::COLOR_ALERT);

	m_colorTabCtrl.InitColorArray();

	UpdateTabColors();

	return bResult;
}

void CPOPropSheet::UpdateTabColors()
{
	//DKB this needs to look at the actual grid instead of pulling from the DB.  
	//this message/function is called when a user marks a line item reviewed within the grid, but has not yet saved.
	if (CGlobals::OrderHasSOMerchandiseAlerts(GetFirstOrderID()))
	{
		m_colorTabCtrl.UseColors((char*)szSO_MERCHANDISE);
	}
	else
	{
		m_colorTabCtrl.UseColors((char*)szSO_MERCHANDISE, false);
	}

	if (CGlobals::OrderHasRegMerchandiseAlerts(GetFirstOrderID()))
	{
		m_colorTabCtrl.UseColors((char*)szREG_MERCHANDISE);
	}
	else
	{
		m_colorTabCtrl.UseColors((char*)szREG_MERCHANDISE, false);
	}

	Invalidate();
}

LRESULT CPOPropSheet::OnTabColorUpdate(WPARAM, LPARAM)
{
	UpdateTabColors();
	return TRUE ;
}

bool CPOPropSheet::IsDirty()
{
	return m_SOMerchPropPage.IsDirty() || m_RegMerchPropPage.IsDirty();

}

bool CPOPropSheet::HasUnknownStatus()
{
	return m_RegMerchPropPage.HasUnknownStatus() || m_SOMerchPropPage.HasUnknownStatus();
}