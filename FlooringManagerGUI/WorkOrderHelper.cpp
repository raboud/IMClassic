#include "stdafx.h"
#include "Globals.h"
#include "WorkOrderHelper.h"
#include "vwWorkOrderMaterialsChecklist.h"

CWorkOrderHelper::CWorkOrderHelper(void)
: m_setCustomer(&g_dbFlooring)
{
	m_setCustomer.Open() ;
	m_setOrders.Open();
	m_strErrorMessage = "";
	m_iCustomerID = -1;
	m_strPOList = "";
	m_bHasStorePickup = false;
}

CWorkOrderHelper::~CWorkOrderHelper(void)
{
	m_setCustomer.Close() ;
	m_setOrders.Close();
}

bool CWorkOrderHelper::SetPoList(CPoList* plistPOs)
{
	bool bOk = true ;

	m_PoList.AddHead(plistPOs) ;
	InitializeFilters() ;

	m_setOrders.MoveFirst() ;
	m_bScheduled = false ;
	COleDateTime dateStart ;
	COleDateTime dateEnd ;
	m_strPOList = "";
	CString strTemp;

	bool bAlertsExist = false;

	while (!m_setOrders.IsEOF())
	{
		if (m_strPOList != "")
		{
			m_strPOList += ", ";
		}
		m_strPOList += m_setOrders.m_PurchaseOrderNumber;
		
		if (m_setOrders.m_Scheduled)
		{
			if (!m_bScheduled)
			{
				m_bScheduled = m_setOrders.m_Scheduled == TRUE  ;
				m_bAM = m_setOrders.m_ScheduledAM == TRUE  ;
				m_dateScheduled = m_setOrders.m_ScheduleStartDate ;

				dateStart = COleDateTime(m_dateScheduled.GetYear(), m_dateScheduled.GetMonth(), m_dateScheduled.GetDay(), 0, 0, 0) ;
				dateEnd = COleDateTime(m_dateScheduled.GetYear(), m_dateScheduled.GetMonth(), m_dateScheduled.GetDay(), 23, 59, 59) ;
			}
			else
			{
				if ((m_setOrders.m_ScheduleStartDate > dateEnd) || (m_setOrders.m_ScheduleStartDate < dateStart))
				{
					bOk = false ;
					m_strErrorMessage = "There is a schedule date mismatch in the selected P.O.s";
				}
				else if ((m_setOrders.m_ScheduledAM == TRUE)!= m_bAM)
				{
					bOk = false ;
					m_strErrorMessage = "One or more P.O.s are scheduled for different times of the day.";
				}
			}
		}

		if (!bAlertsExist)
		{
			bAlertsExist = HasAlerts(m_setOrders.m_OrderID);
		}

		m_setOrders.MoveNext() ;
	}
	m_setOrders.MoveFirst() ;

	if (bOk && m_bScheduled)
	{
		while (!m_setOrders.IsEOF())
		{
			if ((!m_setOrders.m_Scheduled) && (!HasAlerts(m_setOrders.m_OrderID)))
			{
				m_setOrders.Edit() ;
				m_setOrders.m_Scheduled = m_bScheduled ;
				m_setOrders.m_ScheduledAM  = m_bAM ;
				m_setOrders.m_ScheduleStartDate	= dateStart ;
				m_setOrders.Update();
			}
			m_setOrders.MoveNext() ;
		}

		m_setOrders.MoveFirst() ;
		SetParameters();
	}
	else
	{
		int iResponse = -1;
		bool bContinue = true;
		if (bAlertsExist)
		{
			iResponse = AfxMessageBox("Alerts exist for at least one of the selected POs. Continue?", MB_YESNO, NULL);
			if (iResponse != IDYES)
			{
				bContinue = false;
			}
		}

		if (bContinue && (!m_bScheduled))
		{
			int iResponse = AfxMessageBox("The selected P.O.s are not scheduled. Continue?", MB_YESNO, NULL);
			if (iResponse == IDYES)
			{
				SetParameters();
			}
			else
			{
				bOk = false;
			}
		}
	}

	return bOk ;
}

void CWorkOrderHelper::InitializeFilters()
{
	CString strTemp ;
	CString strFilter ;

	POSITION pos = m_PoList.GetHeadPosition() ;
	bool bFirst = true ;
	while (pos)
	{
		strTemp.Format("[OrderID] = '%d'", m_PoList.GetNext(pos) ) ;
		if (!bFirst)
		{
			strFilter += " OR " ;
		}
		bFirst = false ;
		strFilter += strTemp ;
	} 

	m_setOrders.m_strFilter = strFilter ;
	m_setOrders.Requery() ;

}

bool CWorkOrderHelper::SetParameters()
{
	CString strOrderIDSQLFilter = "";
	CString temp;
    
	POSITION pos = m_PoList.GetHeadPosition() ;
	while (pos)
	{
		temp.Format("OrderID = %d", m_PoList.GetNext(pos));
		if (strOrderIDSQLFilter.GetLength() > 0)
		{
			strOrderIDSQLFilter += " OR ";
		}
		strOrderIDSQLFilter += temp;
	}

	// set cust id
	ASSERT(m_setOrders.IsEOF() == FALSE );
	m_iCustomerID = m_setOrders.m_CustomerID;

	m_setCustomer.m_strFilter.Format("[CustomerID] = %d", m_setOrders.m_CustomerID);
	m_setCustomer.Requery();

	CvwWorkOrderMaterialsChecklist setMaterials(&g_dbFlooring);
	setMaterials.m_strFilter = "(" + strOrderIDSQLFilter + ") AND Status = 'STORE PICKUP'";
	setMaterials.Open();

	m_bHasStorePickup = !setMaterials.IsEOF();

	setMaterials.Close();

	return true;
}

bool CWorkOrderHelper::HasAlerts(int iOrderID)
{
	return (CGlobals::OrderHasAlerts(iOrderID, false) || (CGlobals::OrderIsReviewed(iOrderID) == false));
}

CString CWorkOrderHelper::GetPOList()
{
	return m_strPOList;
}

CString CWorkOrderHelper::GetScheduledDate()
{
	CString strDate = m_dateScheduled.Format("%m/%d/%Y");
	return strDate;
}

CString CWorkOrderHelper::GetCustomerID()
{
	CString strCustomerID;
	strCustomerID.Format("%d", m_iCustomerID);
	return strCustomerID;
}

CString CWorkOrderHelper::GetShowStorePickup()
{
	return m_bHasStorePickup ? "true" : "false";
}