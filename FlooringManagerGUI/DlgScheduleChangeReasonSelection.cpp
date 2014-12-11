// DlgScheduleChangeReasonSelection.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgScheduleChangeReasonSelection.h"
#include "SetScheduleChangeReasonCodes.h"
#include ".\dlgschedulechangereasonselection.h"

// CDlgScheduleChangeReasonSelection dialog

IMPLEMENT_DYNAMIC(CDlgScheduleChangeReasonSelection, CDialog)
CDlgScheduleChangeReasonSelection::CDlgScheduleChangeReasonSelection(bool bIsMeasure, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScheduleChangeReasonSelection::IDD, pParent)
	,m_bIsMeasure(bIsMeasure)
	,m_strReasonCode(_T(""))
{
}

CDlgScheduleChangeReasonSelection::~CDlgScheduleChangeReasonSelection()
{
}

void CDlgScheduleChangeReasonSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_REASONS, m_comboReasons);
}


BEGIN_MESSAGE_MAP(CDlgScheduleChangeReasonSelection, CDialog)
END_MESSAGE_MAP()


// CDlgScheduleChangeReasonSelection message handlers

BOOL CDlgScheduleChangeReasonSelection::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_comboReasons.ResetContent();

	CSetScheduleChangeReasonCodes setReasons(&g_dbFlooring);
	setReasons.m_strFilter = m_bIsMeasure ? "Measure = 1" : "Measure = 0";
	setReasons.Open();

	while(!setReasons.IsEOF())
	{
		int iIndex = m_comboReasons.AddString(setReasons.m_ReasonText);
		m_comboReasons.SetItemData(iIndex, setReasons.m_ID);
		setReasons.MoveNext();
	}

	m_comboReasons.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgScheduleChangeReasonSelection::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	m_comboReasons.GetLBText(m_comboReasons.GetCurSel(), m_strReasonCode);

	CDialog::OnOK();
}
