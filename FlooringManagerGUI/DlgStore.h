#pragma once
#include "SetStores.h"
#include "ComboBoxStoreType.h"
#include "ComboBoxStoreMarket.h"
#include "CFIMaskedEdit.h"
#include "Dib.h"
#include "GridStoreContacts.h"

// CDlgStore dialog

class CDlgStore : public CDialog
{
	DECLARE_DYNAMIC(CDlgStore)

public:
	CDlgStore(bool bAdding, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStore();
	void SetStoreID(int iStoreID);

	bool CancelButtonHasFocus();

// Dialog Data
	enum { IDD = IDD_STORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int m_iStoreID;
	bool m_bAdding;  // if true we are adding, else editing

	CStatic	m_bmpDepot;
	CDib m_bmp ;
	CComboBoxStoreType	m_comboStoreType;
	CComboBoxStoreMarket m_cbStoreMarket;

	CEdit			m_editStoreNumber;
	CEdit			m_editStoreAddress;
	CEdit			m_editStoreCity;
	CEdit			m_editStoreState;
	CEdit			m_editStoreNickName;
	CCFIMaskedEdit	m_editZip;
	CCFIMaskedEdit	m_editStorePhoneNumber;
	CCFIMaskedEdit	m_editFaxNumber;
//	CCFIMaskedEdit	m_editAltFaxNumber;
	CEdit			m_editStoreNotes;
//	CButton			m_btnReceiveFaxStatus;
	CButton			m_btnActive;
	CButton			m_btnOK;
	CButton			m_btnCancel;
	BOOL			m_bIncludeInStatusReportAllStores;

	CGridStoreContacts m_gridStoreContacts;

	CSetStores* m_pSet;
	CSetMarket* m_pSetMarket;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();

	void ShowInstSalesMgrFields(bool bShow);
	bool ValidateData(CString& strError);
};
