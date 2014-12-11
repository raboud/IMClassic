// SetPONotes.h : Declaration of the CSetPONotes

#pragma once

// code generated on Wednesday, August 24, 2005, 9:08 AM

class CSetPONotes : public CRecordset
{
public:
	CSetPONotes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetPONotes)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_ID;
	long	m_OrderID;
	long	m_NoteTypeID;
	long    m_SpokeWithID;
	CString	m_ContactName;
	COleDateTime	m_DateTimeEntered;
	CString	m_NoteText;
	long	m_EnteredByUserID;
	BOOL	m_CustomerToCallBack;
	BOOL	m_Scheduled;
	BOOL	m_UnScheduled;
	BOOL	m_ScheduledAM;
	COleDateTime	m_ScheduledDate;
	BOOL	m_Deleted;
	BOOL	m_SentViaXML;
	COleDateTime	m_DateTimeSent;

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


