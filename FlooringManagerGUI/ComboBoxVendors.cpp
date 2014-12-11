// ComboBoxVendors.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboBoxVendors.h"

// CComboBoxVendors

IMPLEMENT_DYNAMIC(CComboBoxVendors, CComboBox)
CComboBoxVendors::CComboBoxVendors()
{
}

CComboBoxVendors::~CComboBoxVendors()
{
}


BEGIN_MESSAGE_MAP(CComboBoxVendors, CComboBox)
END_MESSAGE_MAP()



// CComboBoxVendors message handlers


void CComboBoxVendors::PreSubclassWindow()
{
	CSetVendorNumbers setVendors(&g_dbFlooring);
	setVendors.Open() ;
	CString strTemp;
	while (!setVendors.IsEOF())
	{
		strTemp.Format("%10s - %s", setVendors.m_Description, setVendors.m_VendorNumber);
		int iItem = AddString(strTemp) ;
		SetItemData(iItem, setVendors.m_VendorID) ;
		setVendors.MoveNext() ;
	}
//	SetCurSel(0) ;
	setVendors.Close() ;

	CComboBox::PreSubclassWindow();
}

int CComboBoxVendors::GetSelectedVendorID()
{
	return GetItemData(GetCurSel());
}

CString CComboBoxVendors::GetSelectedVendorNumber()
{
	CString strTemp;
	GetLBText(GetCurSel(), strTemp);
	strTemp = strTemp.Left(strTemp.Find('('));
	return strTemp.Trim();
}

CString CComboBoxVendors::GetSelectedVendorDescription()
{
	CString strTemp;
	GetLBText(GetCurSel(), strTemp);
	int iLeft = strTemp.Find('(');
	int iRight = strTemp.Find(')');
	strTemp = strTemp.Mid(iLeft, iRight);
	return strTemp.Trim();
}
