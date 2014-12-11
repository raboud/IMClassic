/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once


// CDlgPassword dialog

class CDlgPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgPassword)

public:
	CDlgPassword(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPassword();

// Dialog Data
	enum { IDD = IDD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetTitle(CString strTitle);
	bool ValidatePassword();
	CString GetPassword();
protected:
	CString m_strPassword;
	CString m_strTitle;
	virtual void OnOK();
};
