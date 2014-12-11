/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "GridActivityList.h"


// CDlgActivityList dialog

class CDlgActivityList : public CDialog
{
	DECLARE_DYNAMIC(CDlgActivityList)

public:
	CDlgActivityList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgActivityList();

	void RefreshGrid();

// Dialog Data
	enum { IDD = IDD_ACTIVITY_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CGridActivityList* m_pgridActivityList;

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnShowAllActivities;
	CButton m_btnShowOnlyOpenActivities;
	CButton m_btnShowOnlyMyActivities;
	CButton m_cbAutoUpdate;
	CDateTimeCtrl m_dtpStartDate;
	CDateTimeCtrl m_dtpEndDate;
	afx_msg void OnDtnCloseupActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActivitiesDtpStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusActivitiesDtpEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedShowAllActivities();
	afx_msg void OnBnClickedShowOnlyOpenActivities();
	afx_msg void OnBnClickedShowOnlyMyActivities();
	afx_msg LRESULT OnUpdateAdditionalInfo(WPARAM, LPARAM);
	CEdit m_editAdditionalInfo;
protected:
	virtual void PostNcDestroy();
	void InitControls();
	void UpdateGrid();
	void UpdateDateFilter(bool bUpdateGrid = true);

	int m_TimerLength;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnCancel();
public:
	CEdit m_editClosedBy;
	afx_msg void OnBnClickedCheckAutoupdate();
protected:
	virtual void OnOK();
};
