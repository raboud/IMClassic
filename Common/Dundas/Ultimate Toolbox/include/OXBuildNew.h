// ==========================================================================
// 					Function template Specification : BuildNewKey
// ==========================================================================

// Header file : OXBuildNew.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This function template builds a new key starting from an old one
//	The old one already exists and should be resolved into a not yet
//	existing key

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXBUILDNEW_H__
#define __OXBUILDNEW_H__

// New key builder template function
template<class ARG_TYPE, class TYPE>
BOOL BuildNewKey(LONG nTryCount, ARG_TYPE oldKey, TYPE& newKey)
	// --- In  : nTryCount : The number of times a new key was requested for one duplicate
	//			 pOldKey : The old key from which a new one has to be made
	//			 pNewKey : The new key which has to be filled out
	// --- Out : 
	// --- Returns : Whether a new key was generated
	// --- Effect : This generates a new key starting from an old one
	//			    This function may be called several times in succession 
	//				when the new key already exists as well
	{
	// Always fail by default
	return FALSE;
	}

BOOL BuildNewKey(LONG nTryCount, LONG nOldKey, LONG& nNewKey);
BOOL BuildNewKey(LONG nTryCount, LPCTSTR pszOldKey, CString& sNewKey);

#endif // __OXBUILDNEW_H__
// ==========================================================================
