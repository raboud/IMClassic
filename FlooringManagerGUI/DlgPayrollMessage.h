#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "atltime.h"


// CDlgPayrollMessage dialog

class CDlgPayrollMessage : public CDialog
{
	DECLARE_DYNAMIC(CDlgPayrollMessage)

public:
	CDlgPayrollMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPayrollMessage();

// Dialog Data
	enum { IDD = IDD_PAYROLL_MESSAGE_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool Validate();

	CString m_strMessageText;
	CDateTimeCtrl m_dtpStart;
	CDateTimeCtrl m_dtpEnd;

	CEdit m_editMessageText;
	COleDateTime m_timeStartDate;
	COleDateTime m_timeEndDate;

	DECLARE_MESSAGE_MAP()
public:

	void SetMessage(CString strText, COleDateTime timeStart, COleDateTime timeEnd);
	void GetMessage(CString& strText, COleDateTime& timeStart, COleDateTime& timeEnd);
	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

};
