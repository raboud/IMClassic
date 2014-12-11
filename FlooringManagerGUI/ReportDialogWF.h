/*----------------------------------------------------------------------
	Copyright © 2001-2010 JRS Technology, Inc.
-----------------------------------------------------------------------*/

#pragma once
#include <afxwinforms.h>
#include "flooring.h"

// CReportDialogWF dialog

struct SuReportParameter
{
	CString Name;
	CString Value;
};

class CReportDialogWF : public CWinFormsDialog<CFI::InstallationManager::Reports::DisplayReportCtrl>
{
	DECLARE_DYNAMIC(CReportDialogWF)

public:
	CReportDialogWF(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReportDialogWF();
	gcroot<CFI::InstallationManager::Reports::DisplayReportCtrl ^> m_ReportCtrl;
	CString ReportName;
	CString WindowTitle;
	bool PrintOnly;

	CList<SuReportParameter, SuReportParameter&> ReportParameters;

// Dialog Data
	enum { IDD = IDD_EMPTY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
		
	virtual void OnCloseButton(System::Object^ sender, System::EventArgs^ e);

	void AddParameter(CString Name, CString Value);
	
	BEGIN_DELEGATE_MAP( CReportDialogWF )
		EVENT_DELEGATE_ENTRY(OnCloseButton, System::Object^, System::EventArgs^);
	END_DELEGATE_MAP()
};
