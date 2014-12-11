/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ComboSubContractor.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "ComboSubContractor.h"
#include "SetSubContractor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboSubContractor

CComboSubContractor::CComboSubContractor()
{
}

CComboSubContractor::~CComboSubContractor()
{
}


BEGIN_MESSAGE_MAP(CComboSubContractor, CComboBox)
	//{{AFX_MSG_MAP(CComboSubContractor)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboSubContractor message handlers

void CComboSubContractor::PreSubclassWindow() 
{
	CSetSubContractor setSubs(&g_dbFlooring) ;
	setSubs.m_strFilter = "[Helper] = 0";
	setSubs.m_strSort = "[LastName]";
	setSubs.Open() ;
	
	// add "N/A" as first item w/ -1 as value
	int iItem = AddString("N/A");
	SetItemData(iItem, (DWORD_PTR) -1);
	
	while (!setSubs.IsEOF())
	{
		CString strName = setSubs.m_LastName + ", " + setSubs.m_FirstName ;
		iItem = AddString(strName) ;
		SetItemData(iItem, setSubs.m_SubContractorID) ;
		setSubs.MoveNext() ;
	}
	SetCurSel(0) ;
	setSubs.Close() ;
	
	CComboBox::PreSubclassWindow();
}
