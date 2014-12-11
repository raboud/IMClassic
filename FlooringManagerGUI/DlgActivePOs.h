/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "GridActivePOs.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CDlgActivePOs dialog

class CDlgActivePOs : public CDialog
{
	DECLARE_DYNAMIC(CDlgActivePOs)

public:
	CDlgActivePOs(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgActivePOs();

	void RefreshGrid();

	CButton m_btnShowOnlyMyPOs;
	CButton m_cbAutoUpdate;
	CButton m_btnShowAllActivePOs;
	CButton m_btnShowOnlyPOsWithAlerts;
	CButton m_btnIncludeCancelledPOs;

	afx_msg void OnBnClickedCheckOnlyMyPos();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCheckAutoupdate();

	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_ACTIVE_POS };

protected:

	virtual void PostNcDestroy();
	virtual void OnCancel();
	void UpdatePOCount();
	void InitControls();
	void UpdateDateFilter();
	void UpdateGrid();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CGridActivePOs* m_pgridActivePOs;

	int m_TimerLength;

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_dtpStartDate;
	CDateTimeCtrl m_dtpEndDate;
	afx_msg void OnBnClickedActivePOsShowAllActivePOs();
	afx_msg void OnBnClickedActivePOsShowPOsWithAlerts();
	afx_msg void OnBnClickedActivePOsIncludeCancelledPOs();
	CEdit m_editNumPOs;
	
	afx_msg void OnDtnCloseupActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
};
