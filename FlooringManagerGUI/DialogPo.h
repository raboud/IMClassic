/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

#include "ComboBoxMaterialType.h"
#include "POPropSheet.h"
#include "GridLabor.h"
#include "NotesPropSheet.h"

// DialogPo.h : header file
//
#include "FloatEdit.h"
#include "afxwin.h"
#include "flooring.h"
#include "DropTarget.h"

#include "SetDiscrepancies.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogPo dialog

class CDlgPo : public CDialog
{
// Construction
public:
//	bool SetOrderId(long lOrderId);
	bool SetCustomerId(long lCustomerId);
	void SetPONumber(CString strPONumber, CString strStoreNumber);
	void SetPOType(CString strPOType);
	void SetOrigPONumber(CString strOrigPONumber);
	void SetAddingFlag(bool bAddingNew);
	void SetInvokedFromSPNFlag(bool bInvokedFromSPN);
	CDlgPo(CWnd* pParent = NULL);   // standard constructor
	~CDlgPo();
	afx_msg LRESULT OnLineItemUpdate(WPARAM, LPARAM);

	CPOPropSheet m_POPropSheet;
	CNotesPropSheet m_NotesPropSheet;
	DropTarget m_dropTarget;
	
// Dialog Data
	//{{AFX_DATA(CDialogPo)
	enum { IDD = IDD_PO };
	CFloatEdit	m_editBillAmount;
	CEdit	m_editOrderNo;
	CStatic	m_statBilled;
	CStatic	m_statScheduled;
	CComboBox	m_comboDrawingTime;
	CEdit	m_editDrawing;
	CDateTimeCtrl	m_dateDrawing;
	CButton	m_butSevenDay;
	CListBox	m_listCheck;
	CButton	m_butCancel;
	CFloatEdit	m_editTripCharge;
	CButton	m_butNoMin;
	CEdit	m_editPrice;
	CEdit	m_editCustomerData;
	CComboBoxMaterialType	m_comboType;
	CDateTimeCtrl	m_dateScheduled;
	CDateTimeCtrl	m_dateOrder;
	CEdit	m_editNotes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// keeps track of whether current PO is being added (true) or edited (false)
	bool m_bAdding;
	bool m_bReadOnly;
	bool m_bInvokedFromSPN;
	long m_lMaterialType ;
	long m_lStoreTypeId;
	long m_lStoreId;
	long m_lCustomerId;
	long m_lMarketId;
	bool m_bShowInactive;
	bool m_bShowCFIPrice;
	bool m_bShowUnitCost ;
	bool m_bReviewed;
	bool m_bCancelled;
	bool m_bBilled;
	bool m_bUseSOSIDiagram;
	
	CString m_strPONumber;
	CString m_strOrigPONumber;
	CString m_strPOType;
	CString m_strMaterialTypeShortName;
	CString m_strEntryMethod;

	CString m_strStoreNumber;

	CGridLabor m_gridLabor;

	bool m_bDirty;
	bool m_bXmlBase ;

	void UpdatePrice();
	void UpdateCustomerData();
	void SetMaterialType (void);
	void EnableMaterialTypesCombo(bool bEnable);
	bool SaveData();
	void EnableAlertsButton();
	void MarkAlertsReviewed(int iOrderID);
	void SetReviewed(int iOrderID, bool bReviewed);
	void CloseCancelActivities( int iOrderID);
	void CloseChangeActivities( int iOrderID);

	// Generated message map functions
	//{{AFX_MSG(CDialogPo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusType();
	afx_msg void OnChangeTripCharge();
	afx_msg void OnNoMin();
	afx_msg void OnKillfocusDrawingNumber();
	afx_msg void OnDrawingUpdate();
	afx_msg void OnEditPoNum();
	afx_msg void OnEditClearreadonly();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool m_bConsolidatedView;
	bool m_bShowDelete;
	CPoList m_listPOs;

	CString m_strOrderIDFilter;
	CString m_strPOList;

	CSetDiscrepancies m_setDiscrepancies;
	
public:
	afx_msg void OnNMKillfocusOrderDate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeType();
	afx_msg void OnBnClickedPOEdit();
	void SetStoreNumber(CString strStoreNumber);
	afx_msg void OnEditEditponumber();
	void SetMaterialTypeShortName(CString strShortName);
	afx_msg LRESULT OnFilesDropped(WPARAM wParam, LPARAM lParam);

	void SetPOList(CPoList* pListPOs);
	void SetOrderId(int iOrderID);

protected:
	void UpdateTitleBar(void);
	BOOL CreateEmbeddedPropertySheet( CWnd* pParent, 
									  CPropertySheet* pPSheet, 
									  DWORD dwStyle = WS_CHILD | WS_VISIBLE,
									  DWORD dwExStyle = 0 );
	
	void PositionEmbeddedPropertySheet( CWnd* pParent,
										CPropertySheet* pPSheet,
										CRect rcNewPosition );
	void PositionEmbeddedPropertySheet( CWnd* pParent, 
										CPropertySheet* pPSheet, 
										UINT nIDPSheetArea );
	void InitNormal();
	void InitForConsolidatedView();
	void InitMenu();

	int GetFirstOrderID();

	CString GetDiagramName(bool bFullPath);

public:
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

	afx_msg void OnViewShowcfiprice();
	afx_msg void OnViewShowUnitCost();
	afx_msg void OnViewShowinactivematerials();
	afx_msg void OnViewShowDeleted() ;

	afx_msg void OnUpdateViewShowInactiveMaterials(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewShowcfiprice(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewShowUnitCost(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewShowDeleted(CCmdUI *pCmdUI) ;

	CEdit m_editSummary;
	afx_msg void OnBnClickedViewWorkorder();
	afx_msg void OnBnClickedRefreshPrices();
	CEdit m_editXMLPrice;
	CStatic m_stXMLPOAmount;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawingView();
	CButton m_butDrawingView;
	afx_msg void OnCbnSelchangeDrawingTime();
	afx_msg void OnBnClickedAlerts();
	CButton m_btnAlerts;
	CStatic m_stReviewedStatus;
	afx_msg void OnBnClickedNotes();
	CStatic m_stDiagramName;
protected:
	virtual void OnCancel();
public:
	afx_msg void OnEnChangeDrawingNumber();
};

inline void CDlgPo::SetPONumber(CString strPONumber, CString strStoreNumber)
{
	m_strPONumber = strPONumber;
	m_strStoreNumber = strStoreNumber ;
	SetStoreNumber(strStoreNumber);
}

inline void CDlgPo::SetPOType(CString strPOType)
{
	m_strPOType = strPOType;
}

inline void CDlgPo::SetOrigPONumber(CString strOrigPONumber)
{
	m_strOrigPONumber = strOrigPONumber;
}

inline void CDlgPo::SetInvokedFromSPNFlag(bool bInvokedFromSPN)
{
	m_bInvokedFromSPN = bInvokedFromSPN;
}

inline int CDlgPo::GetFirstOrderID()
{
	if (m_listPOs.GetCount() > 0)
	{
        POSITION pos = m_listPOs.GetHeadPosition();
		return m_listPOs.GetNext(pos);
	}

	return -1;
}