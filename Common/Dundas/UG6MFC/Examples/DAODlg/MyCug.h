/***********************************************
	Ultimate Grid
	Copyright 1994 - 2001 Dundas Software Ltd.


	class 
		CUGMyCug
	Purpose
		General purpose derived grid class.
		This class can be used as a starting 
		point for any grid project.
************************************************/
#include "ugctrl.h"

class MyCug:public CUGCtrl
{

public:

	BOOL m_arrowCursor;

	CFont m_font;
	CPen m_pen;
					
	MyCug();
	~MyCug();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyCug)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	
	//data source notifications
	virtual void OnDataSourceNotify(int ID,long msg,long param);


};
