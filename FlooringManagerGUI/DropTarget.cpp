// DropTarget.cpp : implementation file
//

#include "stdafx.h"
#include "DropTarget.h"
#include "CPath.h"

const CLIPFORMAT CF_FILEDESCRIPTOR = (CLIPFORMAT) RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR) ;
const CLIPFORMAT CF_FILECONTENTS = (CLIPFORMAT) RegisterClipboardFormat(CFSTR_FILECONTENTS);

// DropTarget

IMPLEMENT_DYNAMIC(DropTarget, COleDropTarget)


DropTarget::DropTarget()
: m_nMaxCount(1)
, m_strFolder(_T("c:/temp/DandDout/%s"))
, m_dropEffect(DROPEFFECT_NONE)
{
	
}

DropTarget::~DropTarget()
{
}


BEGIN_MESSAGE_MAP(DropTarget, COleDropTarget)
END_MESSAGE_MAP()



// DropTarget message handlers


DROPEFFECT DropTarget::OnDragEnter(CWnd* /* pWnd */, COleDataObject* pDataObject, DWORD /* dwKeyState */, CPoint /* point */)
{
	CStringArray fileNames;

	if (pDataObject->IsDataAvailable(CF_HDROP))
	{
		HGLOBAL hg;
		HDROP   dropInfo;

		// Get the HDROP data from the data object.
		hg = pDataObject->GetGlobalData(CF_HDROP);

		if (NULL == hg)
		{
			return FALSE;
		}
		dropInfo = (HDROP)GlobalLock(hg);

		if (NULL == dropInfo)
		{
			GlobalUnlock(hg);
			return FALSE;
		}

		CString sFile;
		DWORD nBuffer = 0;

		// Get the number of files dropped
		UINT nFilesDropped = DragQueryFile(dropInfo, 0xFFFFFFFF, NULL, 0);

		for (UINT i = 0; i < nFilesDropped; i++)
		{
			// Get the buffer size for the first filename
			nBuffer = DragQueryFile(dropInfo, i, NULL, 0);

			// Get path and name of the first file
			DragQueryFile(dropInfo, i, sFile.GetBuffer(nBuffer + 1), nBuffer + 1);
			sFile.ReleaseBuffer();
			CString file = CPath::GetFileName(sFile);
			CString dest = CPath::AddPathAndFile(this->m_strFolder, file);
			::CopyFile(sFile, dest, FALSE);
			fileNames.Add(dest);
		}

		// Free the memory block containing the dropped-file information
		DragFinish(dropInfo);
		GlobalUnlock(hg);
	}
	else if (pDataObject->IsDataAvailable( CF_FILEDESCRIPTOR))
	{
		HGLOBAL hMem = pDataObject->GetGlobalData(CF_FILEDESCRIPTOR);
		if (hMem != NULL)
		{
			LPFILEGROUPDESCRIPTOR lpFGD = (LPFILEGROUPDESCRIPTOR)::GlobalLock(hMem);
			if (lpFGD != NULL)
			{
				FILEDESCRIPTOR* pFD = lpFGD->fgd;
				for (UINT i = 0; i < lpFGD->cItems; i++)
				{
					CString* pFileName = new CString(pFD->cFileName);
					fileNames.Add(*pFileName);
					pFD++;
				}
				GlobalFree(hMem);
			}
		}

	}

	CString strTemp ;
	if (m_nMaxCount <= 0 || fileNames.GetCount() <= m_nMaxCount)
	{
		for (int i = 0; i < fileNames.GetCount(); i++)
		{
			strTemp += fileNames.GetAt(i);
			m_dropEffect = DROPEFFECT_COPY;
		}
	}
	return m_dropEffect;
}


void DropTarget::OnDragLeave(CWnd* /* pWnd */)
{
	this->m_dropEffect = DROPEFFECT_NONE;
}


DROPEFFECT DropTarget::OnDragOver(CWnd* /* pWnd */ , COleDataObject* /* pDataObject */, DWORD /* dwKeyState */, CPoint /* point */)
{
	return this->m_dropEffect;
}


BOOL DropTarget::OnDrop(CWnd* /* pWnd */, COleDataObject* pDataObject, DROPEFFECT /* dropEffect */, CPoint /* point */)
{
	//	return TRUE;
	return DoPasteDate(pDataObject);
}


BOOL DropTarget::DoPasteDate(COleDataObject* pDataObject)
{
	if (pDataObject->IsDataAvailable(CF_HDROP))
	{
		HGLOBAL hg;
		HDROP   dropInfo;

		// Get the HDROP data from the data object.
		hg = pDataObject->GetGlobalData(CF_HDROP);

		if (NULL == hg)
		{
			return FALSE;
		}
		dropInfo = (HDROP)GlobalLock(hg);

		if (NULL == dropInfo)
		{
			GlobalUnlock(hg);
			return FALSE;
		}

		CString sFile;
		DWORD nBuffer = 0;

		// Get the number of files dropped
		UINT nFilesDropped = DragQueryFile(dropInfo, 0xFFFFFFFF, NULL, 0);

		for (UINT i = 0; i < nFilesDropped; i++)
		{
			// Get the buffer size for the first filename
			nBuffer = DragQueryFile(dropInfo, i, NULL, 0);

			// Get path and name of the first file
			DragQueryFile(dropInfo, i, sFile.GetBuffer(nBuffer + 1), nBuffer + 1);
			sFile.ReleaseBuffer();

			m_fileNames.Add(sFile);
		}

		// Free the memory block containing the dropped-file information
		DragFinish(dropInfo);
		GlobalUnlock(hg);
	}
	else if (pDataObject->IsDataAvailable(CF_FILEDESCRIPTOR))
	{
		HGLOBAL hMem = pDataObject->GetGlobalData(CF_FILEDESCRIPTOR);
		if (hMem != NULL)
		{
			LPFILEGROUPDESCRIPTOR lpFGD = (LPFILEGROUPDESCRIPTOR)::GlobalLock(hMem);
			if (lpFGD != NULL)
			{
				FILEDESCRIPTOR* pFD = lpFGD->fgd;
				FORMATETC fmc;
				fmc.cfFormat = CF_FILECONTENTS;
				fmc.dwAspect = DVASPECT_CONTENT;
				fmc.tymed = TYMED_FILE | TYMED_HGLOBAL | TYMED_ISTREAM
					;
				fmc.ptd = NULL;

				for (UINT i = 0; i < lpFGD->cItems; i++)
				{
					fmc.lindex = i;
					CFile* pFile = pDataObject->GetFileData(CF_FILECONTENTS, &fmc);

					CString pFileName; 
					pFileName.Format(m_strFolder, pFD->cFileName);
					m_fileNames.Add(pFileName);
					CFile* outFile = new CFile();

					outFile->Open(pFileName, CFile::modeWrite |
						CFile::shareExclusive | CFile::modeCreate);
					BYTE buffer[4096];
					DWORD dwRead;

					do
					{
						dwRead = pFile->Read(buffer, sizeof(buffer));
						outFile->Write(buffer, dwRead);
					}
					while (dwRead > 0);
					outFile->Close();
					delete(outFile);
					delete(pFile);
					pFD++;
				}
				GlobalFree(hMem);
			}
		}

	}
	HWND parent = CWnd::FromHandle(this->m_hWnd)->GetParent()->m_hWnd;

	::PostMessage(parent, wm_FILES_DROPPED, 0, (LPARAM) this);
	return 0;
}

void DropTarget::UpdateControl()
{
	::SetWindowText(this->m_hWnd, m_fileNames.GetAt(0));
}
