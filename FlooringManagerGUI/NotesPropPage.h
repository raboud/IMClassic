/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include "afxwin.h"
#include "setorders.h"
#include "notesedit.h"



// CNotesPropPage dialog

class CNotesPropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CNotesPropPage)

public:
	CNotesPropPage();
	virtual ~CNotesPropPage();

	void SetPOList(CPoList* pListPOs, bool bUpdate);
	CString GetNote();
	void SetReadOnly(bool bReadOnly);

	bool IsDirty();

// Dialog Data
	enum { IDD = IDD_NOTES_PROP_PAGE };
	enum { WO_NOTES = 0, SPN_NOTES, INTERNAL_NOTES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitEditField();

	CPoList m_listPOs;
	CString m_strOrigText;

	int m_iPageType;   // WO, SPN, or Internal
	bool m_bConsolidatedView;
	bool m_bReadOnly;
	CString m_strRecordSetFilter;

	CSetOrders* m_pSetOrders;

	DECLARE_MESSAGE_MAP()
public:
	CNotesEdit m_editNotes;
	virtual BOOL OnInitDialog();
	void AdjustControls();

	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

inline bool CNotesPropPage::IsDirty()
{
	CString strTemp;
	m_editNotes.GetWindowText(strTemp);
	if (strTemp.Compare(m_strOrigText) != 0)
	{
		return true;
	}

	return false;
}
