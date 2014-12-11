#pragma once


// CDlgAttachedDocsList dialog

class CDlgAttachedDocsList : public CDialog
{
	DECLARE_DYNAMIC(CDlgAttachedDocsList)

public:
	CDlgAttachedDocsList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAttachedDocsList();

// Dialog Data
	enum { IDD = IDD_ATTACHED_DOCS_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	int m_iCustomerID;
public:
	CString m_CustomerName;
	CString m_CustomerAddress;
	virtual BOOL OnInitDialog();
};
