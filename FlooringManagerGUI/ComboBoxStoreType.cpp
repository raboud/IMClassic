/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ComboBoxStoreType.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboBoxStoreType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxStoreType

CComboBoxStoreType::CComboBoxStoreType()
{
}

CComboBoxStoreType::~CComboBoxStoreType()
{
}


BEGIN_MESSAGE_MAP(CComboBoxStoreType, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxStoreType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxStoreType message handlers

void CComboBoxStoreType::PreSubclassWindow() 
{
	CSetStoreType setStoreType(&g_dbFlooring);
	setStoreType.Open() ;
	while (!setStoreType.IsEOF())
	{
		int iItem = AddString(setStoreType.m_StoreTypeName) ;
		SetItemData(iItem, setStoreType.m_StoreTypeID) ;
		setStoreType.MoveNext() ;
	}
	SetCurSel(0) ;
	setStoreType.Close() ;

	CComboBox::PreSubclassWindow();
}
