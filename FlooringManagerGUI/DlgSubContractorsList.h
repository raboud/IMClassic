#pragma once

#include "afxwin.h"
#include "GridSubContractorsList.h"
#include "ComboBoxInstallerStatus.h"

// CDlgSubContractorsList dialog

class CDlgSubContractorsList : public CDialog
{
	DECLARE_DYNAMIC(CDlgSubContractorsList)

public:
	CDlgSubContractorsList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSubContractorsList();

// Dialog Data
	enum { IDD = IDD_SUBCONTRACTORS_PICKLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


	CGridSubContractorsList m_gridSubContractors;
public:
	virtual BOOL OnInitDialog();
	CComboInstallerStatus m_comboFilter;
	afx_msg void OnCbnSelchangeFilterCombo();
};
