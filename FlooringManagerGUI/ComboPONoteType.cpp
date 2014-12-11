// ComboPONoteType.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboPONoteType.h"
#include ".\comboponotetype.h"
#include "SetNoteTypes.h"


// CComboPONoteType

IMPLEMENT_DYNAMIC(CComboPONoteType, CComboBox)
CComboPONoteType::CComboPONoteType()
{
}

CComboPONoteType::~CComboPONoteType()
{
}


BEGIN_MESSAGE_MAP(CComboPONoteType, CComboBox)
END_MESSAGE_MAP()



// CComboPONoteType message handlers


void CComboPONoteType::PreSubclassWindow()
{
	PopulateList(false);
	CComboBox::PreSubclassWindow();
}

void CComboPONoteType::PopulateList(bool bShowAll)
{
	if (::IsWindow(this->m_hWnd) == FALSE)
	{
		return;
	}

	ResetContent();

	int iItem = AddString("Select note type...") ;
	SetItemData(iItem, 9000) ;

	CSetNoteTypes setNoteTypes(&g_dbFlooring);
	
	if (!bShowAll)
	{
		setNoteTypes.m_strFilter = "ShowInList = 1";
	}

	setNoteTypes.m_strSort = "DisplayOrder";

	setNoteTypes.Open() ;
	
	while (!setNoteTypes.IsEOF())
	{
		bool bCanShow = true;
		if ((!bShowAll) && (TRUE == setNoteTypes.m_PermissionRequiredToSelect))
		{
			CPermissions perm;
			bCanShow = perm.HasNoteTypePermission(setNoteTypes.m_NoteTypeDescription);
		}

		if (bCanShow)
		{
			iItem = AddString(setNoteTypes.m_NoteTypeDescription) ;
			SetItemData(iItem, setNoteTypes.m_ID) ;
		}
		setNoteTypes.MoveNext() ;
	}
	SetCurSel(0) ;
	setNoteTypes.Close() ;
}

CString CComboPONoteType::GetCurrentLBText()
{
	CString strTemp = "";
	if (::IsWindow(m_hWnd))
	{
		GetLBText(GetCurSel(), strTemp);
	}

	return strTemp;
}