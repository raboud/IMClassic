/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

/***************************************************
This is the MyCug CUGCtrl derived class with the 
addition of TRACE statements to allow the various
notification sequences to be seen in the output 
window.  The OnMouseMove and OnGetCell notification
TRACE statements are commented out so as to reduce 
the clutter!  
****************************************************/

#include "stdafx.h"
#include "d4all.hpp"
#include "ugcode.h"

#include "resource.h"
#include "MyCug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug::MyCug()
{
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
void MyCug::OnSetup()
{
}

/***************************************************
****************************************************/
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
    if(0 != rowsfound)
        SetNumberRows(numrows + rowsfound);
}
