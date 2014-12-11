// ==========================================================================
// 					Inline functions : COXMapiFile
// ==========================================================================
//
// Inline file : OXMapifl.inl
// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

inline DWORD COXMapiFile::GetFlags()
	{	
	ASSERT_VALID( this );
	ASSERT( m_pMapiFileDesc != NULL );
	return ( (DWORD)m_pPosition->flFlags );
	}

inline DWORD COXMapiFile::SetFlags( DWORD dwNewFlags )
	{
	ASSERT_VALID( this );

	if ( m_pMapiFileDesc == NULL )
		{
		return ( POINTER_NOT_THERE );
		}
	
	m_pPosition->flFlags = (ULONG)dwNewFlags;
	return ( SUCCESS_SUCCESS );
	}

inline DWORD COXMapiFile::GetAttachmentPosition()
	{
	ASSERT_VALID( this );
	return ( (DWORD)m_pPosition->nPosition );
	}
