/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxext.h"

class CCFIFormView : public CFormView
{
public:
	CCFIFormView(UINT nIDTemplate);
	CCFIFormView(LPCTSTR lpszTemplateName);
	~CCFIFormView(void);
	virtual void Refresh();
};

inline void CCFIFormView::Refresh()
{
}