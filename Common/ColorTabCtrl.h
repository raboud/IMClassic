#pragma once


// CColorTabCtrl

class CColorTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CColorTabCtrl)

public:
	CColorTabCtrl();
	virtual ~CColorTabCtrl();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	void SetTextColor(COLORREF TextColor);
	void SetBkColor(COLORREF BackColor);
	virtual LONG InsertItem( int nItem, TCITEM* pTabCtrlItem);
	virtual LONG InsertItem( int nItem, LPCTSTR lpszItem );
	virtual LONG InsertItem( int nItem, LPCTSTR lpszItem, int nImage );
	virtual LONG InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, int nImage, LPARAM lParam );
	virtual LONG InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, int nImage, LPARAM lParam, DWORD dwState, DWORD dwStateMask );

	void UseColors(char* pszText, bool bUseColors = true);
	void InitColorArray();

protected:
	DECLARE_MESSAGE_MAP()

	void UpdateUseColorArray(LONG lIndex);

	CArray<bool, bool> m_abUseColors;
	COLORREF m_TextColor;
	COLORREF m_BackColor;
};

inline void CColorTabCtrl::SetTextColor(COLORREF TextColor)
{
	m_TextColor = TextColor;
}

inline void CColorTabCtrl::SetBkColor(COLORREF BackColor)
{
	m_BackColor = BackColor;
}


