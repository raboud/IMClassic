// ==========================================================================
//                     Class Implementation : COXClipboard
// ==========================================================================

// Source file : OXClipboard.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXClipboard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Definition of static members
const UINT COXClipboard::m_nBufferBlockSize = 4096;
// --- Block size that will be used to grow the memory block when it bacomes too small

// Data members -------------------------------------------------------------
// protected:
	// CSharedFile* m_pSharedFile;
	// --- The memory file used by this archive
	//     (This is the same as m_pFile, but of the correct type, avoids frequent casting)
	//		We need a pointer because this object must already be valid
	//		during the execution of the constructor of the base class

	// BOOL m_bClipboardOpen;
	// --- Whether the clipboard is successfully opened

	// UINT m_nLastUsedFormat;
	// --- The last used clipboard format

	// CMap<UINT, UINT, CFormatInfo, CFormatInfo> m_formatInfos;
	// --- A mapping from clipboard format to the memory that
	//     contains the data (memory handle, current position and total size)

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXClipboard::COXClipboard(UINT nMode, int nGrowBytes /* = 4096 */)
	:
	CArchive(m_pSharedFile = new CSharedFile(GMEM_DDESHARE|GMEM_MOVEABLE, nGrowBytes), nMode, nGrowBytes),
	m_bClipboardOpen(FALSE),
	m_nLastUsedFormat(0)
	{
	}

BOOL COXClipboard::Open()
	{
	if (m_bClipboardOpen)
		// ... Clipboard already opened : nothing to do
		return TRUE;
	if (!::OpenClipboard(NULL))
		{
		TRACE0("COXClipboard::Open : Cannot open clipboard\n");
		return FALSE;
		}

	// If we arrive here, everything worked fine
	m_bClipboardOpen = TRUE;
	return TRUE;
	}

	
BOOL COXClipboard::SelectFormat(UINT nClipboardFormat)
	{
	// Clipboard has to be opened
	if (!m_bClipboardOpen)
		{
		TRACE0("COXClipboard::SelectFormat : Clipboard not yet opened : Throwing CArchiveException\n");
		AfxThrowArchiveException(CArchiveException::generic);
		}

	CFormatInfo formatInfo;
	// First store the last used format (if any) and detach from file
	StoreFormatInfo(formatInfo);

	// Get the correct memory buffer
	// ... Check whether the requested format has already been used
	if (m_formatInfos.Lookup(nClipboardFormat, formatInfo))
		// Clipboard format has already been created, re-use it
		;
	else
		if (IsLoading())
			{
			// About to load data from the clipboard
			formatInfo.m_hBuffer = GetClipboardData(nClipboardFormat);
			formatInfo.m_nPosition = 0;
			}
		else
			{
			// About to store new data in the clipboard
			// Try clipboard format and create new buffer 
			// ... Use small dummy memory block to try (will never actually contain data)
			HGLOBAL hBuffer = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, m_nBufferBlockSize);
			if (::SetClipboardData(nClipboardFormat, hBuffer) == NULL)
				{
				TRACE0("COXClipboard::SelectFormat : Cannot set new clipboard buffer\n");
				return FALSE;
				}
			// ... Create the memory block that will contain the data
			formatInfo.m_hBuffer = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, m_nBufferBlockSize);
			formatInfo.m_nPosition = 0;
			}

	// Check buffer access success
	if (formatInfo.m_hBuffer == NULL)
		{
		TRACE0("COXClipboard::SelectFormat : Failed to use clipboard format\n");
		return FALSE;
		}

	// ... When loading use existing contents (nGrowBytes = 0) : file cannot grow
	m_pSharedFile->SetHandle(formatInfo.m_hBuffer, IsStoring());
	m_pSharedFile->Seek(formatInfo.m_nPosition, CFile::begin);
	// ... Seek may have chenged the file position directly, resync this archive
	//     See also MSDN PSS ID Q132079)
	if (IsLoading())
		{
		UINT nRead;
		nRead = m_pSharedFile->GetBufferPtr(CFile::bufferRead, m_nBufSize,
			(void**)&m_lpBufStart, (void**)&m_lpBufMax);
		ASSERT(nRead == (UINT)(m_lpBufMax - m_lpBufStart));
		m_lpBufCur = m_lpBufStart;
		}
	else
		{
		// sync up direct mode buffer to new file position
		VERIFY(m_pSharedFile->GetBufferPtr(CFile::bufferWrite, m_nBufSize,
			(void**)&m_lpBufStart, (void**)&m_lpBufMax) == (UINT)m_nBufSize);
		ASSERT((UINT)m_nBufSize == (UINT)(m_lpBufMax - m_lpBufStart));
		m_lpBufCur = m_lpBufStart;
		}

	// ... Add this format to the list
	m_formatInfos.SetAt(nClipboardFormat, formatInfo);
	m_nLastUsedFormat = nClipboardFormat;

	// If we arrive here, everything worked fine
	return TRUE;
	}
	
BOOL COXClipboard::SelectFormat(LPCTSTR pszClipboardFormat)
	{
	UINT nClipboardFormat;
	nClipboardFormat = GetFormatNumber(pszClipboardFormat);
	if (nClipboardFormat == 0)
		{
		TRACE0("COXClipboard::SelectFormat : Failed register clipboard format\n");
		return FALSE;
		}
	return SelectFormat(nClipboardFormat);
	}

void COXClipboard::Close()
	{
	// First store the last used format (if any) and detach from file
	CFormatInfo formatInfo;
	StoreFormatInfo(formatInfo);

	// ... Make sure archive and file are closed
	CArchive::Close();

	// Then actually tranfer the data if we are storing
	if (m_bClipboardOpen)
		{
		if (IsStoring())
			{
			// Tranfer all the memory blockes to the clipboard
			// ... Clear current contents of clipboard before we store new data
			//     (Test memory blocks will be removed here)
			::EmptyClipboard();
			// ... Store new data
			TransferClipboardFormats();
			}
		// ... Close the clipboard we have opened earlier on
		VERIFY(::CloseClipboard());
		m_bClipboardOpen = FALSE;
		}
	// ... Reset internal variables
	Empty();
	}

void COXClipboard::Abort()
	{
	// First store the last used format (if any) and detach from file
	CFormatInfo formatInfo;
	StoreFormatInfo(formatInfo);

	// ... Make sure archive and file are aborted
	CArchive::Abort();

	if (m_bClipboardOpen)
		{
		// Do not tranfer formats to clipboard (will be lost)
		::EmptyClipboard();
		// ... Close the clipboard we have opened earlier on
		VERIFY(::CloseClipboard());
		m_bClipboardOpen = FALSE;
		}
	// ... Reset internal variables
	Empty();
	}

BOOL COXClipboard::IsFormatAvailable(UINT nFormat)
	{
	return ::IsClipboardFormatAvailable(nFormat);
	}

BOOL COXClipboard::IsFormatAvailable(LPCTSTR pszClipboardFormat)
	{
	UINT nClipboardFormat;
	nClipboardFormat = GetFormatNumber(pszClipboardFormat);
	if (nClipboardFormat == 0)
		{
		TRACE0("COXClipboard::IsFormatAvailable : Failed to register clipboard format\n");
		return FALSE;
		}
	return IsFormatAvailable(nClipboardFormat);
	}

CString COXClipboard::GetFormatName(UINT nFormat)
	{
	CString sFormatName;
	LPTSTR pszFormatName;
	int nLength;
	int nMaxLength = 512;

	pszFormatName = sFormatName.GetBuffer(nMaxLength);
	nLength = ::GetClipboardFormatName(nFormat, pszFormatName, nMaxLength);
	sFormatName.ReleaseBuffer(nLength);
#ifdef _DEBUG
	if (nMaxLength <= nLength)
		TRACE(_T("COXClipboard::GetFormatName : Clipboard format name exceeded max length and was trunctated\n"));
#endif
	return sFormatName;
	}

UINT COXClipboard::GetFormatNumber(LPCTSTR pszClipboardFormat)
	{
	return ::RegisterClipboardFormat(pszClipboardFormat);
	}

COXClipboard::~COXClipboard()
	{
	if (m_bClipboardOpen)
		Close();
	delete m_pSharedFile;
	m_pSharedFile = NULL;
	// Set file pointer to NULL before base class destructor is executed
	// because the file object is already deleted
	m_pFile = NULL;
	}
	
// protected:
void COXClipboard::Empty()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Clears the internal data members
	{
	// Do not empty while still working with clipboard (Close first)
	ASSERT(!m_bClipboardOpen);
	m_nLastUsedFormat = 0;
	m_formatInfos.RemoveAll();
	}

void COXClipboard::StoreFormatInfo(CFormatInfo& formatInfo)
	// --- In  : 
	// --- Out : formatInfo : The format info of the last used format
	// --- Returns : 
	// --- Effect : Stores the information about the currently in use format
	//              in the list of all the formats
	//				This is needed to restore it later or to tranfer it to the clipboard
	//				It will also detach the format from the shared file
	{
	// First store the last used format (if any)
	if (m_nLastUsedFormat != 0)
		{
		// ... Last used format must already be in map of formats
		VERIFY(m_formatInfos.Lookup(m_nLastUsedFormat, formatInfo));
		// ... Flush archive so that file pointer will reflect the correct current position
		Flush();
		formatInfo.m_nPosition = m_pSharedFile->GetPosition();
		formatInfo.m_hBuffer = m_pSharedFile->Detach();
		// ... CSharedFile::Detach() does not call its base class implemention
		//     to reset its data members, so we do it explicitely here
		m_pSharedFile->CMemFile::Detach();
		// ... Store change
		m_formatInfos.SetAt(m_nLastUsedFormat, formatInfo);
		}
	}

void COXClipboard::TransferClipboardFormats()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Adds all the different clipboard formats to the clipboard
	//				This does the actual tranfer
	{
	// Can only tranfer to opned clipboard
	ASSERT(m_bClipboardOpen);
	ASSERT(IsStoring());

	UINT nFormat;
	CFormatInfo formatInfo;
	POSITION pos;
	pos = m_formatInfos.GetStartPosition();
	while (pos != NULL)
		{
		m_formatInfos.GetNextAssoc(pos, nFormat, formatInfo);
		// ... Must be able to set format
		VERIFY(::SetClipboardData(nFormat, formatInfo.m_hBuffer));
		}
	}

// private:

// ==========================================================================
