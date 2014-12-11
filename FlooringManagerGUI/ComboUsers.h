/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once


// CComboUsers

class CComboUsers : public CComboBox
{
	DECLARE_DYNAMIC(CComboUsers)

public:
	CComboUsers();
	virtual ~CComboUsers();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


