/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// FlooringDoc.cpp : implementation of the CFlooringDoc class
//

#include "stdafx.h"
#include "Flooring.h"

#include "FlooringDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlooringDoc

IMPLEMENT_DYNCREATE(CFlooringDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlooringDoc, CDocument)
	//{{AFX_MSG_MAP(CFlooringDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlooringDoc construction/destruction

CFlooringDoc::CFlooringDoc()
{
	// TODO: add one-time construction code here

}

CFlooringDoc::~CFlooringDoc()
{
}

BOOL CFlooringDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFlooringDoc serialization

void CFlooringDoc::Serialize(CArchive& ar)
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
// CFlooringDoc diagnostics

#ifdef _DEBUG
void CFlooringDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlooringDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlooringDoc commands
