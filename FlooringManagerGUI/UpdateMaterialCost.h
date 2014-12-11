/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_UPDATEMATERIALCOST_H__B1336502_6F09_4774_BA38_2084DCECD09C__INCLUDED_)
#define AFX_UPDATEMATERIALCOST_H__B1336502_6F09_4774_BA38_2084DCECD09C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateMaterialCost.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateMaterialCost recordset

class CUpdateMaterialCost : public CRecordset
{
public:
	CUpdateMaterialCost(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUpdateMaterialCost)

// Field/Param Data
	//{{AFX_FIELD(CUpdateMaterialCost, CRecordset)
	BOOL	m_Scheduled;
	COleDateTime	m_ScheduleStartDate;
	CString	m_UnitCost;
	CString	m_NewUnitCost;
	long	m_OrderID;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_PurchaseOrderNumber;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateMaterialCost)
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

#endif // !defined(AFX_UPDATEMATERIALCOST_H__B1336502_6F09_4774_BA38_2084DCECD09C__INCLUDED_)
