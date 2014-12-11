// CBase1Doc.h : interface of the CCBase1Doc class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugcode.h"

#if !defined(AFX_CBASE1DOC_H__4F93F01F_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_)
#define AFX_CBASE1DOC_H__4F93F01F_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCBase1Doc : public CDocument
{
protected: // create from serialization only
	CCBase1Doc();
	DECLARE_DYNCREATE(CCBase1Doc)

// Attributes
public:

    // our CodeBase data source...
    CUGCBDataSource m_data;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBase1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCBase1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCBase1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBASE1DOC_H__4F93F01F_EB8A_11D2_8A3A_0080C86AC2FB__INCLUDED_)
