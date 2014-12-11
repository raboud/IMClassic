/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "floatedit.h"
#include "combosubcontractor.h"
#include "SetChargeBacks.h"


// CDlgChargeBack dialog

class CDlgChargeBack : public CDialog
{
	DECLARE_DYNAMIC(CDlgChargeBack)

public:
	CDlgChargeBack(CWnd* pParent = NULL, long lCBId = -1);   // standard constructor
	virtual ~CDlgChargeBack();

	void SetOriginalPO(CString strOriginalPO);
	void SetStoreNumber(CString strStoreNumber);

// Dialog Data
	enum { IDD = IDD_CHARGEBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool GetDirty() ;
	void EnableOk() ;

	bool CheckChargebackNumber() ;
	bool CheckPONumber() ;
	bool CheckInstaller() ;
	bool CheckDollarAmount() ;
	bool CheckCommentField() ;
	void AssignApprovalNumber() ;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangePoNumber();
	CEdit m_editPONumber;
	CEdit m_editMarket;
	CEdit m_editDivision;
	CEdit m_editCBNumber;
	CEdit m_editCusterName;
	CFloatEdit m_editCBAmount;
	CFloatEdit m_editInstallerAmount;
	CComboSubContractor m_comboSubContractor;
	CListBox m_listChecks;

protected:
	CSetChargeBacks	m_setCB ;
	bool m_bNew ;
	long	m_ChargeBackID;

	CString			m_OriginalAmount;
	long			m_OriginalSubcontractorID;
	CString			m_OriginalAmountToSub;
	CString			m_OriginalNumber;
	CString			m_OriginalName;
	CString			m_OriginalReason;
	CString			m_OriginalIssueDate;
	CString			m_OriginalOriginalPO;
	CString			m_OriginalStoreNumber;
	long			m_OriginalOrderID ;
	BOOL			m_OriginalCostAdjustment;
	BOOL			m_OriginalApproved;
	long			m_OriginalApprovalNumber ;

public:
	virtual BOOL OnInitDialog();
	long m_lApprovalNumber;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedApproved();
	afx_msg void OnEnKillfocusPoNumber();
	afx_msg void OnEnChangeChargebackNumber();
	afx_msg void OnEnChangeApprovalNumber();
	afx_msg void OnEnChangeChargebackAmount();
	afx_msg void OnEnChangeInstallerAmount();
	afx_msg void OnCbnSelchangeChargebackSubcontractor();
	afx_msg void OnEnChangeChargebackComments();
	afx_msg void OnEnKillfocusChargebackNumber();
};
