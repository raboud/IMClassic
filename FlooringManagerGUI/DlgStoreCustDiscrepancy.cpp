// DlgStoreCustDiscrepancy.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgStoreCustDiscrepancy.h"
#include ".\dlgstorecustdiscrepancy.h"


// CDlgStoreCustDiscrepancy dialog

IMPLEMENT_DYNAMIC(CDlgStoreCustDiscrepancy, CDialog)
CDlgStoreCustDiscrepancy::CDlgStoreCustDiscrepancy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStoreCustDiscrepancy::IDD, pParent)
{
	m_bHandled = false;
	m_ExtraData = "";
}

CDlgStoreCustDiscrepancy::~CDlgStoreCustDiscrepancy()
{
}

void CDlgStoreCustDiscrepancy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STORECURRENTADDRESS, m_editCurrentAddress);
	DDX_Control(pDX, IDC_STORECURRENTEDIT, m_editCurrent);
	DDX_Control(pDX, IDC_STORENEWADDRESS, m_editNewAddress);
	DDX_Control(pDX, IDC_STORENEWEDIT, m_editNew);
	DDX_Control(pDX, IDC_STATIC_CURRENT, m_staticCurrent);
	DDX_Control(pDX, IDC_STATIC_NEW, m_staticNew);
	DDX_Control(pDX, IDC_DISC_EXTRAINFO, m_staticExtraInfo);
}


BEGIN_MESSAGE_MAP(CDlgStoreCustDiscrepancy, CDialog)
	ON_EN_CHANGE(IDC_STORECURRENTADDRESS, OnEnChangeStorecurrentaddress)
	ON_BN_CLICKED(ID_REJECTCHANGES, OnBnClickedRejectchanges)
END_MESSAGE_MAP()


// CDlgStoreCustDiscrepancy message handlers

void CDlgStoreCustDiscrepancy::OnEnChangeStorecurrentaddress()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

BOOL CDlgStoreCustDiscrepancy::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_editCurrent.SetReadOnly();
	m_editCurrentAddress.SetReadOnly();

	m_staticExtraInfo.SetWindowText(m_ExtraData);

	if (m_DiscType == 1)
	{
		SetWindowText("Store Discrepancy");
	}
	else
	{
		SetWindowText("Customer Discrepancy");
	}

	if (m_DiscSubType == 1)  // Address
	{
		m_editCurrent.ShowWindow(SW_HIDE);
		m_editNew.ShowWindow(SW_HIDE);
		m_editCurrentAddress.SetWindowText(m_CurrentData);
		m_editNewAddress.SetWindowText(m_NewData);
		m_staticCurrent.SetWindowText("Current Address");
		m_staticNew.SetWindowText("New Address");
	}
	else
	{
		m_editCurrentAddress.ShowWindow(SW_HIDE);
		m_editNewAddress.ShowWindow(SW_HIDE);
		m_editCurrent.SetWindowText(m_CurrentData);
		m_editNew.SetWindowText(m_NewData);
		CString strCurrentCaption;
		CString strNewCaption;
		switch(m_DiscSubType)
		{
			case 3: 
				{
					strCurrentCaption = "Current City";
					strNewCaption = "New City";
				}
				break;
			case 4: 
				{
					strCurrentCaption = "Current State";
					strNewCaption = "New State";
				}
				break;
			case 5: 
				{
					strCurrentCaption = "Current Zip";
					strNewCaption = "New Zip";
				}
				break;
			case 6: 
				{
					strCurrentCaption = "Current First Name";
					strNewCaption = "New First Name";
				}
				break;
			case 7: 
				{
					strCurrentCaption = "Current Last Name";
					strNewCaption = "New Last Name";
				}
				break;
			case 8: 
				{
					strCurrentCaption = "Current Home Phone";
					strNewCaption = "New Home Phone";
					m_editCurrent.SetMask(_T("(###)###-####")) ;
					m_editNew.SetMask(_T("(###)###-####")) ;
					m_editCurrent.SetWindowText(m_CurrentData);
					m_editNew.SetWindowText(m_NewData);
				}
				break;
			case 9: 
				{
					strCurrentCaption = "Current Work Phone";
					strNewCaption = "New Work Phone";
					m_editCurrent.SetMask(_T("(###)###-#### EXT #####")) ;
					m_editNew.SetMask(_T("(###)###-#### EXT #####")) ;
					m_CurrentData.Replace(" ", "");
					m_editCurrent.SetInputData(m_CurrentData);
					m_NewData.Replace(" ", "");
					m_editNew.SetInputData(m_NewData);
				}
				break;
			case 10: 
				{
					strCurrentCaption = "Current Store Fax";
					strNewCaption = "New Store Fax";
				}
				break;
			case 11: 
				{
					strCurrentCaption = "Current Store Phone";
					strNewCaption = "New Store Phone";
				}
				break;
			default:
				{
					strCurrentCaption = "Current Data";
					strNewCaption = "New Data";
				}
				break;
		}
		m_staticCurrent.SetWindowText(strCurrentCaption);
		m_staticNew.SetWindowText(strNewCaption);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStoreCustDiscrepancy::OnOK()
{
	CString strAddressData = "";
	CString strEditData = "";
	m_editNewAddress.GetWindowText(strAddressData);
	m_editNew.GetWindowText(strEditData);

	m_bHandled = true;

	// we want to take the new data and update the database...
	if (m_DiscType == 1)  // STORE
	{
		CString strSQL = "";
		switch(m_DiscSubType)
		{
			case 1:  // ADDRESS
				{
					strSQL.Format("UPDATE Stores SET BILLINGADDRESS = '%s' WHERE StoreID = %d", strAddressData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 2:  // ADDRESS
				{
					strSQL.Format("UPDATE Stores SET BILLINGADDRESS = '%s' WHERE StoreID = %d", strAddressData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 3:  // CITY
				{
					strSQL.Format("UPDATE Stores SET CITY = '%s' WHERE StoreID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 4:  // STATE
				{
					strSQL.Format("UPDATE Stores SET STATE = '%s' WHERE StoreID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 5:  // ZIP
				{
					strSQL.Format("UPDATE Stores SET ZIPCODE = '%s' WHERE StoreID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 10:  // STORE FAX
				{
					strSQL.Format("UPDATE Stores SET FAXNUMBER = '%s' WHERE StoreID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 11:  // STORE PHONE
				{
					strSQL.Format("UPDATE Stores SET STOREPHONENUMBER = '%s' WHERE StoreID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			default:
				{
					m_bHandled = false;
				}
				break;
		}
	}
	else if (m_DiscType == 2) // CUSTOMER
	{
		CString strSQL = "";
		switch (m_DiscSubType)
		{
			case 1:  // ADDRESS1
				{
					strSQL.Format("UPDATE Customers SET ADDRESS = '%s' WHERE CustomerID = %d", strAddressData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 2:  // ADDRESS2
				{
					strSQL.Format("UPDATE Customers SET ADDRESS = '%s' WHERE CustomerID = %d", strAddressData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 3:  // CITY
				{
					strSQL.Format("UPDATE Customers SET CITY = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 4:  // STATE
				{
					strSQL.Format("UPDATE Customers SET STATE = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 5:  // ZIP
				{
					strSQL.Format("UPDATE Customers SET ZIPCODE = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 6:  // FIRSTNAME
				{
					strSQL.Format("UPDATE Customers SET FIRSTNAME = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 7:  // LASTNAME
				{
					strSQL.Format("UPDATE Customers SET LASTNAME = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 8:  // HOME PHONE
				{
					strSQL.Format("UPDATE Customers SET PHONENUMBER = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			case 9:  // WORK PHONE
				{
					strSQL.Format("UPDATE Customers SET WORKNUMBER = '%s' WHERE CustomerID = %d", strEditData, m_DetailID);
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				break;
			default:
				{
					m_bHandled = false;
				}
				break;
		}
	}
	CDialog::OnOK();
}

void CDlgStoreCustDiscrepancy::SetDiscType(int DiscType)
{
	m_DiscType = DiscType;
}

void CDlgStoreCustDiscrepancy::SetSubType(int DiscSubType)
{
	m_DiscSubType = DiscSubType;
}

void CDlgStoreCustDiscrepancy::SetDetailID(long DetailID)
{
	m_DetailID = DetailID;
}

void CDlgStoreCustDiscrepancy::SetCurrentData(CString CurrentData)
{
	m_CurrentData = CurrentData;
}

void CDlgStoreCustDiscrepancy::SetNewData(CString NewData)
{
	m_NewData = NewData;
}
void CDlgStoreCustDiscrepancy::OnBnClickedRejectchanges()
{
	m_bHandled = true;
	PostMessage(WM_COMMAND, IDCANCEL);
}

