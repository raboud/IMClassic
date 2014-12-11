/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// MultiListBox.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "MultiListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiListBox

CMultiListBox::CMultiListBox()
{
}

CMultiListBox::~CMultiListBox()
{
}


BEGIN_MESSAGE_MAP(CMultiListBox, CListBox)
	//{{AFX_MSG_MAP(CMultiListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiListBox message handlers

void CMultiListBox::SetSelection(int iSelection)
{
	int iCount = this->GetCount() ;
	for (int iIndex =0; iIndex < iCount; iIndex++)
	{
		bool bSelected = (iSelection & this->GetItemData(iIndex)) != 0 ;
		this->SetSel(iIndex, bSelected);
	}

}

int CMultiListBox::GetSelection()
{
	int iSelection = 0 ;
	int iCount = this->GetSelCount() ;
	int *aiSelected = new int[iCount] ;
	this->GetSelItems(iCount, aiSelected) ;

	for (int iIndex = 0; iIndex < iCount; iIndex++)
	{
		iSelection |= this->GetItemData(aiSelected[iIndex]) ;
	}
	delete [] aiSelected ;
	return iSelection ;
}

CString CMultiListBox::GetSelectedItemStrings()
{
	CString strItems = "";
	CString strTemp = "";

	int iCount = GetSelCount() ;
	int *aiSelected = new int[iCount] ;
	GetSelItems(iCount, aiSelected) ;

	for (int iIndex = 0; iIndex < iCount; iIndex++)
	{
		GetText(aiSelected[iIndex], strTemp);
		strTemp.Trim();
		if (strItems.GetLength() > 0) {strTemp = ", " + strTemp;}
		strItems += strTemp;
	}
	delete [] aiSelected;

	if (strItems.GetLength() == 0) strItems = "None";

	return strItems;
}