/*----------------------------------------------------------------------------
	Copyright 1997, 1998
	Georgia Tech Research Corporation
	225 North Avenue
	Atlanta, Georgia 30332

	This material may be reproduced by or for the 
	U.S. Government pursuant to the copyright license
	under DAR clause 252.227-7013 (OCT 1988).
----------------------------------------------------------------------------*/


#if !defined(_CLREGISTRYSECTION_H)
#define _CLREGISTRYSECTION_H

#include <afx.h>
#include <winreg.h>

/*----------------------------------------------------------{GTDocStart}
Class:
	ClRegistrySection

Description:
	Registry Class

Exceptions:
	This class encapsulates a key in the registry section which values
	can be written to and read from in a straight-forward manner.

Public Functions:
	 Constructor/destructor
	ClRegistrySection(HKEY szKey, const CString strSectionName, BOOL bCreate = TRUE);
	ClRegistrySection(const ClRegistrySection& clRegistrySection);
	~ClRegistrySection();

	 assignment operator
	virtual ClRegistrySection& operator=(const ClRegistrySection& clSource);

	 Gets whether or not the registry key already existed.
	bool CreatedKey() const;

	 return the HKEY member associated with this object
	HKEY GetKey() const;

	 This assigns a binary value to a value specified by lpszValueName.
	LONG WriteRegistryBinary(const CString strValueName, const void* pvData, 
		DWORD dwSize);

	 This assigns an integer to a value specified by lpszValueName.
	LONG WriteRegistryInt(const CString strValueName, DWORD dwValue);

	 This assigns a string to a value specified by lpszValueName.
	LONG WriteRegistryString(const CString strValueName, const CString strValue);

	 This reads the binary value stored in lpszValueName
	DWORD ReadRegistryBinary(LPCTSTR lpszValueName, void* pvData, DWORD dwSize);

	 This returns the integer stored in lpszValueName
	DWORD ReadRegistryInt(const CString strValueName, DWORD dwDefault = 0);

	 This returns the string stored in lpszValueName
	CString ReadRegistryString(const CString strValueName, const CString strDefault);

	 This deletes the value denoted by lpszValueName
	LONG DeleteRegistryValue( const CString strValueName );

	 This writes a window position to the registry
	LONG WriteWindowPlacement( const CString strValueName, WINDOWPLACEMENT wp );

	 Thbis reads a window position from the registry
	LONG ReadWindowPlacement( const CString strValueName, WINDOWPLACEMENT& wp );

	 This deletes the given key and all of its sub-keys
	LONG RecurseDeleteKey( const CString strKey );

Public Data:
	None

Private Functions:
	None

Private Data:
	 holds whether the key already existed or was created
	DWORD m_dwDisposition;

	 holds the "root key" and "path" in the registry
	HKEY m_hKey;
{GTDocStop}-----------------------------------------------------------*/

class ClRegistrySection
{
public:
	// Constructor/destructor
	ClRegistrySection(HKEY szKey, const CString strSectionName, REGSAM rgMask, BOOL bCreate = TRUE);
	ClRegistrySection(const ClRegistrySection& clRegistrySection);
	~ClRegistrySection();

	LONG m_lError;

	// assignment operator
	virtual ClRegistrySection& operator=(const ClRegistrySection& clSource);

	// Gets whether or not the registry key already existed.
	bool CreatedKey() const;

	// return the HKEY member associated with this object
	HKEY GetKey() const;

	CString GetLastError();

	// This assigns a binary value to a value specified by lpszValueName.
	LONG WriteRegistryBinary(const CString strValueName, const void* pvData, 
		DWORD dwSize);

	// This assigns an integer to a value specified by lpszValueName.
	LONG WriteRegistryInt(const CString strValueName, DWORD dwValue);

	// This assigns a string to a value specified by lpszValueName.
	LONG WriteRegistryString(const CString strValueName, const CString strValue);

	// This reads the binary value stored in lpszValueName
	DWORD ReadRegistryBinary(const CString strValueName, void* pvData, DWORD dwSize);

	// This returns the integer stored in lpszValueName
	DWORD ReadRegistryInt(const CString strValueName, DWORD dwDefault = 0);

	// This returns the string stored in lpszValueName
	CString ReadRegistryString(const CString strValueName, const CString strDefault);

	// This deletes the value denoted by lpszValueName
	LONG DeleteRegistryValue( const CString strValueName );

	// This writes a window position to the registry
	LONG WriteWindowPlacement( const CString strValueName, WINDOWPLACEMENT wp );

	// Thbis reads a window position from the registry
	LONG ReadWindowPlacement( const CString strValueName, WINDOWPLACEMENT& wp );

	// This deletes the given key and all of its sub-keys
	LONG RecurseDeleteKey( const CString strKey );
	bool m_bError;

protected:
	// holds the "root key" and "path" in the registry
	HKEY m_hKey;
	
	// This holds whether the key already existed or was created
	DWORD m_dwDisposition;
	
}; // of class ClRegistrySection

// this returns true if the registry key was created, and false otherwise 
//  (i.e. - it already existed)
inline bool ClRegistrySection::CreatedKey() const
{
	return (m_dwDisposition == REG_CREATED_NEW_KEY);
}

// return the HKEY member associated with this object
inline HKEY ClRegistrySection::GetKey() const
{
	return m_hKey;
}

inline CString ClRegistrySection::GetLastError()
{
	LPVOID lpMsgBuf;
	CString strMessage = "";

	int iNumChars = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, m_lError, 0, (LPTSTR) &lpMsgBuf, 0, NULL);
	if (iNumChars > 0)
	{
		strMessage = CString((LPCTSTR) lpMsgBuf);
		LocalFree( lpMsgBuf );
	}
	else
	{
		strMessage = "Could not get the last error - there was a problem allocating memory.";
	}

	m_bError = false;
	return strMessage;
}

#endif // !defined(_CLREGISTRYSECTION_H)
