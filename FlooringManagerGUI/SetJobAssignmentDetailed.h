/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETJOBASSIGNMENTDETAILED_H__C5B0A131_AD90_4ECB_BB16_5F3BEF33BF27__INCLUDED_)
#define AFX_SETJOBASSIGNMENTDETAILED_H__C5B0A131_AD90_4ECB_BB16_5F3BEF33BF27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetJobAssignmentDetailed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetJobAssignmentDetailed recordset

class CSetJobAssignmentDetailed : public CRecordset
{
public:
	CSetJobAssignmentDetailed(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetJobAssignmentDetailed)

// Field/Param Data
	//{{AFX_FIELD(CSetJobAssignmentDetailed, CRecordset)
	long	m_Id;
	long	m_SubContractorId;
	COleDateTime	m_Date;
	CString	m_PurchaseOrderNumber;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_Address;
	CString	m_City;
	CString	m_State;
	CString	m_ZipCode;
	CString	m_PhoneNumber;
	CString	m_WorkNumber;
	long	m_MaterialTypeID;
	CString	m_ShortName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetJobAssignmentDetailed)
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

#endif // !defined(AFX_SETJOBASSIGNMENTDETAILED_H__C5B0A131_AD90_4ECB_BB16_5F3BEF33BF27__INCLUDED_)
