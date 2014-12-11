#pragma once
#include "afxwin.h"
#include "ComboCustomer.h"
#include "SetOrders.h"
#include "CustomerPickList.h"
#include "SetCustomer.h"


// CDlgTransferPO dialog

class CDlgTransferPO : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransferPO)

public:
	CDlgTransferPO(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTransferPO();

// Dialog Data
	enum { IDD = IDD_TRANSFERPO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CString m_strCustName;
	long m_lCustID;

	DECLARE_MESSAGE_MAP()

	virtual void OnOK();

	void CustomerFind();
	void OnCustomerFind();
	bool BuildFilterString(bool bDoPartial = true);

	bool m_bEditing;

	void EnableControl(UINT nID, bool bEnable = true) ;
	void ShowControl(UINT nID, bool bShow = true) ;

	CPoList m_PoList;

public:
	CString m_strMessage;
	virtual BOOL OnInitDialog();
	void SetInfo(CString strCustName, long lCustID, CPoList* pListPOs);
	
	CCustomerPickList m_gridCustomer ;
	CSetCustomer* m_pSet;

	CEdit m_editLastName;
	CEdit m_editFirstName;
	afx_msg void OnEnChangeTransferpoCustlname();
	afx_msg void OnEnChangeTransferpoCustfname();
	afx_msg void OnBnClickedTransferpoFindbutton();
	afx_msg LRESULT OnCustomerSelected (WPARAM, LPARAM);
	afx_msg void OnBnClickedCancel();
};

inline void CDlgTransferPO::SetInfo(CString strCustName, long lCustID, CPoList* pListPOs)
{
	m_strCustName = strCustName;
	m_lCustID = lCustID;
	m_PoList.AddHead(pListPOs);
}
