// ComboIssueTypes.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboIssueTypes.h"
#include ".\comboissuetypes.h"


// CComboIssueTypes

IMPLEMENT_DYNAMIC(CComboIssueTypes, CComboBox)
CComboIssueTypes::CComboIssueTypes()
{
}

CComboIssueTypes::~CComboIssueTypes()
{
}


BEGIN_MESSAGE_MAP(CComboIssueTypes, CComboBox)
END_MESSAGE_MAP()



// CComboIssueTypes message handlers


void CComboIssueTypes::PreSubclassWindow()
{
	CSetIssueTypes setIssueTypes(&g_dbFlooring) ;

	setIssueTypes.m_strSort = "DisplayOrder, IssueType";
	setIssueTypes.Open() ;
    while (!setIssueTypes.IsEOF())
	{
		int iItem = AddString(setIssueTypes.m_IssueType) ;
		SetItemData(iItem, setIssueTypes.m_ID) ;
		setIssueTypes.MoveNext() ;
	}
	//SetCurSel(0) ;
	
	setIssueTypes.Close() ;

	CComboBox::PreSubclassWindow();
}
