/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgMaterialStatus.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "DlgMaterialStatus.h"
#include "SetMatStatus.h"
#include "DlgSelectMerchandise.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int iMAT_STATUS_PRESENT = 2;

/////////////////////////////////////////////////////////////////////////////
// CDlgMaterialStatus dialog


CDlgMaterialStatus::CDlgMaterialStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMaterialStatus::IDD, pParent), m_setSOMerchandiseDetails(&g_dbFlooring)
	, m_setOrders(&g_dbFlooring)
	, m_setCustomer(&g_dbFlooring)
	, m_strCustomerName(_T("N/A"))
	, m_strPO(_T("N/A"))
{
	//{{AFX_DATA_INIT(CDlgMaterialStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_setSOMerchandiseDetails.m_strFilter = "ID = -1";
	m_setSOMerchandiseDetails.Open() ;

	m_setOrders.m_strFilter = "OrderID = -1";
	m_setOrders.Open();

	m_setCustomer.m_strFilter = "CustomerID = -1";
	m_setCustomer.Open();
}


void CDlgMaterialStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMaterialStatus)
	DDX_Control(pDX, IDC_STATUS, m_comboStatus);
	DDX_Control(pDX, IDC_NUMBER, m_editSO);
	DDX_Control(pDX, IDOK, m_butOk);
	DDX_Control(pDX, IDCANCEL, m_butCancel);
	DDX_Control(pDX, IDC_DONE, m_butDone);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_MATERIALSTATUS_CUSTNAME, m_strCustomerName);
	DDX_Text(pDX, IDC_MATERIALSTATUS_PO, m_strPO);
	DDX_Control(pDX, IDC_MATERIALSTATUS_RESET, m_btnReset);
	DDX_Control(pDX, IDC_YARDAGE, m_editYardage);
	DDX_Control(pDX, IDC_CUSTNAME_STATIC, m_stCustName);
	DDX_Control(pDX, IDC_PO_STATIC, m_stPOStatic);
	DDX_Control(pDX, IDC_FIND_BUTTON, m_btnFind);
	DDX_Control(pDX, IDC_MATERIALSTATUS_CUSTNAME, m_stCustNameField);
	DDX_Control(pDX, IDC_MATERIALSTATUS_PO, m_stPOField);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_stStatus);
	DDX_Control(pDX, IDC_MATERIAL_DESCRIPTION, m_statMaterialDescription);
}


BEGIN_MESSAGE_MAP(CDlgMaterialStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgMaterialStatus)
	ON_BN_CLICKED(IDC_DONE, OnDone)
	ON_EN_CHANGE(IDC_NUMBER, OnChangeNumber)
	ON_EN_KILLFOCUS(IDC_NUMBER, OnKillfocusNumber)
	ON_CBN_SELCHANGE(IDC_STATUS, OnSelchangeStatus)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MATERIALSTATUS_RESET, OnBnClickedMaterialstatusReset)
	ON_EN_KILLFOCUS(IDC_YARDAGE, OnEnKillfocusYardage)
	ON_BN_CLICKED(IDC_FIND_BUTTON, OnBnClickedFindButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMaterialStatus message handlers

void CDlgMaterialStatus::OnDone() 
{
	CDlgMaterialStatus::OnOK();
}

void CDlgMaterialStatus::OnCancel() 
{
	CDialog::OnCancel();
	/*m_butCancel.EnableWindow(FALSE) ;
	m_butOk.EnableWindow(FALSE) ;
	m_butDone.EnableWindow();
	UpdateCBStatus();
	m_editSO.EnableWindow() ;
	m_editSO.SetFocus();*/
}

void CDlgMaterialStatus::OnOK() 
{
	if (m_btnFind.IsWindowVisible())
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(m_btnFind.GetDlgCtrlID(), BN_CLICKED), LPARAM(m_btnFind.m_hWnd)); 
		return;
	}
	int StatusID = m_comboStatus.GetItemData(m_comboStatus.GetCurSel());
	if (StatusID != m_setSOMerchandiseDetails.m_MaterialStatusID)
	{
		int iMessage = MessageBox("Save Changes?", "Question", MB_YESNOCANCEL);
		if (iMessage == IDYES)
		{
			m_setSOMerchandiseDetails.Edit();
			m_setSOMerchandiseDetails.m_MaterialStatusID = StatusID;
			if (m_setSOMerchandiseDetails.Update())
			{
				m_setSOMerchandiseDetails.Requery();

				if ((m_setSOMerchandiseDetails.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED) ||
					     (m_setSOMerchandiseDetails.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED))
				{
					if (StatusID == iMAT_STATUS_PRESENT)
					{
						CString strSQL = "";
						strSQL.Format("EXEC up_QueueSPNAction %d, '%d'", CGlobals::iSPN_ACTION_VERIFY_PRODUCT_RECEIPT, m_setSOMerchandiseDetails.m_ID);
						g_dbFlooring.ExecuteSQL(strSQL);
					}
				}
			}
		}
		
		if (iMessage == IDYES || iMessage == IDNO)
		{
			ShowControls(false);
			m_editSO.SetWindowText("");
			m_editYardage.SetWindowText("");
			m_editSO.SetFocus();
		}
	}
	else
	{
		ShowControls(false);
		m_editSO.SetWindowText("");
		m_editYardage.SetWindowText("");
		m_editSO.SetFocus();
	}
	
	/*m_butCancel.EnableWindow(FALSE) ;
	m_butOk.EnableWindow(FALSE) ;
	m_editSO.EnableWindow() ;
	m_butDone.EnableWindow();
	m_editSO.SetFocus();*/
}

void CDlgMaterialStatus::OnChangeNumber() 
{
	/*if (Validate(false))
	{
		UpdateCBStatus() ;
		UpdateStrings();
		UpdateData(FALSE);
	}
	else
	{
		m_butCancel.EnableWindow(FALSE) ;
		m_butOk.EnableWindow(FALSE) ;
		m_comboStatus.EnableWindow(FALSE);
		UpdateData();
		m_strCustomerName = "N/A";
		m_strPO = "N/A";
		m_editSO.SetFocus() ;
		UpdateData(FALSE);
	}*/
}

void CDlgMaterialStatus::OnKillfocusNumber() 
{
	//HandleValidation();
}

void CDlgMaterialStatus::OnSelchangeStatus() 
{
	/*m_butCancel.EnableWindow() ;
	m_butOk.EnableWindow() ;
	m_butDone.EnableWindow(FALSE) ;*/
}

BOOL CDlgMaterialStatus::OnInitDialog() 
{
	m_bError = false ;
	CDialog::OnInitDialog();
	m_editSO.SetLimitText(CGlobals::iMAX_SO_NUMBER) ;
	

	CSetMatStatus set(&g_dbFlooring);

	m_statMaterialDescription.SetWindowText("") ;

	set.Open() ;
	while (!set.IsEOF())
	{
		int iItem = m_comboStatus.AddString(set.m_Status) ;
		m_comboStatus.SetItemData(iItem, set.m_MatStatusID) ;
		set.MoveNext() ;
	}
	set.Close() ;
	m_comboStatus.SetCurSel(-1) ;
	m_comboStatus.EnableWindow(FALSE) ;
//	m_butCancel.EnableWindow(FALSE) ;
//	m_butOk.EnableWindow(FALSE) ;
//	m_editYardage.AllowBlank(true);
//	m_editYardage.AllowNegative(false);
//	m_editYardage.SetNumberDecimals(2);
	ShowControls(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

bool CDlgMaterialStatus::Validate(bool bDisplayMessage)
{
	CString strSo ;
	bool bReturn = false ;
	m_editSO.GetWindowText(strSo) ;
	if (strSo.GetLength() == 8)
	{
		if (strSo.GetAt(2) == '5')
		{
			bReturn = true ;
		}
		else if (bDisplayMessage)
		{	
			m_bError = true ;
			MessageBox("This is an invalid Special Order number.", "SO Number Error") ;
			m_bError = false ;
		}
	}
	else if (bDisplayMessage)
	{	
		m_bError = true ;
		MessageBox("This is an invalid Special Order number.", "SO Number Error") ;
		m_bError = false ;
	}

	if (bReturn)
	{
		// see if this combination of SO Number / Yardage exists in the database
		CString strSo ;
		CString strQuantity;
		double dQuantity;
		m_editSO.GetWindowText(strSo) ;
		m_editYardage.GetWindowText(strQuantity);
		if (strQuantity.GetLength() > 0)
		{
			dQuantity = atof(strQuantity);

			m_setSOMerchandiseDetails.m_strFilter.Format("SONumber = '%s' AND Quantity = %f AND Deleted = 0 ", strSo, dQuantity) ;
			m_setSOMerchandiseDetails.Requery() ;
			if (m_setSOMerchandiseDetails.IsEOF())
			{
				if (bDisplayMessage)
				{	
					m_bError = true ;
					MessageBox("Material Not Found.", "SO Number/Quantity Error") ;
					m_bError = false ;
				}
				bReturn = false;
			}
			else
			{
				CDlgSelectMerchandise dlg;
				dlg.SetSONumber(strSo);
				dlg.SetQuantity(dQuantity);
				if (dlg.DoModal() == IDOK)
				{
					m_setSOMerchandiseDetails.m_strFilter.Format("ID = %d", dlg.GetMerchID());
					m_setSOMerchandiseDetails.Requery();
					if (m_setSOMerchandiseDetails.IsEOF())
					{
						bReturn = false;
						if (bDisplayMessage)
						{
							m_bError = true ;
							MessageBox("Selected merchandise was not found.", "Error!") ;
							m_bError = false ;
						}
					}
				}
				else
				{
					bReturn = false;
				}
				if (!m_setSOMerchandiseDetails.IsEOF())
				{
					m_setSOMerchandiseDetails.MoveFirst();
				}
			}
		}
		else
		{
			if (bDisplayMessage)
			{	
				m_bError = true ;
				MessageBox("Quantity must be entered.", "SO Number/Yardage Error") ;
				m_bError = false ;
			}
			bReturn = false;
		}
	}

	return bReturn ;

}

void CDlgMaterialStatus::UpdateCBStatus()
{
	ASSERT(!m_setSOMerchandiseDetails.IsEOF());
	if (!m_setSOMerchandiseDetails.IsEOF())
	{
		//m_comboStatus.EnableWindow() ;
		for (int i=0;i < m_comboStatus.GetCount();i++)
		{
			if (m_comboStatus.GetItemData(i) == (DWORD) m_setSOMerchandiseDetails.m_MaterialStatusID)
			{
				m_comboStatus.SetCurSel(i);
				break ;
			}
		}
		//m_editSO.EnableWindow(FALSE) ;
	}
	/*else
	{
		m_bError = true ;
		MessageBox("This Special Order number is not in the system.", "SO Number Not Found") ;
		m_bError = false ;
		m_comboStatus.EnableWindow(FALSE) ;
		m_comboStatus.SetCurSel(-1) ;
	}*/
	
}

void CDlgMaterialStatus::UpdateStrings(void)
{
	UpdateData();
	m_strCustomerName = "N/A";
	m_strPO = "N/A";
	if (!m_setSOMerchandiseDetails.IsEOF())
	{
		CString strSONumber;
		int iOrderID;
		m_editSO.GetWindowText(strSONumber);
		iOrderID = m_setSOMerchandiseDetails.m_OrderID;
		m_setOrders.m_strFilter.Format("OrderID = %d", iOrderID) ;
		m_setOrders.Requery();
		if (!m_setOrders.IsEOF())
		{
			m_setCustomer.m_strFilter.Format("CustomerID = %d", m_setOrders.m_CustomerID);
			m_setCustomer.Requery();
			if (!m_setCustomer.IsEOF())
			{
				m_strPO = m_setOrders.m_PurchaseOrderNumber;
				m_strCustomerName.Format("%s, %s", m_setCustomer.m_LastName, m_setCustomer.m_FirstName);
			}
		}
		m_statMaterialDescription.SetWindowText(m_setSOMerchandiseDetails.m_Description) ;
	}
	UpdateData(FALSE);
}

void CDlgMaterialStatus::OnBnClickedMaterialstatusReset()
{
	m_editSO.EnableWindow();
	m_editSO.SetWindowText("");
	m_comboStatus.SetCurSel(-1) ;
	m_comboStatus.EnableWindow(FALSE) ;
	m_butCancel.EnableWindow(FALSE) ;
	m_butOk.EnableWindow(FALSE) ;
	m_butDone.EnableWindow() ;
	m_strCustomerName = "N/A";
	m_strPO = "N/A";
	UpdateData(FALSE);
	//m_editSO.SetFocus();
}

void CDlgMaterialStatus::OnEnKillfocusYardage()
{
	//HandleValidation();
}

void CDlgMaterialStatus::HandleValidation()
{
	CWnd* pFocus = GetFocus() ;

	if ((pFocus != NULL) && (m_bError == false))
	{
		if (pFocus->m_hWnd == m_btnReset.m_hWnd) 
		{
			return;
		}

		if ((pFocus->m_hWnd != m_butDone.m_hWnd) && 
			(pFocus->m_hWnd != m_editYardage.m_hWnd) && 
			(pFocus->m_hWnd != m_editSO.m_hWnd))
		{
			if (Validate(true))
			{
				UpdateCBStatus() ;
				m_comboStatus.SetFocus() ;
			}
			else
			{
				m_butCancel.EnableWindow(FALSE) ;
				m_butOk.EnableWindow(FALSE) ;
				m_editSO.SetFocus() ;
			}
		}
	}
}
void CDlgMaterialStatus::OnBnClickedFindButton()
{
	if (Validate(true))
	{
		ShowControls(true);
		UpdateStrings();
		UpdateCBStatus();
	}
	else
	{
		m_editSO.SetFocus();
	}
}

void CDlgMaterialStatus::ShowControls(bool bFound)
{
	if (bFound)
	{
		this->m_btnFind.ShowWindow(SW_HIDE);
		this->m_butDone.ShowWindow(SW_SHOW);
		this->m_editSO.EnableWindow(FALSE);
		this->m_editYardage.EnableWindow(FALSE);
		this->m_stCustName.ShowWindow(SW_SHOW);
		this->m_stPOStatic.ShowWindow(SW_SHOW);
		this->m_stCustNameField.ShowWindow(SW_SHOW);
		this->m_stPOField.ShowWindow(SW_SHOW);
		this->m_stStatus.ShowWindow(SW_SHOW);
		this->m_comboStatus.ShowWindow(SW_SHOW);
		m_statMaterialDescription.ShowWindow(SW_SHOW) ;

		m_comboStatus.EnableWindow() ;
	}
	else
	{
		this->m_btnFind.ShowWindow(SW_SHOW);
		this->m_butDone.ShowWindow(SW_HIDE);
		this->m_editSO.EnableWindow(TRUE);
		this->m_editYardage.EnableWindow(TRUE);
		this->m_stCustName.ShowWindow(SW_HIDE);
		this->m_stPOStatic.ShowWindow(SW_HIDE);
		this->m_stCustNameField.ShowWindow(SW_HIDE);
		this->m_stPOField.ShowWindow(SW_HIDE);
		this->m_stStatus.ShowWindow(SW_HIDE);
		this->m_comboStatus.ShowWindow(SW_HIDE);
		m_statMaterialDescription.ShowWindow(SW_HIDE) ;
	}

	this->m_btnReset.ShowWindow(SW_HIDE);
	this->m_butOk.ShowWindow(SW_HIDE);
}