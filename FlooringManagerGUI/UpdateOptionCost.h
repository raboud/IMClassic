/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_UPDATEOPTIONCOST_H__1DC13D8C_4C06_493A_BF93_1B017109613E__INCLUDED_)
#define AFX_UPDATEOPTIONCOST_H__1DC13D8C_4C06_493A_BF93_1B017109613E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateOptionCost.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateOptionCost recordset

class CUpdateOptionCost : public CRecordset
{
public:
	CUpdateOptionCost(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUpdateOptionCost)

// Field/Param Data
	//{{AFX_FIELD(CUpdateOptionCost, CRecordset)
	BOOL	m_Scheduled;
	COleDateTime	m_ScheduleStartDate;
	CString	m_UnitCost;
	CString	m_NewUnitCost;
	long	m_OrderID;
	CString	m_PurchaseOrderNumber;
	CString	m_LastName;
	CString	m_FirstName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateOptionCost)
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

#endif // !defined(AFX_UPDATEOPTIONCOST_H__1DC13D8C_4C06_493A_BF93_1B017109613E__INCLUDED_)
