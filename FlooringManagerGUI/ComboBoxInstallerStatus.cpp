// ComboBoxInstallerStatus.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboBoxInstallerStatus.h"
#include "SetInstallerStatus.h"


// CComboInstallerStatus

IMPLEMENT_DYNAMIC(CComboInstallerStatus, CComboBox)
CComboInstallerStatus::CComboInstallerStatus()
{
}

CComboInstallerStatus::~CComboInstallerStatus()
{
}


BEGIN_MESSAGE_MAP(CComboInstallerStatus, CComboBox)
END_MESSAGE_MAP()



// CComboInstallerStatus message handlers


void CComboInstallerStatus::PreSubclassWindow()
{
	AddItems();
	CComboBox::PreSubclassWindow();
}

void CComboInstallerStatus::AddItems(bool bAddAllOption)
{
	int iIndex = -1;
	this->ResetContent();

	if (bAddAllOption)
	{
		iIndex = AddString("All");
		SetItemData(iIndex, 0);
	}

	CSetInstallerStatus setStatus(&g_dbFlooring);
	setStatus.Open();

	while (!setStatus.IsEOF())
	{
		iIndex = AddString(setStatus.m_Status.Trim());
		SetItemData(iIndex, setStatus.m_ID);
		setStatus.MoveNext();
	}

	setStatus.Close();
}

void CComboInstallerStatus::AddAll()
{
	AddItems(true);
	SetCurSel(FindStringExact(0, "Active"));
}
