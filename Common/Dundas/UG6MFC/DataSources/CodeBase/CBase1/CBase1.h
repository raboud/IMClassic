// CBase1.h : main header file for the CBASE1 application
//

#if !defined(AFX_CBASE1_H__4F93F017_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_)
#define AFX_CBASE1_H__4F93F017_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCBase1App:
// See CBase1.cpp for the implementation of this class
//

class CCBase1App : public CWinApp
{
public:
	CCBase1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBase1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCBase1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBASE1_H__4F93F017_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_)
