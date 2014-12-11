// ==========================================================================
//                     Class Implementation : COXGroupCursor
// ==========================================================================

// Source file : OXGrpCrsr.cpp

// Source : R.Mortelmans
// Creation Date : 	   19th December 1995
// Last Modification : 19th December 1995
			  
// #include "stdafx.h"
// #include "OXSGroup.h"
// #include "OXGrpCrsr.h"

// //////////////////////////////////////////////////////////////////////////
// Definition of static members

#define new DEBUG_NEW

// Data members -------------------------------------------------------------
// protected:
	// COXSPtr<T> m_pSObj;
	// --- The actual smart pointer belonging to this item
	//	   This may be a smart NULL pointer

	// G_KEY* m_pKey;
	// --- The key used in the map to access the item
	//     This is NULL when no key is used
	//	   This can always be used to get from the array to the map

	// Index m_possibleArrayIndex;
	// --- The last known index in the array of this item
	//     This is a hint that can be tried to get from the map to the array
	//	   It is not garanteed that this is the actual index, if it is not
	//		the entire array should be iterated to get the corresponding index

// private:
	
// Member functions ---------------------------------------------------------
// public:
template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpItem<T, G_KEY, G_ARG_KEY>::COXGrpItem(const COXSPtr<T>& pSObj, 
	Index possibleArrayIndex)
    // --- In  : pSObj
	//			 possibleArrayIndex
	// --- Out : 
	// --- Returns : 
	// --- Effect : Constructor
	//			    The key pointer is accessed directly by the smart group
	:
	m_pSObj(pSObj),
	m_pKey(NULL),
	m_possibleArrayIndex(possibleArrayIndex)
	{
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpItem<T, G_KEY, G_ARG_KEY>::COXGrpItem(const COXGrpItem<T, G_KEY, G_ARG_KEY>& grpItem)
    // --- In  : grpItem
	// --- Out : 
	// --- Returns : 
	// --- Effect : Copy constructor
	:
	m_pSObj(grpItem.m_pSObj),
	m_pKey(NULL),
	m_possibleArrayIndex(grpItem.m_possibleArrayIndex)
	{
	if (grpItem.m_pKey != NULL)
		m_pKey = new G_KEY(*grpItem.m_pKey);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpItem<T, G_KEY, G_ARG_KEY>::~COXGrpItem()
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Destructs object and corresponding key
	{
	// ... Destructor of m_pSObj will release object
	// ... Delete key (may be NULL)
	delete m_pKey;
	}


// private:

#undef new 
// ==========================================================================
