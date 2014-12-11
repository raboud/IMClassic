// DlgUnitTestResults.cpp : implementation file
//

#include "stdafx.h"
#include "DlgUnitTestResults.h"
#include "afxdialogex.h"


// DlgUnitTestResults dialog

IMPLEMENT_DYNAMIC(DlgUnitTestResults, CDialog)

DlgUnitTestResults::DlgUnitTestResults(CWnd* pParent /*=NULL*/)
	: CDialog(DlgUnitTestResults::IDD, pParent)
{

}

DlgUnitTestResults::~DlgUnitTestResults()
{
}

void DlgUnitTestResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UNIT_TEST_RESULTS_LIST, _listResults);
}


BEGIN_MESSAGE_MAP(DlgUnitTestResults, CDialog)
END_MESSAGE_MAP()


// DlgUnitTestResults message handlers

void DlgUnitTestResults::AddResults(CString testName, bool testResult)
{
	CString message;
	message.Format("%s - %s", testName, (testResult) ? "PASSED!" : "FAILED!");
	_listResults.AddString(message);
}

void DlgUnitTestResults::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}