/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DialogDatePicker.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "DialogDatePicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogDatePicker dialog


CDialogDatePicker::CDialogDatePicker(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDatePicker::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogDatePicker)
	m_dateSelected = CGlobals::GetCurrentSystemTime();
	//}}AFX_DATA_INIT
}


void CDialogDatePicker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDatePicker)
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calSelect);
//	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_dateSelected);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDatePicker, CDialog)
	//{{AFX_MSG_MAP(CDialogDatePicker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogDatePicker message handlers


void CDialogDatePicker::SetCaption(CString strCaption)
{
	m_strTitle = strCaption ;
}

BOOL CDialogDatePicker::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_strTitle) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

COleDateTime CDialogDatePicker::GetDate()
{
	return m_dateSelected ;
}

void CDialogDatePicker::OnOK() 
{
	COleDateTime time;
	m_calSelect.GetCurSel( time );
	m_dateSelected = COleDateTime(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0) ;
	CDialog::OnOK();
}
