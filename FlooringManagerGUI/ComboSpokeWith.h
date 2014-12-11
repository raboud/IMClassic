/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once


// CComboSpokeWith

class CComboSpokeWith : public CComboBox
{
	DECLARE_DYNAMIC(CComboSpokeWith)

public:
	CComboSpokeWith();
	virtual ~CComboSpokeWith();

	void PopulateList(int iNoteTypeID);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


