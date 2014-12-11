/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_DIALOGDATEPICKER_H__337BA3EB_1B51_4567_BECB_2A729BDB1DFB__INCLUDED_)
#define AFX_DIALOGDATEPICKER_H__337BA3EB_1B51_4567_BECB_2A729BDB1DFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogDatePicker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogDatePicker dialog

class CDialogDatePicker : public CDialog
{
// Construction
public:
	COleDateTime GetDate();
	void SetCaption(CString strCaption);
	CDialogDatePicker(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogDatePicker)
	enum { IDD = IDD_DATE_PICKER };
	CMonthCalCtrl	m_calSelect;
	COleDateTime	m_dateSelected;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDatePicker)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strTitle;

	// Generated message map functions
	//{{AFX_MSG(CDialogDatePicker)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDATEPICKER_H__337BA3EB_1B51_4567_BECB_2A729BDB1DFB__INCLUDED_)
