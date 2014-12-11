#pragma once
#include "afxwin.h"
#include "FloatEdit.h"


// CDlgSplitLineItem dialog

class CDlgSplitLineItem : public CDialog
{
	DECLARE_DYNAMIC(CDlgSplitLineItem)

public:
	CDlgSplitLineItem(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSplitLineItem();

// Dialog Data
	enum { IDD = IDD_SPLIT_LINEITEM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	double m_TotalAmount;
	int m_NumDecimals;
	
public:
	virtual BOOL OnInitDialog();
	void SetTotalAmount(double dAmount);
	void SetNumDecimals(int iNumDecimals);
	void SetSplitText(CString strText);
	double GetNewAmount();
	
	CFloatEdit m_editNewAmount;
	CEdit m_editBalance;

protected:
	virtual void OnOK();
	void UpdateButtons();
	void UpdateBalance();

	CString m_strSplitText;

public:
	afx_msg void OnEnChangeEditNewamount();
	double m_fNewAmount;
	CButton m_btnOK;
};

inline double CDlgSplitLineItem::GetNewAmount()
{
	return m_fNewAmount;
}

inline void CDlgSplitLineItem::SetNumDecimals(int iNumDecimals)
{
	m_NumDecimals = iNumDecimals;
}

inline void CDlgSplitLineItem::SetTotalAmount(double dAmount)
{
	m_TotalAmount = dAmount;
}

inline void CDlgSplitLineItem::SetSplitText(CString strText)
{
	m_strSplitText = strText;
}