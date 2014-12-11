/*************************************************************************
				Class Declaration : CUGAutoFontType
**************************************************************************
	Source file : UGCTAfnt.cpp
	Header file : UGCTAfnt.h
	Copyright © Dundas Software Ltd. 1994 - 2002, All Rights Reserved

    Purpose
		This class will automatically size the font of any cell using 
		this celltype so that all of the text will be visible.
*************************************************************************/
#ifndef _UGCTAfnt_H_
#define _UGCTAfnt_H_


//CUGAutoFontType class declaration
class UG_CLASS_DECL CUGAutoFontType: public CUGCellType
{
protected:

	HFONT CreateAutoSizeFont(HDC hdc, RECT *rect,LPCTSTR string);

public:

	CUGAutoFontType();
	~CUGAutoFontType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);

};

#endif //#ifndef _UGCTAfnt_H_