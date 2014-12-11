#pragma once

#include "CustSatPropertyPage.h"

// CCustomerSatPropertySheet

class CCustomerSatPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCustomerSatPropertySheet)

public:
	CCustomerSatPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCustomerSatPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CCustomerSatPropertySheet();

	LRESULT OnRichEditChange(WPARAM wParam, LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()

	CCustSatPropertyPage m_pageAction;
	CCustSatPropertyPage m_pageCause;
	CCustSatPropertyPage m_pageNature;

};


