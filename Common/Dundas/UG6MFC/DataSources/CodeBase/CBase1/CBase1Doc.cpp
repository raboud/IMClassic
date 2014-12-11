// CBase1Doc.cpp : implementation of the CCBase1Doc class
//

#include "stdafx.h"
#include "MyCug.h"

#include "CBase1.h"

#include "CBase1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBase1Doc

IMPLEMENT_DYNCREATE(CCBase1Doc, CDocument)

BEGIN_MESSAGE_MAP(CCBase1Doc, CDocument)
	//{{AFX_MSG_MAP(CCBase1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBase1Doc construction/destruction

CCBase1Doc::CCBase1Doc()
{
	// TODO: add one-time construction code here
    
}

CCBase1Doc::~CCBase1Doc()
{
}

BOOL CCBase1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCBase1Doc serialization

void CCBase1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCBase1Doc diagnostics

#ifdef _DEBUG
void CCBase1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCBase1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCBase1Doc commands

BOOL CCBase1Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	//if (!CDocument::OnOpenDocument(lpszPathName))
	//	return FALSE;
	

    if(UG_SUCCESS != m_data.Open(lpszPathName, NULL))
        return FALSE;

	
	return TRUE;
}
