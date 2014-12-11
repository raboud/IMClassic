// ComboBoxStoreMarket.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboBoxStoreMarket.h"


// CComboBoxStoreMarket

IMPLEMENT_DYNAMIC(CComboBoxStoreMarket, CComboBox)
CComboBoxStoreMarket::CComboBoxStoreMarket()
{
}

CComboBoxStoreMarket::~CComboBoxStoreMarket()
{
}


BEGIN_MESSAGE_MAP(CComboBoxStoreMarket, CComboBox)
END_MESSAGE_MAP()



// CComboBoxStoreMarket message handlers


void CComboBoxStoreMarket::PreSubclassWindow()
{
	CSetMarket setMarket(&g_dbFlooring);
	setMarket.Open() ;
	while (!setMarket.IsEOF())
	{
		int iItem = AddString(setMarket.m_MarketName) ;
		SetItemData(iItem, setMarket.m_MarketId) ;
		setMarket.MoveNext() ;
	}
	SetCurSel(0) ;
	setMarket.Close() ;

	CComboBox::PreSubclassWindow();
}
