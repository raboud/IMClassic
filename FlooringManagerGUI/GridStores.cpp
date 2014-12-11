/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridStores.cpp: implementation of the CGridStores class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridStores.h"
#include "ViewStoreInfo.h"
#include "DlgStore.h"
#include "SetOrders.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridStores::CGridStores()
{
	m_bShowActiveOnly = true;
	HighlightCurrentRow();
}

CGridStores::~CGridStores()
{
}

void CGridStores::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn(" ID  ", ID);
	AddColumn("Store", STORE_NUMBER);
	AddColumn("       Store Type      ", STORE_TYPE);
	AddColumn("    Market    ",	MARKET);
//	AddColumn("      Expeditor      ", EXPEDITOR);
//	AddColumn("       Direct Phone       ",	DIRECT_PHONE_NUM);
	AddColumn("  Store Phone     ",	STORE_PHONE_NUM);
	AddColumn("  Store Fax       ", FAX_NUM);

	InitColumnHeadings();

	CUGCell cell;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	EnableMenu(TRUE) ;
}

void CGridStores::Update()
{
	EnableUpdate(FALSE);

	long lRow = GetCurrentRow();
	
	// get rid of stale data
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	CViewStoreInfo setStoreInfo(&g_dbFlooring) ;
	setStoreInfo.m_strSort = "StoreNumber";
	if (m_bShowActiveOnly)
	{
		setStoreInfo.m_strFilter = "[Active] = 1";
	}
	setStoreInfo.Open() ;
	while (!setStoreInfo.IsEOF())
	{
		AppendRow() ;
		long lRow = GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("%d", setStoreInfo.m_StoreID) ;
		QuickSetText(ID, lRow, strID) ;

		QuickSetText(STORE_NUMBER, lRow, setStoreInfo.m_StoreNumber) ;
		QuickSetText(STORE_TYPE, lRow, setStoreInfo.m_StoreTypeName) ;
		QuickSetText(MARKET, lRow, setStoreInfo.m_MarketName.Trim()) ;
//		QuickSetText(EXPEDITOR, lRow, setStoreInfo.m_Expeditor) ;
//		QuickSetText(DIRECT_PHONE_NUM, lRow, setStoreInfo.m_DirectPhoneNumber) ;
		QuickSetText(STORE_PHONE_NUM, lRow, setStoreInfo.m_StorePhoneNumber) ;
		QuickSetText(FAX_NUM, lRow, setStoreInfo.m_FaxNumber) ;

		setStoreInfo.MoveNext() ;
	}
	setStoreInfo.Close();
	EnableUpdate(TRUE);
	RedrawAll() ;

	if (lRow < GetNumberRows())
	{
		GotoRow(lRow);
	}
}

int CGridStores::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();
		CPermissions permissions;

		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			if (permissions.HasPermission("CanEditStore"))
			{
				AddMenuItem(EDIT_STORE, "Edit") ;
			}

			if (permissions.HasPermission("CanAddStore"))
			{
				AddMenuItem(NEW_STORE, "New") ;
			}

			if (permissions.HasPermission("CanDeleteStore"))
			{
				AddMenuItem(DELETE_STORE, "Delete");
			}
		}
	}
	return TRUE ;
}

void CGridStores::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case EDIT_STORE:
			EditStore(row) ;
			break ;

		case NEW_STORE:
			NewStore() ;
			break ;

		case DELETE_STORE:
			DeleteStore(row);
			break;

		default:
			break ;
		}
	}
}

void CGridStores::OnSH_DClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	EditStore(row) ;
}

void CGridStores::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	EditStore(row) ;
}

void CGridStores::EditStore(long row)
{
	CPermissions permissions;
	if (permissions.HasPermission("CanEditStore"))
	{
		CString strId = QuickGetText(ID, row) ;
		int iId = atoi(strId) ;

		CDlgStore dlg(false) ;
		dlg.SetStoreID(iId) ;
		if (dlg.DoModal() == IDOK)
		{
			Update() ;
		}
	}
}

void CGridStores::NewStore()
{
	CDlgStore dlg(true) ;
	if (dlg.DoModal() == IDOK)
	{
		Update() ;
	}
}

void CGridStores::DeleteStore(long row)
{
	CString strId = QuickGetText(ID, row) ;
	int iId = atoi(strId) ;

	if (CanDeleteStore(iId))
	{
        int iResponse = MessageBox("Are you sure you wish to delete this store? (this operation cannot be undone.)", "Question", MB_YESNO);
		if (iResponse == IDYES)
		{
			CSetStores setStores(&g_dbFlooring);
			setStores.m_strFilter.Format("[StoreID] = %d", iId);
			setStores.Open();
			ASSERT(setStores.IsEOF() == FALSE);
			setStores.Delete();
			setStores.Close();
			Update();
		}
	}
	else
	{
		MessageBox("This store cannot be deleted as it is referenced in at least one customer order.", "Notice!");
	}
}

void CGridStores::ShowActiveOnly( bool bShowActiveOnly )
{
	m_bShowActiveOnly = bShowActiveOnly;
	Update();
}

bool CGridStores::CanDeleteStore(int iStoreID)
{
	bool bCanDelete = false;

	CSetOrders setOrders(&g_dbFlooring);
	setOrders.m_strFilter.Format("[StoreID] = %d", iStoreID);
	setOrders.Open();
	if (setOrders.IsEOF())
	{
		bCanDelete = true;
	}
	setOrders.Close();

	return bCanDelete;
}

int CGridStores::OnCanSizeTopHdg()
{ 
	return FALSE; 
} 

BOOL CGridStores::OnCanSizeCol(int /*col*/)
{
	return TRUE;
}

bool CGridStores::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridStores::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}