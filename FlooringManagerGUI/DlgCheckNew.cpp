/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgCheckNew.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgCheckNew.h"
#include "SetChecks.h"
#include ".\dlgchecknew.h"


// CDlgCheckNew dialog

IMPLEMENT_DYNAMIC(CDlgCheckNew, CDialog)
CDlgCheckNew::CDlgCheckNew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckNew::IDD, pParent)
	, m_CheckDate(COleDateTime::GetCurrentTime())
	, m_strCheckNumber(_T(""))
	, m_strCheckAmount(_T(""))
	, m_iCheckID(-1)
	, m_strOriginalCheckNumber(_T(""))
	, m_strOriginalCheckAmount(_T(""))
	, m_lOriginalVendorID(-1)
{

	m_OriginalCheckDate = m_OriginalCheckDate.GetCurrentTime() ;
}

CDlgCheckNew::~CDlgCheckNew()
{
}

void CDlgCheckNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_CHECK_DATE, m_CheckDate);
	DDX_Text(pDX, IDC_CHECK_NUMBER, m_strCheckNumber);
	DDX_Control(pDX, IDC_CHECK_AMOUNT, m_fleditAmount);
	DDX_Text(pDX, IDC_CHECK_AMOUNT, m_strCheckAmount);
	DDX_Control(pDX, IDC_CHECK_NUMBER, m_editNumber);
	DDX_Control(pDX, IDOK, m_butOK);
	DDX_Control(pDX, IDC_CHECK_VENDOR, m_comboVendor);
}


BEGIN_MESSAGE_MAP(CDlgCheckNew, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_CHECK_NUMBER, OnEnChangeCheckNumber)
	ON_EN_CHANGE(IDC_CHECK_AMOUNT, OnEnChangeCheckAmount)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CHECK_DATE, OnDtnDatetimechangeCheckDate)
	ON_NOTIFY(DTN_CLOSEUP, IDC_CHECK_DATE, OnDtnCloseupCheckDate)
	ON_CBN_SELCHANGE(IDC_CHECK_VENDOR, OnCbnSelchangeCheckVendor)
END_MESSAGE_MAP()


// CDlgCheckNew message handlers

void CDlgCheckNew::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CDlgCheckNew::OnOK()
{
	this->UpdateData() ;
	if (!m_strCheckNumber.IsEmpty() && !m_strCheckAmount.IsEmpty() && (m_comboVendor.GetCurSel() != LB_ERR) )
	{
		if (m_iCheckID == -1)
		{
			CSetChecks setCheck(&g_dbFlooring) ;
			// no duplicate checks with the same VendorID
			setCheck.m_strFilter.Format("CheckNumber = '%s' AND VendorID = %d", m_strCheckNumber, m_comboVendor.GetSelectedVendorID()) ;
			setCheck.Open() ;
			if (setCheck.IsEOF())
			{
				try
				{
					setCheck.AddNew() ;
					setCheck.m_CheckNumber = m_strCheckNumber ;
					setCheck.m_CheckDate = COleDateTime(m_CheckDate.GetYear(), m_CheckDate.GetMonth(), m_CheckDate.GetDay(), 0, 0, 0) ; ;
					setCheck.m_Amount = m_strCheckAmount;
					setCheck.m_VendorID = m_comboVendor.GetSelectedVendorID();
					setCheck.Update() ;
					setCheck.Requery() ;
					m_iCheckID = setCheck.m_CheckID ;
				}
				catch(...)
				{
					return ;
				}
			}
			else
			{
				MessageBox("Check already exists. Hit cancel to exit.", "Duplicate Check") ;
				return ;
			}
		}
		else
		{
			CSetChecks setCheck(&g_dbFlooring) ;
			setCheck.m_strFilter.Format("CheckID <> '%d' AND CheckNumber = '%s' AND VendorID = %d", m_iCheckID, m_strCheckNumber, m_comboVendor.GetSelectedVendorID()) ;
			setCheck.Open() ;
			if (setCheck.IsEOF())
			{
				try
				{
					setCheck.m_strFilter.Format("CheckID = '%d'", m_iCheckID) ;
					setCheck.Requery() ;
					setCheck.Edit() ;
					setCheck.m_CheckNumber = m_strCheckNumber ;
					setCheck.m_CheckDate = COleDateTime(m_CheckDate.GetYear(), m_CheckDate.GetMonth(), m_CheckDate.GetDay(), 0, 0, 0) ; ;
					setCheck.m_Amount = m_strCheckAmount;
					setCheck.m_VendorID = m_comboVendor.GetSelectedVendorID();
					setCheck.Update() ;
				}
				catch(...)
				{
					return ;
				}
			}
			else
			{
				MessageBox("Check number already exists. Hit cancel to exit.", "Non-Existent Check") ;
				return ;
			}
		}
		CDialog::OnOK();
	}
}

BOOL CDlgCheckNew::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_iCheckID != -1)
	{
		CSetChecks setCheck(&g_dbFlooring) ;
		setCheck.m_strFilter.Format("CheckID = '%d'", m_iCheckID) ;
		setCheck.Open() ;
		if (!setCheck.IsEOF())
		{
			m_strOriginalCheckNumber = m_strCheckNumber = setCheck.m_CheckNumber ;
			m_OriginalCheckDate.SetDate(setCheck.m_CheckDate.GetYear(), setCheck.m_CheckDate.GetMonth(), setCheck.m_CheckDate.GetDay()) ;
			m_CheckDate.SetDate(setCheck.m_CheckDate.GetYear(), setCheck.m_CheckDate.GetMonth(), setCheck.m_CheckDate.GetDay()) ;
			m_strOriginalCheckAmount = m_strCheckAmount = setCheck.m_Amount ;
			SetVendorCombo(setCheck.m_VendorID);
			m_lOriginalVendorID = setCheck.m_VendorID;
			UpdateData(FALSE) ;
		}
		this->SetWindowText("Edit Check") ;
	}
	m_editNumber.SetLimitText(7) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCheckNew::OnEnChangeCheckNumber()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CheckDirty() ;
	// TODO:  Add your control notification handler code here
}

void CDlgCheckNew::OnEnChangeCheckAmount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CheckDirty() ;
	// TODO:  Add your control notification handler code here
}

void CDlgCheckNew::CheckDirty(void)
{
	UpdateData(TRUE) ;
	if ((m_strCheckNumber.Compare(m_strOriginalCheckNumber) || 
		 m_strCheckAmount.Compare(m_strOriginalCheckAmount) || 
		 m_lOriginalVendorID != m_comboVendor.GetSelectedVendorID() ||
		 m_OriginalCheckDate != m_CheckDate) && 
		(m_strCheckNumber.GetLength() > 0) &&
		(m_strCheckAmount.GetLength() > 0) && (m_comboVendor.GetCurSel() != LB_ERR))
	{
		m_butOK.EnableWindow(TRUE) ;
	}
	else
	{
		m_butOK.EnableWindow(FALSE) ;
	}
}

void CDlgCheckNew::OnDtnDatetimechangeCheckDate(NMHDR * /* pNMHDR */, LRESULT *pResult)
{
//	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	CheckDirty() ;
	*pResult = 0;
}

void CDlgCheckNew::OnDtnCloseupCheckDate(NMHDR * /* pNMHDR */, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CheckDirty() ;
	*pResult = 0;
}

void CDlgCheckNew::SetVendorCombo(int iVendorID)
{
	int iNumVendors = m_comboVendor.GetCount();
	for (int iIndex = 0; iIndex < iNumVendors; iIndex++)
	{
		int iID = m_comboVendor.GetItemData(iIndex);
		if (iID == iVendorID)
		{
			m_comboVendor.SetCurSel(iIndex);
			break;
		}
	}
}

void CDlgCheckNew::OnCbnSelchangeCheckVendor()
{
	CheckDirty();
}
