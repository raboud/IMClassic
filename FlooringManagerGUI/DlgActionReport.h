/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DLGACTIONREPORT_H__EC45A9B7_6E4F_4C68_B87D_5E32077D98CE__INCLUDED_)
#define AFX_DLGACTIONREPORT_H__EC45A9B7_6E4F_4C68_B87D_5E32077D98CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgActionReport.h : header file
//
#include "ListBoxStoreError.h"
#include "ListBoxMillError.h"
#include "ListBoxMeasureError.h"
#include "ListBoxInstallerError.h"
#include "CFRichEdit.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "CustomerSatPropertyPage.h"
#include <sscemfc.hpp>
#include "FontPreviewCombo.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgActionReport dialog

class CDlgActionReport : public CDialog
{
// Construction
public:
	CDlgActionReport(CWnd* pParent = NULL);   // standard constructor
	~CDlgActionReport();
	void SetId (int iID);
	void SetOrderId (int iOrderID);
	void SetCustomerId(int iCustomerID) ;

// Dialog Data
	//{{AFX_DATA(CDlgActionReport)
	enum { IDD = IDD_ACTION_REPORT };
	CStatic	m_staticInfo;
	CDateTimeCtrl	m_dateEntered;
	CListBoxStoreError	m_listStoreError;
	CListBoxMillError	m_listMillError;
	CListBoxMeasureError	m_listMeasureError;
	CListBoxInstallerError	m_listInstallerError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgActionReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool m_bDirty;

	// Generated message map functions
	//{{AFX_MSG(CDlgActionReport)
	afx_msg void OnChange();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_iId;
	int m_iOrderId;
	int m_iCustomerId;
	CWnd* m_wndeditFocus;

	//CCustomerSatPropertySheet* m_psheetCustomerSat;
	CPropertySheet m_sheetCustomerSat;
	CCustomerSatPropertyPage* m_ppageAction;
	CCustomerSatPropertyPage* m_ppageCause;
	CCustomerSatPropertyPage* m_ppageNature;

	CString m_strCurrentActionText;
	CString m_strCurrentCauseText;
	CString m_strCurrentNatureText;

	void UpdateCurrentRecord();

	LRESULT OnRichEditChange(WPARAM wParam, LPARAM lParam);
	LRESULT OnRichEditLoseFocus(WPARAM wParam, LPARAM lParam);

	SSCE_S16 CheckSpelling(CCustomerSatPropertyPage* pPage);

public:
	CButton m_btnBold;
	CButton m_btnItalic;
	CButton m_btnUnderline;
	CBitmap m_bmpBold;
	CBitmap m_bmpItalic;
	CBitmap m_bmpUnderline;

	afx_msg void OnBnClickedActionReportBoldButton();
	afx_msg void OnBnClickedActionReportItalicButton();
	afx_msg void OnBnClickedActionReportUnderlineButton();
	afx_msg void OnBnClickedActionReportViewprintreportButton();
	CStatic m_stTodaysDate;
	afx_msg void OnBnClickedActionReportCheckspelling();
	CFontPreviewCombo m_cbFontNames;
	CComboBox m_cbFontSizes;
	afx_msg void OnCbnSelchangeActionreportFontsizeCombo();
	afx_msg void OnCbnSelchangeActionreportFontcombo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACTIONREPORT_H__EC45A9B7_6E4F_4C68_B87D_5E32077D98CE__INCLUDED_)
