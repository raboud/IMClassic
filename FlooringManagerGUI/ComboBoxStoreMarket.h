#pragma once


// CComboBoxStoreMarket

#include "setmarket.h"

class CComboBoxStoreMarket : public CComboBox
{
	DECLARE_DYNAMIC(CComboBoxStoreMarket)

public:
	CComboBoxStoreMarket();
	virtual ~CComboBoxStoreMarket();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


