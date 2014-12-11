/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "GridCheckList.h"

// CDlgCheckList dialog

class CDlgCheckList : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckList)

public:
	CDlgCheckList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCheckList();

// Dialog Data
	enum { IDD = IDD_CHECK_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CGridCheckList m_gridCheckList ;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
