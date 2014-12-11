/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

// DlgStoreSelection.cpp : implementation file
//

#include "stdafx.h"
#include "flooring.h"
#include "DlgStoreSelection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SetStores.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgStoreSelection dialog


CDlgStoreSelection::CDlgStoreSelection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStoreSelection::IDD, pParent)
	, m_strStores(_T(""))
	, m_strCurrentStoreNumber(_T(""))
	, m_bLimited(false)
{
	m_strStoreNumber = "" ;
	//{{AFX_DATA_INIT(CDlgStoreSelection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgStoreSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStoreSelection)
	DDX_Control(pDX, IDC_STORE_SELECTION, m_cbStoreSelection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStoreSelection, CDialog)
	//{{AFX_MSG_MAP(CDlgStoreSelection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStoreSelection message handlers

BOOL CDlgStoreSelection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if ( m_bLimited )
	{
		int iStart = 0 ;
		int iEnd = 0 ;
		do
		{
			iEnd = m_strStores.Find('\n', iStart) ;
			m_cbStoreSelection.AddString(m_strStores.Mid(iStart, iEnd - iStart)) ;
			iStart = iEnd + 1 ;
		} while (iStart < m_strStores.GetLength()) ;
	}
	else
	{

		CSetStores setStores(&g_dbFlooring)  ;
		setStores.m_strSort = "[StoreNumber]" ;
		setStores.Open() ;

		while (!setStores.IsEOF())
		{
			m_cbStoreSelection.AddString(setStores.m_StoreNumber) ;
			setStores.MoveNext() ;
		}
	}
	
	if (m_strCurrentStoreNumber.GetLength() > 0)
	{
		m_cbStoreSelection.SelectString(-1, m_strCurrentStoreNumber);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CDlgStoreSelection::GetStoreNumber()
{
	return m_strStoreNumber ;
}

void CDlgStoreSelection::OnOK() 
{
	// TODO: Add extra validation here
	m_cbStoreSelection.GetWindowText(m_strStoreNumber) ;

	
	CDialog::OnOK();
}

// Allow for limiting list of stores
void CDlgStoreSelection::SetStoreList(CString strStores)
{
	m_strStores = strStores ;
	m_bLimited = true ;
}

void CDlgStoreSelection::SetCurrentStoreNumber(CString strCurrentStoreNumber)
{
	m_strCurrentStoreNumber = strCurrentStoreNumber;
}
