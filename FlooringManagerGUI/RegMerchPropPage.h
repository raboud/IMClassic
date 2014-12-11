/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

#include "GridRegMerchandise.h"
#include "OrderPropPage.h"

// CRegMerchPropPage dialog

class CRegMerchPropPage : public COrderPropPage
{
	DECLARE_DYNAMIC(CRegMerchPropPage)

public:
	CRegMerchPropPage();
	virtual ~CRegMerchPropPage();

	virtual BOOL OnInitDialog();
	void ShowDeleted(bool bShow) ;
	void SetAllowStatusUpdate(bool bAllowStatusUpdate) ;
	bool HasUnknownStatus();

// Dialog Data
	enum { IDD = IDD_REG_PROP_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

};
