#pragma once
#include "afxwin.h"


// CDlgSelectCustomer dialog

class CDlgSelectCustomer : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectCustomer)

public:
	CDlgSelectCustomer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectCustomer();

// Dialog Data
	enum { IDD = IDD_SELECT_CUSTOMER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CString m_strPONumber ;
	CString m_strStoreNumber;
	int m_iCustomerID;
	int m_iOrderID;

	void FillComboBox();

	DECLARE_MESSAGE_MAP()

public:
	CStatic m_stStaticText;
	CComboBox m_comboCustomers;
	virtual BOOL OnInitDialog();
	int SetPONumber(CString strPONumber, CString strStoreNumber);
    int GetCustomerID();
	int GetOrderID();
	CString GetStoreNumber();

protected:
	virtual void OnOK();
};

inline int CDlgSelectCustomer::GetCustomerID()
{
	return m_iCustomerID;
}

inline int CDlgSelectCustomer::GetOrderID()
{
	return m_iOrderID;
}

inline CString CDlgSelectCustomer::GetStoreNumber()
{
	return m_strStoreNumber;
}