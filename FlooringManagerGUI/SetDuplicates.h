/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETDUPLICATES_H__F952F14F_1CB8_4754_8F02_345AFCF18B9D__INCLUDED_)
#define AFX_SETDUPLICATES_H__F952F14F_1CB8_4754_8F02_345AFCF18B9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDuplicates.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDuplicates recordset

class CSetDuplicates : public CRecordset
{
public:
	CSetDuplicates(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetDuplicates)

// Field/Param Data
	//{{AFX_FIELD(CSetDuplicates, CRecordset)
	long	m_ID1;
	CString	m_Last1;
	CString	m_First1;
	CString	m_PO1;
	long	m_OrderID1;
	CString	m_SO1;
	long	m_MatStatusID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDuplicates)
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

#endif // !defined(AFX_SETDUPLICATES_H__F952F14F_1CB8_4754_8F02_345AFCF18B9D__INCLUDED_)
