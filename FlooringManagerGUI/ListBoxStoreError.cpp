/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ListBoxStoreError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "ListBoxStoreError.h"
#include "SetStoreError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxStoreError

CListBoxStoreError::CListBoxStoreError()
{
}

CListBoxStoreError::~CListBoxStoreError()
{
}


BEGIN_MESSAGE_MAP(CListBoxStoreError, CMultiListBox)
	//{{AFX_MSG_MAP(CListBoxStoreError)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxStoreError message handlers

void CListBoxStoreError::PreSubclassWindow() 
{
	CSetStoreError set(&g_dbFlooring) ;

	set.Open() ;
	while (!set.IsEOF())
	{
		if (set.m_Id != 0)
		{
			int iItem = AddString(set.m_Description) ;
			SetItemData(iItem, set.m_Id) ;
		}
		set.MoveNext() ;
	}
	set.Close() ;

	CMultiListBox::PreSubclassWindow();
}
