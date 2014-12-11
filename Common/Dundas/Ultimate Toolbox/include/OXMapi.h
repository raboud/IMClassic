// ==========================================================================
// 							Class Specification : COXMapi
// ==========================================================================

// Header file : oxmapi.h

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
//	This class encapsulates the Simple Mapi API
//	Each instance of the class will do a logon  and if the logon
//  fails all other functions are disabled.


// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __MAPI_H__
#define __MAPI_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#ifndef _WIN32

#ifndef _M_I86LM		// test if large model.
	#error The MAPI classes need to be used with a large model /AL 
#endif

#endif // _WIN32

#include "oxmapims.h"


	/////////////////////////////////////////////////////////////////////////////
	//	typedef for static Mapi functions
	//
	typedef ULONG (WINAPI *tLogonProc)(ULONG, LPSTR, LPSTR, FLAGS, ULONG, LPLHANDLE);

	typedef ULONG (WINAPI *tLogoffProc)(LHANDLE, ULONG, FLAGS,ULONG);

	typedef ULONG (WINAPI *tSendMailProc)(LHANDLE, ULONG, lpMapiMessage, FLAGS,
	                                     ULONG);

	typedef ULONG (WINAPI *tSendDocumentsProc)(ULONG, LPSTR, LPSTR, LPSTR, ULONG);

	typedef ULONG (WINAPI *tFindNextProc)(LHANDLE, ULONG, LPSTR, LPSTR, FLAGS,
	                                     ULONG, LPSTR);

	typedef ULONG (WINAPI *tReadMailProc)(LHANDLE, ULONG, LPSTR, FLAGS, ULONG,
	                                     lpMapiMessage FAR *);

	typedef ULONG (WINAPI *tSaveMailProc)(LHANDLE, ULONG, lpMapiMessage, FLAGS,
	                                     ULONG, LPSTR);

	typedef ULONG (WINAPI *tDeleteMailProc)(LHANDLE, ULONG, LPSTR, FLAGS, ULONG);

	typedef ULONG (WINAPI *tFreeBufferProc)(LPVOID);

	typedef ULONG (WINAPI *tAddressProc)(LHANDLE, ULONG, LPSTR, ULONG, LPSTR,
						                ULONG, lpMapiRecipDesc, FLAGS, ULONG,
	                                    LPULONG, lpMapiRecipDesc FAR *);
  
	typedef ULONG (WINAPI *tDetailsProc)(LHANDLE, ULONG,lpMapiRecipDesc, FLAGS,
	                                    ULONG);

	typedef ULONG (WINAPI *tResolveNameProc)(LHANDLE, ULONG, LPSTR, FLAGS,
							                ULONG, lpMapiRecipDesc FAR *);
	//
	///////////////////////////////////////////////////////////////////////


class OX_CLASS_DECL COXMapi : public CObject
{
DECLARE_DYNAMIC( COXMapi );
    
// Data members -------------------------------------------------------------
public:
	
protected:
    
private:
	CWnd*						m_pParent;
	LHANDLE						m_lhSession;

	static UINT					m_COXMapi_InstanceCount;
	
	static HINSTANCE			hinstMAPIdll;

	static tLogonProc			lpfnMAPILogon;
	static tLogoffProc			lpfnMAPILogoff;
	static tSendMailProc		lpfnMAPISendMail;
	static tSendDocumentsProc	lpfnMAPISendDocuments;
	static tFindNextProc		lpfnMAPIFindNext;
	static tReadMailProc		lpfnMAPIReadMail;
	static tSaveMailProc		lpfnMAPISaveMail;
	static tDeleteMailProc		lpfnMAPIDeleteMail;
	static tAddressProc			lpfnMAPIAddress;
	static tResolveNameProc		lpfnMAPIResolveName;
	static tDetailsProc			lpfnMAPIDetails;
	static tFreeBufferProc		lpfnMAPIFreeBuffer;

// Member functions ---------------------------------------------------------
public:

	COXMapi();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	DWORD Logon( CString Name, DWORD dwFlags, CString Password, CWnd* pParent );
	// --- In  : Name : see MAPI technical reference for MapiLogon, the lpszProfileName param
	//			 dwFlags : see MAPI technical reference for MapiLogon, the flFlags param
	//			 Password : see MAPI technical reference for MapiLogon, the lpszPassword param
	//			 pParent : see MAPI technical reference for MapiLogon, the ulUIParam param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h> or SESSION_ALREADY_OPEN
	// --- Effect : Logs on to a MAIL session, see MAPI technical reference for flag details

	DWORD Logoff( DWORD dwFlags, CWnd* pParent );
	// --- In  :  dwFlags : see MAPI technical reference for MapiLogoff, the flFlags param
	//			 pParent : see MAPI technical reference for MapiLogoff, the ulUIParam param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : Logs off a MAIL session, see MAPI technical reference for flag details

	
	inline DWORD FreeBuffer( LPVOID p )
	// --- In  : p : see MAPI technical reference for MapiFreeBuffer, the pv param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : used to free memory allocated by any mapi call
		{	
		ASSERT_VALID( this );
		if ( p == NULL )
			return SUCCESS_SUCCESS;
	#ifdef _DEBUG
		DWORD retval;
		retval = (DWORD)(*lpfnMAPIFreeBuffer)( (LPVOID) p );
		return( retval );
	#else
		return ( (DWORD)(*lpfnMAPIFreeBuffer)( (LPVOID) p ) );
	#endif
		}	

	DWORD Address( CString Caption, DWORD dwEditFields, 
				   CString Labels, COXMapiRecipient& Recip,
	 			   DWORD dwFlags, COXMapiRecipient& NewRecip,
	 			   CWnd* pParent = NULL );
	// --- In  : lpszCaption : see MAPI technical reference for MapiAddress, the lpszProfileName param
	//			 dwEditFields : see MAPI technical reference for MapiAddress, the nEditFields param
	//			 Labels : see MAPI technical reference for MapiAddress, the lpszLabels param
	//			 dwFlags : see MAPI technical reference for MapiAddress, the flFlags param
	//			 pParent : see MAPI technical reference for MapiAddress, the ulUIParam param
	//			 Recip : Recip object will remain unchanged
	//			 NewRecip : Any info in the COXMapiRecipient object NewRecip will be lost
	// --- Out : 
	// --- Returns : return values defined in <mapi.h> or any of the errors returned
	//				 by the COXMapiRecipient, COXMapiFile, or COXMapiMessage member functions
	// --- Effect : creates or modifies a set of address list entries. 
	
	DWORD DeleteMail( CString& MessageID, CWnd* pParent = NULL );
	// --- In  : MessageID : see MAPI technical reference for MapiDeleteMail, the pszMessageID param
	//						 MessageID is returned by COXMapi::FindNext or COXMapi::SaveMail
	//			 pParent : see MAPI technical reference for MapiDeleteMail, the ulUIParam param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : Deletes a MAPI mail
		
	DWORD Details( COXMapiRecipient& Recip, DWORD dwFlags, CWnd* pParent = NULL );
	// --- In  : Recip : see MAPI technical reference for MapiDetails, the lpRecip param
	//					 Input parameter specifying a pointer to the recipient for which
	//					 details are to be displayed
	//			 dwFlags : see MAPI technical reference for MapiDetails, the flFlags param
	//			 pParent : see MAPI technical reference for MapiDetails, the ulUIParam param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : Dis^lays details for a recipient
	
	DWORD FindNext( CString& MessageID, CString& MessageType,
					DWORD dwFlags, CString& SeedMessageID, CWnd* pParent = NULL );
	// --- In  : MessageType : see MAPI technical reference for MapiFindNext, the lpszMessageType param
	//			 dwFlags : see MAPI technical reference for MapiFindNext, the flFlags param
	//			 SeedMessageID : see MAPI technical reference for MapiFindNext, the lpszSeedMessageID param
	//			 pParent : see MAPI technical reference for MapiFindNext, the ulUIParam param
	// --- Out : MessageID
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : retrieves the next (or first) message identifier of a specified type of incoming message. 
	
	DWORD ReadMail( CString& MessageID, DWORD dwFlags, COXMapiMessage& Message, CWnd* pParent = NULL );
	// --- In  : MessageID : see MAPI technical reference for MapiReadMail, the lpszName param
	//			 dwFlags : see MAPI technical reference for MapiReadMail, the flFlags param
	//			 Message : see MAPI technical reference for MapiReadMail, the *lppMessage param
	//			 pParent : see MAPI technical reference for MapiReadMail, the ulUIParam param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : retrieves a message for reading. 
	
	DWORD ResolveName( CString& Name, DWORD dwFlags, COXMapiRecipient& RecipInfo, CWnd* pParent = NULL );
	// --- In  : Name : see MAPI technical reference for MapiResolveName, the lpszProfileName param
	//			 dwFlags : see MAPI technical reference for MapiResolveName, the flFlags param
	//			 pParent : see MAPI technical reference for MapiResolveName, the ulUIParam param
	// --- Out : RecipInfo : a recipient object if the resolution results in a single match.
	//						 The recipient structure contains the resolved name and related
	//						 information
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : transforms a message recipient's name as entered by a user to an unambiguous address list entry.
	
	DWORD SaveMail( COXMapiMessage& MessageDetails, DWORD dwFlags, CString& MessageID, CWnd* pParent = NULL );
	// --- In  : MessageDetails : see MAPI technical reference for MapiSaveMail, the lpMessage param
	//			 dwFlags : see MAPI technical reference for MapiSaveMail, the flFlags param
	//			 MessageID : see MAPI technical reference for MapiSaveMail, the lpszMessageID param
	//			 pParent : see MAPI technical reference for MapiSaveMail, the ulUIParam param
	// --- Out : MessageID : see MAPI technical reference for MapiSaveMail, the lpszMessageID
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : saves a message into the message store. 
	
	DWORD SendMail( COXMapiMessage& MessageDetails, DWORD dwFlags = 0, CWnd* pParent = NULL );
	// --- In  : MessageDetails : see MAPI technical reference for MapiSendMail, the lpszProfileName param
	//			 dwFlags : see MAPI technical reference for MapiSendMail, the flFlags param
	//			 pParent : see MAPI technical reference for MapiSendMail, the ulUIParam param
	// --- Out : 
	// --- Returns : return values defined in <mapi.h>
	// --- Effect : sends a message.

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXMapi();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:      

private:
	UINT InItMAPI();
	void DeInItMAPI();
		
};

#endif
// ==========================================================================
