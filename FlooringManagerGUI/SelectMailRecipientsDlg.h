#pragma once

#include "SetEmployees.h"
#include "afxwin.h"

// CSelectMailRecipientsDlg dialog

class CSelectMailRecipientsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectMailRecipientsDlg)

public:
	CSelectMailRecipientsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectMailRecipientsDlg();

	void IncludeStoreManagement(CString strStoreNumber);

// Dialog Data
	enum { IDD = IDD_SELECT_MAIL_RECIPIENTS };

	virtual BOOL OnInitDialog();
	CListBox m_listEmployees;
	CListBox m_listRecipients;
	afx_msg void OnBnClickedMailAddButton();
	afx_msg void OnBnClickedMailAddAllButton();
	afx_msg void OnBnClickedMailRemoveButton();
	afx_msg void OnBnClickedMailRemoveAllButton();
	CButton m_btnAdd;
	CButton m_btnAddAll;
	CButton m_btnRemove;
	CButton m_btnRemoveAll;
	CButton m_btnOK;
	afx_msg void OnLbnSelchangeMailEmployeesList();
	afx_msg void OnLbnSelchangeMailRecipientsList();

	// returns a string with semi-colon separated list of email addresses
	CString GetRecipientAddresses(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CStringArray m_astrRecipientEmailAddresses;

	CSetEmployees m_setEmployees;
	bool m_bIncludeStoreManagement;
	int m_iStoreID;
	
	DECLARE_MESSAGE_MAP()
	// Enables / Disables buttons as appropriate
	void UpdateButtons(void);
	bool AddMailRecipient(int iIndexToMove);
	bool RemoveMailRecipient(int iIndexToMove);
	void CreateRecipientsList(void);
	virtual void OnOK();
};
