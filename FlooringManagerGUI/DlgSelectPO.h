/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"


// CDlgSelectPO dialog

class CDlgSelectPO : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectPO)

public:
	CDlgSelectPO(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectPO();

// Dialog Data
	enum { IDD = IDD_SELECT_PO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void FillPOCombo(void);

	long m_lCustomerID;
	long m_lOrderID;
	long m_lSelectedOrderID;
	CString m_strStoreNumber;
	CComboBox m_comboPO;

	DECLARE_MESSAGE_MAP()
public:
	
	bool SetOrderID(long lOrderID);
	long GetSelectedOrderID();
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
