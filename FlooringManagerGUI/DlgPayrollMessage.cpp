// DlgPayrollMessage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgPayrollMessage.h"
#include ".\dlgpayrollmessage.h"

// CDlgPayrollMessage dialog

IMPLEMENT_DYNAMIC(CDlgPayrollMessage, CDialog)
CDlgPayrollMessage::CDlgPayrollMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPayrollMessage::IDD, pParent)
	, m_strMessageText(_T(""))
{
	COleDateTime timeNow = CGlobals::GetCurrentSystemTime();
	m_timeStartDate = COleDateTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);
	m_timeEndDate = m_timeStartDate;
}

CDlgPayrollMessage::~CDlgPayrollMessage()
{
}

void CDlgPayrollMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MESSAGE_TEXT, m_strMessageText);
	DDX_Control(pDX, IDC_DTP_START, m_dtpStart);
	DDX_Control(pDX, IDC_DTPEND, m_dtpEnd);
	DDX_Control(pDX, IDC_MESSAGE_TEXT, m_editMessageText);
	DDX_DateTimeCtrl(pDX, IDC_DTP_START, m_timeStartDate);
	DDX_DateTimeCtrl(pDX, IDC_DTPEND, m_timeEndDate);
}


BEGIN_MESSAGE_MAP(CDlgPayrollMessage, CDialog)
END_MESSAGE_MAP()


// CDlgPayrollMessage message handlers

BOOL CDlgPayrollMessage::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dtpStart.SetTime(m_timeStartDate);
	m_dtpEnd.SetTime(m_timeEndDate);

	m_editMessageText.SetLimitText(255);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPayrollMessage::SetMessage(CString strText, COleDateTime timeStart, COleDateTime timeEnd)
{
	m_strMessageText = strText;
	m_timeStartDate = timeStart;
	m_timeEndDate = timeEnd;
}

void CDlgPayrollMessage::GetMessage(CString& strText, COleDateTime& timeStart, COleDateTime& timeEnd)
{
	strText = m_strMessageText;
	timeStart = m_timeStartDate;
	timeEnd = m_timeEndDate;
}

bool CDlgPayrollMessage::Validate()
{
	UpdateData();
	if (m_strMessageText.GetLength() == 0)
	{
		MessageBox("Message length cannot be 0.");
		return false;
	}

	if (m_timeStartDate > m_timeEndDate)
	{
		MessageBox("End Date cannot be before Start Date");
		return false;
	}

	return true;
}
void CDlgPayrollMessage::OnOK()
{
	if (Validate())
	{
		CDialog::OnOK();
	}
}
