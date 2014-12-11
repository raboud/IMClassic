/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridChargeBacks.cpp: implementation of the CGridChargeBacks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridChargeBacks.h"
#include "SetvwChargeback.h"
#include "DlgChargeBack.h"
#include "DlgFind.h"
#include "DlgSelectCustomer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridChargeBacks::CGridChargeBacks()
{
	HighlightCurrentRow();
}

CGridChargeBacks::~CGridChargeBacks()
{
}

void CGridChargeBacks::OnSetup(void)
{
	CCFGrid::OnSetup() ;

	AddColumn("   ID   ", ID);
	AddColumn("  Number ", CB_NUMBER);
	AddColumn(" Original PO ", ORIG_PO);
	AddColumn("       Customer Name       ", CUSTOMER_NAME);
	AddColumn(" App. #", APPROVAL_NUMBER);

	InitColumnHeadings();
    
	EnableMenu(TRUE) ;
	EnableExcelBorders(TRUE) ;

	CUGCell cell;

	GetColDefault(ID, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(ID, &cell) ;

	GetColDefault(CB_NUMBER, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(CB_NUMBER, &cell) ;

	GetColDefault(APPROVAL_NUMBER, &cell) ;
	cell.SetNumberDecimals(0) ;
	SetColDefault(APPROVAL_NUMBER, &cell) ;
}

void CGridChargeBacks::Update(void)
{
	CWaitCursor cur ;
	EnableUpdate(FALSE);
	
	// get rid of stale data
	while(GetNumberRows())
	{
		DeleteRow(0) ;
	} ;

	CSetvwChargeback setCB(&g_dbFlooring) ;
	setCB.m_strSort = "ChargeBackID DESC" ;
	setCB.Open() ;
	while (!setCB.IsEOF())
	{
		AppendRow() ;
		long lRow = this->GetNumberRows() - 1 ;

		CString strID ;
		strID.Format("%d", setCB.m_ChargeBackID) ;
		QuickSetText(ID, lRow, strID) ;

		QuickSetText(CB_NUMBER, lRow, setCB.m_Number) ;

		QuickSetText(ORIG_PO, lRow, setCB.m_OriginalPO) ; 

		if (setCB.IsFieldNull(&setCB.m_OrderID))
		{
			QuickSetText(CUSTOMER_NAME, lRow, setCB.m_Name) ;
		}
		else
		{
			CString strName = setCB.m_LastName + ", " + setCB.m_FirstName ;
			QuickSetText(CUSTOMER_NAME, lRow, strName) ;
		}
		if (setCB.m_Approved)
		{
			CString strApproval ;
			strApproval.Format("%d", setCB.m_ApprovalNumber) ;
			QuickSetText(APPROVAL_NUMBER, lRow, strApproval) ; 
		}
		else
		{
			QuickSetText(APPROVAL_NUMBER, lRow, "N/A") ; 
		}
		setCB.MoveNext() ;
	}
	EnableUpdate(TRUE);
	RedrawAll() ;
}

int CGridChargeBacks::OnMenuStart(int /* col */, long row, int section)
{
	if (section == UG_GRID)
	{
		//* Empty the Menu!!
		EmptyMenu();

		if ((row >= 0) && (row < this->GetNumberRows()))
		{
			AddMenuItem(EDIT_CB, "Edit") ;
			AddMenuItem(NEW_CB, "New") ;
		}
	}
	return TRUE ;
}

void CGridChargeBacks::OnMenuCommand(int /* col */, long row, int section, int item)
{
	if (section == UG_GRID)
	{
		switch (item)
		{
		case EDIT_CB:
			EditCB(row) ;
			break ;

		case NEW_CB:
			NewCB() ;
			break ;

		default:
			break ;
		}
	}
}

void CGridChargeBacks::OnSH_DClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	EditCB(row) ;
}

void CGridChargeBacks::OnDClicked(int /* col */,long row, RECT * /* rect */, POINT * /* point */, BOOL /* processed */)
{
	EditCB(row) ;
}

void CGridChargeBacks::EditCB(long row)
{
	long lID = atol(QuickGetText(ID, row)) ;
	CDlgChargeBack dlg(this, lID) ;
	if (dlg.DoModal() == IDOK)
	{
		Update() ;
	}
}

void CGridChargeBacks::NewCB()
{
	CString strStoreNumber;
	CString strPONumber = GetPONumber(strStoreNumber);

	if (strPONumber.GetLength() > 0)
	{
		CDlgChargeBack dlg(this) ;
		dlg.SetOriginalPO(strPONumber);
		dlg.SetStoreNumber(strStoreNumber);
		if (dlg.DoModal() == IDOK)
		{
			Update() ;
		}
	}
}

CString CGridChargeBacks::GetPONumber(CString& strStoreNumber)
{
	CString strPONumber = "";
	strStoreNumber = "";

	CDlgFind dlg(CDlgFind::EnFIND_TYPE_PO, this) ;
	dlg.SetCaption("Enter PO Number") ;
	bool bContinue = true;
	if (dlg.DoModal() == IDOK)
	{
		CDlgSelectCustomer dlgCustomer;
		int iNumRecords = dlgCustomer.SetPONumber(dlg.m_strNumber, dlg.m_strStoreNumber);
		if ( iNumRecords > 1 )
		{
			if ( dlgCustomer.DoModal() != IDOK )
			{
				bContinue = false;
			}
		}
		else if ( iNumRecords == 0 )
		{
			MessageBox("PO Number Not Found!", "Error") ;
			bContinue = false;
		}

		if (bContinue)
		{
			strPONumber = dlg.m_strNumber;
			strStoreNumber = dlg.m_strStoreNumber;
		}
	}

	return strPONumber;
}

bool CGridChargeBacks::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridChargeBacks::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}