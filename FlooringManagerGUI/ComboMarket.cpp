// ComboMarket.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ComboMarket.h"
#include "SetMarket.h"


// CComboMarket

IMPLEMENT_DYNAMIC(CComboMarket, CComboBox)
CComboMarket::CComboMarket()
{
}

CComboMarket::~CComboMarket()
{
}


BEGIN_MESSAGE_MAP(CComboMarket, CComboBox)
END_MESSAGE_MAP()



// CComboMarket message handlers


void CComboMarket::PreSubclassWindow()
{
	CSetMarket setMarket(&g_dbFlooring) ;

	setMarket.Open() ;
	while (!setMarket.IsEOF())
	{
		int iItem = AddString(setMarket.m_MarketName) ;
		SetItemData(iItem, setMarket.m_MarketId) ;
		setMarket.MoveNext() ;
	}
	SetCurSel(0);
	setMarket.Close() ;

	CComboBox::PreSubclassWindow();
}
