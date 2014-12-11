// SetPayrollMessages.h : Declaration of the CSetPayrollMessages

#pragma once

// code generated on Thursday, August 21, 2003, 11:09 AM

class CSetPayrollMessages : public CRecordset
{
public:
	CSetPayrollMessages(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetPayrollMessages)

// Field/Param Data

	long	m_ID;
	CString	m_Message;
	COleDateTime	m_StartDate;
	COleDateTime	m_EndDate;

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


