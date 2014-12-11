// CustomerSatPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "CustomerSatPropertySheet.h"


// CCustomerSatPropertySheet

IMPLEMENT_DYNAMIC(CCustomerSatPropertySheet, CPropertySheet)
CCustomerSatPropertySheet::CCustomerSatPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_pageNature);
	AddPage(&m_pageAction);
	AddPage(&m_pageCause);
}

CCustomerSatPropertySheet::CCustomerSatPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CCustomerSatPropertySheet::~CCustomerSatPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CCustomerSatPropertySheet, CPropertySheet)
	ON_MESSAGE(WM_USER_RICHEDITCHANGE, OnRichEditChange)
END_MESSAGE_MAP()


// CCustomerSatPropertySheet message handlers

LRESULT CCustomerSatPropertySheet::OnRichEditChange(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
