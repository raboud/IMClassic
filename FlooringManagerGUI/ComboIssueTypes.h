/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

#include "SetIssueTypes.h"

// CComboIssueTypes

class CComboIssueTypes : public CComboBox
{
	DECLARE_DYNAMIC(CComboIssueTypes)

public:
	CComboIssueTypes();
	virtual ~CComboIssueTypes();

protected:
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();
};


