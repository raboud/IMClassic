#pragma once

#include "gridreports.h"
#include "afxwin.h"
#include "AutoRichEditCtrl.h"

// CDlgReportList dialog

class CDlgReportList : public CDialog
{
	DECLARE_DYNAMIC(CDlgReportList)

public:
	CDlgReportList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgReportList();

	void SetOrderId(int iOrderID);

// Dialog Data
	enum { IDD = IDD_REPORT_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CGridReports m_gridReports;
	int m_iOrderId;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CAutoRichEditCtrl m_editHiddenRTF;
};
