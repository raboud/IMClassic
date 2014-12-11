#if !defined(_OX_CURSOR__)
#define _OX_CURSOR__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"



class OX_CLASS_DECL COXCursor
{
public:
	COXCursor(HCURSOR hCursor)
	{
		Init();
		m_bRestorePreviousCursor=TRUE;
		SetCursor(hCursor);
	}

	COXCursor(LPCTSTR lpszResource, HINSTANCE hResourceInstance)
	{
		Init();
		HCURSOR hCursor=NULL;
		if(hResourceInstance==NULL)
			hCursor=::LoadCursor(hResourceInstance,lpszResource);
		else
			hCursor=(HCURSOR)::LoadImage(hResourceInstance,
				lpszResource,IMAGE_CURSOR,0,0,LR_SHARED);
		if(hCursor==NULL)
		{
			TRACE(_T("COXCursor: failed to load the cursor from resource\n"));
			return;
		}
		m_bRestorePreviousCursor=TRUE;
		SetCursor(hCursor);
	}

	COXCursor(LPCTSTR lpszFileName)
	{
		Init();
		HCURSOR hCursor=::LoadCursorFromFile(lpszFileName);
		if(hCursor==NULL)
		{
			TRACE(_T("COXCursor: failed to load the cursor from file\n"));
			return;
		}
		m_bRestorePreviousCursor=TRUE;
		SetCursor(hCursor);
	}

	operator HCURSOR()
	{
		return m_hCursor;
	}

	virtual ~COXCursor()
	{
		RestoreCursor();
	}


protected:
	HCURSOR m_hCursor;
	HCURSOR m_hPrevCursor;
	BOOL m_bRestorePreviousCursor;
	BOOL m_bDestroyCursor;

	void SetCursor(HCURSOR hCursor)
	{
		m_hCursor=hCursor;
		m_hPrevCursor=::SetCursor(m_hCursor);
	}

	void RestoreCursor()
	{
		if(m_bRestorePreviousCursor)
		{
			::SetCursor(m_hPrevCursor);
		}

		if(m_bDestroyCursor)
		{
			ASSERT(m_hCursor!=NULL);
			DestroyCursor(m_hCursor);
		}

		Init();
	}

	void Init()
	{
		m_hCursor=NULL;
		m_hPrevCursor=NULL;
		m_bRestorePreviousCursor=FALSE;
		m_bDestroyCursor=FALSE;
	}
};


#endif	//	_OX_CURSOR__