/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETPADFIX_H__0280B3B3_7E93_447C_955E_857291E2D306__INCLUDED_)
#define AFX_SETPADFIX_H__0280B3B3_7E93_447C_955E_857291E2D306__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPadFix.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetPadFix recordset

class CSetPadFix : public CRecordset
{
public:
	CSetPadFix(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetPadFix)

// Field/Param Data
	//{{AFX_FIELD(CSetPadFix, CRecordset)
	long	m_OrderID;
	CString	m_PurchaseOrderNumber;
	BOOL	m_Billed;
	BOOL	m_Paid;
	CString	m_BilledAmount;
	CString	m_OrderAmount;
	long	m_MaterialID;
	CString	m_UnitPrice;
	double	m_Size;
	CString	m_Price;
	CString	m_CurrentPrice;
	CString	m_CurrentExt;
	CString	m_Amount;
	CString	m_ActualUnit;
	CString	m_Balance;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPadFix)
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

#endif // !defined(AFX_SETPADFIX_H__0280B3B3_7E93_447C_955E_857291E2D306__INCLUDED_)
