/*----------------------------------------------------------------------
	Copyright © 2001-2002 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// ViewSubcontrator.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "ViewSubcontrator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewSubcontrator

IMPLEMENT_DYNCREATE(CViewSubcontrator, CFRecordView)

CViewSubcontrator::CViewSubcontrator()
	: CFRecordView(CViewSubcontrator::IDD)
{
	//{{AFX_DATA_INIT(CViewSubcontrator)
	m_pSet = NULL ;
	//}}AFX_DATA_INIT
}

CViewSubcontrator::~CViewSubcontrator()
{
	if (m_pSet)
	{
		delete m_pSet;
	}
}

void CViewSubcontrator::DoDataExchange(CDataExchange* pDX)
{
	CFRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewSubcontrator)
	DDX_Control(pDX, IDC_RETAINAGE, m_editRetainage);
	DDX_Control(pDX, IDC_WORKCOMP_RATE, m_editWorkmanCompRate);
	DDX_Control(pDX, IDC_ZIP_CODE, m_editZip);
	DDX_Control(pDX, IDC_SSN, m_editSSN);
	DDX_Control(pDX, IDC_PAGER_NUMBER, m_editPager);
	DDX_Control(pDX, IDC_HOME_PHONE, m_editHomePhone);
	DDX_Control(pDX, IDC_CELL_NUMBER, m_editCellNumber);
	DDX_FieldText(pDX, IDC_ADDRESS, m_pSet->m_Address, m_pSet);
	DDX_FieldText(pDX, IDC_CELL_NUMBER, m_pSet->m_CellPhoneNumber, m_pSet);
	DDX_FieldText(pDX, IDC_CITY, m_pSet->m_City, m_pSet);
	DDX_FieldCheck(pDX, IDC_CRIMINAL_CHECK, m_pSet->m_CriminalId, m_pSet);
	DDX_DateTimeCtrl(pDX, IDC_DATE_CRIMINAL_CHECK, m_pSet->m_CriminalIdDate);
	DDX_DateTimeCtrl(pDX, IDC_DATE_INSURANCE, m_pSet->m_InsuranceDate);
	DDX_FieldText(pDX, IDC_FIRST_NAME, m_pSet->m_FirstName, m_pSet);
	DDX_FieldText(pDX, IDC_HOME_PHONE, m_pSet->m_HomePhoneNumber, m_pSet);
	DDX_FieldText(pDX, IDC_LAST_NAME, m_pSet->m_LastName, m_pSet);
	DDX_FieldText(pDX, IDC_NOTES, m_pSet->m_Notes, m_pSet);
	DDX_FieldText(pDX, IDC_PAGER_NUMBER, m_pSet->m_Pager, m_pSet);
	DDX_FieldText(pDX, IDC_SSN, m_pSet->m_SSN, m_pSet);
	DDX_FieldText(pDX, IDC_ZIP_CODE, m_pSet->m_ZipCode, m_pSet);
	DDX_FieldText(pDX, IDC_NICK_NAME, m_pSet->m_NickName, m_pSet);
	DDX_FieldText(pDX, IDC_STATE, m_pSet->m_State, m_pSet);
	//	DDX_FieldText(pDX, IDC_RETAINAGE, m_pSet->m_RetainageRate, m_pSet);
	DDV_MaxChars(pDX, m_pSet->m_State, 2);
	DDX_FieldCheck(pDX, IDC_INSURANCE, m_pSet->m_WorkmansComp, m_pSet);
	DDX_FieldCheck(pDX, IDC_ACTIVE, m_pSet->m_Active, m_pSet);
	DDX_FieldCheck(pDX, IDC_HELPER, m_pSet->m_Helper, m_pSet);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SUBCONTRACTORS_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_SUBCONTRACTORS_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_SUBCONTRACTORS_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_FIRST_NAME, m_editFirstName);
	DDX_Control(pDX, IDC_LAST_NAME, m_editLastName);
	DDX_Control(pDX, IDC_NICK_NAME, m_editNickName);
	DDX_Control(pDX, IDC_ACTIVE, m_btnActive);
	DDX_Control(pDX, IDC_HELPER, m_btnHelper);
	DDX_Control(pDX, IDC_ADDRESS, m_editAddress);
	DDX_Control(pDX, IDC_CITY, m_editCity);
	DDX_Control(pDX, IDC_STATE, m_editState);
	DDX_Control(pDX, IDC_INSURANCE, m_btnInsOK);
	DDX_Control(pDX, IDC_DATE_INSURANCE, m_dtpInsurance);
	DDX_Control(pDX, IDC_CRIMINAL_CHECK, m_btnCrimCheckOK);
	DDX_Control(pDX, IDC_DATE_CRIMINAL_CHECK, m_dtpCrimCheck);
	DDX_Control(pDX, IDC_NOTES, m_editNotes);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_INSTALLER_QUICKPICK_COMBO, m_comboInstallerQuickPick);
	DDX_Control(pDX, IDC_RETAINAGE_TXT_2, m_stRetainageText2);
	DDX_Control(pDX, IDC_RETAINAGE_TXT_1, m_stRetainageText1);
}


BEGIN_MESSAGE_MAP(CViewSubcontrator, CFRecordView)
	//{{AFX_MSG_MAP(CViewSubcontrator)
	ON_BN_CLICKED(IDC_CRIMINAL_CHECK, OnCriminalCheck)
	ON_BN_CLICKED(IDC_INSURANCE, OnInsurance)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_COMMAND(IDOK, OnOK)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SUBCONTRACTORS_ADD, OnBnClickedSubcontractorsAdd)
	ON_BN_CLICKED(IDC_SUBCONTRACTORS_EDIT, OnBnClickedSubcontractorsEdit)
	ON_BN_CLICKED(IDC_SUBCONTRACTORS_DELETE, OnBnClickedSubcontractorsDelete)
	ON_CBN_SELCHANGE(IDC_INSTALLER_QUICKPICK_COMBO, OnCbnSelchangeInstallerQuickpickCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewSubcontrator diagnostics

#ifdef _DEBUG
void CViewSubcontrator::AssertValid() const
{
	CFRecordView::AssertValid();
}

void CViewSubcontrator::Dump(CDumpContext& dc) const
{
	CFRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewSubcontrator message handlers
/////////////////////////////////////////////////////////////////////////////
// CCustomerView database support
CRecordset* CViewSubcontrator::OnGetRecordset()
{
	if (m_pSet != NULL)
	{
		return m_pSet;
	}
	
	m_pSet = new CSetSubContractor((&g_dbFlooring));
	m_pSet->m_strSort = "[LastName], [FirstName]" ;
	m_pSet->Open(AFX_DB_USE_DEFAULT_TYPE, NULL, CRecordset::useBookmarks);

	return m_pSet;
}

CSetSubContractor* CViewSubcontrator::GetRecordset()
{
	CSetSubContractor* pData = (CSetSubContractor*) OnGetRecordset();
	ASSERT(pData == NULL || pData->IsKindOf(RUNTIME_CLASS(CSetSubContractor)));
	return pData;
}

void CViewSubcontrator::OnInitialUpdate() 
{
	GetRecordset();
	m_bInsertable = true ;
	CFRecordView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_editHomePhone.SetPromptSymbol(_T('_')) ;
	m_editCellNumber.SetPromptSymbol(_T('_')) ;
	m_editPager.SetPromptSymbol(_T('_')) ;
	m_editZip.SetPromptSymbol(_T('_')) ;
	m_editSSN.SetPromptSymbol(_T('_')) ;


	m_editHomePhone.SetMask(_T("(###) ###-####")) ;
	m_editCellNumber.SetMask(_T("(###) ###-####")) ;
	m_editPager.SetMask(_T("(###) ###-####")) ;
	m_editZip.SetMask(_T("#####-####")) ;
	m_editSSN.SetMask(_T("###-##-####")) ;
	
	GetParentFrame()->SetTitle("Sub-Contractor Records");

	CPermissions perm;

	if (perm.HasPermission("EditRetainage") == true )
	{
		m_editRetainage.ShowWindow(SW_SHOW) ;
		m_stRetainageText1.ShowWindow(SW_SHOW);
		m_stRetainageText2.ShowWindow(SW_SHOW);
	}
	else
	{
		m_editRetainage.ShowWindow(SW_HIDE) ;
		m_stRetainageText1.ShowWindow(SW_HIDE);
		m_stRetainageText2.ShowWindow(SW_HIDE);
	}

	m_btnAdd.EnableWindow(perm.HasPermission("AddSubContractor") == true);
	m_btnEdit.EnableWindow(perm.HasPermission("EditSubContractor") == true);
	m_btnDelete.EnableWindow(perm.HasPermission("DeleteSubContractor") == true);

	EnableControls(false);
	m_btnOK.ShowWindow(SW_SHOW);
	m_btnCancel.ShowWindow(SW_SHOW);

	UpdateData(false) ;

	UpdatePickList();
	
}

void CViewSubcontrator::OnOK() 
{
	CFRecordView::OnOK();
	GetParentFrame()->DestroyWindow();
}

void CViewSubcontrator::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CFRecordView::OnUpdate(pSender, lHint, pHint) ;
	CString strRate ;
	int iRate ;
	
	iRate = int(atof(m_pSet->m_RetainageRate) * 100);
	strRate.Format("%d", iRate) ;
	m_editRetainage.SetWindowText(strRate) ;
	
	iRate = int(atof(m_pSet->m_WorkmanCompRate) * 100);
	strRate.Format("%d", iRate) ;
	m_editWorkmanCompRate.SetWindowText(strRate) ;
}

void CViewSubcontrator::OnCriminalCheck() 
{
	CButton* pBool = (CButton*) GetDlgItem(IDC_CRIMINAL_CHECK) ;
	int bState = pBool->GetCheck() ;
	EnableControl(IDC_DATE_CRIMINAL_CHECK, (bState == BST_CHECKED)) ;

}

void CViewSubcontrator::OnInsurance() 
{
	CButton* pBool = (CButton*) GetDlgItem(IDC_INSURANCE) ;
	int bState = pBool->GetCheck() ;
	EnableControl(IDC_DATE_INSURANCE, (bState == BST_CHECKED)) ;
}

void CViewSubcontrator::OnCancel() 
{
	if (m_bEditing)
	{
		m_bEditing = false;
		m_btnEdit.SetWindowText("Edit");
		m_btnAdd.EnableWindow();
		m_btnDelete.EnableWindow();
		m_btnOK.EnableWindow();
		EnableControls(false);
		UpdateData(FALSE);
	}
	else if (m_bAdding)
	{
		m_bAdding = false;
		m_btnAdd.SetWindowText("Add");
		m_btnEdit.EnableWindow();
		m_btnDelete.EnableWindow();
		m_btnOK.EnableWindow();
		EnableControls(false);
		m_pSet->CancelUpdate();
		m_pSet->MoveFirst();
		UpdateData(FALSE);
	}
	else
	{
        GetParentFrame()->DestroyWindow();
	}

//	CFRecordView::OnCancel();
//	EnableControl(IDC_DATE_CRIMINAL_CHECK, (m_pSet->m_CriminalId == TRUE)) ;
//	EnableControl(IDC_DATE_INSURANCE, (m_pSet->m_WorkmansComp == TRUE)) ;

}

BOOL CViewSubcontrator::OnMove(UINT nIDMoveCommand) 
{
	int iIndex = m_comboInstallerQuickPick.GetCurSel();

	switch (nIDMoveCommand)
	{
		case ID_RECORD_PREV:
			iIndex--;
			if (iIndex < 0) iIndex = 0;
			break;

		case ID_RECORD_FIRST:
			iIndex = 0;
			break;

		case ID_RECORD_NEXT:
			iIndex++;
			if (iIndex >= m_comboInstallerQuickPick.GetCount())
				iIndex = m_comboInstallerQuickPick.GetCount() - 1;
			break;

		case ID_RECORD_LAST:
			iIndex = m_comboInstallerQuickPick.GetCount() - 1;
			break;
	
		default:
			// Unexpected case value
			ASSERT(FALSE);
	}

	m_comboInstallerQuickPick.SetCurSel(iIndex);

	m_pSet->Edit() ;

	CString strRate ;
	int iRate ;

	m_editRetainage.GetWindowText(strRate) ;
	iRate = atoi(strRate) ;
	m_pSet->m_RetainageRate.Format("%f", iRate / 100.) ;

	m_editWorkmanCompRate.GetWindowText(strRate) ;
	iRate = atoi(strRate) ;
	m_pSet->m_WorkmanCompRate.Format("%f", iRate / 100.) ;

	m_pSet->Update() ;

	BOOL bReturn = CFRecordView::OnMove(nIDMoveCommand);

	if (bReturn)
	{
		CString strRate ;
		int iRate ;
		
		iRate = int(atof(m_pSet->m_RetainageRate) * 100);
		strRate.Format("%d", iRate) ;
		m_editRetainage.SetWindowText(strRate) ;
		
		iRate = int(atof(m_pSet->m_WorkmanCompRate) * 100);
		strRate.Format("%d", iRate) ;
		m_editWorkmanCompRate.SetWindowText(strRate) ;
	}
	
	return bReturn ;
}

void CViewSubcontrator::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFRecordView::CalcWindowRect(lpClientRect, nAdjustType);
}

void CViewSubcontrator::OnBnClickedSubcontractorsAdd()
{
	CSetSubContractor* prs = GetRecordset();
	if (m_bAdding)
	{
		UpdateData();

		CString strRate ;
		int iRate ;

		m_editRetainage.GetWindowText(strRate) ;
		iRate = atoi(strRate) ;
		prs->m_RetainageRate.Format("%f", iRate / 100.) ;
		
		m_editWorkmanCompRate.GetWindowText(strRate) ;
		iRate = atoi(strRate) ;
		prs->m_WorkmanCompRate.Format("%f", iRate / 100.) ;

		prs->Update();
		prs->Requery();
		UpdateData(FALSE);
		EnableControls(false);
		m_bAdding = false;
		m_btnAdd.SetWindowText("Add");
		m_btnEdit.EnableWindow();
		m_btnDelete.EnableWindow();
		m_btnOK.EnableWindow();
		UpdatePickList();
	}
	else
	{
		EnableControls(true);
		m_bAdding = true;
		m_btnAdd.SetWindowText("Save");
		m_btnEdit.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
		m_btnOK.EnableWindow(FALSE);
		prs->AddNew();
		UpdateData(FALSE);
	}
}

void CViewSubcontrator::OnBnClickedSubcontractorsEdit()
{
	CSetSubContractor* prs = GetRecordset();
	if (m_bEditing)
	{
		prs->Edit();
		m_bEditing = false;
		m_btnEdit.SetWindowText("Edit");
		m_btnAdd.EnableWindow();
		m_btnDelete.EnableWindow();
		m_btnOK.EnableWindow();
		UpdateData();

		CString strRate ;
		int iRate ;

		m_editRetainage.GetWindowText(strRate) ;
		iRate = atoi(strRate) ;
		prs->m_RetainageRate.Format("%f", iRate / 100.) ;

		m_editWorkmanCompRate.GetWindowText(strRate) ;
		iRate = atoi(strRate) ;
		prs->m_WorkmanCompRate.Format("%f", iRate / 100.) ;

		prs->Update();
	}
	else
	{
		m_bEditing = true;
		m_btnEdit.SetWindowText("Save");
		m_btnAdd.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
		m_btnOK.EnableWindow(FALSE);
	}

	EnableControls(m_bEditing);
}

void CViewSubcontrator::OnBnClickedSubcontractorsDelete()
{
	int iResponse = MessageBox("Are you sure you wish to delete the current sub-contractor?  The operation cannot be undone.", "Delete Sub-Contractor", MB_YESNO);
	if (iResponse == IDYES)
	{
		try
		{
			CSetSubContractor* prs = GetRecordset();
			prs->Delete();
			prs->Requery();
			UpdateData(FALSE);
			UpdatePickList();
		}
		catch (CDBException* e)
		{
			MessageBox("There was an error deleting this subcontractor.  Record was not deleted.", "Error!");
			e->Delete();
		}
	}
}

void CViewSubcontrator::EnableControls(bool bEnable)
{
	m_btnActive.EnableWindow(bEnable == true);
	m_btnHelper.EnableWindow(bEnable == true) ;
	m_btnCrimCheckOK.EnableWindow(bEnable == true);
	m_btnInsOK.EnableWindow(bEnable == true);
	m_dtpCrimCheck.EnableWindow(bEnable == true);
	m_dtpInsurance.EnableWindow(bEnable == true);
	m_editAddress.EnableWindow(bEnable == true);
	m_editCellNumber.EnableWindow(bEnable == true);
	m_editCity.EnableWindow(bEnable == true);
	m_editFirstName.EnableWindow(bEnable == true);
	m_editHomePhone.EnableWindow(bEnable == true);
	m_editLastName.EnableWindow(bEnable == true);
	m_editNickName.EnableWindow(bEnable == true);
	m_editNotes.EnableWindow(bEnable == true);
	m_editPager.EnableWindow(bEnable == true);
	m_editRetainage.EnableWindow(bEnable == true);
	m_editWorkmanCompRate.EnableWindow(bEnable == true);
	m_editSSN.EnableWindow(bEnable == true);
	m_editState.EnableWindow(bEnable == true);
	m_editZip.EnableWindow(bEnable == true);
	m_comboInstallerQuickPick.EnableWindow(bEnable == false);
}

void CViewSubcontrator::OnCbnSelchangeInstallerQuickpickCombo()
{
	int iInstallerID = m_comboInstallerQuickPick.GetItemData(m_comboInstallerQuickPick.GetCurSel());
	CSetSubContractor* prs = GetRecordset();
	prs->MoveFirst();
	while (!prs->IsEOF())
	{
		if (prs->m_SubContractorID == iInstallerID)
		{
			break;
		}
		prs->MoveNext();
	}

	int iRRate ;
	CString strRate;

	iRRate = int(atof(m_pSet->m_RetainageRate) * 100);
	strRate.Format("%d", iRRate) ;
	m_editRetainage.SetWindowText(strRate) ;

	iRRate = int(atof(m_pSet->m_WorkmanCompRate) * 100);
	strRate.Format("%d", iRRate) ;
	m_editWorkmanCompRate.SetWindowText(strRate) ;

	UpdateData( FALSE );
}

void CViewSubcontrator::UpdatePickList(void)
{
	CSetSubContractor* prs = GetRecordset();
	m_iNextSubContractorID = prs->m_SubContractorID;
	int iSelectedIndex = 0;
	CDBVariant varBookmark;
	prs->GetBookmark(varBookmark);
	prs->MoveFirst();
	m_comboInstallerQuickPick.ResetContent();
	CString strInstaller;
	while (!prs->IsEOF())
	{
		strInstaller.Format("%s, %s", prs->m_LastName, prs->m_FirstName);
		int iIndex = m_comboInstallerQuickPick.AddString( strInstaller );
		m_comboInstallerQuickPick.SetItemData(iIndex, prs->m_SubContractorID);
		if (m_iNextSubContractorID == prs->m_SubContractorID)
		{
			iSelectedIndex = iIndex;
		}
		prs->MoveNext();
	}
	prs->SetBookmark(varBookmark);
	m_comboInstallerQuickPick.SetCurSel(iSelectedIndex);
}