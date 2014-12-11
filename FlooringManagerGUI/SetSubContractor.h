/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#if !defined(AFX_SETSUBCONTRACTOR_H__45288DBD_2F07_4FED_ABE5_43EF32FF31CA__INCLUDED_)
#define AFX_SETSUBCONTRACTOR_H__45288DBD_2F07_4FED_ABE5_43EF32FF31CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSubContractor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetSubContractor recordset

class CSetSubContractor : public CRecordset
{
public:
	CSetSubContractor(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetSubContractor)

// Field/Param Data
	//{{AFX_FIELD(CSetSubContractor, CRecordset)
	long	m_SubContractorID;
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_NickName;
	CString	m_Address;
	CString	m_City;
	CString	m_State;
	CString	m_ZipCode;
	CString	m_HomePhoneNumber;
	CString	m_CellPhoneNumber;
	CString	m_Pager;
	CString	m_SSN;
	BOOL	m_WorkmansCompInsuranceOK;
	BOOL    m_LiabilityInsuranceOK;
	COleDateTime m_WorkmansCompInsuranceDate;
	COleDateTime m_LiabilityInsuranceDate;
	COleDateTime m_BackgroundChkDateApproved;
	BOOL	m_BackgroundCheckPassed;
	CString	m_Notes;
	CString	m_Retainage;
	CString	m_RetainageRate;
	double	m_SavingsRate;
	CString	m_InsuranceRate;
	BOOL	m_Helper;
	BOOL    m_BackgroundRptRequested;
	CString m_BadgeStatus;
	CString m_InsuranceDollarAmount;
	long m_AssignedTo;
	long m_MarketId;
	long m_Status;
	CString m_PictureFilename;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetSubContractor)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSUBCONTRACTOR_H__45288DBD_2F07_4FED_ABE5_43EF32FF31CA__INCLUDED_)
