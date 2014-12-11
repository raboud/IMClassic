// ==========================================================================
// 							Class Specification : COXMapiRecipient
// ==========================================================================

// Header file : oxmapirc.h

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
//	This class encapsulates the MapiRecipDesc structure

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __MAPIRECIPIENT_H__
#define __MAPIRECIPIENT_H__

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


class OX_CLASS_DECL COXMapiRecipient : public CObject
{
DECLARE_SERIAL( COXMapiRecipient );

   	friend class COXMapiMessage;   // needs access to private functions;
   	friend class COXMapi;
    
// Data members -------------------------------------------------------------
public:
	
protected:
    
private:
		lpMapiRecipDesc m_pMapiRecipDesc;			
		lpMapiRecipDesc m_pPosition;
		ULONG 		    m_ulRecipCount;

// Member functions ---------------------------------------------------------
public:
	COXMapiRecipient();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
    
	COXMapiRecipient( lpMapiRecipDesc pMapiRecip, DWORD dwCount );	
	// --- In  : pMapiRecip : pointer to arry of mapirecipients
	//			 dwCount : the number of recipients poited to by pMapiRecip
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	COXMapiRecipient( COXMapiRecipient& b );
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy constructor Can throw a COXMapiException
	//				It will initialize the internal state

    void Flush();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : frees all memory associated with this object.
			
	DWORD GetSize() const;
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Gets the size of array of structures contained in this object
	
	DWORD CreatePointer( WORD wSize );
	// --- In  : wSize : required size of one mapirecipdesc
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_ALREADY_THERE, or MEMORY_ERROR_ON_NEW
	// --- Effect : allocates memory for array of mapirecipdesc structures of wSize
	//				and sets contents to NULL
			
	DWORD SetPosition( DWORD dwPos );
	// --- In  : dwPos : the position the user wants to set. Each mapirecipdesc has a 
	//					 zero based index.
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE, or NOT_VALID_POSITION
	// --- Effect : sets the postion for all other member functions	by the use of an
	//				internal pointer.
								
	inline DWORD GetRecipClass()
	// --- In  : 
	// --- Out : 
	// --- Returns : the class of the Mapi Recipient
	// --- Effect : gets the class for the mapifiledesc currently selected within this object
	//				See MAPI doco for more info
		{	
		ASSERT_VALID( this );
		ASSERT( m_pMapiRecipDesc != NULL );
		return ( (DWORD)m_pPosition->ulRecipClass );
		}


	DWORD SetRecipClass( DWORD dwNewRecipClass );
	// --- In  : 
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE, or NOT_VALID_POSITION
	// --- Effect : sets the class of the Mapi Recipient for the mapifiledesc currently selected
	//				within this object :
	//				See MAPI doco for more info.
				
	CString GetName();
	// --- In  : 
	// --- Out : 
	// --- Returns : the name of the recipient
	// --- Effect : gets name of the recipient of the currently positioned mapifile struct
	//				can throw a COXMapiException. See MAPI doco for more info
		
	DWORD SetName( CString NewName );
	// --- In  : NewName : the new name of the recipient
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : sets the name of the currently positioned recipient	struct
	//				See MAPI doco for more info
	 	
	CString GetAddress();
	// --- In  : 
	// --- Out : 
	// --- Returns : the address of the recipient
	// --- Effect : gets address of the recipient of the currently positioned mapifile struct
	//				can throw a COXMapiException. See MAPI doco for more info
	
	DWORD SetAddress( CString NewAddress );
	// --- In  : NewAddress : the new address of the recipient
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : sets the address of the currently positioned recipient	struct
	//				See MAPI doco for more info

	DWORD SetEntryID ( LPVOID pEntryID, WORD wEIDSize );
	// --- In  : pEntryID : the new EntryID of the recipient
	//			 wEIDSize : the size of the pointer
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : copies the contents of pEntryID into the currently positioned recipient object
	//				See MAPI doco for more info
	
	virtual void Serialize( CArchive& ar );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : read or writes a COXMapiRecipient object to disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException
	
	COXMapiRecipient& operator=( COXMapiRecipient& b );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : assignment operator
	//				May throw a COXMapiException
	
	COXMapiRecipient& operator+=( COXMapiRecipient& b );
	// --- In  : 
	// --- Out : 
	// --- Returns : the concatenation of the source and parameter
	// --- Effect : concatenation operator
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException
	
	COXMapiRecipient& operator[]( DWORD d );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : array operator.
	//				May throw a COXMapiException.
	
	friend OX_API_DECL CArchive& AFXAPI operator <<( CArchive& ar, COXMapiRecipient& recip );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : piping operator to disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException

    friend OX_API_DECL CArchive& AFXAPI operator >>( CArchive& ar, COXMapiRecipient& recip );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : piping operator from disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException
	        
#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXMapiRecipient();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:      

private:
	// Helper functions;
	lpMapiRecipDesc GetPointer();

	DWORD CopyFromPointer( lpMapiRecipDesc pMapiRecip, DWORD dwCount );
		
};

OX_API_DECL CArchive& AFXAPI operator <<( CArchive& ar, COXMapiRecipient& recip );
OX_API_DECL CArchive& AFXAPI operator >>( CArchive& ar, COXMapiRecipient& recip );

#endif
// ==========================================================================
