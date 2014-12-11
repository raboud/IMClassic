// ==========================================================================
// 							Class Specification : COXMapiFile
// ==========================================================================

// Header file : oxmapifl.h

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
#ifndef __MAPIFILE_H__
#define __MAPIFILE_H__

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


class OX_CLASS_DECL COXMapiFile : public CObject
{
DECLARE_SERIAL( COXMapiFile );

friend class COXMapiMessage;


// Data members -------------------------------------------------------------
public:
	
protected:
    
private:
		lpMapiFileDesc	m_pMapiFileDesc;			
		lpMapiFileDesc	m_pPosition;
		ULONG			m_ulFileCount;

// Member functions ---------------------------------------------------------
public:
	COXMapiFile();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
    
	COXMapiFile( COXMapiFile& b );
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy constructor Can throw a COXMapiFileException
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
	// --- In  : wSize : required size of one MapiFileDesc
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_ALREADY_THERE, or MEMORY_ERROR_ON_NEW
	// --- Effect : allocates memory for array of MapiFileDesc structures of wSize
	//				and sets contents to NULL
			
	DWORD SetPosition( DWORD dwPos );
	// --- In  : dwPos : the position the user wants to set. Each mapifiledesc has a 
	//					 zero based index.
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE, or NOT_VALID_POSITION
	// --- Effect : sets the postion for all other member functions	by the use of an
	//				internal pointer.
								
	DWORD GetFlags();
	// --- In  : 
	// --- Out : 
	// --- Returns : the flags for a mapifiledesc structure
	// --- Effect : gets the flags for the mapifiledesc currently selected within this object
	//				See MAPI doco for mapifile flags types.
	
	DWORD SetFlags( DWORD dwNewFlags );
	// --- In  : 
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE, or NOT_VALID_POSITION
	// --- Effect : sets the flags for the mapifiledesc currently selected within this object
	//				See MAPI doco for mapifile flags types.
	
	DWORD SetAttachmentPosition( DWORD dwAttPos	);
	// --- In  : 
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_NOT_THERE, or NOT_VALID_POSITION
	// --- Effect : sets the attachment position for the mapifiledesc currently selected within this object :
	//				the position where the attachment is to be attached to in the mail message
	//				See MAPI doco for more info.
			
	DWORD GetAttachmentPosition();
	// --- In  : 
	// --- Out : 
	// --- Returns : the position of the attachment
	// --- Effect : gets the position where the attachment is to be attached
	//				for the mapifiledesc currently selected within this object
	//				See MAPI doco for more info
			
	CString GetPathName(); 
	// --- In  : 
	// --- Out : 
	// --- Returns : the full pathname
	// --- Effect : gets the pathname of the attachment of the currently positioned mapifile struct
	//				can throw a COXMapiException. See MAPI doco for more info
	
	DWORD SetPathName( CString sNewPathName );
	// --- In  : sNewPathName : the new full pathname
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Effect : sets the pathname of the attachment of the currently positioned mapifile
	//				struct
	//				See MAPI doco for more info

	CString GetFileName(); 
	// --- In  : 
	// --- Out : 
	// --- Returns : the filename(name that appears under the attachment in a mail view) 
	// --- Effect : sets the filename of the attachment of the currently positioned mapifile struct
	//				can throw a COXMapiException. See MAPI doco for more info
	
	DWORD SetFileName( CString NewFileName );
	// --- In  : 
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS or POINTER_NOT_THERE
	// --- Returns : the filename(name that appears under the attachment in a mail view) 
	// --- Effect : sets the filename of the attachment of the currently positioned mapifile struct
	//				See MAPI doco for more info

	virtual void Serialize( CArchive& ar );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : read or writes a COXMapiFile object to disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException

	COXMapiFile& operator=( COXMapiFile& b );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : assignment operator
	//				May throw a COXMapiException
	
	COXMapiFile& operator+=( COXMapiFile& b );
	// --- In  : 
	// --- Out : 
	// --- Returns : the concatenation of the source and parameter
	// --- Effect : concatenation operator
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException
	
	COXMapiFile& operator[]( DWORD d );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : array operator.
	//				May throw a COXMapiException.
	
	friend OX_API_DECL CArchive& AFXAPI operator <<( CArchive& ar, COXMapiFile& file );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : piping operator to disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException

    friend OX_API_DECL CArchive& AFXAPI operator >>( CArchive& ar, COXMapiFile& file );
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : piping operator from disk
	//				may throw a CMemoryException, CArchiveException, CFileException, COXMapiException
	        
#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXMapiFile();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:      

private:
	// Helper functions;
	DWORD CopyFromPointer( lpMapiFileDesc pMapiFile, DWORD dwCount );
			
	lpMapiFileDesc GetPointer();
                   
};

OX_API_DECL CArchive& AFXAPI operator <<( CArchive& ar, COXMapiFile& file );
OX_API_DECL CArchive& AFXAPI operator >>( CArchive& ar, COXMapiFile& file );

#include "OXMapifl.inl"

#endif
// ==========================================================================
