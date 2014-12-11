/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_OPTIONS_H__69F68C01_3FCA_4775_9412_BB393C65A31E__INCLUDED_)
#define AFX_OPTIONS_H__69F68C01_3FCA_4775_9412_BB393C65A31E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOptions recordset

class CSetOptions : public CRecordset
{
public:
	CSetOptions(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOptions)

// Field/Param Data
	//{{AFX_FIELD(CSetOptions, CRecordset)
	long	m_OptionID;
	CString	m_OptionDescription;
	CString	m_UnitPrice;
	CString	m_UnitCost;
	long	m_UnitOfMeasureID;
	long	m_MaterialTypeID;
	BOOL	m_ApplyToMinimum;
	BOOL	m_ApplyToMinimumWO;
	BOOL	m_PrintOnInvoice;
	BOOL	m_PrintOnWorkOrder;
	BOOL	m_Active;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOptions)
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

#endif // !defined(AFX_OPTIONS_H__69F68C01_3FCA_4775_9412_BB393C65A31E__INCLUDED_)
