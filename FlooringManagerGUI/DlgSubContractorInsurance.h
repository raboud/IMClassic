/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "FloatEdit.h"


// DlgSubContractorInsurance dialog

class DlgSubContractorInsurance : public CDialog
{
	DECLARE_DYNAMIC(DlgSubContractorInsurance)

public:
	DlgSubContractorInsurance(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgSubContractorInsurance();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBCONTRACTOR_INSURANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	bool ValidateInsurance(bool bShowMsg = true);

	int m_iSubContractorID;

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void SetSubContractorID(int iID);

	CString m_strSubContractorName;
	CFloatEdit m_editInsuranceDollar;
	CFloatEdit m_editInsurancePct;
};

inline void DlgSubContractorInsurance::SetSubContractorID(int iID)
{
	m_iSubContractorID = iID;
}
