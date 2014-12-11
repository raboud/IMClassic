/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "OrderPropPage.h"
#include "GridSOMerchandise.h"

// CSOMerchPropPage dialog

class CSOMerchPropPage : public COrderPropPage
{
	DECLARE_DYNAMIC(CSOMerchPropPage)

public:
	CSOMerchPropPage();
	virtual ~CSOMerchPropPage();
	virtual BOOL OnInitDialog();

	void ShowDeleted(bool bShow) ;
	void SetAllowStatusUpdate(bool bAllowStatusUpdate) ;

	bool HasUnknownStatus();

// Dialog Data
	enum { IDD = IDD_SO_PROP_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


};

