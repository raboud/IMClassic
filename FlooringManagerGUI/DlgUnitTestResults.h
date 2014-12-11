#pragma once
#include "afxwin.h"
#include "resource.h"


// DlgUnitTestResults dialog

class DlgUnitTestResults : public CDialog
{
	DECLARE_DYNAMIC(DlgUnitTestResults)

public:
	DlgUnitTestResults(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgUnitTestResults();

	void AddResults(CString testName, bool testResult);

// Dialog Data
	enum { IDD = IDD_DLGUNITTESTRESULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void PostNcDestroy();

	DECLARE_MESSAGE_MAP()
public:
	CListBox _listResults;
};
