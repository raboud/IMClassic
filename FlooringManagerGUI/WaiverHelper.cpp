#include "stdafx.h"
#include "WaiverHelper.h"
#include "vwWorkOrderMaterialsChecklist.h"
#include "SetSettings.h"

CWaiverHelper::CWaiverHelper(void)
: m_setCustomer(&g_dbFlooring)
{
	m_setCustomer.m_strFilter = "CustomerID = -1";
	m_setCustomer.Open() ;

	m_setOrders.m_strFilter = "OrderID = -1";
	m_setOrders.Open();

	m_strErrorMessage = "";
}

CWaiverHelper::~CWaiverHelper(void)
{
	m_setCustomer.Close() ;
	m_setOrders.Close();
}

bool CWaiverHelper::SetPoList(CPoList* plistPOs)
{
	bool bOk = true ;

	m_PoList.AddHead(plistPOs) ;

	InitializeFilters();

	m_setOrders.MoveFirst() ;
	
	m_bScheduled = false ;
	COleDateTime dateStart ;
	COleDateTime dateEnd ;
	m_strPOList = "";
	CString strTemp;

	while (!m_setOrders.IsEOF())
	{
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
		m_setOrders.MoveNext() ;
	}

	m_setOrders.MoveFirst() ;

	if (!m_bScheduled)
	{
		int iResponse = AfxMessageBox("Some of the selected P.O.s are not scheduled. Continue?", MB_YESNO, NULL);
		if (iResponse != IDYES)
		{
			bOk = false;
		}
	}

	/*if (bOk)
	{
		SetParameters();
	}*/

	return bOk ;

}

void CWaiverHelper::InitializeFilters()
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

//bool CWaiverHelper::SetParameters()
//{
	//// set order ids
	//POSITION pos = m_PoList.GetHeadPosition() ;
	//while (pos)
	//{
	//	vtValue.intVal = m_PoList.GetNext(pos);
	//	//m_ReportDlg.AddParameter("OrderIDs", vtValue);
	//}

	//vtValue.vt = VT_BOOL;
	//if (m_bScheduled && m_bAM)
	//{
	//	vtValue.boolVal = TRUE;
	//}
	//else
	//{
	//	vtValue.boolVal = FALSE;
	//}
	////m_ReportDlg.AddParameter("ScheduledAM", vtValue);

	//// set scheduled date
	//CString strTemp = "";
	//if (m_bScheduled)
	//{
	//	strTemp = m_dateScheduled.Format("%m/%d/%Y") ;
	//}

	//vtValue.vt = VT_BSTR;
	//vtValue.bstrVal = strTemp.AllocSysString();
	////m_ReportDlg.AddParameter("ScheduledDate", vtValue);

	//return true;
//}

CString CWaiverHelper::GetScheduledAM()
{
	return (m_bScheduled && m_bAM) ? "true" : "false";
}

CString CWaiverHelper::GetScheduledDate()
{
	return m_dateScheduled.Format("%m/%d/%Y");
}

CString CWaiverHelper::GetShowAMPM()
{
	CSetSettings setSettings(&g_dbFlooring);
	return setSettings.GetSetting("WaiverShowAMPM", "1");
}