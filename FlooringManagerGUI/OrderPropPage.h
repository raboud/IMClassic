/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once

#include "GridPOBase.h"

// COrderPropPage dialog

class COrderPropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(COrderPropPage)

public:
	COrderPropPage(UINT nID);
	COrderPropPage();
	virtual ~COrderPropPage();

	void SetPOList(CPoList* pListPOs, bool bUpdateGrid);

	void UpdateRecordSet();

	void SetInvokedFromSPN(bool bInvokedFromSPN);

	bool IsDirty();

// Dialog Data
	enum { IDD = IDD_ORDERPROPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CGridPOBase* m_pGrid;
};

inline bool COrderPropPage::IsDirty()
{
	return m_pGrid->IsDirty();
}
