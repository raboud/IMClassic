// =============================================================================
// 							Class Specification : COXPaletteMap
// =============================================================================
//
// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
//
// /////////////////////////////////////////////////////////////////////////////
//
// Properties:
//
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject
//	NO	Is a Cwnd.
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO  Needs a resource (template)
//	NO	Persistent objects (saveable on disk)
//	NO	Uses exceptions
//
////////////////////////////////////////////////////////////////////////////////
//
// Desciption :
//		This class provides services useful to speeding palletized image
//		creation.  Windows makes working with a more traditional "identity
//		palette" somewhat difficult; this class takes a slightly different
//		approach to the problem.  The color depths supported are 8, 16,
//		24, and 32 bits per pixel.
//
// Remark:
//		While this code has been thoroughly tested on many different types
//		of video hardware, I'm sure it's possible that some bizzare boards
//		have been overlooked.  The new DirectX functions will eventually
//		obviate the need for this class, but until they are stable and are
//		available on all variants of Windows, this class will have to do.
//
// Prerequisites (necessary conditions):
//
// Limited edition:
//
/////////////////////////////////////////////////////////////////////////////

#if !defined( _PALETTEMAP_H_ )
#define _PALETTEMAP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXPaletteMap : public CObject
{
// Data members -------------------------------------------------------------
public:

protected:
	BITMAP m_bmpInfo;		// Compatible bitmap information.
	BYTE* m_pMap;			// Pointer to identity data.
	BYTE* m_pBuffer;		// Pointer to internal memory buffer.
	CPalette* m_pPalette;	// Pointer to color palette.
	int m_iBuffer;			// Size of internal memory buffer.
	int m_iMap;				// Size of map buffer.

private:

// Member functions ---------------------------------------------------------
public:

	COXPaletteMap( const CPalette* pPalette );
	// --- In  : pPalette : palette to make the map of
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	void InitializeBuffer( int iX, int iY, COLORREF cr = -1 );
	// --- In  :iX : Specifies the width (in pixels) of the bitmap.
	//			iY : Specifies the height (in pixels) of the bitmap.
	//			cr : Specifies the color to be matched.
	// --- Out : 
	// --- Returns :
	// --- Effect : Initializes the internal memory buffer for drawing on
	//				a bitmap of the given extents, optionally filled with
	//				the palette color closest to the given value, cr.

	void SetPixel( int iX, int iY, BYTE byIndex );
	// --- In  :iX : memory coordinate x
	//			iY : memory coordinate y
	//			byIndex : palette index
	// --- Out : 
	// --- Returns :
	// --- Effect : Sets the given palette index into the correct memory
	//				position given by the coordinates.

	void CreateBitmap( CBitmap* pBitmap );
	// --- In  :  
	// --- Out : pBitmap : external bitmap to be created
	// --- Returns :
	// --- Effect : Creates an external bitmap and sets its bits based
	//				on the contents of the internal memory buffer.

	void GetBufferExtents( CSize& size ) const
		{ size.cx = m_bmpInfo.bmWidth; size.cy = m_bmpInfo.bmHeight; }
	// --- In  : 
	// --- Out : size : size of internal bufer
	// --- Returns :
	// --- Effect : Provides the maximum extents of the current internal
	//				memory buffer configuration.

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXPaletteMap();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:
	// This method re-configures the internal map based on the palette
	// and current display driver parameters.  It is called automatically
	// when the public buffer initialization routine is called.

	void Initialize();

private:

};

#endif	// _PALETTEMAP_H_
// ==========================================================================
