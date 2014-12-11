// DlgSelectMerchandise.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSelectMerchandise.h"
#include ".\dlgselectmerchandise.h"
#include "SetOrderSOMerchandiseDetails.h"


// CDlgSelectMerchandise dialog

IMPLEMENT_DYNAMIC(CDlgSelectMerchandise, CDialog)
CDlgSelectMerchandise::CDlgSelectMerchandise(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectMerchandise::IDD, pParent)
{
	m_dQuantity = 0.0;
	m_strSONumber = "";
	m_iMerchID = -1;
}

CDlgSelectMerchandise::~CDlgSelectMerchandise()
{
}

void CDlgSelectMerchandise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MERCH_SELECTION, m_comboSelectMerchandise);
}


BEGIN_MESSAGE_MAP(CDlgSelectMerchandise, CDialog)
	ON_REGISTERED_MESSAGE( wm_MATERIAL_SELECT, OnMaterialSelected)
END_MESSAGE_MAP()


// CDlgSelectMerchandise message handlers

BOOL CDlgSelectMerchandise::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT(m_dQuantity != 0.0);
	ASSERT(m_strSONumber.GetLength() > 0);

	FillComboBox();

	m_comboSelectMerchandise.SetCurSel(0);

	m_gridSOSelectMerch.AttachGrid(this, IDC_SO_MERCH_GRID_AREA);
	CString strFilter;
	strFilter.Format("Quantity = %f AND SONumber = '%s'", m_dQuantity, m_strSONumber);
	m_gridSOSelectMerch.SetFilter(strFilter);
	m_gridSOSelectMerch.ShowDeleted(true);
	m_gridSOSelectMerch.UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectMerchandise::FillComboBox()
{
	CSetOrderSOMerchandiseDetails set(&g_dbFlooring);

	set.m_strFilter.Format("Quantity = %f AND SONumber = '%s'", m_dQuantity, m_strSONumber);
	set.Open();

	CString strData;
	while(!set.IsEOF())
	{
		strData.Format("%s (OrderID = %d)", set.m_Description, set.m_OrderID);
		int iIndex = m_comboSelectMerchandise.AddString(strData);
		m_comboSelectMerchandise.SetItemData(iIndex, set.m_ID);
		set.MoveNext();
	}
}


void CDlgSelectMerchandise::OnOK()
{
	//m_iMerchID = m_comboSelectMerchandise.GetItemData(m_comboSelectMerchandise.GetCurSel());
	m_iMerchID = (int)m_gridSOSelectMerch.GetSelectedID();
	CDialog::OnOK();
}

LRESULT CDlgSelectMerchandise::OnMaterialSelected(WPARAM /* wParam */, LPARAM /* lParam */)
{
	::PostMessage(m_hWnd, WM_COMMAND, (WPARAM) IDOK, 0);
	return true ;
}