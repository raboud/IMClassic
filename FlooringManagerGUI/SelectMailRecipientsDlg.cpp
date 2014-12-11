// SelectMailRecipientsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "SelectMailRecipientsDlg.h"
#include "SetViewStoreContacts.h"
#include "SetStoreContacts.h"

// CSelectMailRecipientsDlg dialog

IMPLEMENT_DYNAMIC(CSelectMailRecipientsDlg, CDialog)
CSelectMailRecipientsDlg::CSelectMailRecipientsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectMailRecipientsDlg::IDD, pParent), m_setEmployees(&g_dbFlooring)
{
	m_bIncludeStoreManagement = false;
	m_iStoreID = -1;
}

CSelectMailRecipientsDlg::~CSelectMailRecipientsDlg()
{
}

void CSelectMailRecipientsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIL_EMPLOYEES_LIST, m_listEmployees);
	DDX_Control(pDX, IDC_MAIL_RECIPIENTS_LIST, m_listRecipients);
	DDX_Control(pDX, IDC_MAIL_ADD_BUTTON, m_btnAdd);
	DDX_Control(pDX, IDC_MAIL_ADD_ALL_BUTTON, m_btnAddAll);
	DDX_Control(pDX, IDC_MAIL_REMOVE_BUTTON, m_btnRemove);
	DDX_Control(pDX, IDC_MAIL_REMOVE_ALL_BUTTON, m_btnRemoveAll);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CSelectMailRecipientsDlg, CDialog)
	ON_BN_CLICKED(IDC_MAIL_ADD_BUTTON, OnBnClickedMailAddButton)
	ON_BN_CLICKED(IDC_MAIL_ADD_ALL_BUTTON, OnBnClickedMailAddAllButton)
	ON_BN_CLICKED(IDC_MAIL_REMOVE_BUTTON, OnBnClickedMailRemoveButton)
	ON_BN_CLICKED(IDC_MAIL_REMOVE_ALL_BUTTON, OnBnClickedMailRemoveAllButton)
	ON_LBN_SELCHANGE(IDC_MAIL_EMPLOYEES_LIST, OnLbnSelchangeMailEmployeesList)
	ON_LBN_SELCHANGE(IDC_MAIL_RECIPIENTS_LIST, OnLbnSelchangeMailRecipientsList)
END_MESSAGE_MAP()


// CSelectMailRecipientsDlg message handlers

BOOL CSelectMailRecipientsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int iIndex;

	if (m_bIncludeStoreManagement)
	{
		CSetViewStoreContacts setStoreContacts(&g_dbFlooring);
		setStoreContacts.m_strFilter.Format("StoreID = %d AND DepartmentName = 'Management' AND EmailAddress IS NOT NULL", m_iStoreID);
		setStoreContacts.Open();
		while(!setStoreContacts.IsEOF())
		{
			// Here we add the store management contacts for the relevant store.  Prefix with "SM: " so later we can tell they are not an
			// employee.  That is why it's OK to use the StoreContactsID as the Item Data...
			CString strName;
			strName.Format("SM: %s,%s (%s)", setStoreContacts.m_LastName, setStoreContacts.m_FirstName, setStoreContacts.m_Title);
			iIndex = m_listEmployees.AddString(strName);
			m_listEmployees.SetItemData(iIndex, setStoreContacts.m_StoreContactsID);
			setStoreContacts.MoveNext();
		}
	}

	m_setEmployees.m_strFilter = "[ReceiveCallNotes] = 1 AND SMTPEmail IS NOT NULL";
	m_setEmployees.m_strSort = "LastName";
	m_setEmployees.Open();

	CString strName;
	while (!m_setEmployees.IsEOF())
	{
		BOOL bLNameNull = m_setEmployees.IsFieldNull(&m_setEmployees.m_LastName) || m_setEmployees.m_LastName.GetLength() == 0;
		BOOL bFNameNull = m_setEmployees.IsFieldNull(&m_setEmployees.m_FirstName) || m_setEmployees.m_FirstName.GetLength() == 0;

		if ( !bFNameNull && !bLNameNull )
		{
			strName = m_setEmployees.m_LastName + ", " + m_setEmployees.m_FirstName;
		}
		else if ( bLNameNull && !bFNameNull )
		{
			strName = m_setEmployees.m_FirstName;
		}
		else if ( bFNameNull && !bLNameNull )
		{
            strName = m_setEmployees.m_LastName;
		}
		else
		{
			TRACE("First and Last name fields were both NULL.\n");
			break;
		}
		int iIndex = m_listEmployees.AddString(strName);
		m_listEmployees.SetItemData(iIndex, m_setEmployees.m_ID);

		m_setEmployees.MoveNext();
	}

	m_astrRecipientEmailAddresses.RemoveAll();

	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectMailRecipientsDlg::OnBnClickedMailAddButton()
{
	CArray<int, int> aSelItems;
	int iNumSel = m_listEmployees.GetSelCount();

	aSelItems.SetSize(iNumSel);
	m_listEmployees.GetSelItems(iNumSel, aSelItems.GetData());

	CString strItem;

	// need to count backwards since we will be removing items as we move them.  If we started
	// from the top, all selected indexes below would be changed, invalidating our array
    for (int i=iNumSel-1; i >= 0; i--)
	{
		AddMailRecipient(aSelItems[i]);
	}

	UpdateButtons();
}

void CSelectMailRecipientsDlg::OnBnClickedMailAddAllButton()
{
	CString strItem = "";
	while (m_listEmployees.GetCount() > 0)
	{
		AddMailRecipient(0);
	}

	UpdateButtons();
}

void CSelectMailRecipientsDlg::OnBnClickedMailRemoveButton()
{
	CArray<int, int> aSelItems;
	int iNumSel = m_listRecipients.GetSelCount();

	aSelItems.SetSize(iNumSel);
	m_listRecipients.GetSelItems(iNumSel, aSelItems.GetData());

	CString strItem;

	// need to count backwards since we will be removing items as we move them.  If we started
	// from the top, all selected indexes below would be changed, invalidating our array
    for (int i=iNumSel-1; i >= 0; i--)
	{
		RemoveMailRecipient(aSelItems[i]);
	}

	UpdateButtons();
}

void CSelectMailRecipientsDlg::OnBnClickedMailRemoveAllButton()
{
	CString strItem = "";
	while (m_listRecipients.GetCount() > 0)
	{
		RemoveMailRecipient(0);
	}

	UpdateButtons();
}

// Enables / Disables buttons as appropriate
void CSelectMailRecipientsDlg::UpdateButtons(void)
{
	m_btnAdd.EnableWindow( FALSE );
	m_btnAddAll.EnableWindow( FALSE );
	m_btnRemove.EnableWindow( FALSE );
	m_btnRemoveAll.EnableWindow( FALSE );
	m_btnOK.EnableWindow( FALSE ) ;

	if (m_listEmployees.GetSelCount() > 0) 
	{
		m_btnAdd.EnableWindow( TRUE );
	}

	if (m_listRecipients.GetSelCount() > 0)
	{
		m_btnRemove.EnableWindow( TRUE );
	}

	if (m_listEmployees.GetCount() > 0)
	{
		m_btnAddAll.EnableWindow( TRUE );
	}

	if (m_listRecipients.GetCount() > 0)
	{
		m_btnRemoveAll.EnableWindow( TRUE );
		m_btnOK.EnableWindow( TRUE );
	}
}

void CSelectMailRecipientsDlg::OnLbnSelchangeMailEmployeesList()
{
	UpdateButtons();
}

void CSelectMailRecipientsDlg::OnLbnSelchangeMailRecipientsList()
{
	UpdateButtons();
}

bool CSelectMailRecipientsDlg::AddMailRecipient(int iIndexToMove)
{
	CString strItem;
	int iuid = -1;
	int iIndex = -1;

	if (iIndexToMove >= m_listEmployees.GetCount()) return false;

	iuid = m_listEmployees.GetItemData(iIndexToMove);
	m_listEmployees.GetText(iIndexToMove, strItem);
	iIndex = m_listRecipients.AddString(strItem);
	m_listRecipients.SetItemData(iIndex, iuid);
	m_listEmployees.DeleteString(iIndexToMove);
	return true;
}

bool CSelectMailRecipientsDlg::RemoveMailRecipient(int iIndexToMove)
{
	CString strItem;
	int iuid = -1;
	int iIndex = -1;

	if (iIndexToMove >= m_listRecipients.GetCount()) return false;

	iuid = m_listRecipients.GetItemData(iIndexToMove);
	m_listRecipients.GetText(iIndexToMove, strItem);
	iIndex = m_listEmployees.AddString(strItem);
	m_listEmployees.SetItemData(iIndex, iuid);
	m_listRecipients.DeleteString(iIndexToMove);
	return true;
}

// // returns a string with semi-colon separated list of email addresses
CString CSelectMailRecipientsDlg::GetRecipientAddresses(void)
{
	CString strAddresses = "";
	int iCount = m_astrRecipientEmailAddresses.GetCount();
	for (int iIndex = 0; iIndex < iCount; iIndex++)
	{
		strAddresses += m_astrRecipientEmailAddresses[iIndex];
		strAddresses += ";";
	}
	return strAddresses;
}

void CSelectMailRecipientsDlg::CreateRecipientsList(void)
{
	int iNumRecips = m_listRecipients.GetCount();

	if (iNumRecips > 0)
	{
		CSetStoreContacts setStoreContacts(&g_dbFlooring);
		m_setEmployees.MoveFirst();
		
		CString strTemp = "";
		CString strTempFilter = "";
		CString strEmployeesFilter = "";
		CString strStoreContactsFilter = "";
		
		m_astrRecipientEmailAddresses.RemoveAll();
		
		for (int i = 0; i < iNumRecips; i++)
		{
			m_listRecipients.GetText(i, strTemp);
			strTempFilter.Format("ID = %d", m_listRecipients.GetItemData(i));
			if (strTemp.Find("SM:") == 0)
			{
				if (strStoreContactsFilter.GetLength() > 0) strStoreContactsFilter += " OR ";
				strStoreContactsFilter += strTempFilter;
			}
			else
			{
				if (strEmployeesFilter.GetLength() > 0) strEmployeesFilter += " OR ";
				strEmployeesFilter += strTempFilter;
			}
		}

		m_setEmployees.m_strFilter = strEmployeesFilter;
		m_setEmployees.Requery();

		setStoreContacts.m_strFilter = strStoreContactsFilter;
		setStoreContacts.Open();

		if (strEmployeesFilter.GetLength() > 0)
		{
			while (!m_setEmployees.IsEOF())
			{
				m_astrRecipientEmailAddresses.Add(m_setEmployees.m_SMTPEmail.GetBuffer());
				m_setEmployees.MoveNext();
			}
		}

		if (strStoreContactsFilter.GetLength() > 0)
		{
			while (!setStoreContacts.IsEOF())
			{
				m_astrRecipientEmailAddresses.Add(setStoreContacts.m_EmailAddress.GetBuffer());
				setStoreContacts.MoveNext();
			}
		}
	}
}

void CSelectMailRecipientsDlg::OnOK()
{
	CreateRecipientsList();
	CDialog::OnOK();
}

void CSelectMailRecipientsDlg::IncludeStoreManagement(CString strStoreNumber)
{
	m_iStoreID = CGlobals::StoreIDFromStoreNumber(strStoreNumber);
	m_bIncludeStoreManagement = (m_iStoreID != -1);
}
