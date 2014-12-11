// ==========================================================================
// 						Class Specification : Index
// ==========================================================================

// Header file : OXIndex.h

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
//	This class encapsulates an index in a smart group

// Remark:
//	The index is 1-dimensional for now, but can be extended to
//	 multidimensional by adding extra members and changing the constructor

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXINDEX_H__
#define __OXINDEX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL Index
{
// Data members -------------------------------------------------------------
public:
protected:
	LONG	m_nIndex1;

private:
	
// Member functions ---------------------------------------------------------
public:
	Index(LONG nIndex1 = 0);
	// --- In  : nIndex1 : The index in tha group
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs an index object

	Index(const Index& index);
	// --- In  : index : The index to be copied
	// --- Out : 
	// --- Returns : 
	// --- Effect : Copy constructor

    operator LONG() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Conversion operator

	Index& operator++();
	Index& operator++(int);
	Index& operator--();
	Index& operator--(int);
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This pre- or post-increments or decrements the index

	virtual ~Index();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This destructs the pointer object

protected:

private:
                   
};

#include "OXIndex.inl"

#endif // __OXINDEX_H__
// ==========================================================================
