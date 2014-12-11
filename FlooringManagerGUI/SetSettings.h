// CSetSettings.h : Declaration of the CSetSettings

#pragma once

// code generated on Friday, May 16, 2003, 4:13 PM

class CSetSettings : public CRecordset
{
public:
	CSetSettings(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetSettings)

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CString GetSetting(const CString& strSettingName, const CString& strDefault, int iUserID = -1);	// gets the value of the setting with passed in name
	CString GetSetting(const CString& strSettingName, int iUserID = -1);	// gets the value of the setting with passed in name
	CString GetSettings(const CString& strSettingName, char cSeparator = ';');	// gets a list of all settings with passed in
																	// name, separated by cSeparator
	long GetValueLong(const CString& strSettingName, int iUserID = -1, long lDefault = 0);
	CString GetValueString(const CString& strSettingName, int iUserID = -1, const CString& strDefault = "");
	bool SetSetting(const CString& strSettingName, const CString& strValue, int iUserID = -1);
	bool SetSetting(const CString& strSettingName, long lValue, int iUserID = -1);

protected:
	long m_ID;
	CString m_Name;
	CString m_Value;
	long m_UserID;

};


