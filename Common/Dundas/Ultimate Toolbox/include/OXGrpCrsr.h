// ==========================================================================
// 						Class Specification : COXGrpCursor
// ==========================================================================

// Header file : OXGrpCrsr.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from 

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class is a cursor symbolizing a specific object in a smart group
//	It is used to implement the operator[] of a smart group

// Remark:

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXGRPCRSR_H__
#define __OXGRPCRSR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


// Forward declarations
template <class T> class COXSPtr;
template <class T, class G_KEY, class G_ARG_KEY> class COXSmartGrp;
template <class T, class G_KEY, class G_ARG_KEY> class COXBrilliantGrp;
template <class T, class G_KEY, class G_ARG_KEY> class COXGrpItem;

template <class T, class G_KEY, class G_ARG_KEY> 
class OX_CLASS_DECL COXGrpCursor
{
friend class COXSmartGrp<T, G_KEY, G_ARG_KEY>;
friend class COXBrilliantGrp<T, G_KEY, G_ARG_KEY>;
// Data members -------------------------------------------------------------
public:
protected:
	COXSmartGrp<T, G_KEY, G_ARG_KEY>* m_pSmartGroup;
	COXGrpItem<T, G_KEY, G_ARG_KEY>* m_pGroupItem;
	BOOL m_bAddressedByKey;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXGrpCursor(const COXGrpCursor& groupCursor);
    // --- In  : groupCursor
	// --- Out : 
	// --- Returns : 
	// --- Effect : Copy constructor

	operator const COXSPtr<T>& ()
    // --- In  : 
	// --- Out : 
	// --- Returns : The smart pointer located on this cursor position
	// --- Effect : Conversion operator
	//			    To work around a bug in Visual C++ 2.2 or lower this function 
	//			    is defined in this header file
		{
		// Following 2 ASSERTs generate a compiler error in Visual C++ 2.2 or lower
		// error C2400: inline assembler syntax error in 'opcode'; found 'bad token'
		// If you receive this error remark both lines
		ASSERT(m_pSmartGroup != NULL);
		ASSERT(m_pGroupItem != NULL);
#ifdef _DEBUG
		if (m_pGroupItem->m_pSObj == NULL)
			{
			TRACE(TEXT("COXGrpCursor::operator const COXSPtr<T>& : Using a not yet assigned group item, supplying a smart NULL pointer\n"));
			// Do not throw exception here, will be thrown if m_pSObj itself is dereferenced
			}
#endif // _DEBUG
		
		return m_pGroupItem->m_pSObj;
		}

	const COXSPtr<T>& operator->();
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Dereference operator

    T& operator*() const;
		// throw(CMemoryException);
    // --- In  : 
	// --- Out : 
	// --- Returns : The smart element pointed to
	// --- Effect : Dereference operator

	COXGrpCursor& operator=(COXSPtr<T> pSObj);
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Assignment operator
	//				Assigns a pointer to this cursor position within the group

	virtual ~COXGrpCursor();
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Destructor

protected:
	COXGrpCursor(COXSmartGrp<T, G_KEY, G_ARG_KEY>* pSmartGroup, 
		COXGrpItem<T, G_KEY, G_ARG_KEY>* pGroupItem, BOOL bAddressedByKey);
private:
};

// Template implementation
#include "OXGrpCrsr.inl"

#endif // __OXGRPCRSR_H__
// ==========================================================================
