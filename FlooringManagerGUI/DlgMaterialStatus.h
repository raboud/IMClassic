/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DLGMATERIALSTATUS_H__61D64248_0BBB_44BE_B0F3_61091B3BCA88__INCLUDED_)
#define AFX_DLGMATERIALSTATUS_H__61D64248_0BBB_44BE_B0F3_61091B3BCA88__INCLUDED_

#include "SetOrderSOMerchandiseDetails.h"
#include "SetOrders.h"
#include "SetCustomer.h"
#include "FloatEdit.h"
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMaterialStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMaterialStatus dialog

class CDlgMaterialStatus : public CDialog
{
// Construction
public:
	CDlgMaterialStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMaterialStatus)
	enum { IDD = IDD_MATERIAL_STATUS };
	CComboBox	m_comboStatus;
	CEdit	m_editSO;
	CButton	m_butOk;
	CButton	m_butCancel;
	CButton	m_butDone;
	CButton m_btnReset;
	CFloatEdit m_editYardage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMaterialStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool m_bError;
	CSetOrderSOMerchandiseDetails m_setSOMerchandiseDetails;
	CSetOrders m_setOrders;
	CSetCustomer m_setCustomer;
	void UpdateCBStatus();
	bool Validate (bool bDisplayMessage);
	void HandleValidation();
	void ShowControls(bool bShow);

	// Generated message map functions
	//{{AFX_MSG(CDlgMaterialStatus)
	afx_msg void OnDone();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeNumber();
	afx_msg void OnKillfocusNumber();
	afx_msg void OnSelchangeStatus();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	CString m_strCustomerName;
	CString m_strPO;
	void UpdateStrings(void);

public:
	afx_msg void OnBnClickedMaterialstatusReset();
	afx_msg void OnEnKillfocusYardage();
	CStatic m_stCustName;
	CStatic m_stPOStatic;
	CButton m_btnFind;
	afx_msg void OnBnClickedFindButton();
	CStatic m_stCustNameField;
	CStatic m_stPOField;
	CStatic m_stStatus;
	CStatic m_statMaterialDescription;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATERIALSTATUS_H__61D64248_0BBB_44BE_B0F3_61091B3BCA88__INCLUDED_)
