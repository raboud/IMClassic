/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "GridUserAlerts.h"
#include "afxwin.h"

// CDlgUserAlerts dialog

class CDlgUserAlerts : public CDialog
{
	DECLARE_DYNAMIC(CDlgUserAlerts)

public:
	CDlgUserAlerts(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgUserAlerts();

	void RefreshGrid();

	CButton m_btnShowOnlyMyPOs;
	CButton m_cbAutoUpdate;
	CEdit m_editNumAlerts;

	afx_msg void OnBnClickedCheckOnlyMyPos();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCheckAutoupdate();

	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_USER_ALERTS };

protected:
	
	virtual void PostNcDestroy();
	virtual void OnCancel();
	void UpdateAlertCount();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CGridUserAlerts* m_pgridUserAlerts;

	int m_TimerLength;

	DECLARE_MESSAGE_MAP()

};
