/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"


// CDlgWebService dialog

class CDlgWebService : public CDialog
{
	DECLARE_DYNAMIC(CDlgWebService)

public:
	CDlgWebService(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgWebService();

	bool m_bError;

// Dialog Data
	enum { IDD = IDD_WEBSERVICE_DIALOG };
	enum EnCOMMAND { EnCOMMAND_SPN_PRINT_PO, EnCOMMAND_SPN_UPDATE_PO, EnCOMMAND_SPN_SINGLE_PO, EnCOMMAND_SPN_ADD_NOTE_FOR_EXPEDITOR} ;
		//EnCOMMAND_SOSI_INSTALL_SCHEDULE_UPDATE, EnCOMMAND_SOSI_MEASURE_NOTE_FOR_EXPEDITOR, EnCOMMAND_SOSI_INSTALL_NOTE_FOR_EXPEDITOR, EnCOMMAND_SPN_ADD_NOTE_FOR_EXPEDITOR} ;

	afx_msg LRESULT OnError(WPARAM, LPARAM);
	afx_msg LRESULT OnContinue(WPARAM, LPARAM);

	INT_PTR SPNUpdatePO(CPoList* pListPOs);
	INT_PTR SPNUpdatePO(CString strStoreNumber, CString strPONumber);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	static UINT ExecuteThread(LPVOID pParam) ;

	CAnimateCtrl	m_AnimateCtrl;
	CPoList			m_listPOs;
	CString			m_strStoreNumber ;
	CString			m_strPONumber ;
	CString         m_strReasonCode;
	CString			m_strTitle;
	int             m_iNoteID;

	EnCOMMAND		m_enMode ;

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
	bool PrintPOs(void);
	bool DownloadPOs(void);
	bool DownloadPO(void) ;
	bool InstallScheduleUpdate();
	bool MeasureNoteForExpeditor();
	bool InstallNoteForExpeditor();
	bool SPNNoteForExpeditor();
	void AddString(CString strText);

protected:
	CButton m_butOk;
	bool m_bCopyToSASM;
	bool m_bCopyToExpeditorEmail;
	CEdit m_editStatus;
};
