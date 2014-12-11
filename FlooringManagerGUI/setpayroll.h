/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETPAYROLL_H__506C6CE2_1B6A_468C_B0AB_16FA2EA5A070__INCLUDED_)
#define AFX_SETPAYROLL_H__506C6CE2_1B6A_468C_B0AB_16FA2EA5A070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// setpayroll.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetPayroll recordset

class CSetPayroll : public CRecordset
{
public:
	CSetPayroll(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetPayroll)

// Field/Param Data
	//{{AFX_FIELD(CSetPayroll, CRecordset)
	CString	m_Installer;
	COleDateTime	m_Date;
	CString	m_Name;
	CString m_PONumber;
	CString	m_Pay_Amount;
	CString	m_Comments;
	CString	m_Chargeback;
	CString m_Class ;
	double	m_NO_RETAINAGE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPayroll)
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

#endif // !defined(AFX_SETPAYROLL_H__506C6CE2_1B6A_468C_B0AB_16FA2EA5A070__INCLUDED_)

