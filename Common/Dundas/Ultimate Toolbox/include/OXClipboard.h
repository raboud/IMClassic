// ==========================================================================
// 						Class Specification : COXClipboard
// ==========================================================================

// Header file : OXClipboard.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CArchive

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates the clipboard.  
//	It is used with an underlying object of the class CSHaredFile.
//	This is an undocumented MFC class derived from CMemFile that uses global memory
//	Now objects can be directly serialized to and from the clipboard

// Remark:
//	The normal sequence of function calls is :
//	- construction
//	- Open()
//	- SelectFormat()
//	- Input or output functions : Read/Write, ReadString/WriteString etc.
//	- SelectFormat()
//	- Input or output functions : Read/Write, ReadString/WriteString etc.
//	- ...
//  - Close
//  - destruction

//  An internal buffer is organized per clipboard format
//	It is allowed to chenge formats and append to an earlier selected format
//		SelectFormat(CF_TEXT)
//		Write()
//		SelectFormat(CF_BITMAP)
//		Write()
//		SelectFormat(CF_TEXT)
//		Write()					// Append to the first written CF_TEXT data
//	The same is allowed during reading

// The clipboard is a system wide resource.  Be sure to limit the time you use it,
// because when you are using it no other application can access it.
// The clipboard is used between Open() and Close() on a COXClipboard object.

// Microsoft warns that direct accessing a memory file that is also used through 
// an archive is a tricky thing, so don't do it (MDN PSS ID Q132079)!
// If you still want to do it, take a look at the CFile::GetBufferPtr() function.
// Supplying CFile::bufferRead or CFile::bufferWrite as firts parameter will 
// synchonize the archive buffers during load or store.


// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXCLIPARC_H__
#define __OXCLIPARC_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <afxtempl.h>
#include <afxpriv.h>	// For CSharedFile


class OX_CLASS_DECL COXClipboard : public CArchive
{
// Data members -------------------------------------------------------------
public:
	
protected:
	CSharedFile*	m_pSharedFile;
	BOOL			m_bClipboardOpen;
	UINT			m_nLastUsedFormat;
	struct CFormatInfo
		{
		HGLOBAL		m_hBuffer;
		UINT		m_nPosition;
		};
	CMap<UINT, UINT, CFormatInfo, CFormatInfo>	m_formatInfos;

	static const UINT	m_nBufferBlockSize;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXClipboard(UINT nMode, int nGrowBytes = 4096);
	// --- In  : nMode : Whether this archive will be used to load (CArchive::load)
	//                   or to store information (CArchive::store)
	//			 nGrowBytes : The memory allocation increment in bytes.
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs the object
	//				Before using the object you must call Open

	BOOL Open();
	// --- In  : nClipboardFormat : The clipboard format to be used
	// --- Out : 
	// --- Returns : Whether the clipboard could be opened successfully
	// --- Effect : Opens the clipboard.  It will stay open
	//				until the destructor or Close is called

	BOOL SelectFormat(UINT nClipboardFormat);
	// --- In  : nClipboardFormat : The clipboard format to be used
	// --- Out : 
	// --- Returns : Whether the clipboard format is valid
	// --- Effect : 

	BOOL SelectFormat(LPCTSTR pszClipboardFormat);
	// --- In  : pszClipboardFormat : The clipboard format to be used
	// --- Out : 
	// --- Returns : Whether the clipboard format is valid
	// --- Effect : If the clipboard format is not yet registered it will be done now

	void Close();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Closes the clipboard.

	void Abort();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Closes the clipboard without transfering formats actually to the clipboard.

	static BOOL IsFormatAvailable(UINT nFormat);
	// --- In  : nClipboardFormat : The clipboard format searched for
	// --- Out : 
	// --- Returns : Whether the specified clipboard format is currently in the clipboard
	// --- Effect : 

	static BOOL IsFormatAvailable(LPCTSTR pszClipboardFormat);
	// --- In  : pszClipboardFormat : The clipboard format searched for
	// --- Out : 
	// --- Returns : Whether the specified clipboard format is currently in the clipboard
	// --- Effect : 

	static CString GetFormatName(UINT nFormat);
	// --- In  : nClipboardFormat : The clipboard format number of a private format
	// --- Out : 
	// --- Returns : The name associated with the specified number
	// --- Effect : If the function fails, the return value is empty,
	//              indicating that the requested format does not exist or 
	//              is predefined

	static UINT GetFormatNumber(LPCTSTR pszClipboardFormat);
	// --- In  : pszClipboardFormat : The clipboard format name of a private format
	// --- Out : 
	// --- Returns : The number associated with the specified name
	// --- Effect : 

	virtual ~COXClipboard();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
	//				If the clipboard is still open, it will be closed

protected:      
	void Empty();
	void StoreFormatInfo(CFormatInfo& formatInfo);
	void TransferClipboardFormats();

private:
                   
};

#endif	// __OXCLIPARC_H__
// ==========================================================================
