/*----------------------------------------------------------------------------

	Copyright 1997, 1998
	Georgia Tech Research Corporation
	225 North Avenue
	Atlanta, Georgia 30332

	This material may be reproduced by or for the 
	U.S. Government pursuant to the copyright license
	under DAR clause 252.227-7013 (OCT 1988).

----------------------------------------------------------------------------*/

#include "RegistrySection.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	ClRegistrySection(HKEY szKey, const CString strSectionName, BOOL bCreate = TRUE)

Description:
	Constructs a RegistrySection object

Arguments:
	HKEY szKey - the key name
	LPTSTR lpszSectionName - the section name

Return Value:
	None

Modified:
	Member variables initialized

Exceptions:
	None

PDL:
 	ClRegistrySection::ClRegistrySection(HKEY szKey, const CString strSectionName, 
												BOOL bCreate = TRUE)
 	{
 		try to open the registry key; if it doesn't exist, create it
 		copy the section name to the path member variable
 	}
{GTDocStop}------------------------------------------------------------*/

ClRegistrySection::ClRegistrySection(HKEY szKey, const CString strSectionName, 
									 REGSAM rgMask, BOOL bCreate /*=TRUE*/)
{
	m_bError = false;
	if ( bCreate )
	{
		// try to open the registry key; if it doesn't exist, create it
		m_lError = ::RegCreateKeyEx(szKey, strSectionName, NULL, REG_NONE, 
			0, rgMask, NULL, 
			&m_hKey, &m_dwDisposition);
		m_bError = (m_lError != ERROR_SUCCESS);
	}
	else
	{
		m_lError = ::RegOpenKeyEx(szKey, strSectionName, 0, 
			rgMask, &m_hKey);
		m_bError = (m_lError != ERROR_SUCCESS);
	}
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	ClRegistrySection(const ClRegistrySection& clRegistrySection)

Description:
	Copy constructor

Arguments:
	ClRegistrySection& clRegistrySection - the ClRegistrySection to copy

Return Value:
	None

Modified:
	Member variables initialized

Exceptions:
	None

PDL:
 	ClRegistrySection::ClRegistrySection(const ClRegistrySection& clRegistrySection)
 	{
		Use assignment operator to copy the passed in object to the 
		new object
 	}
{GTDocStop}------------------------------------------------------------*/

ClRegistrySection::ClRegistrySection(const ClRegistrySection& clRegistrySection)
{
	*this = clRegistrySection;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	~ClRegistrySection()

Description:
	Object destructor. This function closes the HKEY when the object
	is destroyed.

Arguments:
	None

Return Value:
	None

Modified:
	None

Exceptions:
	None

PDL:
 	ClRegistrySection::~ClRegistrySection()
 	{
 		close the registry key
 	}
{GTDocStop}------------------------------------------------------------*/

ClRegistrySection::~ClRegistrySection()
{
	// close the registry key
	::RegCloseKey(m_hKey);
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	operator=(const ClRegistrySection& clSource)

Description:
	assignment operator

Arguments:
	ClRegistrySection& clSource - the ClRegistrySection to copy

Return Value:
	ClRegistrySection& - this ClRegistrySection object

Modified:
	Member variables initialized

Exceptions:
	None

PDL:
 	ClRegistrySection::operator=(const ClRegistrySection& clSource)
 	{
		make sure the object isn't trying to copy itself
		duplicate the handle of the passed in object
		copy remaining member variables
 	}
{GTDocStop}------------------------------------------------------------*/

ClRegistrySection& ClRegistrySection::operator=(const ClRegistrySection& clSource)
{
	
	// make sure the object isn't trying to copy itself
	if (this != &clSource)
	{
		// this const is declared as a place hold for the access parameter 
		// of the new handle.  It is ignored since the argument for the options
		// is DUPLICATE_SAME_ACCESS
		const DWORD dwIGNORED_ACCESS = 0;
		const bool bINHERIT_HANLDE = true;
	
		// obtain a handle for the new object
		DuplicateHandle( GetCurrentProcess(), clSource.m_hKey, GetCurrentProcess(), 
			             (LPHANDLE) &m_hKey, dwIGNORED_ACCESS, bINHERIT_HANLDE, 
						 DUPLICATE_SAME_ACCESS );

		// copy the other member variables
		m_dwDisposition = clSource.m_dwDisposition;
	}

	return *this;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	WriteRegistryBinary(const CString strValueName, const void* pvData, DWORD dwSize)

Description:
	This function assigns binary data to a value specified by lpszValueName.

Arguments:
	strValueName - the value name
	pvData - the address of the data to write
	dwSize - the size, in bytes, of the data to write

Return Value:
	LONG - ERROR_SUCCESS if the function succeeds. If the function fails, the 
			return value is a nonzero error code defined in WINERROR.H. You can 
			use the FormatMessage function with the FORMAT_MESSAGE_FROM_SYSTEM 
			flag to get a generic description of the error.

Modified:
	None

Exceptions:
	None

PDL:
 	ClRegistrySection::WriteRegistryBinary(const CString strValueName, 
											const void* pvData, DWORD dwSize)
 	{
 		write the data to the registry
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::WriteRegistryBinary(const CString strValueName, 
											const void* pvData, DWORD dwSize)
{
	ASSERT(m_hKey != NULL);
	ASSERT(pvData != NULL);

	// write the data to the registry
	LONG lResult = ::RegSetValueEx(m_hKey, strValueName, 0, REG_BINARY, 
									(CONST BYTE*) pvData, dwSize);

	return lResult;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	WriteRegistryInt(const CString strValueName, DWORD dwValue)

Description:
	This function assigns an integer to a value specified by lpszValueName.

Arguments:
	strValueName - the value name
	dwValue - the new value

Return Value:
	LONG - ERROR_SUCCESS if the function succeeds. If the function fails, the 
			return value is a nonzero error code defined in WINERROR.H. You can 
			use the FormatMessage function with the FORMAT_MESSAGE_FROM_SYSTEM 
			flag to get a generic description of the error.

Modified:
	None

Exceptions:
	None

PDL:
 	ClRegistrySection::WriteRegistryInt(const CString strValueName, DWORD dwValue)
 	{
 		write the value to the registry
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::WriteRegistryInt(const CString strValueName, DWORD dwValue)
{
	ASSERT(m_hKey != NULL);

	// write the value to the registry
	LONG lResult = ::RegSetValueEx(m_hKey, strValueName, 0, REG_DWORD, 
									(LPBYTE)&dwValue, sizeof(DWORD) );

	return lResult;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	WriteRegistryString(const CString strValueName, const CString strValue)

Description:
	This function assigns a string to a value specified by lpszValueName.

Arguments:
	strValueName - the value name
	strValue - the new value

Return Value:
	LONG - ERROR_SUCCESS if the function succeeds. If the function fails, the 
			return value is a nonzero error code defined in WINERROR.H. You can 
			use the FormatMessage function with the FORMAT_MESSAGE_FROM_SYSTEM 
			flag to get a generic description of the error.

Modified:
	None

Exceptions:
	None thrown

PDL:
 	LONG ClRegistrySection::WriteRegistryString(LPCTSTR lpszValueName, 
												const CString strValue)
 	{
 		write the value to the registry
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::WriteRegistryString(const CString strValueName, 
											const CString strValue)
{
	ASSERT(m_hKey != NULL);

	// write the value to the registry
	LONG lResult = ::RegSetValueEx(m_hKey, strValueName, 0, REG_SZ, 
					(LPBYTE) ((LPCTSTR) strValue), strValue.GetLength() + 1);

	return lResult;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	ReadRegistryBinary(const CString strValueName, void* pvData, DWORD dwSize)

Description:
	This function reads the binary value stored in lpszValueName and puts 
	it in the buffer pointed to by pvData.  Or returns 0.

Arguments:
	strValueName - the value name
	pvData - the address of the buffer to write the data to
	dwSize - the size of the buffer pointed to by pvData

Return Value:
	DWORD - the amount of data read.  
	Check this value to verify valid data was read.

Modified:
	None

Exceptions:
	None

PDL:
 	ClRegistrySection::ReadRegistryBinary(const CString strValueName, 
											void* pvData, DWORD dwSize)
 	{
 		try to read the data
 		if success, make sure binary data was there
 	}
{GTDocStop}------------------------------------------------------------*/

DWORD ClRegistrySection::ReadRegistryBinary(const CString strValueName, 
											void* pvData, DWORD dwSize)
{
	ASSERT(pvData != NULL);

	if (m_hKey != NULL)
	{

		DWORD dwType;

		// try to read the data
		LONG lResult = ::RegQueryValueEx(m_hKey, strValueName, NULL, &dwType, 
											(LPBYTE) pvData, &dwSize);

		// if success, make sure binary data was there
		if (lResult == ERROR_SUCCESS)
		{
			ASSERT(dwType == REG_BINARY);
		}
		else
		{
			dwSize = 0;
		}
	}
	else
	{
		dwSize = 0;
	}

	return dwSize;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	ReadRegistryInt(const CString strValueName, DWORD iDefault=0)

Description:
	This function returns the integer value stored in lpszValueName.
	If the value cannot be read, a default value is returned.

Arguments:
	strValueName - the value name
	iDefault - the default return value

Return Value:
	DWORD

Modified:
	None

Exceptions:
	None

PDL:
 	ClRegistrySection::ReadRegistryInt(const CString strValueName, DWORD iDefault=0)
 	{
 		try to read the value
 		if success, return the value
 		else, return default
 	}
{GTDocStop}------------------------------------------------------------*/

DWORD ClRegistrySection::ReadRegistryInt(const CString strValueName, 
										 DWORD dwDefault /*=0*/)
{
	DWORD dwReturn = dwDefault;

	if ( m_hKey != NULL )
	{
		DWORD dwType;
		DWORD dwValue;
		DWORD dwCount = sizeof(DWORD);

		// try to read the value
		LONG lResult = ::RegQueryValueEx(m_hKey, strValueName, NULL, &dwType,
											(LPBYTE)&dwValue, &dwCount);

		// if success, return the value
		if (lResult == ERROR_SUCCESS)
		{
			ASSERT(dwType == REG_DWORD);
			ASSERT(dwCount == sizeof(dwValue));
			dwReturn = dwValue;
		}
	}

	return dwReturn;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	ReadRegistryString(const CString strValueName, const CString strDefault)

Description:
	This function returns the string stored in lpszValueName.
	If the value cannot be read, a default value is returned.

Arguments:
	strValueName - the value name
	strDefault - the default return value

Return Value:
	CString

Modified:
	None

Exceptions:
	None

PDL:
 	CString ClRegistrySection::ReadRegistryString(const CString strValueName, 
											  const CString strDefault)
 	{
 		try to get the type and size of the value
 		check for success
 			try to get the string value
 			check for success
 				return the value
 		return the default value
 	}
{GTDocStop}------------------------------------------------------------*/

CString ClRegistrySection::ReadRegistryString(const CString strValueName, 
											  const CString strDefault)
{
	CString strReturn = strDefault;

	if (m_hKey != NULL)
	{
		CString strValue;

		DWORD dwType, dwCount;

		// try to get the type and size of the value
		LONG lResult = ::RegQueryValueEx(m_hKey, strValueName, NULL, &dwType,
										NULL, &dwCount);
										
		// check for success
		if (lResult == ERROR_SUCCESS)
		{
			// try to get the string value
			ASSERT(dwType == REG_SZ);
			lResult = ::RegQueryValueEx(m_hKey, strValueName, NULL, &dwType, 
				(LPBYTE) strValue.GetBuffer( dwCount / sizeof(TCHAR) ), &dwCount);
			strValue.ReleaseBuffer();
			
			// check for success
			if (lResult == ERROR_SUCCESS)
			{
				// return the value
				ASSERT(dwType == REG_SZ);
				strReturn = strValue;
			}
		}
	}
	return strReturn;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	DeleteRegistryValue( const CString strValueName )

Description:
	This function deletes the value denoted by lpszValueName.

Arguments:
	strValueName - the value name

Return Value:
	LONG - If the function succeeds, the return value is ERROR_SUCCESS.
			If the function fails, the return value is a nonzero error 
			code defined in WINERROR.H. You can use the FormatMessage 
			function with the FORMAT_MESSAGE_FROM_SYSTEM flag to get a 
			generic description of the error.

Modified:
	None

Exceptions:
	None

PDL:
 	LONG ClRegistrySection::DeleteRegistryValue( const CString strValueName )
 	{
 		delete the registry key
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::DeleteRegistryValue( const CString strValueName )
{
	return ::RegDeleteValue(m_hKey, strValueName);
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	WriteWindowPlacement( const CString strValueName, WINDOWPLACEMENT wp )

Description:
	This writes a WINDOWPLACEMENT structure to the registry.

Arguments:
	strValueName - the key name the window placement should be stored as
	wp - the placement of a window to write to the registry

Return Value:
	LONG - If the function succeeds, the return value is ERROR_SUCCESS.
			If the function fails, the return value is a nonzero error 
			code defined in WINERROR.H. You can use the FormatMessage 
			function with the FORMAT_MESSAGE_FROM_SYSTEM flag to get a 
			generic description of the error.

Modified:
	None

Exceptions:
	None

PDL:
 	LONG ClRegistrySection::WriteWindowPlacement( const CString strValueName, 
													 WINDOWPLACEMENT wp )
 	{
		write the window placement to the registry
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::WriteWindowPlacement( const CString strValueName, 
											  WINDOWPLACEMENT wp )
{
	LONG lReturn;

	lReturn = ::RegSetValueEx(m_hKey, strValueName, 0, REG_BINARY, 
		                      (LPBYTE) &wp, sizeof( WINDOWPLACEMENT ) );

	return lReturn;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	ReadWindowPlacement( const CString strValueName, WINDOWPLACEMENT& wp )

Description:
	This reads a WINDOWPLACEMENT structure from the registry.

Arguments:
	strValueName - the key name the window placement is stored as
	wp - a reference to where the window placement should be placed after 
		 reading from the registry

Return Value:
	LONG - If the function succeeds, the return value is ERROR_SUCCESS.
			If the function fails, the return value is a nonzero error 
			code defined in WINERROR.H. You can use the FormatMessage 
			function with the FORMAT_MESSAGE_FROM_SYSTEM flag to get a 
			generic description of the error.

Modified:
	None

Exceptions:
	None

PDL:
 	LONG ClRegistrySection::ReadWindowPlacement( const CString strValueName, 
													 WINDOWPLACEMENT& wp )
 	{
		read the window placement from the registry
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::ReadWindowPlacement( const CString strValueName, 
											 WINDOWPLACEMENT& wp )
{
	LONG lReturn = ERROR_INVALID_HANDLE;

	if (m_hKey != NULL)
	{
		
		DWORD dwType;
		DWORD dwBufferSize;

		dwBufferSize = sizeof(WINDOWPLACEMENT);


		lReturn = ::RegQueryValueEx(m_hKey, strValueName, 0, &dwType, 
									(LPBYTE) &wp, &dwBufferSize );
	}

	return lReturn;
}

/*-----------------------------------------------------------{GTDocStart}
Function Name:
	RecurseDeleteKey( const CString strKey )

Description:
	This removes the specified key from the registry and explicitly removes 
	any subkeys.

Arguments:
	strKey - the key name to delete

Return Value:
	LONG - If the function succeeds, the return value is ERROR_SUCCESS.
			If the function fails, the return value is a nonzero error 
			code defined in WINERROR.H. You can use the FormatMessage 
			function with the FORMAT_MESSAGE_FROM_SYSTEM flag to get a 
			generic description of the error.

Modified:
	None

Exceptions:
	None

PDL:
 	LONG ClRegistrySection::RecurseDeleteKey( const CString strKey )
 	{
		delete the key and all subkeys
 	}
{GTDocStop}------------------------------------------------------------*/

LONG ClRegistrySection::RecurseDeleteKey( const CString strKey )
{

	CRegKey clRegKey;

	clRegKey.Attach( m_hKey );

	LONG lReturn = clRegKey.RecurseDeleteKey( strKey );

	clRegKey.Detach();

	return lReturn;
}
