/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/
#pragma once

#include "NotesPropPage.h"
#include "flooring.h"
#include "ColorTabCtrl.h"

// CNotesPropSheet

class CNotesPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CNotesPropSheet)

public:
	CNotesPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNotesPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNotesPropSheet(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CNotesPropSheet();

	CNotesPropPage m_WONotesPropPage;
	CNotesPropPage m_SPNNotesPropPage;
	CNotesPropPage m_InternalNotesPropPage;
	
	void SetPOList(CPoList* pListPOs, bool bUpdate = true);
	void UpdateRecordSet();
	void SetReadOnly(bool bReadOnly);

	void AdjustControls();
	void UpdateTabColors();

	bool IsDirty();

protected:

	CPoList m_listPOs;
	CString m_strRecordSetFilter;

	CColorTabCtrl m_colorTabCtrl;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

	int GetFirstOrderID();

};

inline int CNotesPropSheet::GetFirstOrderID()
{
	if (m_listPOs.GetCount() > 0)
	{
        POSITION pos = m_listPOs.GetHeadPosition();
		return m_listPOs.GetNext(pos);
	}

	return -1;
}


