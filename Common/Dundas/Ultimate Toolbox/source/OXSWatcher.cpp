// ==========================================================================
//                     Class Implementation : COXSmartWatcher
// ==========================================================================

// Source file : OXSWatcher.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved              
        
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXSWatcher.h"

#ifdef _DEBUG // entire file

// #ifdef _DEBUG // entire file is only included if _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
// #endif

IMPLEMENT_DYNAMIC(COXSmartWatcher, CObject)

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:
	// CSObjColl m_SmartObjects;
	// --- A collection containing all the objecst that are wrapped by
	//     a smart pointer ('registered')
	//	   It maps the address of the object to its size (cast as (void*))

	// CSPtrColl m_SmartPointers;
	// --- A collection containing all the smart pointers
	//	   It maps the address of the smart pointer to the address of the wrapped object
	//     Some smart NULL pointers may not be included in this collection
	//     (we do not need them here anyway)

	// NOTE : These two collections can be interpreted as a representation of a graph
	//        A smart pointer points to a smart object.
	//		  This object can contain (one or more) other smart pointers.
	//		  Each of these point to another smart object, etc ...
	//		  We store the address of the smart pionter and the address and size
	//         of the smart object, this is all we need
	//		  Not all smart objects contain other smart pointers,
	//		   so the graph does not have to be fully connected (we can have islands of subgraphs)
	//		  A function included in this class will chech whether a graph 
	//		   including a particular pointer is a tree or contains a circular reference
	//		   (IsCircularReferenced())
	//		  Another function will chech whether a specified object can only be referenced
	//		   by the pointers of the circular graph it is part of or
	//		   whether external references still exist
	//		   (IsExternallyUnreachable())

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXSmartWatcher::COXSmartWatcher()
	:
	CObject(),
	m_SmartObjects(),
	m_SmartPointers()
	{
	ASSERT_VALID(this);
	}

void COXSmartWatcher::RegisterPointerAndObject(void* pSPtr, void* pSObj, size_t nSize)
	{
	m_SmartObjects.SetAt(pSObj, (void*)nSize);
	m_SmartPointers.SetAt(pSPtr, pSObj);
	int nNumber = 0;
	if (IsCircularReferenced(pSPtr, &nNumber))
		{
		// Circular smart pointer references may lead to memory leaks, so warn the programmer
		TRACE(_T("COXSmartWatcher::RegisterPointerAndObject : The assignment of smart pointer (%8.8X) has created\n")
			  _T("\ta circular reference of at least %i items\n"), (LONG)pSPtr, nNumber);
		}
	}

void COXSmartWatcher::UnRegisterPointer(void* pSPtr, void* pSObj)
	{
	m_SmartPointers.RemoveKey(pSPtr);
	if (IsExternallyUnreachable(pSObj))
		{
		TRACE(_T("COXSmartWatcher::UnRegisterPointer : The clearing of smart pointer (%8.8X) has resulted\n")
			  _T("\tin a externally unreachable circular reference (including object %8.8X). ")
			  _T("This will result in memory leaks\n"), (LONG)pSPtr, (LONG)pSObj);
		// Restucture your program so that circular smart pointer references
		// are always externally reachable !
		ASSERT(FALSE);
		}
	}

void COXSmartWatcher::UnRegisterObject(void* pSObj)
	{
	m_SmartObjects.RemoveKey(pSObj);
	}

BOOL COXSmartWatcher::IsRegisteredObject(void* pSObj)
	{
	void* pDummy;
	return m_SmartObjects.Lookup(pSObj, pDummy);
	}

// #ifdef _DEBUG // entire file is only included if _DEBUG
void COXSmartWatcher::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXSmartWatcher::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	dc << "\nm_SmartObjects : " << m_SmartObjects;
	dc << "\nm_SmartPointers : " << m_SmartPointers;
	dc << "\n";
	}
// #endif //_DEBUG

COXSmartWatcher::~COXSmartWatcher()
	{
	}

// protected:
BOOL COXSmartWatcher::IsCircularReferenced(void* pSPtr, int* pnNumber)
	// --- In  : pSPtr : Smart pointer to start with
	//			 pnNumber : Pointer to an int containing 0
	// --- Out : pnNumber : The (minimum) size of the circular graph
	//						(number of items participating in the graph)
	// --- Returns : Whether a circular graph exists of which the specified
	//				 pointer is a part
	// --- Effect : 
	{
	CSPtrColl visited;
	return IsReachableFrom(pSPtr, pSPtr, &visited, pnNumber, TRUE);
	}

BOOL COXSmartWatcher::IsExternallyUnreachable(void* pSObj)
	// --- In  : pSObj : Smart object to start with
	// --- Out : 
	// --- Returns : Whether the specified object is only reachable from within
	//				 a circular graph, but has no external references anymore
	// --- Effect : 
	{
	if (pSObj == NULL)
		// Special parameter value that disables the check
		return FALSE;
	CSObjColl visited;
	return IsExternallyUnreachable(pSObj, pSObj, &visited, TRUE);
	}


void* COXSmartWatcher::ReferencedObjectFromPointer(void* pSPtr)
	// --- In  : pSPtr : Smart pointer 
	// --- Out : 
	// --- Returns : The smart object that is referenced by the specified pointer
	// --- Effect : 
	{
	void* pSObj;
	VERIFY(m_SmartPointers.Lookup(pSPtr, pSObj));
	return pSObj;
	}

void* COXSmartWatcher::EmbeddedObjectFromPointer(void* pSPtr)
	// --- In  : pSPtr : Smart pointer 
	// --- Out : 
	// --- Returns : The smart object in which the specified pointer is embedded
	//				 NULL is returned when the pointer is not contained in a smart object
	// --- Effect : 
	{
	// Now iterate all the smart object and search
	// in which the the pointer is embedded (may find none)
	void* pEmbeddedObject = NULL;
	void* pSObj;
	void* pSize;
	void* pSObjEnd;
	POSITION pos = m_SmartObjects.GetStartPosition();
	while ((pEmbeddedObject == NULL) && (pos != NULL))
		{
		m_SmartObjects.GetNextAssoc(pos, pSObj, pSize);
		pSObjEnd = (char*)pSObj + (size_t)pSize;
		if ((pSObj <= pSPtr) && 
			(pSPtr < pSObjEnd))
			pEmbeddedObject = pSObj;
		}
	return pEmbeddedObject;
	}

void COXSmartWatcher::EmbeddedPointersFromObject(void* pSObj, CSPtrColl* pVisited, 
	CSPtrColl* pEmbeddedSPtrs)
	// --- In  : pSObj : Smart object
	//			 pVisited : Collection of smart pointers to exclude
	//			 pEmbeddedSPtrs : A collection of smart pointers
	// --- Out : pEmbeddedSPtrs : A collection of smart pointers
	// --- Returns : 
	// --- Effect : This functions adds all the smart pointers to the list
	//              that are embedded in the specified object and are not part of the
	//				already visited list
	{
	// Iterate all the pointers and check which are embedded in the object

	// First get the objects address range
	void* pSObjEnd;
	void* pSize;
	VERIFY(m_SmartObjects.Lookup(pSObj, pSize));
	pSObjEnd = (char*)pSObj + (size_t)pSize;

	// Now iterate all the smart pointers
	void* pSPtr;
	void* pDummy;
	POSITION pos = m_SmartPointers.GetStartPosition();
	while (pos != NULL)
		{
		m_SmartPointers.GetNextAssoc(pos, pSPtr, pDummy);
		if ((pSObj <= pSPtr) && 
			(pSPtr < pSObjEnd) &&
			!pVisited->Lookup(pSPtr, pDummy))
			pEmbeddedSPtrs->SetAt(pSPtr, NULL);
		}
	}

void COXSmartWatcher::ReferencedPointersFromObject(void* pSObj, CSPtrColl* pReferencedSPtrs)
	// --- In  : pSObj : Smart object
	//			 pReferencedSPtrs : A collection of smart pointers
	// --- Out : pReferencedSPtrs : A collection of smart pointers
	// --- Returns : 
	// --- Effect : This functions adds all the smart pointers to the list
	//              that reference the specified object 
	{
	// Iterate all the pointers and check which refernces the object
	void* pSPtr;
	void* pSRefObj;
	POSITION pos = m_SmartPointers.GetStartPosition();
	while (pos != NULL)
		{
		m_SmartPointers.GetNextAssoc(pos, pSPtr, pSRefObj);
		if (pSObj == pSRefObj)
			pReferencedSPtrs->SetAt(pSPtr, NULL);
		}
	}

BOOL COXSmartWatcher::IsReachableFrom(void* pSPtr, void* pSPtrFrom, CSPtrColl* pVisited, 
		int* pnNumber, BOOL bIgnoreEquality /* = FALSE */)
	// --- In  : pSPtr : Smart pointer to look for
	//			 pSPtrFrom : Smart pointer to smart the search with
	//			 pVisited : The list of smart pointer to be excluded in the search
	//			 pnNumber : The current recursion level (as negative number)
	//                      or the recursion level when a path was found (as positive number)
	//			 bIgnoreEquality : Whether to check if pSPtr == pSPtrFrom
	// --- Out : pVisited : The list of smart pointer to be excluded in the search
	// --- Returns : Whether it is reachable or not
	// --- Effect : This is the main recursive function.
	//				The recursion is started with 
	//				    pSPtr = pSPtrFrom
	//					pVisited : Empty list
	//					pnNumber : Points to 0
	//					bIgnoreEquality : TRUE
	//				In all recursive calls bIgnoreEquality is FALSE
	//				The functions searches through the graph in depth-first
	{
	ASSERT(pVisited != NULL);
	ASSERT(AfxIsValidAddress(pVisited, sizeof(CSPtrColl)));

	// *pnNumber contains the recursion level as a negative number
	// When a circular path is found it is made positive and never changed again
	// ... Start a new level
	if (*pnNumber <= 0)
		(*pnNumber)--;

	// Check for trivial pointer values
	if ((pSPtr == NULL) || (pSPtrFrom == NULL))
		{
		if (*pnNumber <= 0)
			(*pnNumber)++;
		// ... NULL pointers are never 'reachable'
		return FALSE;
		}

	// First check whether the smart pointer and from pointer are the same
	// (ends the recursive call)
	if (!bIgnoreEquality && (pSPtr == pSPtrFrom))
		{
		// Store the previous recursion level as positive number
		(*pnNumber) = -(*pnNumber) - 1;
		return TRUE;
		}

	// Get the object the smart pointer refers to
	void* pSObj;
	pSObj = ReferencedObjectFromPointer(pSPtrFrom);

	// Get all the smart pointers that are part of that object
	// and that have not yet been visited (to avoid endless recursion)
	CSPtrColl embeddedSPtrs;
	EmbeddedPointersFromObject(pSObj, pVisited, &embeddedSPtrs);

	// Add the from pointer to the list ob visited pointer
	// Exclude the pointer we are searching for (should never be in the visited list)
	if (pSPtr != pSPtrFrom)
		pVisited->SetAt(pSPtrFrom, NULL);

	// Recursively search through all the embedded pointers
	// (depth-first search)
	BOOL bReachable = FALSE;
	void* pNextSPtr;
	void* pDummy;
	POSITION pos = embeddedSPtrs.GetStartPosition();
	while (!bReachable && (pos != NULL))
		{
		embeddedSPtrs.GetNextAssoc(pos, pNextSPtr, pDummy);
		bReachable = IsReachableFrom(pSPtr, pNextSPtr, pVisited, pnNumber);
		}

	// ... End the current level
	if (*pnNumber <= 0)
		(*pnNumber)++;

	// Return the result
	return bReachable;
	}

BOOL COXSmartWatcher::IsExternallyUnreachable(void* pSObj, void* pSObjStop, CSObjColl* pVisited, 
		BOOL bIgnoreEquality /* = FALSE */)
	// --- In  : pSObj : Smart object to look for
	//			 pSObjStop : Smart object to indicated when to stop searching
	//			 pVisited : The list of smart objects to be excluded in the search
	//			 bIgnoreEquality : Whether to check if pSObj == pSObjStop
	// --- Out : pVisited : The list of smart objects to be excluded in the search
	// --- Returns : Whether the smart object is only reachable from within a
	//				 circular graph and has no external references
	// --- Effect : This is the main recursive function.
	//				The recursion is started with 
	//				    pSObj = pSObjStop
	//					pVisited : Empty list
	//					bIgnoreEquality : TRUE
	//				In all recursive calls bIgnoreEquality is FALSE
	//				The functions searches through the graph in depth-first
	{
	ASSERT(pVisited != NULL);
	ASSERT(AfxIsValidAddress(pVisited, sizeof(CSObjColl)));

	// Check for trivial pointer values
	if ((pSObj == NULL) || (pSObjStop == NULL))
		// ... NULL pointers are always 'unreachable'
		return TRUE;

	// First check whether we have reached the object we have started with
	// (ends the recursive call)
	if (!bIgnoreEquality && (pSObj == pSObjStop))
		return TRUE;

	// Add the object to the list ob visited objects
	// Exclude the pointer we will stop at (should never be in the visited list)
	if (pSObj != pSObjStop)
		pVisited->SetAt(pSObj, NULL);

	// Get the the smart pointers that reference this this object
	CSPtrColl RefSPtrs;
	ReferencedPointersFromObject(pSObj, &RefSPtrs);

	// Get all the objects that contain these smart pointer
	// If one is not contained in a registered object, we have an external reference
	CSObjColl RefSObjs;
	void* pNextSPtr;
	void* pDummy;
	void* pSObjEmbed;
	POSITION pos = RefSPtrs.GetStartPosition();
	while (pos != NULL)
		{
		RefSPtrs.GetNextAssoc(pos, pNextSPtr, pDummy);
		pSObjEmbed = EmbeddedObjectFromPointer(pNextSPtr);
		if (pSObjEmbed == NULL)
			// Found a smart pointer that is not embedded in a registered object
			return FALSE;
		if (!pVisited->Lookup(pSObjEmbed, pDummy))
			RefSObjs.SetAt(pSObjEmbed, NULL);
		}

	// Recursively search through all the objects
	// (depth-first search)
	BOOL bUnreachable = TRUE;
	void* pSNextObj;
	pos = RefSObjs.GetStartPosition();
	while (bUnreachable && (pos != NULL))
		{
		RefSObjs.GetNextAssoc(pos, pSNextObj, pDummy);
		bUnreachable = IsExternallyUnreachable(pSNextObj, pSObjStop, pVisited);
		}

	// Return the result
	return bUnreachable;
	}


// private:

#endif // _DEBUG 
// ==========================================================================
