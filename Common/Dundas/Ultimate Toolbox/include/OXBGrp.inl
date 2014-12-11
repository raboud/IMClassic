// ==========================================================================
//                     Template Implementation : COXBrilliantGrp
// ==========================================================================

// Source file : OXSGrp.inl

// Source : R.Mortelmans
// Creation Date : 	   19th December 1995
// Last Modification : 23rd January 1996
			  
// //////////////////////////////////////////////////////////////////////////

// Expand the implementation of IMPLEMENT_SCOPY
// here manually, because the template class is interpreted by the macro
// as multiple parameters (because of the comma)
// IMPLEMENT_SCOPY(COXBrilliantGrp<T, G_KEY, G_ARG_KEY>, COXSmartObj)
template <class T, class G_KEY, class G_ARG_KEY>
COXBrilliantObj* COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Clone()
		{ return new COXBrilliantGrp<T, G_KEY, G_ARG_KEY>(*this); }
template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Copy(COXBrilliantGrp<T, G_KEY, G_ARG_KEY>* pSource)
		{ *this = *pSource; }
template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::VirtualCopy(COXBrilliantObj* pSource)
			{ Copy((COXBrilliantGrp<T, G_KEY, G_ARG_KEY>*)pSource); }

// ///////////////////////////////////////////////////////////////////:

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

template <class T, class G_KEY, class G_ARG_KEY>
Index COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Add(COXSPtr<T>& pSObj, Index index /* = Index(G_DEFAULT) */)
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
			SetModified();
			m_array.InsertAt(index, new COXGrpItem<T, G_KEY, G_ARG_KEY>(pSObj, index));
			newIndex = index;
			}
		else
			// Invalid index
			// ... nIndex < -1
			{
			TRACE(TEXT("COXBrilliantGrp::Add : Invalid index (%i) specified, addition failed\n"),
				index);
			newIndex = G_NOT_FOUND;
			}
		}
	else
		{
		if (index == m_array.GetUpperBound() + 1)
			// Add item at tail
			// ... nIndex == GetUpperBound() + 1
			{
			SetModified();
			newIndex = m_array.Add(new COXGrpItem<T, G_KEY, G_ARG_KEY>(pSObj, index));
			}
		else
			// Invalid index
			// ... GetUpperBound() + 1 < nIndex
			{
			TRACE(TEXT("COXBrilliantGrp::Add : Invalid index (%i) specified, addition failed\n"),
				index);
			newIndex = G_NOT_FOUND;
			}
		}

	ASSERT_VALID(this);
	return newIndex;
	}

template <class T, class G_KEY, class G_ARG_KEY>
Index COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Add(COXSPtr<T>& pSObj, G_ARG_KEY key, 
		Index index /* = Index(G_DEFAULT) */, BOOL bResolveKeyConflict /* = FALSE */)
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
				TRACE(TEXT("COXBrilliantGrp::Add : An item with the same key already exists, and no new key could be build, addition failed\n"));
				return G_DUPLICATE;
				}
			}
		else
			{
			TRACE(TEXT("COXBrilliantGrp::Add : An item with the same key already exists, addition failed\n"));
			return G_DUPLICATE;
			}
		}

	ASSERT(!Exist(key));
	Index newIndex;
	// ... Add() may call SetModified()
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
Index COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Add(COXSPtr<COXBrilliantGrp<T, G_KEY, G_ARG_KEY> >& pBGroup, 
		Index index /* = Index(G_DEFAULT) */, BOOL bResolveKeyConflict /* = TRUE */)
	{
	// All items of the specified group will be added to this group
	Index newIndex = index;
	Index tempIndex;
	LONG nIndex;
	LONG nSize = pBGroup->GetSize();
	for (nIndex = 0; nIndex < nSize; nIndex++)
		{
		if (pBGroup->m_array[nIndex]->m_pKey != NULL)
			{
			tempIndex = newIndex;
			newIndex = Add(pBGroup->m_array[nIndex]->m_pSObj, 
				*pBGroup->m_array[nIndex]->m_pKey, 
				newIndex, bResolveKeyConflict);
			}
		else
			newIndex = Add(pBGroup->m_array[nIndex]->m_pSObj, newIndex);
		if (0 <= newIndex)
			newIndex++;
		else if (newIndex == G_NOT_FOUND)
			{
			TRACE(TEXT("COXBrilliantGrp::Add : Invalid index specified, aborting group addition\n"));
			// ... This item was not added due an invalid key, abort iteration
			return newIndex;
			}
		else
			{
			ASSERT(newIndex == Index(G_DUPLICATE));
			TRACE(TEXT("COXBrilliantGrp::Add : Item with specified key already exists, item skipped\n"));
			// ... This item was not added due to duplicate key, keep iterating and try the other items
			newIndex = tempIndex;
			}
		}
	return newIndex - 1;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Replace(Index index, COXSPtr<T>& pSObj)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	// Remove key if one exists
	if (Exist(index))
		{
		SetModified();
		VERIFY(RemoveKey(index));
		ASSERT(m_array[index]->m_pKey == NULL);
		m_array[index]->m_pSObj = pSObj;
		m_array[index]->m_possibleArrayIndex = index;
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXBrilliantGrp::Replace : Cannot remove key of index (%i), replace failed\n"), index);
		bSuccess = FALSE;
		}

	return bSuccess;
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Replace(Index index, COXSPtr<T>& pSObj, G_ARG_KEY key)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	Index keyIndex;
	keyIndex = Find(key);
	if ( (keyIndex == index) || (keyIndex == G_NOT_FOUND) )
		{
		SetModified();
		VERIFY(SetKey(index, key));
		m_array[index]->m_pSObj = pSObj;
		m_array[index]->m_possibleArrayIndex = index;
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXBrilliantGrp::Replace : Key already exists, replace failed\n"));
		bSuccess = FALSE;
		}

	return bSuccess;
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Replace(G_ARG_KEY key, COXSPtr<T>& pSObj)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	Index index;
	index = Find(key);
	if (index != G_NOT_FOUND)
		{
		SetModified();
		m_array[index]->m_pSObj = pSObj;
		m_array[index]->m_possibleArrayIndex = index;
		// Leave key as is
		bSuccess = TRUE;
		}
	else
		{
		TRACE(TEXT("COXBrilliantGrp::Replace : Key not found, replace failed\n"));
		bSuccess = FALSE;
		}

	return bSuccess;
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXSPtr<T> COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Get(Index index) const
	{
	ASSERT_VALID(this);

	if (Exist(index))
		return m_array[index]->m_pSObj;
	else
		{
		// When a non-existing index is used, return a smart NULL pointer and 
		// do NOT add it to the array (a call to m_array[nIndex] would create one automatically)
		TRACE(TEXT("COXBrilliantGrp::Get : Index (%i) not found, returning smart NULL pointer\n"), index);
		return COXSPtr<T>(NULL);
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
COXSPtr<T> COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Get(G_ARG_KEY key) const
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
		TRACE(TEXT("COXBrilliantGrp::Get : Key not found, returning smart NULL pointer\n"));
		ASSERT(pGroupItem == NULL);
		return COXSPtr<T>(NULL);
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
COXGrpCursor<T, G_KEY, G_ARG_KEY> COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator[](Index index)
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
		// ... Add() may call SetModified();
		newIndex = Add(COXSPtr<T>(NULL), index);
		if (newIndex == G_NOT_FOUND)
			{
			TRACE(TEXT("COXBrilliantGrp::operator[] : ")
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
COXGrpCursor<T, G_KEY, G_ARG_KEY> COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator[](G_ARG_KEY key)
	{
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	if (m_map.Lookup(key, pGroupItem))
		return COXGrpCursor<T, G_KEY, G_ARG_KEY>(this, pGroupItem, TRUE);
	else
		{
		// Try to make a new item now
		Index newIndex;
		// ... Add() may call SetModified();
		newIndex = Add(COXSPtr<T>(NULL), key);
		// Should not fail
		ASSERT(newIndex != G_DUPLICATE);
		return COXGrpCursor<T, G_KEY, G_ARG_KEY>(this, m_array[newIndex], TRUE);
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Swap(Index index1, Index index2)
	{
	if (!Exist(index1) || !Exist(index2))
		{
		TRACE(TEXT("COXBrilliantGrp::Swap : Invalid index (%i or %i) specified\n"),
				index1, index2);
		return FALSE;
		}

	if (index1 == index2)
		// Item does not really moves : nothing to do
		return TRUE;

	// Swap the group item pointers
	SetModified();
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
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Swap(G_ARG_KEY key1, G_ARG_KEY key2)
	{
	ASSERT_VALID(this);
	BOOL bSuccess = FALSE;

	Index index1 = Find(key1);
	Index index2 = Find(key2);
	if ((index1 != G_NOT_FOUND) && (index2 != G_NOT_FOUND))
		// ... Swap may call SetModified()
		bSuccess = Swap(index1, index2);
	else
		{
		TRACE(TEXT("COXBrilliantGrp::Swap : Key(s) not found\n"));
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Move(Index index, LONG nOffset)
	{
	if (!Exist(index))
		{
		TRACE(TEXT("COXBrilliantGrp::Move : Invalid index (%i) specified\n"),
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
	SetModified();
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
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Move(G_ARG_KEY key, LONG nOffset)
	{
	ASSERT_VALID(this);
	BOOL bSuccess = FALSE;

	Index nndex = Find(key);
	if (nndex != G_NOT_FOUND)
		// ... Move() may call SetModified()
		bSuccess = Move(nndex, nOffset);
	else
		{
		TRACE(TEXT("COXBrilliantGrp::Move : Key not found\n"));
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY>
Index COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Find(G_ARG_KEY key) const
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
		TRACE(TEXT("COXBrilliantGrp::Find : Key not found\n"));
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
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Remove(Index index)
	{
	ASSERT_VALID(this);

	BOOL bSuccess = FALSE;
	if ((0 <= index) && (index <= m_array.GetUpperBound()))
		{
		SetModified();
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
		TRACE(TEXT("COXBrilliantGrp::Remove : Index (%i) not found\n"), index);
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXBrilliantGrp<T, G_KEY, G_ARG_KEY>& COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator-=(Index index)
	{
	// ... Remove may call SetModified()
	if (!Remove(index))
		TRACE(TEXT("COXBrilliantGrp::operator-= : Could not remove\n"));
	return *this;
	}

template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Remove(G_ARG_KEY key)
	{
	ASSERT_VALID(this);
	BOOL bSuccess = FALSE;

	Index index = Find(key);
	if (index != G_NOT_FOUND)
		// ... Remove may call SetModified()
		bSuccess = Remove(index);
	else
		{
		TRACE(TEXT("COXBrilliantGrp::Remove : Key not found\n"));
		bSuccess = FALSE;
		}

	ASSERT_VALID(this);
	return bSuccess;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXBrilliantGrp<T, G_KEY, G_ARG_KEY>& COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator-=(G_ARG_KEY key)
	{
	// ... Remove() may call SetModified()
	if (!Remove(key))
		TRACE(TEXT("COXBrilliantGrp::operator-= : Could not remove\n"));
	return *this;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Exist(G_ARG_KEY key) const
	{
	ASSERT_VALID(this);
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	return m_map.Lookup(key, pGroupItem);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator>=(Index index) const
	{
	return Exist(index);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Exist(Index index) const
	{
	ASSERT_VALID(this);
	return (0 <= index) && (index < m_array.GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator>=(G_ARG_KEY key) const
	{
	return Exist(key);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator>(Index index) const
	{
	return Exist(index) && (1 < GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator>(G_ARG_KEY key) const
	{
	return Exist(key) && (1 < GetSize());
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator==(Index index) const
	{
	return Exist(index) && (GetSize() == 1);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator==(G_ARG_KEY key) const
	{
	return Exist(key) && (GetSize() == 1);
	}


template <class T, class G_KEY, class G_ARG_KEY> inline
LONG COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::GetSize() const
	{
	ASSERT_VALID(this);
	return m_array.GetSize();
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
LONG COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::GetKeyCount() const
	{
	ASSERT_VALID(this);
	return m_map.GetCount();
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::IsEmpty() const
	{
	ASSERT_VALID(this);
	return m_array.GetSize() == 0;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Empty()
	{
	// All the group items should be deleted by the array, do it now
	if (GetSize() != 0)
		{
		SetModified();

		LONG nIndex;
		for (nIndex = 0; nIndex <= m_array.GetUpperBound(); nIndex++)
			delete m_array[nIndex];
		m_array.RemoveAll();
		m_map.RemoveAll();
		}
	}

template <class T, class G_KEY, class G_ARG_KEY> inline
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::GetKey(Index index, G_KEY& key) const
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
		TRACE(TEXT("COXBrilliantGrp::GetKey : Index (%i) not found or item without key\n"), index);
		bFound = FALSE;
		}
	return bFound;
	}
	
template <class T, class G_KEY, class G_ARG_KEY> 
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::SetKey(Index index, G_ARG_KEY key, BOOL bResolveKeyConflict /* = FALSE */)
	{
	ASSERT_VALID(this);
	if (!Exist(index))
		{
		TRACE(TEXT("COXBrilliantGrp::SetKey : Index (%i) not found\n"), index);
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
				TRACE(TEXT("COXBrilliantGrp::SetKey : An item with the same key already exists, and no new key could be build, function failed\n"));
				return G_DUPLICATE;
				}
			}
		else
			{
			// Existing key must belong to another item
			ASSERT(Find(key) != index);
			TRACE(TEXT("COXBrilliantGrp::SetKey : Key already exists, function failed\n"));
			return FALSE;
			}
		}

	ASSERT(!Exist(key));
	SetModified();
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
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::RemoveKey(Index index)
	{
	ASSERT_VALID(this);

	BOOL bFound = FALSE;
	if (Exist(index))
		{
		if (m_array[index]->m_pKey != NULL)
			{
			SetModified();
			m_map.RemoveKey(*m_array[index]->m_pKey);
			delete m_array[index]->m_pKey;
			m_array[index]->m_pKey = NULL;
			}
		bFound = TRUE;
		}
	else
		{
		TRACE(TEXT("COXBrilliantGrp::RemoveKey : Key not found\n"));
		bFound = FALSE;
		}

	ASSERT_VALID(this);
	return bFound;
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::COXBrilliantGrp(const COXBrilliantGrp<T, G_KEY, G_ARG_KEY>& sGroup)
	{
	ASSERT_VALID(&sGroup);

	this->COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator=(sGroup);
	
	ASSERT_VALID(this);
	}

template <class T, class G_KEY, class G_ARG_KEY> inline 
COXBrilliantGrp<T, G_KEY, G_ARG_KEY>& COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::operator=(const COXBrilliantGrp<T, G_KEY, G_ARG_KEY>& sGroup)
	{
	ASSERT_VALID(this);
	ASSERT_VALID(&sGroup);

	if (&sGroup == this)
		// Assigning to itself : nothing to do
		return *this;

	// First clear the entire group
	// ... Empty() may call Setmodified()
	Empty();

	// Now assign base class members (this will assign the m_bModified flag,
	//  make sure we do not change it during the remainder of this function)
	COXBrilliantObj::operator=(sGroup);

	// Then make copies of all group items ann add them to the
	// array and map
	LONG nIndex;
	COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem = NULL;
	for (nIndex = 0; nIndex <= sGroup.m_array.GetUpperBound(); nIndex++)
		{
		// ... Make copy af group item
		pGroupItem = new COXGrpItem<T, G_KEY, G_ARG_KEY>(*sGroup.m_array[nIndex]);
		// ... Adjust the possible array index to start out correctly
		pGroupItem->m_possibleArrayIndex = nIndex;
		// ... Add to array and map
		VERIFY(m_array.Add(pGroupItem) == nIndex);
		if (pGroupItem->m_pKey != NULL)
			m_map.SetAt(*pGroupItem->m_pKey, pGroupItem);
		}

	ASSERT(GetSize() == sGroup.GetSize());
	ASSERT(GetKeyCount() == sGroup.GetKeyCount());
	ASSERT(IsModified() == sGroup.IsModified());
	ASSERT_VALID(this);
	return *this;
	}

template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::StartTransaction(BOOL bDeferCopy /* = TRUE */)
	{
	// Call base class implementation
	COXBrilliantObj::StartTransaction(bDeferCopy);

	// Start transaction on all elements of the group
	LONG nIndex;
	for (nIndex = 0; nIndex <= m_array.GetUpperBound(); nIndex++)
		m_array[nIndex]->m_pSObj->StartTransaction(bDeferCopy);
	}

template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Commit()
	{
	if (GetTransactionLevel() < 1)
		{
		TRACE(TEXT("COXBrilliantGrp::Commit : No transaction started\n"));
		ASSERT(FALSE);
		return;
		}

	// Commit all elements that were in the group 
	//  at the moment the transaction started
	COXBrilliantGrp<T, G_KEY, G_ARG_KEY>* pPreviousTransactionState;
	pPreviousTransactionState = (COXBrilliantGrp<T, G_KEY, G_ARG_KEY>*)m_transactionStack.Peek();
	if (pPreviousTransactionState == NULL)
		// Group has not changed contents, use this
		pPreviousTransactionState = this;
	LONG nIndex;
	// It is possible that an item was added after the group transaction was started
	// Then the item itself does not have a started transaction
	for (nIndex = 0; nIndex <= pPreviousTransactionState->m_array.GetUpperBound(); nIndex++)
		if (0 < pPreviousTransactionState->m_array[nIndex]->m_pSObj->GetTransactionLevel())
			pPreviousTransactionState->m_array[nIndex]->m_pSObj->Commit();

	// Call base class implementation
	COXBrilliantObj::Commit();
	}

template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Rollback()
	{
	if (GetTransactionLevel() < 1)
		{
		TRACE(TEXT("COXBrilliantGrp::Rollback : No transaction started\n"));
		ASSERT(FALSE);
		return;
		}

	// Rollback all elements that were in the group 
	//  at the moment the transaction started
	COXBrilliantGrp<T, G_KEY, G_ARG_KEY>* pPreviousTransactionState;
	pPreviousTransactionState = (COXBrilliantGrp<T, G_KEY, G_ARG_KEY>*)m_transactionStack.Peek();
	if (pPreviousTransactionState == NULL)
		// Group has not changed contents, use this
		pPreviousTransactionState = this;
	LONG nIndex;
	for (nIndex = 0; nIndex <= pPreviousTransactionState->m_array.GetUpperBound(); nIndex++)
		if (0 < pPreviousTransactionState->m_array[nIndex]->m_pSObj->GetTransactionLevel())
			pPreviousTransactionState->m_array[nIndex]->m_pSObj->Rollback();

	// Call base class implementation
	COXBrilliantObj::Rollback();
	}

template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::SetModified(BOOL bModified /* = TRUE */)
	{
	// First call base class implementation to adjust for this object itself
	COXBrilliantObj::SetModified(bModified);

	// When bModified = FALSE, propagate to all the items of this group
	if (!bModified)
		{
		Index index;
		for (index = 0; index < GetSize(); index++)
			{
			Get(index)->SetModified(FALSE);
			}
		}
	}


template <class T, class G_KEY, class G_ARG_KEY>
BOOL COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::IsModified() const
	{
	// First check whether this object itself has been modified
	BOOL bModified = COXBrilliantObj::IsModified();

	// Then check the items of this group
	Index index = 0;
	while (!bModified && index < GetSize())
		{
		bModified = Get(index)->IsModified();
		index++;
		}
	return bModified;
	}

#ifndef DISABLE_SMART_SERIALIZATION
template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Serialize(CArchive& ar)
	{
	// First call base class
	COXBrilliantObj::Serialize(ar);

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
				// ... Will call SetModified when necessary
				if (Add(pSObj, key) < 0)
					{
					TRACE(TEXT("COXBrilliantGrp::Serialize : Addition failed, throwing CArchiveException\n"));
					AfxThrowArchiveException(CArchiveException::generic);
					}
				}
			else
				// ... Will call SetModified when necessary
				Add(pSObj);
			}
		}
	}

template <class T, class G_KEY, class G_ARG_KEY>
CArchive& AFXAPI operator>>(CArchive& ar, COXBrilliantGrp<T, G_KEY, G_ARG_KEY>*& pSGroup)
	{
	// The operator>> is not supported on COXBrilliantGrp.
	// You can use Serialize which is fully implemented, 
	//  or use DECLARE_SERIAL in a class derived from this class
	TRACE(_T("operator>> of COXBrilliantGrp : Function not supported : throwing NotSupportedException\n"));
	AfxThrowNotSupportedException();
	return ar;
	}
#endif // DISABLE_SMART_SERIALIZATION

#ifdef _DEBUG
template <class T, class G_KEY, class G_ARG_KEY>
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::AssertValid() const
	{
	COXBrilliantObj::AssertValid();

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
void COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::Dump(CDumpContext& dc) const
	{
	COXBrilliantObj::Dump(dc);
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
COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::~COXBrilliantGrp()
	{
	ASSERT_VALID(this);
	Empty();
	}

// protected:
template <class T, class G_KEY, class G_ARG_KEY> inline
COXBrilliantGrp<T, G_KEY, G_ARG_KEY>::COXBrilliantGrp()
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
