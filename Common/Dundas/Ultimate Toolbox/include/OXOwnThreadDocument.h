// ==========================================================================
// 							Class Specification : COXOwnThreadDocument
// ==========================================================================

// Header file : OXOwnThreadDocument.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	This class is an alternative for CDocument. It offers multi-threading
//	functionality to your automation server.
//	By deriving from this class instead of CDocument, all your OLE calls
//	are handled by a separate Own thread. In that way more concurrently 
//	calls can be handled simultaneously.
//	The main part of the implementation is done in the COXOwnThread class, so 
//	the code can be shared by other derivation of CCmdTarget.

// HOW TO USE -> it is as easy as this:
//	As said above, you need to derive from this class instead of CDocument.
//	Further more you need to call the 'EnableOwnthread' function from within
//	the constructor of your derived class.
//	If you are overriding the 'OnFinalRelease' function of CDocument
//	you need also to call 'FinalReleaseRouter()' (see 'FinalReleaseRouter' further on)

//	For derivation of CCmdTarget you have to use COXOwnThreadCmdTarget.
//	For other derivation you can build your own class analogue to COXOwnThreadCmdTarget
//	and COXOwnThreadDocument.

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXOWNTHREADDOCUMENT_H__
#define __OXOWNTHREADDOCUMENT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXOwnThread.h"


/////////////////////////////////////////////////////////////////////////////
// COXOwnThreadDocument document

class OX_CLASS_DECL COXOwnThreadDocument : public CDocument, public COXOwnThread
{
DECLARE_DYNCREATE(COXOwnThreadDocument)

// Data Members
public:

protected:

private:

// Member Functions
public:
	virtual ~COXOwnThreadDocument();

//	The public interface of this class contains 3 easy functions.
//	They are defined in COXOwnThread where this class is derived from:

//	BOOL EnableOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : If the own thread is started successful or not
	//				 This function should always succeed unless
	//				 the operating systems is extremely low on resources
	// --- Effect :  All the OLE Calls to this object will be re-routed
	//				 by the own thread.
	//				 Different objects can be served simultaneous.

//	BOOL HasOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : if the CmdTarget has a own thread started.
	// --- Effect : 

//	BOOL FinalReleaseRouter();
	// --- In  : none
	// --- Out : none
	// --- Returns : if the call is re-routed or not
	// --- Effect : If you override the virtual member function 'OnFinalRelease' of CCmdTarget,
	//				you have to call this function before you do anything else.
	//				If the call returns TRUE, you have to return immediately.
	//	Example:
	//	void CMyCmdTarget::OnFinalRelease()
	//	{
	//		if (FinalReleaseRouter())
	//			return;
	//
	//		// TODO: Add your specialised code here and/or call the base class
	//
	//		CCmdTarget::OnFinalRelease();
	//	}

	virtual LPDISPATCH GetIDispatch(BOOL bAddRef);
	// --- In  : bAddRef: Specifies whether to increment the reference count for the object.
	// --- Out : none
	// --- Returns : The IDispatch pointer associated with the object
	// --- Effect : provides access to the IDispatch handle
	//				Is used by the COXOwnThread base class


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXOwnThreadDocument)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COXOwnThreadDocument();           // protected constructor used by dynamic creation

	virtual LPUNKNOWN GetInterfaceHook(const void*);

	//{{AFX_MSG(COXOwnThreadDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COXOwnThreadDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

private:

};

#endif //__OXOWNTHREADDOCUMENT_H__