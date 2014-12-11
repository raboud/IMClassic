/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridStores.cpp: implementation of the CGridDiscrepancies class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridDiscrepancies.h"
#include "SetVwDiscrepancies.h"
#include "SetDiscrepancies.h"
#include "DlgStoreCustDiscrepancy.h"
#include "DialogPo.h"
#include "SetOrderBasicLaborDetails.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridDiscrepancies::CGridDiscrepancies()
{
	HighlightCurrentRow();
	m_strRecordSetFilter = "";
	m_lCustomerID = -1;
	m_bShowReviewed = false;
}

CGridDiscrepancies::~CGridDiscrepancies()
{
}

void CGridDiscrepancies::OnSetup()
{
	CCFGrid::OnSetup() ;

	AddColumn(" ID  ", ID);
	AddColumn("PO Number", PO_NUMBER);
	AddColumn("Store Number", STORE_NUMBER);
	AddColumn("     Customer     ", CUSTOMER);
	AddColumn("        Type         ", DISC_TYPE);
	AddColumn("       SubType       ", DISC_SUBTYPE);
	AddColumn("    Current Data    ",	CURRENT_DATA);
	AddColumn("      New Data      ", NEW_DATA);
	AddColumn("Reviewed", REVIEWED);
	AddColumn("OrgReviewed", ORG_REVIEWED);
	AddColumn("CanReviewAlert", CAN_REVIEW_ALERT);

	InitColumnHeadings();

	CUGCell cell;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(ID, &cell) ;

	GetColDefault(PO_NUMBER, &cell) ;
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(PO_NUMBER, &cell) ;
	SetColDefault(STORE_NUMBER, &cell) ;	

	GetColDefault(CURRENT_DATA, &cell);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	cell.SetReadOnly(TRUE);
	SetColDefault(CURRENT_DATA, &cell) ;
	SetColDefault(NEW_DATA, &cell) ;

	GetColDefault(REVIEWED, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	cell.SetReadOnly(TRUE);
	SetColDefault(REVIEWED, &cell) ;

	GetColDefault(CAN_REVIEW_ALERT, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
	SetColDefault(CAN_REVIEW_ALERT, &cell) ;

	HideColumn(ORG_REVIEWED);
	HideColumn(CAN_REVIEW_ALERT);

	UseHints(TRUE);
	EnableMenu(TRUE) ;
}

void CGridDiscrepancies::SetPOList(CPoList* pListPOs, bool bShowReviewed /*=false*/, bool bUpdateGrid /*=true*/)
{
	m_bShowReviewed  = bShowReviewed;

	m_strRecordSetFilter = "";
	if (pListPOs != NULL)
	{
		m_listPOs.AddHead(pListPOs);
		if (m_listPOs.GetCount() > 1)
		{
			m_bConsolidatedView = true;
		}

		POSITION pos = m_listPOs.GetHeadPosition();
		int iOrderID = -1;
		while(pos)
		{
			iOrderID = m_listPOs.GetNext(pos);
			if (m_strRecordSetFilter.GetLength() > 0)
			{
				m_strRecordSetFilter += " OR ";
			}
			CString strTemp;
			strTemp.Format("([OrderID] = %d)", iOrderID);
			m_strRecordSetFilter += strTemp;
		}

		pos = m_listPOs.GetHeadPosition();
		iOrderID = m_listPOs.GetNext(pos);
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter.Format("OrderID = %d", iOrderID);
		setOrders.Open();
		if (!setOrders.IsEOF())
		{
			m_lCustomerID = setOrders.m_CustomerID;
		}
		setOrders.Close();

		if (bUpdateGrid)
		{
			UpdateGrid();
		}
	}
	else
	{
		m_listPOs.RemoveAll();
	}
}

void CGridDiscrepancies::Update()
{
	EnableUpdate(FALSE);
	
	// get rid of stale data
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	}

	CSetVwDiscrepancies setDiscrepancies(&g_dbFlooring) ;
	
	if (m_lCustomerID != -1)
	{
		CString strExtraFilter;
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " OR";
		}
		strExtraFilter.Format(" (Type = 'CUSTOMER' AND DetailID = %d)", m_lCustomerID);
		m_strRecordSetFilter += strExtraFilter;
	}

	if (m_strRecordSetFilter.GetLength() > 0)
	{
		m_strRecordSetFilter = "(" + m_strRecordSetFilter + ")";
	}

	if (false == m_bShowReviewed)
	{
		if (m_strRecordSetFilter.GetLength() > 0)
		{
            m_strRecordSetFilter += " AND";
		}
		m_strRecordSetFilter += " Reviewed = 0";
	}

	// filter out NOTES discrepancies when entering the grid from the Maintenance menu
	if (m_listPOs.GetCount() == 0)
	{
		if (m_strRecordSetFilter.GetLength() > 0)
		{
			m_strRecordSetFilter += " AND SubType <> 'NOTES'";
		}
	}

	setDiscrepancies.m_strFilter = m_strRecordSetFilter;
	setDiscrepancies.Open() ;
	bool bCanReviewCustomerAlert = CanReviewAlertForCustomer();
	while (!setDiscrepancies.IsEOF())
	{
		AppendRow() ;
		long lRow = GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("%d", setDiscrepancies.m_ID) ;
		QuickSetText(ID, lRow, strID) ;

		QuickSetText(PO_NUMBER, lRow, setDiscrepancies.m_PONumber);
		QuickSetText(STORE_NUMBER, lRow, setDiscrepancies.m_StoreNumber);
		QuickSetText(DISC_TYPE, lRow, setDiscrepancies.m_Type) ;
		QuickSetText(DISC_SUBTYPE, lRow, setDiscrepancies.m_SubType) ;
		QuickSetText(CUSTOMER, lRow, setDiscrepancies.m_CustomerName) ;
		QuickSetText(CURRENT_DATA, lRow, setDiscrepancies.m_CurrentData) ;
		QuickSetText(NEW_DATA, lRow, setDiscrepancies.m_NewData) ;
		QuickSetBool(REVIEWED, lRow, setDiscrepancies.m_Reviewed == TRUE);
		QuickSetBool(ORG_REVIEWED, lRow, setDiscrepancies.m_Reviewed == TRUE);

		// if we have a CUSTOMER alert, we need to determine whether or not the user has permission
		// to clear alerts for any PO that the customer has.  For example, if the customer has permission
		// to clear alerts for Hard Surface POs and there is an alert for this customer on a Soft Surface
		// PO, the user should be allowed to clear the alert.

		bool bCanReviewAlert = false;
		if ((setDiscrepancies.m_Type != "CUSTOMER") || (setDiscrepancies.m_Type == "CUSTOMER" && m_lCustomerID == -1))
		{
			// non-customer alert
			bCanReviewAlert = CGlobals::HasPermission("CanReviewAlert", setDiscrepancies.m_MarketID, setDiscrepancies.m_DivisionID);
		}
		else
		{
			// we are looking at alerts for a single customer and/or PO
			bCanReviewAlert = bCanReviewCustomerAlert;
		}

		QuickSetBool(CAN_REVIEW_ALERT, lRow, bCanReviewAlert);
		QuickSetReadOnly(REVIEWED, lRow, !bCanReviewAlert);
        
		setDiscrepancies.MoveNext() ;
	}
	setDiscrepancies.Close();

	if (m_strRecordSetFilter.GetLength() > 0)
	{
		HideColumn(PO_NUMBER);
		HideColumn(STORE_NUMBER);
		HideColumn(CUSTOMER);
	}
	EnableUpdate(TRUE);
	UpdateRowHeights();
	RedrawAll() ;
}

int CGridDiscrepancies::OnMenuStart(int col, long row, int section)
{
	UNREFERENCED_PARAMETER(col);

	BOOL bDisplayMenu = FALSE;
	if ((section == UG_GRID) && (row >= 0))
	{
		//* Empty the Menu!!
		EmptyMenu();

		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			if (QuickGetBool(CAN_REVIEW_ALERT, row) == true)
			{
				AddMenuItem(CORRECT_DISCREPANCY, "Correct") ;
				bDisplayMenu = TRUE;
			}
		}
	}
	return bDisplayMenu ;
}

void CGridDiscrepancies::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case CORRECT_DISCREPANCY:
			CorrectDiscrepancy(row) ;
			break ;

		default:
			break ;
		}
	}
	UpdateRowHeights();
	RedrawAll() ;
}

void CGridDiscrepancies::OnSH_DClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	CorrectDiscrepancy(row) ;
}

void CGridDiscrepancies::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	CorrectDiscrepancy(row) ;
}

int CGridDiscrepancies::OnHint(int col, long row, int section, CString *string, int *maxwidth)
{
	if ((section == UG_GRID) && ((col == CURRENT_DATA) || (col == NEW_DATA)))
	{
		CString text;
		text = QuickGetText(col, row);
		string->Format(_T("%s"), text);
		*maxwidth = 500;
		return TRUE; 
	}
	
	return FALSE;
}

void CGridDiscrepancies::CorrectDiscrepancy(long row)
{
	if (QuickGetBool(CAN_REVIEW_ALERT, row) == true)
	{
		CString strId = QuickGetText(ID, row) ;
		int iId = atoi(strId) ;

		CSetDiscrepancies setDisc(&g_dbFlooring);
		setDisc.m_strFilter.Format("ID = %d", iId);
		setDisc.Open();
		if (setDisc.IsEOF() == false)
		{
			int DiscType = setDisc.m_DiscrepancyTypeID;
			int DiscSubType = setDisc.m_DiscrepancySubTypeID;
			long DetailID = setDisc.m_DetailID;
			long OrderID = setDisc.m_OrderID;
			CString CurrentData = setDisc.m_CurrentData;
			CString NewData = setDisc.m_NewData;
			CString XMLFilePath = setDisc.m_XMLFilePath;
			COleDateTime DTFound = setDisc.m_DateFound;

			bool bHandledOK = HandleDiscrepancy(DiscType, DiscSubType, DetailID, OrderID, CurrentData, NewData,
				XMLFilePath, DTFound);

			if (bHandledOK)
			{
				long lCurrentRow = GetCurrentRow();
				QuickSetBool(REVIEWED, lCurrentRow, true);
				UpdateRowHeights();
				RedrawAll();
			}
		}
	}
	else
	{
		MessageBox("You do not have the required permissions to correct this alert.", "Info");
	}
}

int CGridDiscrepancies::OnCanSizeTopHdg()
{ 
	return FALSE; 
} 

BOOL CGridDiscrepancies::OnCanSizeCol(int /*col*/)
{
	return TRUE;
}

bool CGridDiscrepancies::HandleDiscrepancy(int DiscType, int DiscSubType, long DetailID, long OrderID, 
										   CString CurrentData, CString NewData, CString XMLFilePath, COleDateTime DTFound)
{
	UNREFERENCED_PARAMETER(DTFound);
	UNREFERENCED_PARAMETER(OrderID);

	bool bHandledOK = false;
	switch (DiscType)
	{
		case 1:  // STORE
		case 2:  // CUSTOMER
		{
			CDlgStoreCustDiscrepancy dlg;
			dlg.SetDiscType(DiscType);
			dlg.SetSubType(DiscSubType);
			dlg.SetDetailID(DetailID);
			dlg.SetNewData(NewData);
			dlg.SetCurrentData(CurrentData);
			CString strTemp;
			if (DiscType == 1)
			{
				strTemp.Format("Store Number is: %s", CGlobals::StoreNumberFromStoreID(DetailID));
				dlg.SetExtraData(strTemp);
			}
			else
			{
				CString strName = CGlobals::CustomerNameFromCustomerID(DetailID);
				strTemp.Format("Customer: %s (ID = %d)", strName, DetailID);
				dlg.SetExtraData(strTemp);
			}
			dlg.DoModal();
			bHandledOK = dlg.WasHandled();
		}
		break;
		//case 4:  // OPTIONS DETAIL
		//case 5:  // REGULAR MERCHANDISE
		//case 6:  // SO MERCHANDISE
		//case 12: // BASIC LABOR DETAILS
		//case 13: // CUSTOM LABOR DETAIL
		//{
		//	if (DiscSubType == 17)
		//	{
		//		CDlgPo dlg;
		//		if (OrderID != -1)
		//		{
		//			dlg.SetOrderId(OrderID);
		//			dlg.SetInvokedFromSPNFlag(true);
		//			if (dlg.DoModal() == IDOK)
		//			{
		//				bHandledOK = true;
		//			}
		//		}
		//	}
		//	else
		//	{
		//		MessageBox("Discrepancy must be handled by Rob or Dan", "Correct") ;
		//	}
		//}
		//break;
		case 7:  // OTHER
		{
			if (DiscSubType == 27) // NOTES
			{
				CString strMessage = "Notes are handled directly in the P.O. dialog.  Review the\r\n";
				strMessage +=        "notes and make any changes.  Return here to check the\r\n";
				strMessage +=        "Reviewed checkbox when you are done.";
				MessageBox(strMessage);
			}
		//	if (DiscSubType == 20) // WARRANTY PO NOT FOUND
		//	{
		//		CDlgPo dlg;
		//		long OrderID = CustOrStoreID;
		//		if (OrderID != -1)
		//		{
		//			dlg.SetOrderId(OrderID);
		//			dlg.SetInvokedFromSPNFlag(true);
		//			if (dlg.DoModal() == IDOK)
		//			{
		//				int iResponse = MessageBox("Delete this discrepancy?", "Question", MB_YESNO);
		//				if (iResponse == IDYES)
		//				{
		//					bHandledOK = true;
		//				}
		//			}
		//		}
		//	}
		//	else
		//	{
		//		MessageBox("Discrepancy must be handled by Rob or Dan", "Correct") ;
		//	}
		}
		break ;
		default:
			MessageBox("Discrepancy must be handled by an administrator.", "Correct") ;
			break;
	}

	return bHandledOK;
}

int CGridDiscrepancies::OnCellTypeNotify(long ControlID, int col, long row, long msg, long param)
{
	UNREFERENCED_PARAMETER(param);
	UNREFERENCED_PARAMETER(ControlID);
	if ((col == REVIEWED) && (msg == UGCT_CHECKBOXSET))
	{
		IsRowDirty(row) ;
		UpdateRowHeights();
		RedrawAll();
	}
	return TRUE ;
}

void CGridDiscrepancies::UpdateRecordSet()
{
	long lRow = 0;
	CSetDiscrepancies setDisc(&g_dbFlooring);
	setDisc.m_strFilter = "ID = -1";
	setDisc.Open();

	for (lRow = 0; lRow < GetNumberRows() ; lRow++)
	{
		if (IsRowDirty(lRow))
		{
			try
			{
				long lID = (long) QuickGetNumber(ID, lRow);
				setDisc.m_strFilter.Format("ID = %d", lID);
				setDisc.Requery();
				if (!setDisc.IsEOF())
				{
					setDisc.Edit();
					setDisc.m_Reviewed = QuickGetBool(REVIEWED, lRow);
					setDisc.m_ReviewedBy = CGlobals::GetEmployeeID();
					setDisc.m_ReviewedDate = CGlobals::GetCurrentSystemTime();
					setDisc.Update();
				}
			}
			catch (CException* pE)
			{
				pE->Delete() ;
			}
		}
	}
}

bool CGridDiscrepancies::IsRowDirty(long lRow)
{
	bool bDirty = false ;

	if (!bDirty) bDirty = IsColumnDirty(REVIEWED, lRow) ; 

	CString strId ;
	QuickGetText(ID, lRow, &strId) ;

	if (bDirty)
	{
		strId += "*" ;
		strId.Replace("**", "*") ;
	}
	else
	{
		strId.Replace("*", "") ;
	}

	QuickSetText(ID, lRow, strId) ;

	return bDirty ;
}

bool CGridDiscrepancies::IsColumnDirty(int iCol, long lRow)
{
	bool bDirty = true ;

	switch (iCol)
	{
	case REVIEWED :
		bDirty = QuickGetBool(REVIEWED, lRow) != QuickGetBool(ORG_REVIEWED, lRow) ; 
		break ;

	default:
		ASSERT(FALSE) ;
		break ;
	}

	return bDirty;
}

bool CGridDiscrepancies::CanReviewAlertForCustomer()
{
	// this function determines if the current user has permission to review alerts
	// on any PO for this customer.  Filtering out deleted and cancelled pos since
	// this might give the wrong result.

	// we get all the orders for the current customer and check to see if the user
	// has ReviewAlerts permission for any of them.  If they do we set the flag and 
	// exit.
	bool bCanReview = false;

	if (m_lCustomerID != -1)
	{
		CSetOrders setOrders(&g_dbFlooring);
		setOrders.m_strFilter.Format("CustomerID = %d", m_lCustomerID);
		setOrders.Open();
		while (!setOrders.IsEOF() && bCanReview == false)
		{
			bCanReview = CGlobals::HasPermission("CanReviewAlert", CGlobals::MarketIDFromStoreID(setOrders.m_StoreID), CGlobals::DivisionIDFromMaterialTypeID(setOrders.m_MaterialTypeID));
			setOrders.MoveNext();
		}
	}

	return bCanReview;
}

int CGridDiscrepancies::GetMaxRowHeight(int iColumnID1, int iColumnID2, long lRow)
{
	CDC* pDC = GetDC() ;
	CRect rect1(0, 0, GetColWidth(iColumnID1) - 2, 10) ;
	pDC->DPtoLP(&rect1) ;
	
	CRect rect2(0, 0, GetColWidth(iColumnID2) - 2, 10) ;
	pDC->DPtoLP(&rect2) ;

	int iWidth1 = rect1.Width() ;
	int iWidth2 = rect2.Width() ;

	CUGCell cell ;
	GetCell(iColumnID1, 0, &cell) ;

	CFont* pFont = cell.GetFont() ;

	if (pFont == NULL)
	{
		pFont = GetFont(m_fontID) ;
	}
		
	LOGFONT lf;
	pFont->GetLogFont(&lf);
		
	int iRowLeader = (m_GI->m_defRowHeight - lf.lfHeight) / 2 ;

	pDC->SelectObject(pFont);

	rect1.right = rect1.left + iWidth1  ;
	rect2.right = rect2.left + iWidth2  ;
	pDC->DrawText(QuickGetText(iColumnID1, lRow), &rect1, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
	pDC->DrawText(QuickGetText(iColumnID2, lRow), &rect2, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_NOPREFIX) ;
	pDC->LPtoDP(&rect1) ;
	pDC->LPtoDP(&rect2) ;

	int iHeight1 = rect1.Height();
	int iHeight2 = rect2.Height();
	return (iHeight1 < iHeight2) ? iHeight2 + iRowLeader : iHeight1 + iRowLeader;
}

void CGridDiscrepancies::UpdateRowHeights()
{
	long lNumRows = GetNumberRows();

	for (long lRow = 0; lRow < lNumRows; lRow++)
	{
		int iRowHeight = GetMaxRowHeight(CURRENT_DATA, NEW_DATA, lRow);
		SetRowHeight(lRow, iRowHeight) ;
	}
	AdjustComponentSizes() ;
}


