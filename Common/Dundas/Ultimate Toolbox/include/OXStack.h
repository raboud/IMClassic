// ==========================================================================
// 						Template Specification : COXStack
// ==========================================================================

// Header file : OXStack.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CList

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This template class extends the basic CList template so that it can be used
//	for stack operations : Push(), Pop() and Peek()

// Remark:
//	All functions of the base class CList are still accessible,
//	 but you should take care in using them.  
//	E.g. by accessing elements apart from the head directly,
//	 you can violate the stack invariants
//	Other functions like IsEmpty(), RemoveAll() are still usefull

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXSTACK_H__
#define __OXSTACK_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <afxtempl.h>


template <class TYPE, class ARG_TYPE>
class OX_CLASS_DECL COXStack : public CList<TYPE, ARG_TYPE>
{
// Data members -------------------------------------------------------------
public:
protected:
private:
	
// Member functions ---------------------------------------------------------
public:
	void Push(ARG_TYPE newElement);
	// --- In  : newElement : The new element to push on the stack
	// --- Out : 
	// --- Returns : 
	// --- Effect : Adds a new element to the top of the stack

	TYPE& Peek();
	// --- In  : 
	// --- Out : 
	// --- Returns : Element that is at the top of the stack or NULL
	//				 when the stack is empty
	// --- Effect : Peeks at top element of stack
	//				Stack should not be empty

	TYPE Peek() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Element that is at the top of the stack or NULL
	//				 when the stack is empty
	// --- Effect : Peeks at top element of stack

	TYPE Pop();
	// --- In  : 
	// --- Out : 
	// --- Returns : Element that is at the top of the stack
	// --- Effect : Pops the top element off stack.  
	//				The stack should not be empty

protected:

private:
                   
};

#include "OXStack.inl"

#endif // __OXSTACK_H__
// ==========================================================================
