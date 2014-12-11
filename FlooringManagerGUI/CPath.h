
#pragma once

class CPath
{
public:
	//
	//	Returns the file portion from a path
	//
	static CString GetFileOnly(CString Path)
	{
		//	Strip off the path and return just the filename part
		CString temp(Path); // Force CString to make a copy
		::PathStripPath(temp.GetBuffer(0));
		temp.ReleaseBuffer(-1);
		return temp;
	};
	//
	//	Returns the folder portion from a path
	//
	static CString GetFolderOnly(CString Path)
	{
		//	Strip off the file name so we can direct the file scanning dialog to go
		//	back to the same directory as before.
		CString temp = CString(Path); // Force CString to make a copy
		::PathRemoveFileSpec(temp.GetBuffer(0));
		temp.ReleaseBuffer(-1);
		return temp;
	};
	//
	//	Adds a backslash to the end of a path if it is needed
	//
	//static CString AddSlash(CString Path)
	//{
	//	CString cs = Path;
	//	::PathAddBackslash(cs.GetBuffer(_MAX_PATH));
	//	cs.ReleaseBuffer(-1);
	//	if (cs.IsEmpty())
	//		cs = BACK_SLASH;
	//	return cs;
	//}
	//
	//	Removes a backslash from the end of a path if it is there
	//
	static CString RemoveSlash(CString Path)
	{
		CString cs = Path;
		::PathRemoveBackslash(cs.GetBuffer(_MAX_PATH));
		cs.ReleaseBuffer(-1);
		return cs;
	};
	//
	//	Adds a folder path and file together to make a file path
	//
	static CString AddPathAndFile(CString Folder, CString File)
	{
		CString cs = Folder;
		::PathAddBackslash(cs.GetBuffer(_MAX_PATH));
		::PathAppend(cs.GetBuffer(_MAX_PATH), File);
		cs.ReleaseBuffer(-1);
		return cs;
	};
	//
	//	Adds a .ext to the end of a file path
	//
	static CString AddExt(CString Path, CString Ext)
	{
		CString cs = Path;
		::PathAddExtension(cs.GetBuffer(_MAX_PATH), Ext);
		cs.ReleaseBuffer(-1);
		return cs;
	};
	//
	//	Returns true if file exists or false if file does not exist
	//
	static BOOL FileExists(CString Path)
	{
		return (::PathFileExists(Path));
	};
	//
	//	Returns true if file is read only
	//
	static BOOL FileReadOnly(CString Path)
	{
		DWORD nAttributes;
		if ((nAttributes = GetFileAttributes(Path)) != -1) {
			if (nAttributes & FILE_ATTRIBUTE_READONLY)
				return true;
		}
		return false;
	};
	//
	// Returns just the .ext part of the file path
	//
	static CString GetFileExt(CString Path)
	{
		CString cs;
		cs = ::PathFindExtension(Path);
		return cs;
	};
	static CString GetFileName(CString Path)
	{
		CString csFile = GetFileOnly(Path);
		if (!GetFileExt(csFile).IsEmpty()) { // Is there an extension
			::PathRemoveExtension(csFile.GetBuffer(_MAX_PATH));
			csFile.ReleaseBuffer();
		}
		return csFile;
	};
	//
	// Exchanges one file extension for another and returns the new fiel path
	//
	static CString RenameFileExt(CString Path, CString Ext)
	{
		CString cs = Path;
		::PathRenameExtension(cs.GetBuffer(_MAX_PATH), Ext);
		return cs;
	};
};