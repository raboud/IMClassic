/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// JobAssignment.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "JobAssignment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgJobAssignment dialog


CDlgJobAssignment::CDlgJobAssignment(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJobAssignment::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgJobAssignment)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgJobAssignment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJobAssignment)
	DDX_Control(pDX, IDC_DATE, m_datePicker);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgJobAssignment, CDialog)
	//{{AFX_MSG_MAP(CDlgJobAssignment)
	ON_NOTIFY(NM_KILLFOCUS, IDC_DATE, OnKillfocusDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgJobAssignment message handlers

BOOL CDlgJobAssignment::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_gridJobs.AttachGrid(this, IDC_JOBS) ;
	m_gridJobs.EnableWindow(false) ;
	m_gridJobs.ShowWindow(SW_HIDE) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgJobAssignment::OnKillfocusDate(NMHDR* /* pNMHDR */, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	COleDateTime timeSelect ;

	m_datePicker.GetTime(timeSelect) ;

	m_gridJobs.InitializeData(timeSelect) ;
	
	*pResult = 0;
}
