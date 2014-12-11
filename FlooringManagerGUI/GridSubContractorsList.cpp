#include "stdafx.h"
#include "Flooring.h"
#include "GridSubContractorsList.h"
#include "DlgSubContractor.h"
#include "SetSubContractor.h"

CGridSubContractorsList::CGridSubContractorsList(void)
{
	m_bShowActiveOnly = true;
	m_iInstallerStatusFilter = 1;   // default to show Active only
	HighlightCurrentRow();
}

CGridSubContractorsList::~CGridSubContractorsList(void)
{
}

void CGridSubContractorsList::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn(" ID  ", ID);
	AddColumn("  Last Name    ", LAST_NAME);
	AddColumn("  First Name   ", FIRST_NAME);
	AddColumn("                 Address                ", ADDRESS);
	AddColumn("        City         ", CITY);
	AddColumn(" State ", STATE);
	AddColumn("     Zip      ", ZIP);
	AddColumn("  Home Phone  ", HOME_PHONE);
	AddColumn("  Cell Phone  ", CELL_PHONE);
	AddColumn(" Retain. %", RETAINAGE_RATE);

	InitColumnHeadings();

	// hide the retainage column if not admin
	if (!CGlobals::IsAdmin())
	{
		HideColumn(RETAINAGE_RATE);
	}

	EnableMenu(TRUE) ;
	EnableExcelBorders(TRUE) ;

	CUGCell cell;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(RETAINAGE_RATE, &cell) ;
	cell.SetNumberDecimals(2) ;
	cell.SetDataType(UGCELLDATA_NUMBER) ;
	cell.SetReadOnly(TRUE) ;
	SetColDefault(RETAINAGE_RATE, &cell) ;
}

void CGridSubContractorsList::Update()
{
	EnableUpdate(FALSE);
	
	// get rid of stale data
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetSubContractor setSubContractor(&g_dbFlooring) ;
	setSubContractor.m_strSort = "LastName";
	/*if (m_bShowActiveOnly)
	{
		setSubContractor.m_strFilter = "[Active] = 1";
	}*/
	if (m_iInstallerStatusFilter != 0)
	{
		setSubContractor.m_strFilter.Format("[Status] = %d", m_iInstallerStatusFilter);
	}
	setSubContractor.Open() ;
	while (!setSubContractor.IsEOF())
	{
		AppendRow() ;
		long lRow = GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("%d", setSubContractor.m_SubContractorID) ;

		QuickSetText(ID, lRow, strID) ;
		QuickSetText(FIRST_NAME, lRow, setSubContractor.m_FirstName) ;
		QuickSetText(LAST_NAME, lRow, setSubContractor.m_LastName) ;
		QuickSetText(ADDRESS, lRow, setSubContractor.m_Address) ;
		QuickSetText(CITY, lRow, setSubContractor.m_City) ;
		QuickSetText(STATE, lRow, setSubContractor.m_State) ;
		QuickSetText(ZIP, lRow, setSubContractor.m_ZipCode) ;
		QuickSetText(HOME_PHONE, lRow, setSubContractor.m_HomePhoneNumber) ;
		QuickSetText(CELL_PHONE, lRow, setSubContractor.m_CellPhoneNumber) ;
		QuickSetText(RETAINAGE_RATE, lRow, GetRetainagePercent(setSubContractor.m_RetainageRate)) ;

		setSubContractor.MoveNext() ;
	}
	setSubContractor.Close();
	EnableUpdate(TRUE);
	RedrawAll() ;
}

int CGridSubContractorsList::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		if ((row >= 0) && (row < GetNumberRows()))
		{
			if (CGlobals::HasPermission("CanEditSubContractor"))
			{
				AddMenuItem(EDIT_SUB, "Edit") ;
			}

			if (CGlobals::HasPermission("CanAddSubContractor"))
			{
				AddMenuItem(NEW_SUB, "New") ;
			}

			if (CGlobals::HasPermission("CanDeleteSubContractor"))
			{
				AddMenuItem(DELETE_SUB, "Delete");
			}
		}
	}
	return TRUE ;
}

void CGridSubContractorsList::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case EDIT_SUB:
			EditSubContractor(row) ;
			break ;

		case NEW_SUB:
			NewSubContractor() ;
			break ;

		case DELETE_SUB:
			DeleteSubContractor(row);
			break;

		default:
			break ;
		}
	}
}

void CGridSubContractorsList::OnSH_DClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	EditSubContractor(row) ;
}

void CGridSubContractorsList::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	EditSubContractor(row) ;
}

void CGridSubContractorsList::EditSubContractor(long row)
{
	if (CGlobals::HasPermission("CanEditSubContractor"))
	{
		CString strId = QuickGetText(ID, row) ;
		int iId = atoi(strId) ;

		CDlgSubContractor dlg(false) ;
		dlg.SetSubContractorID(iId) ;
		if (dlg.DoModal() == IDOK)
		{
			Update() ;
		}
	}
}

void CGridSubContractorsList::NewSubContractor()
{
	CDlgSubContractor dlg(true) ;
	if (dlg.DoModal() == IDOK)
	{
		Update() ;
	}
}

void CGridSubContractorsList::DeleteSubContractor(long row)
{
	CString strId = QuickGetText(ID, row) ;
	int iId = atoi(strId) ;

	int iResponse = MessageBox("Are you sure you wish to delete this subcontractor? (this operation cannot be undone.)", "Question", MB_YESNO);
	if (iResponse == IDYES)
	{
		CSetSubContractor setSubContractor(&g_dbFlooring);
		setSubContractor.m_strFilter.Format("[SubContractorID] = %d", iId);
		setSubContractor.Open();
		ASSERT(setSubContractor.IsEOF() == FALSE);
		setSubContractor.Delete();
		setSubContractor.Close();
		Update();
	}

}

void CGridSubContractorsList::ShowActiveOnly( bool bShowActiveOnly )
{
	m_bShowActiveOnly = bShowActiveOnly;
	Update();
}

void CGridSubContractorsList::SetShowFilter( int iFilter )
{
	m_iInstallerStatusFilter = iFilter;
	Update();
}

CString CGridSubContractorsList::GetRetainagePercent(CString strValue)
{
	double dValue = atof(strValue) * 100;
	CString strPercent;
	strPercent.Format("%.1f", dValue);

	return strPercent;
}

bool CGridSubContractorsList::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridSubContractorsList::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}