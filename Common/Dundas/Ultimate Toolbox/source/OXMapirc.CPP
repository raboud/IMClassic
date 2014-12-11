// ==========================================================================
// 						Class Implementation : COXMapiRecipient
// ==========================================================================

// Source file : oxmapirc.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                        
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "oxmapirc.h"	// class specification

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL( COXMapiRecipient, CObject, 0 );

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	// lpMapiRecipDesc m_pMapiRecipDesc;			
	// --- The pointer to the beginning of the arrary of MapiRecipDesc structs
	//	lpMapiRecipDesc	m_pPosition;
	// --- The pointer to the currently positioned MapiRecipDesc struct
	//	ULONG			m_ulRecipCount;
	// --- The number of structs in this object

	
// Member functions ---------------------------------------------------------
// public:

COXMapiRecipient::COXMapiRecipient()
	{ 	
	ASSERT_VALID( this );
	m_pMapiRecipDesc = NULL;
	m_pPosition = NULL;
	m_ulRecipCount = 0;
	}

COXMapiRecipient::COXMapiRecipient( COXMapiRecipient& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	
	TRY
		{
		*this = b;
		}
	CATCH( CException, e )
		{
		THROW_LAST();
		m_pMapiRecipDesc = NULL;
		m_pPosition = NULL;
		m_ulRecipCount = 0;
		}
	END_CATCH
	}


////////////////////////////////////////////////////////////////////
// allows the building of an object from a pointer.
// dwCount is the number of elements in the array.
//
COXMapiRecipient::COXMapiRecipient( lpMapiRecipDesc pMapiRecip, DWORD dwCount )
	{
	ASSERT_VALID( this );
	DWORD err;
	
	if ( ( err = CopyFromPointer( pMapiRecip, dwCount ) ) != SUCCESS_SUCCESS )
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );
		}	
	}

COXMapiRecipient::~COXMapiRecipient()
	{
	ASSERT_VALID( this );
	Flush();
	}

void COXMapiRecipient::Flush()
	{
	ASSERT_VALID( this );
	if ( m_pMapiRecipDesc != NULL )
		{
		m_pPosition = m_pMapiRecipDesc;
		
		ULONG i;
		for ( i=0 ; i<m_ulRecipCount ; ++i )
			{
			delete m_pPosition->lpszName;
			m_pPosition->lpszName = NULL;

			delete m_pPosition->lpszAddress;
			m_pPosition->lpszAddress = NULL;

			delete m_pPosition->lpEntryID;
			m_pPosition->lpEntryID = NULL;

			++m_pPosition;
			}
		
		delete m_pMapiRecipDesc;
		m_pMapiRecipDesc = m_pPosition = NULL;
		}

	m_ulRecipCount = 0;
	}

DWORD COXMapiRecipient::CreatePointer( WORD wSize )
	{
	ASSERT_VALID( this );
	
	if ( wSize > 0)
		{
		if ( m_pMapiRecipDesc == NULL )
			{
			m_pMapiRecipDesc = new MapiRecipDesc[wSize];
			
			if ( m_pMapiRecipDesc == NULL )
				{
				return( MEMORY_ERROR_ON_NEW );
				}
			
			m_ulRecipCount = (ULONG)wSize;
			
			_fmemset( m_pMapiRecipDesc, NULL, ( sizeof(MapiRecipDesc) * wSize ) );
			m_pPosition = m_pMapiRecipDesc;
			}
		else
			{
			return( POINTER_ALREADY_THERE );		
			}
		}
	
	return( SUCCESS_SUCCESS );
	}

lpMapiRecipDesc COXMapiRecipient::GetPointer()
	// --- In  :
	// --- Out : 
	// --- Returns : gets the pointer to the MapiRecipDesc or NULL
	// --- Effect : private function( is used by friends COXMapiMessage & COXMapi )
	{	
	ASSERT_VALID( this );
	return ( m_pMapiRecipDesc );
	}
		
DWORD COXMapiRecipient::GetSize() const
	{	
	ASSERT_VALID( this );
	return ( (DWORD)m_ulRecipCount );
	} 

DWORD COXMapiRecipient::SetRecipClass( DWORD dwNewRecipClass )
	{	
	ASSERT_VALID( this );
	if ( m_pMapiRecipDesc == NULL )
		{
		return ( POINTER_NOT_THERE );
		}
	
	m_pPosition->ulRecipClass = (ULONG)dwNewRecipClass;
	return ( SUCCESS_SUCCESS );
	}

CString COXMapiRecipient::GetName() 
	{
	CString sName;

	if ( m_pMapiRecipDesc == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );

		return "";
		}
	sName = m_pPosition->lpszName;

	return sName;
	}

CString COXMapiRecipient::GetAddress() 
	{
	CString sAddress;

	if ( m_pMapiRecipDesc == NULL )
		{
		COXMapiException* e = new COXMapiException( POINTER_NOT_THERE );
		THROW( e );
					
		return "";
		}
	sAddress = m_pPosition->lpszAddress;

	return sAddress;
	}


DWORD COXMapiRecipient::SetPosition( DWORD dwPos )
	{	
	ASSERT_VALID( this );
	ASSERT( dwPos <= m_ulRecipCount );

	if ( m_ulRecipCount == 0 )
		{
		return( POINTER_NOT_THERE );
		
		}
	// re-initialise the pointer m_pPosition
	m_pPosition = m_pMapiRecipDesc;
	
	// set new position
	m_pPosition += dwPos;
	
	return( SUCCESS_SUCCESS );
	}
	
DWORD COXMapiRecipient::SetName( CString NewName )
	{	
	ASSERT_VALID( this );
	if ( m_pMapiRecipDesc == NULL )
		{
		return( POINTER_NOT_THERE );		
		}
	
	// delete old string if there
	delete m_pPosition->lpszName;
	m_pPosition->lpszName = NULL;
	
	if ( NewName.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}
	
	m_pPosition->lpszName = (LPSTR) new char[NewName.GetLength() + 1]; 
	if ( m_pPosition->lpszName == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pPosition->lpszName, (LPCSTR)(LPCTSTR)NewName );
	NewName.ReleaseBuffer();
	return ( SUCCESS_SUCCESS );
	}

DWORD COXMapiRecipient::SetAddress( CString NewAddress )
	{	
	ASSERT_VALID( this );
	if ( m_pMapiRecipDesc == NULL )
		{
		return( POINTER_NOT_THERE );		
		}

	// delete old string if there
	delete m_pPosition->lpszAddress;
	m_pPosition->lpszAddress = NULL;
	

	if ( NewAddress.GetLength() == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}

	m_pPosition->lpszAddress = (LPSTR)new char[NewAddress.GetLength() + 1];
	if ( m_pPosition == NULL )
		{
		return ( MEMORY_ERROR_ON_NEW );
		}
	
	strcpy( m_pPosition->lpszAddress, (LPCSTR)(LPCTSTR)NewAddress );
	NewAddress.ReleaseBuffer();
	return ( SUCCESS_SUCCESS );
	}			


DWORD COXMapiRecipient::SetEntryID ( LPVOID pEntryID, WORD wEIDSize )
	{
	if ( m_pMapiRecipDesc == NULL )
		{
		return( POINTER_NOT_THERE );		
		}

	delete m_pPosition->lpEntryID;
	
	m_pPosition->ulEIDSize = (ULONG) wEIDSize;
	if ( wEIDSize == 0 )
		{
		return( SUCCESS_SUCCESS );		
		}
	m_pPosition->lpEntryID = (LPVOID)new BYTE[wEIDSize];
	
	LPVOID pdummy = m_pPosition->lpEntryID;

	if ( m_pPosition->lpEntryID == NULL )
		{
		return( MEMORY_ERROR_ON_NEW );		
		}
	
	memcpy( pdummy, (LPVOID)pEntryID, wEIDSize );
	return( SUCCESS_SUCCESS );
	}
	
DWORD COXMapiRecipient::CopyFromPointer( lpMapiRecipDesc pMapiRecip, DWORD dwCount )
	// --- In  : pMapiRecip : pointer to the MapiRecipDesc structs
	//			 dwCount : number of structs in array pMapiRecip
	// --- Out : 
	// --- Returns : SUCCESS_SUCCESS, POINTER_ALREADY_THERE, or MEMORY_ERROR_ON_NEW
	// --- Effect : initialises the class with a pointer pMapiRecip returned by a mapi function.
	{
	ASSERT_VALID( this );
	DWORD retval, i, r;
	lpMapiRecipDesc pTemp = pMapiRecip;
	
	Flush();
	
	if ( pMapiRecip == NULL || dwCount == 0 )
		{
		return ( SUCCESS_SUCCESS );
		}
	
	retval = CreatePointer( (WORD)dwCount );
	if ( retval != SUCCESS_SUCCESS )
		{
		return( retval );		
		}
	
	for ( i=0 ; i<dwCount ; ++i )
		{
		SetPosition( i );
		
		SetRecipClass( (DWORD)pTemp->ulRecipClass );
		
		retval = SetName( pTemp->lpszName );
		if ( retval != SUCCESS_SUCCESS )
			{
			//	Clean up all creations to ensure free memory when an error occurs.
			if ( i > 0 )
				{
				for ( r=0 ; r<i ; ++r )
					{
					SetPosition( r );
					SetName( "" );
					SetAddress( "" );
					}
				}
			
			return ( retval );	
			}
	
		retval = SetAddress( pTemp->lpszAddress );
		if ( retval != SUCCESS_SUCCESS )
			{
			//	Clean up all creations to ensure free memory when an error occurs.
			SetName( "" );
			if ( i > 0 )
				{
				for ( r=0 ; r<i ; ++r )
					{
					SetPosition( r );
					SetName( "" );
					SetAddress( "" );
					}
				}
			return ( retval );	
			}
		
		retval = SetEntryID( pTemp->lpEntryID, (WORD)pTemp->ulEIDSize );
		if ( retval != SUCCESS_SUCCESS )
			{
			//	Clean up all creations to ensure free memory when an error occurs.
			SetName( "" );
			SetAddress( "" );
			if ( i > 0 )
				{
				for ( r=0 ; r<i ; ++r )
					{
					SetPosition( r );
					SetName( "" );
					SetAddress( "" );
					}
				}
		
			return ( retval );	
			}
		m_pPosition->ulReserved = pTemp->ulReserved;
		m_pPosition->ulRecipClass = pTemp->ulRecipClass;
		++pTemp;
		}
	
	return( SUCCESS_SUCCESS );	
	}

COXMapiRecipient& COXMapiRecipient::operator[]( DWORD d )
	{
	DWORD err;
	ASSERT( d <= m_ulRecipCount );
	
	if ( ( err = SetPosition( d ) ) != SUCCESS_SUCCESS )
		{
		COXMapiException* e = new COXMapiException( err );
		THROW( e );
		}
	
	return ( *this );
	}

COXMapiRecipient& COXMapiRecipient::operator=(COXMapiRecipient& b)
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	DWORD err;
	
	// test if "b" is the same as this;
	if ( this == &b )
		{
		return( *this );
		}
	
	if ( b.GetSize() > 0 )
		{
		if ( ( err = CopyFromPointer( b.GetPointer(), b.GetSize() ) ) !=SUCCESS_SUCCESS )
			{
			Flush();
			
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			}
		}
	else
		{
		Flush();
		}
	return( *this );
	}

#pragma warning ( disable : 4135 )
COXMapiRecipient& COXMapiRecipient::operator+=( COXMapiRecipient& b )
	{
	ASSERT_VALID( this );
	ASSERT_VALID( &b );
	DWORD err;
	
	if ( this == &b )
		{
		return( *this );
		}
	
	COXMapiRecipient dest;
	
	if ( b.GetSize() == 0 )
		{
		return( *this );
		}
	
	if ( GetSize() == 0 )
		{
		*this = b;
		return( *this );
		}
	
	if ( ( err = dest.CreatePointer( (WORD)( GetSize() + b.GetSize() ) ) ) != SUCCESS_SUCCESS )  // b may be larger than 1 recipenent
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
		
		
		if ( ( err = dest.SetName( GetName() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
		
		if ( ( err = dest.SetAddress( GetAddress() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
		
		if ( ( err = dest.SetEntryID( m_pPosition->lpEntryID, (WORD)m_pPosition->ulEIDSize ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
		
		if ( ( err = dest.SetRecipClass( GetRecipClass() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}
		
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
		
			
		if ( ( err = dest.SetName( b.GetName() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}

		if ( ( err = dest.SetAddress( b.GetAddress() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}

		if ( ( err = dest.SetEntryID( b.m_pPosition->lpEntryID, (WORD)b.m_pPosition->ulEIDSize ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}

		if ( ( err = dest.SetRecipClass( b.GetRecipClass() ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			
			return( *this );
			}

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


void COXMapiRecipient::Serialize( CArchive& ar )
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


CArchive& AFXAPI operator <<( CArchive& ar, COXMapiRecipient& recip )
	{
	int i;
	CString String;
	
	TRACE(_T(" Serializing to disk a COXMapiRecipient object\n"));
	
	TRY
		{
		ar << recip.GetSize();
	
		if ( recip.GetSize() > 0 )
			{
			for ( i=0; i < (int)recip.GetSize(); ++i )
				{
				recip.SetPosition( i );
				
				ar << recip.GetRecipClass();
				
				String = recip.GetName();
				ar << String;
				
				String = recip.GetAddress();
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

CArchive& AFXAPI operator >>( CArchive& ar, COXMapiRecipient& recip )
	{
	int i;
	DWORD dwSize, dwClass, err;
	CString string;
	
	TRACE(_T(" Serializing from disk a COXMapiRecipient object\n"));
		
	recip.Flush();
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
		if ( ( err = recip.CreatePointer( (WORD)dwSize ) ) != SUCCESS_SUCCESS )
			{
			COXMapiException* e = new COXMapiException( err );
			THROW( e );
			recip.Flush();
			return( ar );
			}		
		
		for ( i=0; i < (int)recip.GetSize(); ++i )
			{
			if ( ( err = recip.SetPosition( i ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				recip.Flush();
				return( ar );
				}
			
			TRY
				{
				ar >> dwClass;
				}
			CATCH( CException, e )
				{
				THROW_LAST();
				}
			END_CATCH
			if ( ( err = recip.SetRecipClass( dwClass ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				recip.Flush();
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
			if ( ( err = recip.SetName( string ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				recip.Flush();
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
			if ( ( err = recip.SetAddress( string ) ) != SUCCESS_SUCCESS )
				{
				COXMapiException* e = new COXMapiException( err );
				THROW( e );
				recip.Flush();
				return( ar );
				}
			}
		}
	
	return( ar );
	}

#ifdef _DEBUG

void COXMapiRecipient::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXMapiRecipient::Dump( CDumpContext& dc ) const
	{
	CObject::Dump( dc );
	
	dc << " \nDumping a COXMapiRecipient object \n\n";
	if ( GetSize() == 0 )
		{
		dc << " COXMapiRecipient is empty \n";
		return;
		}
	
	int i;
	
		// initialise the pointer pPosition
	lpMapiRecipDesc pPosition = m_pMapiRecipDesc;
	for ( i=0; i<(int)GetSize(); ++i )
		{
		dc << "Element number:- " << i << "\n";
		dc << " RecipClass is " << pPosition->ulRecipClass << "\n";
		dc << " Name is " << pPosition->lpszName << "\n";
		dc << " Address is " << pPosition->lpszAddress << "\n";
		dc << " Number of bytes in lpEntryID is " << pPosition->ulEIDSize << "\n";
		dc << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
		pPosition++;
		}
	
	dc << "Finished dumping COXMapiRecipient object\n\n";
	}
#endif  //_DEBUG
	
// protected:

// private:

// ==========================================================================
