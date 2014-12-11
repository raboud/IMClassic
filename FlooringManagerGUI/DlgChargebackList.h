/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "GridChargeBacks.h"

// CDlgChargebackList dialog

class CDlgChargebackList : public CDialog
{
	DECLARE_DYNAMIC(CDlgChargebackList)

public:
	CDlgChargebackList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgChargebackList();

// Dialog Data
	enum { IDD = IDD_CHARGEBACK_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CGridChargeBacks m_gridChargeBackList ;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
