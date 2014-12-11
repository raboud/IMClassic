// ComboSpokeWith.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboSpokeWith.h"
#include ".\combospokewith.h"
#include "SetSpokeWith.h"
#include "SetNoteTypes.h"
#include "SetEmployees.h"


// CComboSpokeWith

IMPLEMENT_DYNAMIC(CComboSpokeWith, CComboBox)
CComboSpokeWith::CComboSpokeWith()
{
}

CComboSpokeWith::~CComboSpokeWith()
{
}


BEGIN_MESSAGE_MAP(CComboSpokeWith, CComboBox)
END_MESSAGE_MAP()



// CComboSpokeWith message handlers


void CComboSpokeWith::PreSubclassWindow()
{
	PopulateList(-1);
	CComboBox::PreSubclassWindow();
}

void CComboSpokeWith::PopulateList(int iNoteTypeID)
{
	if (::IsWindow(this->m_hWnd) == FALSE)
	{
		return;
	}

	ResetContent();

	int iItem = -1;
	CSetNoteTypes setNoteTypes(&g_dbFlooring);
	setNoteTypes.m_strFilter.Format("ID = '%d'", iNoteTypeID);
	setNoteTypes.Open();

	if (!setNoteTypes.IsEOF())
	{
		CSetSpokeWith setSpokeWith(&g_dbFlooring);
		setSpokeWith.m_strSort = "DisplayOrder";

		if (setNoteTypes.m_ShowSpokeWith)
		{
			// we are going to include everything in the ShowSpoke with table
			setSpokeWith.Open() ;
			while (!setSpokeWith.IsEOF())
			{
				iItem = AddString(setSpokeWith.m_SW_Text) ;
				SetItemData(iItem, setSpokeWith.m_SpokeWith) ;
				setSpokeWith.MoveNext() ;
			}
			setSpokeWith.Close() ;
		}
		else
		{
			// we are only going to include items in the ShowSpokeWith table that has ShowAlways = 1
			setSpokeWith.m_strFilter = "ShowAlways = 1";
			setSpokeWith.Open();
			while (!setSpokeWith.IsEOF())
			{
				iItem = AddString(setSpokeWith.m_SW_Text) ;
				SetItemData(iItem, setSpokeWith.m_SpokeWith) ;
				setSpokeWith.MoveNext() ;
			}
			setSpokeWith.Close() ;
		}

		if (setNoteTypes.m_ShowEmployees)
		{
			CSetEmployees setEmployees(&g_dbFlooring);
			setEmployees.m_strFilter = "ReceiveCallNotes = 1 AND Active = 1";
			setEmployees.m_strSort = "LastName";
			setEmployees.Open();
			while(!setEmployees.IsEOF())
			{
				iItem = AddString(setEmployees.m_FirstName + " " + setEmployees.m_LastName);
				SetItemData(iItem, 8000+setEmployees.m_ID);   // add 8000 so we know this is an employee id, not spokewith id
				setEmployees.MoveNext();
			}
			setEmployees.Close();
		}
	}

	SetCurSel(0) ;
}