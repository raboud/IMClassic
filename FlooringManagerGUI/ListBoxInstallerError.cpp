/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ListBoxInstallerError.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "ListBoxInstallerError.h"
#include "SetInstallerError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxInstallerError

CListBoxInstallerError::CListBoxInstallerError()
{
}

CListBoxInstallerError::~CListBoxInstallerError()
{
}


BEGIN_MESSAGE_MAP(CListBoxInstallerError, CMultiListBox)
	//{{AFX_MSG_MAP(CListBoxInstallerError)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxInstallerError message handlers

void CListBoxInstallerError::PreSubclassWindow() 
{
	CSetInstallerError set(&g_dbFlooring);

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
