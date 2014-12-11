// =============================================================================
// 							Class Implementation : COXPaletteMap
// =============================================================================
//
// Source file : 		PaletteMap.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved

// //////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OXPalMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:

	// BITMAP m_bmpInfo;		
	// --- Compatible bitmap information.

	// BYTE* m_pMap;			
	// --- Pointer to identity data

	// BYTE* m_pBuffer;		
	// --- Pointer to internal memory buffer.

	// CPalette* m_pPalette;	
	// --- Pointer to color palette.

	// int m_iBuffer;			
	// --- Size of internal memory buffer.

	// int m_iMap;				
	// --- Size of map buffer.

// private:
	
// Member functions ---------------------------------------------------------
// public:

// This helper function creates a copy of the specified palette.
// If the function has more general applicability, I would suggest
// making it public.

static CPalette* DuplicatePalette( const CPalette* pPalette )
{
	CPalette* pReturn = NULL;
	ASSERT( pPalette != NULL );
	
	if ( pPalette != NULL )
	{
		// This nasty little cast is necessary because whoever wrote
		// the GetEntryCount declaration failed to notice it should
		// have been const.
		
		int iNumColors = const_cast<CPalette*>( pPalette )->GetEntryCount();
		int iSizePal = sizeof( LOGPALETTE ) + iNumColors * sizeof( PALETTEENTRY );
		LPTSTR p = new TCHAR[iSizePal];
		ASSERT( p != NULL );
		
		if ( p != NULL )
		{
			LOGPALETTE* pLP = (LOGPALETTE*)p;
			pLP->palVersion = 0x300;
			pLP->palNumEntries = (WORD)iNumColors;
			pPalette->GetPaletteEntries( 0, iNumColors, pLP->palPalEntry );
			
			CPalette* pPalette = new CPalette;
			if ( pPalette->CreatePalette( pLP ) )
				pReturn = pPalette;
			else
				delete pPalette;
			delete [] p;
		}
	}
	
	return pReturn;
}

COXPaletteMap::COXPaletteMap( const CPalette* pPalette )
	:
	m_pPalette( NULL ),
	m_iBuffer( 0 ),
	m_pMap( NULL ),
	m_iMap( 0 ),
	m_pBuffer( NULL )
{
	// Make a locally owned copy of the specified palette before
	// other initialization.
	m_pPalette = DuplicatePalette( pPalette );
	Initialize();
}
	
COXPaletteMap::~COXPaletteMap()
{
	delete m_pPalette;
	delete [] m_pMap;
	delete [] m_pBuffer;
}

void COXPaletteMap::Initialize()
{
	// Compare the current display driver color depth parameters
	// against those currently in effect; if no different, get out
	// of here.
	
	CDC dcMem;
	VERIFY( dcMem.CreateCompatibleDC( NULL ) );
	int iBpp = dcMem.GetDeviceCaps( BITSPIXEL );
	int iPlanes = dcMem.GetDeviceCaps( PLANES );
	
	// These are the only color depths for which the class has support.
	// Notably absent is the stock 16-color 4bpp mode which would require
	// dithering -- something I didn't want to provide.
	
	ASSERT( iBpp == 8 || iBpp == 16 || iBpp == 24 || iBpp == 32 );
	
	if ( iBpp != m_bmpInfo.bmBitsPixel || iPlanes != m_bmpInfo.bmPlanes )
	{
		// Otherwise, clear out the internal bitmap structure, reset
		// the color depth parameters, and delete the map.
		
		memset( &m_bmpInfo, 0, sizeof( m_bmpInfo ) );
		m_bmpInfo.bmBitsPixel = (WORD)iBpp;
		m_bmpInfo.bmPlanes = (WORD)iPlanes;
		delete [] m_pMap;
		m_pMap = NULL;
		
		// Get the number of entries in the palette and prepare a
		// temporary bitmap for creating the map.
		
		int iNumColors = m_pPalette->GetEntryCount();
		ASSERT( 0 < iNumColors && iNumColors < 257 );
		CPalette* ppalOld = dcMem.SelectPalette( m_pPalette, FALSE );
		dcMem.RealizePalette();
		CBitmap bmp;
		VERIFY( bmp.CreateBitmap( iNumColors, 1, iPlanes, iBpp, NULL ) );
		CBitmap* pbmpOld = dcMem.SelectObject( &bmp );
		
		// Shove each palette color into the bitmap such that we end
		// up with a bitmap one pixel in width for each color.
		
		for ( int i = 0; i < iNumColors; i++ )
			dcMem.SetPixel( i, 0, PALETTEINDEX( i ) );
		
		// Get the bitmap information for future use, allocate space
		// for the map data, get the map data, and clean up.
		
		bmp.GetObject( sizeof( m_bmpInfo ), &m_bmpInfo );
		DWORD dwBytesExpected = (DWORD)m_bmpInfo.bmWidthBytes * (DWORD)m_bmpInfo.bmHeight;
		m_pMap = new BYTE[dwBytesExpected];
		m_iMap = dwBytesExpected;
		bmp.GetBitmapBits( dwBytesExpected, m_pMap );
		dcMem.SelectPalette( ppalOld, FALSE );
		dcMem.SelectObject( pbmpOld );
	}
}

void COXPaletteMap::InitializeBuffer( int iX, int iY, COLORREF cr )
{
	// Make sure the internal parameters are valid for the
	// current screen resolution.
	
	Initialize();
	
	// Create a temporary bitmap for retrieving information.
	
	CBitmap bmp;
	BOOL bOk = bmp.CreateBitmap( iX, iY, m_bmpInfo.bmPlanes, 
		m_bmpInfo.bmBitsPixel, NULL );
	ASSERT( bOk );
	bmp.GetObject( sizeof( m_bmpInfo ), &m_bmpInfo );
	
	// Figure out the requisite buffer size and allocate if
	// the current buffer is not large enough.
	
	int iBytes = iY * m_bmpInfo.bmWidthBytes;
	if ( iBytes > m_iBuffer )
	{
		delete [] m_pBuffer;
		m_pBuffer = new BYTE[iBytes];
		m_iBuffer = iBytes;
	}
	
	// If the user has requested initialization, find the nearest 
	// palette index for the specified color and set the pixels.
	
	if ( cr != -1 )
	{
		UINT uiIndex = m_pPalette->GetNearestPaletteIndex( cr );
		ASSERT( uiIndex < (UINT)m_pPalette->GetEntryCount() );
		if ( uiIndex < (UINT)m_pPalette->GetEntryCount() )
		{
			for ( int y = 0; y < iY; y++ )
				for ( int x = 0; x < iX; x++ )
				SetPixel( x, y, (BYTE)uiIndex );
		}
	}
}

void COXPaletteMap::CreateBitmap( CBitmap* p )
{
	BOOL bOk = p->CreateBitmap( m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, 
		m_bmpInfo.bmPlanes, m_bmpInfo.bmBitsPixel, NULL );
	ASSERT( bOk );
	int iBytes = m_bmpInfo.bmHeight * m_bmpInfo.bmWidthBytes;
	ASSERT( iBytes <= m_iBuffer );
	p->SetBitmapBits( iBytes, m_pBuffer );
}

void COXPaletteMap::SetPixel( int iX, int iY, BYTE byIndex )
{
	// Un-comment the assert statements for major league validation.
	
	size_t Bytes = m_bmpInfo.bmBitsPixel / 8;
	ASSERT( 0 < Bytes == 1 && Bytes < 5 );
	int iDest = ( iY * m_bmpInfo.bmWidthBytes + iX * Bytes );
	int iSrc = byIndex * Bytes;
	ASSERT( -1 < iDest && iDest < m_iBuffer );
	ASSERT( -1 < iSrc && iSrc < m_iMap );
	ASSERT( (int)( iSrc + Bytes - 1 ) < m_iMap );
	memcpy( &m_pBuffer[iDest], &m_pMap[iSrc], Bytes );
}

#ifdef _DEBUG
void COXPaletteMap::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << _T("\nm_pPalette : ") << (void*)m_pPalette;
	dc << _T("\nm_pMap : ") << (void*)m_pMap;
	dc << _T("\nm_pBuffer : ") << (void*)m_pBuffer;
	dc << _T("\nm_bmpInfo : ") << (void*)&m_bmpInfo;
}

void COXPaletteMap::AssertValid() const
{
	CObject::AssertValid();
}
#endif

