/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "GridActivePOs.h"
#include "CFIFormView.h"

// CViewActivePOs form view

class CViewActivePOs : public CCFIFormView
{
	DECLARE_DYNCREATE(CViewActivePOs)

protected:
	CViewActivePOs();           // protected constructor used by dynamic creation
	virtual ~CViewActivePOs();

	void RefreshGrid();

	CButton m_btnShowOnlyMyPOs;
	CButton m_cbAutoUpdate;
	CButton m_btnShowAllActivePOs;
	CButton m_btnShowOnlyPOsWithAlerts;
	CButton m_btnIncludeCancelledPOs;

	CDateTimeCtrl m_dtpStartDate;
	CDateTimeCtrl m_dtpEndDate;
	CEdit m_editNumPOs;

public:
	enum { IDD = IDD_ACTIVE_POS };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	
	void UpdatePOCount();
	void InitControls();
	void UpdateDateFilter();
	void UpdateGrid();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CGridActivePOs* m_pgridActivePOs;

	virtual void PostNcDestroy();

	int m_TimerLength;

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckOnlyMyPos();
	afx_msg void OnBnClickedCheckAutoupdate();
	afx_msg void OnDtnCloseupActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActiveposDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActiveposDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedActivePOsShowAllActivePOs();
	afx_msg void OnBnClickedActivePOsShowPOsWithAlerts();
	afx_msg void OnBnClickedActivePOsIncludeCancelledPOs();

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
};


