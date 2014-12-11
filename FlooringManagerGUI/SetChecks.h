/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETCHECKS_H__7EC3D8E5_58FF_436A_8948_983607808674__INCLUDED_)
#define AFX_SETCHECKS_H__7EC3D8E5_58FF_436A_8948_983607808674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetChecks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetChecks recordset

class CSetChecks : public CRecordset
{
public:
	CSetChecks(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetChecks)

// Field/Param Data
	//{{AFX_FIELD(CSetChecks, CRecordset)
	long	m_CheckID;
	CString	m_CheckNumber;
	COleDateTime m_CheckDate;
	CString	m_Amount;
	CString m_QBTxnId;
	long m_VendorID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetChecks)
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

#endif // !defined(AFX_SETCHECKS_H__7EC3D8E5_58FF_436A_8948_983607808674__INCLUDED_)
