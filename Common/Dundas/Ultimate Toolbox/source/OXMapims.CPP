// ==========================================================================
// 						Class Implementation : COXMapiMessage
// ==========================================================================

// Source file : oxmapims.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxmapims.h"	// class specification

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL( COXMapiMessage, CObject, 2 );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	// lpMapiMessage	m_pMapiMessage;
	// --- The pointer to the MapiMessage structure
	// COXMapiRecip	m_Orig
	// --- The originator of the Mapi message
	// COXMapiRecip m_Recip
	// --- The recipients of the Mapi message
	// COXMapiFile		m_File;
	// --- The attachments of the Mapi message

	
// Member functions ---------------------------------------------------------
// public:

COXMapiMessage::COXMapiMessage()
	{
	ASSERT_VALID( this );
	DWORD err;
	
	m_pMapiMessage = NULL;
	if ( ( err = CreatePointer() ) != SUCCESS_SUCCESS )
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );
		}
	}

COXMapiMessage::COXMapiMessage( COXMapiMessage& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	
	DWORD err;
	
	m_pMapiMessage = NULL;
	
	if ( ( err = CopyFromPointer( b.GetPointer() ) ) != SUCCESS_SUCCESS )
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );
		}
	}

COXMapiMessage::~COXMapiMessage()
	{
	ASSERT_VALID( this );
	Flush();
	}

void COXMapiMessage::Flush()
	{
	ASSERT_VALID( this );
	if ( m_pMapiMessage != NULL )
		{
		delete m_pMapiMessage->lpszSubject;
		m_pMapiMessage->lpszSubject = NULL;
		
		delete m_pMapiMessage->lpszNoteText;
		m_pMapiMessage->lpszNoteText = NULL;
		
		delete m_pMapiMessage->lpszMessageType;
		m_pMapiMessage->lpszMessageType = NULL;
		
		delete m_pMapiMessage->lpszDateReceived;
		m_pMapiMessage->lpszDateReceived = NULL;
		
		delete m_pMapiMessage->lpszConversationID;
		m_pMapiMessage->lpszConversationID = NULL;

		delete[] m_pMapiMessage;
		m_pMapiMessage = NULL;
		m_Orig.Flush();
		m_Recip.Flush();
		m_File.Flush();
		}
	}

DWORD COXMapiMessage::CreatePointer()
	// --- In  : 
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_ALREADY_THERE, or MEMORY_ERROR_ON_NEW
	// --- Effect : allocates memory for a MapiMessage structure
	//				and sets contents to NULL
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		m_pMapiMessage = new MapiMessage;
		if ( m_pMapiMessage == NULL )
			{
			return( MEMORY_ERROR_ON_NEW );
			}
		
		_fmemset( m_pMapiMessage, NULL, sizeof( MapiMessage ) );
		}
	else
		{
		return( POINTER_ALREADY_THERE );		
		}
	
	return( SUCCESS_SUCCESS );
	}		

DWORD COXMapiMessage::CopyFromPointer( lpMapiMessage pMessage )
	// --- In  : pMessage : pointer to the MapiMessage struct
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_ALREADY_THERE, or MEMORY_ERROR_ON_NEW
	// --- Effect : initialises the class with a pointer pMessage.
	{
	ASSERT_VALID( this );
	DWORD retval;
	
	if ( pMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	if ( m_pMapiMessage != NULL )
		{
		return( POINTER_ALREADY_THERE );		
		}
	
	if ( ( retval = CreatePointer() ) != SUCCESS_SUCCESS )
		{
		return( retval );
		}
			
	if ( ( retval = SetSubject( pMessage->lpszSubject ) ) != SUCCESS_SUCCESS )
		{
		delete m_pMapiMessage;
		m_pMapiMessage = NULL;
		return( retval );		
		}
	
	if ( ( retval = SetNoteText( pMessage->lpszNoteText ) ) != SUCCESS_SUCCESS )
		{
		SetSubject( "" );
		delete m_pMapiMessage;
		m_pMapiMessage = NULL;
		return( retval );		
		}

	if ( ( retval = SetMessageType( pMessage->lpszMessageType ) ) != SUCCESS_SUCCESS )
		{
		SetSubject( "" );
		SetNoteText( "" );
		delete m_pMapiMessage;
		m_pMapiMessage = NULL;
		
		return( retval );		
		}
	
	if ( pMessage->lpszDateReceived != NULL ) // test if the is something there to copy.
		{
		m_pMapiMessage->lpszDateReceived = new char[ _fstrlen( pMessage->lpszDateReceived ) + 1 ];
		if ( m_pMapiMessage->lpszDateReceived == NULL )
			{
			SetSubject( "" );
			SetNoteText( "" );
			SetMessageType( "" );
			delete m_pMapiMessage;
			m_pMapiMessage = NULL;
		
			return( MEMORY_ERROR_ON_NEW );		
			}

		_fstrcpy( m_pMapiMessage->lpszDateReceived, pMessage->lpszDateReceived );
		}
	
	if ( ( retval = SetConversationID( pMessage->lpszConversationID ) ) != SUCCESS_SUCCESS )
		{
		SetSubject( "" );
		SetNoteText( "" );
		delete m_pMapiMessage->lpszDateReceived;
		delete m_pMapiMessage;
		m_pMapiMessage = NULL;
		
		return( retval );		
		}
	
	m_pMapiMessage->flFlags = pMessage->flFlags;
	
	if ( ( retval = m_Orig.CopyFromPointer( pMessage->lpOriginator, 1 ) ) != SUCCESS_SUCCESS )
		{
		SetSubject( "" );
		SetNoteText( "" );
		delete m_pMapiMessage->lpszDateReceived;
		SetConversationID( "" );
		delete m_pMapiMessage;
		m_pMapiMessage = NULL;
		
		return( retval );		
		}
	
	m_pMapiMessage->lpOriginator = m_Orig.GetPointer();
	
	if ( pMessage->nRecipCount > 0 )
		{
		retval = m_Recip.CopyFromPointer( pMessage->lpRecips, pMessage->nRecipCount );
		if ( retval != SUCCESS_SUCCESS )
			{
			SetSubject( "" );
			SetNoteText( "" );
			delete m_pMapiMessage->lpszDateReceived;
			SetConversationID( "" );
			m_Orig.Flush();
			delete m_pMapiMessage;
			m_pMapiMessage = NULL;
			
			return( retval );		
			}
		}
	
	m_pMapiMessage->nRecipCount = m_Recip.GetSize();
	m_pMapiMessage->lpRecips = m_Recip.GetPointer();

	if ( pMessage->nFileCount > 0 )
		{
		retval = m_File.CopyFromPointer( pMessage->lpFiles, pMessage->nFileCount );
		if ( retval != SUCCESS_SUCCESS )
			{
			SetSubject( "" );
			SetNoteText( "" );
			delete m_pMapiMessage->lpszDateReceived;
			SetConversationID( "" );
			m_Orig.Flush();
			m_Recip.Flush();
			delete m_pMapiMessage;
			m_pMapiMessage = NULL;
		
			return( retval );		
			}
		}
	
	m_pMapiMessage->nFileCount = m_File.GetSize();
	m_pMapiMessage->lpFiles = m_File.GetPointer();
	
	m_pMapiMessage->ulReserved = pMessage->ulReserved;
	
	return( SUCCESS_SUCCESS );
	}
	
lpMapiMessage COXMapiMessage::GetPointer()
	// --- In  :
	// --- Out : 
	// --- Returns : gets the pointer to the MapiMessage or NULL
	// --- Effect : 
	{	
	ASSERT_VALID( this );
	return( m_pMapiMessage );
	}

CString COXMapiMessage::GetSubject() 
	{	
	CString sSub;

	if ( m_pMapiMessage == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );

		return "";
		}
	
	sSub = m_pMapiMessage->lpszSubject;
	return( sSub );
	}

DWORD COXMapiMessage::SetSubject( CString Subject )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	// Delete old string if there;
	delete m_pMapiMessage->lpszSubject;
	m_pMapiMessage->lpszSubject = NULL;
		
	if ( Subject.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}

	m_pMapiMessage->lpszSubject = (LPSTR)new char[Subject.GetLength() + 1];
	if ( m_pMapiMessage->lpszSubject == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pMapiMessage->lpszSubject, (LPCSTR)(LPCTSTR)Subject );
	return ( SUCCESS_SUCCESS );
	}			

CString COXMapiMessage::GetNoteText() 
	{
	CString sNote;

	if ( m_pMapiMessage == NULL )
		{
			COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
			THROW( e );
					
			return "";
		}
	
	sNote = m_pMapiMessage->lpszNoteText;
	return( sNote );
	}

DWORD COXMapiMessage::SetNoteText( CString NoteText )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	// Delete old string if there;
	delete m_pMapiMessage->lpszNoteText;
	m_pMapiMessage->lpszNoteText = NULL;
	
	if ( NoteText.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}

	m_pMapiMessage->lpszNoteText = (LPSTR)new char[NoteText.GetLength() + 1];
	if ( m_pMapiMessage->lpszNoteText == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pMapiMessage->lpszNoteText, (LPCSTR)(LPCTSTR)NoteText );
	return ( SUCCESS_SUCCESS );
	}				

CString COXMapiMessage::GetMessageType() 
	{	
	CString sType;

	if ( m_pMapiMessage == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );
					
		return "";
		}
	
	sType = m_pMapiMessage->lpszMessageType;
	return( sType );
	}

DWORD COXMapiMessage::SetMessageType( CString MessageType )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	// Delete old string if there;
	delete m_pMapiMessage->lpszMessageType;
	m_pMapiMessage->lpszMessageType = NULL;
	
	if ( MessageType.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}

	m_pMapiMessage->lpszMessageType = (LPSTR)new char[MessageType.GetLength() + 1];
	if ( m_pMapiMessage->lpszMessageType == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}

	strcpy( m_pMapiMessage->lpszMessageType, (LPCSTR)(LPCTSTR)MessageType );
	return ( SUCCESS_SUCCESS );
	}			

DWORD COXMapiMessage::GetTimeReceived( CTime& RecevTime)
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}

	if ( m_pMapiMessage->lpszDateReceived == NULL )
		{
		return( POINTER_NOT_THERE );
		}
	
	CString tempstring = m_pMapiMessage->lpszDateReceived;

#ifndef _UNICODE
	CTime retval( atoi(tempstring.Mid( 0, 4 )),			// extract year
				  atoi(tempstring.Mid( 5, 2 )),			// extract month
				  atoi(tempstring.Mid( 8, 2 )),			// extract day
				  atoi(tempstring.Mid( 11, 2 )),		// extract hour
				  atoi(tempstring.Mid( 14, 2 )), 0);	// extract minuet
#else
	CTime retval( _wtoi(tempstring.Mid( 0, 4 )),			// extract year
				  _wtoi(tempstring.Mid( 5, 2 )),			// extract month
				  _wtoi(tempstring.Mid( 8, 2 )),			// extract day
				  _wtoi(tempstring.Mid( 11, 2 )),		// extract hour
				  _wtoi(tempstring.Mid( 14, 2 )), 0);	// extract minuet
#endif
	
	RecevTime = retval;
	
	return( SUCCESS_SUCCESS );
	}

DWORD COXMapiMessage::SetTimeReceived( CTime time )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );
		}
	else
		{
		delete m_pMapiMessage->lpszDateReceived;
		
		m_pMapiMessage->lpszDateReceived = new char[17];
		if ( m_pMapiMessage->lpszDateReceived == NULL )
			{
			return( MEMORY_ERROR_ON_NEW );
			}
		
		strcpy( m_pMapiMessage->lpszDateReceived, 
			(LPCSTR)(LPCTSTR)time.Format(_T("%Y/%m/%d %H:%M")) );
		
		return ( SUCCESS_SUCCESS );
		}
	}

CString COXMapiMessage::GetConversationID() 
	{
	CString sID;

	if ( m_pMapiMessage == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );
					
		return "";
		}

	sID = m_pMapiMessage->lpszConversationID;
	return sID;
	}

DWORD COXMapiMessage::SetConversationID( CString ConversationID )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	// Delete old string if there;
	delete m_pMapiMessage->lpszConversationID;
	m_pMapiMessage->lpszConversationID = NULL;
	
	if ( ConversationID.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}

	m_pMapiMessage->lpszConversationID = (LPSTR)new char[ConversationID.GetLength() + 1];
	if ( m_pMapiMessage->lpszConversationID == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pMapiMessage->lpszConversationID, (LPCSTR)(LPCTSTR)ConversationID );
	return ( SUCCESS_SUCCESS );
	}			

COXMapiRecipient& COXMapiMessage::GetOriginator()
	{
	ASSERT_VALID( this );
	
	return( m_Orig );
	}

DWORD COXMapiMessage::SetOriginator( COXMapiRecipient& recip )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiMessage == NULL )
		{
		return ( POINTER_NOT_THERE );
		}

	TRY
		{
		m_Orig = recip;
		}
	CATCH( COXMapiException, e )
		{
		m_pMapiMessage->lpOriginator = NULL;
		return( e->m_dwErrorCode );
		}
	END_CATCH
	
	m_pMapiMessage->lpOriginator = m_Orig.GetPointer();
	return( SUCCESS_SUCCESS );
	}
	
COXMapiRecipient& COXMapiMessage::GetRecips()
	{
	ASSERT_VALID( this );
	
	return( m_Recip );
	}
	
DWORD COXMapiMessage::SetRecips( COXMapiRecipient& Recip )
	{
	ASSERT_VALID( this );
	DWORD retval;
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	retval = m_Recip.CopyFromPointer( Recip.GetPointer(), Recip.GetSize() );
	if ( retval != SUCCESS_SUCCESS )
		{
		return( retval );
		}
	
	m_pMapiMessage->nRecipCount = m_Recip.GetSize();
	m_pMapiMessage->lpRecips = m_Recip.GetPointer();
	
	return( SUCCESS_SUCCESS );
	}

COXMapiFile& COXMapiMessage::GetFiles()
	{
	ASSERT_VALID( this );
	
	return( m_File );
	}
	
DWORD COXMapiMessage::SetFiles( COXMapiFile& File )
	{
	ASSERT_VALID( this );
	DWORD retval;
	
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	retval = m_File.CopyFromPointer( File.GetPointer(), File.GetSize() );
	if ( retval != SUCCESS_SUCCESS )
		{
		return( retval );
		}
	
	m_pMapiMessage->nFileCount = m_File.GetSize();
	m_pMapiMessage->lpFiles = m_File.GetPointer();
	
	return( SUCCESS_SUCCESS );
	}	

COXMapiMessage& COXMapiMessage::operator=( COXMapiMessage& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );

	DWORD err;
	
	// Test if "b"==this
	if ( this == &b )
		{
		return ( *this );
		}
	
    Flush();
	if ( ( err = CopyFromPointer( b.GetPointer() ) ) != SUCCESS_SUCCESS )
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );
		}
	
	return ( *this );
	}

DWORD COXMapiMessage::GetFlags()
	{	
	ASSERT_VALID( this );
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );
		}
	else 
		{
		return( (DWORD)m_pMapiMessage->flFlags );
		}
	}
		
DWORD COXMapiMessage::SetFlags( DWORD dwFlags )
	{	
	ASSERT_VALID( this );
	if ( m_pMapiMessage == NULL )
		{
		return( POINTER_NOT_THERE );
		}
	else
		{
		m_pMapiMessage->flFlags = (ULONG)dwFlags;
		return( SUCCESS_SUCCESS );
		}
	}

CArchive& AFXAPI operator <<( CArchive& ar, COXMapiMessage& message )
	{
	
	CString String;
	
    TRY
		{
		String = message.GetSubject();
    	ar << String;
    
    	String = message.GetNoteText();
    	ar << String;
    
    	String = message.GetMessageType();
    	ar << String;
    
    	CTime time;
		message.GetTimeReceived( time );
		ar << time;
	
		String = message.GetConversationID();
		ar << String;
	
		ar << message.GetFlags();
	
		ar << message.GetOriginator();
	
		ar << message.GetRecips();
	
		ar << message.GetFiles();
		}
	CATCH( CException, e )
		{
		THROW_LAST();
		}
	END_CATCH
	
	return ( ar );
	}

CArchive& AFXAPI operator >>( CArchive& ar, COXMapiMessage& message )
	{
	CString string;
	COXMapiRecipient recip;
	COXMapiFile file;
	DWORD dwFlags;
	
    TRY
		{
		ar >> string;
    	message.SetSubject( string );
    
    	ar >> string;
    	message.SetNoteText( string );
    
    	ar >> string;
    	message.SetMessageType( string );
    
    	CTime time;
		ar >> time;
		message.SetTimeReceived( time );
	
		ar >> string;
		message.SetConversationID( string );
	
		ar >> dwFlags;
		message.SetFlags( dwFlags );
	
		ar >> recip;
		message.SetOriginator( recip );
	
		recip.Flush();
		ar >> recip;
		message.SetRecips( recip );
	
		ar >> file;
		message.SetFiles( file );
		}
	CATCH( CException, e )
		{
		message.Flush();
		THROW_LAST();
		}
	END_CATCH
		
	return ( ar );
	}

//////////////////////////////////////////////////////////
//
#ifdef _DEBUG

void COXMapiMessage::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXMapiMessage::Dump( CDumpContext& dc ) const
	{
	CObject::Dump( dc );
	
	dc << " Dumping a COXMapiMessage object \n";
	dc << "#############################\n";
	if ( m_pMapiMessage == NULL )
		{
		dc << " COXMapiMessage is empty \n";
		return;
		}
	
	dc << " Subject is " << m_pMapiMessage->lpszSubject	 << "\n";
	dc << " NoteText is " << m_pMapiMessage->lpszNoteText	 << "\n";
	dc << " MessageType is " << m_pMapiMessage->lpszMessageType << "\n";
	dc << " Date Received is " << m_pMapiMessage->lpszDateReceived << "\n";
	dc << " ConversationID is " << m_pMapiMessage->lpszConversationID	<< "\n";

	}
#endif  //_DEBUG
	
// protected:

// private:

// ==========================================================================
