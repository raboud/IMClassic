// ==========================================================================
// 						Template Specification : COXSmartGrp
// ==========================================================================

// Header file : OXSGrp.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	YES	Uses exceptions
//			(CMemoryException by NULL-pointer dereference using operator[])

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This is a collection class that can be used to store smart pointers
//	 of a specific type
//	The group itself is derived from CObject and will also be
//	 accessed through a smart pointer

// Remark:
//	You can address the items in the group in two ways : on index and on
//	 key

//	Valid indices are from 0 till number of items - 1
//	This provides an ordered sequence of the items
//	When adding you can decide where you want to add the new item
//	 by default it is added at the tail of the group
//	You can move existing items to put them on a new position
//	The indexes are specified by an Index object.  
//	You can easily convert the Index to and from a LONG type
//	To avoid conficts do not use LONGs directly

//	You can choose the type of the key yourself (because this is a template)
//	You sypply 2 types (one the actual class and the other as function argument)
//	 e.g. CString and LPCTSTR  or  double and double
//	You do not have to provide a key when you add an item, but you can
//	The value of a key must be unique over the entire group

//	Because an additionion increases the reference count of the object you add
//	 you may delete other references if you want to

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __SGRP_H__
#define __SGRP_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <limits.h>
#include "OXSPtr.h"
#include "OXIndex.h"
#include "OXBuildNew.h"


#ifndef G_BEGIN
#define G_BEGIN	 	(LONG_MIN)
#define G_END		(LONG_MAX)
#define G_NOT_FOUND	(-1)
#define G_DUPLICATE	(-2)
#define G_DEFAULT	(-1)
#endif // G_BEGIN

// Forward declaration of templated friend functions
template <class T, class G_KEY, class G_ARG_KEY> class COXSmartGrp;
template <class T, class G_KEY, class G_ARG_KEY> class COXGrpItem;
template <class T, class G_KEY, class G_ARG_KEY> class COXGrpCursor;
#ifndef DISABLE_SMART_SERIALIZATION
template <class T, class G_KEY, class G_ARG_KEY>
CArchive& AFXAPI operator>>(CArchive& ar, COXSmartGrp<T, G_KEY, G_ARG_KEY>*& pSGroup);
#endif // DISABLE_SMART_SERIALIZATION

template <class T, class G_KEY, class G_ARG_KEY> 
class OX_CLASS_DECL COXSmartGrp : public CObject
{
friend class COXSPtr<COXSmartGrp<T, G_KEY, G_ARG_KEY> >;

// Data members -------------------------------------------------------------
public:
protected:
	CArray<COXGrpItem<T, G_KEY, G_ARG_KEY>*, COXGrpItem<T, G_KEY, G_ARG_KEY>*> m_array;
	CMap<G_KEY, G_ARG_KEY, COXGrpItem<T, G_KEY, G_ARG_KEY>*, COXGrpItem<T, G_KEY, G_ARG_KEY>*> m_map;

private:
	
// Member functions ---------------------------------------------------------
public:
	Index Add(COXSPtr<T>& pSObj, Index index = Index(G_DEFAULT));
    // --- In  : pSObj : Smart pointer to add
	//			 index : The position where to add
	//					 By default (Index(G_DEFAULT)) it is added at the tail
	// --- Out : 
	// --- Returns : The position where the smart pointer is added
	//				 or G_NOT_FOUND when an invalid index is specified
	// --- Effect : Adds a smart pointer at the specified position
	//				Valid indexes are 0..number of items already in group

	Index Add(COXSPtr<T>& pSObj, G_ARG_KEY key, Index index = Index(G_DEFAULT),
		BOOL bResolveKeyConflict = FALSE);
    // --- In  : pSObj : Smart pointer to add
	//			 key : The key belonging to the smart pointer
	//			 index : The position where to add
	//					 By default (Index(G_DEFAULT)) it is added at the tail
	//			 bResolveKeyConflict : Whether a key conflict should be resolved
	// --- Out : 
	// --- Returns : The position where the smart pointer is added
	//				 or G_NOT_FOUND when an invalid index is specified
	//				 or G_DUPLICATE when the key already exists
	// --- Effect : Adds a smart pointer at the specified position
	//				Valid indexes are 0..number of items already in group
	//				If bResolveKeyConflict == FALSE valid key values are 
	//				all the values that are not yet in the smart group
	//				Otherwise it will be resolved by creating a new unique key on the fly.
	//				The template function MakeNewKey() is used for this

	Index Add(COXSPtr<COXSmartGrp<T, G_KEY, G_ARG_KEY> >& pSGroup, 
		Index index = Index(G_DEFAULT), BOOL bResolveKeyConflict = TRUE);
    // --- In  : pSGroup : Group of smart pointers to add
	//			 index : The position where to add
	//					 By default (Index(G_DEFAULT)) it is added at the tail
	//			 bResolveKeyConflict : Whether a key conflict should be resolved
	// --- Out : 
	// --- Returns : The position where the last smart pointer is added
	//				 or G_NOT_FOUND when an invalid index is specified
	// --- Effect : Adds the smart pointers of the specified group to this group
	//				at the specified position
	//				Valid indexes are 0..number of items already in group
	//				When a key of an element to be added already exists
	//				it can be resolved by creating a new unique key on the fly.
	//				The template function MakeNewKey() is used for this

	BOOL Replace(Index index, COXSPtr<T>& pSObj);
    // --- In  : index : The position to replace
	//			 pSObj : The new smart pointer
	//			 
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Replaces the smart pointer at the specified position
	//				by the specified one
	//				A possible old key will be removed

	BOOL Replace(Index index, COXSPtr<T>& pSObj, G_ARG_KEY key);
    // --- In  : index : The position to replace
	//			 pSObj : The new smart pointer
	//			 key : The new key to be used
	//			 
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Replaces the smart pointer at the specified position
	//				by the specified one

	BOOL Replace(G_ARG_KEY key, COXSPtr<T>& pSObj);
    // --- In  : key : The position to replace
	//			 pSObj : The new smart pointer
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Replaces the smart pointer at the specified position
	//				by the specified one
	//				A possible old key will be removed
	//				The old key value will be maintained

	COXSPtr<T> Get(Index index) const;
	COXSPtr<T> Get(G_ARG_KEY key) const;
    // --- In  : index / key : The position of the smart pointer
	// --- Out : 
	// --- Returns : The smart pointer at that position or
	//				 a smart NULL pointer when the index or key does not exist
	// --- Effect : 

	COXGrpCursor<T, G_KEY, G_ARG_KEY> operator[](Index index);
		// throw(CMemoryException);
    // --- In  : index : The position of the smart pointer
	// --- Out : 
	// --- Returns : A group cursor that points to the spacified
	//				 group item
	// --- Effect : The operator can be used to add items by specifying
	//				 a valid new index (Index(G_DEFAULT)) or number of items already in group
	//				When an existing index is specified you can change 
	//				 or replace the item
	//				When an invalid index is spacified a memory exception
	//				 will be thrown 
	//				A possible old key will be removed when replacing an item

	COXGrpCursor<T, G_KEY, G_ARG_KEY> operator[](G_ARG_KEY key);
    // --- In  : key : The position of the smart pointer
	//			 
	// --- Out : 
	// --- Returns : A group cursor that points to the spacified
	//				 group item
	// --- Effect : The operator can be used to add items by specifying
	//				 a valid new key 
	//				When an existing key is specified you can change 
	//				 or replace the item
	//				The old key value will always be maintained

	BOOL Swap(Index index1, Index index2);
	BOOL Swap(G_ARG_KEY key1, G_ARG_KEY key2);
    // --- In  : index1 / key1
	//			 index2 / key2
	// --- Out : 
	// --- Returns : Whether the swap succeeded
	// --- Effect : Swaps the two smart pointers at the specified position

	BOOL Move(Index index, LONG nOffset);
	BOOL Move(G_ARG_KEY key, LONG nOffset);
    // --- In  : index / key
	//			 nOffset : Positions and direction to move
	//					   (negative = to head, positive = to tail)
	// --- Out : 
	// --- Returns : Whether the move succeeded
	// --- Effect : Moves the specified smart pointer in the specified direction 
	//				Use G_BEGIN to move to the head and G_END to move to the tail
	//				Invalid offsets are converted to valid offsets automatically

	Index Find(G_ARG_KEY key) const;
    // --- In  : key
	// --- Out : 
	// --- Returns : The index of the smart pointer with the specified key
	//				 or G_NOT_FOUND when the key does not exist
	// --- Effect : 


	BOOL Remove(Index index);
	COXSmartGrp& operator-=(Index index);
    // --- In  : index
	// --- Out : 
	// --- Returns : non-operator : Whether the smart pointer was removed successfukky
	// --- Effect : Removes the specified item from the group

	BOOL Remove(G_ARG_KEY key);
	COXSmartGrp& operator-=(G_ARG_KEY key);
    // --- In  : key
	// --- Out : 
	// --- Returns : non-operator : Whether the smart pointer was removed successfukky
	// --- Effect : Removes the specified item from the group

	BOOL Exist(Index index) const;
	BOOL operator>=(Index index) const;
	BOOL Exist(G_ARG_KEY key) const;
	BOOL operator>=(G_ARG_KEY key) const;
    // --- In  : index / key 
	// --- Out : 
	// --- Returns : Whether the specified item exists (is part of the group)
	// --- Effect : 

	BOOL operator>(Index index) const;
	BOOL operator>(G_ARG_KEY key) const;
    // --- In  : index / key 
	// --- Out : 
	// --- Returns : Whether the specified item exists in the group among others
	// --- Effect : 

	BOOL operator==(Index index) const;
	BOOL operator==(G_ARG_KEY key) const;
    // --- In  : index / key 
	// --- Out : 
	// --- Returns : Whether the specified item is the only one in the group
	// --- Effect : 

	LONG GetSize() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : The number of items in the group
	// --- Effect : 

	LONG GetKeyCount() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : The number of items with a key 
	// --- Effect : 

	BOOL IsEmpty() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : Whether the group is empty
	// --- Effect : 

	void Empty();
    // --- In  : 
	// --- Out : 
	// --- Returns : Makes the group empty by removing all the items
	// --- Effect : 

	BOOL GetKey(Index index, G_KEY& key) const;
    // --- In  : index 
	// --- Out : key
	// --- Returns : Whether the specified index has a key
	// --- Effect : Retrieves the key of a specified item (if it has one)

	BOOL SetKey(Index index, G_ARG_KEY key, BOOL bResolveKeyConflict = FALSE);
    // --- In  : index : index of the item
	//			 key : the new key
	//			 bResolveKeyConflict : Whether a key conflict should be resolved
	// --- Out : 
	// --- Returns : Whether the specified items has suvccessfully received a new key
	// --- Effect : Replaces the key of an item by another one
	//				If no key-conflict resolution is selected then 
	//              the new key should not yet exist on another item

	BOOL RemoveKey(Index index);
    // --- In  : index : index of the item
	// --- Out : 
	// --- Returns : Whether the specified items has suvccessfully removed its key
	// --- Effect : Removes the key of an item 

#ifndef DISABLE_SMART_SERIALIZATION
	virtual void Serialize(CArchive& ar);
    // --- In  : ar : The archive to which this object will be serialized
	// --- Out : 
	// --- Returns : 
	// --- Effect : 

	friend CArchive& AFXAPI operator>>(CArchive& ar, COXSmartGrp<T, G_KEY, G_ARG_KEY>*& pSGroup);
	// The function operator>> is NOT supported for smart groups
	// It only exist to enable correct compilation of nested groups
	// Use the Serialize function which is fully implemented, 
	//  or use DECLARE_SERIAL in a class derived from this class
#endif // DISABLE_SMART_SERIALIZATION

#ifdef _DEBUG
	virtual void AssertValid() const;
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	
	virtual void Dump(CDumpContext& dc) const;
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
#endif

	virtual ~COXSmartGrp();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This destructs the object

protected:
	COXSmartGrp();

private:
                   
};

// Include help templates
#include "OXGrpItem.h"
#include "OXGrpCrsr.h"

// Template implementation
#include "OXSGrp.inl"

#endif // __OXSGRP_H__
// ==========================================================================
