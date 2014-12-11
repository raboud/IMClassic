#pragma once


// CComboCustomer

class CComboCustomer : public CComboBox
{
	DECLARE_DYNAMIC(CComboCustomer)

public:
	CComboCustomer();
	virtual ~CComboCustomer();

	void SortByCustID(bool bSortCustID);
	void FillCombo();
	void Reset();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

	CString m_strSort;
    bool m_bSortCustID;
};


