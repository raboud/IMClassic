// ==========================================================================
// 						Class Implementation : COXMapiFile
// ==========================================================================

// Source file : oxmapifl.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxmapifl.h"	// class specification

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL( COXMapiFile, CObject, 0 );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	//	lpMapiFileDesc	m_pMapiFileDesc;			
	// --- The pointer to the beginning of the arrary of MapiFileDesc structs
	//	lpMapiFileDesc	m_pPosition;
	// --- The pointer to the currently positioned MapiFileDesc struct
	//	ULONG			m_ulFileCount;
	// --- The number of structs in this object

	
// Member functions ---------------------------------------------------------
// public:

COXMapiFile::COXMapiFile()
	{
 	ASSERT_VALID( this );
	m_pMapiFileDesc = NULL;
	m_pPosition = NULL;
	m_ulFileCount = 0;
	}

COXMapiFile::COXMapiFile( COXMapiFile& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	
	m_pMapiFileDesc = NULL;
	m_pPosition = NULL;
	m_ulFileCount = 0;

	if ( b.GetSize() == 0 )
		{
		return;
		}
	
	TRY
		{
		*this = b;
		}
	CATCH( CException, e )
		{
		THROW_LAST();
		}
	END_CATCH
	}


COXMapiFile::~COXMapiFile()
	{
	ASSERT_VALID( this );
	Flush();
	}

void COXMapiFile::Flush()
	{
	ASSERT_VALID( this );
	if ( m_pMapiFileDesc != NULL )
		{
		m_pPosition = m_pMapiFileDesc;
		
		ULONG i;
		for ( i=0 ; i<m_ulFileCount ; ++i )
			{
			delete m_pPosition->lpszPathName;
			m_pPosition->lpszPathName = NULL;

			delete m_pPosition->lpszFileName;
			m_pPosition->lpszFileName = NULL;

			++m_pPosition;
			}
	
		delete[] m_pMapiFileDesc;
		m_pMapiFileDesc = m_pPosition = NULL;
		}
	
	m_ulFileCount = 0;
	}

DWORD COXMapiFile::CreatePointer( WORD wSize )
	{
	ASSERT_VALID( this );
	ASSERT ( wSize > 0 );
	
	if ( m_pMapiFileDesc == NULL )
		{
		m_pMapiFileDesc = new MapiFileDesc[wSize];
		if ( m_pMapiFileDesc == NULL )
			{
			return( MEMORY_ERROR_ON_NEW );
			}

		m_ulFileCount = (ULONG)wSize;
		
		_fmemset( m_pMapiFileDesc, NULL, ( sizeof(MapiFileDesc) * wSize ) );
		m_pPosition = m_pMapiFileDesc;
		}
	else
		{
		return( POINTER_ALREADY_THERE );		
		}
	
	return( SUCCESS_SUCCESS );
	}		

DWORD COXMapiFile::CopyFromPointer( lpMapiFileDesc pMapiFile, DWORD dwCount )
	// --- In  : pMapiFile : pointer to the beginning of an array of MapiFileDesc's
	//			 dwCount :  the number of MapiFileDesc structs behind pMapiFile
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_ALREADY_THERE, or MEMORY_ERROR_ON_NEW
	// --- Effect : initialises the class with a pointer returned by a mapi function.
	//				For use inside a COXMapiFileMessage object or a COXMapiFile object.
	{
	ASSERT_VALID( this );
	DWORD retval, i, r;
	lpMapiFileDesc pTemp = pMapiFile;
	
	Flush();
	
	if ( pMapiFile == NULL || dwCount == 0 )
		{
		return( SUCCESS_SUCCESS );
		}
	
	retval = CreatePointer( (WORD)dwCount );
	if ( retval != SUCCESS_SUCCESS )
		{
		return( retval );		
		}
	
	for ( i=0 ; i < dwCount ; ++i )
		{
		SetPosition( i );
		
		SetFlags( (DWORD)pTemp->flFlags);
		SetAttachmentPosition( (DWORD) pTemp->nPosition );
		
		retval = SetPathName( pTemp->lpszPathName );
		if ( retval != SUCCESS_SUCCESS )
			{
			//	Clean up all creations to ensure free memory when an error occurs.
			if ( i > 0 )
				{
				for ( r=0 ; r<i ; ++r )
					{
					SetPosition( r );
					SetPathName( "" );
					SetFileName( "" );
					}
				}
			
			return ( retval );	
			}
		
		retval = SetFileName( pTemp->lpszFileName );
		if ( retval != SUCCESS_SUCCESS )
			{
			//	Clean up all creations to ensure free memory when an error occurs.
			SetPathName( "" );
			if ( i > 0 )
				{
				for ( r=0 ; r<i ; ++r )
					{
					SetPosition( r );
					SetPathName( "" );
					SetFileName( "" );
					}
				}
			
			return ( retval );	
			}
		
		m_pPosition->ulReserved = pTemp->ulReserved;
		m_pPosition->flFlags = pTemp->flFlags;
		++pTemp;
		}
	
	return( SUCCESS_SUCCESS );
	}
  	
lpMapiFileDesc COXMapiFile::GetPointer()
	// --- In  :
	// --- Out : 
	// --- Returns : gets the pointer to the current MapiFileDesc  or NULL
	// --- Effect : 
	{	
	ASSERT_VALID( this );
	return ( m_pMapiFileDesc );
	}

DWORD COXMapiFile::GetSize() const
	{
	ASSERT_VALID( this );
	return ( (DWORD)m_ulFileCount );
	} 

DWORD COXMapiFile::SetAttachmentPosition( DWORD dwAttPos	)
	{	
	ASSERT_VALID( this );
	if ( m_pMapiFileDesc == NULL )
		{
		return ( POINTER_NOT_THERE );
		}

	m_pPosition->nPosition = (ULONG) dwAttPos;
	return ( SUCCESS_SUCCESS );
	}

DWORD COXMapiFile::SetPosition( DWORD dwPos )
	{	
	ASSERT_VALID( this );
	ASSERT( dwPos <= m_ulFileCount );
	if (dwPos > m_ulFileCount)
		{
		return( NOT_VALID_POSITION );
		}


	if ( m_ulFileCount == 0 )
		{
		return( POINTER_NOT_THERE );
		}

	// re-initialise the pointer m_pPosition
	m_pPosition = m_pMapiFileDesc;
	
	// set new position
	m_pPosition += dwPos;
	
	return( SUCCESS_SUCCESS );
	}

CString COXMapiFile::GetPathName() 
	{	
	CString sPathName;

	if ( m_pMapiFileDesc == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );

		return "";
		}
	
	sPathName = m_pPosition->lpszPathName;
	return ( sPathName );
	}

	
DWORD COXMapiFile::SetPathName( CString NewPathName )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiFileDesc == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	// delete old string if there
	delete m_pPosition->lpszPathName;
	m_pPosition->lpszPathName = NULL;
	
	if ( NewPathName.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}
	
	m_pPosition->lpszPathName = (LPSTR) new char[NewPathName.GetLength() + 1]; 
	if ( m_pPosition->lpszPathName == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pPosition->lpszPathName, (LPCSTR)(LPCTSTR)NewPathName );
	NewPathName.ReleaseBuffer();
	return ( SUCCESS_SUCCESS );
	}

CString COXMapiFile::GetFileName() 
	{
	CString sFileName;

	if ( m_pMapiFileDesc == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );
					
		return "";
		}

	sFileName = m_pPosition->lpszFileName;
	return ( sFileName );
	}

DWORD COXMapiFile::SetFileName( CString NewFileName )
	{
	ASSERT_VALID( this );
	
	if ( m_pMapiFileDesc == NULL )
		{
		return( POINTER_NOT_THERE );		
		}

	// delete old string if there
	delete m_pPosition->lpszFileName;
	m_pPosition->lpszFileName = NULL;
	
	if ( NewFileName.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}

	m_pPosition->lpszFileName = (LPSTR)new char[NewFileName.GetLength() + 1];
	if ( m_pPosition == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pPosition->lpszFileName, (LPCSTR)(LPCTSTR)NewFileName );
	NewFileName.ReleaseBuffer();
	return ( SUCCESS_SUCCESS );
	}			

void COXMapiFile::Serialize( CArchive& ar )
	{
 	TRY
 		{
 		CObject::Serialize( ar );
    
    	if( ar.IsStoring() )
    		{
    		ar << *this;
    		}
    	else
    		{
    		ar >> *this;
    		}
		}
    CATCH( CException, e )
   		{
   		THROW_LAST();
   		}
   	END_CATCH
	}

COXMapiFile& COXMapiFile::operator[]( DWORD d )
	{
	DWORD err;
	ASSERT( d <= m_ulFileCount );
	
	if ( ( err = SetPosition( d ) ) != SUCCESS_SUCCESS )
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );
		}
	
	return ( *this );
	}

COXMapiFile& COXMapiFile::operator=( COXMapiFile& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	DWORD err;
	
	// test for "b" == to this
	if ( this == &b )
		{
		return ( *this );
		}
		
	Flush();
	
	if ( b.GetSize() > 0 )
		{
		if ( ( err = CopyFromPointer( b.GetPointer(), b.GetSize() ) ) !=SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			Flush();
			}
		}
	else
		{
		Flush();
		}
	
	return( *this );
	}

#pragma warning ( disable : 4135 )
COXMapiFile& COXMapiFile::operator+=( COXMapiFile& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	
	COXMapiFile dest;
	DWORD err;
	
	if ( b.GetSize() == 0 )
		{
		return( *this );
		}
	
	if ( GetSize() == 0 )
		{
		*this = b;
		return( *this );
		}
	
	if ( ( err = dest.CreatePointer( (WORD)(GetSize() + b.GetSize()) ) ) != SUCCESS_SUCCESS ) // b may be larger than 1 recipenent
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );                     
		
		return( *this );
		}
		
	
	int i;
	for ( i=0; i<(int)GetSize(); ++i )
		{
		if ( ( err = SetPosition( i ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetPosition( i ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		
		if ( ( err = dest.SetAttachmentPosition( GetAttachmentPosition() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetFileName( GetFileName() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetFlags( GetFlags() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetPathName( GetPathName() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		
		dest.m_pPosition->ulReserved = m_pPosition->ulReserved;
		dest.m_pPosition->ulReserved = m_pPosition->ulReserved;
		}
	
	int j = 0;
	for ( i = GetSize(); i<(int)dest.GetSize(); ++i )
		{
		if ( ( err = dest.SetPosition( i ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = b.SetPosition( j ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
			
		if ( ( err = dest.SetAttachmentPosition( b.GetAttachmentPosition() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetFileName( b.GetFileName() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetFlags( b.GetFlags() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		if ( ( err = dest.SetPathName( b.GetPathName() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
			
		
		dest.m_pPosition->ulReserved = b.m_pPosition->ulReserved;
		dest.m_pPosition->ulReserved = b.m_pPosition->ulReserved;
		
		++j;
		}
	
	
	TRY
		{
		*this = dest;  // copy the new recip class into this.
		}
	CATCH( CException, e )
		{
		THROW_LAST();
		}
	END_CATCH
	
	return( *this );
	}
	
#ifdef _DEBUG
//////////////////////////////////////////////////////////
//
void COXMapiFile::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXMapiFile::Dump( CDumpContext& dc ) const
	{
	CObject::Dump( dc );
	
	dc << " Dumping a COXMapiFile object \n";
	dc << "#############################\n";
	if ( GetSize() == 0 )
		{
		dc << " COXMapiFile is empty \n";
		return;
		}
	
	int i;
	
	// initialise the pointer pPosition
	lpMapiFileDesc pPosition = m_pMapiFileDesc;
	for ( i=0; i<(int)GetSize(); ++i )
		{
		dc << "Element number:- " << i << "\n";
		dc << " FileName is " << pPosition->lpszFileName << "\n";
		dc << " PathName is " << pPosition->lpszPathName << "\n";
		dc << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		// set new position
		pPosition++;
		}
	}
#endif  //_DEBUG

CArchive& AFXAPI operator <<( CArchive& ar, COXMapiFile& file )
	{
	int i;
	CString String;
	
	TRY
		{
		ar << file.GetSize();
	
		if ( file.GetSize() > 0 )
			{
			for ( i=0; i < (int)file.GetSize(); ++i )
				{
				file.SetPosition( i );
				
				ar << file.GetFlags();
				
				ar << file.GetAttachmentPosition();
				
				String = file.GetPathName();
				ar << String;
				
				String = file.GetFileName();
				ar << String;
				}
			}
		}
	CATCH( CException, e )
		{
		THROW_LAST();
		}
	END_CATCH
	 
	return( ar );
	}

CArchive& AFXAPI operator >>( CArchive& ar, COXMapiFile& file )
	{
	int i;
	DWORD dwFlags, dwPOS, dwSize, err;
	CString string;
	
	file.Flush();
	
	TRY
		{
		ar >> dwSize;
		}
	CATCH( CException, e )
		{
		THROW_LAST();
		}
	END_CATCH
	
	if ( dwSize > 0 )
		{
		if ( ( err = file.CreatePointer( (WORD)dwSize ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( ar );
			}
		
		for ( i=0; i < (int)file.GetSize(); ++i )
			{
			if ( ( err = file.SetPosition( i ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				file.Flush();
				return( ar );
				}
			
			TRY
				{
				ar >> dwFlags;
				}
			CATCH( CException, e )
				{
				THROW_LAST();
				}
			END_CATCH
			if ( ( err = file.SetFlags( dwFlags ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				file.Flush();
				return( ar );
				}
			
			TRY
				{
				ar >> dwPOS;
				}
			CATCH( CException, e )
				{
				THROW_LAST();
				}
			END_CATCH
			if ( ( err = file.SetAttachmentPosition( dwPOS ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				file.Flush();
				return( ar );
				}
			
			TRY
				{
				ar >> string;
				}
			CATCH( CException, e )
				{
				THROW_LAST();
				}
			END_CATCH
			if ( ( err = file.SetPathName( string ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				file.Flush();
				return( ar );
				}
			
			TRY
				{
				ar >> string;
				}
			CATCH( CException, e )
				{
				THROW_LAST();
				}
			END_CATCH
			if ( ( err = file.SetFileName( string ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				file.Flush();
				return( ar );
				}
			}
		}
	
	return( ar );
	}
	
// protected:

// private:

// ==========================================================================
