/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETTOTALPAYMENT_H__4BE84AF1_5579_4C95_8A7D_083EC9A2D8E6__INCLUDED_)
#define AFX_SETTOTALPAYMENT_H__4BE84AF1_5579_4C95_8A7D_083EC9A2D8E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetTotalPayment.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetTotalPayment recordset

class CSetTotalPayment : public CRecordset
{
public:
	CSetTotalPayment(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetTotalPayment)

// Field/Param Data
	//{{AFX_FIELD(CSetTotalPayment, CRecordset)
	CString	m_TotalAmount;
	long	m_OrderID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetTotalPayment)
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

#endif // !defined(AFX_SETTOTALPAYMENT_H__4BE84AF1_5579_4C95_8A7D_083EC9A2D8E6__INCLUDED_)
