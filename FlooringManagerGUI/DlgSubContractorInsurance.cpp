// DlgSubContractorInsurance.cpp : implementation file
//

#include "stdafx.h"
#include "Flooring.h"
#include "DlgSubContractorInsurance.h"
#include ".\dlgsubcontractorinsurance.h"
#include "SetSubContractor.h"


// DlgSubContractorInsurance dialog

IMPLEMENT_DYNAMIC(DlgSubContractorInsurance, CDialog)
DlgSubContractorInsurance::DlgSubContractorInsurance(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSubContractorInsurance::IDD, pParent)
	, m_strSubContractorName(_T(""))
{
	m_iSubContractorID = -1;
}

DlgSubContractorInsurance::~DlgSubContractorInsurance()
{
}

void DlgSubContractorInsurance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SUB_INSURANCE_SUBNAME, m_strSubContractorName);
	DDX_Control(pDX, IDC_SUB_INSURANCE_DOLLAR, m_editInsuranceDollar);
	DDX_Control(pDX, IDC_SUB_INSURANCE_PCT, m_editInsurancePct);
}


BEGIN_MESSAGE_MAP(DlgSubContractorInsurance, CDialog)
END_MESSAGE_MAP()


// DlgSubContractorInsurance message handlers

BOOL DlgSubContractorInsurance::OnInitDialog()
{
	CDialog::OnInitDialog();

	CSetSubContractor set(&g_dbFlooring);
	set.m_strFilter.Format("SubContractorID = %d", m_iSubContractorID);
	set.Open();
	if (!set.IsEOF())
	{
		m_strSubContractorName = set.m_LastName + ", " + set.m_FirstName;
	}
	set.Close();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSubContractorInsurance::OnOK()
{
	if (ValidateInsurance())
	{
		CDialog::OnOK();
	}
}

bool DlgSubContractorInsurance::ValidateInsurance(bool bShowMsg /*=true*/)
{
	bool bValid = true;
	CString strRate;
	CString strDollars;

	m_editInsuranceDollar.GetWindowText(strDollars);
	m_editInsurancePct.GetWindowText(strRate);
	
    double dDollars = 0.0;
	double dRate = 0.0;

	if (strDollars.GetLength() > 0)
	{
		dDollars = atof(strDollars);
	}

	if (strRate.GetLength() > 0)
	{
		dRate = atof(strRate) / 100;
	}

	if ((dDollars > 0) && (dRate > 0))
	{
		if (bShowMsg)
		{
			MessageBox("The amount to take out must EITHER be a dollar amount OR a percentage - you cannot enter both.", "Error!");
			m_editInsuranceDollar.SetFocus();
		}
		bValid = false;
	}

	if (bValid)
	{
		CString strSQL;
		strSQL.Format("UPDATE dbo.SubContractors SET InsuranceRate = %f, InsuranceDollarAmount = %f WHERE SubContractorID = %d", dRate, dDollars, m_iSubContractorID);
		g_dbFlooring.ExecuteSQL(strSQL);
	}

	return bValid;
}