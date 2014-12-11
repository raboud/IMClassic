/*----------------------------------------------------------------------
	Copyright © 2001-2004 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridInvoicing.cpp: implementation of the CGridInvoicing class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Flooring.h"
#include "GridInvoicing.h"
#include "SetOrderAndCustomer.h"
#include "SetPayments.h"
#include <math.h>
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//enum {ENTRY_MANUAL = 1, SPN_ENTRY_IMPORTED, SPN_ENTRY_IMPORTED_HANDMODIFIED, SPN_ENTRY_IMPORTED_XMLDELETED, SOSI_ENTRY_IMPORTED, SOSI_ENTRY_IMPORTED_HANDMODIFIED, SOSI_ENTRY_IMPORTED_XMLDELETED} ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridInvoicing::CGridInvoicing()
	: m_setOrders(&g_dbFlooring)
	, m_iVendorID(-1)
{
	m_setOrders.m_strFilter = "[Billed] = '0'" ;
	m_setOrders.Open() ;

	m_setOrders.m_strSort = "[PurchaseOrderNumber]" ;

	HighlightCurrentRow();
}

CGridInvoicing::~CGridInvoicing()
{
	m_setOrders.Close() ;
}

void CGridInvoicing::SetBilledDate(COleDateTime timeBilled)
{
	this->m_BillDate = timeBilled ;
}

void CGridInvoicing::OnSetup()
{
	CCFGrid::OnSetup();

	// Get the index value of the font.
	int fontID = AddFont("Lucida Console", 14, FW_NORMAL);

	//Set the Grid's default font
	SetDefFont(fontID);

	AddColumn("   ID   ", ID);
	AddColumn("NAME                                   ", NAME);
	AddColumn("PO NUMBER   ", PO_NUMBER);
	AddColumn("INVOICED", INVOICE);
	AddColumn("AMOUNT    ", AMOUNT);
	AddColumn("  INV DATE   ", INVOICE_DATE);
	AddColumn("SOSI", IS_SOSI);
	AddColumn("IS_INSTALL", IS_INSTALL);

	InitColumnHeadings();

	//EnableMenu(TRUE) ;
	EnableExcelBorders(TRUE) ;

	CUGCell cell;
	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(AMOUNT, &cell) ;
	cell.SetNumberDecimals(2) ;
	cell.SetFormatClass(&m_formatCurrency) ;
	SetColDefault(AMOUNT, &cell) ;

	GetColDefault(INVOICE, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	SetColDefault(INVOICE, &cell) ;

	cell.SetReadOnly(TRUE);
	SetColDefault(IS_SOSI, &cell) ;
	SetColDefault(IS_INSTALL, &cell);

	HideColumn(IS_INSTALL);
	HideColumn(IS_SOSI);

	RECT			rect = {0,0,0,0};

	// Create a mask edit to use with ultimate grid mask edit
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);

	InitializeData() ;
}

int CGridInvoicing::OnCellTypeNotify(long Id, int col, long row, long msg, long param)
{
	CUGCell cell ;
	if ((Id == UGCT_CHECKBOX) && (msg == UGCT_CHECKBOXSET) && (col == INVOICE))
	{
		if (param == 1)
		{
			CString strID = QuickGetText(ID, row) ;
			m_setOrders.m_strFilter.Format("[OrderID] = '%s'", strID) ;
			m_setOrders.Requery() ;
			if (!m_setOrders.IsFieldNull(&m_setOrders.m_XMLOrderCostAmount))
			{
				QuickSetNumber(AMOUNT, row, ((atol(m_setOrders.m_XMLOrderCostAmount) + 50) /100) / 100.) ;
			}
			else if (m_setOrders.IsFieldNull(&m_setOrders.m_BilledAmount))
			{
				QuickSetNumber(AMOUNT, row, atof(m_setOrders.m_OrderAmount)) ;
			}
			else
			{
				QuickSetNumber(AMOUNT, row, atof(m_setOrders.m_BilledAmount)) ;
			}
			QuickSetText(INVOICE_DATE, row, this->m_BillDate.Format("%m/%d/%Y")) ;
			QuickSetReadOnly(AMOUNT, row, false) ;
			for (int iCol = 0; iCol < this->GetNumberCols(); iCol++)
			{
				GetCell(iCol, row, &cell) ;
				cell.SetBackColor(RGB(192, 192, 192) ) ;
				SetCell(iCol, row, &cell) ;
			}
		}
		else
		{
			QuickSetText(AMOUNT, row, "") ;
			QuickSetText(INVOICE_DATE, row, "") ;
			QuickSetReadOnly(AMOUNT, row, true) ;
			for (int iCol = 0; iCol < this->GetNumberCols(); iCol++)
			{
				GetCell(iCol, row, &cell) ;
				cell.SetBackColor(RGB(255,255,255) ) ;
				SetCell(iCol, row, &cell) ;
			}
		}
	}
	this->RedrawRow(row) ;
	UpdateTotals() ;
	return TRUE ;
}

void CGridInvoicing::InitializeData()
{
	CWaitCursor curWait ;

	// make sure we are empty
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetOrderAndCustomer setCombined(&g_dbFlooring)  ;

	if (m_iVendorID != -1)
	{
		CString strTemp;
		strTemp.Format("[VendorID] = %d", m_iVendorID);
		strTemp += " AND ([Billed] = '0' OR [Billed] IS NULL) AND ([Cancelled] = '0' OR [Cancelled] IS NULL) AND [Scheduled] = 1";
        setCombined.m_strFilter = strTemp;
	}
	else
	{
		setCombined.m_strFilter = "([Billed] = '0' OR [Billed] IS NULL) AND ([Cancelled] = '0' OR [Cancelled] IS NULL) AND [Scheduled] = 1" ;
	}
	setCombined.m_strSort = "[PurchaseOrderNumber]" ;
	setCombined.Open() ;

	EnableUpdate(FALSE);

	while(!setCombined.IsEOF())
	{
		AppendRow() ;
		long lRow = this->GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("%d", setCombined.m_OrderID) ;
		QuickSetText(ID, lRow, strID) ;

		CString strName ;
		strName = setCombined.m_Name;		

		QuickSetText(NAME, lRow, strName) ;
		QuickSetText(PO_NUMBER, lRow, setCombined.m_PurchaseOrderNumber) ;
//		QuickSetText(AMOUNT, lRow, m_setOrders.m_OrderAmount) ;
		QuickSetReadOnly(INVOICE, lRow, false) ;
		QuickSetBool(IS_SOSI, lRow, (setCombined.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED || setCombined.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED));
		QuickSetBool(IS_INSTALL, lRow, (setCombined.m_ShortName.MakeUpper().Trim() != "MEASURE"));
		if ((setCombined.m_EntryMethodID == CGlobals::ENTRY_MANUAL) && (setCombined.m_PurchaseOrderNumber.Trim().GetLength() == 8))
		{
			QuickSetReadOnly(IS_SOSI, lRow, false);
		}
		setCombined.MoveNext() ;
	}
	EnableUpdate(TRUE);
	RedrawAll() ;
	UpdateTotals() ;
	setCombined.Close() ;
}

void CGridInvoicing::UpdateRecordSet()
{
	// DKB - might could improve this whole process by keeping track of which lines changed...we
	// might only need to look at "invoiced" items and keep a list of orderids.  Down below perhaps
	// just update the affected orderids...
	int iNumSOSIDocs = 0;
	int iNumSPNActions = 0;
	CString strMessage = "";
	for (long lRow = 0; lRow <GetNumberRows(); lRow++)
	{
		if (QuickGetBool(INVOICE, lRow))
		{
			int iOrderID = (int) QuickGetNumber(ID, lRow);
			m_setOrders.m_strFilter.Format("[OrderID] = '%d'", iOrderID) ;
			m_setOrders.Requery() ;
			m_setOrders.Edit() ;

			m_setOrders.m_Billed = true ;
			m_setOrders.m_BilledAmount = QuickGetText(AMOUNT, lRow) ;
			m_setOrders.m_BilledAmount.Remove('$');
			CString strTime = QuickGetText(INVOICE_DATE, lRow) ;
			int nYear = atoi(strTime.Right(4)) ;
			int nMonth = atoi(strTime.Left(2)) ;
			int nDay = atoi(strTime.Mid(3,2)) ;
			m_setOrders.m_BilledDate = COleDateTime( nYear, nMonth, nDay, 0, 0, 0) ;
			BOOL bIsSOSI = QuickGetBool(IS_SOSI, lRow);
			BOOL bIsInstall = QuickGetBool(IS_INSTALL, lRow);
			if (m_setOrders.Update())
			{
				if ( bIsSOSI && bIsInstall )
				{
					CString strSQL = "";
					strSQL.Format("EXEC AddSOSIOutgoingDocument %d, '%d', '%s'", CGlobals::iSOSI_COMMUNICATE_INSTALL_SERVICE_COMPLETE_DOC_ID, iOrderID, "");
					g_dbFlooring.ExecuteSQL(strSQL);
					iNumSOSIDocs++;
				}
				else if (!bIsSOSI && bIsInstall)
				{

					// we are going to first queue up a command to schedule the PO to ensure it has been scheduled
					// then we queue up the close PO command with a 30 minute delay built in...
					CGlobals::QueueSchedulePO(iOrderID);
					COleDateTime datetime = CGlobals::GetCurrentSystemTime();
					COleDateTimeSpan span = COleDateTimeSpan(0,0,30,0);
					datetime = datetime + span;
					CGlobals::QueueClosePO(iOrderID, datetime);
					iNumSPNActions++;
				}
			}
			else
			{
				if (bIsSOSI)
				{
					strMessage.Format("Database update failed for PO %s.  The Install Service Complete Document was not sent.", QuickGetText(PO_NUMBER, lRow));
					MessageBox(strMessage);
				}
				else
				{
					strMessage.Format("Database update failed for PO %s.  The PO was NOT closed via the SPN Portal.", QuickGetText(PO_NUMBER, lRow));
					MessageBox(strMessage);
				}
			}
		}
	}

	// DKB - see about replacing the below code with a stored procedure with the following two lines
	// UPDATE Orders SET Orders.Paid = 1 WHERE Orders.OrderID IN (SELECT Payments.OrderID from Payments WHERE Payments.Paid = 0 and (ABS(Payments.Balance) <= 5.00))
	// UPDATE Orders SET Orders.Paid = 0 WHERE Orders.OrderID IN (SELECT Payments.OrderID from Payments WHERE Payments.Paid = 1 and (ABS(Payments.Balance) > 5.00))

	CSetPayments setPayments(&g_dbFlooring) ;
	//setPayments.m_strFilter = "Paid = 0 and (Balance >= -5.00 and Balance <= 5.00)";
	setPayments.m_strFilter = "Paid = 0 and (ABS(Balance) <= 5.00)";
	setPayments.Open() ;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter = "OrderID = -1";
	setOrders.Open() ;
	
	while (!setPayments.IsEOF())
	{
		setOrders.m_strFilter.Format("[OrderID] = '%d'", setPayments.m_OrderID) ;
		setOrders.Requery() ;
		setOrders.Edit() ;
		setOrders.m_Paid = TRUE ;
		setOrders.Update() ;
		setPayments.MoveNext() ;
	}

	//setPayments.m_strFilter = "Paid = 1 and (Balance < -5.00 or Balance > 5.00)";
	setPayments.m_strFilter = "Paid = 1 and (ABS(Balance) > 5.00)";
	setPayments.Requery();
	while (!setPayments.IsEOF())
	{
        setOrders.m_strFilter.Format("[OrderID] = '%d'", setPayments.m_OrderID) ;
		setOrders.Requery() ;
		setOrders.Edit() ;
		setOrders.m_Paid = FALSE ;
		setOrders.Update() ;
		setPayments.MoveNext() ;
	}

	if ((iNumSOSIDocs > 0) || (iNumSPNActions > 0))
	{
		//strMessage.Format("SOSI: Queued up %d Install Service Complete documents.\r\nSPN: Queued up %d Close PO Actions.", iNumSOSIDocs, iNumSPNActions);
		strMessage.Format("Queued up %d Close PO Actions.", iNumSPNActions);
		MessageBox(strMessage, "SPN Service Complete Activity");
	}
}


void CGridInvoicing::UpdateTotals()
{
	long lNumber = 0 ;
	long lAmount = 0 ;
	double fAmount = 0.0 ;
	for (long lRow = 0; lRow <GetNumberRows(); lRow++)
	{
		if (QuickGetBool(INVOICE, lRow))
		{
			lNumber++ ;
			fAmount += QuickGetNumber(AMOUNT, lRow) ;
		}
		
	}
	lAmount += long(fAmount*100) ;
	::PostMessage((this->GetParent())->m_hWnd, wm_INVOICED, lNumber, lAmount) ;
}

int CGridInvoicing::OnEditStart(int col, long row, CWnd **edit)
{
	int bEdit = FALSE ;

	if ((row >= 0) && (col >= 0) )
	{
		switch (col)
		{
			case AMOUNT: 
				*edit = &this->m_editNumeric ;
				bEdit = TRUE ;
				break ;
		}
	}
	return bEdit ;
}

BOOL CGridInvoicing::OnCanMove(int oldcol, long oldrow, int newcol, long newrow)
{
	UpdateTotals() ;
	return CCFGrid::OnCanMove(oldcol, oldrow, newcol, newrow) ;
}

int CGridInvoicing::AppendRow()
{
	int bResult = CCFGrid::AppendRow() ;
	long lRow = this->GetNumberRows() - 1;

	CUGCell cell ;

	for (int iCol = 0; iCol < this->GetNumberCols() ; iCol++)
	{
		GetCell(iCol, lRow, &cell) ;
		cell.SetBorder(UG_BDR_LTHIN | UG_BDR_TTHIN | UG_BDR_RTHIN | UG_BDR_BTHIN) ;
		cell.SetBorderColor(m_pen);
		SetCell(iCol, lRow, &cell) ;
	}
	return bResult ;
}

void CGridInvoicing::SetVendorID(int iVendorID)
{
	m_iVendorID = iVendorID;
	InitializeData();
}

int CGridInvoicing::ConfirmSendCompleteServiceDocs()
{
	int iResponse = -1;
	int iNumSOSIInstalls = 0;
	int iNumSPNInstalls = 0;

	for (long lRow = 0; lRow <GetNumberRows(); lRow++)
	{
		if ( QuickGetBool(INVOICE, lRow) && QuickGetBool(IS_INSTALL, lRow) )
		{
			if (QuickGetBool(IS_SOSI, lRow))
			{
				iNumSOSIInstalls++;
			}
			else
			{
				iNumSPNInstalls++;
			}
		}
	}

	if (iNumSOSIInstalls > 0)
	{
		CString strMessage;
		//strMessage.Format("You are about to COMPLETE INSTALL SERVICE on %d SOSI INSTALL POs and %d SPN POs.  Is this correct?", iNumSOSIInstalls, iNumSPNInstalls);
		strMessage.Format("You are about to COMPLETE INSTALL SERVICE on %d SPN POs.  Is this correct?", iNumSPNInstalls);
		iResponse = MessageBox(strMessage, "Complete Install Service?", MB_YESNOCANCEL);
	}

	return iResponse;
}

bool CGridInvoicing::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridInvoicing::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}