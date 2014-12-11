#pragma once
#include "afxwin.h"


// CDlgPOEntry dialog

class CDlgPOEntry : public CDialog
{
	DECLARE_DYNAMIC(CDlgPOEntry)

public:
	CDlgPOEntry(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPOEntry();

// Dialog Data
	enum { IDD = IDD_POENTRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	bool DataValidated(void);
	bool ValidateDataForAdd(void);
	bool ValidateDataForEdit(void);

	long m_lOrderID;
	bool m_bAdding;
	long m_lCustomerID;
	CString m_strPONumber;
	CString m_strPOType;
	CString m_strOrigPONumber;
	CString m_strStoreNumber;

	CString m_strPONumberInit;
	CString m_strPOTypeInit;
	CString m_strOrigPONumberInit;

	bool m_bPriceUpdateNeeded;

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editPONumber;
	CComboBox m_comboPOType;
	CComboBox m_comboOrigPO;

	virtual BOOL OnInitDialog();
	bool SetOrderID(long lOrderID);
	bool SetCustomerID(long lCustomerID);
	void FillOrigPOCombo(void);
	CString GetPOType();
	CString GetPONumber();
	CString GetOrigPONumber();
	
	afx_msg void OnCbnSelChangePOTypeCombo();

protected:
	bool StoreTypeDifference(CString strNewStoreNumber);
	bool MarketDifference(CString strNewStoreNumber);
	void InitVars(void);
public:
	CString GetStoreNumber(void);
	void SetPONumber(CString strPONumber);
	void SetOrigPONumber(CString strOrigPONumber);
	void SetPOType(CString strPOType);
	CButton m_btnOK;
	CComboBox m_cbStoreNumber;
	afx_msg void OnEnKillfocusPoentryPonumberedit();
protected:
	void UpdateStoreNumberCombo(void);
	void EnableOK(void);
public:
	void SetStoreNumber(CString strStoreNumber);
	void SetMaterialTypeShortName(CString strShortName);
protected:
	CString m_strMaterialTypeShortName;
public:
	CString GetMaterialTypeShortName(void);
	afx_msg void OnCbnSelchangePOEntryOrigPOCombo();
protected:
	void UpdateMaterialTypeShortName(void);
public:
	afx_msg void OnCbnSelchangePoentryStorenumber();
	bool IsPriceUpdateNeeded(void);
};

