// DlgUserSelect.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgUserSelect.h"
#include ".\dlguserselect.h"


// CDlgUserSelect dialog

IMPLEMENT_DYNAMIC(CDlgUserSelect, CDialog)
CDlgUserSelect::CDlgUserSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserSelect::IDD, pParent)
{
	m_ID = -1;
}

CDlgUserSelect::~CDlgUserSelect()
{
}

void CDlgUserSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_COMBO, m_comboUsers);
}


BEGIN_MESSAGE_MAP(CDlgUserSelect, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CDlgUserSelect message handlers

int CDlgUserSelect::GetEmployeeID()
{
	return m_ID;
}
void CDlgUserSelect::OnBnClickedButtonReset()
{
	m_ID = -1;
	CDialog::OnOK();
}

void CDlgUserSelect::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	m_ID = m_comboUsers.GetItemData(m_comboUsers.GetCurSel());

	CDialog::OnOK();
}
