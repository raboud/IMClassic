#pragma once
#include "afxwin.h"


// CDlgSelectDepartment dialog

class CDlgSelectDepartment : public CDialog
{
	DECLARE_DYNCREATE(CDlgSelectDepartment)

public:
	CDlgSelectDepartment(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectDepartment();

	int GetDepartmentID();

// Dialog Data
	enum { IDD = IDD_DEPT_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void FillComboBox();

	int m_iDeptID;

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboDepts;
protected:
	virtual void OnOK();
};

inline int CDlgSelectDepartment::GetDepartmentID()
{
	return m_iDeptID;
}
