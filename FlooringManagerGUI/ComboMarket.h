#pragma once


// CComboMarket

class CComboMarket : public CComboBox
{
	DECLARE_DYNAMIC(CComboMarket)

public:
	CComboMarket();
	virtual ~CComboMarket();
	void SetInitialSelection(CString strSelection);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	CString m_strInitialSelection;
};

inline void CComboMarket::SetInitialSelection(CString strSelection)
{
	m_strInitialSelection = strSelection;
	if (IsWindow(this->m_hWnd))
	{
		if (m_strInitialSelection.GetLength() > 0)
		{
			int i = FindString(0, m_strInitialSelection);
			if (i != -1) SetCurSel(i);
		}
		else
		{
			SetCurSel(0) ;
		}
	}
}


