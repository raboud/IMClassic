/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DialogChecking.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DialogChecking.h"
#include "SetChecks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMultiDocTemplate* g_pTemplateReportCheck ;

/////////////////////////////////////////////////////////////////////////////
// CDialogChecking dialog


CDialogChecking::CDialogChecking(int iCheckID, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogChecking::IDD, pParent)
	, m_iCheckID(iCheckID) 	
	, m_iPaid(0)
	, m_fPaid(0.0)
{
	//{{AFX_DATA_INIT(CDialogChecking)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	CSetChecks setCheck(&g_dbFlooring) ;
	setCheck.m_strFilter.Format("[CheckID] = '%d'", m_iCheckID) ;
	setCheck.Open() ;

	m_fCheckAmount = atof(setCheck.m_Amount);
	setCheck.Close() ;

}


void CDialogChecking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogChecking)
	DDX_Control(pDX, IDC_CHECK, m_Paid);
	DDX_Control(pDX, IDC_CHECK_DIFF, m_statDifference);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogChecking, CDialog)
	//{{AFX_MSG_MAP(CDialogChecking)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE( wm_CHECKING, OnInvoiced)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogChecking message handlers

BOOL CDialogChecking::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_gridCheck.AttachGrid(this, IDC_CHECK_GRID) ;

	m_gridCheck.SetCheckID(m_iCheckID) ;
	m_gridCheck.ShowWindow(SW_SHOW) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CDialogChecking::OnInvoiced(WPARAM wParam, LPARAM lParam)
{
	m_iPaid = wParam ;
	m_fPaid = lParam / 100. ;
	CString strInvoiced ;
	strInvoiced.Format("%d - $%10.2f", m_iPaid, m_fPaid) ;
	m_Paid.SetWindowText(strInvoiced) ;

	CString strDiff ;
	strDiff.Format("$%10.2f", m_fCheckAmount - m_fPaid ) ;
	m_statDifference.SetWindowText(strDiff) ;

	return TRUE ;
}

void CDialogChecking::OnOK() 
{
	CWaitCursor cur ;

	m_gridCheck.UpdateRecordSet() ;	

	cur.Restore() ;

	if (MessageBox("Do you wish to print the check report?", "Check Report", MB_YESNO) == IDYES)
	{
		::CFI::InstallationManager::Reports::ReportHelper::PONote(m_iCheckID, true);
	}

	CDialog::OnOK();
}

void CDialogChecking::OnCancel() 
{
	if (m_gridCheck.IsDirty())
	{
		if (IDNO == MessageBox("Changes have been made.  Are you sure you want to quit?", "Data Changed", MB_YESNO))
		{
			return  ;
		}
	}

	CDialog::OnCancel();
}

