// C:\code\Common\Source\ColorTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ColorTabCtrl.h"


// CColorTabCtrl

IMPLEMENT_DYNAMIC(CColorTabCtrl, CTabCtrl)
CColorTabCtrl::CColorTabCtrl()
{
	
}

CColorTabCtrl::~CColorTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorTabCtrl, CTabCtrl)
END_MESSAGE_MAP()



// CColorTabCtrl message handlers
void CColorTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	TC_ITEM tci;
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rect(lpDIS->rcItem);
	char szTabText[256];
	memset(szTabText, '\0', sizeof(szTabText));

	tci.mask = TCIF_TEXT;
	tci.pszText = szTabText;
	tci.cchTextMax = sizeof(szTabText) - 1;
	GetItem(lpDIS->itemID, &tci);

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		LONG lNum = m_abUseColors.GetCount();
		if ((lNum > 0) && (lpDIS->itemID <= (UINT)lNum))
		{
			if (m_abUseColors[lpDIS->itemID] == true)
			{
				pDC->SetTextColor(m_TextColor);
				pDC->SetBkColor(m_BackColor);
			}
		}
		pDC->TextOut(rect.left+5, rect.top+5, tci.pszText);
	}

	/*if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		pDC->SetTextColor(m_TextColor);
		pDC->SetBkColor(m_BackColor);
		pDC->TextOut(rect.left+5, rect.top+5, tci.pszText);
	}*/
}

LONG CColorTabCtrl::InsertItem( int nItem, TCITEM* pTabCtrlItem)
{
	LONG lReturn = CTabCtrl::InsertItem(nItem, pTabCtrlItem);
	UpdateUseColorArray(lReturn);
	return lReturn;
}
LONG CColorTabCtrl::InsertItem( int nItem, LPCTSTR lpszItem )
{
	LONG lReturn = CTabCtrl::InsertItem(nItem, lpszItem);
	UpdateUseColorArray(lReturn);
	return lReturn;
}
LONG CColorTabCtrl::InsertItem( int nItem, LPCTSTR lpszItem, int nImage )
{
	LONG lReturn = CTabCtrl::InsertItem(nItem, lpszItem, nImage);
	UpdateUseColorArray(lReturn);
	return lReturn;
}
LONG CColorTabCtrl::InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, int nImage, LPARAM lParam )
{
	LONG lReturn = CTabCtrl::InsertItem(nMask, nItem, lpszItem, nImage, lParam);
	UpdateUseColorArray(lReturn);
	return lReturn;
}
LONG CColorTabCtrl::InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, int nImage, LPARAM lParam, DWORD dwState, DWORD dwStateMask )
{
	LONG lReturn = CTabCtrl::InsertItem(nMask, nItem, lpszItem, nImage, lParam, dwState, dwStateMask);
	UpdateUseColorArray(lReturn);
	return lReturn;
}

void CColorTabCtrl::UpdateUseColorArray(LONG lIndex)
{
	if (lIndex != -1)
	{
		m_abUseColors.SetSize(lIndex);
		m_abUseColors[lIndex] = false;
	}
}

void CColorTabCtrl::UseColors(char* pszText, bool bUseColors /*= true*/)
{
	int iItems = GetItemCount();
	char szTabText[256];
	
	ASSERT(m_abUseColors.GetCount() == iItems);

	TCITEM tci;
	for (int iIndex = 0; iIndex < iItems; iIndex++)
	{
		memset(szTabText, '\0', sizeof(szTabText));
		tci.mask = TCIF_TEXT;
		tci.pszText = szTabText;
		tci.cchTextMax = sizeof(szTabText) - 1;
		if (GetItem(iIndex, &tci))
		{
			if (strcmp(szTabText, pszText) == 0)
			{
				m_abUseColors[iIndex] = bUseColors;
				return;
			}
		}
	}
}

void CColorTabCtrl::InitColorArray()
{
	int iItems = GetItemCount();
	m_abUseColors.SetSize(iItems);
	for (int iIndex = 0; iIndex < iItems; iIndex++)
	{
		m_abUseColors[iIndex] = false;
	}
}