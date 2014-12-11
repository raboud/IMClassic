/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "GridActivityList.h"

// CViewActivityList form view

class CViewActivityList : public CFormView
{
	DECLARE_DYNCREATE(CViewActivityList)

protected:
	CViewActivityList();           // protected constructor used by dynamic creation
	virtual ~CViewActivityList();

public:
	enum { IDD = IDD_ACTIVITY_LIST };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CGridActivityList* m_pgridActivityList;

	int m_TimerLength;

	void InitControls();
	void UpdateGrid();
	void UpdateDateFilter(bool bUpdateGrid = true);

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnShowAllActivities;
	CButton m_btnShowOnlyOpenActivities;
	CButton m_btnShowOnlyMyActivities;
	CButton m_cbAutoUpdate;
	CDateTimeCtrl m_dtpStartDate;
	CDateTimeCtrl m_dtpEndDate;
	CEdit m_editAdditionalInfo;
	CEdit m_editClosedBy;
	afx_msg void OnDtnCloseupActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedShowOnlyOpenActivities();
	afx_msg void OnBnClickedShowAllActivities();
	afx_msg void OnBnClickedShowOnlyMyActivities();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckAutoupdate();
	virtual void OnInitialUpdate();

	void RefreshGrid();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUpdateAdditionalInfo(WPARAM, LPARAM);
	afx_msg void OnDestroy();
};


