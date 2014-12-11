#pragma once


// CComboInstallerStatus

class CComboInstallerStatus : public CComboBox
{
	DECLARE_DYNAMIC(CComboInstallerStatus)

public:
	CComboInstallerStatus();
	virtual ~CComboInstallerStatus();

	void AddAll();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	void AddItems(bool bAddAllOption = false);
};


