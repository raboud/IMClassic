/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "Flooring.h"
#include "CustomerPickList.h"

class CSetCustomer;

// CFindCustomers form view

class CFindCustomers : public CFormView
{
	DECLARE_DYNCREATE(CFindCustomers)

protected:
	CFindCustomers();           // protected constructor used by dynamic creation
	virtual ~CFindCustomers();

public:
	enum { IDD = IDD_FINDCUSTOMER };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	CCustomerPickList m_gridCustomer ;
	CSetCustomer* m_pSet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void UpdateCustomerFilter();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnreset();
	CEdit m_editLastName;
	CEdit m_editFirstName;
	virtual void OnInitialUpdate();
	afx_msg void OnEnChangeFirstName();
	afx_msg void OnEnChangeLastName();
};


