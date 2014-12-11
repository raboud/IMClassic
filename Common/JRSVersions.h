/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#ifndef _VERSIONS_h
#define _VERSIONS_h

#include "winver.h"

class CJRSVersion : public CObject
{
	public:
		CJRSVersion();
		CJRSVersion(bool bRetrieveInfo);
		virtual ~CJRSVersion();

		void DisplayBetaMessage() const;
		void DisplayDebugMessage() const;
		inline CString GetAppName() const;
		inline CString GetCopyright() const;
		inline CString GetProductName() const;
		inline CString GetProductVersion() const;
		inline CString GetProductBuild() const;
		inline CString GetAboutText() const;
		inline CString GetCompleteVersionInfo() const;
		inline bool IsBeta() const;
		inline bool IsDebug() const;
		inline bool IsValid() const;
		void RetrieveInfo();

	protected:
		void ClearInfo();

		struct SuVersionInfo
		{
			CString	csAppName;
			CString	csCopyright;
			CString	csProductName;
			CString	csProductVersion;
			CString	csProductBuild;
			CString	csAboutText;
			CString csCompleteVersionInfo;
			bool		bIsDebug;
			bool		bIsBeta;
		};
		SuVersionInfo m_suInfo;
		bool m_bRetrievedInfo;
};

inline CString CJRSVersion::GetAppName() const
{
	return m_suInfo.csAppName;
}

inline CString CJRSVersion::GetCopyright() const
{
	return m_suInfo.csCopyright;
}

inline CString CJRSVersion::GetProductName() const
{
	return m_suInfo.csProductName;
}

inline CString CJRSVersion::GetProductVersion() const
{
	return m_suInfo.csProductVersion;
}


inline CString CJRSVersion::GetProductBuild() const
{
	return m_suInfo.csProductBuild;
}

inline CString CJRSVersion::GetAboutText() const
{
	return m_suInfo.csAboutText;
}

inline bool CJRSVersion::IsBeta() const
{
	return m_suInfo.bIsBeta;
}

inline bool CJRSVersion::IsDebug() const
{
	return m_suInfo.bIsDebug;
}

inline bool CJRSVersion::IsValid() const
{
	return m_bRetrievedInfo;
}

inline CString CJRSVersion::GetCompleteVersionInfo() const
{
	return m_suInfo.csCompleteVersionInfo;
}

#endif
