/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CustomerView.h : interface of the CCustomerView class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "FRecordView.h"
#include "CFIMaskedEdit.h"
#include "CustomerPickList.h"
#include "ComboBoxStore.h"	// Added by ClassView
#include "POPickList.h"	// Added by ClassView
#include "FlooringDoc.h"

class CSetCustomer;

class CCustomerView : public CFRecordView
{
protected: // create from serialization only
	CCustomerView();
	DECLARE_DYNCREATE(CCustomerView)

public:
	//{{AFX_DATA(CCustomerView)
	enum { IDD = IDD_FLOORING_FORM };
	CStatic	m_statWarrenty;
	CStatic	m_statScheduled;
	CStatic	m_statPaid;
	CStatic	m_InvAndPaid;
	CStatic	m_statInvoiced;
	CStatic	m_statCancelled;
	CComboBoxStore	m_comboStore;
	CEdit	m_editFirstName;
	CEdit	m_editLastName;
	CCFIMaskedEdit	m_editZip;
	CCFIMaskedEdit	m_editHomePhone;
	CCFIMaskedEdit	m_editWorkPhone;
	CCFIMaskedEdit  m_editMobilePhone;
	CEdit m_editEmailAddress;

	CCustomerPickList m_gridCustomer ;
	CPOPickList m_gridPoPickList;
	CSetCustomer* m_pSet;
	CSetOrders* m_pSetOrders;
	//}}AFX_DATA

// Attributes
public:
	CFlooringDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlooringDoc)));
		return (CFlooringDoc*)m_pDocument;
	} ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomerView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void CloseView();
	afx_msg LRESULT OnCustomerSelected (WPARAM, LPARAM);
	afx_msg LRESULT OnPOSelected(WPARAM wParam, LPARAM lParam) ;

	bool m_bEditing;
	virtual ~CCustomerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CBrush * m_pBrush;
	void CustomerFind();
	void EnableCustomerEdit();
	void BuildFilterString (bool bDoPartial = true);
	void ShowCustomerData (int nCmdShow);
	void EnableCustomerData (bool bState);

//	long m_lCustomerID;
	//{{AFX_MSG(CCustomerView)
	afx_msg void OnCustomerFind();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnCustomerNew();
	afx_msg void OnCustomerEdit();
	afx_msg void OnChangeFirstName();
	afx_msg void OnChangeLastName();
	afx_msg void OnFindByPo();
	afx_msg void OnFindByOrderNumber();
	afx_msg void OnFindByCustomerNumber();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnFindBySpecialOrder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFindByHomePhonenumber();
	afx_msg void OnFindByWorkPhonenumber();
	afx_msg void OnFindBysearchingnotes();

	void FindByCustomerNumber(CString strNumber);
	void FindByOrderNumber(long lOrderID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
