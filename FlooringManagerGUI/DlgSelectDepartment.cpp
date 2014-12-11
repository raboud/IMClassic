// DlgSelectDepartment.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSelectDepartment.h"
#include "SetDepartments.h"
#include ".\dlgselectdepartment.h"


// CDlgSelectDepartment dialog

IMPLEMENT_DYNCREATE(CDlgSelectDepartment, CDialog)

CDlgSelectDepartment::CDlgSelectDepartment(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectDepartment::IDD, pParent)
{
	m_iDeptID = -1;
}

CDlgSelectDepartment::~CDlgSelectDepartment()
{
}

void CDlgSelectDepartment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEPT_SELECTION, m_comboDepts);
}

BOOL CDlgSelectDepartment::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillComboBox();
	if (m_iDeptID != -1)
	{
		for (int i = 0; i < m_comboDepts.GetCount(); i++)
		{
			if (m_comboDepts.GetItemData(i) == (DWORD) m_iDeptID)
			{
				m_comboDepts.SetCurSel(i);
				break;
			}
		}
		
	}
	else
	{
		m_comboDepts.SetCurSel(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CDlgSelectDepartment, CDialog)
END_MESSAGE_MAP()

// CDlgSelectDepartment message handlers
void CDlgSelectDepartment::FillComboBox()
{
	CSetDepartments setDepartments(&g_dbFlooring);
	setDepartments.Open();
	while(!setDepartments.IsEOF())
	{
		int iIndex = m_comboDepts.AddString(setDepartments.m_DepartmentName);
		m_comboDepts.SetItemData(iIndex, setDepartments.m_ID);
		setDepartments.MoveNext();
	}
}

void CDlgSelectDepartment::OnOK()
{
	m_iDeptID = m_comboDepts.GetItemData(m_comboDepts.GetCurSel());

	CDialog::OnOK();
}
