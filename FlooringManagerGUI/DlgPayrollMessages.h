#pragma once


#include "GridPayrollMessages.h"

// CDlgPayrollMessages dialog

class CDlgPayrollMessages : public CDialog
{
	DECLARE_DYNAMIC(CDlgPayrollMessages)

public:
	CDlgPayrollMessages(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPayrollMessages();

// Dialog Data
	enum { IDD = IDD_PAYROLL_MESSAGES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CGridPayrollMessages m_gridPayrollMessages;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
