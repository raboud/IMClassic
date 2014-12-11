#pragma once
#include "afxwin.h"
#include "CFIMaskedEdit.h"

// CDlgStoreCustDiscrepancy dialog

class CDlgStoreCustDiscrepancy : public CDialog
{
	DECLARE_DYNAMIC(CDlgStoreCustDiscrepancy)

public:
	CDlgStoreCustDiscrepancy(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStoreCustDiscrepancy();

// Dialog Data
	enum { IDD = IDD_STORECUSTDISCREPANCY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	int m_DiscType;
	int m_DiscSubType;
	long m_DetailID;
	CString m_CurrentData;
	CString m_NewData;
	CString m_ExtraData;
	bool m_bHandled;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeStorecurrentaddress();
	CEdit m_editCurrentAddress;
	CCFIMaskedEdit m_editCurrent;
	CEdit m_editNewAddress;
	CCFIMaskedEdit m_editNew;
	CStatic m_staticCurrent;
	CStatic m_staticNew;
	virtual BOOL OnInitDialog();

	void SetSubType(int DiscSubType);
	void SetDetailID(long DetailID);
	void SetCurrentData(CString CurrentData);
	void SetNewData(CString NewData);
	void SetDiscType(int DiscType);
	void SetExtraData(CString strExtraData);
	bool WasHandled();

protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedRejectchanges();
	CStatic m_staticExtraInfo;
};

inline bool CDlgStoreCustDiscrepancy::WasHandled()
{
	return m_bHandled;
}

inline void CDlgStoreCustDiscrepancy::SetExtraData(CString strExtraData)
{
	m_ExtraData = strExtraData;
}