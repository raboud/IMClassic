/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ListBoxMeasureError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "ListBoxMeasureError.h"
#include "SetMeasureError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxMeasureError

CListBoxMeasureError::CListBoxMeasureError()
{
}

CListBoxMeasureError::~CListBoxMeasureError()
{
}


BEGIN_MESSAGE_MAP(CListBoxMeasureError, CMultiListBox)
	//{{AFX_MSG_MAP(CListBoxMeasureError)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxMeasureError message handlers

void CListBoxMeasureError::PreSubclassWindow() 
{
	CSetMeasureError set(&g_dbFlooring);

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
