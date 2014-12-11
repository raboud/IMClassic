#pragma once

#include "setorders.h"
// CDlgDeletePOConfirm dialog

class CDlgDeletePOConfirm : public CDialog
{
	DECLARE_DYNAMIC(CDlgDeletePOConfirm)

public:
	CDlgDeletePOConfirm(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDeletePOConfirm();

// Dialog Data
	enum { IDD = IDD_DELETE_PO_DIALOG };

	CString m_editYesBox;

	void SetPOList(CPoList* pListPOs);
	CString m_strMessageText;

	virtual BOOL OnInitDialog();
	bool CanDeletePO();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool DeletePO();

	DECLARE_MESSAGE_MAP()

	CPoList m_PoList;

	CSetOrders m_setOrders;

	virtual void OnOK();

	CString m_strOrderIDFilter;
};

inline void CDlgDeletePOConfirm::SetPOList(CPoList* pListPOs)
{
	m_PoList.AddHead(pListPOs);
}
