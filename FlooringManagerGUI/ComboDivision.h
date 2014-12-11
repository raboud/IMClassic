#pragma once


// CComboDivision

class CComboDivision : public CComboBox
{
	DECLARE_DYNAMIC(CComboDivision)

public:
	CComboDivision();
	virtual ~CComboDivision();
	void SetInitialSelection(CString strSelection);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	CString m_strInitialSelection;
};

inline void CComboDivision::SetInitialSelection(CString strSelection)
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