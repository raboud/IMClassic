/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
// SetStores.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetStores recordset

class CSetStores : public CRecordset
{
public:
	CSetStores(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetStores)

// Field/Param Data
	//{{AFX_FIELD(CSetStores, CRecordset)
	long	m_StoreID;
	long	m_StoreTypeID;
	CString	m_StoreNumber;
	CString	m_BillingAddress;
	CString	m_City;
	CString	m_State;
	CString	m_ZipCode;
	CString	m_StorePhoneNumber;
	CString	m_DirectPhoneNumber;
	CString	m_Extension;
	CString	m_FaxNumber;
	CString	m_Notes;
	long	m_MarketId ;
	CString	m_StoreNickName;
	BOOL	m_Active;
	BOOL    m_IncludeInStatusReportAll;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetStores)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
