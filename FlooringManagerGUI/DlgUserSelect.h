/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "ComboUsers.h"


// CDlgUserSelect dialog

class CDlgUserSelect : public CDialog
{
	DECLARE_DYNAMIC(CDlgUserSelect)

public:
	CDlgUserSelect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgUserSelect();

	int GetEmployeeID();

// Dialog Data
	enum { IDD = IDD_USERS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	int m_ID;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonReset();
protected:
	virtual void OnOK();
public:
	CComboUsers m_comboUsers;
};
