/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETCUSTOMER_H__983D0463_BA0A_455D_92BE_8AD72C85EFB1__INCLUDED_)
#define AFX_SETCUSTOMER_H__983D0463_BA0A_455D_92BE_8AD72C85EFB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCustomer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetCustomer recordset

class CSetCustomer : public CRecordset
{
public:
	CSetCustomer(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetCustomer)

// Field/Param Data
	//{{AFX_FIELD(CSetCustomer, CRecordset)
	long	m_CustomerID;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_Address;
	CString	m_City;
	CString	m_State;
	CString	m_ZipCode;
	CString	m_PhoneNumber;
	CString	m_WorkNumber;
	CString m_MobileNumber;
	CString m_EmailAddress;
//	CString	m_Extension;
	CString	m_Directions;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetCustomer)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
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

#endif // !defined(AFX_SETCUSTOMER_H__983D0463_BA0A_455D_92BE_8AD72C85EFB1__INCLUDED_)
