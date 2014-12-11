// ComboDivision.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboDivision.h"
#include "SetDivision.h"


// CComboDivision

IMPLEMENT_DYNAMIC(CComboDivision, CComboBox)
CComboDivision::CComboDivision()
{
}

CComboDivision::~CComboDivision()
{
}


BEGIN_MESSAGE_MAP(CComboDivision, CComboBox)
END_MESSAGE_MAP()



// CComboDivision message handlers


void CComboDivision::PreSubclassWindow()
{
	CSetDivision setDivision(&g_dbFlooring) ;

	setDivision.Open() ;
	while (!setDivision.IsEOF())
	{
		int iItem = AddString(setDivision.m_Division) ;
		SetItemData(iItem, setDivision.m_DivisionID) ;
		setDivision.MoveNext() ;
	}
	SetCurSel(0) ;
	
	setDivision.Close() ;

	CComboBox::PreSubclassWindow();
}
