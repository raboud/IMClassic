/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DIALOGINVOICING_H__B8706B18_4752_4889_89F6_427888F87C94__INCLUDED_)
#define AFX_DIALOGINVOICING_H__B8706B18_4752_4889_89F6_427888F87C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogInvoicing.h : header file
//

#include "GridInvoicing.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogInvoicing dialog

class CDialogInvoicing : public CDialog
{
// Construction
public:
	LRESULT OnInvoiced(WPARAM wParam, LPARAM lParam);
	CDialogInvoicing(CWnd* pParent = NULL);   // standard constructor
	void SetVendorID(int iVendorID);

// Dialog Data
	//{{AFX_DATA(CDialogInvoicing)
	enum { IDD = IDD_INVOICING };
	CDateTimeCtrl	m_dateInvoice;
	CStatic	m_Invoiced;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogInvoicing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	double m_fInvoiced;
	int m_iInvoice;
	CGridInvoicing m_gridInvoice;

	// Generated message map functions
	//{{AFX_MSG(CDialogInvoicing)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimeChangeInvoicedate(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGINVOICING_H__B8706B18_4752_4889_89F6_427888F87C94__INCLUDED_)
