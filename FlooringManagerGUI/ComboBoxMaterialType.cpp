/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ComboBoxMaterialType.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboBoxMaterialType.h"
#include "SetMaterialType.h"	// Added by ClassView
#include "SetVwMaterialTypesAndMarketsMapping.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxMaterialType

CComboBoxMaterialType::CComboBoxMaterialType()
{
}

CComboBoxMaterialType::~CComboBoxMaterialType()
{
}


BEGIN_MESSAGE_MAP(CComboBoxMaterialType, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxMaterialType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxMaterialType message handlers

void CComboBoxMaterialType::UpdateChoices(long lStoreTypeId, long lMarketID, CString strShortName, bool bShowActiveOnly /*= false */)
{
	int iCurSel = GetCurSel() ;
	int iCurMatId = GetItemData(iCurSel) ;
	ResetContent() ;
	iCurSel = CB_ERR ;
	//CSetMaterialType setMaterialType(&g_dbFlooring);
	CSetVwMaterialTypesAndMarketsMapping setMaterialType(&g_dbFlooring);
	if (bShowActiveOnly)
	{
		setMaterialType.m_strFilter.Format("[StoreTypeID] = %d AND [MarketID] = %d AND [Active] = 1", 
			lStoreTypeId, lMarketID) ;
	}
	else
	{
		setMaterialType.m_strFilter.Format("[StoreTypeID] = %d AND [MarketID] = %d", lStoreTypeId, lMarketID) ;
	}

	if (strShortName.GetLength() > 0)
	{
		CString strTemp;
		strTemp.Format(" AND [ShortName] = '%s'", strShortName);
		setMaterialType.m_strFilter += strTemp;
	}

	setMaterialType.Open() ;
	while (!setMaterialType.IsEOF())
	{
		int iItem = AddString(setMaterialType.m_MaterialTypeName) ;
		SetItemData(iItem, setMaterialType.m_MaterialTypeID) ;
		if (setMaterialType.m_MaterialTypeID == iCurMatId)
		{
			iCurSel = iItem ;
		}
		setMaterialType.MoveNext() ;
	}
	SetCurSel(iCurSel) ;
	setMaterialType.Close() ;
	this->RedrawWindow() ;
}
