/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "JRSVersions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CJRSVersion::CJRSVersion()
{
	ClearInfo();
} 

CJRSVersion::CJRSVersion(bool bRetrieveInfo)
{
	if (true == bRetrieveInfo)
	{
		RetrieveInfo();
	}
	else
	{
		ClearInfo();
	}
}

CJRSVersion::~CJRSVersion()
{
}

void CJRSVersion::ClearInfo()
{
	m_bRetrievedInfo = false;
	m_suInfo.csAppName = _T("Unknown");
	m_suInfo.csProductName = _T("Unknown");
	m_suInfo.csProductVersion = _T("Unknown");
	m_suInfo.csProductBuild = _T("Unknown");
	m_suInfo.csAboutText = _T("Unknown Application");
	m_suInfo.csCompleteVersionInfo = _T("Unknown") ;
	m_suInfo.bIsBeta = false;
	m_suInfo.bIsDebug = false;
}

void CJRSVersion::DisplayBetaMessage() const
{
	CString csMessage;

	if ((true == m_bRetrievedInfo) && (true == m_suInfo.bIsBeta))
	{
		csMessage = _T("This is a beta version of ");
		csMessage += m_suInfo.csProductName;
		csMessage += _T(".\n");
		csMessage += _T("Please report any errors or suggestions to JRS Technology, Inc.");
		::MessageBox(NULL,csMessage,"Warning",MB_OK | MB_ICONINFORMATION);
	}
}

void CJRSVersion::DisplayDebugMessage() const
{
	CString csMessage;

	if ((true == m_bRetrievedInfo) && (true == m_suInfo.bIsDebug))
	{
		csMessage = _T("This is a debug version of ");
		csMessage += m_suInfo.csProductName;
		csMessage += _T(".");
		::MessageBox(NULL,csMessage,"Warning",MB_OK | MB_ICONINFORMATION);
	}
}

void CJRSVersion::RetrieveInfo ()
{
	DWORD		dwVerInfoSize;
	DWORD		dwDummyVar;
	DWORD		dwNameLength;
	LPVOID	lpVerInfoData;
	BOOL		bSuccess = FALSE;
	UINT		uDataLength;
	LPSTR		lpszProductVersion;
	LPSTR		lpszProductName;
	LPSTR		lpszCopyright;
	CString	csMessage;
	unsigned short	usHiWord;
	unsigned short	usLoWord;
	VS_FIXEDFILEINFO  *vData ;

	ClearInfo();
	// Get the module name with path
	dwNameLength = ::GetModuleFileName(AfxGetInstanceHandle(),
		m_suInfo.csAppName.GetBufferSetLength(_MAX_PATH),
		_MAX_PATH);
	// Find out how big the version information is
	dwVerInfoSize = ::GetFileVersionInfoSize(m_suInfo.csAppName.GetBuffer(0),
		&dwDummyVar);
	if (dwVerInfoSize > 0)
	{
		lpVerInfoData = new char[dwVerInfoSize];
		if (lpVerInfoData)
		{
			// Get the version info from the resource
			bSuccess = ::GetFileVersionInfo(m_suInfo.csAppName.GetBuffer(0),
				dwDummyVar, dwVerInfoSize, lpVerInfoData);
			if (bSuccess)
			{
				// Parse the STRING product name
				bSuccess = VerQueryValue(lpVerInfoData,
					_T("\\StringFileInfo\\040904b0\\ProductName"),
					(void**)&lpszProductName, &uDataLength);
				if (bSuccess)
				{
					m_suInfo.csProductName = lpszProductName;
					m_suInfo.csAboutText = lpszProductName;
					// Parse the STRING version number
					bSuccess = VerQueryValue(lpVerInfoData,
						_T("\\StringFileInfo\\040904b0\\ProductVersion"),
						(void**)&lpszProductVersion, &uDataLength);
					if (bSuccess)
					{
						m_suInfo.csAboutText += " - Version ";
						m_suInfo.csAboutText += lpszProductVersion;
						m_suInfo.csCompleteVersionInfo = lpszProductVersion;
						// Get the STRING copyright info
						bSuccess = VerQueryValue(lpVerInfoData,
							_T("\\StringFileInfo\\040904b0\\LegalCopyright"),
							(void**)&lpszCopyright,&uDataLength);
						if (bSuccess)
						{
							m_suInfo.csCopyright = lpszCopyright;
							// Get the numerical version info
							bSuccess = VerQueryValue(lpVerInfoData, _T("\\"), 
								(LPVOID*)&vData,&uDataLength);
							if (bSuccess)
							{
								// Parse the "debug" and "prerelease" flags
								m_suInfo.bIsDebug = (0 != (vData->dwFileFlags & VS_FF_DEBUG));
								m_suInfo.bIsBeta = (0 != (vData->dwFileFlags & VS_FF_PRERELEASE));
								usHiWord = (unsigned short)((vData->dwProductVersionMS & 0xFFFF0000) >> 16);
								usLoWord = (unsigned short)(vData->dwProductVersionMS & 0x0000FFFF);
								//m_suInfo.csProductVersion.Format("%02X.%02X",usHiWord, usLoWord);
								m_suInfo.csProductVersion.Format("%02d.%02d",usHiWord, usLoWord);
								
								usHiWord = (unsigned short)((vData->dwProductVersionLS & 0xFFFF0000) >> 16);
								usLoWord = (unsigned short)(vData->dwProductVersionLS & 0x0000FFFF);
								m_suInfo.csProductBuild.Format("%05d - %02d",usHiWord, usLoWord);

								//ulBuildNumber = (unsigned long)vData->dwProductVersionLS;
								//m_suInfo.csProductBuild.Format("%04lu",ulBuildNumber);
							}
						}
					}
				}
			}
			delete [] lpVerInfoData;
		}
	}
	m_bRetrievedInfo = (bSuccess == TRUE);
}
