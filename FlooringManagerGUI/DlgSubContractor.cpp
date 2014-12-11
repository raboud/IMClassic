// DlgSubContractor.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSubContractor.h"
#include "dlgsubcontractor.h"
#include "DataExchange.h"
#include "DlgSubContractor.h"
#include "SetSubContractorsDivisionAssignments.h"
#include "SetInstallerStatus.h"
#include "Winnetwk.h"
#include "SetSettings.h"
#include "CShellFileOp.h"

const int iMAX_BADGE_STATUS_CHARS = 10;
const int iMAX_RETAINAGE_CHARS = 3;

// CDlgSubContractor dialog

IMPLEMENT_DYNAMIC(CDlgSubContractor, CDialog)
CDlgSubContractor::CDlgSubContractor(bool bAdding, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSubContractor::IDD, pParent),
	m_bAdding(bAdding)
{
	m_pSet = new CSetSubContractor(&g_dbFlooring);
	m_pSet->Open();
	m_iSubContractorID = -1;
	this->assingedTo = -1;
}

CDlgSubContractor::~CDlgSubContractor()
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

void CDlgSubContractor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FIRST_NAME, m_editFirstName);
	DDX_Control(pDX, IDC_LAST_NAME, m_editLastName);
	DDX_Control(pDX, IDC_NICK_NAME, m_editNickName);
	DDX_Control(pDX, IDC_HELPER, m_btnHelper);

	DDX_Control(pDX, IDC_ADDRESS, m_editAddress);
	DDX_Control(pDX, IDC_CITY, m_editCity);
	DDX_Control(pDX, IDC_STATE, m_editState);
	DDX_Control(pDX, IDC_ZIP_CODE, m_editZip);	
	DDX_Control(pDX, IDC_SSN, m_editSSN);
	DDX_Control(pDX, IDC_HOME_PHONE, m_editHomePhone);
	DDX_Control(pDX, IDC_CELL_NUMBER, m_editCellNumber);
	DDX_Control(pDX, IDC_PAGER_NUMBER, m_editPager);

	DDX_Control(pDX, IDC_WORKMANSCOMP_INSURANCE_OK, m_btnWorkmansCompInsuranceOK);
	DDX_Control(pDX, IDC_DATE_WORKMANSCOMP_INSURANCE, m_dtpWorkmansCompInsurance);
	DDX_Control(pDX, IDC_DATE_LIABILITY_INSURANCE, m_dtpLiabilityInsurance);
	DDX_Control(pDX, IDC_INSURANCE_RATE_PCT, m_editInsuranceRatePct);
	DDX_Control(pDX, IDC_INSURANCE_RATE_DOLLAR, m_editInsuranceRateDollars);
	DDX_Control(pDX, IDC_LIABILITY_INSURANCE_OK, m_btnLiabilityInsuranceOK);

	DDX_Control(pDX, IDC_RETAINAGE_PCT, m_editRetainageRate);
	DDX_Control(pDX, IDC_RETAINAGE_TXT_1, m_stRetainageText1);
	DDX_Control(pDX, IDC_RETAINAGE_ACCOUNT_BAL, m_editRetainageAccountBalance);

	DDX_Control(pDX, IDC_SUBCONTRACTOR_BACKGND_RPT_REQ, m_btnBackgroundReqSent);
	DDX_Control(pDX, IDC_SUBCONTRACTOR_BACKGND_CHECK_PASSED, m_btnBackgroundCheckPassed);
	DDX_Control(pDX, IDC_SUBCONTRACTOR_BADGE_STATUS, m_editBadgeStatus);
	DDX_Control(pDX, IDC_SUBCONTRACTOR_BACKGROUNDCHK_DATE_APPROVED, m_dtpBackgroundChkDateApproved);

	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);

	DDX_Control(pDX, IDC_NOTES, m_editNotes);

	DDX_Control(pDX, IDC_SUBCONTRACTOR_ASSIGNEDTO, m_comboAssignedTo);

	DDX_Control(pDX, IDC_SUBCONTRACTOR_BRANCHOFFICE, m_cbMarket);
	DDX_Control(pDX, IDC_SUBCONTRACTOR_DIVISIONS, m_lbDivisions);
	DDX_Control(pDX, IDC_STATUS_COMBO, m_comboInstallerStatus);

	DDX_ComboBoxData(pDX, IDC_SUBCONTRACTOR_BRANCHOFFICE, m_pSet->m_MarketId);

	DDX_FieldText(pDX, IDC_FIRST_NAME, m_pSet->m_FirstName, m_pSet);
	DDX_FieldText(pDX, IDC_LAST_NAME, m_pSet->m_LastName, m_pSet);
	DDX_FieldText(pDX, IDC_NICK_NAME, m_pSet->m_NickName, m_pSet);

	DDX_FieldCheck(pDX, IDC_HELPER, m_pSet->m_Helper, m_pSet);

	DDX_FieldText(pDX, IDC_ADDRESS, m_pSet->m_Address, m_pSet);
	DDX_FieldText(pDX, IDC_CITY, m_pSet->m_City, m_pSet);
	DDX_FieldText(pDX, IDC_STATE, m_pSet->m_State, m_pSet);
	DDX_FieldText(pDX, IDC_ZIP_CODE, m_pSet->m_ZipCode, m_pSet);
	DDX_FieldText(pDX, IDC_SSN, m_pSet->m_SSN, m_pSet);

	DDX_FieldText(pDX, IDC_HOME_PHONE, m_pSet->m_HomePhoneNumber, m_pSet);
	DDX_FieldText(pDX, IDC_CELL_NUMBER, m_pSet->m_CellPhoneNumber, m_pSet);
	DDX_FieldText(pDX, IDC_PAGER_NUMBER, m_pSet->m_Pager, m_pSet);

	DDX_FieldCheck(pDX, IDC_WORKMANSCOMP_INSURANCE_OK, m_pSet->m_WorkmansCompInsuranceOK, m_pSet);
	DDX_FieldCheck(pDX, IDC_LIABILITY_INSURANCE_OK, m_pSet->m_LiabilityInsuranceOK, m_pSet);

	DDX_ComboBoxData(pDX, IDC_SUBCONTRACTOR_ASSIGNEDTO, this->assingedTo);

	DDX_FieldCheck(pDX, IDC_SUBCONTRACTOR_BACKGND_CHECK_PASSED, m_pSet->m_BackgroundCheckPassed, m_pSet);
	DDX_FieldCheck(pDX, IDC_SUBCONTRACTOR_BACKGND_RPT_REQ, m_pSet->m_BackgroundRptRequested, m_pSet);

	DDX_FieldText(pDX, IDC_SUBCONTRACTOR_BADGE_STATUS, m_pSet->m_BadgeStatus, m_pSet);

	DDX_FieldText(pDX, IDC_NOTES, m_pSet->m_Notes, m_pSet);

	DDX_FieldText(pDX, IDC_RETAINAGE_ACCOUNT_BAL, m_pSet->m_Retainage, m_pSet);

	if (pDX->m_bSaveAndValidate)
	{
		try
		{
			COleDateTime time ;
			m_dtpBackgroundChkDateApproved.GetTime( time ) ;
			m_pSet->m_BackgroundChkDateApproved = COleDateTime( time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);

			m_dtpWorkmansCompInsurance.GetTime( time );
			m_pSet->m_WorkmansCompInsuranceDate = COleDateTime( time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);

			m_dtpLiabilityInsurance.GetTime( time );
			m_pSet->m_LiabilityInsuranceDate = COleDateTime( time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
		}
		catch( CException* e)
		{
			e->Delete();
		}
	}
	else
	{
		try
		{
			m_dtpBackgroundChkDateApproved.SetTime( m_pSet->m_BackgroundChkDateApproved ) ;
			m_dtpWorkmansCompInsurance.SetTime( m_pSet->m_WorkmansCompInsuranceDate );
			m_dtpLiabilityInsurance.SetTime( m_pSet->m_LiabilityInsuranceDate );
		}
		catch( CException* e)
		{
			e->Delete();
		}
	}

	UpdateRates(pDX);
	UpdateDivisionsLB(pDX);
	UpdateStatus(pDX);

	// this causes the field to format correctly - without this call, there are 4
	// digits to the right of the decimal point.
	m_editRetainageAccountBalance.UpdateField();




	DDX_Control(pDX, IDC_SUBCONTRACTOR_PIC, m_pictSubContractor);
	DDX_Control(pDX, IDC_SUB_PICTURE_SELECT, m_butSetPicture);
}


BEGIN_MESSAGE_MAP(CDlgSubContractor, CDialog)
	ON_BN_CLICKED(IDC_HELPER, OnBnClickedHelper)
	ON_BN_CLICKED(IDC_WORKMANSCOMP_INSURANCE_OK, OnBnClickedWorkmansCompInsuranceOK)
	ON_BN_CLICKED(IDC_LIABILITY_INSURANCE_OK, OnBnClickedLiabilityInsuranceOK)
	ON_BN_CLICKED(IDC_SUB_PICTURE_SELECT, OnBnClickedSubPictureSelect)
END_MESSAGE_MAP()


// CDlgSubContractor message handlers

BOOL CDlgSubContractor::OnInitDialog()
{
	// make sure we've set the subcontractor id if we are editing
	ASSERT( (!m_bAdding && m_iSubContractorID != -1) || (m_bAdding));
	CDialog::OnInitDialog();
	
	if (!m_bAdding)
	{
		m_pSet->m_strFilter.Format("[SubContractorID] = %d", m_iSubContractorID);
		m_pSet->Requery();
		m_pSet->Edit();
	}
	else
	{
		m_pSet->AddNew();
		m_comboInstallerStatus.SetCurSel(m_comboInstallerStatus.FindStringExact(0,"Active"));
		ClearDivisionSelections();	
	}

	m_editBadgeStatus.SetLimitText(iMAX_BADGE_STATUS_CHARS);
	m_editRetainageRate.SetLimitText(iMAX_RETAINAGE_CHARS);
	m_editInsuranceRatePct.SetLimitText(iMAX_RETAINAGE_CHARS);
	m_editState.SetLimitText(2);
	
	if (!CGlobals::IsAdmin())
	{
		ShowRetainageControls(false);
	}

	m_editZip.SetMask(_T("#####-####"));
	m_editSSN.SetMask(_T("###-##-####"));
	m_editHomePhone.SetMask(_T("(###) ###-####"));
	m_editCellNumber.SetMask(_T("(###) ###-####"));
	m_editPager.SetMask(_T("(###) ###-####"));

	if (m_pSet->IsFieldNull(&(m_pSet->m_AssignedTo)))
	{
		assingedTo = -1;
	}
	else
	{
		assingedTo = m_pSet->m_AssignedTo;
	}

	UpdateData(FALSE);

	OnBnClickedHelper();
	OnBnClickedWorkmansCompInsuranceOK();
	OnBnClickedLiabilityInsuranceOK();

	if (m_pSet->m_PictureFilename.GetLength() > 0)
	{
		CSetSettings setSettings;
		CString strPicturePathFilename = setSettings.GetSetting("SubContractorPicturesPath");
		strPicturePathFilename += m_pSet->m_PictureFilename;
		m_pictSubContractor.LoadImage(strPicturePathFilename);
	}

	if (!CGlobals::HasPermission("CanBrowseSubContractorPictures"))
	{
		m_butSetPicture.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSubContractor::SetSubContractorID(int iSubContractorID)
{
	m_iSubContractorID = iSubContractorID;
}

void CDlgSubContractor::OnOK()
{
	UpdateData();
	if ((this->assingedTo == -1) || (!m_pSet->m_Helper))
	{
		m_pSet->SetFieldNull(&m_pSet->m_AssignedTo, TRUE);
	}
	else
	{
		m_pSet->m_AssignedTo = this->assingedTo;
	}

	if (ValidateInsurance())
	{
		if (m_btnHelper.GetCheck() == BST_UNCHECKED)
		{
			CString strDollars;
			CString strRate;
			m_editInsuranceRateDollars.GetWindowText(strDollars);
			m_editInsuranceRatePct.GetWindowText(strRate);
			COleDateTime dtWorkmansComp;
			COleDateTime dtLiability;
			COleDateTime timeNow = COleDateTime::GetCurrentTime();
			m_dtpWorkmansCompInsurance.GetTime(dtWorkmansComp);
			m_dtpLiabilityInsurance.GetTime(dtLiability);

			double dDollars = atof(strDollars);
			double dRate = atof(strRate);

			if (((dtWorkmansComp < timeNow) || (m_btnWorkmansCompInsuranceOK.GetCheck() != BST_CHECKED)) || ((dtLiability < timeNow) || (m_btnLiabilityInsuranceOK.GetCheck() != BST_CHECKED)))
			{
				if ((dDollars == 0) && (dRate == 0))
				{
					// expired insurance and not taking any money out for it...we want to alert the user about this
					int Response = MessageBox("The insurance is expired and you are not taking any money out for it.  Is this OK?", "Question", MB_YESNO);
					if (Response == IDNO)
					{
						m_editInsuranceRatePct.SetFocus();
						return;
					}

				}
			}
		}

		if (ValidateName())
		{
			bool bCont = true;
			if (!ValidateSSN())
			{
				if (CGlobals::IsAdmin())
				{
					int iResponse = MessageBox("The SSN is invalid. Continue?", "Info", MB_YESNO | MB_ICONQUESTION   );
					if (iResponse != IDYES)
					{
						bCont = false;
					}
				}
			}
			
			if (bCont)
			{
				if (ValidateHelper())
				{
					CDialog::OnOK();
					if ( m_bAdding )
					{
						int iInstallerStatus = m_comboInstallerStatus.GetItemData(m_comboInstallerStatus.GetCurSel());
						m_pSet->m_Status = iInstallerStatus;

						CString strFName = m_pSet->m_FirstName;
						CString strLName = m_pSet->m_LastName;
						CString strSSN = m_pSet->m_SSN;
						if ( m_pSet->Update() )
						{
							m_pSet->m_strFilter.Format("[FirstName] = '%s' AND [LastName] = '%s' AND [SSN] = '%s'", strFName, strLName, strSSN); 
							m_pSet->Requery();
							if (!m_pSet->IsEOF())
							{
								UpdateData();
							}
						}
					}
					else
					{
						try
						{
							m_pSet->Update();
						}
						catch (CDBException* e)
						{
							MessageBox("An error occurred while trying to update the record.  The data was not updated.", "Error!");
							e->Delete();
						}
					}
				}
			}
		}
	}
}

void CDlgSubContractor::OnCancel()
{
	m_pSet->CancelUpdate();
	CDialog::OnCancel();
}

void CDlgSubContractor::UpdateRates(CDataExchange* pDX)
{
	CString strRate ;
	int iRate ;
	double dRate;

	if (pDX->m_bSaveAndValidate)
	{
		// from controls to recordset
		m_editRetainageRate.GetWindowText(strRate) ;
		dRate = double(atof(strRate) / 100.0);
		strRate.Format("%.2f", dRate);
		m_pSet->m_RetainageRate = strRate;
		
		if (ValidateInsurance(false))
		{
			m_editInsuranceRatePct.GetWindowText(strRate) ;
			dRate = double(atof(strRate) / 100.0);
			strRate.Format("%.2f", dRate);
			m_pSet->m_InsuranceRate = strRate;

			m_editInsuranceRateDollars.GetWindowText(strRate);
			// make sure we have a number we can convert
			dRate = double(atof(strRate));
			strRate.Format("%.2f", dRate);
			m_pSet->m_InsuranceDollarAmount = strRate;
		}
	}
	else
	{
		// from recordset to controls
		iRate = int(atof(m_pSet->m_RetainageRate) * 100);
		strRate.Format("%d", iRate) ;
		m_editRetainageRate.SetWindowText(strRate) ;
		
		iRate = int(atof(m_pSet->m_InsuranceRate) * 100);
		strRate.Format("%d", iRate) ;
		m_editInsuranceRatePct.SetWindowText(strRate) ;

		dRate = atof(m_pSet->m_InsuranceDollarAmount);
		strRate.Format("%.2f", dRate) ;
		m_editInsuranceRateDollars.SetWindowText(strRate) ;

	}
	
}

bool CDlgSubContractor::ValidateInsurance(bool bShowMsg /*=true*/)
{
	bool bValid = true;
	CString strRate;
	CString strDollars;

	m_editInsuranceRateDollars.GetWindowText(strDollars);
	m_editInsuranceRatePct.GetWindowText(strRate);
	
	if ( (strDollars.GetLength() > 0) && (strRate.GetLength() > 0))
	{
		double dDollars = atof(strDollars);
		double dRate = atof(strRate);

		if ((dDollars > 0) && (dRate > 0))
		{
			if (bShowMsg)
			{
				MessageBox("The Retainage fields for Worksman's Comp - Dollars and Worksman's Comp - Percentage cannot both be greater than 0.  Please enter 0 into one or both fields.", "Error!");
				m_editInsuranceRateDollars.SetFocus();
			}
			bValid = false;
		}
	}

	return bValid;
}

void CDlgSubContractor::ShowRetainageControls(bool bShow)
{
	int iShow = SW_HIDE;
	if (bShow)
	{
		iShow = SW_SHOW;
	}

	GetDlgItem(IDC_WORKCOMP_RATE_PCT)->ShowWindow(iShow);
	GetDlgItem(IDC_WORKCOMP_RATE_DOLLAR)->ShowWindow(iShow);
	GetDlgItem(IDC_INSURANCE_PCT_TXT)->ShowWindow(iShow);
	GetDlgItem(IDC_INSURANCE_DOLLAR_TXT)->ShowWindow(iShow);
	GetDlgItem(IDC_INSURANCE_TXT_1)->ShowWindow(iShow);
	GetDlgItem(IDC_WORKMANSCOMP_INSURANCE_OK)->ShowWindow(iShow);
	GetDlgItem(IDC_LIABILITY_INSURANCE_OK)->ShowWindow(iShow);
	GetDlgItem(IDC_EXPIRES_TEXT)->ShowWindow(iShow);
	GetDlgItem(IDC_EXPIRES_TEXT2)->ShowWindow(iShow);
	GetDlgItem(IDC_EXPIRES_TEXT3)->ShowWindow(iShow);
	GetDlgItem(IDC_INSURANCE_GROUP)->ShowWindow(iShow);
	GetDlgItem(IDC_DATE_INSURANCE)->ShowWindow(iShow);
	GetDlgItem(IDC_RETAINAGE_PCT)->ShowWindow(iShow);
	GetDlgItem(IDC_RETAINAGE_TXT_1)->ShowWindow(iShow);
	GetDlgItem(IDC_RETAINAGE_TXT_2)->ShowWindow(iShow);
	GetDlgItem(IDC_RETAINAGE_TXT_3)->ShowWindow(iShow);
	GetDlgItem(IDC_RETAINAGE_ACCOUNT_BAL)->ShowWindow(iShow);
	GetDlgItem(IDC_RETAINAGE_GROUP)->ShowWindow(iShow);
	GetDlgItem(IDC_DATE_LIABILITY_INSURANCE)->ShowWindow(iShow);
	GetDlgItem(IDC_DATE_WORKMANSCOMP_INSURANCE)->ShowWindow(iShow);
	
}


void CDlgSubContractor::OnBnClickedHelper()
{
	if (m_btnHelper.GetCheck())
	{
		m_comboAssignedTo.EnableWindow();
		ShowRetainageControls(false);
	}
	else
	{
		m_comboAssignedTo.SetCurSel(0);
		m_comboAssignedTo.EnableWindow(FALSE);
		ShowRetainageControls(true);
	}
}

bool CDlgSubContractor::ValidateName()
{
	bool bValid = true;

	if (m_bAdding)
	{
		CSetSubContractor setSub(&g_dbFlooring);
		CString strFirstName;
		CString strLastName;
		CString strSSN;
		m_editFirstName.GetWindowText(strFirstName);
		m_editLastName.GetWindowText(strLastName);
		m_editSSN.GetWindowText(strSSN);

		setSub.m_strFilter.Format("[FirstName] = '%s' and [LastName] = '%s' and [SSN] = '%s'", strFirstName, strLastName, strSSN);
		setSub.Open();

		if (!setSub.IsEOF())
		{
			MessageBox("A SubContractor with this First Name, Last Name, and SSN is already in the database.", "Error");
			bValid = false;
		}
		setSub.Close();
	}

	return bValid;
}

bool CDlgSubContractor::ValidateSSN()
{
	// This is from the web site www.ssa.gov, under the faq section

	// An invalid (or impossible) Social Security number (SSN) is one which has not yet been assigned. 
	// The SSN is divided as follows: the area number (first three digits), group number (fourth and fifth digits), 
	// and serial number (last four digits). To determine if an SSN is invalid consider the following:

	// No SSNs with an area number in the 800 or 900 series, or "000" area number, have been assigned. 

	// No SSNs with an area number above 728 have been assigned in the 700 series, 
	// except for 729 through 733 and 764 through 772. 

	// No SSN's with a "00" group number or "0000" serial number have been assigned.

	// No SSNs with an area number of "666" have been or will be assigned.

	bool bValid = true;
	CString strErrorMsg = "";

	CString strSSN;
	m_editSSN.GetWindowText(strSSN);
	int iArea = atoi(strSSN.Left(3));
	int iGroup = atoi(strSSN.Mid(4,2));
	int iSerial = atoi(strSSN.Right(4));

	if ( (iArea == 0) || (iArea > 772))
	{
		strErrorMsg = "First 3 digits of SSN are invalid.";
		bValid = false;
	}
	else if ( (iArea > 733) && (iArea < 764) )
	{
		strErrorMsg = "First 3 digits of SSN are invalid.";
		bValid = false;
	}
	else if ( iArea == 666 )
	{
		strErrorMsg = "First 3 digits of SSN are invalid.";
		bValid = false;
	}
	else if (iGroup == 0)
	{
		strErrorMsg = "The middle 2 digits of the SSN cannot be 00.";
		bValid = false;
	}
	else if (iSerial == 0)
	{
		strErrorMsg = "The last 4 digits of the SSN cannot be 0000.";
		bValid = false;
	}

	if (!bValid)
	{
        MessageBox(strErrorMsg);
		m_editSSN.SetFocus();
	}

	return bValid;

}
void CDlgSubContractor::UpdateDivisionsLB(CDataExchange* pDX)
{
	if (!IsWindow(m_lbDivisions.m_hWnd))
		return;

	CSetSubContractorsDivisionAssignments setSubs(&g_dbFlooring);
	
	if (pDX->m_bSaveAndValidate)
	{
		CString strSQL;
		strSQL.Format("DELETE FROM SubContractorsDivisionAssignments WHERE SubContractorID = %d", m_iSubContractorID); 
		g_dbFlooring.ExecuteSQL(strSQL);

		int iNumSelItems = m_lbDivisions.GetSelCount();
		if (iNumSelItems > 0)
		{
			setSubs.m_strFilter = "[SubContractorID] = -1";
			setSubs.Open();
			int* aiSelIndexes = new int[iNumSelItems];
			m_lbDivisions.GetSelItems(iNumSelItems, aiSelIndexes);
			for (int iIndex = 0; iIndex < iNumSelItems; iIndex++)
			{
				long lData = m_lbDivisions.GetItemData(aiSelIndexes[iIndex]);
				setSubs.AddNew();
				setSubs.m_SubContractorID = m_iSubContractorID;
				setSubs.m_DivisionID = lData;
				setSubs.Update();
			}
			setSubs.Close();
			delete [] aiSelIndexes;
		}
	}
	else
	{
		ClearDivisionSelections();	

		if (m_iSubContractorID != -1)
		{
			int iCount = m_lbDivisions.GetCount();
			setSubs.m_strFilter.Format("[SubContractorID] = %d", m_iSubContractorID);
			setSubs.Open();
			while (!setSubs.IsEOF())
			{
				for (int iIndex = 0; iIndex < iCount; iIndex++)
				{
					long lData = m_lbDivisions.GetItemData(iIndex);
					if (setSubs.m_DivisionID == lData)
					{
						m_lbDivisions.SetSel(iIndex);
						break;
					}
				}
				setSubs.MoveNext();
			}
		}
	}
}
bool CDlgSubContractor::ValidateHelper(void)
{
	bool bOK = true;
	if ( m_btnHelper.GetCheck() )
	{
		CString strName;
		int index = m_comboAssignedTo.GetCurSel();
		if (index != -1)
		{
			m_comboAssignedTo.GetLBText(index, strName);
			if (strName == "N/A")
			{
				bOK = false;
			}
		}
		else
		{
			bOK = false;
		}
	}

	if (!bOK)
	{
		MessageBox("Please choose a subcontractor who is responsible for this helper.");
		m_comboAssignedTo.SetFocus();
	}

	return bOK;
}

void CDlgSubContractor::ClearDivisionSelections(void)
{
	int iCount = m_lbDivisions.GetCount();
	for (int iIndex = 0; iIndex < iCount; iIndex++)
	{
		m_lbDivisions.SetSel(iIndex, FALSE);
	}
}

void CDlgSubContractor::UpdateStatus(CDataExchange* pDX)
{
	if (!IsWindow(m_comboInstallerStatus.m_hWnd))
		return;

	CSetInstallerStatus setStatus(&g_dbFlooring);
	
	if (pDX->m_bSaveAndValidate)
	{
		int iInstallerStatus = m_comboInstallerStatus.GetItemData(m_comboInstallerStatus.GetCurSel());
		m_pSet->m_Status = iInstallerStatus;
	}
	else
	{
		int iInstallerStatus = m_pSet->m_Status;
		int iCount = m_comboInstallerStatus.GetCount();
		for (int iIndex = 0; iIndex < iCount; iIndex++)
		{
			if (iInstallerStatus == (int) m_comboInstallerStatus.GetItemData(iIndex))
			{
				m_comboInstallerStatus.SetCurSel(iIndex);
				break;
			}
		}
	}	
}
void CDlgSubContractor::OnBnClickedWorkmansCompInsuranceOK()
{
	if (m_btnWorkmansCompInsuranceOK.GetCheck() == BST_CHECKED)
	{
		m_dtpWorkmansCompInsurance.EnableWindow();
	}
	else
	{
		m_dtpWorkmansCompInsurance.EnableWindow(FALSE);
	}
}

void CDlgSubContractor::OnBnClickedLiabilityInsuranceOK()
{
	if (m_btnLiabilityInsuranceOK.GetCheck() == BST_CHECKED)
	{
		m_dtpLiabilityInsurance.EnableWindow();
	}
	else
	{
		m_dtpLiabilityInsurance.EnableWindow(FALSE);
	}
}

void CDlgSubContractor::OnBnClickedSubPictureSelect()
{
	TCHAR szFilters[] = _T("JPEG files (*.jpg)|*.jpg|Bitmap files (*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, _T("jpg"), _T("*.jpg"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (dlg.DoModal() == IDOK)
	{
		CString strFilename = dlg.GetFileName();
		CString strPathAndFilename = dlg.GetPathName();
		CString strNewFilename = "";

		if (CopyPicture(strPathAndFilename, strFilename, strNewFilename))
		{
			m_pSet->m_PictureFilename = strNewFilename;

			CSetSettings setSettings;
			CString strPicturePathFilename = setSettings.GetSetting("SubContractorPicturesPath");
			strPicturePathFilename += strNewFilename;

			m_pictSubContractor.LoadImage(strPicturePathFilename);
		}
		
		// This section was to derive the UNC path from where the picture is located.  Not needed now 
		// since we are only storing the file name, and the path to where the picture is located is
		// going to be specified by the settings table.  we will copy the picture to that location.

		//DWORD cbBuff = 1000;
		//TCHAR szBuff[1000];    // Buffer to receive information
		//REMOTE_NAME_INFO  * prni = (REMOTE_NAME_INFO *)   &szBuff;
		//// Pointers to head of buffer
		//UNIVERSAL_NAME_INFO * puni = (UNIVERSAL_NAME_INFO *) &szBuff;

		//if (::WNetGetUniversalName(strFilename, UNIVERSAL_NAME_INFO_LEVEL, (LPVOID) &szBuff, &cbBuff) == NO_ERROR)
		//{
		//	strFilename = CString(puni->lpUniversalName);
		//}
	}
}

bool CDlgSubContractor::CopyPicture(const CString& strPathAndFilename, const CString& strFilename, CString& strNewFilename)
{
	bool bSuccess = true;

	CSetSettings setSettings;
	CString strDestPath = setSettings.GetSetting("SubContractorPicturesPath");

	if (strDestPath.GetLength() == 0)
	{
		MessageBox("ERROR: Missing destination path from database.", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// if our path does not exist, create it
	int iReturnCDir = ERROR_SUCCESS;
	if (!PathFileExists(strDestPath))
	{
		iReturnCDir = SHCreateDirectoryEx(this->m_hWnd, strDestPath, NULL);
	}

	if (iReturnCDir != ERROR_SUCCESS)
	{
		MessageBox("ERROR: Could not create directory.", "Error", MB_ICONEXCLAMATION | MB_OK);
	}

	CString strExt = strFilename.Right(strFilename.GetLength() - strFilename.ReverseFind('.'));
	CString strSubContractorFileName;
	bool FileExists = true;
	int Index = 1;
	while (FileExists)
	{
		strSubContractorFileName.Format("%s_%s_%d%s", m_pSet->m_LastName, m_pSet->m_FirstName, Index, strExt);
		FileExists = (TRUE == ::PathFileExists(strDestPath + strSubContractorFileName));
		Index++;
	}
	strNewFilename = strSubContractorFileName;

	strSubContractorFileName = strDestPath + strSubContractorFileName;
	
	CShellFileOp fileop;
	fileop.AddSourceFile(strPathAndFilename);
	fileop.AddDestFile(strSubContractorFileName);
	fileop.SetOperationFlags(FO_COPY, AfxGetMainWnd(), FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE);

	BOOL bAPICalled = FALSE;
	int nAPIReturnVal = 0;
	if (!fileop.Go( &bAPICalled, &nAPIReturnVal ))
	{
		bSuccess = false;
	}

	return bSuccess;
}

