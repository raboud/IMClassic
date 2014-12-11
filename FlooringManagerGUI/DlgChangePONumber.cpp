// DlgChangePONumber.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgChangePONumber.h"
#include "SetOrders.h"
#include "SetStores.h"


// CDlgChangePONumber dialog

IMPLEMENT_DYNAMIC(CDlgChangePONumber, CDialog)
CDlgChangePONumber::CDlgChangePONumber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangePONumber::IDD, pParent)
	, m_strMessage(_T(""))
	, m_strOldPONumber(_T(""))
	, m_strNewPONumber(_T(""))
	, m_strErrorMessage(_T(""))
	, m_iOrderID(0)
	, m_strOldStoreNumber(_T(""))
	, m_bChangingMarkets(false)
{
}

CDlgChangePONumber::~CDlgChangePONumber()
{
}

void CDlgChangePONumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHANGEPO_DIALOG_MESSAGE, m_strMessage);
	DDX_Control(pDX, IDC_CHANGEPO_DIALOG_POEDIT, m_editCorrectPO);
	DDX_Text(pDX, IDC_CHANGEPO_DIALOG_POEDIT, m_strNewPONumber);
	DDV_MaxChars(pDX, m_strNewPONumber, 8);
}


BEGIN_MESSAGE_MAP(CDlgChangePONumber, CDialog)
END_MESSAGE_MAP()


// CDlgChangePONumber message handlers

void CDlgChangePONumber::OnOK()
{
	if ( !ValidateAndChangePO() )
	{
		MessageBox(m_strErrorMessage, "Error");
		return;
	}
	CDialog::OnOK();
}

BOOL CDlgChangePONumber::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT(m_iOrderID != 0);
	ASSERT(m_strOldPONumber != "");

	m_strMessage.Format("This dialog allows you to modify a PO Number that has been incorrectly entered.\nThe current PO Number is: %s", m_strOldPONumber);
	m_strNewPONumber = m_strOldPONumber;
	UpdateData(FALSE);
	m_editCorrectPO.SetSel(0, m_strOldPONumber.GetLength());
	m_editCorrectPO.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgChangePONumber::ValidateAndChangePO()
{
	bool bValid = false;
	UpdateData();

	CSetStores setStore(&g_dbFlooring) ;
	CSetOrders setOrders(&g_dbFlooring) ;

	CString strOldStoreNumber = "";
	CString strNewStoreNumber = "";
	
	int iNewStoreID = -1;

	int iNewPOLength = m_strNewPONumber.GetLength();

	// make sure new PO Number has correct length, format
	if ( ((iNewPOLength == 8) && (m_strNewPONumber.GetAt(2) == '4')) ||
		 (iNewPOLength == 4) ) 
	{
		if (iNewPOLength == 4)
		{
			// verify this is a warranty or invoice type PO
			if (!IsWarrantyOrInvoice())
			{
				m_strErrorMessage = "To change this to a store number PO, you must first edit the PO and set either the Warranty or Invoice checkboxes.";
				return false;
			}
		}

		// get the old store number
		strOldStoreNumber = CGlobals::StoreNumberFromOrderID(m_iOrderID);
		if (strOldStoreNumber == "")
		{
			m_strErrorMessage = "The Store Number for the current order could not be determined.";
			return false;
		}

		// get the new store number
		strNewStoreNumber = CGlobals::POtoStoreNumber(m_strNewPONumber);
		if (strNewStoreNumber == "")
		{
			if (iNewPOLength == 4)
			{
                m_strErrorMessage = "The new PO Number is not a valid store number.";
			}
			else
			{
				m_strErrorMessage = "Could not determine the new store number from the new PO number.";
			}
			return false;
		}

		if ( (iNewPOLength != 4) && CGlobals::POInUse(m_strNewPONumber, strNewStoreNumber) )
		{
			m_strErrorMessage.Format("The PO Number you entered is already in use by store %s.", strNewStoreNumber);
			return false;
		}

		bValid = true;
	}
	else
	{
		m_strErrorMessage = "The PO Number is not valid.";
	}

	// see if we are changing store types, set flag is market is changing
	if (strOldStoreNumber != strNewStoreNumber)
	{
		// changing stores, need to check store types
		int iOldStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(strOldStoreNumber);
		int iNewStoreTypeID = CGlobals::StoreTypeIDFromStoreNumber(strNewStoreNumber);

		if (iOldStoreTypeID != iNewStoreTypeID)
		{
			m_strErrorMessage = "The PO Number change involves changing the store type.  \nSince this could involve invalid line items and pricing \nchanges, the change cannot be made.  You will need to \ndelete the PO and re-enter it.";
			return false;
		}

		// since we are changing stores, see if we are changing markets too
		int iMarketID1 = CGlobals::MarketIDFromStoreNumber(strOldStoreNumber);
		int iMarketID2 = CGlobals::MarketIDFromStoreNumber(strNewStoreNumber);
		m_bChangingMarkets = (iMarketID1 != iMarketID2);
		
	}

	if (bValid)
	{
		iNewStoreID = CGlobals::StoreIDFromStoreNumber(strNewStoreNumber);
		if (iNewStoreID == -1)
		{
			m_strErrorMessage = "The Store ID could not be determined when updating the database.";
			return false;
		}

		setOrders.m_strFilter.Format("[OrderID] = %d", m_iOrderID);
		setOrders.Open();
		if (!setOrders.IsEOF())
		{
			setOrders.Edit();
			setOrders.m_PurchaseOrderNumber = m_strNewPONumber;
			setOrders.m_StoreID = iNewStoreID;
			setOrders.Update();
		}
		else
		{
			m_strErrorMessage = "The current order could not be found in the database.";
			return false;
		}
		setOrders.Close();

		if (m_bChangingMarkets)
		{
			if ( !CGlobals::RefreshPrices(m_iOrderID) )
			{
				m_strErrorMessage = "An error occurred while refreshing the prices.";
				return false;
			}
		}
	}

	return bValid;
}

void CDlgChangePONumber::SetOrderID(int iOrderID)
{
	m_iOrderID = iOrderID;
}

void CDlgChangePONumber::SetCurrentPONumber(CString strPONumber)
{
	m_strOldPONumber = strPONumber.TrimRight();
}

bool CDlgChangePONumber::IsWarrantyOrInvoice()
{
	bool bIsWarrantyOrInvoice = false;
	
	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("[OrderID] = %d", m_iOrderID);
	setOrders.Open();
	ASSERT(setOrders.IsEOF() == FALSE);
	if (!setOrders.IsEOF())
	{
		bIsWarrantyOrInvoice = (setOrders.m_Warrenty || setOrders.m_Invoice);
	}
	setOrders.Close();

	return bIsWarrantyOrInvoice;
}