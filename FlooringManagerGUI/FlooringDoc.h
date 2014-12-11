/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// FlooringDoc.h : interface of the CFlooringDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOORINGDOC_H__ED42B299_4E43_4159_9923_B6767AA949C7__INCLUDED_)
#define AFX_FLOORINGDOC_H__ED42B299_4E43_4159_9923_B6767AA949C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SetCustomer.h"


class CFlooringDoc : public CDocument
{
protected: // create from serialization only
	CFlooringDoc();
	DECLARE_DYNCREATE(CFlooringDoc)

// Attributes
public:
	//CSetCustomer m_flooringSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlooringDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlooringDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlooringDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOORINGDOC_H__ED42B299_4E43_4159_9923_B6767AA949C7__INCLUDED_)
