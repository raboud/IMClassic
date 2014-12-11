#pragma once
#include "afxwin.h"


// CDlgChangePONumber dialog

class CDlgChangePONumber : public CDialog
{
	DECLARE_DYNAMIC(CDlgChangePONumber)

public:
	CDlgChangePONumber(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgChangePONumber();

	CString GetErrorMessage();

	void SetOrderID(int iOrderID);
	void SetCurrentPONumber(CString strPONumber);

	
// Dialog Data
	enum { IDD = IDD_CHANGEPO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	int m_iOrderID;

	CString m_strOldPONumber;
	CString m_strOldStoreNumber;

	CString m_strNewPONumber;

	CString m_strErrorMessage;
	bool m_bChangingMarkets;

	virtual void OnOK();
	bool ValidateAndChangePO();
	

	CString m_strMessage;
	CEdit m_editCorrectPO;
	virtual BOOL OnInitDialog();

	bool IsWarrantyOrInvoice();

};

inline CString CDlgChangePONumber::GetErrorMessage()
{
	return m_strMessage;
}
