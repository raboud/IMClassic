#pragma once
#include "SetSubContractor.h"	// Added by ClassView
#include "CFIMaskedEdit.h"
#include "FloatEdit.h"
#include "ComboSubContractor.h"
#include "ComboMarket.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ListBoxDivision.h"
#include "ComboBoxInstallerStatus.h"
#include "afxdtctl.h"
#include "Pictctrl.h"

// CDlgSubContractor dialog

class CDlgSubContractor : public CDialog
{
	DECLARE_DYNAMIC(CDlgSubContractor)

public:
	CDlgSubContractor(bool bAdding, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSubContractor();

// Dialog Data
	enum { IDD = IDD_SUBCONTRACTOR };
	
	CEdit m_editFirstName;
	CEdit m_editLastName;
	CEdit m_editNickName;

	CButton m_btnActive;
	CButton m_btnHelper;

	CEdit m_editAddress;
	CEdit m_editCity;
	CEdit m_editState;
	
	CCFIMaskedEdit	m_editZip;
	CCFIMaskedEdit	m_editSSN;
	CCFIMaskedEdit	m_editHomePhone;
	CCFIMaskedEdit	m_editCellNumber;
	CCFIMaskedEdit	m_editPager;

	CButton m_btnWorkmansCompInsuranceOK;
	CButton m_btnLiabilityInsuranceOK;

	CDateTimeCtrl m_dtpWorkmansCompInsurance;
	CDateTimeCtrl m_dtpLiabilityInsurance;

	CFloatEdit	m_editInsuranceRatePct;
	CFloatEdit	m_editInsuranceRateDollars;

	CFloatEdit	m_editRetainageRate;
	CFloatEdit  m_editRetainageAccountBalance;
	CStatic m_stRetainageText1;
	CStatic m_stRetainageText2;

	CButton m_btnBackgroundReqSent;
	CButton m_btnBackgroundCheckPassed;
	CEdit	m_editBadgeStatus;
	CDateTimeCtrl m_dtpBackgroundChkDateApproved;
	
	long assingedTo;
	
	CEdit m_editNotes;

	CButton m_btnOK;
	CButton m_btnCancel;

	CComboSubContractor m_comboAssignedTo;
	CComboInstallerStatus m_comboInstallerStatus;

	CSetSubContractor* m_pSet;
	
	virtual BOOL OnInitDialog();

	void SetSubContractorID(int iSubContractorID);
	afx_msg void OnBnClickedHelper();
	CComboMarket m_cbMarket;
	CListBoxDivision m_lbDivisions;
	afx_msg void OnBnClickedWorkmansCompInsuranceOK();
	
	
	afx_msg void OnBnClickedLiabilityInsuranceOK();
	CPictureCtrl m_pictSubContractor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void UpdateRates(CDataExchange* pDX);
	void UpdateDivisionsLB(CDataExchange* pDX);

	bool ValidateInsurance(bool bShowMsg = true);
	bool ValidateSSN();
	bool ValidateName();
	void ShowRetainageControls(bool bShow);
	void UpdateStatus(CDataExchange* pDX);
	bool CopyPicture(const CString& strPathAndFilename, const CString& strFilename, CString& strNewFilename);

	bool m_bAdding;  // if true we are adding, else editing
	int m_iSubContractorID;  // only valid if editing

	DECLARE_MESSAGE_MAP()

	virtual void OnOK();
	virtual void OnCancel();

	bool ValidateHelper(void);
	void ClearDivisionSelections(void);

	//CString m_strPictureFilename;
	
public:
	CButton m_butSetPicture;
	afx_msg void OnBnClickedSubPictureSelect();
};
