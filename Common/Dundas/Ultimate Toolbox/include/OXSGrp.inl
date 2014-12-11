// ==========================================================================
//                     Template Implementation : COXSmartGrp
// ==========================================================================

// Source file : OXSGrp.inl

// Source : R.Mortelmans
// Creation Date : 	   19th December 1995
// Last Modification : 23rd January 1996
			  
// //////////////////////////////////////////////////////////////////////////

// Data members -------------------------------------------------------------
// protected:
	// CArray<COXGrpItem<T, G_KEY, G_ARG_KEY>*, COXGrpItem<T, G_KEY, G_ARG_KEY>*> m_array;
	// --- Array containing pointers to group items
	//	   The keys in the item will be constructed and deleted when they are added and removed
	
	// CMap<G_KEY, G_ARG_KEY, COXGrpItem<T, G_KEY, G_ARG_KEY>*, COXGrpItem<T, G_KEY, G_ARG_KEY>*> m_map;
	// --- Map from the key (must exist) to the group item
	//     This is the same group items as used by the array
	//     The map does NOT construct or delete the items

// private:
	
// Member functions ---------------------------------------------------------
// public:

// ///////////////////////////////////////////////////////////////////:

template <class T, class G_KEY, class G_ARG_KEY>
Index COXSmartGrp<T, G_KEY, G_ARG_KEY>::Add(COXSPtr<T>& pSObj, Index index /* = Index(G_DEFAULT) */)
	{
	ASSERT_VALID(this);

	Index newIndex;
	if (index == G_DEFAULT)
		index = m_array.GetUpperBound() + 1;
	if (index <= m_array.GetUpperBound())
		{
		if (0 <= index)
			// Insert item at specified position
			// ... 0 <= nIndex <= GetUpperBound()
			{
			m_array.InsertAt(index, new COXGrpItem<T, G_KEY, G_ARG_KEY>(pSObj, index));
			newIndex = index;
			}
		else
			// Invalid index
			// ... nIndex < -1
			{
			TRACE(TEXT("COXSmartGrp::Add : Invalid index (%i) specified, addition failed\n"),
				index);
			newIndex = G_NOT_FOUND;
			}
		}
	else
		{
		if (index == m_array.GetUpperBound() + 1)
			// Add item at tail
			// ... nIndex == GetUpperBound() + 1
			newIndex = m_array.Add(new COXGrpItem<T, G_KEY, G_ARG_KEY>(pSObj, index));
		else
			// Invalid index
			// ... GetUpperBound() + 1 < nIndex
			{
			TRACE(TEXT("COXSmartGrp::Add : Invalid index (%i) specified, addition failed\n"),
				index);
			newIndex = G_NOT_FOUND;
			}
		}

	ASSERT_VALID(this);
	return newIndex;
	}

template <class T, class G_KEY, class G_ARG_KEY>
Index COXSmartGrp<T, G_KEY, G_ARG_KEY>::Add(COXSPtr<T>& pSObj, G_ARG_KEY key, Index index /* = Index(G_DEFAULT) */,
		BOOL bResolveKeyConflict /* = FALSE */)
	{
	ASSERT_VALID(this);

	// First check whether the key does not yet exist
	G_KEY newKey;
	if (Exist(key))
		{
		if (bResolveKeyConflict)
			{
			G_KEY oldKey = key;
			BOOL bNewKey;
			LONG nTryCount = 1;
			// Keep iterating until valid new key is build
			do
				{
				bNewKey = BuildNewKey(nTryCount, (G_ARG_KEY)oldKey, newKey);
				// ... Make sure the oldkey is not just returned as new key
				//     which would cause an infinite loop
				ASSERT(!bNewKey || (newKey != oldKey));
				oldKey = newKey;
				} while (bNewKey && Exist(newKey));
			if (bNewKey)
				key = newKey;
			else
				{
				TRACE(TEXT("COXSmartGrp::Add : An item with the same key already exists, and no new key could be build, addition failed\n"));
				return G_DUPLICATE;
				}
			}
		else
			{
			TRACE(TEXT("COXSmartGrp::Add : An item with the same key already exists, addition failed\n"));
			return G_DUPLICATE;
			}
		}

	ASSERT(!Exist(key));
	Index newIndex;
	newIndex = Add(pSObj, index);
	if (newIndex != G_NOT_FOUND)
		{
		// Add to the map
		// ... Key should not yet exist
		ASSERT(!Exist(key));
		// ... Make sure we are pointing to right object
		ASSERT(m_array[newIndex]->m_pSObj == pSObj);
		// ... with the most up to date info
		ASSERT(m_array[newIndex]->m_possibleArrayIndex == newIndex);
		m_map.SetAt(key, m_array[newIndex]);
		// Mark in array which the key is used
		m_array[newIndex]->m_pKey = new G_KEY(key);
		}

	ASSERT_VALID(this);
	return newIndex;
	}

template <class T, class G_KEY, class G_ARG_KEY>
Index COXSmartGrp<T, G_KEY, G_ARG_KEY>::Add(COXSPtr<COXSmartGrp<T, G_KEY, G_ARG_KEY> >& pSGroup, 
		Index index /* = Index(G_DEFAULT) */, BOOL bResolveKeyConflict /* = TRUE */)
	{
	// All items of the specified group will be added to this group
	Index newIndex = index;
	Index tempIndex;
	LONG nIndex;
	LONG nSize = pSGroup->GetSize();
	for (nIndex = 0; nIndex < nSize; nIndex++)
		{
		if (pSGroup->m_array[nIndex]->m_pKey != NULL)
			{
			tempIndex = newIndex;
			newIndex = Add(pSGroup->m_array[nIndex]->m_pSObj, 
				*pSGroup->m_array[nIndex]->m_pKey, 
				newIndex, bResolveKeyConflict);
			}
		else
			newIndex = Add(pSGroup->m_array[nIndex]->m_pSObj, newIndex);
		if (0 <= newIndex)
			newIndex++;
		else if (newIndex == G_NOT_FOUND)
			{
			TRACE(TEXT("COXSmartGrp::Add : Invalid index specified, aborting group addition\n"));
			// ... This item was not added due an invalid key, abort iteration
			return newIndex;
			}
		else
			{
			ASSERT(newIndex == Index(G_DUPLICATE));
			TRACE(TEXT("COXSmartGrp::Add : Item with specified key already exists, item skipped\n"));
			// ... This item was not added due to duplicate key, keep iterating and try the other items
			newIndex = tempIndex;
			}
		}
	return newIndex - 1;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Replace(Index index, COXSPtr<T>& pSObj)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	// Remove key if one exists
	if (RemoveKey(index))
		{
		// Removed key, thus index must exist
		ASSERT(Exist(index));
		ASSERT(m_array[index]->m_pKey == NULL);
		m_array[index]->m_pSObj = pSObj;
		m_array[index]->m_possibleArrayIndex = index;
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXSmartGrp::Replace : Cannot remove key of index (%i), replace failed\n"), index);
		bSuccess = FALSE;
		}

	return bSuccess;
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Replace(Index index, COXSPtr<T>& pSObj, G_ARG_KEY key)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	if (SetKey(index, key))
		{
		m_array[index]->m_pSObj = pSObj;
		m_array[index]->m_possibleArrayIndex = index;
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXSmartGrp::Replace : Key already exists, replace failed\n"));
		bSuccess = FALSE;
		}

	return bSuccess;
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Replace(G_ARG_KEY key, COXSPtr<T>& pSObj)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	Index index;
	index = Find(key);
	if (index != G_NOT_FOUND)
		{
		m_array[index]->m_pSObj = pSObj;
		m_array[index]->m_possibleArrayIndex = index;
		// Leave key as is
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXSmartGrp::Replace : Key not found, replace failed\n"));
		bSuccess = FALSE;
		}

	return bSuccess;
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXSPtr<T> COXSmartGrp<T, G_KEY, G_ARG_KEY>::Get(Index index) const
	{
	ASSERT_VALID(this);

	if (Exist(index))
		return m_array[index]->m_pSObj;
	else
		{
		// When a non-existing index is used, return a smart NULL pointer and 
		// do NOT add it to the array (a call to m_array[nIndex] would create one automatically)
		TRACE(TEXT("COXSmartGrp::Get : Index (%i) not found, returning smart NULL pointer\n"), index);
		return COXSPtr<T>(NULL);
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
COXSPtr<T> COXSmartGrp<T, G_KEY, G_ARG_KEY>::Get(G_ARG_KEY key) const
	{
	ASSERT_VALID(this);

	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	if (m_map.Lookup(key, pGroupItem))
		{
		ASSERT(pGroupItem != NULL);
		return pGroupItem->m_pSObj;
		}
	else
		{
		// When a non-existing key is used, return a smart NULL pointer and 
		// do NOT add it to the map (a call to m_map[key] would create one automatically)
		TRACE(TEXT("COXSmartGrp::Get : Key not found, returning smart NULL pointer\n"));
		ASSERT(pGroupItem == NULL);
		return COXSPtr<T>(NULL);
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
COXGrpCursor<T, G_KEY, G_ARG_KEY> COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator[](Index index)
	{
	Index newIndex;
	if (Exist(index))
		{
		// First adjust possible array index to the correct value
		m_array[index]->m_possibleArrayIndex = index;
		newIndex = index;
		}
	else
		{
		// Try to make a new item now
		newIndex = Add(COXSPtr<T>(NULL), index);
		if (newIndex == G_NOT_FOUND)
			{
			TRACE(TEXT("COXSmartGrp::operator[] : ")
				TEXT("Trying to reference a nonexisting index and ")
				TEXT("new addition failed (index = %i),\n\t")
				TEXT("throwing memory exception\n"), index);
			ASSERT(FALSE);
			AfxThrowMemoryException();
			}
		}
	ASSERT(Exist(newIndex));
	return COXGrpCursor<T, G_KEY, G_ARG_KEY>(this, m_array[newIndex], FALSE);
	}

template <class T, class G_KEY, class G_ARG_KEY>
COXGrpCursor<T, G_KEY, G_ARG_KEY> COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator[](G_ARG_KEY key)
	{
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	if (m_map.Lookup(key, pGroupItem))
		return COXGrpCursor<T, G_KEY, G_ARG_KEY>(this, pGroupItem, TRUE);
	else
		{
		// Try to make a new item now
		Index newIndex;
		newIndex = Add(COXSPtr<T>(NULL), key);
		// Should not fail
		ASSERT(newIndex != G_DUPLICATE);
		return COXGrpCursor<T, G_KEY, G_ARG_KEY>(this, m_array[newIndex], TRUE);
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Swap(Index index1, Index index2)
	{
	if (!Exist(index1) || !Exist(index2))
		{
		TRACE(TEXT("COXSmartGrp::Swap : Invalid index (%i or %i) specified\n"),
				index1, index2);
		return FALSE;
		}

	if (index1 == index2)
		// Item does not really moves : nothing to do
		return TRUE;

	// Swap the group item pointers
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pTempGroupItem;
	pTempGroupItem = m_array[index1];
	m_array[index1] = m_array[index2];
	m_array[index2] = pTempGroupItem;

	// Adjust the possible array index
	m_array[index1]->m_possibleArrayIndex = index1;
	m_array[index2]->m_possibleArrayIndex = index2;

	return TRUE;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Swap(G_ARG_KEY key1, G_ARG_KEY key2)
	{
	ASSERT_VALID(this);
	BOOL bSuccess = FALSE;

	Index index1 = Find(key1);
	Index index2 = Find(key2);
	if ((index1 != G_NOT_FOUND) && (index2 != G_NOT_FOUND))
		bSuccess = Swap(index1, index2);
	else
		{
		TRACE(TEXT("COXSmartGrp::Swap : Key(s) not found\n"));
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Move(Index index, LONG nOffset)
	{
	if (!Exist(index))
		{
		TRACE(TEXT("COXSmartGrp::Move : Invalid index (%i) specified\n"),
				index);
		return FALSE;
		}

	Index newIndex = index + nOffset;
	if (newIndex < 0)
		newIndex = 0;
	if (m_array.GetUpperBound() < newIndex)
		newIndex = m_array.GetUpperBound();

	if (index == newIndex)
		// Item does not really moves : nothing to do
		return TRUE;

	// Remove the item and insert it at another position
#ifdef _DEBUG
	LONG nSizeBeforeMove = GetSize();
#endif
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	pGroupItem = m_array.GetAt(index);
	m_array.RemoveAt(index);
	m_array.InsertAt(newIndex, pGroupItem);
	// ... Size before and after move must be the same
	ASSERT(nSizeBeforeMove == GetSize());

	// Adjust the possible index to the correct one
	// Notice that all items between index and newIndex will have an incorrect 
	//  possible index.  This will be resolved during a Find() call
	pGroupItem->m_possibleArrayIndex = newIndex;

	return TRUE;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Move(G_ARG_KEY key, LONG nOffset)
	{
	ASSERT_VALID(this);
	BOOL bSuccess = FALSE;

	Index nndex = Find(key);
	if (nndex != G_NOT_FOUND)
		bSuccess = Move(nndex, nOffset);
	else
		{
		TRACE(TEXT("COXSmartGrp::Move : Key not found\n"));
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY>
Index COXSmartGrp<T, G_KEY, G_ARG_KEY>::Find(G_ARG_KEY key) const
	{
	// In the map is the key associated with the group items
	// This contains a possible array index.
	// We first try this one, 
	//  when it not correct we iterate all array elements until we find it
	ASSERT_VALID(this);

	Index foundIndex = G_NOT_FOUND;

	// Get the group item belonging to the key
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	if (!m_map.Lookup(key, pGroupItem))
		{
		TRACE(TEXT("COXSmartGrp::Find : Key not found\n"));
		return G_NOT_FOUND;
		}

	// First check whether the possible array index is correct
	// This means the the item in the array on the proposed index
	//  must point to the same smart object as the key in the map
	if (Exist(pGroupItem->m_possibleArrayIndex) &&
	    (pGroupItem->m_pSObj == m_array[pGroupItem->m_possibleArrayIndex]->m_pSObj) )
		{
		foundIndex = pGroupItem->m_possibleArrayIndex;
		return foundIndex;
		}

	// If the possible array index is incorrect, iterate the map
	ASSERT(foundIndex == G_NOT_FOUND);
	Index index = 0;
	while ((index <= m_array.GetUpperBound()) && (foundIndex == G_NOT_FOUND))
		{
		if (m_array[index]->m_pSObj == pGroupItem->m_pSObj)
			foundIndex = index;
		index++;
		}

	// The key is part of the map, so it should be in the array as well
	ASSERT(foundIndex != G_NOT_FOUND);		
	// ... Store this correct array index for later use
	m_array[foundIndex]->m_possibleArrayIndex = foundIndex;

	return foundIndex;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Remove(Index index)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	if ((0 <= index) && (index <= m_array.GetUpperBound()))
		{
		// First remove from map
		if (m_array[index]->m_pKey != NULL)
			VERIFY(m_map.RemoveKey(*m_array[index]->m_pKey));
		// Then remove from array
		delete m_array.GetAt(index);
		m_array.RemoveAt(index);
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXSmartGrp::Remove : Index (%i) not found\n"), index);
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXSmartGrp<T, G_KEY, G_ARG_KEY>& COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator-=(Index index)
	{
	if (!Remove(index))
		TRACE(TEXT("COXSmartGrp::operator-= : Could not remove\n"));
	return *this;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Remove(G_ARG_KEY key)
	{
	ASSERT_VALID(this);
	BOOL bSuccess = FALSE;

	Index index = Find(key);
	if (index != G_NOT_FOUND)
		bSuccess = Remove(index);
	else
		{
		TRACE(TEXT("COXSmartGrp::Remove : Key not found\n"));
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXSmartGrp<T, G_KEY, G_ARG_KEY>& COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator-=(G_ARG_KEY key)
	{
	if (!Remove(key))
		TRACE(TEXT("COXSmartGrp::operator-= : Could not remove\n"));
	return *this;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Exist(G_ARG_KEY key) const
	{
	ASSERT_VALID(this);
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	return m_map.Lookup(key, pGroupItem);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator>=(Index index) const
	{
	return Exist(index);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::Exist(Index index) const
	{
	ASSERT_VALID(this);
	return (0 <= index) && (index < m_array.GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator>=(G_ARG_KEY key) const
	{
	return Exist(key);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator>(Index index) const
	{
	return Exist(index) && (1 < GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator>(G_ARG_KEY key) const
	{
	return Exist(key) && (1 < GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator==(Index index) const
	{
	return Exist(index) && (GetSize() == 1);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::operator==(G_ARG_KEY key) const
	{
	return Exist(key) && (GetSize() == 1);
	}


template <class T, class G_KEY, class G_ARG_KEY> inline
LONG COXSmartGrp<T, G_KEY, G_ARG_KEY>::GetSize() const
	{
	ASSERT_VALID(this);
	return m_array.GetSize();
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
LONG COXSmartGrp<T, G_KEY, G_ARG_KEY>::GetKeyCount() const
	{
	ASSERT_VALID(this);
	return m_map.GetCount();
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::IsEmpty() const
	{
	ASSERT_VALID(this);
	return m_array.GetSize() == 0;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
void COXSmartGrp<T, G_KEY, G_ARG_KEY>::Empty()
	{
	// All the group items should be deleted by the array, do it now
	LONG nIndex;
	for (nIndex = 0; nIndex <= m_array.GetUpperBound(); nIndex++)
		delete m_array[nIndex];
	m_array.RemoveAll();
	m_map.RemoveAll();
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::GetKey(Index index, G_KEY& key) const
	{
	ASSERT_VALID(this);

	BOOL bFound = FALSE;
	if (Exist(index) && m_array[index]->m_pKey != NULL)
		{
		key = *m_array[index]->m_pKey;
		bFound = TRUE;
		}
	else
		{
		TRACE(TEXT("COXSmartGrp::GetKey : Index (%i) not found or item without key\n"), index);
		bFound = FALSE;
		}
	return bFound;
	}
	
template <class T, class G_KEY, class G_ARG_KEY> 
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::SetKey(Index index, G_ARG_KEY key, BOOL bResolveKeyConflict /* = FALSE */)
	{
	ASSERT_VALID(this);
	if (!Exist(index))
		{
		TRACE(TEXT("COXSmartGrp::SetKey : Index (%i) not found\n"), index);
		return FALSE;
		}
	if ((m_array[index]->m_pKey != NULL) && (*m_array[index]->m_pKey == key))
		// Old key is the same as the new : nothing to do
		return TRUE;

	G_KEY newKey;
	if (Exist(key))
		{
		if (bResolveKeyConflict)
			{
			G_KEY oldKey = key;
			BOOL bNewKey;
			LONG nTryCount = 1;
			// Keep iterating until valid new key is build
			do
				{
				bNewKey = BuildNewKey(nTryCount, (G_ARG_KEY)oldKey, newKey);
				// ... Make sure the oldkey is not just returned as new key
				//     which would cause an infinite loop
				ASSERT(!bNewKey || (newKey != oldKey));
				oldKey = newKey;
				} while (bNewKey && Exist(newKey));
			if (bNewKey)
				key = newKey;
			else
				{
				TRACE(TEXT("COXSmartGrp::SetKey : An item with the same key already exists, and no new key could be build, function failed\n"));
				return G_DUPLICATE;
				}
			}
		else
			{
			// Existing key must belong to another item
			ASSERT(Find(key) != index);
			TRACE(TEXT("COXSmartGrp::SetKey : Key already exists, function failed\n"));
			return FALSE;
			}
		}

	ASSERT(!Exist(key));
	if(m_array[index]->m_pKey != NULL)
		{
		m_map.RemoveKey(*m_array[index]->m_pKey);
		// ... Delete previous key (may be NULL)
		delete m_array[index]->m_pKey;
		m_array[index]->m_pKey = NULL;
		}

	// ... Construct new key
	m_array[index]->m_pKey = new G_KEY(key);
	m_array[index]->m_possibleArrayIndex = index;
	m_map.SetAt(key, m_array[index]);

	ASSERT_VALID(this);
	return TRUE;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXSmartGrp<T, G_KEY, G_ARG_KEY>::RemoveKey(Index index)
	{
	ASSERT_VALID(this);

	BOOL bFound = FALSE;
	if (Exist(index))
		{
		if (m_array[index]->m_pKey != NULL)
			{
			m_map.RemoveKey(*m_array[index]->m_pKey);
			delete m_array[index]->m_pKey;
			m_array[index]->m_pKey = NULL;
			}
		bFound = TRUE;
		}
	else
		{
		TRACE(TEXT("COXSmartGrp::RemoveKey : Key not found\n"));
		bFound = FALSE;
		}

	ASSERT_VALID(this);
	return bFound;
	}

#ifndef DISABLE_SMART_SERIALIZATION
template <class T, class G_KEY, class G_ARG_KEY>
void COXSmartGrp<T, G_KEY, G_ARG_KEY>::Serialize(CArchive& ar)
	{
	// First call base class
	CObject::Serialize(ar);

	// Then serialize members
	if (ar.IsStoring())
		{
		// ... Write number of members
		ar << (DWORD)GetSize();
		LONG nIndex;
		for (nIndex = 0; nIndex <= m_array.GetUpperBound(); nIndex++)
			{
			if (m_array[nIndex]->m_pKey != NULL)
				{
				// ... Mark that this item uses a key
				ar << (BYTE)TRUE;
				// ... Serialize the key
				ar <<  *m_array[nIndex]->m_pKey;
				}
			else
				// ... Mark that this item does not use a key
				ar << (BYTE)FALSE;
			// ... Serialize the object itself (not the smart pointer!)
			//     Use operator<< instead of Serialize to support polymorphic use
			ar << m_array[nIndex]->m_pSObj;
			}
		}
	else
		{
		DWORD nSize;
		BYTE bHasKey;
		G_KEY key;
		// ... Do not create empty object now
		COXSPtr<T> pSObj = NULL;

		// ... Read number of members
		ar >> nSize;
		DWORD nIndex;
		for (nIndex = 0; nIndex < nSize; nIndex++)
			{
			// ... Check whether this item uses a key
			ar >> bHasKey;
			if (bHasKey)
				// ... Serialize the key
				ar >> key;
			// ... Create smart NULL pointer and let the serialize create it
			pSObj = NULL;
			// ... Use operator<< instead of Serialize to support polymorphic use
			ar >> pSObj;
			if (bHasKey)
				{
				if (Add(pSObj, key) < 0)
					{
					TRACE(TEXT("COXSmartGrp::Serialize : Addition failed, throwing CArchiveException\n"));
					AfxThrowArchiveException(CArchiveException::generic);
					}
				}
			else
				Add(pSObj);
			}
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
CArchive& AFXAPI operator>>(CArchive& ar, COXSmartGrp<T, G_KEY, G_ARG_KEY>*& pSGroup)
	{
	// The operator>> is not supported on COXSmartGrp.
	// You can use Serialize which is fully implemented, 
	//  or use DECLARE_SERIAL in a class derived from this class
	TRACE(_T("operator>> of COXSmartGrp : Function not supported : throwing NotSupportedException\n"));
	AfxThrowNotSupportedException();
	return ar;
	}
#endif // DISABLE_SMART_SERIALIZATION

#ifdef _DEBUG
template <class T, class G_KEY, class G_ARG_KEY>
void COXSmartGrp<T, G_KEY, G_ARG_KEY>::AssertValid() const
	{
	CObject::AssertValid();

	// Can never have more keys than items in array,
	//  but items in array without key are allowed
	ASSERT(m_map.GetCount() <= m_array.GetSize());

	// Every item of array with a key must be in map
	LONG nWithoutKey = 0;
	Index index;
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;

	for (index = 0; index <= m_array.GetUpperBound(); index++)
		{
		if (m_array[index]->m_pKey != NULL)
			{
			// ... Array item must be in map to
			ASSERT(m_map.Lookup(*m_array[index]->m_pKey, pGroupItem));
			// ... Array item and map item must contain the same object
			ASSERT(m_array[index] == pGroupItem);
			}
		else
			nWithoutKey++;
		}

	// The number of items in the map + number of items without key 
	// MUST equal the total number of items
	ASSERT(m_map.GetCount() + nWithoutKey == m_array.GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY>
void COXSmartGrp<T, G_KEY, G_ARG_KEY>::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	dc << "with " << GetSize() << " elements";
	dc << "\nm_array : " << (void*) &m_array;
	dc << "\nm_map : " << (void*) &m_map;
	if (dc.GetDepth() > 0)
		{
		for (Index i = 0; i < GetSize(); i++)
			dc << "\n\t[" << (LONG)i << "] = " << (T*)Get(i);
		}

	dc << "\n";
	}
#endif //_DEBUG

template <class T, class G_KEY, class G_ARG_KEY> inline
COXSmartGrp<T, G_KEY, G_ARG_KEY>::~COXSmartGrp()
	{
	ASSERT_VALID(this);
	Empty();
	}

// protected:
template <class T, class G_KEY, class G_ARG_KEY> inline
COXSmartGrp<T, G_KEY, G_ARG_KEY>::COXSmartGrp()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs an object
	:
	m_array(),
	m_map()
	{
	ASSERT_VALID(this);
	}

// private:

// ==========================================================================
