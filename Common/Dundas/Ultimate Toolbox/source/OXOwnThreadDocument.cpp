// ==========================================================================
// 							Class Implementation : COXOwnThreadDocument
// ==========================================================================

// Source file : OXOwnThreadDocument.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved

// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXOwnThreadDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(COXOwnThreadDocument, CDocument)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// COXOwnThreadDocument


COXOwnThreadDocument::COXOwnThreadDocument()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : constructs the object
{
}

COXOwnThreadDocument::~COXOwnThreadDocument()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : destructs the object
{
}

void COXOwnThreadDocument::OnFinalRelease()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : will re-route the call if necessary
//				It is important that the destruction of the object is done
//				by the same thread that constructed the object.
//				There for 'FinalReleaseRouter' will check if the call is made by
//				the Owner thread or by the Own thread;
//				In case it is made by the Own thread the call is re-routed and
//				OnFinalRelease returns immediately
{
	if (FinalReleaseRouter())
		return;
	CDocument::OnFinalRelease();
}

LPDISPATCH COXOwnThreadDocument::GetIDispatch(BOOL bAddRef)
{
	return CDocument::GetIDispatch(bAddRef);
}


BEGIN_MESSAGE_MAP(COXOwnThreadDocument, CDocument)
	//{{AFX_MSG_MAP(COXOwnThreadDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COXOwnThreadDocument, CDocument)
	//{{AFX_DISPATCH_MAP(COXOwnThreadDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// COXOwnThreadDocument diagnostics

#ifdef _DEBUG
void COXOwnThreadDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void COXOwnThreadDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



LPUNKNOWN COXOwnThreadDocument::GetInterfaceHook(const void* CIID)
// --- In  : Class ID of the wanted interface
// --- Out : none
// --- Returns : The interface handle
// --- Effect : Re-routes this function to the base class
//				which will determine to hook the marshalled IDispatch handle
//				in case this call is done by the Owner thread
{
	return COXOwnThread::GetInterfaceHook(CIID);	
}


