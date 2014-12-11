// DlgPONoteEntry.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgPONoteEntry.h"
#include "SetEmployees.h"
#include "SetCustomer.h"
#include "SetNoteTypes.h"
#include "SetSpokeWith.h"
#include "DialogSchedule.h"
#include "SetSettings.h"
#include "SelectMailRecipientsDlg.h"
#include "DlgSendNote.h"
#include "Globals.h"

const int iMANAGER_ACTION_ID = 15;

// CDlgPONoteEntry dialog

IMPLEMENT_DYNAMIC(CDlgPONoteEntry, CDialog)
CDlgPONoteEntry::CDlgPONoteEntry(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPONoteEntry::IDD, pParent)
	, m_bEditing(false)
	, m_strCustomerName(_T(""))
	, m_strSiteAddress(_T(""))
{
	m_iOrderID = -1;
	m_iCustomerID = -1;
	m_iId = -1 ;
	m_bNewNote = true;
	m_strEmailBody = "";
	m_strPONumber = "";
	m_strStoreNumber = "";
	m_bCanSchedule = true;
	m_bAskToSend = false;
	m_bSendToExpeditor = false;
	
	VERIFY(m_fontPhoneNumbers.CreatePointFont(12, "Courier"));
}

CDlgPONoteEntry::~CDlgPONoteEntry()
{
}

void CDlgPONoteEntry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PONOTE_COMBO_NOTETYPE, m_comboNoteType);
	DDX_Control(pDX, IDC_PONOTE_COMBO_SPOKEWITH, m_comboSpokeWith);
	DDX_Control(pDX, IDC_PONOTE_OTHEREDIT, m_editSpokeWithOther);
	DDX_Control(pDX, IDC_SCHEDULED, m_btnScheduled);
	DDX_Control(pDX, IDC_UNSCHEDULED, m_btnUnscheduled);
	DDX_Control(pDX, IDC_DATE_SCHEDULE, m_dtScheduledDate);
	DDX_Control(pDX, IDC_AM, m_btnAM);
	DDX_Control(pDX, IDC_PM, m_btnPM);
	DDX_Control(pDX, IDC_CUST_TO_CALL, m_btnCustCallback);
	DDX_Control(pDX, IDC_PONOTE_NOTES, m_editNotes);
	DDX_Control(pDX, IDC_PONOTES_NOTESADD, m_editAddNotes);
	DDX_Control(pDX, IDC_STATIC_ADDNOTES, m_stAddNotes);
	DDX_Control(pDX, IDC_STATIC_PHONEGROUP, m_stPhoneGroup);
	DDX_Control(pDX, IDC_PONOTE_SAVEANDEMAIL_BUTTON, m_btnSaveAndEmail);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_SCHEDULE_GROUPBOX, m_stScheduleGroup);
	DDX_Control(pDX, IDC_STATIC_SCHEDULETEXT, m_stScheduleText);
	DDX_Control(pDX, IDC_STATIC_CURRENT_SCHEDULE_DATE, m_stCurrentScheduleDate);
	DDX_Control(pDX, IDC_DATE_ENDSCHEDULE, m_ScheduleEndDate);
	DDX_Control(pDX, IDC_STATIC_STARTDATE, m_stScheduleStart);
	DDX_Control(pDX, IDC_STATIC_ENDDATE, m_stScheduleEnd);
	DDX_Text(pDX, IDC_CUSTOMERNAME, m_strCustomerName);
	DDX_Text(pDX, IDC_SITEADDRESS, m_strSiteAddress);
	DDX_Control(pDX, IDC_EDIT_HOMEPHONE, m_editPhoneHome);
	DDX_Control(pDX, IDC_EDIT_WORKPHONE, m_editPhoneWork);
	DDX_Control(pDX, IDC_EDIT_MOBILEPHONE, m_editPhoneMobile);
	DDX_Control(pDX, IDC_EDIT_EMAILADDRESS, m_editEmailAddress);
}


BEGIN_MESSAGE_MAP(CDlgPONoteEntry, CDialog)
	ON_CBN_SELCHANGE(IDC_PONOTE_COMBO_NOTETYPE, OnCbnSelchangePonoteComboNotetype)
	ON_CBN_SELCHANGE(IDC_PONOTE_COMBO_SPOKEWITH, OnCbnSelchangePonoteComboSpokewith)
	ON_BN_CLICKED(IDC_SCHEDULED, OnBnClickedScheduled)
	ON_BN_CLICKED(IDC_UNSCHEDULED, OnBnClickedUnscheduled)
	ON_EN_CHANGE(IDC_PONOTE_NOTES, OnEnChangePonoteNotes)
	ON_BN_CLICKED(IDC_AM, OnBnClickedAm)
	ON_BN_CLICKED(IDC_PM, OnBnClickedPm)
	ON_BN_CLICKED(IDC_CUST_TO_CALL, OnBnClickedCustToCall)
	ON_EN_CHANGE(IDC_PONOTES_NOTESADD, OnEnChangePonotesNotesadd)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_SCHEDULE, OnDtnDatetimechangeDateSchedule)
	ON_BN_CLICKED(IDC_PONOTE_SAVEANDEMAIL_BUTTON, OnBnClickedPonoteSaveandemailButton)
	ON_EN_CHANGE(IDC_EDIT_HOMEPHONE, &CDlgPONoteEntry::OnEnHomePhoneChange)
	ON_EN_CHANGE(IDC_EDIT_WORKPHONE, &CDlgPONoteEntry::OnEnWorkPhoneChange)
	ON_EN_CHANGE(IDC_EDIT_MOBILEPHONE, &CDlgPONoteEntry::OnEnMobilePhoneChange)
	ON_EN_CHANGE(IDC_EDIT_EMAILADDRESS, &CDlgPONoteEntry::OnEnEmailAddressChange)
END_MESSAGE_MAP()


// CDlgPONoteEntry message handlers

BOOL CDlgPONoteEntry::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitializeControlsForNewNote();	

	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("OrderID = '%d'", m_iOrderID);
	setOrders.Open();

	InitializeCustomerAndPOFields(setOrders);

	try
	{
		InitializeCustomerDetails();

		InitializeScheduleDateField(setOrders);

		// if we are editing an existing note, initialize the fields...
		if (false == m_bNewNote)
		{
			InitializeFieldsForExistingNote();
		}
		else
		{
			m_comboNoteType.PopulateList(false);
			
			ShowScheduleBox(false);
		}
	}
	catch (CException *pE)
	{
		pE->Delete() ;
	}

	setOrders.Close();

	ConfigureNoteEditFields();

	ConfigureSchedulingControls();

	m_bDirty = false ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPONoteEntry::ConfigureNoteEditFields() 
{
	{
		BOOL bCanEditNoteType = CGlobals::HasNoteTypePermission(m_comboNoteType.GetCurrentLBText());

		// if we are editing, but do not have permissions, then show the additional window to add notes
		if ((CGlobals::HasPermission("EditCallNote") == false) && (m_bEditing == true))
		{
			// show 2nd Edit box for additional comments and enable it
			//m_editAddNotes.EnableWindow(bCanEditNoteType);
			m_editAddNotes.SetReadOnly(bCanEditNoteType == FALSE);
			// setting the length for additional notes so the total length does not exceed our max.  Also
			// subtracting 100 extra to account for the "additional notes added by..." text
			int iMaxLength = CGlobals::iMAX_ORDER_NOTES - m_editNotes.GetWindowTextLength() - 100;
			if (iMaxLength > 0)
			{
				m_editAddNotes.SetLimitText(iMaxLength);
			}
			else
			{
				MessageBox("This note is already at maximum size.  No more text can be entered.", "Note!");
				m_editAddNotes.SetReadOnly();
			}

			m_editNotes.SetReadOnly();

			CString strTemp = "";
			m_comboSpokeWith.GetLBText(m_comboSpokeWith.GetCurSel(), strTemp);
			if (strTemp.MakeUpper().Find("SELECT") != -1)
			{
				m_comboSpokeWith.EnableWindow();
			}
		}
		else
		{
			//hide additional notes edit box and resize the main box to fill the whole space
			RECT rectAdd;
			RECT rect;
			m_editNotes.GetWindowRect(&rect);
			m_editAddNotes.GetWindowRect(&rectAdd); 
			m_editAddNotes.ShowWindow(SW_HIDE);
			m_stAddNotes.ShowWindow(SW_HIDE);
			//resize main comments edit box to cover area
			rect.bottom = rectAdd.bottom ;
			ScreenToClient(&rect);
			m_editNotes.MoveWindow(&rect);  
			m_editNotes.SetReadOnly(bCanEditNoteType == FALSE);

			CString strTemp = "";
			if (m_comboSpokeWith.GetCount() > 0)
			{
				m_comboSpokeWith.GetLBText(m_comboSpokeWith.GetCurSel(), strTemp);
				if (strTemp.MakeUpper().Find("SELECT") != -1)
				{
					m_comboSpokeWith.EnableWindow();
				}
			}
		}
	}
}

void CDlgPONoteEntry::OnCbnSelchangePonoteComboNotetype()
{
	OnChange();
	int iNoteTypeID = GetNoteTypeID();
	m_comboSpokeWith.PopulateList(iNoteTypeID);
	EnableSpokeWith(iNoteTypeID);
	ShowScheduleControlsByNoteType();
	EnableButtons(iNoteTypeID);
	ConfigureNoteEditFields();
}

void CDlgPONoteEntry::EnableSpokeWith(int iNoteTypeID)
{
	m_comboSpokeWith.EnableWindow(FALSE);
	m_editSpokeWithOther.EnableWindow(FALSE);

	CSetNoteTypes setNoteType(&g_dbFlooring);
	setNoteType.m_strFilter.Format("ID = '%d'", iNoteTypeID);
	setNoteType.Open();
	if (!setNoteType.IsEOF())
	{
		if (setNoteType.m_RequireSpokeWith)
		{
			m_comboSpokeWith.EnableWindow();
			m_comboSpokeWith.SetCurSel(1);
		}
		else
		{
			m_comboSpokeWith.SetCurSel(m_comboSpokeWith.FindStringExact(0,"N/A"));
		}
	}
	setNoteType.Close();
}

void CDlgPONoteEntry::ShowScheduleControlsByNoteType()
{
	int iNoteTypeID = GetNoteTypeID();
	int iSpokeWithID = GetSpokeWithID();
	bool bShow = false;

	CSetNoteTypes setNoteType(&g_dbFlooring);
	setNoteType.m_strFilter.Format("ID = '%d'", iNoteTypeID);
	setNoteType.Open();

	CSetSpokeWith setSpokeWith(&g_dbFlooring);
	setSpokeWith.m_strFilter.Format("SpokeWith = '%d'", iSpokeWithID);
	setSpokeWith.Open();

	if (!setNoteType.IsEOF())
	{
		if (setNoteType.m_EnableSchedulingInfo)
		{
			if (setNoteType.m_RequireSpokeWith)
			{
				if (setSpokeWith.m_EnableSchedulingInfo)
				{
					bShow = true;
				}
			}
			else
			{
				bShow = true;
			}
		}
	}
	setNoteType.Close();
	setSpokeWith.Close();

	ShowScheduleBox(bShow);

	if (bShow)
	{
		if (m_btnScheduled.GetCheck() == BST_CHECKED)
		{
			ShowScheduleControls(true);
		}
		else if (m_btnUnscheduled.GetCheck() == BST_CHECKED)
		{
			ShowScheduleControls(false);
		}
		else
		{
			ShowScheduleControls(false);
		}
	}
}

void CDlgPONoteEntry::OnOK()
{
	if (Validate())
	{
		CString NoteTypeText = GetNoteType();
		//m_comboNoteType.GetLBText(m_comboNoteType.GetCurSel(), NoteTypeText);

		if (m_bNewNote)
		{
			if (NoteTypeText == "FAX TO STORE")
			{
				if (MessageBox("Do you want to print note so it can be FAXed to store?", "Print?", MB_YESNO) == IDYES)
				{
					CGlobals::PrintPONote(m_iId);
				}
			}
			
			if (m_bAskToSend)
			{
				CDlgSendNote dlgSendNote;
				
				dlgSendNote.ShowCopyToSASM(true);
				dlgSendNote.ShowCopyToExpeditorEmail(true);

				if (dlgSendNote.DoModal() == IDOK)
				{
					m_bSendToExpeditor = true;
					m_bCopyToSASM = (dlgSendNote.m_CopyNoteToSASM == TRUE);
					m_bCopyToExpeditorEmail = (dlgSendNote.m_CopyNoteToExpeditorEmail == TRUE);
				}
			}
		}
        CDialog::OnOK();
	}
}

bool CDlgPONoteEntry::Validate()
{
	bool bValid = false;

	CString strTemp = "";
	m_editAddNotes.GetWindowText(strTemp);
	if ((m_bDirty) || (strTemp.GetLength() > 0))
	{
		// verify the Other field is filled in appropriately
		CString strSpokeWith = "";
		m_comboSpokeWith.GetLBText(m_comboSpokeWith.GetCurSel(), strSpokeWith);
		if (strSpokeWith == "OTHER")
		{
			m_editSpokeWithOther.GetWindowText(strSpokeWith);
			if (strSpokeWith.GetLength() < 2)
			{
				MessageBox("The appropriate name must be entered into the Other field.", "Error") ;
				m_editSpokeWithOther.SetFocus() ;
				return bValid;
			}
		}

		// verify the Person Spoke with is valid based on the Note Type 
		int iNoteType = GetNoteTypeID() ;
		CSetNoteTypes setNoteType(&g_dbFlooring);
		setNoteType.m_strFilter.Format("ID = '%d'", iNoteType);
		setNoteType.Open();
		if (!setNoteType.IsEOF())
		{
			if (TRUE == setNoteType.m_RequireSpokeWith)
			{
                if (strSpokeWith.Find("Select") != -1)
				{
                    MessageBox("The person spoken to must be selected.", "Error") ;
					setNoteType.Close();
					return bValid;
				}
			}

			if ((TRUE == setNoteType.m_CanSendToExpeditor) && (CGlobals::HasPermission("CanSendNoteToStore") == true))
			{
				m_bAskToSend = true;
			}
		}
		setNoteType.Close();

		bool bSchedule = m_btnScheduled.GetCheck() == BST_CHECKED ;
		bool bUnschedule = m_btnUnscheduled.GetCheck() == BST_CHECKED ;

		// verify notes are correctly entered.
		if (!bSchedule && (strSpokeWith != "Left Message") && (strSpokeWith != "No Answer"))
		{
			CString strNotes ;
			m_editNotes.GetWindowText(strNotes);

			if (strNotes.GetLength() < 10)
			{
				MessageBox("The appropriate comments must be entered.") ;
				m_editNotes.SetFocus() ;
				return bValid;
			}
		}

		COleDateTime dateSchedStart ;
		COleDateTime dateSchedEnd ;
		CDialogSchedule dlgSched;
		if (bSchedule)
		{
			m_dtScheduledDate.GetTime(dateSchedStart) ;
			m_ScheduleEndDate.GetTime(dateSchedEnd);

			dateSchedStart = COleDateTime(dateSchedStart.GetYear(), dateSchedStart.GetMonth(), dateSchedStart.GetDay(), 0, 0, 0) ;
			dateSchedEnd = COleDateTime(dateSchedEnd.GetYear(), dateSchedEnd.GetMonth(), dateSchedEnd.GetDay(), 0, 0, 0) ;

			bool bAM = m_btnAM.GetCheck() == BST_CHECKED ;
			bool bPM = m_btnPM.GetCheck() == BST_CHECKED ;
			if (!bAM && !bPM)
			{
				MessageBox("Either AM or PM must be selected to schedule the installation.") ;
				return bValid;
			}

			// Show the job list dialog box
			dlgSched.SetScheduled(m_iCustomerID, m_iOrderID, dateSchedStart, dateSchedEnd, bAM) ;
			if (dlgSched.DoModal() == IDCANCEL)
			{
				return bValid;
			}
		}

		if (bUnschedule)
		{
			dlgSched.SetUnschedled(m_iCustomerID, m_iOrderID) ;
			if (dlgSched.DoModal() == IDCANCEL)
			{
				return bValid;
			}
		}

		// get our recordset to do the updates
		
		CSetPONotes set(&g_dbFlooring) ;
		set.m_strFilter = "ID = -1";

		if (m_iId == -1)
		{
			set.Open() ;
			set.AddNew();
			set.m_OrderID = m_iOrderID ;
		}
		else
		{
			set.m_strFilter.Format("ID = '%d'", m_iId) ;
			set.Open() ;
			set.MoveFirst() ;
			set.Edit() ;
		}

		// update the database
		set.m_EnteredByUserID = CGlobals::GetEmployeeID() ;

		set.m_Scheduled = bSchedule;
		set.m_UnScheduled = bUnschedule;

        if (bSchedule)
		{
			set.m_ScheduledDate = dateSchedStart;
			set.m_ScheduledAM = m_btnAM.GetCheck() == BST_CHECKED ;
		}
		
		set.m_NoteTypeID = GetNoteTypeID() ;
		set.m_SpokeWithID = GetSpokeWithID();
		m_editSpokeWithOther.GetWindowText(set.m_ContactName) ;
		
		set.m_CustomerToCallBack = m_btnCustCallback.GetCheck() == BST_CHECKED;
		CString strNotes;
		CString strAdditionalNotes;
		CString strDateTime;
		COleDateTime time = CGlobals::GetCurrentSystemTime();
		strDateTime = time.Format("%m/%d/%Y %I:%M:%S %p");
		m_editNotes.GetWindowText(strNotes); 
		m_editAddNotes.GetWindowText(strAdditionalNotes);

		// format the note text
		if (strAdditionalNotes.GetLength() > 0)
		{
			strNotes += "\r\nAdditional notes added by " + CGlobals::GetUserFirstAndLastName() + " on: " + strDateTime + "\r\n";
			strNotes += strAdditionalNotes;
		}

		// be sure that we limit our text here...
		if (strNotes.GetLength() > CGlobals::iMAX_ORDER_NOTES)
		{
			strNotes = strNotes.Left(CGlobals::iMAX_ORDER_NOTES);
		}

		CString strScheduleNote = "";
		if (m_bEditing == false)
		{
			if (bSchedule)
			{
				strScheduleNote.Format("SCHEDULED FOR: %s %s\r\n", set.m_ScheduledDate.Format( "%Y/%m/%d" ), (set.m_ScheduledAM) ? "AM" : "PM");
			}
			else if (bUnschedule)
			{
				strScheduleNote = "UNSCHEDULED\r\n";
			}
			
			strNotes = strScheduleNote + strNotes;
		}

		set.m_NoteText = strNotes;

		// set the date/time this note was entered.
		if (m_bNewNote)
		{
			set.m_DateTimeEntered = COleDateTime(time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond()) ;
		}

		// go ahead and get the time filter string in case we need it below.
		CString strTimeFilter = strDateTime;

		set.m_SentViaXML = 0;
		set.SetFieldNull(&set.m_DateTimeSent);
		set.m_Deleted = 0;

		// update the record - this moves the record ptr to the first one.
		set.Update() ;

		if ( m_iId == -1 )
		{
			// we just added a new record and do not know what the m_iId is, so the next few lines
			// requery the recordset to find the record that was just added.  This is done by filtering
			// on the user id and date/time.
			
			set.m_strFilter.Format("OrderId = %d AND DateTimeEntered = '%s'", m_iOrderID, strTimeFilter);
			set.Requery();
			ASSERT( set.GetRecordCount() == 1 );
			m_iId = set.m_ID;
		}

		// we need to update the other POs that had their schedules modified with a note
		// saying what happened.
		POSITION pos = dlgSched.m_listPOsWithModifiedSchedules.GetHeadPosition();
		while (pos)
		{
			int iOrderID = dlgSched.m_listPOsWithModifiedSchedules.GetNext(pos);
			if (iOrderID != m_iOrderID)
			{
				CString strSQL = "";
				CString strSQLSafeNotes = set.m_NoteText;
				strSQLSafeNotes.Replace("'", "''");
				strSQL.Format("EXEC AddPONote %d, %d, %d, '%s', '%s', '%s', %d, %d, %d, %d, %d, '%s'", iOrderID, set.m_NoteTypeID,
					set.m_SpokeWithID, set.m_ContactName, set.m_DateTimeEntered.Format("%m/%d/%Y %H:%M:%S" ), strSQLSafeNotes, set.m_EnteredByUserID,
					set.m_CustomerToCallBack, set.m_Scheduled, set.m_UnScheduled, set.m_ScheduledAM, set.m_ScheduledDate.Format("%m/%d/%Y %H:%M:%S" ));
				TRY
				{
					g_dbFlooring.ExecuteSQL(strSQL);
				}
				CATCH(CDBException, e)
				{
					MessageBox(e->m_strError, "Error!");
				}
				END_CATCH
			}
		}
	
		set.Close() ;

		CSetCustomer setCustomer(&g_dbFlooring) ;
		setCustomer.m_strFilter.Format("CustomerID = '%d'", m_iCustomerID) ;
		setCustomer.Open() ;
		setCustomer.MoveFirst();
		setCustomer.Edit();
		m_editPhoneHome.GetWindowText(setCustomer.m_PhoneNumber);
		m_editPhoneWork.GetWindowText(setCustomer.m_WorkNumber);
		m_editPhoneMobile.GetWindowText(setCustomer.m_MobileNumber);
		m_editEmailAddress.GetWindowText(setCustomer.m_EmailAddress);
		setCustomer.Update();
		setCustomer.Close();		

		bValid = true;
	}
	else
	{
		bValid = true;
	}

	if (bValid)
	{
		FormatEmailBody();
	}

	return bValid;
}

int CDlgPONoteEntry::GetNoteTypeID()
{
	return m_comboNoteType.GetItemData(m_comboNoteType.GetCurSel());
}

CString CDlgPONoteEntry::GetNoteType()
{
	CString strText;
	m_comboNoteType.GetLBText(m_comboNoteType.GetCurSel(), strText);
	return strText;
}

int CDlgPONoteEntry::GetSpokeWithID()
{
	return m_comboSpokeWith.GetItemData(m_comboSpokeWith.GetCurSel());
}

bool CDlgPONoteEntry::FormatEmailBody()
{
	bool bFormatOK = true;

	ASSERT(m_iId != -1);

	CSetPONotes setNote(&g_dbFlooring);
	setNote.m_strFilter.Format("Id = '%d'", m_iId) ;
	setNote.Open() ;
	
	ASSERT( setNote.GetRecordCount() == 1 );
	
	CString strTemp;
	if (GetNoteTypeID() == iMANAGER_ACTION_ID)
	{
		m_strEmailBody =  "MANAGER'S ACTION REQUIRED!\n\n";
	}
	else
	{
		m_strEmailBody =  "PO Note\n\n";
	}
	m_strEmailBody += "Customer: " + m_strCustomerName + "\n";
	strTemp.Format("Store/PO - %s / %s (Internal Order Number = %d)\n", m_strStoreNumber, m_strPONumber, m_iOrderID);
	m_strEmailBody += strTemp;
	strTemp.Format("Note Entered: %s\n\n", setNote.m_DateTimeEntered.Format("%m/%d/%y %H:%M:%S"));
	m_strEmailBody += strTemp;

	m_strEmailBody += "Comments:\n\n";
	m_strEmailBody += setNote.m_NoteText;

	return bFormatOK;
}

bool CDlgPONoteEntry::HasAlerts()
{
	return (CGlobals::OrderHasAlerts(m_iOrderID, false) || (CGlobals::OrderIsReviewed(m_iOrderID) == false));
}

bool CDlgPONoteEntry::AllowSchedulingWithAlerts()
{
	bool bAllow = false;
	CSetSettings setSettings(&g_dbFlooring);
	if (setSettings.GetValueLong("AllowSchedulingWithAlerts") == 1)
	{
		bAllow = true;
	}
	
	return bAllow;
}

void CDlgPONoteEntry::OnCbnSelchangePonoteComboSpokewith()
{
	OnChange();
	EnableOther();
	ShowScheduleControlsByNoteType();
}

void CDlgPONoteEntry::EnableOther()
{
	CString strTemp = "";
	m_comboSpokeWith.GetLBText(m_comboSpokeWith.GetCurSel(), strTemp);
	
	if (strTemp.MakeUpper().Find("OTHER") != -1)
	{
		m_editSpokeWithOther.EnableWindow();
	}
	else
	{
		m_editSpokeWithOther.EnableWindow(FALSE);
	}
}

void CDlgPONoteEntry::OnBnClickedScheduled()
{
	OnChange();
	if (m_btnScheduled.GetCheck() == BST_CHECKED)
	{
		m_btnUnscheduled.SetCheck(BST_UNCHECKED);
		ShowScheduleControls(true);
	}
	else
	{
		ShowScheduleControls(false);
	}
}

void CDlgPONoteEntry::OnBnClickedUnscheduled()
{
	OnChange();
	if (m_btnUnscheduled.GetCheck() == BST_CHECKED)
	{
		m_btnScheduled.SetCheck(BST_UNCHECKED);
		ShowScheduleControls(false);
	}
}

void CDlgPONoteEntry::EnableScheduleBox(bool bEnable)
{
	if (bEnable)
	{
		m_btnScheduled.EnableWindow();
		m_btnUnscheduled.EnableWindow();
		m_stScheduleGroup.EnableWindow();
		m_dtScheduledDate.EnableWindow();
		m_btnAM.EnableWindow();
		m_btnPM.EnableWindow();
		m_stScheduleStart.EnableWindow();
		m_stScheduleEnd.EnableWindow();
		m_ScheduleEndDate.EnableWindow();
	}
	else
	{
		m_btnScheduled.EnableWindow(FALSE);
		m_btnUnscheduled.EnableWindow(FALSE);
		m_stScheduleGroup.EnableWindow(FALSE);
		m_dtScheduledDate.EnableWindow(FALSE);
		m_btnAM.EnableWindow(FALSE);
		m_btnPM.EnableWindow(FALSE);
		m_stScheduleStart.EnableWindow(FALSE);
		m_stScheduleEnd.EnableWindow(FALSE);
		m_ScheduleEndDate.EnableWindow(FALSE);
	}
}

void CDlgPONoteEntry::ShowScheduleBox(bool bShow)
{
	if (bShow && m_bCanSchedule)
	{
		m_btnScheduled.ShowWindow(SW_SHOW);
		m_btnUnscheduled.ShowWindow(SW_SHOW);
		//m_stScheduleGroup.ShowWindow(SW_SHOW);
		m_stScheduleText.ShowWindow(SW_HIDE);
	}
	else
	{
		m_btnScheduled.ShowWindow(SW_HIDE);
		m_btnUnscheduled.ShowWindow(SW_HIDE);
		//m_stScheduleGroup.ShowWindow(SW_HIDE);
		m_stScheduleText.ShowWindow(SW_SHOW);
	}

	ShowScheduleControls(bShow);
}

void CDlgPONoteEntry::ShowScheduleControls(bool bShow)
{
	if (bShow && m_bCanSchedule)
	{	
		m_dtScheduledDate.ShowWindow(SW_SHOW);
		m_ScheduleEndDate.ShowWindow(SW_SHOW);
		m_btnAM.ShowWindow(SW_SHOW);
		m_btnPM.ShowWindow(SW_SHOW);
		m_stScheduleStart.ShowWindow(SW_SHOW);
		m_stScheduleEnd.ShowWindow(SW_SHOW);
	}
	else
	{
		m_dtScheduledDate.ShowWindow(SW_HIDE);
		m_ScheduleEndDate.ShowWindow(SW_HIDE);
		m_btnAM.ShowWindow(SW_HIDE);
		m_btnPM.ShowWindow(SW_HIDE);
		m_stScheduleStart.ShowWindow(SW_HIDE);
		m_stScheduleEnd.ShowWindow(SW_HIDE);
	}
}

void CDlgPONoteEntry::OnEnChangePonoteNotes()
{
	OnChange();
}

void CDlgPONoteEntry::OnChange() 
{
	m_bDirty = true ;
}
void CDlgPONoteEntry::OnBnClickedAm()
{
	OnChange();
}

void CDlgPONoteEntry::OnBnClickedPm()
{
	OnChange();
}

void CDlgPONoteEntry::OnBnClickedCustToCall()
{
	OnChange();
}

void CDlgPONoteEntry::OnEnChangePonotesNotesadd()
{
	OnChange();
}

void CDlgPONoteEntry::OnDtnDatetimechangeDateSchedule(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	OnChange();
	OnChangeDate();
	*pResult = 0;
}

void CDlgPONoteEntry::EnableButtons(int iNoteTypeID)
{
	CSetNoteTypes setNoteType(&g_dbFlooring);
	setNoteType.m_strFilter.Format("ID = '%d'", iNoteTypeID);
	setNoteType.Open();
	if (!setNoteType.IsEOF())
	{
		bool bEnable = true;
		if (TRUE == setNoteType.m_PermissionRequiredToSelect)
		{
			bEnable = false;
			CString strPermissionName;
			CString strTemp = setNoteType.m_NoteTypeDescription;
			strTemp.Remove(' ');
			strPermissionName.Format("CanSelectNoteType_%s", strTemp);
			if (CGlobals::HasPermission(strPermissionName))
			{
				bEnable = true;
			}
		}
		
		if (bEnable)
		{
			m_btnOK.EnableWindow();
			m_btnSaveAndEmail.EnableWindow();
		}
	}
	else
	{
		m_btnOK.EnableWindow(FALSE);
		m_btnSaveAndEmail.EnableWindow(FALSE);
	}
	setNoteType.Close();
}

void CDlgPONoteEntry::OnBnClickedPonoteSaveandemailButton()
{
	CString strError = "";
	bool bOK = false;
	if (Validate())
	{
		int iNoteTypeID = GetNoteTypeID();
		CSelectMailRecipientsDlg dlgRecipients;
		if (iNoteTypeID == iMANAGER_ACTION_ID)
		{
			dlgRecipients.IncludeStoreManagement(m_strStoreNumber);
		}

		int iResponse = dlgRecipients.DoModal();
		
		if ( iResponse == IDOK )
		{
			CString strTo = dlgRecipients.GetRecipientAddresses();
			CString strFrom = CGlobals::GetCurrentUserSMTPEmailAddress();
			CString strReplyToAddr = CGlobals::GetCurrentUserReplyToEmailAddress();
			CString strPassword = CGlobals::GetUserEmailPassword();
			CString strSubject = "";
			CString strError = "";

			if (iNoteTypeID == iMANAGER_ACTION_ID)
			{
				strSubject.Format("ACTION REQUIRED - PO: %s (Store %s)", m_strPONumber, m_strStoreNumber);
			}
			else
			{
				strSubject = _T("PO Note - Customer: ") + m_strCustomerName;
			}			

			bool bSendOK = false;
			{
				CWaitCursor cursor;
				bSendOK = CGlobals::SendEmail(strTo, strFrom, strPassword, strFrom, strReplyToAddr, strSubject, m_strEmailBody, strError);
			}

			if ( bSendOK )
			{
				bOK = true;
			}
			else
			{
				if (strError.GetLength() > 0)
				{
					MessageBox(strError, "Error!");
				}				
			}
		}
		else
		{
			if ((iResponse == IDCANCEL) || (iResponse == IDABORT))
			{
				bOK = true;  // not really an error
			}
			else
			{
				strError = "There was an error related to the Select Mail Recipients dialog box.  No mail was sent.";
				MessageBox(strError, "Error!");
			}
		}

		if (m_bAskToSend)
		{
			CDlgSendNote dlgSendNote;
				
			dlgSendNote.ShowCopyToSASM(true);
			dlgSendNote.ShowCopyToExpeditorEmail(true);

			if (dlgSendNote.DoModal() == IDOK)
			{
				m_bSendToExpeditor = true;
				m_bCopyToSASM = (dlgSendNote.m_CopyNoteToSASM == TRUE);
				m_bCopyToExpeditorEmail = (dlgSendNote.m_CopyNoteToExpeditorEmail == TRUE);
			}
		}

		CDialog::OnOK();			
	}
}

void CDlgPONoteEntry::OnChangeDate()
{
	COleDateTime dtStart;
	COleDateTime dtEnd;

	m_dtScheduledDate.GetTime(dtStart);
	m_ScheduleEndDate.SetTime(dtStart);
}

void CDlgPONoteEntry::OnEnHomePhoneChange()
{
	OnChange();
}


void CDlgPONoteEntry::OnEnWorkPhoneChange()
{
	OnChange();
}


void CDlgPONoteEntry::OnEnMobilePhoneChange()
{
	OnChange();
}


void CDlgPONoteEntry::OnEnEmailAddressChange()
{
	OnChange();
}

void CDlgPONoteEntry::ConfigureSchedulingControls()
{
	// if there are alerts and we are not allowing scheduling with alerts, then disable the scheduled checkbox
	// to disallow scheduling
	if (HasAlerts() && (false == AllowSchedulingWithAlerts()))
	{
		m_bCanSchedule = false;
		ShowScheduleBox(false);
		m_stScheduleText.SetWindowText("Cannot schedule - PO has alerts!");
		m_stScheduleText.ShowWindow(SW_SHOW);
	}
}

void CDlgPONoteEntry::InitializeCustomerDetails()
{
	CSetCustomer setCustomer(&g_dbFlooring) ;
	setCustomer.m_strFilter.Format("CustomerID = '%d'", m_iCustomerID) ;
	setCustomer.Open() ;

	ConfigureTitleBar(setCustomer);
	InitializeCustomerContactFields(setCustomer);

	UpdateData(FALSE);
	setCustomer.Close() ;
}

void CDlgPONoteEntry::ConfigureTitleBar(CSetCustomer &setCustomer)
{
	// set up title bar of dialog	
	CString strTemp;
	m_strCustomerName.Format("%s, %s", setCustomer.m_LastName, setCustomer.m_FirstName) ;
	strTemp.Format("Notes - %s -- P.O. %s / %s", m_strCustomerName, m_strStoreNumber, m_strPONumber);
	SetWindowText(strTemp) ;
}

void CDlgPONoteEntry::InitializeCustomerContactFields(CSetCustomer &setCustomer)
{
	m_strSiteAddress.Format("%s\r\n%s, %s  %s", setCustomer.m_Address, setCustomer.m_City, setCustomer.m_State, setCustomer.m_ZipCode) ;

	m_editPhoneHome.SetMask(_T("(###)###-####")) ;		
	m_editPhoneHome.SetPromptSymbol(' ');
	m_editPhoneHome.SetWindowText(setCustomer.m_PhoneNumber);

	m_editPhoneWork.SetMask(_T("(###)###-#### Ext. #####")) ;
	m_editPhoneWork.SetPromptSymbol(' ');
	m_editPhoneWork.SetWindowText(setCustomer.m_WorkNumber);

	m_editPhoneMobile.SetMask(_T("(###)###-####")) ;
	m_editPhoneMobile.SetPromptSymbol(' ');
	m_editPhoneMobile.SetWindowText(setCustomer.m_MobileNumber);

	m_editEmailAddress.SetLimitText(255);
	m_editEmailAddress.SetWindowText(setCustomer.m_EmailAddress);
}

void CDlgPONoteEntry::InitializeControlsForNewNote()
{
	// assume we are adding a new note - only fields that should be enabled first is NoteType combo and 
	// the main edit box
	m_comboNoteType.EnableWindow();
	m_editNotes.SetReadOnly(FALSE);
	m_comboSpokeWith.EnableWindow(FALSE);
	m_editSpokeWithOther.EnableWindow(FALSE) ;
	m_editNotes.SetLimitText(CGlobals::iMAX_ORDER_NOTES) ;
	m_editAddNotes.SetReadOnly();
	m_btnCustCallback.EnableWindow(FALSE);
	m_btnOK.EnableWindow(FALSE);
	m_btnSaveAndEmail.EnableWindow(FALSE);
	m_stScheduleText.ShowWindow(SW_HIDE);

	m_editSpokeWithOther.SetLimitText(50);   // no more characters than are allowed in the DB.
	m_editNotes.SetLimitText(CGlobals::iMAX_ORDER_NOTES);
}

void CDlgPONoteEntry::InitializeCustomerAndPOFields( CSetOrders &setOrders )
{
	// init customer id if not already done
	if (m_iCustomerID == -1)
	{
		if (!setOrders.IsEOF())
		{
			m_iCustomerID = setOrders.m_CustomerID;
			m_strPONumber = setOrders.m_PurchaseOrderNumber;
			m_strStoreNumber = CGlobals::StoreNumberFromStoreID(setOrders.m_StoreID);
		}
	}
}

void CDlgPONoteEntry::InitializeScheduleDateField( CSetOrders &setOrders )
{
	CString strTemp;
	if (setOrders.m_Scheduled)
	{
		strTemp.Format("%s %s", setOrders.m_ScheduleStartDate.Format( "%Y/%m/%d" ), (setOrders.m_ScheduledAM) ? "AM" : "PM");
	}
	else
	{
		strTemp = "NOT SCHEDULED";
	}
	m_stCurrentScheduleDate.SetWindowText(strTemp);
}

void CDlgPONoteEntry::InitializeFieldsForExistingNote()
{
	CSetPONotes setNotes(&g_dbFlooring);
	setNotes.m_strFilter.Format("ID = '%d'", m_iId);
	setNotes.Open();

	// show all items in the list since we are editing a note
	m_comboNoteType.PopulateList(true);

	// need to disable the note type dropdown
	m_comboNoteType.EnableWindow(FALSE);

	if(!setNotes.IsEOF())
	{
		// set Note Type combo box
		int iNumEntries = m_comboNoteType.GetCount();
		int iIndex = 0;
		for (iIndex = 0; iIndex < iNumEntries; iIndex++)
		{
			if ((DWORD)setNotes.m_NoteTypeID == m_comboNoteType.GetItemData(iIndex))
			{
				m_comboNoteType.SetCurSel(iIndex);
				break;
			}
		}

		m_comboSpokeWith.PopulateList(setNotes.m_NoteTypeID);

		// set SpokeWith combo box
		iNumEntries = m_comboSpokeWith.GetCount();
		bool bFound = false;
		for (iIndex = 0; iIndex < iNumEntries; iIndex++)
		{
			if ((DWORD)setNotes.m_SpokeWithID == m_comboSpokeWith.GetItemData(iIndex))
			{
				bFound = true;
				m_comboSpokeWith.SetCurSel(iIndex);
				CString strTemp;
				m_comboSpokeWith.GetLBText(iIndex, strTemp);
				if (strTemp.MakeUpper().Find("OTHER") != -1)
				{
					m_editSpokeWithOther.SetWindowText(setNotes.m_ContactName);
				}
				break;
			}
		}

		if (!bFound)
		{
			m_comboSpokeWith.SetCurSel(m_comboSpokeWith.FindStringExact(1,"N/A"));
		}

		EnableScheduleBox(false);

		m_editNotes.SetWindowText(setNotes.m_NoteText);

		if (setNotes.m_CustomerToCallBack)
		{
			m_btnCustCallback.SetCheck(BST_CHECKED);
		}
		else
		{
			m_btnCustCallback.SetCheck(BST_UNCHECKED);
		}

		EnableButtons(GetNoteTypeID());
	}

	setNotes.Close();
}
