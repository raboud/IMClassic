/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// CDialogSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DialogSchedule.h"
#include "DlgScheduleChangeReasonSelection.h"
#include "SetMaterialType.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSchedule dialog


CDialogSchedule::CDialogSchedule(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSchedule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSchedule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSchedule)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSchedule, CDialog)
	//{{AFX_MSG_MAP(CDialogSchedule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSchedule message handlers

BOOL CDialogSchedule::OnInitDialog() 
{

	CDialog::OnInitDialog();
	m_grid.AttachGrid(this, IDC_GRID) ;
	if (m_bSchedule)
	{
		m_grid.SetScheduled(m_lCustomerId, m_lOrderId, m_dateScheduled, m_dateScheduledEnd, m_bAM) ;
	}
	else
	{
		m_grid.SetUnscheduled(m_lCustomerId, m_lOrderId) ;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogSchedule::OnOK() 
{
	m_grid.Update() ;

	if (m_grid.m_listSPNPOsWithModifiedSchedules.GetCount() > 0)
	{
		// we have modified POs
		CString strSQL = "";
		int iOrderID = -1;
		POSITION pos = m_grid.m_listSPNPOsWithModifiedSchedules.GetHeadPosition();
		while (pos)
		{
			iOrderID = m_grid.m_listSPNPOsWithModifiedSchedules.GetNext(pos);
			strSQL.Format("EXEC up_QueueSPNAction %d, '%d'", CGlobals::iSPN_ACTION_SCHEDULE_PO, iOrderID);
			TRY
			{
				g_dbFlooring.ExecuteSQL(strSQL);
			}
			CATCH(CDBException, e)
			{
				MessageBox(e->m_strError, "Error!");
			}
			END_CATCH
		}
	}

	// copy OrderIDs from our grid collection up to the dialog collection
	if (m_grid.m_listPOsWithModifiedSchedules.GetCount() > 0)
	{
		POSITION pos = m_grid.m_listPOsWithModifiedSchedules.GetHeadPosition();
		while (pos)
		{
			m_listPOsWithModifiedSchedules.AddTail(m_grid.m_listPOsWithModifiedSchedules.GetNext(pos));
		}
	}

	CDialog::OnOK();
}

void CDialogSchedule::SetScheduled(long lCustomerId, long lOrderId, COleDateTime dateSchedule, COleDateTime dateScheduleEnd, bool bAM)
{
//	m_grid.SetScheduled(lCustomerId, lOrderId, dateSchedule, bAM) ;

	m_bSchedule = true ;
	m_lOrderId = lOrderId;
	m_lCustomerId = lCustomerId;
	m_dateScheduled = dateSchedule;
	m_dateScheduledEnd = dateScheduleEnd;
	m_bAM = bAM;

}

void CDialogSchedule::SetUnschedled(long lCustomerId, long lOrderId)
{
//	m_grid.SetUnschedled(lCustomerId, lOrderId) ;

	m_bSchedule = false ;
	m_lOrderId = lOrderId;
	m_lCustomerId = lCustomerId;

}
