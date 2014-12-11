/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "ComboMarket.h"
#include "ComboDivision.h"

// CTransactionDetailsDialog dialog

const CString strOVERHEAD = "Overhead";
const CString strREGULAR = "Regular";

class CTransactionDetailsDialog : public CDialog
{
	DECLARE_DYNAMIC(CTransactionDetailsDialog)

public:
	CTransactionDetailsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransactionDetailsDialog();

// Dialog Data
	enum { IDD = IDD_PAYROLL_MARKET_DIVISION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int m_iMarketID;
	CString m_strMarket;
	int m_iDivisionID;
	CString m_strDivision;
	CString m_strType;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboMarket m_comboMarket;
	CComboDivision m_comboDivision;
	CComboBox m_comboType;
	CString m_strTransactionDetails;

	void SetTransactionDetails(CString strDetails);
	int GetMarketID();
	CString GetMarket();
	int GetDivisionID();
	CString GetDivision();
	bool IsOverheadTx();
	afx_msg void OnCbnSelchangeTransactionTypeCombo();
};

inline int CTransactionDetailsDialog::GetMarketID()
{
	return m_iMarketID;
}

inline CString CTransactionDetailsDialog::GetMarket()
{
	return m_strMarket;
}

inline int CTransactionDetailsDialog::GetDivisionID()
{
	return m_iDivisionID;
}

inline CString CTransactionDetailsDialog::GetDivision()
{
	return m_strDivision;
}

inline bool CTransactionDetailsDialog::IsOverheadTx()
{
	return (m_strType == strOVERHEAD);
}