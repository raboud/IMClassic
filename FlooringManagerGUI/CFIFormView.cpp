/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "CFIFormView.h"

CCFIFormView::CCFIFormView(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{
}

CCFIFormView::CCFIFormView(LPCTSTR lpszTemplateName)
	: CFormView(lpszTemplateName)
{
}

CCFIFormView::~CCFIFormView(void)
{
	CFormView::~CFormView();
}
