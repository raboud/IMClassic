// ==========================================================================
// 							Class Specification : COXSmartWatcher
// ==========================================================================

// Header file : OXSWatcher.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :
//	This class is used to check certain operations with smart pointers
//  It check for circular graphs and for wrapping a smart pointer
//  around an object that is already wrapped

// Remark:
//	This file has an implementation only if _DEBUG is defined

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG // entire file

#ifndef __OXSWATCHER_H__
#define __OXSWATCHER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


typedef CMapPtrToPtr CSObjColl;
typedef CMapPtrToPtr CSPtrColl;

class OX_CLASS_DECL COXSmartWatcher : public CObject
{
DECLARE_DYNAMIC(COXSmartWatcher)

// Data members -------------------------------------------------------------
public:
protected:
	CSObjColl	m_SmartObjects;
	CSPtrColl	m_SmartPointers;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXSmartWatcher();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs an object

	void RegisterPointerAndObject(void* pSPtr, void* pSObj, size_t nSize);
	// --- In  : pSPtr : The address of the smart pointer 
	//			 pSObj : The address of the wrapped object
	//			 nSize : The size of the wrapped object
	// --- Out : 
	// --- Returns : 
	// --- Effect : This registers a new (pointer, object) pair
	//			    The object may already be wrapped by another smart pointer
	//				A test is performed to check whether this creates a circular graph

	void UnRegisterPointer(void* pSPtr, void* pSObj);
	// --- In  : pSPtr : The address of the smart pointer 
	//			 pSObj : The address of the wrapped object
	// --- Out : 
	// --- Returns : 
	// --- Effect : This unregisters a smart pointer
	//				A test is performed to check whether the object
	//				is still referencable from outside a possible circular graph

	void UnRegisterObject(void* pSObj);
	// --- In  : pSObj : The address of the wrapped object
	// --- Out : 
	// --- Returns : 
	// --- Effect : This unregisters an object
	//				This needs to be called when the reference count of the object
	//				reaches zero

	BOOL IsRegisteredObject(void* pSObj);
	// --- In  : pSObj : The address of the wrapped object
	// --- Out : 
	// --- Returns : Whether this object is already registered
	// --- Effect : 

// #ifdef _DEBUG // entire file is only included if _DEBUG
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
// #endif // _DEBUG

	virtual ~COXSmartWatcher();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This destructs the object

protected:
	BOOL IsCircularReferenced(void* pSPtr, int* pnNumber);
	BOOL IsExternallyUnreachable(void* pSObj);

	void* ReferencedObjectFromPointer(void* pSPtr);
	void* EmbeddedObjectFromPointer(void* pSPtr);
	void EmbeddedPointersFromObject(void* pSObj, CSPtrColl* pVisited, CSPtrColl* pEmbeddedSPtrs);
	void ReferencedPointersFromObject(void* pSObj, CSPtrColl* pReferencedSPtrs);

	BOOL IsReachableFrom(void* pSPtr, void* pSPtrFrom, CSPtrColl* pVisited, 
		int* pnNumber, BOOL bIgnoreEquality = FALSE);
	BOOL IsExternallyUnreachable(void* pSObj, void* pSObjStop, CSObjColl* pvisited, 
		BOOL bIgnoreEquality = FALSE);
private:
                   
};

#endif // __OXSWATCHER_H__
#endif // _DEBUG 
// ==========================================================================
