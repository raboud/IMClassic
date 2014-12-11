#pragma once


// CListBoxDivision

class CListBoxDivision : public CListBox
{
	DECLARE_DYNAMIC(CListBoxDivision)

public:
	CListBoxDivision();
	virtual ~CListBoxDivision();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


