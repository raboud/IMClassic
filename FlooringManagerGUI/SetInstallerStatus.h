// SetInstallerStatus.h : Declaration of the CSetInstallerStatus

#pragma once

// code generated on Tuesday, August 12, 2003, 10:59 AM

class CSetInstallerStatus : public CRecordset
{
public:
	CSetInstallerStatus(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetInstallerStatus)

// Field/Param Data

	long	m_ID;
	CString	m_Status;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


