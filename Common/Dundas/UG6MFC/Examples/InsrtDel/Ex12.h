// Ex12.h : main header file for the EX12 application
//

#if !defined(AFX_EX12_H__CF04F2F3_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
#define AFX_EX12_H__CF04F2F3_0EB5_11D1_B1F1_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx12App:
// See Ex12.cpp for the implementation of this class
//

class CEx12App : public CWinApp
{
public:
	CEx12App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx12App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12_H__CF04F2F3_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
