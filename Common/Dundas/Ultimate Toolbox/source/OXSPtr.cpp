// ==========================================================================
//                     Template Implementation : COXSPtr
// ==========================================================================

// Source file : OXSPtr.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      

/////////////////////////////////////////////////////////////////////////////			  
#include "stdafx.h"
#include "OXSPtr.h"

// //////////////////////////////////////////////////////////////////////////
// Definition of static variables

// Define the only valid COXObjectCreator object
OX_CLASS_DECL COXObjectCreator NEW_OBJECT;

#if defined(_DEBUG) && !defined(DISABLE_SMART_CHECK)
// Use a global object that keeps track of smart pointers and 
// that will be used for debugging purposes
COXSmartWatcher smartWatcher;
#endif

// ==========================================================================
