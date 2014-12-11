/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// GridSchedule.cpp: implementation of the CGridSchedule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flooring.h"
#include "GridSchedule.h"

#include "SetMaterialType.h"
#include "SetViewOrderSOMerchandiseDetails.h"
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

CGridSchedule::CGridSchedule()
: m_setOrders(&g_dbFlooring)
{
	m_listSOSIPOsWithModifiedSchedules.RemoveAll();
	m_listSPNPOsWithModifiedSchedules.RemoveAll();
	m_listPOsWithModifiedSchedules.RemoveAll();
	m_bRescheduled = false;
	m_bIsMeasure = false;
}

CGridSchedule::~CGridSchedule()
{
	m_setOrders.Close() ;
}

void CGridSchedule::OnSetup()
{
	CCFGrid::OnSetup() ;
	struct
	{
		int		iRow ;
		char*	pString ;
		int		iCol ;
	} asuHeading1[] = {	{-1, "   ID   ",					ID },
						{-1, "PO Number  ",					PO },
						{-1, "Material Type          ",		MATERIAL_TYPE},
						{-1, "Size   ",						MAT_SIZE},
						{-1, "Schedule",					SCHEDULE}} ;


	SetNumberCols (LAST, false) ;

	//Add the Column Heading to the grid
	for (int iIndex = 0; iIndex < sizeof(asuHeading1) / sizeof(asuHeading1[0]); iIndex++)
	{
		QuickSetText(asuHeading1[iIndex].iCol, asuHeading1[iIndex].iRow, asuHeading1[iIndex].pString);
	}

	BestFit(-1, LAST - 1, 0, UG_BESTFIT_TOPHEADINGS) ;
//	Fill() ;
}

void CGridSchedule::Update()
{
	EnableUpdate(FALSE);

	for (long lRow = 0; lRow <GetNumberRows(); lRow++)
	{
		CString strId = QuickGetText(ID, lRow) ;
		m_setOrders.m_strFilter.Format("OrderID = '%s'", strId) ;
		m_setOrders.Requery() ;

		m_setOrders.Edit() ;

		BOOL bScheduling = QuickGetBool(SCHEDULE, lRow) ;
		//bool bScheduleDateChanged = ((m_setOrders.m_ScheduleStartDate != m_dateScheduled) && (m_dateScheduled.GetTime() != 0));
		bool bScheduleDateChanged = (m_setOrders.m_ScheduleStartDate != m_dateScheduled.Format());
		bool bAMPMChanged = ((m_setOrders.m_ScheduledAM != (m_bAM == true)) && m_bSchedule);

		// Are we changing the schedule date/time, or are we unscheduling a previously scheduled job?
		if ((m_setOrders.m_Scheduled && bScheduling && ( bScheduleDateChanged || bAMPMChanged )) ||
			(m_setOrders.m_Scheduled != bScheduling))
		{
			if (!m_setOrders.IsFieldNull(&m_setOrders.m_ScheduleStartDate))
			{
				m_bRescheduled = true;
			}
			
			// add the OrderID to our list - only if it is a SOSI one though
			if ((m_setOrders.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED) || (m_setOrders.m_EntryMethodID == CGlobals::ENTRY_SOSI_IMPORTED_HANDMODIFIED))
			{
                m_listSOSIPOsWithModifiedSchedules.AddTail(m_setOrders.m_OrderID);
			}

			// add the OrderID to our list of SPN POs with modified schedules
			if ((m_setOrders.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED) || (m_setOrders.m_EntryMethodID == CGlobals::ENTRY_SPN_IMPORTED_HANDMODIFIED))
			{
                m_listSPNPOsWithModifiedSchedules.AddTail(m_setOrders.m_OrderID);
			}
			
			// add OrderID to our list of modified POs.
			m_listPOsWithModifiedSchedules.AddTail(m_setOrders.m_OrderID);

			m_setOrders.m_Scheduled = bScheduling;
		
			if (bScheduling && m_bSchedule)
			{
				m_setOrders.m_ScheduledAM = m_bAM ;
				m_setOrders.m_ScheduleStartDate = m_dateScheduled.Format("%Y-%m-%d") ;
				m_setOrders.m_ScheduleEndDate = m_dateScheduledEnd.Format("%Y-%m-%d");
			}
		}

		if (!bScheduling && !m_bSchedule)
		{
			// if unscheduling a previously scheduled job, move the scheduled date out 30 days.
			if (!m_setOrders.IsFieldNull(&m_setOrders.m_ScheduleStartDate))
			{
				COleDateTime time = CGlobals::GetCurrentSystemTime();
				COleDateTimeSpan ts = COleDateTimeSpan(30, 0, 0, 0);
				time += ts;
				m_setOrders.m_ScheduleStartDate = time.Format("%Y-%m-%d");
				m_setOrders.m_ScheduleEndDate = time.Format("%Y-%m-%d");
			}
		}
		
		m_setOrders.Update() ;

	}

	EnableUpdate(TRUE);
	RedrawAll();
}

void CGridSchedule::SetUnscheduled(long lCustomerId, long lOrderId)
{
	m_lCustomerId = lCustomerId ;
	m_lOrderId = lOrderId ;
	m_bSchedule = false ;

	m_setOrders.m_strFilter.Format("OrderId = '%d'", m_lOrderId) ;
	m_setOrders.Open() ;
	CSetMaterialType setMT(&g_dbFlooring);
	setMT.m_strFilter.Format("MaterialTypeID = %d", m_setOrders.m_MaterialTypeID);
	setMT.Open();
	m_bIsMeasure = (setMT.m_HDType == "M");
	setMT.Close();
	m_dateScheduled.ParseDateTime(m_setOrders.m_ScheduleStartDate);
	m_setOrders.m_strFilter.Format("CustomerID = '%d' and Scheduled = '1' and ScheduleStartDate = '%s' and Cancelled = '0' and Deleted = '0'", m_lCustomerId, m_setOrders.m_ScheduleStartDate) ;
	m_setOrders.Requery() ;
	Fill() ;
}

void CGridSchedule::SetScheduled(long lCustomerId, long lOrderId, COleDateTime dateSchedule, COleDateTime dateScheduleEnd, bool bAM)
{
	m_bSchedule = true ;
	m_lCustomerId = lCustomerId ;
	m_lOrderId = lOrderId ;
	m_bAM = bAM ;
	m_dateScheduled = dateSchedule ;
	m_dateScheduledEnd = dateScheduleEnd;

	m_setOrders.m_strFilter.Format("OrderId = '%d'", m_lOrderId) ;
	m_setOrders.Open() ;
	
	CSetMaterialType setMT(&g_dbFlooring);
	setMT.m_strFilter.Format("MaterialTypeID = %d", m_setOrders.m_MaterialTypeID);
	setMT.Open();
	m_bIsMeasure = (setMT.m_HDType == "M");
	setMT.Close();

	COleDateTime timeScheduleDate;
	if (m_setOrders.m_Scheduled == TRUE)
	{
		timeScheduleDate.ParseDateTime(m_setOrders.m_ScheduleStartDate);
	}
	m_setOrders.m_strFilter.Format("(CustomerID = '%d' and Scheduled = '0' and Cancelled = '0' and Deleted = '0') or (CustomerID = '%d' and Billed = '0' and Scheduled = '1' and Cancelled = '0' and Deleted = '0' and ScheduleStartDate = '%s') or (OrderId = '%d')", m_lCustomerId, m_lCustomerId, timeScheduleDate.Format("%Y-%m-%d"), m_lOrderId) ;
	m_setOrders.Requery() ;
	Fill() ;
}

void CGridSchedule::Fill()
{
	if (m_setOrders.IsOpen())
	{
		int iRow = 0;
		SetNumberRows (0, false) ;
		CSetMaterialType setMT(&g_dbFlooring) ;
		setMT.m_strFilter = "MaterialTypeID = -1";
		setMT.Open() ;
		
		//Add the Row Heading to the grid
		while (!m_setOrders.IsEOF())
		{
			setMT.m_strFilter.Format("[MaterialTypeID] = '%d'", m_setOrders.m_MaterialTypeID) ;
			setMT.Requery() ;

			bool bContinue = false;
			if (m_bIsMeasure && setMT.m_HDType == "M")
			{
				bContinue = true;
			}
			else if (!m_bIsMeasure && setMT.m_HDType == "I")
			{
				bContinue = true;
			}

			if (bContinue)
			{

				AppendRow() ;
				iRow = GetNumberRows() - 1;

				CString strHeading ;

				strHeading.Format("%d", m_setOrders.m_OrderID);
				
				QuickSetText(ID, iRow, strHeading);
				QuickSetReadOnly(ID, iRow, true) ;

				QuickSetText(PO, iRow, m_setOrders.m_PurchaseOrderNumber) ;
				QuickSetReadOnly(PO, iRow, true) ;

				QuickSetText(MATERIAL_TYPE, iRow, setMT.m_ShortName ) ;
				QuickSetReadOnly(MATERIAL_TYPE, iRow, true) ;

				CSetViewOrderSOMerchandiseDetails setDetails(&g_dbFlooring);
				setDetails.m_strFilter.Format("(([OrderID] = '%d') AND (Billable = '1') and (Deleted = 0) and (Quantity > 0))", m_setOrders.m_OrderID) ;
				setDetails.Open() ;
				double fSize = 0 ;
				bool bPresent = true ;
				while (!setDetails.IsEOF())
				{
					fSize += setDetails.m_Quantity ;
					bPresent = bPresent && ((setDetails.m_MaterialStatusID == 2) ||(setDetails.m_MaterialStatusID == 4) || (setDetails.m_MaterialStatusID == 11)) ;
					setDetails.MoveNext() ;
				}

				QuickSetNumberDecimals(MAT_SIZE, iRow, 2) ;
				QuickSetNumber(MAT_SIZE, iRow, fSize) ;
				QuickSetReadOnly(MAT_SIZE, iRow, true) ;

				QuickSetCellType(SCHEDULE, iRow, UGCT_CHECKBOX) ;
				if (CGlobals::OrderHasAlerts(m_setOrders.m_OrderID, false) || (CGlobals::OrderIsReviewed(m_setOrders.m_OrderID) == false))
				{
					QuickSetReadOnly(SCHEDULE, iRow, true) ;
					SetRowColor(iRow, CGlobals::COLOR_BLUE, CCFGrid::EnColorMode_TEXT);
					SetRowColor(iRow, CGlobals::COLOR_ALERT, CCFGrid::EnColorMode_BACK); 
				}
				else
				{
					QuickSetReadOnly(SCHEDULE, iRow, false) ;
					SetRowColor(iRow, CGlobals::COLOR_BLACK, CCFGrid::EnColorMode_TEXT);
					SetRowColor(iRow, CGlobals::COLOR_WHITE, CCFGrid::EnColorMode_BACK);
					QuickSetBool(SCHEDULE, iRow, m_bSchedule) ;
				}
							
				setDetails.Close() ;
				iRow++ ;
			}
			m_setOrders.MoveNext() ;
		}
		setMT.Close() ;
	}
}

bool CGridSchedule::IsRowDirty(long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	return false;
}

bool CGridSchedule::IsColumnDirty(int iCol, long lRow)
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iCol);
	return false;
}