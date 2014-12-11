/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "flooring.h"

// CDlgSendNote dialog

class CDlgSendNote : public CDialog
{
	DECLARE_DYNAMIC(CDlgSendNote)

private:
	CFont m_Font;
	CFont m_Font2;
	bool m_bShowCopyToSASM;
	bool m_bShowCopyToExpeditorEmail;

public:
	CDlgSendNote(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSendNote();

// Dialog Data
	enum { IDD = IDD_SENDNOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ShowCopyToSASM(bool bShow);
	void ShowCopyToExpeditorEmail(bool bShow);
	afx_msg void OnBnClickedCancel();
	
	BOOL m_CopyNoteToSASM;
	BOOL m_CopyNoteToExpeditorEmail;
};
