#pragma once
#include "afxwin.h"
#include "ComboBoxVendors.h"


// CDlgSelectVendor dialog

class CDlgSelectVendor : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectVendor)

public:
	CDlgSelectVendor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectVendor();

// Dialog Data
	enum { IDD = IDD_SELECT_VENDOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBoxVendors m_comboVendor;
	int GetVendorID(void);
	CString GetVendorDescription();
	CString GetVendorNumber();
protected:
	int m_iVendorID;
	CString m_strVendorDescription;
	CString m_strVendorNumber;
	virtual void OnOK();
public:
	afx_msg void OnCbnSelchangeSelectVendorCombo();
	virtual BOOL OnInitDialog();
};

inline int CDlgSelectVendor::GetVendorID(void)
{
	return m_iVendorID;
}

inline CString CDlgSelectVendor::GetVendorDescription()
{
	return m_strVendorDescription;
}

inline CString CDlgSelectVendor::GetVendorNumber()
{
	return m_strVendorNumber;
}
