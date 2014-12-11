/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETUNPAID_H__328A7F0E_369F_4783_91E9_CE45483CC52B__INCLUDED_)
#define AFX_SETUNPAID_H__328A7F0E_369F_4783_91E9_CE45483CC52B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUnpaid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUnpaid recordset

class CSetUnpaid : public CRecordset
{
public:
	CSetUnpaid(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetUnpaid)

// Field/Param Data
	//{{AFX_FIELD(CSetUnpaid, CRecordset)
	double	m_fBilledAmount;
	double	m_fPaidAmount;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUnpaid)
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

#endif // !defined(AFX_SETUNPAID_H__328A7F0E_369F_4783_91E9_CE45483CC52B__INCLUDED_)
