/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_VIEWSUBCONTRATOR_H__AB338E5F_C78F_410E_8B04_3D51353B639B__INCLUDED_)
#define AFX_VIEWSUBCONTRATOR_H__AB338E5F_C78F_410E_8B04_3D51353B639B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewSubcontrator.h : header file
//
#include "FRecordView.h"
#include "SetSubContractor.h"	// Added by ClassView
#include "OXMaskedEdit.h"
#include "afxwin.h"
#include "afxdtctl.h"

/////////////////////////////////////////////////////////////////////////////
// CViewSubcontrator record view

class CViewSubcontrator : public CFRecordView
{
protected:
	CViewSubcontrator();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewSubcontrator)

public:
	//{{AFX_DATA(CViewSubcontrator)
	enum { IDD = IDD_SUBCONTRACTOR };
	CEdit	m_editRetainage;
	CEdit	m_editWorkmanCompRate;
	COXMaskedEdit	m_editZip;
	COXMaskedEdit	m_editSSN;
	COXMaskedEdit	m_editPager;
	COXMaskedEdit	m_editHomePhone;
	COXMaskedEdit	m_editCellNumber;
	CSetSubContractor* m_pSet;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewSubcontrator)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual void OnInitialUpdate();
	virtual BOOL OnMove(UINT nIDMoveCommand);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewSubcontrator();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewSubcontrator)
	virtual void OnOK();
	afx_msg void OnRecordNew();
	afx_msg void OnCriminalCheck();
	afx_msg void OnInsurance();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSubcontractorsAdd();
	afx_msg void OnBnClickedSubcontractorsEdit();
	afx_msg void OnBnClickedSubcontractorsDelete();
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDelete;
protected:
	void EnableControls(bool bEnable);
	CSetSubContractor* GetRecordset();

	void UpdatePickList(void);

	int m_iNextSubContractorID;
public:
	CEdit m_editFirstName;
	CEdit m_editLastName;
	CEdit m_editNickName;
	CButton m_btnActive;
	CButton m_btnHelper;
	CEdit m_editAddress;
	CEdit m_editCity;
	CEdit m_editState;
	CButton m_btnInsOK;
	CDateTimeCtrl m_dtpInsurance;
	CButton m_btnCrimCheckOK;
	CDateTimeCtrl m_dtpCrimCheck;
	CEdit m_editNotes;

protected:
public:
	CButton m_btnOK;
	CButton m_btnCancel;
	CComboBox m_comboInstallerQuickPick;
	afx_msg void OnCbnSelchangeInstallerQuickpickCombo();
	CStatic m_stRetainageText2;
	CStatic m_stRetainageText1;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSUBCONTRATOR_H__AB338E5F_C78F_410E_8B04_3D51353B639B__INCLUDED_)
