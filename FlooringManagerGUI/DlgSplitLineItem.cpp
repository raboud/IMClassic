// DlgSplitLineItem.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSplitLineItem.h"
#include ".\dlgsplitlineitem.h"


// CDlgSplitLineItem dialog

IMPLEMENT_DYNAMIC(CDlgSplitLineItem, CDialog)
CDlgSplitLineItem::CDlgSplitLineItem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplitLineItem::IDD, pParent)
	, m_strSplitText(_T(""))
	, m_fNewAmount(0)
{
	m_NumDecimals = 0;
}

CDlgSplitLineItem::~CDlgSplitLineItem()
{
}

void CDlgSplitLineItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SPLIT_TEXT, m_strSplitText);
	DDX_Control(pDX, IDC_EDIT_NEWAMOUNT, m_editNewAmount);
	DDX_Control(pDX, IDC_EDIT_BALANCE, m_editBalance);
//	DDX_Text(pDX, IDC_EDIT_NEWAMOUNT, m_fNewAmount);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CDlgSplitLineItem, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NEWAMOUNT, OnEnChangeEditNewamount)
END_MESSAGE_MAP()


// CDlgSplitLineItem message handlers

BOOL CDlgSplitLineItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editNewAmount.SetNumberDecimals(m_NumDecimals);
	m_editNewAmount.AllowBlank(true);
	m_editNewAmount.AllowNegative(false);
	UpdateBalance();
	CString strTemp;
	m_editBalance.GetWindowText(strTemp);
	m_editNewAmount.LimitText(strTemp.GetLength());
	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSplitLineItem::OnOK()
{
	CDialog::OnOK();
}

void CDlgSplitLineItem::OnEnChangeEditNewamount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData();

	CString strNewAmount;
	m_editNewAmount.GetWindowText(strNewAmount);
	if (strNewAmount.GetLength() > 0)
	{
		m_fNewAmount = atof(strNewAmount);
	}
	else
	{
		m_fNewAmount = 0.0;
	}

	UpdateBalance();

	UpdateButtons();
}

void CDlgSplitLineItem::UpdateButtons()
{
	if ((m_fNewAmount == 0.0) || (m_fNewAmount >= m_TotalAmount))
	{
		m_btnOK.EnableWindow(FALSE);
	}
	else
	{
		m_btnOK.EnableWindow(TRUE);
	}
}

void CDlgSplitLineItem::UpdateBalance()
{
	CString strFormat;
	strFormat.Format("%%.%df", m_NumDecimals);
	double dBalance = m_TotalAmount - m_fNewAmount;
	
	CString strBalance;
	strBalance.Format(strFormat, dBalance);
	m_editBalance.SetWindowText(strBalance);
}