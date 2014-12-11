// ==========================================================================
// 					Class Specification : COXBrilliantObj
// ==========================================================================

// Header file : OXBObj.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class makes transactions possible
//  After you have started the transaction, you can make modifications to the object
//	Then you can commit these changes (make them permananent)
//	 or roll them back (discard them)

// Remark:
//	Transactions can be nested, so you can start a second transaction
//	 when the first is still running

// Prerequisites (necessary conditions):
//	In order to work for derived classes, your class must have a 
//		- copy constructor
//		- assignment operator
//	You must also add the macro call
//		DECLARE_BCOPY(class) to your specification (.h)
//		IMPLEMENT_BCOPY(class, base_clase) to your implementation (.cpp)
//		This latter will make a virtual copy and assignment function
//  Every function that modifies the object must call SetModified()
//		BEFORE modifying the object

/////////////////////////////////////////////////////////////////////////////

#ifndef __BOBJ_H__
#define __BOBJ_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXBCopy.h"
#include "OXStack.h"


template <class T> class COXSPtr;

class OX_CLASS_DECL COXBrilliantObj : public CObject
{
DECLARE_SERIAL(COXBrilliantObj)
DECLARE_BCOPY(COXBrilliantObj)

// Data members -------------------------------------------------------------
public:
	
protected:
	BOOL m_bModified;
	COXStack<COXBrilliantObj*, COXBrilliantObj*> m_transactionStack;

private:
	
// Member functions ---------------------------------------------------------
public:
	virtual void SetModified(BOOL bModified = TRUE);
	// --- In  : bModified : Whether the object is modified
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the modified state
	//				SetModified(TRUE) corresponds only to this object itself
	//				SetModified(FALSE) is passed on to possible child objects
	
	virtual BOOL IsModified() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether this object itself or one of its possible child objects 
	//               has been modified
	// --- Effect : 

	virtual void StartTransaction(BOOL bDeferCopy = TRUE);
	// --- In  : bDeferCopy : Whether a transaction copy should be taken at the 
	//						  first change (TRUE) or at the start of the 
	//						  transaction (FALSE)
	// --- Out : 
	// --- Returns :
	// --- Effect : Starts a transaction

	virtual void Commit();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Commits the work that has been done since the transaction
	//				started

	virtual void Rollback();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Rolls back since the transaction started
	//				All the chenges will be discarded
	
	virtual LONG GetTransactionLevel() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The nesting level of the started transactions
	// --- Effect : 

	virtual void Serialize(CArchive& ar);
    // --- In  : ar : The archive to which this object will be serialized
	// --- Out : 
	// --- Returns : 
	// --- Effect : 

#ifdef _DEBUG
	virtual void AssertValid() const;
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	
	virtual void Dump(CDumpContext& dc) const;
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
#endif

protected:
	COXBrilliantObj();
	COXBrilliantObj(const COXBrilliantObj& brilliantObj);
	COXBrilliantObj& operator=(const COXBrilliantObj& brilliantObj);

	void MakeTransactionCopy();
	void ClearTransactionStack();

	virtual ~COXBrilliantObj();

private:
                   
};

#endif // __OXBOBJ_H__
// ==========================================================================
