// CSetSettings.h : Implementation of the CSetSettings class



// CSetSettings implementation

// code generated on Friday, May 16, 2003, 4:13 PM

#include "stdafx.h"
#include "SetSettings.h"
IMPLEMENT_DYNAMIC(CSetSettings, CRecordset)

CSetSettings::CSetSettings(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = _T("");
	m_Value = _T(L"");
	m_UserID = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CSetSettings::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetSettings::GetDefaultSQL()
{
	return _T("[dbo].[Settings]");
}

void CSetSettings::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Value]"), m_Value);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);

}
/////////////////////////////////////////////////////////////////////////////
// CSetSettings diagnostics

#ifdef _DEBUG
void CSetSettings::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetSettings::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

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
		m_strFilter.Format("Name = '%s'", strSettingName);
	}
	else
	{
		m_strFilter.Format("Name = '%s' AND UserID = %d", strSettingName, iUserID);
	}
    
	if ( !IsOpen() )
	{
		Open();
	}
	else
	{
		Requery();
	}

	if (!IsEOF())
	{
		// move through the set to update the recordcount
		while (!IsEOF())
		{
			MoveNext();
		}
		// there should only be 1 Name/Value pair for a given Name, ID combo
		// global settings have UserID = -1
		ASSERT(GetRecordCount() == 1);
		MoveFirst();

		strValue = m_Value;
	}

	return strValue;
}

CString CSetSettings::GetSettings(const CString& strSettingName, char cSeparator/* = ';'*/)
{
	CString strValue = "";

	m_strFilter.Format("Name = '%s'", strSettingName);
    
	if ( !IsOpen() )
	{
		Open();
	}
	else
	{
		Requery();
	}

	CString strTemp = "";
	while (!IsEOF())
	{
		if (strValue.GetLength() > 0)
		{
			strTemp.Format("%c%s", cSeparator, m_Value);
		}
		else
		{
			strTemp = m_Value;
		}
		strValue += strTemp;
		MoveNext();
	}

	return strValue;
}

bool CSetSettings::SetSetting(const CString& strSettingName, const CString& strValue, int iUserID /* -1 */)
{
	m_strFilter.Format("Name = '%s' AND UserID = %d", strSettingName, iUserID);
    
	if ( !IsOpen() )
	{
		Open();
	}
	else
	{
		Requery();
	}
	
	if (!IsEOF())
	{
		Edit() ;
	}
	else
	{
		AddNew() ;
		this->m_Name = strSettingName ;
		this->m_UserID = iUserID ;
	}
	this->m_Value = strValue ;
	return (Update() == TRUE);
}

bool CSetSettings::SetSetting(const CString& strSettingName, long lValue, int iUserID /* = -1 */)
{
	CString strValue ;
	strValue.Format("%d", lValue) ;
	return SetSetting(strSettingName, strValue, iUserID) ;
}

