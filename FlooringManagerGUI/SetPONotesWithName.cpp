// SetPONotesWithName.h : Implementation of the CSetPONotesWithName class



// CSetPONotesWithName implementation

// code generated on Tuesday, August 30, 2005, 2:03 PM

#include "stdafx.h"
#include "SetPONotesWithName.h"
#include "flooring.h"
IMPLEMENT_DYNAMIC(CSetPONotesWithName, CRecordset)

CSetPONotesWithName::CSetPONotesWithName(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_OrderID = 0;
	m_DateTimeEntered;
	m_NoteText = "";
	m_EnteredByName = L"";
	m_Scheduled = FALSE;
	m_Unscheduled = FALSE;
	m_NoteTypeID = 0;
	m_SentViaXML = FALSE;
	m_DateTimeSent;
	m_ScheduledDate;
	m_ScheduledAM = FALSE;
	m_nFields = 12;
	m_nDefaultType = dynaset;
}

CString CSetPONotesWithName::GetDefaultConnect()
{
	return _T("ODBC;DSN=Flooring;");
}

CString CSetPONotesWithName::GetDefaultSQL()
{
	return _T("[dbo].[vwPONotesWithName]");
}

void CSetPONotesWithName::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (CFieldExchange::Fixup == pFX->m_nOperation)
	{
		pFX->m_bField = TRUE;
	}
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[OrderID]"), m_OrderID);
	RFX_Date(pFX, _T("[DateTimeEntered]"), m_DateTimeEntered);
	RFX_Text(pFX, _T("[NoteText]"), m_NoteText, CGlobals::iMAX_ORDER_NOTES);
	RFX_Text(pFX, _T("[EnteredByName]"), m_EnteredByName);
	RFX_Bool(pFX, _T("[Scheduled]"), m_Scheduled);
	RFX_Bool(pFX, _T("[Unscheduled]"), m_Unscheduled);
	RFX_Long(pFX, _T("[NoteTypeID]"), m_NoteTypeID);
	RFX_Bool(pFX, _T("[SentViaXML]"), m_SentViaXML);
	RFX_Date(pFX, _T("[DateTimeSent]"), m_DateTimeSent);
	RFX_Date(pFX, _T("[ScheduledDate]"), m_ScheduledDate);
	RFX_Bool(pFX, _T("[ScheduledAM]"), m_ScheduledAM);

}
/////////////////////////////////////////////////////////////////////////////
// CSetPONotesWithName diagnostics

#ifdef _DEBUG
void CSetPONotesWithName::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetPONotesWithName::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


