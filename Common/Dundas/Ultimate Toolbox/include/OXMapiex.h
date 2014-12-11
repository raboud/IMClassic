// ==========================================================================
// 							Class Specification : COXMapiException
// ==========================================================================

// Header file : oxmapiex.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CException

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates a new exception for MAPI

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __MAPIEXCEPTION_H__
#define __MAPIEXCEPTION_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#ifndef _WIN32

	#ifndef _M_I86LM		// test if large model.
		#error The CMapi classes need to be used with a large model /AL 
	#endif

#else

	#define _fmemset memset
	#define _fstrcpy strcpy
	#define _fstrcat strcat
	#define _fstrlen strlen

#endif // _WIN32

#ifndef __cplusplus
	#error  must be used as a C++ header file
#endif

#include "stdafx.h"


#define ERROR_STRING_OFFSET		3300
#define SESSION_ALREADY_OPEN	95
#define NOT_VALID_POSITION 		96
#define POINTER_NOT_THERE 		97
#define POINTER_ALREADY_THERE 	98
#define MEMORY_ERROR_ON_NEW 	99

#define ERR_LOAD_LIB  0x02
#define ERR_LOAD_FUNC 0x04

class OX_CLASS_DECL COXMapiException : public CException
{
DECLARE_DYNAMIC( COXMapiException )
    
// Data members -------------------------------------------------------------
public:
	DWORD m_dwErrorCode;	

protected:
    
private:

// Member functions ---------------------------------------------------------
public:
    COXMapiException( DWORD dwEc );
		// --- In  : 
		// --- Out : 
		// --- Returns :
		// --- Effect : Contructor of object
		//				It will initialize the internal state

protected:      

private:
		
};

#endif
// ==========================================================================
