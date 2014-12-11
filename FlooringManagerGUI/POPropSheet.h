/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "SOMerchPropPage.h"
#include "RegMerchPropPage.h"
#include "flooring.h"
#include "ColorTabCtrl.h"

// CPOPropSheet

class CPOPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPOPropSheet)

public:
	CPOPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPOPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPOPropSheet(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPOPropSheet();

	double CalculatePrice(bool bOnlyBasicToMinimum);

	bool IsDirty();

	CSOMerchPropPage m_SOMerchPropPage;
	CRegMerchPropPage m_RegMerchPropPage;

	void ShowDeleted(bool bShow) ;
	void SetAllowStatusUpdate(bool bAllowStatusUpdate) ;
	void SetInvokedFromSPN(bool bInvokedFromSPN);

//	void SetOrderID(long lOrderID);
	void SetOrderDate(COleDateTime datePODate);

	void SetPOList(CPoList* pListPOs, bool bUpdateGrid = true);
	void UpdateRecordSet();

	void UpdateTabColors();

	bool HasUnknownStatus();

protected:
	DECLARE_MESSAGE_MAP()

	int GetFirstOrderID();

	CColorTabCtrl m_colorTabCtrl;
	CPoList m_listPOs;


public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnTabColorUpdate (WPARAM, LPARAM);
	virtual BOOL OnInitDialog();
};

inline int CPOPropSheet::GetFirstOrderID()
{
	if (m_listPOs.GetCount() > 0)
	{
        POSITION pos = m_listPOs.GetHeadPosition();
		return m_listPOs.GetNext(pos);
	}

	return -1;
}
