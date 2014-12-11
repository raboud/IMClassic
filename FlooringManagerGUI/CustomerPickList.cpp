/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CustomerPickList.cpp: implementation of the CCustomerPickList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Flooring.h"
#include "CustomerPickList.h"
#include "SetCustomer.h"
#include "SetOrders.h"
#include "DlgMergeCustomers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomerPickList::CCustomerPickList()
{
	HighlightCurrentRow();
}

CCustomerPickList::~CCustomerPickList()
{
}

void CCustomerPickList::SetCustomerSet(CSetCustomer *pSet)
{
	m_pSet = pSet ;
}

void CCustomerPickList::OnSetup()
{
	CCFGrid::OnSetup() ;

	InitDefaultFont();

	AddColumn(" ID  ", ID);
	AddColumn("Last Name    ", LAST_NAME);
	AddColumn("First Name", FIRST_NAME);
	AddColumn("Address              ", ADDRESS);
	AddColumn("City          ", CITY);
	AddColumn("State", STATE);
	AddColumn("Zip        ", ZIP);

	InitColumnHeadings();
    
	EnableMenu(TRUE) ;
	SetMultiSelectMode(TRUE);
}

void CCustomerPickList::Update()
{
	CWaitCursor cWait ;

	EnableUpdate(FALSE);

	while (GetNumberRows())
	{
		DeleteRow(0) ;
	}

	int iRow = 0;
	try 
	{
		m_pSet->MoveFirst() ;
		//Add the Row Heading to the grid
		while (!m_pSet->IsEOF() && (iRow < 1000))
		{
//			InsertRow(iRow) ;
			AppendRow() ;

			iRow = GetNumberRows() - 1 ;
			CString strHeading ;
			strHeading.Format("%d", m_pSet->m_CustomerID);
			QuickSetText(ID, iRow, strHeading);
			QuickSetText(LAST_NAME, iRow, m_pSet->m_LastName) ;
			QuickSetText(FIRST_NAME, iRow, m_pSet->m_FirstName) ;
			QuickSetText(ADDRESS, iRow, m_pSet->m_Address) ;
			QuickSetText(CITY, iRow, m_pSet->m_City) ;
			QuickSetText(STATE, iRow, m_pSet->m_State) ;
			QuickSetText(ZIP, iRow, m_pSet->m_ZipCode) ;
			m_pSet->MoveNext() ;
			iRow++ ;
		}
	}
	catch(CDBException *pE)
	{
		pE->Delete() ;
	}

	EnableUpdate(TRUE);
	RedrawAll() ;

}

void CCustomerPickList::OnSH_DClicked(int col,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	SelectCustomer(col, row) ;
}

void CCustomerPickList::OnDClicked(int col,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	SelectCustomer(col, row) ;
}

void CCustomerPickList::OnCharDown(UINT *vcKey, BOOL /* processed */)
{
	if ((*vcKey == VK_SPACE) || (*vcKey == VK_RETURN))
	{
		int col = this->GetCurrentCol() ;
		long row = this->GetCurrentRow() ;

		SelectCustomer(col, row) ;
	}
}

void CCustomerPickList::SelectCustomer(int /* col */, long row)
{
	if ((row < this->GetNumberRows()) && (row >= 0))
	{
		m_pSet->m_strFilter.Format("[CustomerID] = '%d'", int (QuickGetNumber(-1, row))) ;
		m_pSet->Requery() ;
		::PostMessage((this->GetParent())->m_hWnd, wm_CUSTOMER_SELECT, 0, row) ;
	}
}

int CCustomerPickList::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		if ((row >= 0) && (row < GetNumberRows()))
		{
			bool bGrayed = false;
			int iNumSelected = GetSelectedCustomers();

			AddMenuItem(2000, "Delete", bGrayed) ;
			if (iNumSelected == 2)
			{
				AddMenuItem(2001, "Merge Selected");
			}
		}
	}
	return TRUE ;
}

void CCustomerPickList::OnMenuCommand(int col, long row, int section, int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	
	if (section == UG_GRID)
	{
		if (item == 2000)
		{
			CString strMessage;
			int iNumSelected = m_aiSelectedCustIDs.GetCount();
			if ( iNumSelected > 1)
			{
				strMessage = "You are about to delete the selected customers from the data base. Is this really what you want?";
			}
			else
			{
				strMessage = "You are about to delete the customer from the data base. Is this really what you want?";
			}

			if (MessageBox(strMessage, "Deleting", MB_YESNO) == IDYES)
			{
				try
				{
					CString strOrdersFilter = "";
					CString strTemp;
					for (int iIndex = 0; iIndex < iNumSelected; iIndex++)
					{
						if (strOrdersFilter.GetLength() > 0)
						{
							strOrdersFilter += " OR ";
						}
						strTemp.Format("[CustomerID] = %d", m_aiSelectedCustIDs.GetAt(iIndex));
						strOrdersFilter += strTemp;
					}

					CString strOldFilter = m_pSet->m_strFilter ;
					CSetOrders setOrders(&g_dbFlooring);
					setOrders.m_strFilter = strOrdersFilter ;
					setOrders.Open();

					if (!setOrders.IsEOF())
					{
						if (iNumSelected > 1)
						{
                            MessageBox("At least one of the selected customers is referenced by one or more P.O.s.\nPlease transfer the P.O.s of each selected customer to another customer before trying to delete.", "Error");
						}
						else
						{
							MessageBox("This customer is referenced by one or more P.O.s.\nPlease transfer the P.O.s to another customer before trying to delete.", "Error");
						}
					}
					else
					{
						m_pSet->m_strFilter = strOrdersFilter ;
						m_pSet->Requery() ;
						m_pSet->Delete() ;
						m_pSet->m_strFilter = strOldFilter ;
						m_pSet->Requery() ;
						Update() ;
					}
					setOrders.Close();
				}
				catch(CDBException* e)
				{
					CString strMessage;
					strMessage.Format("There was an error while trying to delete customer(s).\nThe record(s) may or may not have been deleted, therefore please notify an administrator with the following information.\n\nError: %s", e->m_strError);
					MessageBox(strMessage, "Error");
				}
			}
		}
		else if (item == 2001)
		{
			MergeCustomers();
			m_pSet->Requery() ;
			Update() ;
		}
	}
}

int CCustomerPickList::GetSelectedCustomers()
{
	m_aiSelectedCustIDs.RemoveAll();

	int iCol ;
	long lRow ;
	long lLastRow = -1 ;

	EnumFirstSelected(&iCol, &lRow);
	do
	{
		if (lRow != lLastRow)
		{
			m_aiSelectedCustIDs.Add(int(QuickGetNumber(-1, lRow)));
		}
		lLastRow = lRow ;
	} while (EnumNextSelected(&iCol, &lRow) == UG_SUCCESS) ;

	return m_aiSelectedCustIDs.GetCount();
}

void CCustomerPickList::MergeCustomers()
{
	CDlgMergeCustomers dlg;
	if ( dlg.SetCustomerIDs(m_aiSelectedCustIDs.GetAt(0), m_aiSelectedCustIDs.GetAt(1)))
	{
		dlg.DoModal();
	}
}

bool CCustomerPickList::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CCustomerPickList::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}