// ==========================================================================
// 							Class Specification : COXMapiMessage
// ==========================================================================

// Header file : oxmapims.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates the MapiMessage structure

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __MAPIMSG_H__
#define __MAPIMSG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#ifndef _WIN32

#ifndef _M_I86LM		// test if large model.
	#error The MAPI classes need to be used with a large model /AL 
#endif

#endif // _WIN32

#include <mapi.h>
#include "oxmapiex.h"
#include "oxmapifl.h"
#include "oxmapirc.h"


class OX_CLASS_DECL COXMapiMessage : public CObject
{
DECLARE_SERIAL( COXMapiMessage );

friend class COXMapi;


// Data members -------------------------------------------------------------
public:
	
protected:
    
private:
	lpMapiMessage		m_pMapiMessage;
	COXMapiRecipient	m_Orig, m_Recip;
	COXMapiFile			m_File;

// Member functions ---------------------------------------------------------
public:
	COXMapiMessage();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

    COXMapiMessage( lpMapiMessage pMessage );
	// --- In  : pMessage : pointer to a MapiMessage to initialize from
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state from a MapiMessage pointer
    
	COXMapiMessage( COXMapiMessage& b );
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy constructor Can throw a COXMapiException
	//				It will initialize the internal state

	void Flush();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : deallocates all allocated memory

	DWORD GetFlags();
	// --- In  : 
	// --- Out : 
	// --- Returns : the flags for a mapimessage structure
	// --- Effect : gets the flags for the mapimessage
	//				See MAPI doco for mapimessage flags types.
	
	DWORD SetFlags( DWORD dwNewFlags );
	// --- In  : 
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE, or NOT_VALID_POSITION
	// --- Effect : sets the flags for the mapimessage
	//				See MAPI doco for mapimessage flags types.

    CString GetSubject();
	// --- In  : 
	// --- Out : 
	// --- Returns : the subject of the message
	// --- Effect : gets the subject of the message
	//				can throw a COXMapiException See MAPI doco for more info
		
	DWORD SetSubject( CString Subject );
	// --- In  : Subject : the new subject of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE or MEMORY_ERROR_ON_NEW 
	// --- Effect : sets the subject of the message	struct
	//				See MAPI doco for more info

	CString GetNoteText();
	// --- In  : 
	// --- Out : 
	// --- Returns : the text of the message
	// --- Effect : gets the text of the message
	//				can throw a COXMapiException See MAPI doco for more info
			
	DWORD SetNoteText( CString NoteText );
	// --- In  : NoteText : the new subject of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE or MEMORY_ERROR_ON_NEW 
	// --- Effect : sets the text of the message struct
	//				See MAPI doco for more info

	CString GetMessageType();
	// --- In  : 
	// --- Out : 
	// --- Returns : the type of the message
	// --- Effect : gets the type of the message
	//				can throw a COXMapiException See MAPI doco for more info
	
	DWORD SetMessageType( CString MessageType );
	// --- In  : MessageType : the new type of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE or MEMORY_ERROR_ON_NEW 
	// --- Effect : sets the type of the message
	//				See MAPI doco for more info

	DWORD GetTimeReceived( CTime& retval );
	// --- In  : 
	// --- Out : retval : the receive time of the message
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : gets receive time of the message
	//				See MAPI doco for more info
			
	CString GetConversationID();
	// --- In  : 
	// --- Out : 
	// --- Returns : the conversationID of the message
	// --- Effect : gets the conversationID of the message
	//				can throw a COXMapiException See MAPI doco for more info
		
	DWORD SetConversationID( CString ConversationID );
	// --- In  : MessageType : the new conversationID of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE or MEMORY_ERROR_ON_NEW 
	// --- Effect : sets the conversationID of the message
	//				See MAPI doco for more info

	COXMapiRecipient& GetOriginator();
	// --- In  : 
	// --- Out : 
	// --- Returns : the originator of the message
	// --- Effect : gets the originator of the message

	DWORD SetOriginator( COXMapiRecipient& recip );
	// --- In  : recip : the originator of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : sets the originator of the message
	//				can throw a COXMapiException See MAPI doco for more info

	COXMapiRecipient& GetRecips();
	// --- In  : 
	// --- Out : 
	// --- Returns : the recipients of the message
	// --- Effect : gets the recipients of the message

	DWORD SetRecips( COXMapiRecipient& Recip );
	// --- In  : recip : the recipients of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : sets the recipients of the message
	//				can throw a COXMapiException See MAPI doco for more info
	
	COXMapiFile& GetFiles();	
	// --- In  : 
	// --- Out : 
	// --- Returns : the attachments of the message
	// --- Effect : gets the attachments of the message

	DWORD SetFiles( COXMapiFile& File );
	// --- In  : File : the attachments of the message
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : sets the attachments of the message
	//				can throw a COXMapiException See MAPI doco for more info
	
	COXMapiMessage& operator=( COXMapiMessage& b );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : assignment operator
	//				May throw a COXMapiFileException

	friend OX_API_DECL CArchive& AFXAPI operator <<( CArchive& ar, COXMapiMessage& file );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : piping operator to disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException

    friend OX_API_DECL CArchive& AFXAPI operator >>( CArchive& ar, COXMapiMessage& file );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : piping operator from disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapixception
	        
#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXMapiMessage();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:      

private:
	// Helper functions;
	DWORD SetTimeReceived( CTime time );
	
	DWORD CreatePointer();
	
	DWORD CopyFromPointer( lpMapiMessage pMessage );

	lpMapiMessage GetPointer();
                   
};

OX_API_DECL CArchive& AFXAPI operator <<( CArchive& ar, COXMapiMessage& file );
OX_API_DECL CArchive& AFXAPI operator >>( CArchive& ar, COXMapiMessage& file );


#endif
// ==========================================================================
