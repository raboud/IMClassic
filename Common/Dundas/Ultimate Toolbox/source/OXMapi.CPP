// ==========================================================================
// 						Class Implementation : COXMapi
// ==========================================================================

// Source file : oxmapifl.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxmapi.h"	// class specification

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( COXMapi, CObject );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

tLogonProc			COXMapi::lpfnMAPILogon;
tLogoffProc			COXMapi::lpfnMAPILogoff;
tSendMailProc		COXMapi::lpfnMAPISendMail;
tSendDocumentsProc	COXMapi::lpfnMAPISendDocuments;
tFindNextProc		COXMapi::lpfnMAPIFindNext;
tReadMailProc		COXMapi::lpfnMAPIReadMail;
tSaveMailProc		COXMapi::lpfnMAPISaveMail;
tDeleteMailProc		COXMapi::lpfnMAPIDeleteMail;
tAddressProc		COXMapi::lpfnMAPIAddress;
tResolveNameProc	COXMapi::lpfnMAPIResolveName;
tDetailsProc		COXMapi::lpfnMAPIDetails;
tFreeBufferProc		COXMapi::lpfnMAPIFreeBuffer;

HINSTANCE			COXMapi::hinstMAPIdll;
UINT 				COXMapi::m_COXMapi_InstanceCount = 0;

// Data members -------------------------------------------------------------
// protected:

// private:
	//	CWnd* m_pParent;			
	// --- The parent of any user interface used by MAPI
	//	LHANDLE	m_lhSession;
	// --- The MAPI session handle
	
// Member functions ---------------------------------------------------------
// public:

COXMapi::COXMapi()
	{
	ASSERT_VALID( this );
	
	m_pParent = NULL;
	m_lhSession = NULL;
	if ( !m_COXMapi_InstanceCount )
		{
		DWORD err;
		
		if ( ( err = InItMAPI() ) != 0  )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );	
			}
		
		}
	
	++m_COXMapi_InstanceCount;
	}



#pragma warning ( disable : 4769 )
COXMapi::~COXMapi()
	{
	Logoff(0, NULL);

	--m_COXMapi_InstanceCount;
	if ( m_COXMapi_InstanceCount == 0 )
		{
		DeInItMAPI();
		}	
	}

#pragma warning ( disable : 4769 )
DWORD COXMapi::Logon( CString Name, DWORD dwFlags, CString Password, CWnd* pParent )
	{
	ULONG retval;

	if (m_lhSession != NULL)
		return SESSION_ALREADY_OPEN;

    m_pParent = pParent;
    
	if ( Password.GetLength() == 0 )
		{
		retval = (*lpfnMAPILogon)( ((m_pParent != NULL) ? (ULONG)m_pParent->m_hWnd : NULL),
									(LPSTR)Name.GetBuffer(Name.GetLength()),
									0L, (FLAGS)dwFlags, 0L, &m_lhSession );
		}
	else
		{
		retval = (*lpfnMAPILogon)( ((m_pParent != NULL) ? (ULONG)m_pParent->m_hWnd : NULL),
									(LPSTR)Name.GetBuffer(Name.GetLength()),
							   		(LPSTR)Password.GetBuffer(Password.GetLength()), 
							   		(FLAGS)dwFlags, 0L, &m_lhSession );
		Password.ReleaseBuffer();
		}
	
	Name.ReleaseBuffer();
	
	if ( retval != SUCCESS_SUCCESS )
		{
		m_lhSession = NULL;
		}
	
	return( (DWORD)retval );
	}

DWORD COXMapi::Logoff( DWORD dwFlags, CWnd* pParent )
	{
	ULONG retval;

	if (m_lhSession == NULL)
		return SUCCESS_SUCCESS;

	retval = (*lpfnMAPILogoff)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
			 (FLAGS)dwFlags, 0L );
	
	if ( retval == SUCCESS_SUCCESS )
		{
		m_lhSession = NULL;
		}

	return( (DWORD)retval ); 
	}

DWORD COXMapi::Address( CString Caption, DWORD dwEditFields, 
					  CString Labels, COXMapiRecipient& Recip,
					  DWORD dwFlags, COXMapiRecipient& NewRecip, CWnd *pParent /*= NULL*/ )
	{
	ASSERT_VALID( this );
	
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}
	
	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}
	
	ULONG retval;
	lpMapiRecipDesc pNewRecips;
	ULONG		    ulNewRecipCount;
	
	//Make srings null terminated.
	
	NewRecip.Flush();
	
	retval = (*lpfnMAPIAddress)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								 (LPSTR)Caption.GetBuffer(Caption.GetLength()), (ULONG)dwEditFields,
								 (LPSTR)Labels.GetBuffer(Labels.GetLength()), (ULONG)Recip.GetSize(),
								 Recip.GetPointer(), (FLAGS)dwFlags, 0L,
								 &ulNewRecipCount, &pNewRecips );
	Caption.ReleaseBuffer();
	Labels.ReleaseBuffer();
	
	if ( retval == SUCCESS_SUCCESS && pNewRecips == NULL )
		{
		return( (DWORD)retval );
		}

	if ( retval != SUCCESS_SUCCESS )
		{
		FreeBuffer ( pNewRecips );
		return( (DWORD)retval );
		}

	if ( ulNewRecipCount == 0 )
		{
		FreeBuffer ( pNewRecips );
		return( (DWORD)retval );
		}
	
	retval = NewRecip.CopyFromPointer( pNewRecips, ulNewRecipCount );
	if ( retval != SUCCESS_SUCCESS )
		{
		FreeBuffer ( pNewRecips );
		return( (DWORD)retval );
		}

	FreeBuffer ( pNewRecips );
	return( (DWORD)retval );	
	}

DWORD COXMapi::DeleteMail( CString& MessageID, CWnd *pParent /*= NULL*/ )
	{	
	ASSERT_VALID( this );
	
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}

	ULONG retval;
	
	retval = (*lpfnMAPIDeleteMail)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								    (LPSTR)MessageID.GetBuffer(MessageID.GetLength()),
								    0L, 0L );
	
	MessageID.ReleaseBuffer();
	return ( (DWORD)retval );
	}

DWORD COXMapi::Details( COXMapiRecipient& Recip, DWORD dwFlags, CWnd *pParent /*= NULL*/ )
	{	ASSERT_VALID( this );

	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}
	
	ULONG retval;
	retval = (*lpfnMAPIDetails)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								 Recip.GetPointer(), (FLAGS)dwFlags, 0L );
	return ( (DWORD)retval );
	}
	
DWORD COXMapi::FindNext( CString& MessageID, CString& MessageType,
					   DWORD dwFlags, CString& SeedMessageID, CWnd *pParent /*= NULL*/ )
	{
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}

	ULONG retval;
	
	retval = (*lpfnMAPIFindNext)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								  (LPSTR)MessageType.GetBuffer(MessageType.GetLength()),
								  (LPSTR)SeedMessageID.GetBuffer(SeedMessageID.GetLength()),
								  (FLAGS)dwFlags, 0L,
								  (LPSTR)MessageID.GetBuffer(512) );
	MessageType.ReleaseBuffer();
	SeedMessageID.ReleaseBuffer();
	MessageID.ReleaseBuffer();
	return( (DWORD)retval );
	}

DWORD COXMapi::ReadMail ( CString& MessageID, DWORD dwFlags, COXMapiMessage& MessageDetails, CWnd *pParent /*= NULL*/ )
	{
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}

	ULONG retval;
	lpMapiMessage lpMessage;
	MessageDetails.Flush();
	
	retval = (*lpfnMAPIReadMail)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								  (LPSTR)MessageID.GetBuffer(MessageID.GetLength() ),
								  (FLAGS)dwFlags, 0L, &lpMessage );
	
	MessageID.ReleaseBuffer();
	if ( retval != SUCCESS_SUCCESS )
		{
		FreeBuffer( lpMessage ); 
		return( (DWORD)retval );
		}	

	retval = MessageDetails.CopyFromPointer( lpMessage );

	FreeBuffer( lpMessage );
	return( (DWORD)retval );
	}


DWORD COXMapi::ResolveName( CString& Name, DWORD dwFlags, COXMapiRecipient& RecipInfo, CWnd *pParent /*= NULL*/ )
	{
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}

	if ( Name.GetLength() == 0 )
		{
		return( MAPI_E_INVALID_RECIPS );
		}

	ULONG retval;
	lpMapiRecipDesc lpRecip;
	
	RecipInfo.Flush();
	
	retval = (*lpfnMAPIResolveName)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
									 (LPSTR)Name.GetBuffer( Name.GetLength() ),
									 (ULONG)dwFlags, 0L, &lpRecip );
	Name.ReleaseBuffer();
	
	if ( retval != SUCCESS_SUCCESS )
		{
		FreeBuffer( lpRecip );
		return( (DWORD)retval );
		}
	
	retval = (ULONG)RecipInfo.CopyFromPointer( lpRecip, 1 );

	FreeBuffer( lpRecip );
	return( (DWORD)retval );
	}

DWORD COXMapi::SaveMail( COXMapiMessage& MessageDetails, DWORD dwFlags, CString& MessageID, CWnd *pParent /*= NULL*/ )
	{
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}

	ULONG retval;
	
	retval = (*lpfnMAPISaveMail)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								  MessageDetails.GetPointer(), (FLAGS)dwFlags,
								  0L, (LPSTR)MessageID.GetBuffer(MessageID.GetLength()) );
	MessageID.ReleaseBuffer();
	
	return( (DWORD)retval );
	}
	
DWORD COXMapi::SendMail( COXMapiMessage& MessageDetails, DWORD dwFlags, CWnd *pParent /*= NULL*/ )
	{
	if ( pParent == NULL )
		{
		pParent = m_pParent;
		}

	if ( m_lhSession == NULL )
		{
		return( MAPI_E_INVALID_SESSION );
		}

	ULONG retval;
	
	retval = (*lpfnMAPISendMail)( m_lhSession, ((pParent != NULL) ? (ULONG)pParent->m_hWnd : NULL),
								  MessageDetails.GetPointer(),
								  (FLAGS)dwFlags, 0L );
	return( (DWORD)retval );
	}

#ifdef _DEBUG

void COXMapi::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXMapi::Dump( CDumpContext& dc ) const
	{
	CObject::Dump( dc );
	
	dc << " Dumping a COXMapi object \n";
	dc << "#############################\n";
	if ( m_lhSession == NULL )
		{
		dc << " COXMapi is empty \n";
		return;
		}
	
	dc << " Session Handle is " << m_lhSession	 << "\n";

	}
#endif  //_DEBUG
	
// protected:

// private:

UINT COXMapi::InItMAPI()
	{
#ifndef _WIN32
	if ((hinstMAPIdll = ::LoadLibrary("MAPI.DLL")) < (HINSTANCE)32)
    	return(ERR_LOAD_LIB);
	if ( ( lpfnMAPILogon = (tLogonProc)GetProcAddress(hinstMAPIdll,"MAPILogon") ) == NULL )
		return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPILogoff = (tLogoffProc)GetProcAddress(hinstMAPIdll,"MAPILogOff") ) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPISendMail = (tSendMailProc)GetProcAddress(hinstMAPIdll,"MAPISendMail")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPISendDocuments = (tSendDocumentsProc)GetProcAddress(hinstMAPIdll,"MAPISendDocuments")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPIFindNext = (tFindNextProc)GetProcAddress(hinstMAPIdll,"MAPIFindNext")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPIReadMail = (tReadMailProc)GetProcAddress(hinstMAPIdll,"MAPIReadMail")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPISaveMail = (tSaveMailProc)GetProcAddress(hinstMAPIdll,"MAPISaveMail")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPIDeleteMail = (tDeleteMailProc)GetProcAddress(hinstMAPIdll,"MAPIDeleteMail")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPIFreeBuffer = (tFreeBufferProc)GetProcAddress(hinstMAPIdll,"MAPIFreeBuffer")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ((lpfnMAPIAddress = (tAddressProc)GetProcAddress(hinstMAPIdll,"MAPIAddress")) == NULL)
    	return(ERR_LOAD_FUNC);

	if ( ( lpfnMAPIDetails = (tDetailsProc)GetProcAddress(hinstMAPIdll,"MAPIDetails")) == NULL)
    	return(ERR_LOAD_FUNC);
		
	if ( ( lpfnMAPIResolveName= (tResolveNameProc)GetProcAddress(hinstMAPIdll,"MAPIResolveName")) == NULL)
    	return(ERR_LOAD_FUNC);
#else
	if ((hinstMAPIdll = ::LoadLibrary(_T("MAPI32.DLL"))) == NULL )	
		return(GetLastError());
	if ( ( lpfnMAPILogon = (tLogonProc)GetProcAddress(hinstMAPIdll,"MAPILogon") ) == NULL )
		return(GetLastError());

	if ( ( lpfnMAPILogoff = (tLogoffProc)GetProcAddress(hinstMAPIdll,"MAPILogoff") ) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPISendMail = (tSendMailProc)GetProcAddress(hinstMAPIdll,"MAPISendMail")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPISendDocuments = (tSendDocumentsProc)GetProcAddress(hinstMAPIdll,"MAPISendDocuments")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPIFindNext = (tFindNextProc)GetProcAddress(hinstMAPIdll,"MAPIFindNext")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPIReadMail = (tReadMailProc)GetProcAddress(hinstMAPIdll,"MAPIReadMail")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPISaveMail = (tSaveMailProc)GetProcAddress(hinstMAPIdll,"MAPISaveMail")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPIDeleteMail = (tDeleteMailProc)GetProcAddress(hinstMAPIdll,"MAPIDeleteMail")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPIFreeBuffer = (tFreeBufferProc)GetProcAddress(hinstMAPIdll,"MAPIFreeBuffer")) == NULL)
    	return(GetLastError());

	if ((lpfnMAPIAddress = (tAddressProc)GetProcAddress(hinstMAPIdll,"MAPIAddress")) == NULL)
    	return(GetLastError());

	if ( ( lpfnMAPIDetails = (tDetailsProc)GetProcAddress(hinstMAPIdll,"MAPIDetails")) == NULL)
    	return(GetLastError());
		
	if ( ( lpfnMAPIResolveName= (tResolveNameProc)GetProcAddress(hinstMAPIdll,"MAPIResolveName")) == NULL)
    	return(GetLastError());
#endif //_WIN32	
	
	return(0);
	}


void COXMapi::DeInItMAPI()
	{
	lpfnMAPILogon = NULL;
	lpfnMAPILogoff= NULL;
	lpfnMAPISendMail= NULL;
	lpfnMAPISendDocuments= NULL;
	lpfnMAPIFindNext= NULL;
	lpfnMAPIReadMail= NULL;
	lpfnMAPISaveMail= NULL;
	lpfnMAPIDeleteMail= NULL;
	lpfnMAPIFreeBuffer = NULL;
	lpfnMAPIAddress= NULL;
	lpfnMAPIDetails = NULL;
	lpfnMAPIResolveName = NULL;

	::FreeLibrary(hinstMAPIdll);
	}	

// ==========================================================================
