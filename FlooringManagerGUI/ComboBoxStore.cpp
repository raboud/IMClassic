/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ComboBoxStore.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboBoxStore.h"
#include "SetStores.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxStore

CComboBoxStore::CComboBoxStore()
{
}

CComboBoxStore::~CComboBoxStore()
{
}


BEGIN_MESSAGE_MAP(CComboBoxStore, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxStore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxStore message handlers

void CComboBoxStore::PreSubclassWindow() 
{
	CSetStores setStores(&g_dbFlooring);

	setStores.Open() ;
	while (!setStores.IsEOF())
	{
		int iItem = AddString(setStores.m_StoreNumber) ;
		SetItemData(iItem, setStores.m_StoreID) ;
		setStores.MoveNext() ;
	}
	SetCurSel(0) ;
	setStores.Close() ;

	CComboBox::PreSubclassWindow();
}
