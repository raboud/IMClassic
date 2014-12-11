/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgChargeBack.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgChargeBack.h"
#include "DataExchange.h"
#include "vwPOMarketDivision.h"
#include "SetVwChargeBacksTaken.h"
#include "SetSettings.h"
#include "DlgSelectCustomer.h"

// CDlgChargeBack dialog

IMPLEMENT_DYNAMIC(CDlgChargeBack, CDialog)

CDlgChargeBack::CDlgChargeBack(CWnd* pParent /*=NULL*/, long lCBId /* =-1*/)
	: CDialog(CDlgChargeBack::IDD, pParent)
	, m_setCB(&g_dbFlooring)
{
	if (lCBId == -1)
	{
		m_setCB.m_strFilter = "[ChargeBackID] = -1";
		m_setCB.Open() ;
		m_setCB.AddNew() ;
		m_setCB.m_ApprovalNumber = 0 ;
		m_setCB.m_Approved = FALSE ;
		m_setCB.m_IssueDate = COleDateTime(COleDateTime::GetCurrentTime().GetYear(), COleDateTime::GetCurrentTime().GetMonth(), COleDateTime::GetCurrentTime().GetDay(), 0, 0, 0) ;
		m_bNew = true ;
	}
	else
	{
		m_setCB.m_strFilter.Format("[ChargeBackID] = '%d'", lCBId) ;
		m_setCB.Open() ;
		m_setCB.Edit() ;
		m_bNew = false ;
	}
}

CDlgChargeBack::~CDlgChargeBack()
{
	m_setCB.Close() ;
}

void CDlgChargeBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PO_NUMBER, m_editPONumber);
	DDX_Control(pDX, IDC_CHARGEBACK_MARKET, m_editMarket);
	DDX_Control(pDX, IDC_CHARGEBACK_DIVISION, m_editDivision);
	DDX_Control(pDX, IDC_CHARGEBACK_CUSTNAME, m_editCusterName);

	DDX_Control(pDX, IDC_CHARGEBACK_NUMBER, m_editCBNumber);
	DDX_Control(pDX, IDC_CHARGEBACK_AMOUNT, m_editCBAmount);
	DDX_Control(pDX, IDC_INSTALLER_AMOUNT, m_editInstallerAmount);
	DDX_Control(pDX, IDC_CHARGEBACK_SUBCONTRACTOR, m_comboSubContractor);
	DDX_Control(pDX, IDC_LIST1, m_listChecks);

	DDX_Text(pDX, IDC_CHARGEBACK_AMOUNT, m_setCB.m_Amount);
	DDX_ComboBoxData(pDX, IDC_CHARGEBACK_SUBCONTRACTOR, m_setCB.m_SubcontractorID);
	DDX_Text(pDX, IDC_INSTALLER_AMOUNT, m_setCB.m_AmountToSub);
	DDX_Text(pDX, IDC_CHARGEBACK_NUMBER, m_setCB.m_Number);
	DDX_Text(pDX, IDC_CHARGEBACK_CUSTNAME, m_setCB.m_Name);
    DDX_Text(pDX, IDC_CHARGEBACK_COMMENTS, m_setCB.m_Reason);
	DDX_Text(pDX, IDC_PO_NUMBER, m_setCB.m_OriginalPO);
	DDX_Check(pDX, IDC_APPROVED, m_setCB.m_Approved);
	DDX_Text(pDX, IDC_APPROVAL_NUMBER, m_setCB.m_ApprovalNumber);
}


BEGIN_MESSAGE_MAP(CDlgChargeBack, CDialog)
//	ON_EN_CHANGE(IDC_PO_NUMBER, OnEnChangePoNumber)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_APPROVED, OnBnClickedApproved)
	ON_EN_KILLFOCUS(IDC_PO_NUMBER, OnEnKillfocusPoNumber)
	ON_EN_CHANGE(IDC_CHARGEBACK_NUMBER, OnEnChangeChargebackNumber)
	ON_EN_CHANGE(IDC_APPROVAL_NUMBER, OnEnChangeApprovalNumber)
	ON_EN_CHANGE(IDC_CHARGEBACK_AMOUNT, OnEnChangeChargebackAmount)
	ON_EN_CHANGE(IDC_INSTALLER_AMOUNT, OnEnChangeInstallerAmount)
	ON_CBN_SELCHANGE(IDC_CHARGEBACK_SUBCONTRACTOR, OnCbnSelchangeChargebackSubcontractor)
	ON_EN_CHANGE(IDC_CHARGEBACK_COMMENTS, OnEnChangeChargebackComments)
	ON_EN_KILLFOCUS(IDC_CHARGEBACK_NUMBER, OnEnKillfocusChargebackNumber)
END_MESSAGE_MAP()


// CDlgChargeBack message handlers

void CDlgChargeBack::OnEnChangePoNumber()
{
}

BOOL CDlgChargeBack::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_APPROVAL_NUMBER)->EnableWindow(FALSE) ;
	m_editPONumber.SetLimitText(CGlobals::iMAX_PO_NUMBER) ;
	m_editCBNumber.SetLimitText(50);

	if (!m_bNew)
	{
		CvwPOMarketDivision setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter.Format("OrderID = '%d'", m_setCB.m_OrderID) ;
		setOrders.Open() ;

		if (setOrders.IsEOF())
		{
				m_editPONumber.SetWindowText(m_setCB.m_OriginalPO) ;
				m_editMarket.SetWindowText("N/A");
				m_editDivision.SetWindowText("N/A");
				m_editCusterName.SetWindowText(m_setCB.m_Name);
		}
		else
		{
			m_editPONumber.SetWindowText(setOrders.m_PurchaseOrderNumber) ;
			m_editMarket.SetWindowText(setOrders.m_Market);
			m_editDivision.SetWindowText(setOrders.m_Division);
			CString strName = setOrders.m_LastName + ", " + setOrders.m_FirstName ;
			m_editCusterName.SetWindowText(strName);
			m_OriginalStoreNumber = setOrders.m_StoreNumber ;
		}

		setOrders.Close() ;

		CSetVwChargeBacksTaken setTaken(&g_dbFlooring) ;
		setTaken.m_strFilter.Format("[ChargeBackID] = '%d'", m_setCB.m_ChargeBackID) ;
		setTaken.Open() ;
		if (!setTaken.IsEOF())
		{
			CRect rect ;
			m_listChecks.GetClientRect(rect) ;
			m_listChecks.SetTabStops(rect.Width() / 3) ;

			while (!setTaken.IsEOF())
			{
				CString strCheck ;
				strCheck.Format("%s - CK# %7s - $%7.2f", setTaken.m_CheckDate.Format("%m/%d/%Y"), setTaken.m_CheckNumber, setTaken.m_Amount) ;
				m_listChecks.AddString(strCheck) ;
				setTaken.MoveNext() ;
			}
		}
		else
		{
			m_listChecks.AddString("None") ;
		}
	}
	else
	{
		ASSERT(m_OriginalOriginalPO.GetLength() > 0);
		ASSERT(m_OriginalStoreNumber.GetLength() > 0);
		m_editPONumber.SetWindowText(m_OriginalOriginalPO) ;
		OnEnKillfocusPoNumber();
	}

	m_OriginalAmount = m_setCB.m_Amount;
	m_OriginalSubcontractorID = m_setCB.m_SubcontractorID;
	m_OriginalAmountToSub = m_setCB.m_AmountToSub;
	m_OriginalNumber = m_setCB.m_Number;
	m_OriginalName = m_setCB.m_Name;
	m_OriginalReason = m_setCB.m_Reason;
	m_OriginalIssueDate = m_setCB.m_IssueDate;
	m_OriginalOriginalPO = m_setCB.m_OriginalPO;
	m_OriginalOrderID = m_setCB.m_OrderID ;
	m_OriginalCostAdjustment = m_setCB.m_CostAdjustment;
	m_OriginalApproved = m_setCB.m_Approved;
	m_OriginalApprovalNumber = m_setCB.m_ApprovalNumber ;

	EnableOk() ;

//	OnBnClickedApproved() ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChargeBack::OnBnClickedOk()
{
	try
	{
		UpdateData() ;
		// check for unique Chargeback number
		bool bOK = CheckChargebackNumber() ;
		// is PO number valid
		if (bOK) bOK = CheckPONumber() ;
		// is Installer selected.
		if (bOK) bOK = CheckInstaller() ;
		// dollar amounts for the the installer and overall amount
		if (bOK) bOK = CheckDollarAmount() ;
		// verify comments field is filled in
		if (bOK) bOK = CheckCommentField() ;
		// if approved and if new assign approval number
		// if approved and not new and not previously approved assign 
		if (bOK) AssignApprovalNumber() ;

		// store the approval number for later use after the update statement
		int iLastValidApprovalNumber = m_setCB.m_ApprovalNumber;

		// this resets our recordset to the first record...
		if (bOK) bOK = (m_setCB.Update() == TRUE);
		
		if (bOK)
		{
			CButton* pbtn = (CButton*) GetDlgItem(IDC_APPROVED);
			if ((pbtn->GetCheck()) && (m_OriginalApproved == FALSE) && (m_OriginalApprovalNumber == 0))
			{
				CSetSettings setSettings(&g_dbFlooring) ;
				setSettings.SetSetting("NextApprovalNumber", (iLastValidApprovalNumber + 1) );
			}
		}

		if (bOK) OnOK();
	}
	catch(CDBException* e)
	{
		MessageBox(e->m_strError, "Error!");
		e->Delete();
	}
}

void CDlgChargeBack::OnBnClickedCancel()
{
	if (GetDirty())
	{
		if (IDNO == MessageBox("Changes have been made.  Are you sure you want to quit?", "Data Changed", MB_YESNO))
		{
			return  ;
		}
	}
	m_setCB.CancelUpdate() ;
	OnCancel();
}

void CDlgChargeBack::OnBnClickedApproved()
{
	UpdateData() ;
	AssignApprovalNumber() ;
	UpdateData(FALSE) ;
	EnableOk() ;
}

bool CDlgChargeBack::GetDirty()
{
	UpdateData(TRUE) ;
	bool bReturn =  
	((m_OriginalAmount != m_setCB.m_Amount) ||
	(m_OriginalSubcontractorID != m_setCB.m_SubcontractorID) ||
	(m_OriginalAmountToSub != m_setCB.m_AmountToSub) ||
	(m_OriginalNumber != m_setCB.m_Number) ||
	(m_OriginalName != m_setCB.m_Name) ||
	(m_OriginalReason != m_setCB.m_Reason) ||
	(m_OriginalIssueDate != m_setCB.m_IssueDate) ||
	(m_OriginalOriginalPO != m_setCB.m_OriginalPO) ||
	(m_OriginalOrderID != m_setCB.m_OrderID) ||
	(m_OriginalCostAdjustment != m_setCB.m_CostAdjustment) ||
	(m_OriginalApproved != m_setCB.m_Approved) ||
	(m_OriginalApprovalNumber != m_setCB.m_ApprovalNumber)) ;
	return bReturn ;
}

void CDlgChargeBack::EnableOk()
{
	this->GetDlgItem(IDOK)->EnableWindow(GetDirty()) ;
}


void CDlgChargeBack::OnEnKillfocusPoNumber()
{
	CheckPONumber() ;
	EnableOk() ;
}

void CDlgChargeBack::OnEnChangeChargebackNumber()
{
	EnableOk() ;
}

void CDlgChargeBack::OnEnChangeApprovalNumber()
{
	EnableOk() ;
}

void CDlgChargeBack::OnEnChangeChargebackAmount()
{
	EnableOk() ;
}

void CDlgChargeBack::OnEnChangeInstallerAmount()
{
	EnableOk() ;
}

void CDlgChargeBack::OnCbnSelchangeChargebackSubcontractor()
{
	EnableOk() ;
}

void CDlgChargeBack::OnEnChangeChargebackComments()
{
	EnableOk() ;
}

bool CDlgChargeBack::CheckChargebackNumber()
{
	bool bOK = false;

	CSetChargeBacks	setCB(&g_dbFlooring) ;
	CString strCBNumber;
	m_editCBNumber.GetWindowText(strCBNumber);

	if (strCBNumber.GetLength() == 0)
	{	
		MessageBox("Chargeback number must be entered.", "Error") ;
	}
	else
	{
		if (m_bNew)
		{
			setCB.m_strFilter.Format("[Number] = '%s'", m_setCB.m_Number) ;
		}
		else
		{
			setCB.m_strFilter.Format("[Number] = '%s' AND [ChargeBackID] <> '%d'", m_setCB.m_Number, m_setCB.m_ChargeBackID) ;
		}
		setCB.Open() ;
		bOK = (setCB.IsEOF() == TRUE) ;
		if (!bOK)
		{
			MessageBox("Chargeback number has already been entered.", "Error") ;
		}
		setCB.Close() ;
	}

	return (bOK) ;
}

bool CDlgChargeBack::CheckPONumber()
{
	bool bOK = false;
	CString strPO ;
	CString strStoreNumber = m_OriginalStoreNumber;
    m_editPONumber.GetWindowText(strPO) ;

	// if the PO number has changed, need to reverify the customer data...
	bool bContinue = true;
	if ((strPO != m_OriginalOriginalPO) || (strStoreNumber == ""))
	{
		CDlgSelectCustomer dlgCustomer;
		int iNumRecords = dlgCustomer.SetPONumber(strPO, strStoreNumber);

		if ( iNumRecords > 1 )
		{
			if ( dlgCustomer.DoModal() != IDOK )
			{
				bContinue = false;
			}
		}
		else if ( iNumRecords == 0 )
		{
			MessageBox("PO Number Not Found!", "Error") ;
			bContinue = false;
		}

		if (bContinue)
		{
			strStoreNumber = dlgCustomer.GetStoreNumber();
		}
		m_OriginalOriginalPO = strPO;
	}

	if (bContinue)
	{
		CvwPOMarketDivision setOrders(&g_dbFlooring) ;
		setOrders.m_strFilter.Format("PurchaseOrderNumber = '%s' AND StoreNumber = '%s'", strPO, strStoreNumber) ;
		setOrders.Open() ;
	    
		if (setOrders.IsEOF())
		{
			MessageBox("PO Number does not exist", "Error") ;
		}
		else
		{
			m_editMarket.SetWindowText(setOrders.m_Market);
			m_editDivision.SetWindowText(setOrders.m_Division);
			CString strName = setOrders.m_LastName + ", " + setOrders.m_FirstName ;
			m_editCusterName.SetWindowText(strName);
			m_setCB.m_OrderID = setOrders.m_OrderID ;
			EnableOk() ;
		}
		bOK = (setOrders.IsEOF() == FALSE) ;

		setOrders.Close() ;
	}
	return bOK ;
}

bool CDlgChargeBack::CheckInstaller()
{
	bool bOK = (m_comboSubContractor.GetCurSel() != LB_ERR) ;
	if (!bOK)
	{
		MessageBox("You must select an installer", "Error") ;
	}
	return bOK ;
}


void CDlgChargeBack::OnEnKillfocusChargebackNumber()
{
	UpdateData() ;
	CheckChargebackNumber() ;
}

void CDlgChargeBack::AssignApprovalNumber()
{
	if ((m_setCB.m_Approved == TRUE) && (m_OriginalApproved == FALSE) && (m_OriginalApprovalNumber == 0))
	{
		CSetSettings setSettings(&g_dbFlooring) ;
		m_setCB.m_ApprovalNumber = setSettings.GetValueLong("NextApprovalNumber");
	}
}

bool CDlgChargeBack::CheckDollarAmount()
{
	double dAmount = atof(m_setCB.m_Amount) ;

	bool bOK = (dAmount >= 0.0) ;
	if (!bOK)
	{
		MessageBox("You must enter an amount for the chargeback.", "Error") ;
	}
	return bOK ;
}

bool CDlgChargeBack::CheckCommentField()
{
	bool bOK = (m_setCB.m_Reason.GetLength() > 0);
	if (!bOK)
	{
		MessageBox("You must enter the reason for the chargeback into the Comments field.");
	}

	return bOK;
}

void CDlgChargeBack::SetOriginalPO(CString strOriginalPO)
{
	m_OriginalOriginalPO = strOriginalPO;
}

void CDlgChargeBack::SetStoreNumber(CString strStoreNumber)
{
	m_OriginalStoreNumber = strStoreNumber;
}