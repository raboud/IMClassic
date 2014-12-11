#pragma once
#include "afxwin.h"
#include "flooring.h"
#include "GridSelectSOMerchandise.h"

// CDlgSelectMerchandise dialog

class CDlgSelectMerchandise : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectMerchandise)

public:
	CDlgSelectMerchandise(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectMerchandise();

// Dialog Data
	enum { IDD = IDD_MERCH_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	void FillComboBox();

	DECLARE_MESSAGE_MAP()

	CString m_strSONumber;
	double m_dQuantity;
	int m_iMerchID;

	CGridSelectSOMerchandise m_gridSOSelectMerch;

public:
	CComboBox m_comboSelectMerchandise;
	virtual BOOL OnInitDialog();

	void SetQuantity(double dQuantity);
	void SetSONumber(CString strSONumber);
	int  GetMerchID();

	afx_msg LRESULT OnMaterialSelected(WPARAM /* wParam */, LPARAM /* lParam */);

protected:
	virtual void OnOK();
};

inline void CDlgSelectMerchandise::SetQuantity(double dQuantity)
{
	m_dQuantity = dQuantity;
}

inline void CDlgSelectMerchandise::SetSONumber(CString strSONumber)
{
	m_strSONumber = strSONumber;
}

inline int CDlgSelectMerchandise::GetMerchID()
{
	return m_iMerchID;
}
