/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgFind.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgFind.h"
#include ".\dlgfind.h"
#include "setstores.h"
#include "setorders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFind dialog


CDlgFind::CDlgFind(EnFIND_TYPE enType, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFind::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFind)
	m_strNumber = _T("");
	m_enType = enType;

	m_strMask = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFind)
	DDX_Text(pDX, IDC_MASKEDNUMBER, m_strNumber);
	DDX_Text(pDX, IDC_STORECOMBO, m_strStoreNumber);
	DDX_Control(pDX, IDC_STORECOMBO, m_cbStoreNumber);
	DDX_Control(pDX, IDC_MASKEDNUMBER, m_editMaskedNumber);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_ST_STORE, m_stStoreText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFind, CDialog)
	//{{AFX_MSG_MAP(CDlgFind)
	//}}AFX_MSG_MAP
	ON_NOTIFY(OXMEN_VALIDATE, IDC_MASKEDNUMBER, OnEnKillFocusMaskedNumber)
	ON_CBN_SELCHANGE(IDC_STORECOMBO, OnCbnSelchangeStorecombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFind message handlers

void CDlgFind::SetCaption(CString strCaption)
{
	m_strTitle = strCaption ;
}

BOOL CDlgFind::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_cbStoreNumber.ShowWindow(SW_HIDE);
	m_stStoreText.ShowWindow(SW_HIDE);
	switch(m_enType)
	{
		case EnFIND_TYPE_ORDERID :
			{
				m_strTitle = "Find By Internal Order Number";
				m_iMaxChars = CGlobals::iMAX_ORDERID_DIGITS;
				break;
			}
		case EnFIND_TYPE_CUSTOMERID :
			{
				m_strTitle = "Find By Internal Customer Number";
				m_iMaxChars = CGlobals::iMAX_CUSTID_DIGITS;
				break;
			}
		case EnFIND_TYPE_PO :
			{
				m_strTitle = "Find By HD PO Number";
				m_iMaxChars = CGlobals::iMAX_PO_NUMBER;
				m_btnOK.EnableWindow(FALSE);
				m_cbStoreNumber.ShowWindow(SW_NORMAL);
				m_stStoreText.ShowWindow(SW_NORMAL);
				m_editMaskedNumber.SetFocus();
				break;
			}
		case EnFIND_TYPE_SO :
			{
				m_strTitle = "Find By SO Number";
				m_iMaxChars = CGlobals::iMAX_SO_NUMBER;
				m_btnOK.EnableWindow(FALSE);
				m_cbStoreNumber.ShowWindow(SW_NORMAL);
				m_stStoreText.ShowWindow(SW_NORMAL);
				break;
			}
		case EnFIND_TYPE_TEXT :
			{
				m_strTitle = "Find By Searching Notes";
				m_iMaxChars = 255;
				m_strMask = "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
				break;
			}
		case EnFIND_TYPE_HOME_PHONE :
			{
				m_strTitle = "Find By Home Phone Number";
				m_strMask = "(###)###-####";
				break;
			}
		case EnFIND_TYPE_WORK_PHONE :
			{
				m_strTitle = "Find By Work Phone Number";
				m_strMask = "(###)###-####";
				break;
			}
		default:
			{
			}
	}

	SetWindowText(m_strTitle) ;

	if (m_iMaxChars > 0)
	{
		m_editMaskedNumber.SetLimitText(m_iMaxChars);
	}

	if (m_strMask.GetLength() > 0)
	{
		m_editMaskedNumber.SetMask(m_strMask);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFind::SetMask(CString strMask)
{
	m_strMask = strMask;
}

void CDlgFind::UpdateStoreNumberCombo(CString strPONumber)
{
	m_cbStoreNumber.ResetContent();
	CSetStores setStores(&g_dbFlooring) ;
	setStores.m_strFilter = "[StoreNumber] LIKE '__" + strPONumber.Left(2) + "'" ;
	setStores.Open() ;

	// populate the list box with the store numbers
	while (!setStores.IsEOF())
	{
		int iIndex = m_cbStoreNumber.AddString(setStores.m_StoreNumber.Trim());
		m_cbStoreNumber.SetItemData(iIndex, setStores.m_StoreID);
		setStores.MoveNext();
	}

	if ( m_cbStoreNumber.GetCount() == 1 )
	{
		m_cbStoreNumber.SetCurSel(0);
		m_btnOK.EnableWindow();
	}
	else if (m_cbStoreNumber.GetCount() > 1)
	{
		m_cbStoreNumber.SetCurSel(-1);
		if (m_enType == EnFIND_TYPE_PO)
		{
			CSetOrders setOrders(&g_dbFlooring);
			setOrders.m_strFilter = "[PurchaseOrderNumber] = '" + strPONumber + "' AND Deleted = 0";
			setOrders.Open();
			if (!setOrders.IsEOF())
			{
				setStores.m_strFilter.Format("StoreID = %d", setOrders.m_StoreID);
				setStores.Requery();
				if (!setStores.IsEOF())
				{
					m_cbStoreNumber.SetCurSel(m_cbStoreNumber.FindStringExact(-1, setStores.m_StoreNumber));
					m_btnOK.EnableWindow();
				}
			}
		}
	}
}
void CDlgFind::OnEnKillFocusMaskedNumber(NMHDR* pNMHDR, LRESULT* /* pResult */)
{
	if ((m_enType == EnFIND_TYPE_PO) || (m_enType == EnFIND_TYPE_SO))
	{
		((MENMHDR*)pNMHDR)->bDefaultValidation = FALSE;
		UpdateData();
		m_btnOK.EnableWindow(FALSE);

		bool bValid = ValidatePO();
		if (bValid)
		{
			UpdateStoreNumberCombo(m_strNumber);
		}
		else
		{
			m_cbStoreNumber.ResetContent();
		}

		CWnd* pWnd = GetFocus();
		if (pWnd != NULL)
		{
			if (pWnd->m_hWnd != GetDlgItem(IDCANCEL)->m_hWnd)
			{
				if (!bValid)
				{
					m_editMaskedNumber.SetFocus();
				}
			}
		}

	}
}

bool CDlgFind::ValidatePO()
{
	bool bValid = false;
	if (m_enType == EnFIND_TYPE_PO)
	{
		if ((m_strNumber.GetLength() == 8) && (m_strNumber.GetAt(2) == '4'))
		{
			bValid = true;
		}
	}
	else if (m_enType == EnFIND_TYPE_SO)
	{
		if ((m_strNumber.GetLength() == 8) && (m_strNumber.GetAt(2) == '5'))
		{
			bValid = true;
		}
	}
	else
	{
		bValid = true;
	}

	return bValid;
}

void CDlgFind::OnCbnSelchangeStorecombo()
{
	UpdateData();
	if (ValidatePO())
	{
		m_btnOK.EnableWindow();
	}
}


void CDlgFind::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData();

	CDialog::OnOK();
}
