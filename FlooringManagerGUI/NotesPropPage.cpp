/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// NotesPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "NotesPropPage.h"

// CNotesPropPage dialog

IMPLEMENT_DYNAMIC(CNotesPropPage, CPropertyPage)
CNotesPropPage::CNotesPropPage()
	: CPropertyPage(CNotesPropPage::IDD)
{
	m_bConsolidatedView = false;
	m_strRecordSetFilter = "";
	m_bReadOnly = false;
	m_pSetOrders = NULL;
	m_strOrigText = "";
}

CNotesPropPage::~CNotesPropPage()
{
	if (m_pSetOrders != NULL)
	{
		delete m_pSetOrders;
	}
}

void CNotesPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOTES, m_editNotes);
}


BEGIN_MESSAGE_MAP(CNotesPropPage, CPropertyPage)
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CNotesPropPage message handlers

void CNotesPropPage::SetPOList(CPoList* pListPOs, bool bUpdate)
{
	if (pListPOs != NULL)
	{
		m_listPOs.AddHead(pListPOs);
		if (m_listPOs.GetCount() > 1)
		{
			m_bConsolidatedView = true;
		}

		m_strRecordSetFilter = "";

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

	if (bUpdate)
	{
		InitEditField();
	}
}

CString CNotesPropPage::GetNote()
{
	CString strNote = "";
	m_editNotes.GetWindowText(strNote);
	
	return strNote;
}

void CNotesPropPage::InitEditField()
{
	m_editNotes.SetLimitText(CGlobals::iMAX_ORDER_NOTES);
	if (m_strRecordSetFilter.GetLength() > 0)
	{
		m_pSetOrders = new CSetOrders(&g_dbFlooring);
		m_pSetOrders->m_strFilter = m_strRecordSetFilter;
		m_pSetOrders->Open();
		
		if (!m_pSetOrders->IsEOF())
		{
			switch (m_iPageType)
			{
				case WO_NOTES:
					{
						m_editNotes.SetWindowText(m_pSetOrders->m_Notes);
						m_editNotes.SetSel(-1, 0);
					}
					break;
				case SPN_NOTES:
					{
						CString strText = m_pSetOrders->m_SPNNotes;
						strText.Replace("<NOTE>", "");
						strText.Replace("</NOTE>", "");
						m_editNotes.SetWindowText(strText);
						m_editNotes.SetReadOnly();
						m_bReadOnly = true;
						m_editNotes.SetSel(-1, 0);
					}
					break;				
				default:
					break;
			}
		}
	}

	m_editNotes.GetWindowText(m_strOrigText);
}

void CNotesPropPage::AdjustControls()
{
	if (::IsWindow(this->m_hWnd))
	{
		CRect page_rect;
		GetClientRect(&page_rect);
		m_editNotes.MoveWindow(&page_rect);
	}
}

BOOL CNotesPropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CString strTitle(m_psp.pszTitle);

	if (strTitle == szWO_NOTES)
	{
		m_iPageType = WO_NOTES;
	}
	else if (strTitle == szSPN_NOTES)
	{
		m_iPageType = SPN_NOTES;
		m_editNotes.SetReadOnly();
		m_bReadOnly = true;
	}
	else
	{
		ASSERT(FALSE);
	}

	m_editNotes.SetReadOnly( m_bReadOnly == true );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNotesPropPage::SetReadOnly(bool bReadOnly)
{
	if (m_iPageType == WO_NOTES)
	{
		m_bReadOnly = bReadOnly;
		if (::IsWindow(m_editNotes.m_hWnd))
		{
			m_editNotes.SetReadOnly( m_bReadOnly == true );
		}
	}
	else
	{
		m_editNotes.SetCanAddNote( !bReadOnly );
	}
}

