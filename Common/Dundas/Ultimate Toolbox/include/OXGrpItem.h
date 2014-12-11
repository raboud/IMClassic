// ==========================================================================
// 						Class Specification : COXGrpItem
// ==========================================================================

// Header file : OXGrpItem.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from 

//	NO	Is a CWnd              
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class is used to represent one item in the smart group

// Remark:

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXGRPITEM_H__
#define __OXGRPITEM_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


template <class T> class COXSPtr;
template <class T, class G_KEY, class G_ARG_KEY> class COXSmartGrp;
template <class T, class G_KEY, class G_ARG_KEY> class COXBrilliantGrp;
template <class T, class G_KEY, class G_ARG_KEY> class COXGrpItem;
template <class T, class G_KEY, class G_ARG_KEY> class COXGrpCursor;

template <class T, class G_KEY, class G_ARG_KEY> 
class OX_CLASS_DECL COXGrpItem
{
friend class COXSmartGrp<T, G_KEY, G_ARG_KEY>;
friend class COXBrilliantGrp<T, G_KEY, G_ARG_KEY>;
friend class COXGrpCursor<T, G_KEY, G_ARG_KEY>;
// Data members -------------------------------------------------------------
public:
protected:
	COXSPtr<T> m_pSObj;
	G_KEY* 	m_pKey;
	Index m_possibleArrayIndex;

private:
	
// Member functions ---------------------------------------------------------
public:
protected:
	COXGrpItem(const COXSPtr<T>& pSObj, Index possibleArrayIndex);
	COXGrpItem(const COXGrpItem<T, G_KEY, G_ARG_KEY>& grpItem);
	virtual ~COXGrpItem();
private:
};

// Template implementation
#include "OXGrpItem.inl"

#endif // __OXGRPITEM_H__
// ==========================================================================
