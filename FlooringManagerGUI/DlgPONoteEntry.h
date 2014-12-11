/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "ComboPONoteType.h"
#include "ComboSpokeWith.h"
#include "afxdtctl.h"
#include "SetPONotes.h"
#include "CFIMaskedEdit.h"


// CDlgPONoteEntry dialog

class CDlgPONoteEntry : public CDialog
{
	DECLARE_DYNAMIC(CDlgPONoteEntry)

public:
	CDlgPONoteEntry(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPONoteEntry();

	CFont m_fontPhoneNumbers;

// Dialog Data
	enum { IDD = IDD_PONOTE_ENTRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void EnableSpokeWith(int iNoteTypeID);
	void ShowScheduleControlsByNoteType();
	int GetNoteTypeID();
	CString GetNoteType();
	int GetSpokeWithID();
//	void SetSchedulingInfo(COleDateTime dtScheduledDate, BOOL bScheduled, BOOL UnScheduled, BOOL bScheduledAM);
	bool Validate();
	bool FormatEmailBody();
	bool HasAlerts();
	bool AllowSchedulingWithAlerts();
	void EnableOther();
	void EnableButtons(int iNoteTypeID);
	void ShowScheduleControls(bool bShow);
	void ShowScheduleBox(bool bShow);
	void EnableScheduleBox(bool bEnable);
	
	bool m_bCanSchedule;


	int m_iOrderID;
	int m_iCustomerID;
	//CString m_strCustName;
	int m_iId;
	bool m_bNewNote;
	CString m_strEmailBody;
	CString m_strPONumber;
	CString m_strStoreNumber;

	//CString m_strCustPhone1;
	//CString m_strCustPhone2;
	//CString m_strCustPhone3;

	bool m_bDirty;
	bool m_bEditing;
	bool m_bAskToSend;
	
	//bool m_bScheduleChanged;
	//bool m_bReschedule;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void SetOrderID(int iOrderID);
	void SetCustomerID(int iCustomerID);
	void SetNoteId(int iID);
	int  GetNoteID();
	void SetEditingFlag(bool bEditing);

	void OnChange();
	void OnChangeDate();

	CComboPONoteType m_comboNoteType;
	afx_msg void OnCbnSelchangePonoteComboNotetype();
	CComboSpokeWith m_comboSpokeWith;
	CEdit m_editSpokeWithOther;
	CButton m_btnScheduled;
	CButton m_btnUnscheduled;
	CDateTimeCtrl m_dtScheduledDate;
	CButton m_btnAM;
	CButton m_btnPM;
	CButton m_btnCustCallback;
	CEdit m_editNotes;
	CEdit m_editAddNotes;
protected:
	virtual void OnOK();
public:
	afx_msg void OnCbnSelchangePonoteComboSpokewith();
	CStatic m_stAddNotes;
	afx_msg void OnBnClickedScheduled();
	afx_msg void OnBnClickedUnscheduled();
	afx_msg void OnEnChangePonoteNotes();
	afx_msg void OnBnClickedAm();
	afx_msg void OnBnClickedPm();
	afx_msg void OnBnClickedCustToCall();
	afx_msg void OnEnChangePonotesNotesadd();
	afx_msg void OnDtnDatetimechangeDateSchedule(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPonoteSaveandemailButton();
	CStatic m_stPhoneGroup;
	//CStatic m_stPhoneField1;
	//CStatic m_stPhoneField2;
	//CStatic m_stPhoneField3;
	CButton m_btnSaveAndEmail;
	CButton m_btnOK;
	CStatic m_stScheduleGroup;
	CStatic m_stScheduleText;

	bool m_bSendToExpeditor;
	bool m_bCopyToSASM;
	bool m_bCopyToExpeditorEmail;
	CStatic m_stCurrentScheduleDate;
	CDateTimeCtrl m_ScheduleEndDate;
	CStatic m_stScheduleStart;
	CStatic m_stScheduleEnd;
protected:
	CString m_strCustomerName;
	CString m_strSiteAddress;
	CCFIMaskedEdit m_editPhoneWork;
	CCFIMaskedEdit m_editPhoneHome;
	CCFIMaskedEdit m_editPhoneMobile;
	CEdit m_editEmailAddress;
public:
	afx_msg void OnEnHomePhoneChange();
	afx_msg void OnEnWorkPhoneChange();
	afx_msg void OnEnMobilePhoneChange();
	afx_msg void OnEnEmailAddressChange();
};

inline void CDlgPONoteEntry::SetOrderID(int iOrderID)
{
	m_iOrderID = iOrderID;
}

inline void CDlgPONoteEntry::SetCustomerID(int iCustomerID)
{
	m_iCustomerID = iCustomerID;
}

inline int CDlgPONoteEntry::GetNoteID()
{ 
	return m_iId;
}

inline void CDlgPONoteEntry::SetNoteId(int iID)
{
	m_iId = iID ;

	m_bNewNote = false ;

	CSetPONotes set(&g_dbFlooring) ;
	set.m_strFilter.Format("ID = '%d'", m_iId) ;
	set.Open() ;
	SetOrderID(set.m_OrderID) ;
	set.Close() ;
}

inline void CDlgPONoteEntry::SetEditingFlag(bool bEditing)
{
	m_bEditing = bEditing;
}