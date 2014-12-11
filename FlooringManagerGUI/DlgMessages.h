#pragma once
#include "afxcoll.h"
#include "afxwin.h"

#include "multilinelistbox.h"

// CDlgMessages dialog

class CDlgMessages : public CDialog
{
	DECLARE_DYNAMIC(CDlgMessages)

public:
	CDlgMessages(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMessages();

// Dialog Data
	enum { IDD = IDD_MESSAGES_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMessagesPrint();

protected:
	CStringArray m_astrMessages;
	//CListBox m_lbMessages;
	CMultiLineListBox m_lbMessages;
	CStatic m_stListTitle;
	CString m_strDialogTitle;
	CString m_strListTitle;
	CString m_strOKButtonText;
	CString m_strCancelButtonText;
	void UpdateButtonText(int iButtonID, CString strText);

public:
	void SetMessages(CStringArray* pstrMessages);
	void SetDialogTitle(CString strTitle);
	void SetListTitle(CString strTitle);
	void SetButtonText(int iButtonID, CString strText);
	
	CButton m_btnPrint;
};
