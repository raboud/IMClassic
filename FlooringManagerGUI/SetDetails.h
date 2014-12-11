/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETDETAILS_H__1C91FD5C_5489_414D_A20B_BE5EE6B8A087__INCLUDED_)
#define AFX_SETDETAILS_H__1C91FD5C_5489_414D_A20B_BE5EE6B8A087__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetJobDetails recordset

class CSetJobDetails : public CRecordset
{
public:
	CSetJobDetails(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetJobDetails)

// Field/Param Data
	//{{AFX_FIELD(CSetJobDetails, CRecordset)
	long	m_JobDetailID;
	long	m_JobID;
	long	m_DetailID;
	long	m_DetailType;
	CString	m_AmountPaid;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetJobDetails)
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

#endif // !defined(AFX_SETDETAILS_H__1C91FD5C_5489_414D_A20B_BE5EE6B8A087__INCLUDED_)
