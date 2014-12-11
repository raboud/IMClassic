// DlgStore.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgStore.h"
#include "DataExchange.h"
#include ".\dlgstore.h"
#include "SetStoreType.h"
#include "Dib.h"


// CDlgStore dialog

IMPLEMENT_DYNAMIC(CDlgStore, CDialog)
CDlgStore::CDlgStore(bool bAdding, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStore::IDD, pParent),
	m_bAdding(bAdding)
{
	m_pSet = new CSetStores(&g_dbFlooring);
	m_pSet->Open();
	m_iStoreID = -1;
	m_bIncludeInStatusReportAllStores = FALSE;
}

CDlgStore::~CDlgStore()
{
	if (m_pSet)
	{
		if (m_pSet->IsOpen())
		{
			m_pSet->Close();
		}
		delete m_pSet;
	}
}

void CDlgStore::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STORES_STORENUMBER, m_editStoreNumber);
	DDX_Control(pDX, IDC_STORES_STORETYPE, m_comboStoreType);
	DDX_Control(pDX, IDC_STORES_MARKET, m_cbStoreMarket);
    DDX_Control(pDX, IDC_DEPOT, m_bmpDepot);
	DDX_Control(pDX, IDC_STORES_ADDRESS, m_editStoreAddress);
	DDX_Control(pDX, IDC_CITY, m_editStoreCity);
	DDX_Control(pDX, IDC_STATE, m_editStoreState);
	DDX_Control(pDX, IDC_ZIP, m_editZip);
	DDX_Control(pDX, IDC_STORE_PHONE_NUMBER, m_editStorePhoneNumber);
	DDX_Control(pDX, IDC_FAX_NUMBER, m_editFaxNumber);
	DDX_Control(pDX, IDC_STORES_NOTES, m_editStoreNotes);
	DDX_Control(pDX, IDC_STORES_ACTIVE_CHECK, m_btnActive);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STORE_NICKNAME, m_editStoreNickName);

	DDX_FieldText(pDX, IDC_STORES_STORENUMBER, m_pSet->m_StoreNumber, m_pSet);
	DDX_ComboBoxData(pDX, IDC_STORES_STORETYPE, m_pSet->m_StoreTypeID);
	DDX_ComboBoxData(pDX, IDC_STORES_MARKET, m_pSet->m_MarketId);
	DDX_FieldText(pDX, IDC_STORES_ADDRESS, m_pSet->m_BillingAddress, m_pSet);
	DDX_FieldText(pDX, IDC_STORE_NICKNAME, m_pSet->m_StoreNickName, m_pSet);
	DDX_FieldText(pDX, IDC_CITY, m_pSet->m_City, m_pSet);
	DDX_FieldText(pDX, IDC_STATE, m_pSet->m_State, m_pSet);
	DDX_FieldText(pDX, IDC_ZIP, m_pSet->m_ZipCode, m_pSet);
	DDX_FieldText(pDX, IDC_STORE_PHONE_NUMBER, m_pSet->m_StorePhoneNumber, m_pSet);
	DDX_FieldText(pDX, IDC_FAX_NUMBER, m_pSet->m_FaxNumber, m_pSet);
	DDX_FieldText(pDX, IDC_STORES_NOTES, m_pSet->m_Notes, m_pSet);
	if (!m_bAdding)
	{
		DDX_FieldCheck(pDX, IDC_STORES_ACTIVE_CHECK, m_pSet->m_Active, m_pSet);
	}
	
	DDX_FieldCheck(pDX, IDC_INCLUDEINSTATUSREPORTALLSTORES, m_pSet->m_IncludeInStatusReportAll, m_pSet);

	DDV_MaxChars(pDX, m_pSet->m_BillingAddress, 255);
	DDV_MaxChars(pDX, m_pSet->m_State, 2);
	DDV_TELEPHONE(pDX, m_pSet->m_StorePhoneNumber, m_pSet, false) ;
	DDV_TELEPHONE(pDX, m_pSet->m_DirectPhoneNumber, m_pSet, false) ;
	DDV_TELEPHONE(pDX, m_pSet->m_FaxNumber, m_pSet, false) ;
}


BEGIN_MESSAGE_MAP(CDlgStore, CDialog)
END_MESSAGE_MAP()


// CDlgStore message handlers

void CDlgStore::SetStoreID(int iStoreID)
{
	m_iStoreID = iStoreID;
}
BOOL CDlgStore::OnInitDialog()
{
	// make sure we've set the subcontractor id if we are editing
	ASSERT( (!m_bAdding && m_iStoreID != -1) || (m_bAdding));
	CDialog::OnInitDialog();

	m_gridStoreContacts.AttachGrid(this, IDC_CONTACT_GRID_PLACEHOLDER);
	m_gridStoreContacts.SetStoreID(m_iStoreID);
	
	if (!m_bAdding)
	{
		m_pSet->m_strFilter.Format("[StoreID] = %d", m_iStoreID);
		m_pSet->Requery();
		m_pSet->Edit();
	}
	else
	{
		m_pSet->AddNew();
		m_btnActive.SetCheck(BST_CHECKED);
	}

	m_editZip.SetMask(_T("#####-####"));
	m_editStorePhoneNumber.SetMask(_T("(###) ###-####"));
	m_editFaxNumber.SetMask(_T("(###) ###-####"));

	m_editStoreNumber.SetLimitText(5);
	m_editStoreAddress.SetLimitText(255);
	m_editStoreCity.SetLimitText(50);
	m_editStoreState.SetLimitText(2);
	m_editStoreNotes.SetLimitText(1024);

	UpdateData(FALSE);

	CSetStoreType setType(&g_dbFlooring) ;
	setType.m_strFilter.Format("[StoreTypeID] = '%d'", m_pSet->m_StoreTypeID) ;
	setType.Open() ;

	// TODO: change this so the database only has the name of the bitmap, not the drive letter
	// use the Settings table to locate the shared drive - that way if it ever changes, no
	// code changes needed.
	m_bmp.Load(setType.m_ImageName) ;
	m_bmpDepot.SetBitmap(m_bmp) ;
	setType.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStore::OnOK()
{
	CString strError = "";
	UpdateData();
	
	if (ValidateData(strError))
	{
		CDialog::OnOK();
		CString strStoreNumber = m_pSet->m_StoreNumber;
		
		if ( m_bAdding )
		{
			int iCheck = m_btnActive.GetCheck();
			if (iCheck == BST_CHECKED)
			{
				m_pSet->m_Active = 1;
			}
			else
			{
				m_pSet->m_Active = 0;
			}
		}
		
		m_pSet->Update();
		m_pSet->m_strFilter.Format("StoreNumber = '%s'", strStoreNumber);
		m_pSet->Requery();

		if (!m_pSet->IsEOF())
		{
			// we have to call this in case we just added a new store...the false keeps the grid from
			// reinitializing the data...
			m_gridStoreContacts.SetStoreID(m_pSet->m_StoreID, false);
			try
			{
				m_gridStoreContacts.UpdateRecordSet();
			}
			catch (CDBException* pE)
			{
				pE->Delete() ;
			}
		}
	}
	else
	{
		MessageBox(strError, "Error!");
	}
}

void CDlgStore::OnCancel()
{
	m_pSet->CancelUpdate();
	
	CDialog::OnCancel();
}

void CDlgStore::ShowInstSalesMgrFields(bool bShow)
{
	int iShow = SW_SHOW;
	if (!bShow)
	{
		iShow = SW_HIDE;
	}
    
	GetDlgItem(IDC_STORES_LABEL1)->ShowWindow(iShow);
	GetDlgItem(IDC_STORES_LABEL2)->ShowWindow(iShow);
	GetDlgItem(IDC_STORES_LABEL3)->ShowWindow(iShow);
	GetDlgItem(IDC_STORES_LABEL4)->ShowWindow(iShow);
	GetDlgItem(IDC_STORES_INSTSALESMGR_FIRST_NAME)->ShowWindow(iShow);
	GetDlgItem(IDC_STORES_INSTSALESMGR_LAST_NAME)->ShowWindow(iShow);
	GetDlgItem(IDC_STORES_INSTSALESMGR_PHONE_NUMBER)->ShowWindow(iShow);
}	

bool CDlgStore::ValidateData(CString& strError)
{
	bool bValid = true;

	if (m_bAdding)
	{
		// make sure store number is not duplicate
		CString strStore;
		m_editStoreNumber.GetWindowText(strStore);
		if (strStore.GetLength() > 0)
		{
			CSetStores setStores(&g_dbFlooring);
			setStores.m_strFilter.Format("[StoreNumber] = '%s'", strStore);
			setStores.Open();
			if (!setStores.IsEOF())
			{
				// error
				bValid = false;
				strError = "This store number already exists in the database!";
			}
			setStores.Close();
		}
		else
		{
			bValid = false;
			strError = "You must enter a store number.";
		}
	}

	return bValid;
}

bool CDlgStore::CancelButtonHasFocus()
{
	CWnd* pwnd = GetFocus();
	CWnd* pCancelBtn = GetDlgItem(IDCANCEL);
	if (pwnd->m_hWnd == pCancelBtn->m_hWnd)
	{
		TRACE("Cancel Button has focus...");
		return true;
	}

	return false;
}