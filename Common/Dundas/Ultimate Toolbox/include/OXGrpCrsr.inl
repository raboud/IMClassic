// ==========================================================================
//                     Class Implementation : COXGrpCursor
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
	// COXSmartGrp<T, G_KEY, G_ARG_KEY>* m_pSmartGroup;
	// --- The smart group this cursor belongs to

	// COXGrpItem<T, G_KEY, G_ARG_KEY>* m_pGroupItem;
	// --- The specific group item this cursor points to

	// BOOL m_bAddressedByKey;
	// --- Whether the item this cursor point to was addressed by key (TRUE)
	//	   or by index (FALSE)
// private:
	
// Member functions ---------------------------------------------------------
// public:
template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpCursor<T, G_KEY, G_ARG_KEY>::COXGrpCursor(const COXGrpCursor<T, G_KEY, G_ARG_KEY>& groupCursor)
	:
	m_pSmartGroup(groupCursor.m_pSmartGroup),
	m_pGroupItem(groupCursor.m_pGroupItem),
	m_bAddressedByKey(groupCursor.m_bAddressedByKey)
	{
	ASSERT(m_pSmartGroup != NULL);
	ASSERT(m_pGroupItem != NULL);
	ASSERT(!m_bAddressedByKey || (m_pGroupItem->m_pKey != NULL));
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
const COXSPtr<T>& COXGrpCursor<T, G_KEY, G_ARG_KEY>::operator->()
	{
	ASSERT(m_pSmartGroup != NULL);
	ASSERT(m_pGroupItem != NULL);
#ifdef _DEBUG
	if (m_pGroupItem->m_pSObj == NULL)
		{
		TRACE(TEXT("COXGrpCursor::operator-> : Using a not yet assigned group item, supplying a smart NULL pointer\n"));
		// Do not throw exception here, will be thrown if m_pSObj itself is dereferenced
		}
#endif // _DEBUG
	return m_pGroupItem->m_pSObj;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
T& COXGrpCursor<T, G_KEY, G_ARG_KEY>::operator*() const
	{ 
	ASSERT(m_pSmartGroup != NULL);
	ASSERT(m_pGroupItem != NULL);
#ifdef _DEBUG
	if (m_pGroupItem->m_pSObj == NULL)
		{
		TRACE(TEXT("COXGrpCursor::operator* : Using a not yet assigned group item, supplying a smart NULL pointer\n"));
		// Do not throw exception here, will be thrown if m_pSObj itself is dereferenced
		}
#endif // _DEBUG
	return *m_pGroupItem->m_pSObj;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpCursor<T, G_KEY, G_ARG_KEY>& COXGrpCursor<T, G_KEY, G_ARG_KEY>::operator=(COXSPtr<T> pSObj)
	{
	ASSERT(m_pSmartGroup != NULL);
	ASSERT(m_pGroupItem != NULL);
	if (m_bAddressedByKey)
		{
		ASSERT(m_pGroupItem->m_pKey != NULL);
		VERIFY(m_pSmartGroup->Replace(*m_pGroupItem->m_pKey, pSObj));
		}
	else
		VERIFY(m_pSmartGroup->Replace(m_pGroupItem->m_possibleArrayIndex, pSObj));
	return *this;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpCursor<T, G_KEY, G_ARG_KEY>::~COXGrpCursor()
	{
	}

// protected:
template <class T, class G_KEY, class G_ARG_KEY> inline
COXGrpCursor<T, G_KEY, G_ARG_KEY>::COXGrpCursor(COXSmartGrp<T, G_KEY, G_ARG_KEY>* pSmartGroup, 
		COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem, BOOL bAddressedByKey)
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs a group cursor object
	:
	m_pSmartGroup(pSmartGroup),
	m_pGroupItem(pGroupItem),
	m_bAddressedByKey(bAddressedByKey)
	{
	ASSERT(m_pSmartGroup != NULL);
	ASSERT(m_pGroupItem != NULL);
	ASSERT(!m_bAddressedByKey || (m_pGroupItem->m_pKey != NULL));
	}

// private:

#undef new 
// ==========================================================================
