// ==========================================================================
// 						Class Implementation : COXMapiException
// ==========================================================================

// Source file : oxmapiex.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxmapiex.h"	// class specification

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( COXMapiException, CObject );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:
COXMapiException::COXMapiException( DWORD dwEc )
	{
	m_dwErrorCode = dwEc;
	}
	
// protected:

// private:

// ==========================================================================
