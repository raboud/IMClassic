/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// listBoxMillError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "listBoxMillError.h"
#include "SetMillError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxMillError

CListBoxMillError::CListBoxMillError()
{
}

CListBoxMillError::~CListBoxMillError()
{
}


BEGIN_MESSAGE_MAP(CListBoxMillError, CMultiListBox)
	//{{AFX_MSG_MAP(CListBoxMillError)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxMillError message handlers

void CListBoxMillError::PreSubclassWindow() 
{
	CSetMillError set(&g_dbFlooring);

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
