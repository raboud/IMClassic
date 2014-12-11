// ==========================================================================
// 						Template Specification : COXBrilliantGrp
// ==========================================================================

// Header file : OXSGrp.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COXBrilliantObj

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO Persistent objects (saveable on disk)      
//	YES	Uses exceptions
//			(CMemoryException by NULL-pointer dereference using operator[])

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This has the same functionality as COXSmartGrp with the additional feature 
//	 the transactions are implemented.  This class is derived from COXBrilliantObj
//   instead of CObject
//  For more information see the header of COXSmartGrp 

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXBGRP_H__
#define __OXBGRP_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <limits.h>
#include "OXBObj.h"
#include "OXSPtr.h"
#include "OXIndex.h"
#include "OXBuildNew.h"
#include "OXGrpItem.h"

#ifndef G_BEGIN
#define G_BEGIN	 	(LONG_MIN)
#define G_END		(LONG_MAX)
#define G_NOT_FOUND	(-1)
#define G_DUPLICATE	(-2)
#define G_DEFAULT	(-1)
#endif // G_BEGIN


// Forward declaration of templated friend functions
template <class T, class G_KEY, class G_ARG_KEY> class COXBrilliantGrp;
#ifndef DISABLE_SMART_SERIALIZATION
template <class T, class G_KEY, class G_ARG_KEY>
CArchive& AFXAPI operator>>(CArchive& ar, COXBrilliantGrp<T, G_KEY, G_ARG_KEY>*& pBGroup);
#endif // DISABLE_SMART_SERIALIZATION

template <class T, class G_KEY, class G_ARG_KEY> 
class OX_CLASS_DECL COXBrilliantGrp : public COXBrilliantObj
{
// Expand the declarations of  DECLARE_SCOPY
// here manually, because the template class is interpreted by the macro
// as multiple parameters (because of the comma)
// DECLARE_SCOPY(COXBrilliantGrp<T, G_KEY, G_ARG_KEY>)
virtual COXBrilliantObj* Clone();
void Copy(COXBrilliantGrp<T, G_KEY, G_ARG_KEY> * COXBrilliantObj);
virtual void VirtualCopy(COXBrilliantObj* pSource);

friend class COXSPtr<COXBrilliantGrp<T, G_KEY, G_ARG_KEY> >;

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

	Index Add(COXSPtr<COXBrilliantGrp<T, G_KEY, G_ARG_KEY> >& pBGroup, 
		Index index = Index(G_DEFAULT), BOOL bResolveKeyConflict = TRUE);
    // --- In  : pBGroup : Brilliant group to add
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
	COXBrilliantGrp& operator-=(Index index);
    // --- In  : index
	// --- Out : 
	// --- Returns : non-operator : Whether the smart pointer was removed successfukky
	// --- Effect : Removes the specified item from the group

	BOOL Remove(G_ARG_KEY key);
	COXBrilliantGrp& operator-=(G_ARG_KEY key);
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

	COXBrilliantGrp(const COXBrilliantGrp& sGroup);
    // --- In  : sGroup : The smart group to be copied
	// --- Out : 
	// --- Returns : 
	// --- Effect : Copy constructor

	COXBrilliantGrp& operator=(const COXBrilliantGrp& sGroup);
    // --- In  : sGroup : The smart group to be copied
	// --- Out : 
	// --- Returns : 
	// --- Effect : Assignment operator

	virtual void StartTransaction(BOOL bDeferCopy = TRUE);
	// --- In  : bDeferCopy : Whether a transaction copy should be taken at the 
	//						  first change (TRUE) or at the start of the 
	//						  transaction (FALSE)

	virtual void Commit();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Commits the work that has been done since the transaction
	//				started

	virtual void Rollback();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Rolls back since the transaction started
	//				All the chenges will be discarded

	virtual void SetModified(BOOL bModified = TRUE);
	// --- In  : bModified : Whether the object is modified
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the modified state
	//				SetModified(TRUE) corresponds only to this object itself
	//				SetModified(FALSE) is passed on to possible child objects

	virtual BOOL IsModified() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether this object itself or one of its possible child objects 
	//               has been modified
	// --- Effect : 

#ifndef DISABLE_SMART_SERIALIZATION
	virtual void Serialize(CArchive& ar);
    // --- In  : ar : The archive to which this object will be serialized
	// --- Out : 
	// --- Returns : 
	// --- Effect : 

	friend CArchive& AFXAPI operator>>(CArchive& ar, COXBrilliantGrp<T, G_KEY, G_ARG_KEY>*& pBGroup);
	// The functions operator>> is NOT supported for brilliant groups
	// It only exists to enable correct compilation of nested groups
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

	virtual ~COXBrilliantGrp();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This destructs the object

protected:
	COXBrilliantGrp();

private:
                   
};

// Include help templates
#include "OXGrpItem.h"
#include "OXGrpCrsr.h"

// Template implementation
#include "OXBGrp.inl"

#endif // __OXBGRP_H__
// ==========================================================================
