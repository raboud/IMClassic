/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_REPORTPAYROLL_H__14106C3E_1DEE_4757_95B6_A2DC652DFEC2__INCLUDED_)
#define AFX_REPORTPAYROLL_H__14106C3E_1DEE_4757_95B6_A2DC652DFEC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportPayroll.h : header file
//

#include "CFScrollView.h"
#include "setpayroll.h"	// Added by ClassView
#include "registrysection.h"

/*
const char szREGISTRY_KEY_QBSTRINGS[] = "Quickbooks Settings";
const char szREGISTRY_VALUE_QBFILENAME[] = "QuickbooksFilename";
const char szREGISTRY_VALUE_ACCOUNTSPAYABLEACCOUNT[] = "AccountsPayableAccount";
const char szREGISTRY_VALUE_LABORSUBCONTRACTACCOUNT[] = "LaborSubcontractAccount";
const char szREGISTRY_VALUE_RETAINAGEACCOUNT[] = "RetainageAccount";
const char szREGISTRY_VALUE_SAVINGSACCOUNT[] = "SavingsAccount";
const char szREGISTRY_VALUE_SOFTSURFACECLASS[] = "SoftSurfaceClass";
const char szREGISTRY_VALUE_HARDSURFACECLASS[] = "HardSurfaceClass";
const char szREGISTRY_VALUE_COMMERCIALCLASS[] = "CommercialClass";
const char szREGISTRY_VALUE_RETAINAGECLASS[] = "RetainageClass";
const char szREGISTRY_VALUE_SAVINGSCLASS[] = "SavingsClass";
const char szREGISTRY_VALUE_OVERHEADCLASS[] = "OverheadClass";

const char szREGISTRY_VALUE_QBFILENAME_DEFAULT[] = "Sub-Contractors.iif";
const char szREGISTRY_VALUE_ACCOUNTSPAYABLEACCOUNT_DEFAULT[] = "Accounts Payable";
const char szREGISTRY_VALUE_LABORSUBCONTRACTACCOUNT_DEFAULT[] = "Labor Subcontract";
const char szREGISTRY_VALUE_RETAINAGEACCOUNT_DEFAULT[] = "Retainage";
const char szREGISTRY_VALUE_SAVINGSACCOUNT_DEFAULT[] = "Savings";
const char szREGISTRY_VALUE_SOFTSURFACECLASS_DEFAULT[] = "Home Depot:Soft Surface";
const char szREGISTRY_VALUE_HARDSURFACECLASS_DEFAULT[] = "Home Depot:Hard Surface";
const char szREGISTRY_VALUE_COMMERCIALCLASS_DEFAULT[] = "Commercial";
const char szREGISTRY_VALUE_RETAINAGECLASS_DEFAULT[] = "Retainage";
const char szREGISTRY_VALUE_SAVINGSCLASS_DEFAULT[] = "Savings";
const char szREGISTRY_VALUE_OVERHEADCLASS_DEFAULT[] = "Overhead";
*/

/////////////////////////////////////////////////////////////////////////////
// CReportPayroll view

class CReportPayroll : public CCFScrollView
{
protected:
	CReportPayroll();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportPayroll)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportPayroll)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	double m_fGrandTotal;
	CString GetWeekEnding ();
	void BuildQuickbooksFile();
	long m_lDateColumWidth;
	long m_lNameColumWidth;
	long m_lAmountColumWidth;
	long m_lCommentColumWidth;
	long m_lLeftMargin;
	long m_lRightMargin;
	CSetPayroll m_set;
	void GotoPage(int iPage);
	virtual void PrintPageBody (CDC* pDC, CPrintInfo* pInfo);
	virtual ~CReportPayroll();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CString OutputRetainage(CString strInstaller, double fRetainage, double dSusbjectToRetainage, double& dPayAmount) ;
	CString OutputSavings(CString strInstaller, bool bInstallerOk, double fSavings, double dSusbjectToRetainage, double& dPayAmount) ;
	CString OutputHeader(CString strInstaller, double dPayAmount) ;
	CString ClassTrans(CString strClass) ;

	// Generated message map functions
	//{{AFX_MSG(CReportPayroll)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// retrieves the value of the specified key, or a default value
	CString GetQBString(CString strKey, CString strDefault);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTPAYROLL_H__14106C3E_1DEE_4757_95B6_A2DC652DFEC2__INCLUDED_)

