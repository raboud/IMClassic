#pragma once


// CComboBoxVendors

#include "SetVendorNumbers.h"

class CComboBoxVendors : public CComboBox
{
	DECLARE_DYNAMIC(CComboBoxVendors)

public:
	CComboBoxVendors();
	virtual ~CComboBoxVendors();

	int GetSelectedVendorID();
	CString GetSelectedVendorNumber();
	CString GetSelectedVendorDescription();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


