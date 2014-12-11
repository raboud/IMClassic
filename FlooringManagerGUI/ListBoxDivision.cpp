// ListBoxDivision.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ListBoxDivision.h"
#include "SetDivision.h"


// CListBoxDivision

IMPLEMENT_DYNAMIC(CListBoxDivision, CListBox)
CListBoxDivision::CListBoxDivision()
{
}

CListBoxDivision::~CListBoxDivision()
{
}


BEGIN_MESSAGE_MAP(CListBoxDivision, CListBox)
END_MESSAGE_MAP()



// CListBoxDivision message handlers


void CListBoxDivision::PreSubclassWindow()
{
	CSetDivision setDivision(&g_dbFlooring) ;

	setDivision.Open() ;
	while (!setDivision.IsEOF())
	{
		if (setDivision.m_DivisionID != -1)
		{
			int iItem = AddString(setDivision.m_Division.Trim()) ;
			SetItemData(iItem, setDivision.m_DivisionID) ;
		}
		setDivision.MoveNext() ;
	}
	SetCurSel(0) ;
	
	setDivision.Close() ;

	CListBox::PreSubclassWindow();
}
