#include "stdafx.h"
#include "Flooring.h"
#include "GridStoreContacts.h"
#include "SetViewStoreContacts.h"
#include "SetDepartmentsStoresAssignments.h"
#include "SetStoreContacts.h"
#include "DlgSelectDepartment.h"
#include "SetVwDepartmentsContactTitles.h"
#include "OXRegExpression.h"
#include "DlgStore.h"

CGridStoreContacts::CGridStoreContacts(void) : m_setDepartments(&g_dbFlooring)
{
//	m_setContactTitles.m_strSort.Format("Title");
//	m_setContactTitles.Open();
	m_setDepartments.Open();

	m_aszFAX_STRINGS[NO_FAX] = "NO FAX";
	m_aszFAX_STRINGS[FAX] = "FAX";
	m_aszFAX_STRINGS[ALT_FAX] = "ALT FAX";
	m_aszFAX_STRINGS[TRY_BOTH] = "TRY BOTH";

	m_iNumRowsPerEntry = (options_rowoffset_LAST < contact_rowoffset_LAST) ? contact_rowoffset_LAST : options_rowoffset_LAST;
}

CGridStoreContacts::~CGridStoreContacts(void)
{
}

void CGridStoreContacts::OnSetup()
{
	CCFGrid::OnSetup() ;
	SetHighlightRow(FALSE);
	SetCurrentCellMode(1);

	AddColumn(" ID  ", DEPARTMENTSSTORESASSIGNMENTID);
	AddColumn(" ", STORECONTACTID);
	AddColumn("    Dept.    ", DEPARTMENT);
	AddColumn("          Title          ", TITLE);
	AddColumn("   First Name   ", FIRST_NAME);
	AddColumn("   Last Name    ", LAST_NAME);
	AddColumn("Contact Info", CONTACT_INFO);
	AddColumn("                         ", CONTACT_INFO_1);
	AddColumn("      Options      ", OPTIONS);
	AddColumn("           ", OPTIONS_1);

	InitColumnHeadings();

	EnableMenu(TRUE) ;
	EnableExcelBorders(TRUE) ;

	CUGCell cell;

	GetColDefault(DEPARTMENTSSTORESASSIGNMENTID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(DEPARTMENTSSTORESASSIGNMENTID, &cell) ;

	GetColDefault(STORECONTACTID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(STORECONTACTID, &cell) ;

	GetColDefault(DEPARTMENT, &cell) ;
	//cell.SetCellType(UGCT_DROPLIST);
	SetColDefault(DEPARTMENT, &cell);

	GetColDefault(TITLE, &cell) ;
	cell.SetCellType(UGCT_DROPLIST);
	SetColDefault(TITLE, &cell);

	HideColumn(STORECONTACTID);
	HideColumn(DEPARTMENTSSTORESASSIGNMENTID);	

	// Create a mask edit to use with ultimate grid mask edit
	m_editPhone.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,32002);
	m_editPhone.m_ctrl = this;
	
	m_editFax.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,32003);
	m_editFax.m_ctrl = this;

	JoinCells(CONTACT_INFO, -1, CONTACT_INFO_1, -1);
	JoinCells(OPTIONS, -1, OPTIONS_1, -1);

}

void CGridStoreContacts::OnDrawFocusRect(CDC *dc,RECT *rect)
{
    CCFGrid::OnDrawFocusRect(dc, rect);
}

void CGridStoreContacts::OnDClicked(int col,long row, RECT *rect, POINT *point, BOOL processed)
{
	UNREFERENCED_PARAMETER(processed);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(row);
	switch(col)
	{
		case FIRST_NAME :
		case LAST_NAME :
		case CONTACT_INFO_1:
			{
				StartEdit();
			}
			break;
	}
}

void CGridStoreContacts::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
}

int CGridStoreContacts::OnCellTypeNotify(long ControlID, int col, long row, long msg, long param)
{
	UNREFERENCED_PARAMETER(ControlID);
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(param);
	return TRUE ;
}

int CGridStoreContacts::OnEditStart(int col, long row, CWnd **edit)
{
	int bEdit = FALSE ;

	if ((row >= 0) && (col >= 0) )
	{

		CUGCell cell ;
		GetCell(col, row, &cell) ;

		switch (col)
		{
			case FIRST_NAME:
			case LAST_NAME:
				{
					CUGEdit* editClass = (CUGEdit*)this->GetEditClass();
					editClass->LimitText(200);
					//editClass->ModifyStyle(0, ES_UPPERCASE);
					bEdit = TRUE ;
				}
				break ;
			case CONTACT_INFO_1:
				{
					CString strTemp = QuickGetText(CONTACT_INFO, row);
					if (strTemp.Find("Phone") > -1)
					{
                        *edit = &m_editPhone;
						bEdit = TRUE ;
					}
					else if (strTemp.Find("Fax") > -1)
					{
						*edit = &m_editFax;
						bEdit = TRUE ;
					}
					else if (strTemp.Find("E-mail") > -1)
					{
						CUGEdit* editClass = (CUGEdit*)this->GetEditClass();
						editClass->LimitText(200);
						//editClass->ModifyStyle(0, ES_UPPERCASE);
						bEdit = TRUE ;
					}
				}
				break;
		}
	}

	return bEdit ;
}

int CGridStoreContacts::OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag) 
{
	UNREFERENCED_PARAMETER(edit);
	bool bChanged = false;
	CString tempstr(string);
	CString tempstr2;
	CUGCell cell;
	GetCellIndirect(col, row, &cell);
	CString strOld;
	if (cell.GetDataType() == UGCELLDATA_STRING)
	{
		strOld = QuickGetText(col, row);
		bChanged = strOld != tempstr;
	}

	CDlgStore* pwnd = (CDlgStore*) GetParent();
	bool bCancelButtonHasFocus = pwnd->CancelButtonHasFocus();
	if (bCancelButtonHasFocus || cancelFlag)
	{
		if (bChanged)
		{
			int iResponse = MessageBox("Changes have been made - cancel changes?", "Notice", MB_YESNO);
			if (iResponse == IDYES)
			{
				if (bCancelButtonHasFocus)
				{
					::PostMessage(GetParent()->m_hWnd, WM_CLOSE, 0, 0);
				}
				return CCFGrid::OnEditFinish(col, row, edit, string, TRUE);
			}
		}
	}
	
	BOOL bAllowChanges = TRUE;

	bool bFaxValid = false;
	bool bAltFaxValid = false;
	if (col == CONTACT_INFO_1)
	{
		CString strTemp = QuickGetText(CONTACT_INFO, row);
		if (strTemp.Find("Alt. Fax") > -1)
		{
			bAltFaxValid = ValidateFaxNumber(tempstr);
			if (false == bAltFaxValid)
			{
				MessageBox("Invalid Fax Number!", "Error!");
				bAllowChanges = FALSE;
			}
			tempstr2 = QuickGetText(col, row-1);
			bFaxValid = ValidateFaxNumber(tempstr2);
			UpdateFaxToDropDown(bFaxValid, bAltFaxValid, (row / m_iNumRowsPerEntry) * m_iNumRowsPerEntry);
		}
		else if (strTemp.Find("Fax") > -1)
		{
			bFaxValid = ValidateFaxNumber(tempstr);
			if (false == bFaxValid)
			{
				MessageBox("Invalid Fax Number!", "Error!");
				bAllowChanges = FALSE;
			}
			tempstr2 = QuickGetText(col, row+1);
			bAltFaxValid = ValidateFaxNumber(tempstr2);
			UpdateFaxToDropDown(bFaxValid, bAltFaxValid, (row / m_iNumRowsPerEntry) * m_iNumRowsPerEntry);
		}
		else if (strTemp.Find("E-mail") > -1)
		{
			if (false == ValidateEmailAddress(tempstr))
			{
				MessageBox("Invalid Email Address!", "Error!");
				bAllowChanges = FALSE;
			}
		}
	}

	return bAllowChanges;
}

void CGridStoreContacts::UpdateFaxToDropDown(bool bFaxValid, bool bAltFaxValid, long ContactRowNumber)
{
	CString strChoices = m_aszFAX_STRINGS[NO_FAX] + CString("\n");

	CString strCurrentChoice = m_aszFAX_STRINGS[NO_FAX];
	QuickGetText(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, &strCurrentChoice);

	if (!bFaxValid && !bAltFaxValid)
	{
		QuickSetText(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, m_aszFAX_STRINGS[NO_FAX]);
		QuickSetReadOnly(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, true);
	}
	else
	{
		if (bFaxValid)
		{
			strChoices += m_aszFAX_STRINGS[FAX] + CString("\n");
		}

		if (bAltFaxValid)
		{
			strChoices += m_aszFAX_STRINGS[ALT_FAX] + CString("\n");
		}

		if (bFaxValid && bAltFaxValid)
		{
			strChoices += m_aszFAX_STRINGS[TRY_BOTH]  + CString("\n");
		}

		CUGCell cell;
		GetCell(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, &cell);
		cell.SetLabelText(strChoices);
		cell.SetCellType(UGCT_DROPLIST);
		SetCell(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, &cell);

		if (strChoices.Find(strCurrentChoice) != -1)
		{
			QuickSetText(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, strCurrentChoice);
		}
		else
		{
			QuickSetText(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, m_aszFAX_STRINGS[NO_FAX]);
		}

		QuickSetReadOnly(OPTIONS_1, ContactRowNumber + options_rowoffset_FAX_STATUS, false);
	}
}

void CGridStoreContacts::Update()
{
	ASSERT(FALSE);
	EnableUpdate(FALSE);
	
	// get rid of stale data
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetViewStoreContacts setStoreContacts(&g_dbFlooring) ;
	setStoreContacts.m_strFilter.Format("StoreID = %d", m_iStoreID) ;
	setStoreContacts.m_strSort.Format("DepartmentName, Title");
	setStoreContacts.Open() ;

	while (!setStoreContacts.IsEOF())
	{
		long lRow = InsertRow(setStoreContacts.m_DepartmentID) ;
		CUGCell cell ;

		CString strTemp ;
		strTemp.Format("%d", setStoreContacts.m_DepartmentStoreID) ;
		QuickSetText(DEPARTMENTSSTORESASSIGNMENTID, lRow, strTemp) ;

		strTemp.Format("%d", setStoreContacts.m_StoreContactsID) ;
		QuickSetText(STORECONTACTID, lRow, strTemp) ;
		setStoreContacts.MoveNext();
	}

	setStoreContacts.Close();

	EnableUpdate(TRUE);
	RedrawAll() ;
}

int CGridStoreContacts::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		if (CGlobals::HasPermission("CanAddStoreContact"))
		{
			AddMenuItem(NEW_CONTACT, "New");
		}

		if ((row >= 0) && (row < GetNumberRows()))
		{
			if (CGlobals::HasPermission("CanDeleteContact"))
			{
				AddMenuItem(DELETE_CONTACT, "Delete");
			}
		}
		
	}
	return TRUE ;
}

void CGridStoreContacts::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case NEW_CONTACT:
			AddNewContact();
			break;
		case DELETE_CONTACT:
			DeleteContact(row);
			break;

		default:
			break ;
		}
	}
}

void CGridStoreContacts::DeleteContact(long row)
{
	int iResponse = MessageBox("Are you sure you wish to delete this contact? (this operation cannot be undone.)", "Question", MB_YESNO);
	if (iResponse == IDYES)
	{
		EnableUpdate(FALSE);
		DeleteRow(row);
		EnableUpdate(TRUE);
	}

	RedrawAll();
}

void CGridStoreContacts::AddNewContact()
{
	CDlgSelectDepartment dlg;
	if (dlg.DoModal() == IDOK)
	{
		int iDeptID = dlg.GetDepartmentID();
		EnableUpdate(FALSE);
		InsertRow(iDeptID);
		EnableUpdate(TRUE);
	}
	
	RedrawAll();
}

void CGridStoreContacts::OnKillFocus(CWnd* pOldWnd )
{
	UNREFERENCED_PARAMETER(pOldWnd);
}

void CGridStoreContacts::UpdateRecordSet()
{
	long lContactRow ;

	CSetDepartmentsStoresAssignments setDeptStoresAssignments(&g_dbFlooring);
	setDeptStoresAssignments.m_strFilter = "ID = -1";
	setDeptStoresAssignments.Open();

	CSetStoreContacts setStoreContacts(&g_dbFlooring);
	setStoreContacts.m_strFilter = "ID = -1";
	setStoreContacts.Open();

	CSetDepartments setDepartments(&g_dbFlooring);
	setDepartments.m_strFilter = "ID = -1";
	setDepartments.Open();

	CSetContactTitles setTitles(&g_dbFlooring);
	setTitles.m_strFilter = "ID = -1";
	setTitles.Open();

	CString strDeptStoreAssignID = "";
	CString strStoreContactID = "";
	CString strTemp = "";
	int iNumRows = GetNumberRows();
	int iNumContacts = iNumRows / m_iNumRowsPerEntry;
	CUGCell cell;

	for (lContactRow = 0; lContactRow < iNumContacts; lContactRow++)
	{
		long lActualRow = lContactRow * m_iNumRowsPerEntry;

		strStoreContactID = QuickGetText(STORECONTACTID, lActualRow);
		
		// filter Department recordset
		strTemp = QuickGetText(DEPARTMENT, lActualRow);
		setDepartments.m_strFilter.Format("DepartmentName = '%s'", strTemp);
		setDepartments.Requery();

		// filter ContactTitles recordset
		strTemp = QuickGetText(TITLE, lActualRow);
		setTitles.m_strFilter.Format("Title = '%s'", strTemp);
		setTitles.Requery();

		// Update the DeptStoresAssignments table
		setDeptStoresAssignments.m_strFilter.Format("StoreID = %d AND DepartmentID = %d", m_iStoreID, setDepartments.m_ID);
		setDeptStoresAssignments.Requery();
		if (setDeptStoresAssignments.IsEOF())
		{
			// adding new dept. store assignment
			setDeptStoresAssignments.AddNew();
			setDeptStoresAssignments.m_StoreID = m_iStoreID;
			setDeptStoresAssignments.m_DepartmentID = setDepartments.m_ID;
		}
		else
		{
			// else we just edit what is there
			setDeptStoresAssignments.Edit();
		}

		setDeptStoresAssignments.m_FaxNumber = QuickGetText(CONTACT_INFO_1, lActualRow+contact_rowoffset_FAX1);
		setDeptStoresAssignments.m_AltFaxNumber = QuickGetText(CONTACT_INFO_1, lActualRow+contact_rowoffset_FAX2);
		setDeptStoresAssignments.m_FaxStatusReportTo = GetFaxToID(QuickGetText(OPTIONS_1, lActualRow+options_rowoffset_FAX_STATUS));
		
		setDeptStoresAssignments.Update();		
		
		// update contact info
		setStoreContacts.m_strFilter.Format("ID = %s", strStoreContactID.GetLength() > 0 ? strStoreContactID : "-1");
		setStoreContacts.Requery();
		if (!setStoreContacts.IsEOF())
		{
			// existing
			setStoreContacts.Edit();
		}
		else
		{
			// must be new
			setStoreContacts.AddNew();
		}

		setStoreContacts.m_StoreID = m_iStoreID;

		if (!setDepartments.IsEOF())
		{
			setStoreContacts.m_DepartmentID = setDepartments.m_ID;
		}

		setStoreContacts.m_FirstName = QuickGetText(FIRST_NAME, lActualRow);
		setStoreContacts.m_LastName = QuickGetText(LAST_NAME, lActualRow);

		if (!setTitles.IsEOF())
		{
			setStoreContacts.m_TitleID = setTitles.m_ID;
		}

		setStoreContacts.m_PhoneNumber = QuickGetText(CONTACT_INFO_1, lActualRow+contact_rowoffset_PHONE);
		setStoreContacts.m_AltPhoneNumber = QuickGetText(CONTACT_INFO_1, lActualRow+contact_rowoffset_ALTPHONE);
		setStoreContacts.m_EmailAddress = QuickGetText(CONTACT_INFO_1, lActualRow+contact_rowoffset_EMAIL);
		setStoreContacts.m_EmailStatusReport = QuickGetBool(OPTIONS_1, lActualRow+options_rowoffset_EMAIL_STATUS);

		setStoreContacts.Update();

	}

	DeleteRecordList(setStoreContacts, "ID = %s", "");

	setStoreContacts.Close();
	setDepartments.Close();
	setTitles.Close();
	setDeptStoresAssignments.Close();
}

void CGridStoreContacts::UpdateGrid()
{
	EnableUpdate(FALSE);

	CSetViewStoreContacts setStoreContacts(&g_dbFlooring) ;
	setStoreContacts.m_strFilter.Format("StoreID = %d", m_iStoreID) ;
	setStoreContacts.m_strSort.Format("DepartmentName, Title");
	setStoreContacts.Open() ;

	while (!setStoreContacts.IsEOF())
	{
		long lRow = InsertRow(setStoreContacts.m_DepartmentID) ;
		CUGCell cell ;

		for (int iCount = 0; iCount < m_iNumRowsPerEntry; iCount++)
		{
			QuickSetNumber(DEPARTMENTSSTORESASSIGNMENTID, lRow+iCount, setStoreContacts.m_DepartmentStoreID);
			QuickSetNumber(STORECONTACTID, lRow+iCount, setStoreContacts.m_StoreContactsID);
		}
		
		QuickSetText(DEPARTMENT, lRow, setStoreContacts.m_DepartmentName);
		QuickSetText(TITLE, lRow, setStoreContacts.m_Title);
		QuickSetText(LAST_NAME, lRow, setStoreContacts.m_LastName);
		QuickSetText(FIRST_NAME, lRow, setStoreContacts.m_FirstName);

		QuickSetText(CONTACT_INFO_1, lRow+contact_rowoffset_EMAIL, setStoreContacts.m_EmailAddress);
		QuickSetText(CONTACT_INFO_1, lRow+contact_rowoffset_PHONE, setStoreContacts.m_PhoneNumber);
		QuickSetText(CONTACT_INFO_1, lRow+contact_rowoffset_ALTPHONE, setStoreContacts.m_PhoneNumber);
		QuickSetText(CONTACT_INFO_1, lRow+contact_rowoffset_FAX1, setStoreContacts.m_FaxNumber);
		QuickSetText(CONTACT_INFO_1, lRow+contact_rowoffset_FAX2, setStoreContacts.m_AltFaxNumber);

		if (!setStoreContacts.IsFieldNull(&setStoreContacts.m_FaxStatusReportTo))
		{
			QuickSetText(OPTIONS_1, lRow + options_rowoffset_FAX_STATUS, GetFaxToString(setStoreContacts.m_FaxStatusReportTo));
		}
		else
		{
			QuickSetText(OPTIONS_1, lRow + options_rowoffset_FAX_STATUS, GetFaxToString(NO_FAX));
		}

		if (!setStoreContacts.IsFieldNull(&setStoreContacts.m_EmailStatusReport))
		{
			QuickSetBool(OPTIONS_1, lRow + options_rowoffset_EMAIL_STATUS, (setStoreContacts.m_EmailStatusReport == TRUE));
		}
		else
		{
			QuickSetBool(OPTIONS_1, lRow + options_rowoffset_EMAIL_STATUS, FALSE);
		}

		bool bFaxValid = ValidateFaxNumber(CONTACT_INFO_1, lRow+contact_rowoffset_FAX1);
		bool bAltFaxValid = ValidateFaxNumber(CONTACT_INFO_1, lRow+contact_rowoffset_FAX2);
		
		UpdateFaxToDropDown(bFaxValid, bAltFaxValid, lRow);

		//if (!setStoreContacts.IsFieldNull(&setStoreContacts.m_EmailStatusReport))
		//{
		//	QuickSetBool(EMAIL_STATUS_REPORT, lRow, (setStoreContacts.m_EmailStatusReport == TRUE));
		//}

		/*if (!setStoreContacts.IsFieldNull(&setStoreContacts.m_EmailStatusReportTo))
		{
			QuickSetText(EMAIL_ADDRESSES, lRow, setStoreContacts.m_EmailStatusReportTo);
		}*/

		setStoreContacts.MoveNext();
	}

	setStoreContacts.Close();

	EnableUpdate(TRUE);
	RedrawAll();

}

void CGridStoreContacts::InitRow(long lRow, int iDeptID)
{
	CUGCell cell ;

	GetColDefault(DEPARTMENTSSTORESASSIGNMENTID, &cell) ;
	cell.SetText("");
	for (int iCount = 0; iCount < m_iNumRowsPerEntry; iCount++)
	{
		SetCell(DEPARTMENTSSTORESASSIGNMENTID, lRow+iCount, &cell);
		SetCell(STORECONTACTID, lRow+iCount, &cell);
	}

	GetColDefault(DEPARTMENT, &cell) ;
	if (iDeptID != -1)
	{
		m_setDepartments.m_strFilter.Format("ID = %d", iDeptID);
		m_setDepartments.Requery();
		cell.SetText(m_setDepartments.m_DepartmentName);
	}

	SetCell(DEPARTMENT, lRow, &cell) ;	

	cell.SetBackColor(RGB(245,245,245));
	cell.SetText("");
	cell.SetReadOnly(TRUE);
	SetCell(DEPARTMENT, lRow+1, &cell);
	
	GetColDefault(TITLE, &cell);
	CString strChoices = "";

	CSetVwDepartmentsContactTitles setDeptContactTitles(&g_dbFlooring);
	setDeptContactTitles.m_strFilter.Format("DepartmentID = %d", iDeptID);
	setDeptContactTitles.m_strSort = "Title";
	setDeptContactTitles.Open();
	while (!setDeptContactTitles.IsEOF())
	{
		strChoices += setDeptContactTitles.m_Title;
		strChoices += "\n" ;
		setDeptContactTitles.MoveNext() ;
	}
	setDeptContactTitles.Close();

	cell.SetLabelText(strChoices);
	SetCell(TITLE, lRow, &cell);
	
	cell.SetCellType(UGCT_NORMAL);
	cell.SetBackColor(RGB(245,245,245));
	SetCell(TITLE, lRow+1, &cell);
		
	GetColDefault(LAST_NAME, &cell);
	SetColDefault(LAST_NAME, &cell);
	SetColDefault(FIRST_NAME, &cell) ;
	cell.SetBackColor(RGB(245,245,245));
	SetCell(FIRST_NAME, lRow+1, &cell);
	SetCell(LAST_NAME, lRow+1, &cell);

	JoinCells(DEPARTMENT, lRow+1, LAST_NAME,  lRow+m_iNumRowsPerEntry-1);

	GetColDefault(CONTACT_INFO, &cell);
	cell.SetReadOnly(TRUE);
	SetColDefault(CONTACT_INFO, &cell);

	QuickSetText(CONTACT_INFO, lRow, "E-mail");
	QuickSetText(CONTACT_INFO, lRow + contact_rowoffset_PHONE, "Phone");
	QuickSetText(CONTACT_INFO, lRow + contact_rowoffset_ALTPHONE, "Alt. Phone");
	QuickSetText(CONTACT_INFO, lRow + contact_rowoffset_FAX1, "Fax");
	QuickSetText(CONTACT_INFO, lRow + contact_rowoffset_FAX2, "Alt. Fax");
	
	QuickSetMask(CONTACT_INFO_1, lRow + contact_rowoffset_PHONE, _T("(###) ###-#### Ext. ####"));
	QuickSetMask(CONTACT_INFO_1, lRow + contact_rowoffset_ALTPHONE, _T("(###) ###-#### Ext. ####"));
	QuickSetMask(CONTACT_INFO_1, lRow + contact_rowoffset_FAX1, _T("(###) ###-####"));
	QuickSetMask(CONTACT_INFO_1, lRow + contact_rowoffset_FAX2, _T("(###) ###-####"));

	QuickSetText(OPTIONS, lRow + options_rowoffset_FAX_STATUS, "Fax Status Report");
	QuickSetText(OPTIONS, lRow + options_rowoffset_EMAIL_STATUS, "Email Status Report");

	GetCell(OPTIONS_1, lRow + options_rowoffset_FAX_STATUS, &cell);
	cell.SetCellType(UGCT_DROPLIST);
	strChoices = "";
	for (int iCount = 0; iCount < FAX_LAST; iCount++)
	{
		strChoices += CString(m_aszFAX_STRINGS[iCount]) + CString("\n");
	}
	cell.SetLabelText(strChoices);
	SetCell(OPTIONS_1, lRow + options_rowoffset_FAX_STATUS, &cell);

	GetCell(OPTIONS_1, lRow + options_rowoffset_EMAIL_STATUS, &cell);
	cell.SetCellType(UGCT_CHECKBOX);
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK | UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER | UG_ALIGNVCENTER );
	SetCell(OPTIONS_1, lRow + options_rowoffset_EMAIL_STATUS, &cell);

	GetCell(OPTIONS, lRow + options_rowoffset_LAST, &cell);
	cell.SetBackColor(RGB(245,245,245));
	cell.SetReadOnly(TRUE);
	SetCell(OPTIONS, lRow + options_rowoffset_LAST, &cell);
	JoinCells(OPTIONS, lRow + options_rowoffset_LAST, OPTIONS_1, lRow + m_iNumRowsPerEntry-1);
	
    RedrawRow(lRow);

}

int CGridStoreContacts::AppendRow(int iDeptID)
{
	int iReturn = CCFGrid::AppendRow() ;

	if (iReturn == UG_SUCCESS)
	{
		long lRow = GetNumberRows() - 1;
		InitRow(lRow, iDeptID);
	}
		
	return iReturn ;
}

long CGridStoreContacts::InsertRow(int iDeptID)
{
	ASSERT(iDeptID != -1);

	long lNumRowsTotal = GetNumberRows();
	
	m_setDepartments.m_strFilter.Format("ID = %d", iDeptID);
	m_setDepartments.Requery();
	CString strDepartment = m_setDepartments.m_DepartmentName.Trim();
	
	bool bFound = false;
	CString strCurrent = "";
	long lInsertIndex = lNumRowsTotal;
	for (long lIndex = 0; lIndex < lNumRowsTotal; lIndex++)
	{
		QuickGetText(DEPARTMENT, lIndex, &strCurrent);
		if (strCurrent == strDepartment)
		{
			bFound = true;
		}
		else if (bFound && (strCurrent != strDepartment) && (strCurrent.GetLength() > 0))
		{
			lInsertIndex = lIndex;
			break;
		}
	}

	// insert enough rows to handle all the contact info
	int iReturn = UG_SUCCESS;
	for (int iCount = 0; iCount < m_iNumRowsPerEntry; iCount++)
	{
		iReturn += CCFGrid::InsertRow(lInsertIndex);
	}
		
	if (iReturn == UG_SUCCESS)
	{
		InitRow(lInsertIndex, iDeptID);	  // sets up the rows and fills in contact labels
	}

	if (lInsertIndex > 0)
	{
		CUGCell cell;
		for (int iCount = 0; iCount < LAST; iCount++)
		{
			GetCell(iCount, lInsertIndex, &cell);
			cell.SetBorder(UG_BDR_TMEDIUM);
			SetCell(iCount, lInsertIndex, &cell);
		}
	}

	return lInsertIndex;
}

int CGridStoreContacts::DeleteRow(long lRow)
{
	// calculate the first row of this contact
	long lContactStartRow = (lRow / m_iNumRowsPerEntry) * m_iNumRowsPerEntry;

	CString strID = QuickGetText(STORECONTACTID, lContactStartRow) ;
	if (strID != "")
	{
		m_listRecord.AddHead(strID) ;
	}

	int iReturn = UG_SUCCESS;
	for (int iCount = 0; iCount < m_iNumRowsPerEntry; iCount++)
	{
        iReturn += CUGCtrl::DeleteRow(lContactStartRow) ;
	}

	return iReturn;
}

void CGridStoreContacts::OnTH_LClicked(int col, long row, int updn,RECT * rect, POINT * point, BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
}

bool CGridStoreContacts::ValidateFaxNumber(CString& strFaxNumber)
{
	bool bValid = false;

	if (strFaxNumber.GetLength() > 0)
	{
		strFaxNumber.Remove(' ');
		strFaxNumber.Trim();
		if (strFaxNumber.GetLength() == 13)
		{
			bValid = true;
		}
	}

	return bValid;
}

bool CGridStoreContacts::ValidateFaxNumber(int col, long row)
{
	CString strNumber;
	QuickGetText(col, row, &strNumber);

	return ValidateFaxNumber(strNumber);
}

bool CGridStoreContacts::ValidateEmailAddress(CString& strEmailAddress)
{
	if (strEmailAddress.GetLength() == 0)
	{
		return true;
	}

	bool bValid = false;
	//COXRegExpression regex;
	//CString strRule = "^[a-zA-Z0-9_]@[^\\.]";  // good
	//CString strRule = "^[a-zA-Z0-9_]@[^\\.][a-zA-Z0-9_]\\.[a-zA-Z]{2,}";
	//CString strRule = "[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\\.]@[^\\.][abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789]\\.[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]";
	//CString strRule = "[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\\.]@[^\\.][abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\\.]\\.[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\\.]";
	//CString strRule = ".+@.+\\..+";
	/*if (regex.LoadRule(strRule))
	{
		int NumMatches = regex.Match(strEmailAddress);
		if (NumMatches == 1)
		{
			bValid = true;
		}
	}
	else
	{
		CString strError;
		regex.TranslateError(regex.GetError(), strError);
		MessageBox(strError, "Error!");
	}*/

	CString strTemp = strEmailAddress;
	if (strTemp.Replace('@', '*') == 1)  // only 1 @ symbol
	{
		if (strTemp.Replace(' ', '*') == 0)  // no spaces
		{
            strTemp = strEmailAddress;
			int iIndex = strTemp.Find('@');
			if (strTemp.GetAt(iIndex+1) != '.')
			{
				iIndex = strTemp.ReverseFind('.');
				int iTLDLength = strTemp.Right(strTemp.GetLength() - iIndex -1).GetLength();
				if (iTLDLength > 1 && iTLDLength < 5)
				{
					bValid = true;
				}
			}
		}
	}

	return bValid;
}

int CGridStoreContacts::GetFaxToID(CString strFaxToID)
{
	if (strFaxToID == m_aszFAX_STRINGS[NO_FAX]) return NO_FAX;
	if (strFaxToID == m_aszFAX_STRINGS[FAX]) return FAX;
	if (strFaxToID == m_aszFAX_STRINGS[ALT_FAX]) return ALT_FAX;
	if (strFaxToID == m_aszFAX_STRINGS[TRY_BOTH]) return TRY_BOTH;

	return NO_FAX;
}

CString CGridStoreContacts::GetFaxToString(long lID)
{
	if ((lID != NULL) && (lID < FAX_LAST))
	{
		return m_aszFAX_STRINGS[lID];
	}

	return m_aszFAX_STRINGS[NO_FAX];
}

bool CGridStoreContacts::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridStoreContacts::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}