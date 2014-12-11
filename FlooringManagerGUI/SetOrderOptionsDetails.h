/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETORDEROPTIONSDETAILS_H__9065304B_E3A9_416D_B87F_5E476B1874F9__INCLUDED_)
#define AFX_SETORDEROPTIONSDETAILS_H__9065304B_E3A9_416D_B87F_5E476B1874F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetOrderOptionsDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOrderOptionsDetails recordset

class CSetOrderOptionsDetails : public CRecordset
{
public:
	CSetOrderOptionsDetails(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderOptionsDetails)

// Field/Param Data
	//{{AFX_FIELD(CSetOrderOptionsDetails, CRecordset)
	long	m_OrdeOptionslID;
	long	m_OrderID;
	long	m_OptionID;
	double	m_Quantity;
	CString	m_UnitPrice;
	long	m_SubContractorID;
	CString	m_UnitCost;
	CString	m_UnitRetail;
	long	m_EntryMethodID;
	BOOL    m_PrintOnInvoice;
	BOOL    m_PrintOnWO;
	BOOL	m_Deleted ;
	BOOL    m_Reviewed ;
	long    m_ReviewedBy ;
	COleDateTime   m_ReviewedDate ;
	BOOL    m_SubContractorPaid;
	double  m_SubContractorPay;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOrderOptionsDetails)
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

#endif // !defined(AFX_SETORDEROPTIONSDETAILS_H__9065304B_E3A9_416D_B87F_5E476B1874F9__INCLUDED_)
