/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// POPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "NotesPropSheet.h"
#include "SetDiscrepancies.h"
#include "Globals.h"

// CNotesPropSheet

IMPLEMENT_DYNAMIC(CNotesPropSheet, CPropertySheet)
CNotesPropSheet::CNotesPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CNotesPropSheet::CNotesPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CNotesPropSheet::CNotesPropSheet(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet("test", pParentWnd, iSelectPage)
{
	m_WONotesPropPage.m_psp.dwFlags |= PSP_USETITLE;
	m_WONotesPropPage.m_psp.pszTitle = szWO_NOTES;

	m_SPNNotesPropPage.m_psp.dwFlags |= PSP_USETITLE;
	m_SPNNotesPropPage.m_psp.pszTitle = szSPN_NOTES;

	//m_InternalNotesPropPage.m_psp.dwFlags |= PSP_USETITLE;
	//m_InternalNotesPropPage.m_psp.pszTitle = szINTERNAL_NOTES;

	AddPage(&m_WONotesPropPage);
	AddPage(&m_SPNNotesPropPage);
	//AddPage(&m_InternalNotesPropPage);

	m_strRecordSetFilter = "";
}

CNotesPropSheet::~CNotesPropSheet()
{
}


BEGIN_MESSAGE_MAP(CNotesPropSheet, CPropertySheet)
END_MESSAGE_MAP()


// CNotesPropSheet message handlers

void CNotesPropSheet::SetPOList(CPoList* pListPOs, bool bUpdate)
{
	m_WONotesPropPage.SetPOList(pListPOs, bUpdate);
	m_SPNNotesPropPage.SetPOList(pListPOs, bUpdate);
//	m_InternalNotesPropPage.SetPOList(pListPOs, bUpdate);
	m_listPOs.RemoveAll();
	m_listPOs.AddHead(pListPOs);
	
	POSITION pos = m_listPOs.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_listPOs.GetNext(pos);
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " OR ";
		}
		CString strTemp;
		strTemp.Format("([OrderID] = %d)", iOrderID);
		m_strRecordSetFilter += strTemp;
	}
}

void CNotesPropSheet::UpdateRecordSet()
{
	// get the notes from all three windows and do one update to the record set
	CString strWONotes = m_WONotesPropPage.GetNote();
//	CString strInternalNotes = m_InternalNotesPropPage.GetNote();
	if (m_listPOs.GetCount() == 1)
	{
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter = m_strRecordSetFilter;
		setOrders.Open();
		if (!setOrders.IsEOF())
		{
			setOrders.Edit();
			setOrders.m_Notes = strWONotes;
//			setOrders.m_InternalNotes = strInternalNotes;
			setOrders.Update();
		}
	}
}

void CNotesPropSheet::SetReadOnly(bool bReadOnly)
{
	m_WONotesPropPage.SetReadOnly(bReadOnly);
//	m_InternalNotesPropPage.SetReadOnly(bReadOnly);
}

void CNotesPropSheet::AdjustControls()
{
	m_WONotesPropPage.AdjustControls();
	m_SPNNotesPropPage.AdjustControls();
//	m_InternalNotesPropPage.AdjustControls();
}

BOOL CNotesPropSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	m_colorTabCtrl.SubclassWindow(GetTabControl()->m_hWnd);
	m_colorTabCtrl.ModifyStyle(0, TCS_OWNERDRAWFIXED);

	m_colorTabCtrl.SetTextColor(CGlobals::COLOR_BLUE);
	m_colorTabCtrl.SetBkColor(CGlobals::COLOR_ALERT);

	m_colorTabCtrl.InitColorArray();

	UpdateTabColors();

	return bResult;
}

void CNotesPropSheet::UpdateTabColors()
{
	if (CGlobals::OrderHasNotesAlerts(GetFirstOrderID()))
	{
		m_colorTabCtrl.UseColors((char*)szWO_NOTES);
		m_colorTabCtrl.UseColors((char*)szSPN_NOTES);
	}
	else
	{
		m_colorTabCtrl.UseColors((char*)szWO_NOTES, false);
		m_colorTabCtrl.UseColors((char*)szSPN_NOTES, false);
	}

	Invalidate();
}

bool CNotesPropSheet::IsDirty()
{
	return m_WONotesPropPage.IsDirty() || m_SPNNotesPropPage.IsDirty();
}