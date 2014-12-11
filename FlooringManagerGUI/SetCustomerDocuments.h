/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// SetCustomerDocuments.h : Declaration of the CSetCustomerDocuments

#pragma once

// code generated on Monday, February 23, 2009, 11:17 PM

class CSetCustomerDocuments : public CRecordset
{
public:
	CSetCustomerDocuments(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCustomerDocuments)

// Field/Param Data
	long	m_ID;
	long	m_CustomerID;
	CString	m_Path;
	CString	m_Filename;
	CString	m_Notes;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


