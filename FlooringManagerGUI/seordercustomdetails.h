/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once
// SetOrderCustomDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeOrderCustomDetails recordset

class CSetOrderCustomDetails : public CRecordset
{
public:
	CSetOrderCustomDetails(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrderCustomDetails)

// Field/Param Data
	//{{AFX_FIELD(CSetOrderCustomDetails, CRecordset)
	long	m_OrderCustomID;
	long	m_OrderID;
	long	m_SubContractorID;
	CString	m_RetailPrice;
	CString	m_UnitCost;
	CString	m_UnitPrice;
	double	m_Quanity;
	CString	m_Description;
//	double	m_Multiplier;
//	double	m_CostMultiplier;
	long	m_UnitOfMeasureID;
	BOOL	m_NotOnInvoice;
	BOOL	m_NotOnWorkOrder;
	BOOL	m_Deleted ;
	long    m_EntryMethodID;
	BOOL    m_Reviewed ;
	long    m_ReviewedBy ;
	COleDateTime   m_ReviewedDate ;

	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOrderCustomDetails)
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
