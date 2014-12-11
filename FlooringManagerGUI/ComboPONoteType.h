/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once


// CComboPONoteType

class CComboPONoteType : public CComboBox
{
	DECLARE_DYNAMIC(CComboPONoteType)

public:
	CComboPONoteType();
	virtual ~CComboPONoteType();
	void PopulateList(bool bShowAll);
	CString GetCurrentLBText();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

};


