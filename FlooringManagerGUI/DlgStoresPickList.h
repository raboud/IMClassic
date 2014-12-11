#pragma once
#include "afxwin.h"
#include "GridStores.h"


// CDlgStoresPickList dialog

class CDlgStoresPickList : public CDialog
{
	DECLARE_DYNAMIC(CDlgStoresPickList)

public:
	CDlgStoresPickList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStoresPickList();

// Dialog Data
	enum { IDD = IDD_STORES_PICKLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CGridStores m_gridStores;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_btnShowActiveOnly;
	afx_msg void OnBnClickedStoresShowActive();
};
