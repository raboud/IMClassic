/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewStoreInfo.h : Declaration of the CViewStoreInfo

#pragma once

// code generated on Friday, June 06, 2003, 6:33 PM

class CViewStoreInfo : public CRecordset
{
public:
	CViewStoreInfo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CViewStoreInfo)

// Field/Param Data

	long	m_StoreID;
	CString	m_StoreNumber;
	CString	m_StoreTypeName;
	CString	m_MarketName;
	CString	m_StorePhoneNumber;
	CString	m_DirectPhoneNumber;
	CString	m_FaxNumber;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


