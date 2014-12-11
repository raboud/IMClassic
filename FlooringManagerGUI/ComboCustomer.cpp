// ComboCustomer.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboCustomer.h"
#include "SetCustomer.h"


// CComboCustomer

IMPLEMENT_DYNAMIC(CComboCustomer, CComboBox)
CComboCustomer::CComboCustomer()
{
	m_bSortCustID = false;
}

CComboCustomer::~CComboCustomer()
{
}


BEGIN_MESSAGE_MAP(CComboCustomer, CComboBox)
END_MESSAGE_MAP()



// CComboCustomer message handlers


void CComboCustomer::PreSubclassWindow()
{
	FillCombo();
	CComboBox::PreSubclassWindow();
}

void CComboCustomer::SortByCustID(bool bSortCustID)
{
	m_bSortCustID = bSortCustID;
}

void CComboCustomer::Reset()
{
	this->ResetContent();
	FillCombo();
}

void CComboCustomer::FillCombo()
{
	CSetCustomer setCustomer(&g_dbFlooring) ;
	
	if (m_bSortCustID)
	{
		setCustomer.m_strSort = "[CustomerID]";
	}
	else
	{
		setCustomer.m_strSort = "[LastName], [FirstName]";
	}

	if (!setCustomer.IsOpen())
	{
		setCustomer.Open();
	}
	else
	{
		setCustomer.Requery();
	}
	
	setCustomer.MoveFirst();
	
	while (!setCustomer.IsEOF())
	{
		CString strName;
		strName.Format("%s, %s (%d)", setCustomer.m_LastName, setCustomer.m_FirstName, setCustomer.m_CustomerID) ;
		int iItem = AddString(strName) ;
		SetItemData(iItem, setCustomer.m_CustomerID) ;
		setCustomer.MoveNext() ;
	}
	SetCurSel(0) ;
	setCustomer.Close() ;
}
