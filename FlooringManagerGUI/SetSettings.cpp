// CSetSettings.h : Implementation of the CSetSettings class



// CSetSettings implementation

// code generated on Friday, May 16, 2003, 4:13 PM

#include "stdafx.h"
#include "SetSettings.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace CFI::InstallationManager::Business;
using namespace CFI::DB::Entities;

CSetSettings::CSetSettings(CDatabase*  /* pdb */)
{
}

long CSetSettings::GetValueLong(const CString& strSettingName, int iUserID/* = -1 */, long lDefault/* = 0 */)
{
	CString strValue = GetSetting(strSettingName, iUserID) ;
	long lValue = atol(strValue) ;

	// if we don't actually have a value, return the default
	if (strValue.GetLength() == 0)
	{
		lValue = lDefault;
	}

	return lValue ;
}

CString CSetSettings::GetValueString(const CString& strSettingName, int iUserID, const CString& strDefault)
{
	CString strValue = GetSetting(strSettingName, iUserID) ;
	
	// if we don't actually have a value, return the default
	if (strValue.GetLength() == 0)
	{
		strValue = strDefault;
	}

	return strValue ;
}

CString CSetSettings::GetSetting(const CString& strSettingName, int iUserID /* = -1 */)
{
	return GetSetting(strSettingName, "", iUserID);
}

CString CSetSettings::GetSetting(const CString& strSettingName, const CString& strDefault, int iUserID /* = -1 */)
{
	CString strValue = strDefault;

	if (iUserID == -1)
	{
		strValue = SettingsBLL::GetSetting(CachedData::Context, gcnew System::String(strSettingName), gcnew System::String(strDefault));
	}
	else
	{
		strValue = SettingsBLL::GetUserSetting(CachedData::Context, gcnew System::String(strSettingName), gcnew System::String(strDefault), iUserID);
	}
    
	return strValue;
}

CString CSetSettings::GetSettings(const CString& strSettingName, char cSeparator/* = ','*/)
{
	List<String^> setting =   SettingsBLL::GetSettingsValues(CachedData::Context, gcnew System::String(strSettingName));

	CString strValue = "";
	CString strTemp = "";

	for each (String^ value in setting)
	{
		if (strValue.GetLength() > 0)
		{
			strTemp.Format("%c%s", cSeparator, value);
		}
		else
		{
			strTemp = value;
		}
		strValue += strTemp;
	}

	return strValue;
}

bool CSetSettings::SetSetting(const CString& strSettingName, const CString& strValue, int iUserID /* -1 */)
{
    return SettingsBLL::SetUserSetting(gcnew System::String(strSettingName), gcnew System::String(strValue), iUserID, CachedData::Context);
}

bool CSetSettings::SetSetting(const CString& strSettingName, long lValue, int iUserID /* = -1 */)
{
	CString strValue ;
	strValue.Format("%d", lValue) ;
	return SetSetting(strSettingName, strValue, iUserID) ;
}

