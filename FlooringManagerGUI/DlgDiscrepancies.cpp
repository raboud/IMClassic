// DlgDiscrepancies.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgDiscrepancies.h"

#include "SetDiscrepancies.h"
#include "SetCustomer.h"
#include "SetOrderBasicLaborDetails.h"
#include "SetVwDiscrepancies.h"
#include <math.h>
#include ".\dlgdiscrepancies.h"

// CDlgDiscrepancies dialog

IMPLEMENT_DYNAMIC(CDlgDiscrepancies, CDialog)
CDlgDiscrepancies::CDlgDiscrepancies(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiscrepancies::IDD, pParent)
{
	m_listPOs.RemoveAll();
}

CDlgDiscrepancies::~CDlgDiscrepancies()
{
}

void CDlgDiscrepancies::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDiscrepancies, CDialog)
END_MESSAGE_MAP()


// CDlgDiscrepancies message handlers

BOOL CDlgDiscrepancies::OnInitDialog()
{
	FixZipCodes() ;
	FixWorkPhoneNumbers() ;
	FixQuantity() ;
	FixPrice() ;

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_gridDiscrepancies.AttachGrid(this, IDC_DISCREPANCIESGRID) ;
	long lNumPOs = m_listPOs.GetCount();
	if (lNumPOs > 0)
	{
		m_gridDiscrepancies.SetPOList(&m_listPOs);
	}
	m_gridDiscrepancies.Update();
	m_gridDiscrepancies.ShowWindow(SW_SHOW);

	if (lNumPOs == 1)
	{
		CSetVwDiscrepancies setDisc(&g_dbFlooring);
		POSITION pos = m_listPOs.GetHeadPosition();
		setDisc.m_strFilter.Format("OrderID = %d", m_listPOs.GetNext(pos));
		setDisc.Open();
		if (!setDisc.IsEOF())
		{
			CString strText;
			strText.Format("SPN Discrepancies - %s (%s/%s)", setDisc.m_CustomerName, setDisc.m_StoreNumber, setDisc.m_PONumber);
            SetWindowText(strText);
		}
		setDisc.Close();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDiscrepancies::FixZipCodes()
{
	// DKB See if this is needed
	/*CString strSQL ;
	CSetDiscrepancies setDescrep(&g_dbFlooring) ;
	CSetCustomer setCustomer(&g_dbFlooring) ;

	setDescrep.Open() ;
	setCustomer.Open() ;

	setDescrep.m_strFilter = "([DiscrepancyTypeID] = 2) and ([DiscrepancySubTypeID] = 5)" ;
	setDescrep.Requery() ;

	CList<int,int> id2Delete ;

	while (!setDescrep.IsEOF())
	{
		if ((setDescrep.m_CurrentData.Trim().GetLength() == 6) && (setDescrep.m_NewData.Trim().GetLength() == 10))
		{
			if (setDescrep.m_NewData.Left(6) == setDescrep.m_CurrentData)
			{
				setCustomer.m_strFilter.Format("[CustomerID] = %d", setDescrep.m_CustOrStoreID) ;
				setCustomer.Requery() ;
				if (!setCustomer.IsEOF())
				{
					setCustomer.Edit() ;
					setCustomer.m_ZipCode = setDescrep.m_NewData ;
					setCustomer.Update() ;
					id2Delete.AddHead(setDescrep.m_ID) ;

				}
			}
		}
		setDescrep.MoveNext() ;
	}

	POSITION pos = id2Delete.GetHeadPosition() ;

	while (NULL != pos)
	{
		int id = id2Delete.GetAt(pos) ;

		strSQL.Format("DELETE FROM [Discrepancies] WHERE ([ID] = %d)", id);
		g_dbFlooring.ExecuteSQL(strSQL);

		id2Delete.GetNext(pos) ;
	}*/
}

void CDlgDiscrepancies::FixWorkPhoneNumbers() 
{
	// DKB See if this is needed
	/*CString strSQL ;
	CSetDiscrepancies setDescrep(&g_dbFlooring) ;
	CSetCustomer setCustomer(&g_dbFlooring) ;

	setDescrep.Open() ;
	setCustomer.Open() ;

	setDescrep.m_strFilter = "([DiscrepancyTypeID] = 2) and ([DiscrepancySubTypeID] = 9)" ;
	setDescrep.Requery() ;

	CList<int,int> id2Delete ;

	while (!setDescrep.IsEOF())
	{
		if (setDescrep.m_NewData == "")
		{
			id2Delete.AddHead(setDescrep.m_ID) ;
		}
		else if (setDescrep.m_CurrentData.Trim() == "(   )   -     Ext.")
		{
			setCustomer.m_strFilter.Format("[CustomerID] = %d", setDescrep.m_CustOrStoreID) ;
			setCustomer.Requery() ;
			if (!setCustomer.IsEOF())
			{
				setCustomer.Edit() ;
				setCustomer.m_WorkNumber = setDescrep.m_NewData ;
				setCustomer.Update() ;
				id2Delete.AddHead(setDescrep.m_ID) ;

			}
		}
		setDescrep.MoveNext() ;
	}

	POSITION pos = id2Delete.GetHeadPosition() ;

	while (NULL != pos)
	{
		int id = id2Delete.GetAt(pos) ;

		strSQL.Format("DELETE FROM [Discrepancies] WHERE ([ID] = %d)", id);
		g_dbFlooring.ExecuteSQL(strSQL);

		id2Delete.GetNext(pos) ;
	}*/
}

void CDlgDiscrepancies::FixQuantity() 
{
	// DKB See if this is needed
	/*CString strSQL ;
	CSetDiscrepancies setDescrep(&g_dbFlooring) ;
	CSetOrderBasicLaborDetails setBasicLaborDetails(&g_dbFlooring) ;

	setDescrep.Open() ;
	setBasicLaborDetails.Open() ;

	setDescrep.m_strFilter = "([DiscrepancyTypeID] = 3) and ([DiscrepancySubTypeID] = 14)" ;
	setDescrep.Requery() ;

	CList<int,int> id2Delete ;

	while (!setDescrep.IsEOF())
	{
		double fNewData = atof(setDescrep.m_NewData) ;
		float fCurrentData ;
		long lDetailId ;

		sscanf(setDescrep.m_CurrentData, "%d;%f", &lDetailId, &fCurrentData) ;
		if (fabs(fNewData - fCurrentData) < .01)
		{
			setBasicLaborDetails.m_strFilter.Format("[ID] = %d", lDetailId) ;
			setBasicLaborDetails.Requery() ;
			if (!setBasicLaborDetails.IsEOF())
			{
				setBasicLaborDetails.Edit() ;
				setBasicLaborDetails.m_InstallQuantity = fNewData ;
				setBasicLaborDetails.Update() ;
				id2Delete.AddHead(setDescrep.m_ID) ;

			}
		}
		else
		{
			setBasicLaborDetails.m_strFilter.Format("[ID] = %d", lDetailId) ;
			setBasicLaborDetails.Requery() ;
			if (!setBasicLaborDetails.IsEOF())
			{
				setDescrep.Edit() ;
				setDescrep.m_CustOrStoreID = setBasicLaborDetails.m_OrderID ;
				setDescrep.Update() ;
			}
			else
			{
				id2Delete.AddHead(setDescrep.m_ID) ;
			}
		}
		setDescrep.MoveNext() ;
	}

	POSITION pos = id2Delete.GetHeadPosition() ;

	while (NULL != pos)
	{
		int id = id2Delete.GetAt(pos) ;

		strSQL.Format("DELETE FROM [Discrepancies] WHERE ([ID] = %d)", id);
		g_dbFlooring.ExecuteSQL(strSQL);

		id2Delete.GetNext(pos) ;
	}*/
}

void CDlgDiscrepancies::FixPrice() 
{
	// DKB See if this is needed
	/*CString strSQL ;
	CSetDiscrepancies setDescrep(&g_dbFlooring) ;
	CSetCustomer setCustomer(&g_dbFlooring) ;
	CSetOrderBasicLaborDetails setBasicLaborDetails(&g_dbFlooring) ;

	setCustomer.Open() ;
	setBasicLaborDetails.Open() ;

	setDescrep.m_strFilter = "([DiscrepancyTypeID] = 3) and ([DiscrepancySubTypeID] = 15)" ;
	setDescrep.Open() ;

	CList<int,int> id2Delete ;

	while (!setDescrep.IsEOF())
	{
		float fCurrentData ;
		long lDetailId ;

		sscanf(setDescrep.m_CurrentData, "%d;%f", &lDetailId, &fCurrentData) ;

		setBasicLaborDetails.m_strFilter.Format("[ID] = %d", lDetailId) ;
		setBasicLaborDetails.Requery() ;
		if (!setBasicLaborDetails.IsEOF())
		{
			setDescrep.Edit() ;
			setDescrep.m_CustOrStoreID = setBasicLaborDetails.m_OrderID ;
			setDescrep.Update() ;
		}
		else
		{
			id2Delete.AddHead(setDescrep.m_ID) ;
		}
		setDescrep.MoveNext() ;
	}

	POSITION pos = id2Delete.GetHeadPosition() ;

	while (NULL != pos)
	{
		int id = id2Delete.GetAt(pos) ;

		strSQL.Format("DELETE FROM [Discrepancies] WHERE ([ID] = %d)", id);
		g_dbFlooring.ExecuteSQL(strSQL);

		id2Delete.GetNext(pos) ;
	}*/
}

void CDlgDiscrepancies::SetPOList(CPoList* pListPOs)
{
	m_listPOs.RemoveAll();
	m_listPOs.AddTail(pListPOs);
}
void CDlgDiscrepancies::OnOK()
{
	m_gridDiscrepancies.UpdateRecordSet();
	CDialog::OnOK();
}
