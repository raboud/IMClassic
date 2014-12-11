#pragma once

#include "SetCustomer.h"
#include "afxwin.h"

// CDlgMergeCustomers dialog

class CDlgMergeCustomers : public CDialog
{
	DECLARE_DYNAMIC(CDlgMergeCustomers)

public:
	CDlgMergeCustomers(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMergeCustomers();

// Dialog Data
	enum { IDD = IDD_MERGE_CUSTOMERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CString m_strCustomer1;
	CString m_strCustomer2;

	int m_iCustID1;
	int m_iCustID2;

	bool m_bCustomerIDsOK;

	CSetCustomer* m_pSetCustomers;

	virtual void OnOK();

	void Merge();

public:
	virtual BOOL OnInitDialog();

	bool SetCustomerIDs(int iCustID1, int iCustID2);
	CButton m_btnCust1;
	CButton m_btnCust2;
};


