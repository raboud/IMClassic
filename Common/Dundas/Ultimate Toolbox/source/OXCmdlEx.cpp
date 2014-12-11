// ==========================================================================
// 						Class Implementation : COXCommandLineException
// ==========================================================================

// Source file : oxcmdlex.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxcmdlex.h"	// class specification
#include "oxcmdopt.h"

#ifdef WIN32
	#include "wincon.h"		// for AllocConsole call	
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( COXCommandLineException, CException );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:
COXCommandLineException::COXCommandLineException(LPCTSTR pszcError,
												 COXCommandOptions* pCmdOpt /* = NULL */)
	{
	if (pCmdOpt != NULL)
		{
		ASSERT(pCmdOpt->IsKindOf(RUNTIME_CLASS(COXCommandOptions)));
		m_sErrMsg = pCmdOpt->Usage(pszcError);
		}
	else
		m_sErrMsg = pszcError;
	}

BOOL COXCommandLineException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
											  UINT* /* pnHelpContext */ /* = NULL */)
	{
	ASSERT(lpszError != NULL && AfxIsValidString(lpszError, nMaxError));

	lstrcpyn(lpszError, m_sErrMsg, nMaxError);

	return TRUE;
	}

BOOL COXCommandLineException::WriteToStdErr()
	{            
#ifdef WIN32	
	DWORD written;
	HANDLE StdErr = GetStdHandle(STD_ERROR_HANDLE);
	if (StdErr == INVALID_HANDLE_VALUE)
		{
		if (AllocConsole())
			StdErr = GetStdHandle(STD_ERROR_HANDLE);
		else
			return FALSE;
		}

	if (StdErr != INVALID_HANDLE_VALUE)
		{
		WriteFile(StdErr, m_sErrMsg, m_sErrMsg.GetLength(), &written, 0);
		return TRUE;
		}

	return FALSE;
#else
	fprintf(stderr, m_sErrMsg);      
    return TRUE;  
#endif	
	}

// protected:

// private:

// ==========================================================================
