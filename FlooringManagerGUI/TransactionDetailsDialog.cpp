// TransactionDetailsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "TransactionDetailsDialog.h"




// CTransactionDetailsDialog dialog

IMPLEMENT_DYNAMIC(CTransactionDetailsDialog, CDialog)
CTransactionDetailsDialog::CTransactionDetailsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTransactionDetailsDialog::IDD, pParent)
	, m_strTransactionDetails(_T(""))
{
	m_strTransactionDetails = "";
}

CTransactionDetailsDialog::~CTransactionDetailsDialog()
{
}

void CTransactionDetailsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSACTION_MARKET_COMBO, m_comboMarket);
	DDX_Control(pDX, IDC_TRANSACTION_DIVISION_COMBO, m_comboDivision);
	DDX_Control(pDX, IDC_TRANSACTION_TYPE_COMBO, m_comboType);
	DDX_Text(pDX, IDC_TRANSACTION_DETAILS_STATIC, m_strTransactionDetails);

	if (pDX->m_bSaveAndValidate)
	{
		m_iMarketID = m_comboMarket.GetItemData(m_comboMarket.GetCurSel());
		m_comboMarket.GetLBText(m_comboMarket.GetCurSel(), m_strMarket);
		m_iDivisionID = m_comboDivision.GetItemData(m_comboDivision.GetCurSel());
		m_comboDivision.GetLBText(m_comboDivision.GetCurSel(), m_strDivision);
		m_comboType.GetLBText(m_comboType.GetCurSel(), m_strType );
	}
}

BEGIN_MESSAGE_MAP(CTransactionDetailsDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_TRANSACTION_TYPE_COMBO, OnCbnSelchangeTransactionTypeCombo)
END_MESSAGE_MAP()


// CTransactionDetailsDialog message handlers

BOOL CTransactionDetailsDialog::OnInitDialog()
{
	ASSERT(m_strTransactionDetails.GetLength() > 0);

	CDialog::OnInitDialog();

	m_comboType.AddString(strOVERHEAD);
	m_comboType.AddString(strREGULAR);

	m_comboType.SetCurSel(m_comboType.FindStringExact(0, strREGULAR));
	m_comboMarket.SetInitialSelection("Metro Atlanta");
	m_comboDivision.SetInitialSelection("Soft Surface");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTransactionDetailsDialog::SetTransactionDetails(CString strDetails)
{
	m_strTransactionDetails = strDetails;
}

void CTransactionDetailsDialog::OnCbnSelchangeTransactionTypeCombo()
{
	m_comboMarket.EnableWindow( false == IsOverheadTx() );
	m_comboMarket.EnableWindow( false == IsOverheadTx() );
}
