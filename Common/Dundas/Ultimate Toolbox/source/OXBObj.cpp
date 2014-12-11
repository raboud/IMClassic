// ==========================================================================
//				Class Implementation : COXBrilliantObj
// ==========================================================================

// Source file : OXBObj.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXBObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(COXBrilliantObj, COXBrilliantObj, 1 | VERSIONABLE_SCHEMA)
IMPLEMENT_BCOPY(COXBrilliantObj, CObject)

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// protected:
	// BOOL m_bModified;
	// --- Whether this object has been modified

	// COXStack<COXBrilliantObj*, COXBrilliantObj*> m_transactionStack;
	// --- A stack of rollback copies of this object
	//	   When a transaction is started a new element pointer is added
	//	   This element can be NULL when no copy needs to be taken yet
	//	   Transaction state :
	//	   	 m_transactionStack.GetCount() is the nesting level of transactions
	//		 m_transactionStack.IsEmpty() when no transactions have been started

// private:
	
// Member functions ---------------------------------------------------------
// public:

void COXBrilliantObj::SetModified(BOOL bModified /* = TRUE */)
	{
	ASSERT_VALID(this);
	// First check whether a copy need to be made
	if (bModified && 					 	// needs copy
		!m_transactionStack.IsEmpty() && 	// transaction started 
		m_transactionStack.Peek() == NULL	// no copy taken yet
		)
		{
		// Modification during transaction : make copy 
		MakeTransactionCopy();
		}
	// THEN adjust the modified flag (the order of these statements is important!)
	m_bModified = bModified;

	// No child objects to pass on to
	}
	
BOOL COXBrilliantObj::IsModified() const
	{
	return m_bModified;
	}

void COXBrilliantObj::StartTransaction(BOOL bDeferCopy /* = TRUE */)
	{
	ASSERT_VALID(this);
	m_transactionStack.Push(NULL);
	if (!bDeferCopy)
		// Make a transaction copy at the start of the transaction
		MakeTransactionCopy();
	}
	
void COXBrilliantObj::Commit()
	{
	ASSERT_VALID(this);
	if (m_transactionStack.IsEmpty())
		{
		TRACE(TEXT("COXBrilliantObj::Commit : No transaction started\n"));
		ASSERT(FALSE);
		return;
		}

	// If old copy was saved, pop it (may be NULL)
	COXBrilliantObj* pLastObj = m_transactionStack.Pop();
	if ( (pLastObj != NULL) &&
	     !m_transactionStack.IsEmpty() && 
		 (m_transactionStack.Peek() == NULL) )
		{
		// Nested transaction where only the top has a copy
		// Move this copy one level down
		m_transactionStack.Peek() = pLastObj;
		}
	else
		delete pLastObj;
	}
	
void COXBrilliantObj::Rollback()
	{
	ASSERT_VALID(this);
	if (m_transactionStack.IsEmpty())
		{
		TRACE(TEXT("COXBrilliantObj::Rollback : No transaction started\n"));
		ASSERT(FALSE);
		return;
		}
	
	COXBrilliantObj* pRollbackCopy = m_transactionStack.Pop();
	if(pRollbackCopy != NULL)
		// If changes where made and old copy was saved, restore old copy
		{
		// Temporary store modification state of the rollback copy
		// because VirtualCopy (operator=) may set this flag to TRUE
		BOOL bTempModified = pRollbackCopy->m_bModified;
		VirtualCopy(pRollbackCopy);
		m_bModified = bTempModified;
		if (!m_transactionStack.IsEmpty() && (m_transactionStack.Peek() == NULL) )
			{
			// Nested transaction where only the top has a copy
			// Move this copy one level down
			m_transactionStack.Peek() = pRollbackCopy;
			}
		else
			delete pRollbackCopy;
		}
	}

LONG COXBrilliantObj::GetTransactionLevel() const
	{
	return m_transactionStack.GetCount();
	}

void COXBrilliantObj::Serialize(CArchive& /* ar */)
	{
	// This is a base class : nothing to serialize
	}

#ifdef _DEBUG
void COXBrilliantObj::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXBrilliantObj::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	dc << "\nm_bModified : " << m_bModified;
	dc << "\nm_transactionStack : " << (void*)&m_transactionStack;
	}
#endif //_DEBUG

// protected:
COXBrilliantObj::COXBrilliantObj()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs an object
	:
	m_bModified(FALSE),
	m_transactionStack()
	{
	ASSERT_VALID(this);
	}

COXBrilliantObj::COXBrilliantObj(const COXBrilliantObj& brilliantObj)
	// --- In  : brilliantObj : the smart element object to be copied
	// --- Out : 
	// --- Returns : 
	// --- Effect : Copy constructor
	:
	m_bModified(brilliantObj.m_bModified)
	{
	ASSERT_VALID(&brilliantObj);
	ASSERT_VALID(this);
	}

COXBrilliantObj& COXBrilliantObj::operator=(const COXBrilliantObj& brilliantObj)
    // --- In  : brilliantObj : the smart element object to be copied
	// --- Out : 
	// --- Returns : 
	// --- Effect : Assignment operator
	{
	ASSERT_VALID(&brilliantObj);
	// Adjust the modified flag
	m_bModified = brilliantObj.m_bModified;
	ASSERT_VALID(this);
	return *this;
	}

void COXBrilliantObj::MakeTransactionCopy()
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Makes a transaction copy of this object and
	//				puts it in the place of the NULL at the top of the stack
	{
	ASSERT_VALID(this);
	ASSERT(!m_transactionStack.IsEmpty());		// Must be during transaction
	ASSERT(m_transactionStack.Peek() == NULL);	// Copy not yet made

	// Replace all the top stack entry by a copy
	m_transactionStack.Peek() = Clone();
	}

void COXBrilliantObj::ClearTransactionStack()
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Clears the transaction stack of this object
	{
	ASSERT_VALID(this);
	while (!m_transactionStack.IsEmpty())
		// Delete all the stack entries (some might be NULL)
		delete m_transactionStack.Pop();
	}

COXBrilliantObj::~COXBrilliantObj()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This destructs the object
	{
#ifdef _DEBUG
	if (!m_transactionStack.IsEmpty())
		{
		TRACE(TEXT("COXBrilliantObj::~COXBrilliantObj : Deleting object with %li outstanding transactions\n"),
			m_transactionStack.GetCount());
		}
#endif _DEBUG
	ClearTransactionStack();
	}

// private:

// ==========================================================================
