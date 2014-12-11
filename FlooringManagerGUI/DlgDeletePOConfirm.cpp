// DlgDeletePOConfirm.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgDeletePOConfirm.h"

#include "SetCheckDetails.h"


// CDlgDeletePOConfirm dialog

IMPLEMENT_DYNAMIC(CDlgDeletePOConfirm, CDialog)
CDlgDeletePOConfirm::CDlgDeletePOConfirm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeletePOConfirm::IDD, pParent)
	, m_editYesBox(_T(""))
	, m_strMessageText(_T(""))
	, m_setOrders(&g_dbFlooring)
{
}

CDlgDeletePOConfirm::~CDlgDeletePOConfirm()
{
}

void CDlgDeletePOConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DELETE_PO_DIALOG_YES, m_editYesBox);
	DDV_MaxChars(pDX, m_editYesBox, 3);
	DDX_Text(pDX, IDC_DELETE_PO_DIALOG_TEXT, m_strMessageText);
}


BEGIN_MESSAGE_MAP(CDlgDeletePOConfirm, CDialog)
END_MESSAGE_MAP()


// CDlgDeletePOConfirm message handlers

BOOL CDlgDeletePOConfirm::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT(m_PoList.GetCount() > 0);

	CString strPOList = "";
	m_strOrderIDFilter = "";
	POSITION pos = m_PoList.GetHeadPosition();
	while(pos)
	{
		int iOrderID = m_PoList.GetNext(pos);
		if (strPOList.GetLength() > 0)
		{
			strPOList += ", ";
		}
		if (m_strOrderIDFilter.GetLength() > 0)
		{
			m_strOrderIDFilter += " OR ";
		}
		strPOList += CGlobals::POFromOrderID(iOrderID);
		CString strTemp;
		strTemp.Format("([OrderID] = %d)", iOrderID);
		m_strOrderIDFilter += strTemp;
	}

	if (m_PoList.GetCount() > 1)
	{
		m_strMessageText.Format("To confirm deletion of MULTIPLE POs %s, type \"yes\" into the box below and click OK.", strPOList);
	}
	else
	{
		m_strMessageText.Format("To confirm deletion of PO %s, type \"yes\" into the box below and click OK.", strPOList);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDeletePOConfirm::OnOK()
{
	UpdateData();

	if ( m_editYesBox.MakeUpper() == "YES" )
	{
		if (!DeletePO())
		{
			MessageBox("PO was NOT deleted.", "Notice");
		}
	}

	CDialog::OnOK();
}

bool CDlgDeletePOConfirm::CanDeletePO()
{
	// the PO cannot be deleted if it is referenced in a CheckDetail or Job

	bool bCanDelete = true;

	POSITION pos = m_PoList.GetHeadPosition();

	CSetCheckDetails setCheckDetails(&g_dbFlooring);
	setCheckDetails.m_strFilter = "OrderID = -1";
	setCheckDetails.Open();

	while(pos)
	{
		int iOrderID = m_PoList.GetNext(pos);

		setCheckDetails.m_strFilter.Format("OrderID = %d", iOrderID);
		setCheckDetails.Requery();
		if ( !setCheckDetails.IsEOF() )
		{
			// we found a record, so can't delete PO
			return false;
		}
	}

	setCheckDetails.Close();

	return bCanDelete;

}

bool CDlgDeletePOConfirm::DeletePO()
{
	bool bDeletedOK = true;

	POSITION pos = m_PoList.GetHeadPosition();

	while(pos)
	{
		CString strFilter;
		int iOrderID = m_PoList.GetNext(pos);
		strFilter.Format("[OrderID] = %d", iOrderID);
		
		try
		{
			m_setOrders.m_strFilter = strFilter;
			m_setOrders.Open();
			m_setOrders.Edit() ;
			m_setOrders.m_Deleted = true ;
			m_setOrders.Update() ;
			m_setOrders.Close();
		}
		catch (CDBException* e)
		{
			MessageBox(e->m_strError, "Error!");
			e->Delete();
			bDeletedOK = false;
			break;
		}
	}

	return bDeletedOK;
}
