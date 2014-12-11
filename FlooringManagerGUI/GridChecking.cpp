/*----------------------------------------------------------------------
	Copyright © 2001-2003 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridInvoicing.cpp: implementation of the CGridChecking class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Flooring.h"
#include "GridChecking.h"
#include "SetOrderAndCustomer.h"
#include "SetCheckDetails.h"
#include "SetPayments.h"
#include "SetTotalPayment.h"
#include "SetCheckCBDetails.h"
#include "SetvwChargeback.h"
#include "DialogPo.h"
#include "DlgChargeBack.h"
#include "SetChecks.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGridChecking::CGridChecking()
	: m_iVendorID(-1)
{
	m_bDirty = false ;

	HighlightCurrentRow();
}

CGridChecking::~CGridChecking()
{
}

void CGridChecking::SetCheckID(int iCheckID)
{
	m_iCheckID = iCheckID ;
	InitializeData() ;
}

void CGridChecking::OnSetup()
{
	CCFGrid::OnSetup();

	// Get the index value of the font.
	int fontID = AddFont("Lucida Console", 14, FW_NORMAL);

	//Set the Grid's default font
	SetDefFont(fontID);

	AddColumn("  ID  ", ID);
	AddColumn("NAME                               ", NAME);
	AddColumn("PO NUMBER   ", PO_NUMBER);
	AddColumn("BALANCE   ", AMOUNT);
	AddColumn("INVOICED", INVOICE);
	AddColumn("  INV DATE   ", INVOICE_DATE);
	AddColumn("PAID", PAID);
	AddColumn("PAID AMOUNT", PAID_AMOUNT);

	InitColumnHeadings();

	CUGCell cell;

	EnableMenu(TRUE) ;
	EnableExcelBorders(TRUE) ;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(AMOUNT, &cell) ;
	cell.SetNumberDecimals(2) ;
	cell.SetDataType(UGCELLDATA_NUMBER) ;
	cell.SetFormatClass(&m_formatCurrency) ;
	SetColDefault(AMOUNT, &cell) ;

	GetColDefault(PAID_AMOUNT, &cell) ;
	cell.SetNumberDecimals(2) ;
	cell.SetDataType(UGCELLDATA_NUMBER) ;
	cell.SetFormatClass(&m_formatCurrency) ;
	SetColDefault(PAID_AMOUNT, &cell) ;

	GetColDefault(INVOICE, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	cell.SetReadOnly(TRUE);
	SetColDefault(INVOICE, &cell) ;

	GetColDefault(PAID, &cell) ;
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	SetColDefault(PAID, &cell) ;

	RECT			rect = {0,0,0,0};
	// Create a mask edit to use with ultimate grid mask edit
	m_editNumeric.Create(WS_VISIBLE,rect,this,125);

}

int CGridChecking::OnCellTypeNotify(long Id, int /* col */, long row, long msg, long param)
{
	CUGCell cell ;
	if ((Id == UGCT_CHECKBOX) && (msg == UGCT_CHECKBOXSET))
	{
		if (param == 1)
		{
			QuickSetNumber(PAID_AMOUNT, row, QuickGetNumber(AMOUNT, row)) ;
			QuickSetNumberDecimals(PAID_AMOUNT, row, 2) ;
			QuickSetReadOnly(PAID_AMOUNT, row, false) ;
			QuickSetNumber(AMOUNT, row, 0) ;

			SetRowBackColor(row, RGB(192, 192, 192));
		}
		else
		{
			double dBalance = QuickGetNumber(AMOUNT, row) ;
			double dPaid = QuickGetNumber(PAID_AMOUNT, row) ;
			QuickSetNumber(AMOUNT, row, dBalance + dPaid) ;

			QuickSetNumber(PAID_AMOUNT, row, 0) ;
			QuickSetReadOnly(PAID_AMOUNT, row, true) ;

			SetRowBackColor(row, RGB(255,255,255));
		}
		UpdateTotals() ;
		m_bDirty = true ;
		this->RedrawRow(row) ;
	}
	return TRUE ;
}

void CGridChecking::InitializeData()
{
	CUGCell cell ;

	CWaitCursor curWait ;

	// make sure we are empty
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	// retrieve the vendor id for the current check
	CSetChecks setChecks(&g_dbFlooring);
	setChecks.m_strFilter.Format("[CheckID] = %d", m_iCheckID);
	setChecks.Open();
	m_iVendorID = setChecks.m_VendorID;
	setChecks.Close();

	CSetOrderAndCustomer setCombined(&g_dbFlooring) ;

	// filter the orders
	CString strTemp;
	strTemp.Format("[VendorID] = %d", m_iVendorID);
	strTemp += " AND [PAID] = '0' AND [Warrenty] = '0' AND [Cancelled] = '0'" ;
	setCombined.m_strFilter = strTemp;
	
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
		QuickSetBool(INVOICE, lRow, (setCombined.m_Billed == TRUE)) ;

		double fTotal = atof(setCombined.m_TotalAmount) ;

		if(setCombined.m_Billed)
		{
			QuickSetNumber(AMOUNT, lRow, atof(setCombined.m_BilledAmount) - fTotal) ;
			QuickSetText(INVOICE_DATE, lRow, setCombined.m_BilledDate.Format("%m/%d/%Y")) ;
		}
		else
		{
			if (!setCombined.IsFieldNull(&setCombined.m_XMLOrderCostAmount))
			{
				QuickSetNumber(AMOUNT, lRow, (((atol(setCombined.m_XMLOrderCostAmount) + 50) / 100) / 100.) - fTotal) ;
			}
			else
			{
				QuickSetNumber(AMOUNT, lRow, atof(setCombined.m_OrderAmount) - fTotal) ;
			}
			QuickSetText(INVOICE_DATE, lRow, "") ;
		}
		QuickSetBool(PAID, lRow, (setCombined.m_Paid == TRUE)) ;
		QuickSetReadOnly(PAID, lRow, false) ;
		setCombined.MoveNext() ;
	}

	CSetvwChargeback setVwChargeBack(&g_dbFlooring) ;
	strTemp.Format("[VendorID] = %d", m_iVendorID);
	setVwChargeBack.m_strFilter = strTemp + " AND (([Approved] = '1' AND [Balance] > 0) OR ([Balance] < -5.0))" ;
	setVwChargeBack.Open() ;
	while(!setVwChargeBack.IsEOF())
	{
		AppendRow() ;
		long lRow = this->GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("CB%d", setVwChargeBack.m_ChargeBackID) ;
		QuickSetText(ID, lRow, strID) ;

		if (setVwChargeBack.m_LastName.IsEmpty())
		{
			QuickSetText(NAME, lRow, setVwChargeBack.m_Name) ;
		}
		else
		{
			CString strName ;
			strName = setVwChargeBack.m_LastName + ", " + setVwChargeBack.m_FirstName ;
			QuickSetText(NAME, lRow, strName) ;
		}

		QuickSetText(PO_NUMBER, lRow, setVwChargeBack.m_Number) ;
		QuickSetNumber(AMOUNT, lRow, setVwChargeBack.m_Balance) ;
		QuickSetBool(INVOICE, lRow, true) ;
		QuickSetText(INVOICE_DATE, lRow, setVwChargeBack.m_IssueDate.Format("%m/%d/%Y")) ;
		QuickSetBool(PAID, lRow, false) ;

		for (int iCol = 0; iCol < this->GetNumberCols(); iCol++)
		{
			GetCell(iCol, lRow, &cell) ;
			cell.SetTextColor(RGB(255, 0, 0) ) ;
			SetCell(iCol, lRow, &cell) ;
		}

		QuickSetReadOnly(PAID, lRow, false) ;
		setVwChargeBack.MoveNext() ;
	}

	CSetCheckCBDetail setCbTaken(&g_dbFlooring);
	setCbTaken.m_strFilter.Format("[CheckID] = '%d'", this->m_iCheckID) ;
	setCbTaken.Open() ;
	
	while(!setCbTaken.IsEOF())
	{
		AppendRow() ;
		long lRow = this->GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("CT%d", setCbTaken.m_CheckCBDetailID) ;
		QuickSetText(ID, lRow, strID) ;
		setVwChargeBack.m_strFilter.Format("[ChargeBackID] = '%d'", setCbTaken.m_ChargeBackID) ;
		setVwChargeBack.Requery() ;

		if (setVwChargeBack.m_LastName.IsEmpty())
		{
			QuickSetText(NAME, lRow, setVwChargeBack.m_Name) ;
		}
		else
		{
			CString strName ;
			strName = setVwChargeBack.m_LastName + ", " + setVwChargeBack.m_FirstName ;
			QuickSetText(NAME, lRow, strName) ;
		}

		QuickSetText(PO_NUMBER, lRow, setVwChargeBack.m_Number) ;
		QuickSetNumber(AMOUNT, lRow, setVwChargeBack.m_Balance) ;
		QuickSetBool(INVOICE, lRow, true) ;
		QuickSetText(INVOICE_DATE, lRow, setVwChargeBack.m_IssueDate.Format("%m/%d/%Y")) ;
		QuickSetBool(PAID, lRow, true) ;
		QuickSetNumber(PAID_AMOUNT, lRow, setCbTaken.m_Amount * -1.0) ;

		for (int iCol = 0; iCol < this->GetNumberCols(); iCol++)
		{
			GetCell(iCol, lRow, &cell) ;
			cell.SetBackColor(RGB(255,0,0) ) ;
			SetCell(iCol, lRow, &cell) ;
		}

		QuickSetReadOnly(PAID, lRow, false) ;
		setCbTaken.MoveNext() ;
	}

	CSetPayments setPayments(&g_dbFlooring) ;
	setPayments.m_strFilter.Format("CheckID = '%d'", this->m_iCheckID) ;
	setPayments.Open() ;
	while (!setPayments.IsEOF())
	{
		AppendRow() ;
		long lRow = this->GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("PY%d", setPayments.m_CheckDetailID) ;
		QuickSetText(ID, lRow, strID) ;

		CString strName ;
		strName = setPayments.m_LastName + ", " + setPayments.m_FirstName ;
		

		QuickSetText(NAME, lRow, strName) ;
		QuickSetText(PO_NUMBER, lRow, setPayments.m_PurchaseOrderNumber) ;
		QuickSetBool(INVOICE, lRow, (setPayments.m_Billed == TRUE)) ;
		if(setPayments.m_Billed)
		{
			QuickSetNumber(AMOUNT, lRow, atof(setPayments.m_Balance)) ;
			QuickSetText(INVOICE_DATE, lRow, setPayments.m_BilledDate.Format("%m/%d/%Y")) ;
		}
		QuickSetBool(PAID, lRow, (TRUE)) ;
		QuickSetNumber(PAID_AMOUNT, lRow, atof(setPayments.m_Amount)) ;
		for (int iCol = 0; iCol < this->GetNumberCols(); iCol++)
		{
			GetCell(iCol, lRow, &cell) ;
			cell.SetBackColor(RGB(0,255,0) ) ;
			SetCell(iCol, lRow, &cell) ;
		}

		QuickSetReadOnly(PAID, lRow, false) ;
		setPayments.MoveNext() ;
	}

	EnableUpdate(TRUE);
	RedrawAll() ;

	UpdateTotals() ;
	setCombined.Close() ;
	m_bDirty = false ;
}

void CGridChecking::UpdateRecordSet()
{
	bool bError = false ;

	CSetCheckDetails setDetails(&g_dbFlooring) ;
	setDetails.m_strFilter = "CheckDetailID = -1";
	setDetails.Open() ;

	CSetCheckCBDetail setCheckCB(&g_dbFlooring) ;
	setCheckCB.m_strFilter = "CheckCBDetailID = -1";
	setCheckCB.Open() ;

	CSetOrders setOrders(&g_dbFlooring) ;
	setOrders.m_strFilter = "OrderID = -1";
	setOrders.Open() ;

	try
	{

		for (long lRow = 0; lRow <GetNumberRows(); lRow++)
		{
			CString strId = QuickGetText(ID, lRow) ;
			if (QuickGetBool(PAID, lRow))
			{
				if ((strId.Left(2) != "CB") && (strId.Left(2) != "PY") && (strId.Left(2) != "CT"))
				{
					try
					{
						setDetails.AddNew() ;
						setDetails.m_CheckID = this->m_iCheckID ;
						setDetails.m_OrderID = atoi(QuickGetText(ID, lRow));
						setDetails.m_Amount = QuickGetText(PAID_AMOUNT, lRow) ;
						setDetails.m_Amount.Remove('$');
						setDetails.Update() ;
					}
					catch(...)
					{
						bError = true ;
					}
				}
				else if (strId.Left(2) == "CB")
				{
					try
					{
						setCheckCB.AddNew() ;
						setCheckCB.m_CheckID = this->m_iCheckID ;
						long lCBId = atol(strId.Mid(2)) ;
						setCheckCB.m_ChargeBackID = lCBId ;
						setCheckCB.m_Amount = QuickGetNumber(PAID_AMOUNT, lRow) * -1.0; ;
						setCheckCB.Update() ;
					}
					catch(...)
					{
						bError = true ;
					}
				}
				else if (strId.Left(2) == "CT")
				{
					try
					{
						setCheckCB.m_strFilter.Format("[CheckCBDetailID] = '%s'", strId.Mid(2)) ;
						setCheckCB.Requery() ;
						setCheckCB.Edit() ;
						setCheckCB.m_Amount = QuickGetNumber(PAID_AMOUNT, lRow) * -1.0;
						setCheckCB.Update() ;
					}
					catch(...)
					{
						bError = true ;
					}
				}
				else if (strId.Left(2) == "PY")
				{
					try
					{
						setDetails.m_strFilter.Format("[CheckDetailID] = '%s'", strId.Mid(2)) ;
						setDetails.Requery() ;
						setDetails.Edit() ;
						setDetails.m_Amount = QuickGetText(PAID_AMOUNT, lRow) ;
						setDetails.m_Amount.Remove('$');
						setDetails.Update() ;
					}
					catch(...)
					{
						bError = true ;
					}
				}
			}
			else
			{
				if (strId.Left(2) == "PY")
				{
					try
					{
						setDetails.m_strFilter.Format("CheckDetailID = '%s'", strId.Mid(2)) ;
						setDetails.Requery() ;
						CSetOrderAndCustomer set(&g_dbFlooring) ;
						
						set.m_strFilter.Format("[OrderID] = '%d'", setDetails.m_OrderID) ;
						set.Open() ;

						setDetails.Delete() ;
						
						// make sure we found the order ID (exception thrown if not)
						int Id = set.m_OrderID ;

						//double fBalance = atof(set.m_TotalAmount) - atof(set.m_BilledAmount) ;
                        double fBalance = QuickGetNumber(AMOUNT, lRow) ;
						
						if (fabs((fBalance)) > 5)
						{
							try
							{
								setOrders.m_strFilter.Format("[OrderID] = '%d'", Id) ;
								setOrders.Requery() ;
								setOrders.Edit() ;
								setOrders.m_Paid = FALSE ;
								if (set.m_MarkBilledWhenPaid)
								{
									setOrders.m_Billed = FALSE;
									setOrders.m_BilledAmount = _T("0");
								}
								setOrders.Update() ;
							}
							catch(...)
							{
								bError = true ;
							}
						}
						set.Close() ;
					}
					catch(...)
					{
						bError = true ;
					}
				}
				else if (strId.Left(2) == "CT")
				{
					try
					{
						setCheckCB.m_strFilter.Format("[CheckCBDetailID] = '%s'", strId.Mid(2)) ;
						setCheckCB.Requery() ;
						setCheckCB.Delete() ;
					}
					catch(...)
					{
						bError = true ;
					}
				}
			}
		}

		CSetPayments setPayments(&g_dbFlooring) ;
		setPayments.m_strFilter.Format("[CheckID] = '%d'", this->m_iCheckID) ;
		setPayments.Open() ;

		CSetOrderAndCustomer set(&g_dbFlooring) ;
		set.Open();

		while (!setPayments.IsEOF())
		{
			if (fabs(atof(setPayments.m_Balance)) <= 5)
			{
				try
				{
					setOrders.m_strFilter.Format("[OrderID] = '%d'", setPayments.m_OrderID) ;
					setOrders.Requery() ;
					setOrders.Edit() ;
					setOrders.m_Paid = TRUE ;
					set.m_strFilter.Format("[OrderID] = '%d'", setPayments.m_OrderID) ;
					set.Requery();
					if (set.m_MarkBilledWhenPaid)
					{
						setOrders.m_Billed = TRUE;
						setOrders.m_BilledAmount = setOrders.m_OrderAmount;  // just set billed amount to the order amount
						setOrders.m_BilledDate = setPayments.m_CheckDate;
					}
					
					setOrders.Update() ;
				}
				catch(...)
				{
					bError = true ;
				}
			}
			setPayments.MoveNext() ;
		}
		set.Close();
		setPayments.Close();
	}
	catch(...)
	{
		bError = true ;
	}

	setDetails.Close() ;
	setCheckCB.Close() ;
	setOrders.Close() ;

	if (bError)
	{
		AfxMessageBox("An Error Occurred. You will need to verify the check.") ;
	}
}

void CGridChecking::UpdateTotals()
{
	long lNumber = 0 ;
	long lAmount = 0 ;
	for (long lRow = 0; lRow <GetNumberRows(); lRow++)
	{
		if (QuickGetBool(PAID, lRow))
		{
			lNumber++ ;
			double fTemp = QuickGetNumber(PAID_AMOUNT, lRow) ;
			long lTemp ;
			if (fTemp < 0)
			{
				lTemp = long((fTemp * 100) - .5) ;
			}
			else
			{
				lTemp = long((fTemp * 100) + .5) ;
			}
			lAmount += lTemp ;
		}
		
	}
//	lAmount = long((fAmount * 100) + .0000001) ;
	::PostMessage((this->GetParent())->m_hWnd, wm_CHECKING, lNumber, lAmount) ;
}

int CGridChecking::OnEditStart(int col, long row, CWnd **edit)
{
	int bEdit = FALSE ;

	if ((row >= 0) && (col >= 0) )
	{
		switch (col)
		{
			case PAID_AMOUNT: 
				m_dOriginalPaid = QuickGetNumber(PAID_AMOUNT, row) ;
				*edit = &this->m_editNumeric ;
				bEdit = TRUE ;
				break ;
		}
	}
	return bEdit ;
}

int CGridChecking::OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag)
{
	if (cancelFlag == FALSE)
	{
		int iReturn = CCFGrid::OnEditFinish(col, row, edit, string, cancelFlag) ;
		if (iReturn == TRUE)
		{
			double dBalance = QuickGetNumber(AMOUNT, row) ;
			double dPaid = atof(string) ;
			QuickSetNumber(AMOUNT, row, dBalance + m_dOriginalPaid - dPaid) ;
			RedrawCell(AMOUNT, row) ;
		}
		return iReturn ;
	}
	else
	{
		return CCFGrid::OnEditFinish(col, row, edit, string, cancelFlag) ;
	}
}

BOOL CGridChecking::OnCanMove(int oldcol, long oldrow, int newcol, long newrow)
{
	UpdateTotals() ;
	return CCFGrid::OnCanMove(oldcol, oldrow, newcol, newrow) ;
}


int CGridChecking::AppendRow()
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

//bool CGridChecking::IsDirty()
//{
//	return m_bDirty ;
//}

void CGridChecking::OnMenuCommand(int /* col */,long row,int section,int item)
{
	if ((row < this->GetNumberRows()) && (row >= 0))
	{
		if (section == UG_GRID)
		{
			if (item == 2000)
			{
				CString strID = QuickGetText(ID, row) ;
				long lID ;

				if( strID.Left(2) == "CT")
				{
					lID = atol(strID.Mid(2)) ;

					CSetCheckCBDetail setCheckCB(&g_dbFlooring) ;
					setCheckCB.m_strFilter.Format("[CheckCBDetailID] = '%d'", lID) ;
					setCheckCB.Open() ;
					CDlgChargeBack dlgCB(this, setCheckCB.m_ChargeBackID) ;
					if (dlgCB.DoModal() == IDOK)
					{
					}
				}
				else if (strID.Left(2) == "CB")
				{
					lID = atol(strID.Mid(2)) ;
					CDlgChargeBack dlgCB(this, lID) ;
					if (dlgCB.DoModal() == IDOK)
					{
					}
				}
				else if (strID.Left(2) == "PY")
				{
					lID = atol(strID.Mid(2)) ;

					CSetCheckDetails setDetails(&g_dbFlooring) ;
					setDetails.m_strFilter.Format("[CheckDetailID] = '%d'", lID) ;
					setDetails.Open() ;

					CDlgPo dlgPo ;
					dlgPo.SetOrderId(setDetails.m_OrderID) ;

					if (dlgPo.DoModal() == IDOK)
					{
//						Update(m_lCustomerId) ;
					}
					setDetails.Close() ;

				}
				else
				{
					lID = atol(strID) ;

					CDlgPo dlgPo ;
					dlgPo.SetOrderId(lID) ;

					if (dlgPo.DoModal() == IDOK)
					{
// TODO - rar get updated bill amount						Update(m_lCustomerId) ;
					}
				}
			}
		}
}
}

int CGridChecking::OnMenuStart(int /* col */,long row,int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			AddMenuItem(2000, "Edit") ;
		}
	}
	return TRUE ;

}

bool CGridChecking::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return m_bDirty ;
}

bool CGridChecking::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}