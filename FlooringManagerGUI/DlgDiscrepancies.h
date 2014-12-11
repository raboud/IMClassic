#pragma once

#include "GridDiscrepancies.h"

// CDlgDiscrepancies dialog

class CDlgDiscrepancies : public CDialog
{
	DECLARE_DYNAMIC(CDlgDiscrepancies)

public:
	CDlgDiscrepancies(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDiscrepancies();

	void SetPOList(CPoList* pListPOs);

// Dialog Data
	enum { IDD = IDD_DISCREPANCIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void FixZipCodes() ;
	void FixWorkPhoneNumbers() ;
	void FixPrice() ;
	void FixQuantity() ;
	CGridDiscrepancies m_gridDiscrepancies;

	CPoList m_listPOs;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
