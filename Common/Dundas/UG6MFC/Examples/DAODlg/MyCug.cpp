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

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"
#include "ugdao.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug::MyCug()
{
	m_arrowCursor = FALSE;
}
/***************************************************
****************************************************/
MyCug::~MyCug()
{
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){
	
	SetUniformRowHeight(TRUE);
}


/***************************************************
****************************************************/
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound){
	if(rowsfound >0){
		SetNumberRows(numrows+rowsfound,FALSE);
	}
}
void MyCug::OnDataSourceNotify(int ID,long msg,long param){
	if ( ID == UGDS_ID_DAO){
		switch (msg) {
		case UGDSM_DAO_EOF:
			break;
		case UGDSM_DAO_UPDATEFAILED:
				break;
		case UGDSM_DAO_KILLEXTRAROW:
				break;
		case UGDSM_DAO_ADJUSTROWS:
			SetNumberRows(param);
			break;
		default:
			break;
		}

	}
}
