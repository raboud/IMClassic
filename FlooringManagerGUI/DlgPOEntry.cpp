// DlgPOEntry.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgPOEntry.h"
#include "dlgpoentry.h"
#include "dlgpoentry.h"
#include "SetOrders.h"
#include "SetCustomer.h"
#include "SetStores.h"
#include "DlgPOEntry.h"
#include "SetOrderAndCustomer.h"
#include "SetMaterialType.h"
#include ".\dlgpoentry.h"

// CDlgPOEntry dialog

IMPLEMENT_DYNAMIC(CDlgPOEntry, CDialog)
CDlgPOEntry::CDlgPOEntry(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPOEntry::IDD, pParent)
	, m_lOrderID(-1)
	, m_bAdding(true)
	, m_lCustomerID(-1)
	, m_strPONumber(_T(""))
	, m_strPONumberInit(_T(""))
	, m_strPOType(_T(""))
	, m_strPOTypeInit(_T(""))
	, m_strOrigPONumber(_T(""))
	, m_strOrigPONumberInit(_T(""))
	, m_strStoreNumber(_T(""))
	, m_bPriceUpdateNeeded(false)
	, m_strMaterialTypeShortName(_T(""))
{
}

CDlgPOEntry::~CDlgPOEntry()
{
}

void CDlgPOEntry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POENTRY_PONUMBEREDIT, m_editPONumber);
	DDX_Control(pDX, IDC_POENTRY_POTYPECOMBO, m_comboPOType);
	DDX_Control(pDX, IDC_POENTRY_ORIGPOCOMBO, m_comboOrigPO);
	DDX_Text(pDX, IDC_POENTRY_PONUMBEREDIT, m_strPONumber);
	DDX_CBString(pDX, IDC_POENTRY_POTYPECOMBO, m_strPOType);
	DDX_CBString(pDX, IDC_POENTRY_ORIGPOCOMBO, m_strOrigPONumber);
	DDX_CBString(pDX, IDC_POENTRY_STORENUMBER, m_strStoreNumber);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_POENTRY_STORENUMBER, m_cbStoreNumber);
}


BEGIN_MESSAGE_MAP(CDlgPOEntry, CDialog)
	ON_CBN_SELCHANGE(IDC_POENTRY_POTYPECOMBO, OnCbnSelChangePOTypeCombo)
	ON_EN_KILLFOCUS(IDC_POENTRY_PONUMBEREDIT, OnEnKillfocusPoentryPonumberedit)
	ON_CBN_SELCHANGE(IDC_POENTRY_ORIGPOCOMBO, OnCbnSelchangePOEntryOrigPOCombo)
	ON_CBN_SELCHANGE(IDC_POENTRY_STORENUMBER, OnCbnSelchangePoentryStorenumber)
END_MESSAGE_MAP()


// CDlgPOEntry message handlers

BOOL CDlgPOEntry::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_editPONumber.SetLimitText(8);
	
	if (CGlobals::HasPermission("CanEnterRegularPO")) m_comboPOType.AddString("Regular");
	if (CGlobals::HasPermission("CanEnterInvoicePO")) m_comboPOType.AddString("Invoice");
	if (CGlobals::HasPermission("CanEnterWarrantyPO")) m_comboPOType.AddString("Warranty");

	if ( (m_bAdding) || (m_strPOType != "Warranty") )
	{
		m_comboOrigPO.EnableWindow(FALSE);
	}
	
	if (m_strPOType == "")
	{
		m_comboPOType.SetCurSel(-1);
	}

	if (m_strStoreNumber == "")
	{
		m_cbStoreNumber.SetCurSel(-1);
	}

	UpdateStoreNumberCombo();

	if (m_strPOType == "Warranty")
	{
		FillOrigPOCombo();
	}

	EnableOK();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgPOEntry::OnOK()
{
	UpdateData();
	if (DataValidated())
	{
		CDialog::OnOK();
	}
}

void CDlgPOEntry::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgPOEntry::OnEnKillfocusPoentryPonumberedit()
{
	UpdateData();
	UpdateStoreNumberCombo();

	EnableOK();
}

void CDlgPOEntry::OnCbnSelChangePOTypeCombo()
{
	UpdateData();

	if (m_strPOType == "Warranty")
	{
		m_comboOrigPO.EnableWindow();
		FillOrigPOCombo();
	}
	else
	{
		m_comboOrigPO.ResetContent();
		m_comboOrigPO.EnableWindow(FALSE);
		m_strOrigPONumber = "";
	}

	EnableOK();

}

bool CDlgPOEntry::DataValidated(void)
{
	bool bOK = false;

	if (m_bAdding)
	{
		bOK = ValidateDataForAdd();
	}
	else
	{
		bOK = ValidateDataForEdit();
	}
	return bOK;
}

void CDlgPOEntry::FillOrigPOCombo(void)
{
	ASSERT(m_lCustomerID != -1);
	int iIndex = 0;
	int iStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(m_strStoreNumber);
	m_comboOrigPO.ResetContent();
	CSetOrderAndCustomer setOrders(&g_dbFlooring);
	if (m_strMaterialTypeShortName.GetLength() == 0)
	{
		setOrders.m_strFilter.Format("[OrderID] <> %d AND [CustomerID] = %d AND [Invoice] = 0 AND [StoreTypeID] = %d", m_lOrderID, m_lCustomerID, iStoreTypeID);
	}
	else
	{
		setOrders.m_strFilter.Format("[OrderId] <> %d AND [CustomerId] = %d AND [Invoice] = 0 AND [ShortName] = '%s'", m_lOrderID, m_lCustomerID, m_strMaterialTypeShortName);
	}
	setOrders.Open();
	while (!setOrders.IsEOF())
	{	
		iIndex = m_comboOrigPO.AddString(setOrders.m_PurchaseOrderNumber.Trim());
		m_comboOrigPO.SetItemData(iIndex, setOrders.m_OrderID);
		setOrders.MoveNext();
	}
	setOrders.Close();

	m_comboOrigPO.SetCurSel(-1);
}


bool CDlgPOEntry::ValidateDataForAdd(void)
{
	bool bValid = true;

	int iLength = m_strPONumber.GetLength();

	if (iLength > 0)
	{
		if (iLength == 4)
		{
			if ((m_strPOType == "Warranty") || (m_strPOType == "Invoice"))
			{
				if (m_strStoreNumber == "")
				{
					MessageBox("The PO Number is not a valid Store Number.", "PO Number Validation Error") ;
					bValid = false;
				}

				if (bValid)
				{
					if (m_strPOType == "Warranty")
					{
						CString strOrigPO = "";

						if (m_strOrigPONumber.GetLength() == 0)
						{
							MessageBox("Please select a Warranty PO.", "PO Entry Error");
							bValid = false;
						}
					}
				}
			}
			else
			{
				MessageBox("A 4-digit PO must either be a Warranty or Invoice type PO.", "PO Entry Error");
				bValid = false;
			}
		}
		else if (iLength == 8)
		{
			if (m_strPONumber.GetAt(2) != '4')
			{
				MessageBox("The third digit must be a 4.", "PO Entry Error");
				bValid = false;
			}

			if (bValid && (m_strPOType == "Invoice"))
			{
				MessageBox("An Invoice PO must match a 4-digit store number.", "PO Entry Error");
				bValid = false;
			}
			else if (bValid)
			{
				if (m_strPOType == "Warranty")
				{
					if (m_strOrigPONumber.GetLength() == 0)
					{
						MessageBox("Please select a Warranty PO.", "PO Entry Error");
						bValid = false;
					}
				}

				if (bValid)
				{
					// make sure new PO is not already entered in
					if ((m_strStoreNumber == "") && (m_cbStoreNumber.GetCount() > 0))
					{
						MessageBox("Please select a Store Number.", "PO Number Validation Error") ;
						bValid = false;
					}
					else if (m_cbStoreNumber.GetCount() == 0)
					{
						MessageBox("Could not validate the PO number.", "PO Number Validation Error") ;
						bValid = false;
					}
					else
					{
						if (CGlobals::POInUse(m_strPONumber, m_strStoreNumber))
						{
							CString strTemp;
							strTemp.Format("Duplicate PO Number:  Store %s has already issued this PO.", m_strStoreNumber);
							MessageBox(strTemp, "PO Number Error", MB_OK) ; 
							bValid = false ;
						}
					}
				}
			}
		}
		else
		{
			MessageBox("A PO number must either be 4-digits or 8-digits.", "PO Entry Error");
			bValid = false;
		}
	}
	else
	{
		MessageBox("Please enter a PO Number.", "PO Number Error");
		bValid = false;
	}
	return bValid;
}

bool CDlgPOEntry::ValidateDataForEdit(void)
{
	bool bValid = true;
	CString strNewPONumber;

	// Validate the PO Number if it changed
	if (m_strPONumber != m_strPONumberInit)
	{
		if ((m_strPONumber.GetLength() != 8) && (m_strPONumber.GetLength() != 4))
		{
			MessageBox("The PO Number is not valid.", "PO Number Validation Error") ;
			bValid = false;
		}
		else
		{
			// PO Number changed
			if (m_strStoreNumber == "")
			{
				MessageBox("Could not validate the PO number.", "PO Number Validation Error") ;
				bValid = false;
			}
			else
			{
				// make sure they are not changing the store type
				if ( StoreTypeDifference( m_strStoreNumber ) )
				{
					MessageBox("The new PO Number is for a different store type than the old PO Number.  This is an invalid operation.", "PO Number Validation Error") ;
					bValid = false;
				}
				else if ( MarketDifference( m_strStoreNumber ))
				{
					// if the market changed, we might need to refresh the prices
					m_bPriceUpdateNeeded = true;
				}

				// make sure it's not in use by another order
				if (m_strPONumber.GetLength() == 8)
				{
					int iOrderID = -1;
					if ( CGlobals::POInUse(m_strPONumber, m_strStoreNumber, iOrderID))
					{
						if (iOrderID != m_lOrderID)
						{
							CString strTemp;
							strTemp.Format("Duplicate PO Number:  Store %s has already issued this PO.", m_strStoreNumber);
							MessageBox(strTemp, "PO Number Error", MB_OK) ; 
							bValid = false ;
						}
					}
				}
			}
		}
	}

	// validate POType
	if (bValid)
	{
		if (m_strPONumber.GetLength() == 4)
		{
			if (m_strPOType == "Regular")
			{
				MessageBox("A 4-digit PO must either be a Warranty or Invoice type PO.", "PO Entry Error");
				bValid = false;
			}
		}
		else
		{
			if (m_strPOType == "Invoice")
			{
				MessageBox("An Invoice PO must match a 4-digit store number.", "PO Entry Error");
				bValid = false;
			}
		}

		if ( bValid && (m_strPOType == "Warranty"))
		{
			if (m_strOrigPONumber.GetLength() == 0)
			{
				MessageBox("Please select a Warranty PO.", "PO Entry Error");
				bValid = false;
			}
		}
	}

	return bValid;
}

bool CDlgPOEntry::StoreTypeDifference(CString strNewStoreNumber)
{
	bool bDifference = false;

	CString strStoreNumber = CGlobals::StoreNumberFromOrderID(m_lOrderID);
	int iStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(strStoreNumber);
	int iNewStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(strNewStoreNumber);

	bDifference = (iStoreTypeID != iNewStoreTypeID);
	
	return bDifference;
}

bool CDlgPOEntry::MarketDifference(CString strNewStoreNumber)
{
	bool bDifference = false;

	CString strStoreNumber = CGlobals::StoreNumberFromOrderID(m_lOrderID);
	int iMarketID = CGlobals::MarketIDFromStoreNumber(strStoreNumber);
	int iNewMarketID = CGlobals::MarketIDFromStoreNumber(strNewStoreNumber);

	bDifference = (iMarketID != iNewMarketID);
	
	return bDifference;
}

void CDlgPOEntry::InitVars(void)
{
	if (m_bAdding)
	{
		ASSERT(m_lCustomerID != -1);
		if (m_strPOType == "")
		{
			m_strPOType = "Regular";
		}
	}
	else
	{
		ASSERT(m_lOrderID != -1);
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter.Format("[OrderID] = %d", m_lOrderID);
		setOrders.Open();
		if (!setOrders.IsEOF())
		{
			m_strPONumber = setOrders.m_PurchaseOrderNumber.Trim();
			m_strPONumberInit = m_strPONumber;
			if ((!setOrders.m_Warrenty) && (!setOrders.m_Invoice))
			{
				m_strPOType = "Regular";
			}
			else if ((setOrders.m_Warrenty) && (!setOrders.m_Invoice))
			{
				m_strPOType = "Warranty";
			}
			else if ((setOrders.m_Invoice) && (!setOrders.m_Warrenty))
			{
				m_strPOType = "Invoice";
			}
			else
			{
				m_strPOType = "";
			}
		}
		setOrders.Close();
	}
}

CString CDlgPOEntry::GetPOType()
{
	return m_strPOType;
}

CString CDlgPOEntry::GetPONumber()
{
	return m_strPONumber;
}

CString CDlgPOEntry::GetOrigPONumber()
{
	return m_strOrigPONumber;
}

CString CDlgPOEntry::GetStoreNumber(void)
{
	return m_strStoreNumber;
}

bool CDlgPOEntry::SetOrderID(long lOrderID)
{
	bool bOK = false;
	CSetOrderAndCustomer setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("[OrderID] = %d", lOrderID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		m_lOrderID = lOrderID;
		m_lCustomerID = setOrders.m_CustomerID;
		m_strStoreNumber = CGlobals::StoreNumberFromOrderID(lOrderID);
		m_strPONumber = setOrders.m_PurchaseOrderNumber.Trim();
		m_strOrigPONumber = setOrders.m_OriginalPO.Trim();
		m_strMaterialTypeShortName = setOrders.m_ShortName;
		if ((!setOrders.m_Warrenty) && (!setOrders.m_Invoice))
		{
			m_strPOType = "Regular";
		}
		else if ((setOrders.m_Warrenty) && (!setOrders.m_Invoice))
		{
			m_strPOType = "Warranty";
		}
		else if ((setOrders.m_Invoice) && (!setOrders.m_Warrenty))
		{
			m_strPOType = "Invoice";
		}
		m_bAdding = false;
		bOK = true;
	}
	setOrders.Close();

	return bOK;
}

bool CDlgPOEntry::SetCustomerID(long lCustomerID)
{
	bool bOK = false;
	CSetCustomer setCustomer(&g_dbFlooring);
	setCustomer.m_strFilter.Format("[CustomerID] = %d", lCustomerID);
	setCustomer.Open();
	if (!setCustomer.IsEOF())
	{
		m_lCustomerID = lCustomerID;
		bOK = true;
	}
	setCustomer.Close();

	InitVars();

	return bOK;
}

void CDlgPOEntry::SetPONumber(CString strPONumber)
{
	m_strPONumber = strPONumber.Trim();
}

void CDlgPOEntry::SetOrigPONumber(CString strOrigPONumber)
{
	m_strOrigPONumber = strOrigPONumber.Trim();
}

void CDlgPOEntry::SetPOType(CString strPOType)
{
	m_strPOType = strPOType;
}

void CDlgPOEntry::UpdateStoreNumberCombo(void)
{
	m_cbStoreNumber.ResetContent();
	CSetStores setStores(&g_dbFlooring) ;
	if (m_strPONumber.GetLength() == 8)
	{
		setStores.m_strFilter = "[StoreNumber] LIKE '__" + m_strPONumber.Left(2) + "'" ;
	}
	else if (m_strPONumber.GetLength() == 4)
	{
		setStores.m_strFilter = "[StoreNumber] = '" + m_strPONumber + "'";
	}
	setStores.Open() ;
	while (!setStores.IsEOF())
	{
		m_cbStoreNumber.AddString(setStores.m_StoreNumber.Trim());
		setStores.MoveNext();
	}

	if (m_strStoreNumber.GetLength() > 0)
	{
		m_cbStoreNumber.SelectString(-1, m_strStoreNumber);
	}
	else if ( m_cbStoreNumber.GetCount() == 1 )
	{
		m_cbStoreNumber.SetCurSel(0);
		m_cbStoreNumber.GetLBText(0,m_strStoreNumber);
	}
}

void CDlgPOEntry::EnableOK(void)
{
	bool bEnable = true;
	if ( m_strPONumber.GetLength() == 0)
	{
		bEnable = false;
	}
	else if ( m_strPOType == "Warranty")
	{
		CString strTemp = "";
		int iIndex = m_comboOrigPO.GetCurSel();
		if (iIndex != -1)
		{
            m_comboOrigPO.GetLBText(iIndex, strTemp);
		}
		
		if (strTemp.GetLength() == 0)
		{
			bEnable = false;
		}
	}
	int Length = m_comboPOType.GetLBTextLen(m_comboPOType.GetCurSel());
	if (Length <= 0)
	{
		bEnable = false;
	}

	m_btnOK.EnableWindow(bEnable == true);
}

void CDlgPOEntry::SetStoreNumber(CString strStoreNumber)
{
	m_strStoreNumber = strStoreNumber;
}

void CDlgPOEntry::SetMaterialTypeShortName(CString strShortName)
{
	m_strMaterialTypeShortName = strShortName;
}

CString CDlgPOEntry::GetMaterialTypeShortName(void)
{
	return m_strMaterialTypeShortName;
}

void CDlgPOEntry::OnCbnSelchangePOEntryOrigPOCombo()
{
	UpdateData();
	if (m_bAdding)
	{
		UpdateMaterialTypeShortName();
	}

	EnableOK();
}

void CDlgPOEntry::UpdateMaterialTypeShortName(void)
{
	int iOrderID = m_comboOrigPO.GetItemData(m_comboOrigPO.GetCurSel());
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("[OrderID] = %d", iOrderID);
	setOrders.Open();
	if (!setOrders.IsEOF())
	{
		int iMaterialTypeID = setOrders.m_MaterialTypeID;
		CSetMaterialType setMaterialType(&g_dbFlooring);
		setMaterialType.m_strFilter.Format("[MaterialTypeID] = %d", iMaterialTypeID);
		setMaterialType.Open();
		if (!setMaterialType.IsEOF())
		{
			m_strMaterialTypeShortName = setMaterialType.m_ShortName.Trim();
		}
		setMaterialType.Close();
	}
	setOrders.Close();
}

void CDlgPOEntry::OnCbnSelchangePoentryStorenumber()
{
	UpdateData();
}

bool CDlgPOEntry::IsPriceUpdateNeeded(void)
{
	return m_bPriceUpdateNeeded;
}
