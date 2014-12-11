// ReportDialogWF.cpp : implementation file
//

#include "stdafx.h"
#include "ReportDialogWF.h"


// CReportDialogWF dialog 

IMPLEMENT_DYNAMIC(CReportDialogWF, CWinFormsDialog<CFI::InstallationManager::Reports::DisplayReportCtrl>)

CReportDialogWF::CReportDialogWF(CWnd* pParent /*=NULL*/)
	: CWinFormsDialog<CFI::InstallationManager::Reports::DisplayReportCtrl>(CReportDialogWF::IDD, pParent)
{
	ReportName = "";
	WindowTitle = "";
	PrintOnly = false;
}

CReportDialogWF::~CReportDialogWF()
{
}

void CReportDialogWF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReportDialogWF, CWinFormsDialog<CFI::InstallationManager::Reports::DisplayReportCtrl>)
END_MESSAGE_MAP()

BOOL CReportDialogWF::OnInitDialog()
{
	m_ReportCtrl = safe_cast<CFI::InstallationManager::Reports::DisplayReportCtrl ^>(this->GetControl());
	m_ReportCtrl->SetReportName(gcnew System::String(ReportName));
	m_ReportCtrl->SetPrintOnly(PrintOnly);
	m_ReportCtrl->btnClose->Click += MAKE_DELEGATE(System::EventHandler, OnCloseButton);	
	
	POSITION pos = ReportParameters.GetHeadPosition();
	while(pos)
	{
		SuReportParameter _param = ReportParameters.GetNext(pos);
		m_ReportCtrl->AddParameter(gcnew System::String(_param.Name), gcnew System::String(_param.Value));
	}


	CWinFormsDialog<CFI::InstallationManager::Reports::DisplayReportCtrl>::OnInitDialog();
	SetWindowTextA(WindowTitle);
	SetWindowLong(this->m_hWnd, GWL_STYLE, GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	ShowWindow(SW_SHOWMAXIMIZED);
			
	return TRUE;
}

void CReportDialogWF::OnCloseButton(System::Object ^sender, System::EventArgs ^e)
{
	UNREFERENCED_PARAMETER(e);
	UNREFERENCED_PARAMETER(sender);
	this->EndDialog(IDCANCEL);
}

void CReportDialogWF::AddParameter(CString Name, CString Value)
{
	//System::Object^ _value = gcnew System::Object();
	//_value = Value;
	//m_ReportCtrl->AddParameter(gcnew System::String(Name), gcnew System::String(Value));
	SuReportParameter _param;
	_param.Name = Name;
	_param.Value = Value;
	ReportParameters.AddHead(_param);
}

// CReportDialogWF message handlers
