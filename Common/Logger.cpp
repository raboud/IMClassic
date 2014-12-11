#include "stdafx.h"
#include "windows.h"
//#include "stdio.h"
#include "logger.h"


bool Logger::LogMessage(CString messageToLog)
{
	CString newMessage;
	newMessage.Format("[INFO] - \t\t%s", messageToLog);
	return Log(newMessage);
}

bool Logger::LogError(CString messageToLog)
{
	CString newMessage;
	newMessage.Format("[ERROR] - \t\t%s", messageToLog);
	return Log(newMessage);
}

bool Logger::LogException(CString messageToLog)
{
	CString newMessage;
	newMessage.Format("[EXCEPTION] - \t%s", messageToLog);
	return Log(newMessage);
}

bool Logger::Log(CString messageToLog)
{
	bool bSuccessful = true;

	try
	{
		CString fileName;
		CString pathName;
		TCHAR specialFolderPathName[MAX_PATH];
		SHGetSpecialFolderPath(0, specialFolderPathName, CSIDL_APPDATA, FALSE);	
		pathName.Format("%s\\InstallationManager", specialFolderPathName);
		if (GetFileAttributes(pathName) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(pathName, NULL);
		}
		COleDateTime dt = COleDateTime::GetCurrentTime();
		fileName.Format("%s\\IMClassic_%s.log", pathName, dt.Format("%m%d%Y"));
		CStdioFile fileOut(fileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) ;
		fileOut.SeekToEnd();

		messageToLog.Format("%s  %s\r\n", dt.Format("%Y-%m-%d %H:%M:%S"), messageToLog);

		fileOut.WriteString(messageToLog) ;
		fileOut.Close();
	}
	catch (CMemoryException* /* e */)
	{
		bSuccessful = false;
	}
	catch (CFileException* /* e */)
	{
		bSuccessful = false;
	}
	catch (CException* /* e */)
	{
		bSuccessful = false;
	}	

	return bSuccessful;
}