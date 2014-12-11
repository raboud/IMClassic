/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETBILLS_H__BA7C6904_B8AF_4EB7_83CF_E1A79D6EE723__INCLUDED_)
#define AFX_SETBILLS_H__BA7C6904_B8AF_4EB7_83CF_E1A79D6EE723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// setbills.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetBills recordset

class CSetBills : public CRecordset
{
public:
	CSetBills(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetBills)

// Field/Param Data
	//{{AFX_FIELD(CSetBills, CRecordset)
	CString	m_Account;
	COleDateTime	m_Date;
	long	m_ID;
	CString	m_Memo;
	CString	m_Name;
	CString	m_Num;
	CString	m_Original_Amount;
	CString	m_Paid_Amount;
	CString	m_Split;
	CString	m_Type;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetBills)
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

#endif // !defined(AFX_SETBILLS_H__BA7C6904_B8AF_4EB7_83CF_E1A79D6EE723__INCLUDED_)
