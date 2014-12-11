// ComboUsers.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboUsers.h"
#include ".\combousers.h"
#include "SetEmployees.h"


// CComboUsers

IMPLEMENT_DYNAMIC(CComboUsers, CComboBox)
CComboUsers::CComboUsers()
{
}

CComboUsers::~CComboUsers()
{
}


BEGIN_MESSAGE_MAP(CComboUsers, CComboBox)
END_MESSAGE_MAP()



// CComboUsers message handlers


void CComboUsers::PreSubclassWindow()
{
	CSetEmployees setEmployees(&g_dbFlooring);
	setEmployees.Open() ;
	while (!setEmployees.IsEOF())
	{
		int iItem = AddString(setEmployees.m_LastName + ", " + setEmployees.m_FirstName) ;
		SetItemData(iItem, setEmployees.m_ID) ;
		setEmployees.MoveNext() ;
	}
	SetCurSel(0) ;
	setEmployees.Close() ;

	CComboBox::PreSubclassWindow();
}
