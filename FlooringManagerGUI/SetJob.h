/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETJOB_H__50E94BF3_36DD_4E0B_ABCA_BCAC17E2BF0F__INCLUDED_)
#define AFX_SETJOB_H__50E94BF3_36DD_4E0B_ABCA_BCAC17E2BF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetJob.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetJob recordset

class CSetJob : public CRecordset
{
public:
	CSetJob(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetJob)

// Field/Param Data
	//{{AFX_FIELD(CSetJob, CRecordset)
	long	m_OrderID;
	long	m_JobID;
	COleDateTime	m_DateScheduled;
	long	m_SubContractorID;
	COleDateTime	m_PaidDate;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetJob)
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

#endif // !defined(AFX_SETJOB_H__50E94BF3_36DD_4E0B_ABCA_BCAC17E2BF0F__INCLUDED_)
