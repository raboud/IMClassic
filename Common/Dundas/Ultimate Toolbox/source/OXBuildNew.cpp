// ==========================================================================
//                 Function template Implementation : BuildNewKey
// ==========================================================================

// Source file : OXBuildNew.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
			  
#include "StdAfx.h"
#include "OXBuildNew.h"

// //////////////////////////////////////////////////////////////////////////
// New key builder template function
BOOL BuildNewKey(LONG /* nTryCount */, LONG nOldKey, LONG& nNewKey)
	{
	nNewKey = nOldKey + 1;
	return TRUE;
	}

BOOL BuildNewKey(LONG /* nTryCount */, LPCTSTR pszOldKey, CString& sNewKey)
	{
	// First get the trailing number if one exists
	LPCTSTR pszNum;
	LPTSTR pszNew;
	LONG nNumber;
	pszNum = pszOldKey + _tcslen(pszOldKey) - 1;

	// Search backwards to find the first non-digit char
	while (pszOldKey <= pszNum && _istdigit(*pszNum))
		pszNum--;
	// ... Point to the first digit (or to zero terminator)
	pszNum++;
	ASSERT(*pszNum == TEXT('\0') || _istdigit(*pszNum));

	// Increase number and build new string
	nNumber = _ttoi(pszNum) + 1;
	pszNew = sNewKey.GetBuffer(_tcslen(pszOldKey) + 20);
	_tcsncpy(pszNew, pszOldKey, pszNum - pszOldKey);
	_itot(nNumber, pszNew + (pszNum - pszOldKey), 10);
	sNewKey.ReleaseBuffer();
	return TRUE;
	}

// ==========================================================================
