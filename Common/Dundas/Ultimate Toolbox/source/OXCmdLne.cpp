// ==========================================================================
// 							Class Implementation : COXCommandLine
// ==========================================================================

// Source file : OXCmdLne.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
                        
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <string.h>
#include "OXCmdLne.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXCommandLine, CObject)

#define new DEBUG_NEW

void COXCommandLine::Tokenize(LPTSTR pszCmdLine) 
	{
	LPTSTR delimiters = _T(" =\r\n");
	CString token;
	LPCTSTR curTok = _tcstok(pszCmdLine, delimiters);
	while (curTok != NULL)
		{
		if (*curTok == _T('\'') || *curTok == _T('"'))
			{
			TCHAR quote[2];
			*quote = *curTok;
			quote[1] = 0;
			LPTSTR pLastToken = _tcsrchr(curTok, quote[0]);
			if (pLastToken != curTok)
				{
				*pLastToken = '\0';
				token = (curTok + 1);
				curTok = token;
				}
			else
				{
				token = (curTok + 1);
				token += _T(" ");
				curTok = _tcstok(NULL, quote);
				token += curTok;
				curTok = token;
				}
			}
		
		m_Tokens.Add(curTok);
		m_NumTokens++;
		curTok = _tcstok(NULL, delimiters);
		}

	// A sentinel
	m_Tokens.Add(_T("|"));
	}

COXCommandLine::COXCommandLine(LPCSTR psczCmdLine)
	{
	CString sCmdLine(psczCmdLine);
	m_Tokens.RemoveAll();
	m_NumTokens = 0;
	Tokenize(sCmdLine.GetBuffer(0));

	sCmdLine.ReleaseBuffer();
	}

#ifdef WIN32
COXCommandLine::COXCommandLine(LPCWSTR psczCmdLine)
	{
	CString sCmdLine(psczCmdLine);
	m_Tokens.RemoveAll();
	m_NumTokens = 0;
	Tokenize(sCmdLine.GetBuffer(0));

	sCmdLine.ReleaseBuffer();
	}       
	
#endif

COXCommandLine::COXCommandLine(CStdioFile* pInfile)
	{
	m_Tokens.RemoveAll();
	m_NumTokens = 0;
	TCHAR ReadLine[256];
	while (pInfile->ReadString(ReadLine, 256) != NULL)
		Tokenize(ReadLine);
	}

COXCommandLine::~COXCommandLine()
	{
	}
